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
 * pygtkextra_sheet_unref_links
 */
void
pygtkextra_sheet_unref_links(GtkSheet *sheet, GtkSheetRange *range)
{
    gint row0, col0, rowi, coli, row;

    /* Decrements the reference count of all objects linked to cells
       in the given range.  If range is NULL the reference count of
       all objects is decremented. */
    
    if (range) {
	row0 = range->row0;
	col0 = range->col0;
	rowi = range->rowi;
	coli = range->coli;
    } else {
	row0 = 0;
	col0 = 0;
	rowi = sheet->maxallocrow;
	coli = sheet->maxalloccol;
    }
    for (row = row0; row <= rowi; ++row) {
	gint col;
	
	for (col = col0; col <= coli; ++col) {
	    PyObject *object;

	    object = (PyObject *) gtk_sheet_get_link(sheet, row, col);
	    Py_XDECREF(object);
	}
    }
}

/*
 * pygtkextra_sheet_destroy_cb
 */
void
pygtkextra_sheet_destroy_cb(GtkSheet *sheet, gpointer user_data)
{
    PyGtk_BlockThreads();
    pygtkextra_sheet_unref_links(sheet, NULL);
    PyGtk_UnblockThreads();
}
