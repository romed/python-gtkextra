/* -*- Mode: C; c-basic-offset: 4 -*- */
/*
 * Python bindings for the GtkExtra widget set
 *
 * Copyright (C) 2000-2001 Andreas Voegele
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "pygtkextra-private.h"

/*
 * pygtkextra_color_combo_get_size
 *
 * Calculates the best size of the color combo's palette window from
 * the number of colors.  If neither the number of rows nor the number
 * of columns is given both values are calculated.  If only one value
 * is given the missing value is calculated.  The function returns the
 * product of the rows and columns, which may be greater than the
 * number of colors.
 */
static void
calculate_rows_and_columns(int number_of_colors, int *out_rows,
			   int *out_columns)
{
    int rows, columns;

    /* Ideally the palette window is quadratic. */
    columns = (int) ceil(sqrt(number_of_colors));
    if (columns == 0)
	columns = 1;
    rows = columns;

    /* The number of rows is changed until rows * columns = number_of_colors
       or rows and columns differ by more than 1. */
    while (rows > 1 && columns - rows <= 1) {
	div_t d;

	d = div(number_of_colors, rows);
	if (d.rem == 0) {
	    columns = d.quot;
	    goto cleanup;
	}

	--rows;
    }

    /* If nothing else works, columns is simply calculated from
       number_of_colors and rows.  In some cases rows * columns will
       be greater than number_of_colors. */
    columns = (int) ceil((double) number_of_colors / (double) rows);
    
cleanup:
    
    if (columns == 0)
	columns = 1;

    *out_rows = rows;
    *out_columns = columns;
}

int
pygtkextra_color_combo_get_size(int number_of_colors, int *in_out_rows,
				int *in_out_columns)
{
    int rows, columns;

    rows = *in_out_rows;
    columns = *in_out_columns;

    if (rows <= 0 && columns <= 0) {
	calculate_rows_and_columns(number_of_colors, &rows, &columns);
    } else if (rows <= 0) {
	rows = (int) ceil((double) number_of_colors / (double) columns);
	if (rows == 0)
	    rows = 1;
    } else if (columns <= 0) {
	columns = (int) ceil((double) number_of_colors / (double) rows);
	if (columns == 0)
	    columns = 1;
    }

    *in_out_rows = rows;
    *in_out_columns = columns;

    return rows * columns;
}

/*
 * pygtkextra_get_colorname
 *
 * Checks if a Python object contains a color name, a GdkColor or a
 * 3-tuple of RGB values.  Returns a color name, that must be freed
 * by the calling function with g_free(), or NULL in case of an
 * error.  The Python error indicator is not set.
 */
char *
pygtkextra_get_colorname(PyObject *py_color)
{
    char *colorname = NULL;

    if (PyString_Check(py_color)) {
	colorname = g_strdup(PyString_AS_STRING(py_color));
    } else if (PyGdkColor_Check(py_color)) {
	GdkColor *color = PyGdkColor_Get(py_color);
	colorname = g_strdup_printf("#%04X%04X%04X",
				    (unsigned) color->red,
				    (unsigned) color->green,
				    (unsigned) color->blue);
    } else if (PySequence_Check(py_color)
	       && PySequence_Length(py_color) == 3) {
	PyObject *red, *green, *blue;
	    
	red = PySequence_GetItem(py_color, 0);
	green = PySequence_GetItem(py_color, 1);
	blue = PySequence_GetItem(py_color, 2);

	if (red && PyInt_Check(red) && green && PyInt_Check(green)
	    && blue && PyInt_Check(blue)) {
	    colorname = g_strdup_printf("#%04X%04X%04X",
					(unsigned) PyInt_AS_LONG(red),
					(unsigned) PyInt_AS_LONG(green),
					(unsigned) PyInt_AS_LONG(blue));
	}

	Py_XDECREF(red);
	Py_XDECREF(green);
	Py_XDECREF(blue);
    }
    return colorname;
}
