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
#ifndef WITHOUT_NUMPY
#include <Numeric/arrayobject.h>
#else
#define PyArray_NOTYPE 0
#endif

static const gchar *plot_function_key = "pygtkextra::plot_function";

static const gchar *array_types_key  =
"pygtkextra::array_types";

static const char *axis_name[] = { "X", "Y", "Z", "A",
				   "DX", "DY", "DZ", "DA" };

#define PLOT_FUNCTION_TYPE_PLOT 0
#define PLOT_FUNCTION_TYPE_PLOT3D 1
#define PLOT_FUNCTION_TYPE_ITERATOR 2

static char *
get_ordinal_suffix(int i)
{
    switch (i % 10) {
    case 1:
	return "st";
    case 2:
	return "nd";
    case 3:
	return "rd";
    default:
	return "th";
    }
}

/*
 * pygtkextra_plot_data_register_plot_function
 * pygtkextra_plot_data_register_plot3d_function
 * pygtkextra_plot_data_register_plot_iterator
 *
 * Associates a Python plot function and its arguments with a
 * GtkPlotData instance.  Must be called internally when a plot
 * function is created with GtkPlotData.__init__(),
 * GtkPlot.add_function() etc.
 */
static gboolean
pygtkextra_plot_data_register_plot_function_real(GtkPlotData *data,
						 PyObject *function,
						 PyObject *extra,
						 int type)
{
    int i, len, num_values;
    PyObject *args, *value, **vector;

    switch (type) {
    case PLOT_FUNCTION_TYPE_PLOT:
    case PLOT_FUNCTION_TYPE_ITERATOR:
	num_values = 1;
	break;
    case PLOT_FUNCTION_TYPE_PLOT3D:
	num_values = 2;
	break;
    }
    
    /* Create a tuple for the plot function's arguments. */
    len = (extra) ? PyTuple_Size(extra) : 0;
    args = PyTuple_New(num_values + len);
    if (!args)
	return FALSE;
    switch (type) {
    case PLOT_FUNCTION_TYPE_PLOT:
    case PLOT_FUNCTION_TYPE_PLOT3D:
	for (i = 0; i < num_values; ++i) {
	    value = PyFloat_FromDouble(0.0);
	    if (!value) {
		Py_DECREF(args);
		return FALSE;
	    }
	    PyTuple_SET_ITEM(args, i, value);
	}
	break;
    case PLOT_FUNCTION_TYPE_ITERATOR:
	value = PyInt_FromLong(0);
	if (!value) {
	    Py_DECREF(args);
	    return FALSE;
	}
	PyTuple_SET_ITEM(args, i, value);
	break;
    }
    /* Copy the extra arguments. */
    for (i = 0; i < len; ++i) {
	PyObject *item = PyTuple_GetItem(extra, i);
	Py_INCREF(item);
	PyTuple_SET_ITEM(args, i + num_values, item);
    }
    /* The plot function and the argument tuple are stored in a C vector. */
    vector = g_new(PyObject *, 2);
    if (!vector) {
	Py_DECREF(args);
	return FALSE;
    }
    Py_INCREF(function);
    vector[0] = function;
    vector[1] = args;
    gtk_object_set_data(GTK_OBJECT(data), plot_function_key, vector);
    return TRUE;
}

gboolean
pygtkextra_plot_data_register_plot_function(GtkPlotData *data,
					    PyObject *function,
					    PyObject *extra)
{
    return pygtkextra_plot_data_register_plot_function_real(data, function,
							    extra,
							    PLOT_FUNCTION_TYPE_PLOT);
}

gboolean
pygtkextra_plot_data_register_plot3d_function(GtkPlotData *data,
					      PyObject *function,
					      PyObject *extra)
{
    return pygtkextra_plot_data_register_plot_function_real(data, function,
							    extra,
							    PLOT_FUNCTION_TYPE_PLOT3D);
}

gboolean
pygtkextra_plot_data_register_plot_iterator(GtkPlotData *data,
					    PyObject *function,
					    PyObject *extra)
{
    return pygtkextra_plot_data_register_plot_function_real(data, function,
							    extra,
							    PLOT_FUNCTION_TYPE_ITERATOR);
}


/*
 * pygtkextra_plot_data_call_plot_function
 * pygtkextra_plot_data_call_plot3d_function
 * pygtkextra_plot_data_call_plot_iterator
 *
 * Calls the Python plot function belonging to a GtkPlotData instance.  This
 * function must be used as the C plot function when a plot function is
 * created with GtkPlotData.__init__(), GtkPlot.add_function() etc.
 *
 * 2-D plot functions get an X value and all the extra arguments that
 * were passed to GtkPlotData.__init__() or GtkPlot.add_function().
 * The plot function should return the Y value or None, if it isn't
 * possible to calculate the Y value.
 *
 * 3-D plot functions get X and Y and return Z or None.
 *
 * Iterators get the number of the point and return a tuple of 8 or 9
 * values, ie. (X, Y, Z, A, DX, DY, DZ, DA[, LABEL]) or None.
 */
gdouble
pygtkextra_plot_data_call_plot_function(GtkPlot *plot, GtkPlotData *data,
					gdouble x, gboolean *out_error)
{
    gdouble y;
    PyObject **vector, *function, *args, *value, *result;

    y = 0.0;
    
    PyGtk_BlockThreads();

    *out_error = TRUE;

    /* Get the Python function and the argument tuple that belong to
       the given GtkPlotData instance. */
    vector = (PyObject **) gtk_object_get_data(GTK_OBJECT(data),
					       plot_function_key);
    if (!vector) {
	PyErr_SetString(PyExc_RuntimeError, "cannot find plot function");
	goto cleanup;
    }
    function = vector[0];
    args = vector[1];

    /* Put the X value into the first item of the argument tuple. */
    /*
    value = PyFloat_FromDouble(x);
    if (!value)
	goto cleanup;
    PyTuple_SetItem(args, 0, value);
    */
    value = PyTuple_GET_ITEM(args, 0);
    ((PyFloatObject *) value)->ob_fval = x;

    /* Call the Python function. */
    result = PyEval_CallObject(function, args);
    if (!result)
	goto cleanup;

    /* Get the Y value. */
    if (PyFloat_Check(result)) {
	y = PyFloat_AS_DOUBLE(result);
	*out_error = FALSE;
    } else if (PyNumber_Check(result) && (value = PyNumber_Float(result))) {
	y = PyFloat_AS_DOUBLE(value);
	Py_DECREF(value);
	*out_error = FALSE;
    } else if (result != Py_None) {
	PyErr_SetString(PyExc_TypeError,
			"plot function must return number or None");
    }
    
    Py_DECREF(result);

cleanup:

    if (PyErr_Occurred()) {
	PyErr_Print();
	PyErr_Clear();
    }
    
    PyGtk_UnblockThreads();

    return y;
}

gdouble
pygtkextra_plot_data_call_plot3d_function(GtkPlot *plot, GtkPlotData *data,
					  gdouble x, gdouble y,
					  gboolean *out_error)
{
    gdouble z;
    PyObject **vector, *function, *args, *value, *result;

    z = 0.0;
    
    PyGtk_BlockThreads();

    *out_error = TRUE;

    /* Get the Python function and the argument tuple that belong to
       the given GtkPlotData instance. */
    vector = (PyObject **) gtk_object_get_data(GTK_OBJECT(data),
					       plot_function_key);
    if (!vector) {
	PyErr_SetString(PyExc_RuntimeError, "cannot find plot function");
	goto cleanup;
    }
    function = vector[0];
    args = vector[1];

    /* Put the X and Y value into the first two items of the argument tuple. */
    /*
    value = PyFloat_FromDouble(x);
    if (!value)
	goto cleanup;
    PyTuple_SetItem(args, 0, value);
    value = PyFloat_FromDouble(y);
    if (!value)
	goto cleanup;
    PyTuple_SetItem(args, 1, value);
    */
    value = PyTuple_GET_ITEM(args, 0);
    ((PyFloatObject *) value)->ob_fval = x;
    value = PyTuple_GET_ITEM(args, 1);
    ((PyFloatObject *) value)->ob_fval = y;

    /* Call the Python function. */
    result = PyEval_CallObject(function, args);
    if (!result)
	goto cleanup;

    /* Get the Z value. */
    if (PyFloat_Check(result)) {
	z = PyFloat_AS_DOUBLE(result);
	*out_error = FALSE;
    } else if (PyNumber_Check(result) && (value = PyNumber_Float(result))) {
	z = PyFloat_AS_DOUBLE(value);
	Py_DECREF(value);
	*out_error = FALSE;
    } else if (result != Py_None) {
	PyErr_SetString(PyExc_TypeError,
			"plot function must return number or None");
    }
    
    Py_DECREF(result);

cleanup:

    if (PyErr_Occurred()) {
	PyErr_Print();
	PyErr_Clear();
    }
    
    PyGtk_UnblockThreads();

    return z;
}

void
pygtkextra_plot_data_call_plot_iterator(GtkPlot *plot, GtkPlotData *data,
					gint iter,
					gdouble *out_x, 
					gdouble *out_y, 
					gdouble *out_z,
					gdouble *out_a,
					gdouble *out_dx, 
					gdouble *out_dy, 
					gdouble *out_dz,
					gdouble *out_da,
					gchar **out_label,
					gboolean *out_error)
{
    PyObject **vector, *function, *args, *value, *result;

    PyGtk_BlockThreads();

    *out_error = TRUE;

    /* Get the Python function and the argument tuple that belong to
       the given GtkPlotData instance. */
    vector = (PyObject **) gtk_object_get_data(GTK_OBJECT(data),
					       plot_function_key);
    if (!vector) {
	PyErr_SetString(PyExc_RuntimeError, "cannot find plot function");
	goto cleanup;
    }
    function = vector[0];
    args = vector[1];

    /* Put the index into the first item of the argument tuple. */
    /*
    value = PyInt_FromLong(iter);
    if (!value)
	goto cleanup;
    PyTuple_SetItem(args, 0, value);
    */
    value = PyTuple_GET_ITEM(args, 0);
    ((PyIntObject *) value)->ob_ival = iter;

    /* Call the Python function. */
    result = PyEval_CallObject(function, args);
    if (!result)
	goto cleanup;

    if (PySequence_Check(result)) {
	int n = PySequence_Length(result);
	if (n < 8 || n > 9) {
	    PyErr_SetString(PyExc_TypeError,
			    "plot iterator must return 9-sequence or None");
	} else {
	    int i;
	    gdouble *v[8];
	    PyObject *item;

	    v[0] = out_x; v[1] = out_y; v[2] = out_z; v[3] = out_a;
	    v[4] = out_dx; v[5] = out_dy; v[6] = out_dz; v[7] = out_da;
	    *out_error = FALSE;
	    for (i = 0; i < 8; ++i) {
		item = PySequence_GetItem(result, i);
		if (item == Py_None) {
		    *v[i] = 0.0;
		} else if (PyFloat_Check(item)) {
		    *v[i] = PyFloat_AS_DOUBLE(item);
		} else if (PyNumber_Check(item)
			   && (value = PyNumber_Float(item))) {
		    *v[i] = PyFloat_AS_DOUBLE(value);
		    Py_DECREF(value);
		} else {
		    gchar buf[256];

		    *out_error = TRUE;
		    g_snprintf(buf, sizeof(buf),
			       "%d%s item must be number or None",
			       i + 1, get_ordinal_suffix(i + 1));
		    PyErr_SetString(PyExc_TypeError, buf);
		    Py_XDECREF(item);
		    Py_DECREF(result);
		    goto cleanup;
		}
		Py_XDECREF(item);
	    }
	    *out_label = NULL;
	    if (n >= 9) {
		item = PySequence_GetItem(result, 8);
		if (PyString_Check(item)) {
		    *out_label = PyString_AS_STRING(item);
		} else if (item != Py_None) {
		    *out_error = TRUE;
		    PyErr_SetString(PyExc_TypeError,
				    "last item must be string or None");
		}
		Py_XDECREF(item);
	    }
	}
    } else if (result != Py_None) {
	PyErr_SetString(PyExc_TypeError,
			"plot iterator must return sequence or None");
    }
    
    Py_DECREF(result);

cleanup:

    if (PyErr_Occurred()) {
	PyErr_Print();
	PyErr_Clear();
    }
    
    PyGtk_UnblockThreads();
}

/*
 * new_points
 *
 * Stores the items of a Numerical Python array or a Python sequence in a
 * C vector of double values.  Returns the number of elements or -1.
 * The C vector must be freed with g_free().
 */
static gint
new_points(PyObject *sequence, gdouble **out_points, int *out_array_type)
{
    int n = 0;
    gdouble *points = NULL;

    *out_array_type = PyArray_NOTYPE;
#ifndef WITHOUT_NUMPY
    if (PyArray_Check(sequence)) {
	PyArrayObject *array;

	array = (PyArrayObject *)
	    PyArray_ContiguousFromObject(sequence, PyArray_DOUBLE, 1, 1);
	if (!array)
	    return -1;
	n = array->dimensions[0];
	points = g_new(gdouble, n);
	memcpy(points, array->data, n * sizeof(double));
	Py_DECREF(array);
	*out_array_type = ((PyArrayObject *) sequence)->descr->type_num;
    } else
#endif
	if (PySequence_Check(sequence)) {
	n = PySequence_Length(sequence);
	if (n > 0) {
	    int i;
	    
	    points = g_new(gdouble, n);
	    for (i = 0; i < n; ++i) {
		PyObject *item, *value;

		item = PySequence_GetItem(sequence, i);
		if (PyFloat_Check(item)) {
		    points[i] = PyFloat_AS_DOUBLE(item);
		} else if (PyNumber_Check(item)
			   && (value = PyNumber_Float(item))) {
		    points[i] = PyFloat_AS_DOUBLE(value);
		    Py_DECREF(value);
		} else {
		    PyErr_SetString(PyExc_TypeError,
				    "sequence items must be numbers");
		    Py_DECREF(item);
		    g_free(points);
		    points = NULL;
		    return -1;
		}
		Py_DECREF(item);
	    }
	}
    } else if (sequence != Py_None) {
	PyErr_SetString(PyExc_TypeError, "argument must be sequence or None");
	return -1;
    }
    *out_points = points;
    return n;
}

/*
 * resize_points
 *
 * Resizes a C vector of double values.  New elements are initialized with
 * 0.0.
 */
static gdouble *
resize_points(gdouble *points, gint old_n, gint new_n)
{
    gdouble *new_points;

    new_points = g_renew(gdouble, points, new_n);
    if (new_points)
	while (old_n < new_n)
	    new_points[old_n++] = 0.0;
    else if (new_n > 0)
	g_free(points);
    return new_points;
}

/*
 * new_array
 *
 * Returns the contents of a C vector as a Numerical Python array or a
 * Python sequence.
 */
static PyObject *
new_array(gdouble *points, int n, int array_type)
{
    int i;
    PyObject *sequence;

    /* If there aren't any values an empty list is returned.  An empty
       object is more useful than None since the user can right away
       start to append items to it. */
    if (!points)
	n = 0;

    if (array_type == PyArray_NOTYPE) {
	if (!(sequence = PyList_New(n)))
	    return NULL;
	for (i = 0; i < n; ++i) {
	    PyObject *value;
	    
	    value = PyFloat_FromDouble(points[i]);
	    if (!value) {
		Py_DECREF(sequence);
		return NULL;
	    }
	    PyList_SET_ITEM(sequence, i, value);
	}
    }
#ifndef WITHOUT_NUMPY
    else {
	int dimensions[1];
	PyArrayObject *array;

	dimensions[0] = n;
	if (!(array = (PyArrayObject *)
	      PyArray_FromDims(1, dimensions, array_type)))
	    return NULL;
	switch (array_type) {
	case PyArray_DOUBLE:
	    memcpy(array->data, points, n * sizeof(double));
	    break;
	case PyArray_FLOAT:
	    for (i = 0; i < n; ++i)
		((float *) array->data)[i] = (float) points[i];
	    break;
	case PyArray_LONG:
	    for (i = 0; i < n; ++i)
		((long *) array->data)[i] = (long) points[i];
	    break;
	case PyArray_INT:
	    for (i = 0; i < n; ++i)
		((int *) array->data)[i] = (int) points[i];
	    break;
	case PyArray_SHORT:
	    for (i = 0; i < n; ++i)
		((short *) array->data)[i] = (short) points[i];
	    break;
	case PyArray_SBYTE:
	    for (i = 0; i < n; ++i)
		((signed char *) array->data)[i] = (signed char) points[i];
	    break;
	case PyArray_UBYTE:
	    for (i = 0; i < n; ++i)
		((unsigned char *) array->data)[i] = (unsigned char) points[i];
	    break;
	case PyArray_CHAR:
	    for (i = 0; i < n; ++i)
		((char *) array->data)[i] = (char) points[i];
	    break;
	default:
	    PyErr_SetString(PyExc_TypeError, "type not supported");
	    Py_DECREF((PyObject *) array);
	    return NULL;
	}
	sequence = (PyObject *) array;
    }
#endif
    return sequence;
}

/*
 * get_array_types
 *
 * The data types of the Numerical Python arrays passed to
 * GtkPlotData.set_points() etc. are stored in a C vector, that is
 * associated with the GtkPlotData instance.  The type information is
 * used in GtkPlotData.get_points() etc.
 *
 * 0 -> X
 * 1 -> Y
 * 2 -> Z
 * 3 -> A
 * 4 -> DX
 * 5 -> DY
 * 6 -> DZ
 * 7 -> DA
 */
static int *
get_array_types(GtkPlotData *data)
{
    int *array_types;

    array_types = (int *)
	gtk_object_get_data(GTK_OBJECT(data), array_types_key);
    if (!array_types) {
	int i;

	array_types = g_new(int, 8);
	if (!array_types) {
	    PyErr_SetString(PyExc_RuntimeError,
			    "could not create array types");
	    return NULL;
	}

	for (i = 0; i < 8; ++i)
	    array_types[i] = PyArray_NOTYPE;
	gtk_object_set_data(GTK_OBJECT(data), array_types_key, array_types);
    }
    return array_types;
}

/*
 * resize_labels
 *
 * Resizes a C vector of dynamically allocated strings.  New elements
 * are initialized with NULL.
 */
static gchar **
resize_labels(gchar **labels, gint old_n, gint new_n)
{
    gchar **new_labels;

    while (old_n > new_n)
	g_free(labels[--old_n]);
    new_labels = g_renew(gchar *, labels, new_n);
    if (new_labels)
	while (old_n < new_n)
	    new_labels[old_n++] = NULL;
    else if (new_n > 0)
	g_free(labels);
    return new_labels;
}

/*
 * free_labels
 *
 * Frees a C vector of dynamically allocated strings.
 */
static void
free_labels(GtkPlotData *data)
{
    gchar **labels;
    gboolean show_labels;

    labels = gtk_plot_data_get_labels(data, &show_labels);
    if (labels) {
	int i, n;
	
	n = gtk_plot_data_get_numpoints(data);
	for (i = 0; i < n; ++i) {
	    g_free(labels[i]);
	}
	g_free(labels);
	gtk_plot_data_set_labels(data, NULL);
    }
}

/*
 * wrong_number_of_values
 *
 * Sets the Python error indicator.
 */
static void
wrong_number_of_values(int which, int expected, int given)
{
    gchar buf[256];

    g_snprintf(buf, sizeof(buf),
	       "wrong number of %s values; expected %d, got %d",
	       axis_name[which], expected, given);
    PyErr_SetString(PyExc_ValueError, buf);
}

void
pygtkextra_plot_data_destroy_cb(GtkPlotData *data, gpointer *user_data)
{
    gint n;
    int *array_types;
    PyObject *object, **vector;

    array_types = (int *)
	gtk_object_get_data(GTK_OBJECT(data), array_types_key);
    if (array_types) {
	g_free(array_types);
    }
    
    vector = (PyObject **)
	gtk_object_get_data(GTK_OBJECT(data), plot_function_key);
    if (vector) {
	Py_DECREF(vector[0]);
	Py_DECREF(vector[1]);
	g_free(vector);
    }

    object = (PyObject *) gtk_plot_data_get_link(data);
    Py_XDECREF(object);
    gtk_plot_data_set_link(data, NULL);

    if (!data->is_function) {
	g_free(gtk_plot_data_get_x(data, &n));
	gtk_plot_data_set_x(data, NULL);
	g_free(gtk_plot_data_get_y(data, &n));
	gtk_plot_data_set_y(data, NULL);
	g_free(gtk_plot_data_get_z(data, &n));
	gtk_plot_data_set_z(data, NULL);
    }
    g_free(gtk_plot_data_get_a(data, &n));
    gtk_plot_data_set_a(data, NULL);
    g_free(gtk_plot_data_get_dx(data, &n));
    gtk_plot_data_set_dx(data, NULL);
    g_free(gtk_plot_data_get_dy(data, &n));
    gtk_plot_data_set_dy(data, NULL);
    g_free(gtk_plot_data_get_dz(data, &n));
    gtk_plot_data_set_dz(data, NULL);
    g_free(gtk_plot_data_get_da(data, &n));
    gtk_plot_data_set_da(data, NULL);

    free_labels(data);
}

PyObject *
pygtkextra_plot_data_set_points(GtkPlotData *data, PyObject *x, PyObject *y,
				PyObject *dx, PyObject *dy, gint new_n)
{
    gint old_n, nx, ny, ndx, ndy;
    gdouble *x_points = NULL, *y_points = NULL, *dx_points = NULL,
	*dy_points = NULL;
    int *array_types, x_array_type, y_array_type, dx_array_type,
	dy_array_type;

    array_types = get_array_types(data);
    if (!array_types)
	return NULL;
    old_n = gtk_plot_data_get_numpoints(data);
    if ((nx = new_points(x, &x_points, &x_array_type)) < 0
	|| (ny = new_points(y, &y_points, &y_array_type)) < 0
	|| (ndx = new_points(dx, &dx_points, &dx_array_type)) < 0
	|| (ndy = new_points(dy, &dy_points, &dy_array_type)) < 0)
	goto cleanup;
    if (new_n < 0)
	new_n = nx;
    if (nx != new_n) {
	wrong_number_of_values(0, new_n, nx);
	goto cleanup;
    }
    if (ny != new_n) {
	wrong_number_of_values(1, new_n, ny);
	goto cleanup;
    }
    if (ndx != new_n && ndx != 0) {
	wrong_number_of_values(4, new_n, ndx);
	goto cleanup;
    }
    if (ndy != new_n && ndy != 0) {
	wrong_number_of_values(5, new_n, ndy);
	goto cleanup;
    }
    g_free(gtk_plot_data_get_x(data, &nx));
    g_free(gtk_plot_data_get_y(data, &ny));
    g_free(gtk_plot_data_get_dx(data, &ndx));
    g_free(gtk_plot_data_get_dy(data, &ndy));
    gtk_plot_data_set_points(data, x_points, y_points, dx_points, dy_points,
			     new_n);
    /* Resize the other vectors. */
    if (new_n != old_n) {
	gdouble *points;
	gchar **labels;
	gboolean show_labels;

	/* Resize the Z points */
	points = gtk_plot_data_get_z(data, &old_n);
	if (points) {
	    points = resize_points(points, old_n, new_n);
	    gtk_plot_data_set_z(data, points);
	}
	
	/* Resize the A points */
	points = gtk_plot_data_get_a(data, &old_n);
	if (points) {
	    points = resize_points(points, old_n, new_n);
	    gtk_plot_data_set_a(data, points);
	}

	/* Resize the DZ points */
	points = gtk_plot_data_get_dz(data, &old_n);
	if (points) {
	    points = resize_points(points, old_n, new_n);
	    gtk_plot_data_set_dz(data, points);
	}
	
	/* Resize the DA points */
	points = gtk_plot_data_get_da(data, &old_n);
	if (points) {
	    points = resize_points(points, old_n, new_n);
	    gtk_plot_data_set_da(data, points);
	}

	/* Resize the labels */
	labels = gtk_plot_data_get_labels(data, &show_labels);
	if (labels) {
	    labels = resize_labels(labels, old_n, new_n);
	    gtk_plot_data_set_labels(data, labels);
	}
    }
    array_types[0] = x_array_type;
    array_types[1] = y_array_type;
    array_types[4] = dx_array_type;
    array_types[5] = dy_array_type;
    Py_INCREF(Py_None);
    return Py_None;
cleanup:
    g_free(x_points);
    g_free(y_points);
    g_free(dx_points);
    g_free(dy_points);
    return NULL;
}

PyObject *
pygtkextra_plot_data_get_points(GtkPlotData *data)
{
    gint n;
    gdouble *points;
    PyObject *x, *y, *dx, *dy;
    int *array_types;
    
    array_types = get_array_types(data);
    if (!array_types)
	return NULL;
    points = gtk_plot_data_get_x(data, &n);
    if (!(x = new_array(points, n, array_types[0])))
	return NULL;
    points = gtk_plot_data_get_y(data, &n);
    if (!(y = new_array(points, n, array_types[1]))) {
	Py_DECREF(x);
	return NULL;
    }
    points = gtk_plot_data_get_dx(data, &n);
    if (!(dx = new_array(points, n, array_types[4]))) {
	Py_DECREF(x);
	Py_DECREF(y);
	return NULL;
    }
    points = gtk_plot_data_get_dy(data, &n);
    if (!(dy = new_array(points, n, array_types[5]))) {
	Py_DECREF(x);
	Py_DECREF(y);
	Py_DECREF(dx);
	return NULL;
    }
    return Py_BuildValue("(NNNNi)", x, y, dx, dy, (int) n);
}

PyObject *
pygtkextra_plot_data_set_numpoints(GtkPlotData *data, gint new_n)
{
    gint old_n;
    gdouble *points;
    gchar **labels;
    gboolean show_labels;

    if (new_n < 0) {
	PyErr_SetString(PyExc_ValueError,
			"argument must be zero or positive");
	return NULL;
    }

    old_n = gtk_plot_data_get_numpoints(data);
    if (new_n == old_n)
	goto cleanup;
	
    /* Resize the X points */
    points = gtk_plot_data_get_x(data, &old_n);
    points = resize_points(points, old_n, new_n);
    gtk_plot_data_set_x(data, points);
    
    /* Resize the Y points */
    points = gtk_plot_data_get_y(data, &old_n);
    points = resize_points(points, old_n, new_n);
    gtk_plot_data_set_y(data, points);
    
    /* Resize the Z points */
    points = gtk_plot_data_get_z(data, &old_n);
    if (points) {
	points = resize_points(points, old_n, new_n);
	gtk_plot_data_set_z(data, points);
    }
    
    /* Resize the A points */
    points = gtk_plot_data_get_a(data, &old_n);
    if (points) {
	points = resize_points(points, old_n, new_n);
	gtk_plot_data_set_a(data, points);
    }
    
    /* Resize the DX points */
    points = gtk_plot_data_get_dx(data, &old_n);
    if (points) {
	points = resize_points(points, old_n, new_n);
	gtk_plot_data_set_dx(data, points);
    }
    
    /* Resize the DY points */
    points = gtk_plot_data_get_dy(data, &old_n);
    if (points) {
	points = resize_points(points, old_n, new_n);
	gtk_plot_data_set_dy(data, points);
    }
    
    /* Resize the DZ points */
    points = gtk_plot_data_get_dz(data, &old_n);
    if (points) {
	points = resize_points(points, old_n, new_n);
	gtk_plot_data_set_dz(data, points);
    }
    
    /* Resize the DA points */
    points = gtk_plot_data_get_da(data, &old_n);
    if (points) {
	points = resize_points(points, old_n, new_n);
	gtk_plot_data_set_da(data, points);
    }
    
    /* Resize the labels */
    labels = gtk_plot_data_get_labels(data, &show_labels);
    if (labels) {
	labels = resize_labels(labels, old_n, new_n);
	gtk_plot_data_set_labels(data, labels);
    }
    
    gtk_plot_data_set_numpoints(data, new_n);

cleanup:
    
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *
pygtkextra_plot_data_set_array(GtkPlotData *data, int which,
			       PyObject *sequence)
{
    gint old_n, new_n;
    gdouble *old_points, *points;
    int *array_types, array_type;

    array_types = get_array_types(data);
    if (!array_types)
	return NULL;
    if ((new_n = new_points(sequence, &points, &array_type)) < 0)
	return NULL;
    switch (which) {
    case 0:
	old_points = gtk_plot_data_get_x(data, &old_n);
	break;
    case 1:
	old_points = gtk_plot_data_get_y(data, &old_n);
	break;
    case 2:
	old_points = gtk_plot_data_get_z(data, &old_n);
	break;
    case 3:
	old_points = gtk_plot_data_get_a(data, &old_n);
	break;
    case 4:
	old_points = gtk_plot_data_get_dx(data, &old_n);
	break;
    case 5:
	old_points = gtk_plot_data_get_dy(data, &old_n);
	break;
    case 6:
	old_points = gtk_plot_data_get_dz(data, &old_n);
	break;
    case 7:
	old_points = gtk_plot_data_get_da(data, &old_n);
	break;
    default:
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    /* Check if the number of points is correct.  X and Y cannot be
       set to NULL if the number of points is > 0. */
    if (new_n != old_n
	&& (which < 2 || (which >= 2 && new_n != 0))) {
	wrong_number_of_values(which, old_n, new_n);
	g_free(points);
	return NULL;
    }
    g_free(old_points);
    switch (which) {
    case 0:
	gtk_plot_data_set_x(data, points);
	break;
    case 1:
	gtk_plot_data_set_y(data, points);
	break;
    case 2:
	gtk_plot_data_set_z(data, points);
	break;
    case 3:
	gtk_plot_data_set_a(data, points);
	break;
    case 4:
	gtk_plot_data_set_dx(data, points);
	break;
    case 5:
	gtk_plot_data_set_dy(data, points);
	break;
    case 6:
	gtk_plot_data_set_dz(data, points);
	break;
    case 7:
	gtk_plot_data_set_da(data, points);
	break;
    }
    array_types[which] = array_type;
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *
pygtkextra_plot_data_get_array(GtkPlotData *data, int which)
{
    gint n;
    gdouble *points;
    int *array_types;
    
    array_types = get_array_types(data);
    if (!array_types)
	return NULL;
    switch (which) {
    case 0:
	points = gtk_plot_data_get_x(data, &n);
	break;
    case 1:
	points = gtk_plot_data_get_y(data, &n);
	break;
    case 2:
	points = gtk_plot_data_get_z(data, &n);
	break;
    case 3:
	points = gtk_plot_data_get_a(data, &n);
	break;
    case 4:
	points = gtk_plot_data_get_dx(data, &n);
	break;
    case 5:
	points = gtk_plot_data_get_dy(data, &n);
	break;
    case 6:
	points = gtk_plot_data_get_dz(data, &n);
	break;
    case 7:
	points = gtk_plot_data_get_da(data, &n);
	break;
    default:
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    return new_array(points, n, array_types[which]);
}

PyObject *
pygtkextra_plot_data_set_labels(GtkPlotData *data, PyObject *sequence)
{
    gchar **labels = NULL;

    if (PySequence_Check(sequence)) {
	int num_labels;
	
	num_labels = PySequence_Length(sequence);
	if (num_labels > 0) {
	    int i, n;
	    
	    n = gtk_plot_data_get_numpoints(data);
	    if (num_labels != n) {
		char buf[256];

		g_snprintf(buf, sizeof(buf),
			   "wrong number of labels; expected %d, got %d",
			   n, num_labels);
		PyErr_SetString(PyExc_ValueError, buf);
		return NULL;
	    }
	
	    labels = g_new(gchar *, n);
	    for (i = 0; i < n; ++i) {
		gchar *string;
		PyObject *item;

		string = NULL;
		item = PySequence_GetItem(sequence, i);
		if (PyString_Check(item)) {
		    string = g_strdup(PyString_AS_STRING(item));
		} else if (item != Py_None) {
		    PyErr_SetString(PyExc_TypeError,
				    "sequence items must be strings or None");
		    while (i > 0) {
			--i;
			g_free(labels[i]);
		    }
		    g_free(labels);
		    Py_DECREF(item);
		    return NULL;
		}
		labels[i] = string;
		Py_DECREF(item);
	    }
	}
    } else if (sequence != Py_None) {
	PyErr_SetString(PyExc_TypeError, "argument must be sequence or None");
	return NULL;
    }
    free_labels(data);
    gtk_plot_data_set_labels(data, labels);
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *
pygtkextra_plot_data_get_labels(GtkPlotData *data)
{
    gchar **labels;
    gboolean show_labels;
    PyObject *list;
    
    labels = gtk_plot_data_get_labels(data, &show_labels);
    if (labels) {
	int i, n;

	n = gtk_plot_data_get_numpoints(data);
	list = PyList_New(n);
	if (!list)
	    return NULL;
	for (i = 0; i < n; ++i) {
	    PyObject *label;

	    label = PyString_FromString((labels[i]) ? labels[i] : "");
	    if (!label) {
		Py_DECREF(list);
		return NULL;
	    }
	    PyList_SET_ITEM(list, i, label);
	}
    } else {
	/* If there aren't any labels an empty list is returned.
	   An empty list is more useful than None since the user
	   can right away start to append items to it. */
	list = PyList_New(0);
	if (!list)
	    return NULL;
    }
    return list;
}

PyObject *
pygtkextra_plot_surface_set_points(GtkPlotSurface *data, PyObject *x,
				   PyObject *y, PyObject *z, PyObject *dx,
				   PyObject *dy, PyObject *dz, gint new_nx,
				   gint new_ny)
{
    gint new_nz, nx, ny, nz, ndx, ndy, ndz;
    gdouble *x_points = NULL, *y_points = NULL, *z_points = NULL,
	*dx_points = NULL, *dy_points = NULL, *dz_points = NULL;
    int *array_types, x_array_type, y_array_type, z_array_type,
	dx_array_type, dy_array_type, dz_array_type;

    array_types = get_array_types(GTK_PLOT_DATA(data));
    if (!array_types)
	return NULL;
    if ((nx = new_points(x, &x_points, &x_array_type)) < 0
	|| (ny = new_points(y, &y_points, &y_array_type)) < 0
	|| (nz = new_points(z, &z_points, &z_array_type)) < 0
	|| (ndx = new_points(dx, &dx_points, &dx_array_type)) < 0
	|| (ndy = new_points(dy, &dy_points, &dy_array_type)) < 0
	|| (ndz = new_points(dz, &dz_points, &dz_array_type)) < 0)
	goto cleanup;
    new_nz = new_nx * new_ny;
    if (nx != new_nz) {
	wrong_number_of_values(0, new_nz, nx);
	goto cleanup;
    }
    if (ny != new_nz) {
	wrong_number_of_values(1, new_nz, ny);
	goto cleanup;
    }
    if (nz != new_nz) {
	wrong_number_of_values(2, new_nz, nz);
	goto cleanup;
    }
    if (ndx != new_nz && ndx != 0) {
	wrong_number_of_values(4, new_nz, ndx);
	goto cleanup;
    }
    if (ndy != new_nz && ndy != 0) {
	wrong_number_of_values(5, new_nz, ndy);
	goto cleanup;
    }
    if (ndz != new_nz && ndz != 0) {
	wrong_number_of_values(6, new_nz, ndz);
	goto cleanup;
    }
    g_free(gtk_plot_surface_get_x(data, &nx));
    g_free(gtk_plot_surface_get_y(data, &ny));
    g_free(gtk_plot_surface_get_z(data, &nx, &ny));
    g_free(gtk_plot_surface_get_dx(data));
    g_free(gtk_plot_surface_get_dy(data));
    g_free(gtk_plot_surface_get_dz(data));
    gtk_plot_surface_set_points(data, x_points, y_points, z_points, dx_points,
				dy_points, dz_points, new_nx, new_ny);
    array_types[0] = x_array_type;
    array_types[1] = y_array_type;
    array_types[2] = z_array_type;
    array_types[4] = dx_array_type;
    array_types[5] = dy_array_type;
    array_types[6] = dz_array_type;
    Py_INCREF(Py_None);
    return Py_None;
cleanup:
    g_free(x_points);
    g_free(y_points);
    g_free(z_points);
    g_free(dx_points);
    g_free(dy_points);
    g_free(dz_points);
    return NULL;
}

PyObject *
pygtkextra_plot_surface_get_points(GtkPlotSurface *data)
{
    gint nx, ny, nz;
    gdouble *points;
    PyObject *x, *y, *z, *dx, *dy, *dz;
    int *array_types;
    
    array_types = get_array_types(GTK_PLOT_DATA(data));
    if (!array_types)
	return NULL;
    nz = gtk_plot_surface_get_nx(data) * gtk_plot_surface_get_ny(data);
    points = gtk_plot_surface_get_x(data, &nx);
    if (!(x = new_array(points, nz, array_types[0])))
	return NULL;
    points = gtk_plot_surface_get_y(data, &ny);
    if (!(y = new_array(points, nz, array_types[1]))) {
	Py_DECREF(x);
	return NULL;
    }
    points = gtk_plot_surface_get_z(data, &nx, &ny);
    if (!(z = new_array(points, nz, array_types[2]))) {
	Py_DECREF(x);
	Py_DECREF(y);
	return NULL;
    }
    points = gtk_plot_surface_get_dx(data);
    if (!(dx = new_array(points, nz, array_types[4]))) {
	Py_DECREF(x);
	Py_DECREF(y);
	Py_DECREF(z);
	return NULL;
    }
    points = gtk_plot_surface_get_dy(data);
    if (!(dy = new_array(points, nz, array_types[5]))) {
	Py_DECREF(x);
	Py_DECREF(y);
	Py_DECREF(z);
	Py_DECREF(dx);
	return NULL;
    }
    points = gtk_plot_surface_get_dz(data);
    if (!(dz = new_array(points, nz, array_types[6]))) {
	Py_DECREF(x);
	Py_DECREF(y);
	Py_DECREF(z);
	Py_DECREF(dx);
	Py_DECREF(dy);
	return NULL;
    }
    return Py_BuildValue("(NNNNNNii)", x, y, z, dx, dy, dz, (int) nx,
			 (int) ny);
}

PyObject *
pygtkextra_plot_surface_set_nx(GtkPlotSurface *data, gint new_nx)
{
    gint old_nx, ny, old_nz, new_nz;
    gdouble *points;

    if (new_nx < 0) {
	PyErr_SetString(PyExc_ValueError,
			"argument must be zero or positive");
	return NULL;
    }

    old_nx = gtk_plot_surface_get_nx(data);
    if (new_nx == old_nx)
	goto cleanup;
    ny = gtk_plot_surface_get_ny(data);
    old_nz = old_nx * ny;
    new_nz = new_nx * ny;

    /* Resize the X points */
    points = gtk_plot_surface_get_x(data, &old_nx);
    points = resize_points(points, old_nz, new_nz);
    gtk_plot_surface_set_x(data, points);
    
    /* Resize the Y points */
    points = gtk_plot_surface_get_y(data, &ny);
    points = resize_points(points, old_nz, new_nz);
    gtk_plot_surface_set_x(data, points);
    
    /* Resize the Z points */
    points = gtk_plot_surface_get_z(data, &old_nx, &ny);
    points = resize_points(points, old_nz, new_nz);
    gtk_plot_surface_set_z(data, points);
    
    /* Resize the DX points */
    points = gtk_plot_surface_get_dx(data);
    if (points) {
	points = resize_points(points, old_nz, new_nz);
	gtk_plot_surface_set_dx(data, points);
    }
    
    /* Resize the DY points */
    points = gtk_plot_surface_get_dy(data);
    if (points) {
	points = resize_points(points, old_nz, new_nz);
	gtk_plot_surface_set_dy(data, points);
    }
    
    /* Resize the DZ points */
    points = gtk_plot_surface_get_dz(data);
    if (points) {
	points = resize_points(points, old_nz, new_nz);
	gtk_plot_surface_set_dz(data, points);
    }

    gtk_plot_surface_set_nx(data, new_nx);

cleanup:
    
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *
pygtkextra_plot_surface_set_ny(GtkPlotSurface *data, gint new_ny)
{
    gint nx, old_ny, old_nz, new_nz;
    gdouble *points;

    if (new_ny < 0) {
	PyErr_SetString(PyExc_ValueError,
			"argument must be zero or positive");
	return NULL;
    }

    old_ny = gtk_plot_surface_get_ny(data);
    if (new_ny == old_ny)
	goto cleanup;
    nx = gtk_plot_surface_get_nx(data);
    old_nz = nx * old_ny;
    new_nz = nx * new_ny;

    /* Resize the X points */
    points = gtk_plot_surface_get_x(data, &nx);
    points = resize_points(points, old_nz, new_nz);
    gtk_plot_surface_set_x(data, points);
    
    /* Resize the Y points */
    points = gtk_plot_surface_get_y(data, &old_ny);
    points = resize_points(points, old_nz, new_nz);
    gtk_plot_surface_set_x(data, points);
    
    /* Resize the Z points */
    points = gtk_plot_surface_get_z(data, &nx, &old_ny);
    if (points) {
	points = resize_points(points, old_nz, new_nz);
	gtk_plot_surface_set_z(data, points);
    }
    
    /* Resize the DX points */
    points = gtk_plot_surface_get_dx(data);
    if (points) {
	points = resize_points(points, old_nz, new_nz);
	gtk_plot_surface_set_dx(data, points);
    }
    
    /* Resize the DY points */
    points = gtk_plot_surface_get_dy(data);
    if (points) {
	points = resize_points(points, old_nz, new_nz);
	gtk_plot_surface_set_dy(data, points);
    }
    
    /* Resize the DZ points */
    points = gtk_plot_surface_get_dz(data);
    if (points) {
	points = resize_points(points, old_nz, new_nz);
	gtk_plot_surface_set_dz(data, points);
    }

    gtk_plot_surface_set_ny(data, new_ny);

cleanup:
    
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *
pygtkextra_plot_surface_set_array(GtkPlotSurface *data, int which,
				  PyObject *sequence)
{
    gint old_n, new_n, nx, ny;
    gdouble *old_points, *points;
    int *array_types, array_type;

    array_types = get_array_types(GTK_PLOT_DATA(data));
    if (!array_types)
	return NULL;
    if ((new_n = new_points(sequence, &points, &array_type)) < 0)
	return NULL;
    switch (which) {
    case 0:
	old_points = gtk_plot_surface_get_x(data, &nx);
	break;
    case 1:
	old_points = gtk_plot_surface_get_y(data, &nx);
	break;
    case 2:
	old_points = gtk_plot_surface_get_z(data, &nx, &ny);
	break;
    case 4:
	old_points = gtk_plot_surface_get_dx(data);
	break;
    case 5:
	old_points = gtk_plot_surface_get_dy(data);
	break;
    case 6:
	old_points = gtk_plot_surface_get_dz(data);
	break;
    default:
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    /* Check if the number of points is correct.  X, Y and Z cannot be
       set be set to NULL if the number of points is > 0. */
    old_n = gtk_plot_surface_get_nx(data) * gtk_plot_surface_get_ny(data);
    if (new_n != old_n
	&& (which < 3 || (which >= 3 && new_n != 0))) {
	wrong_number_of_values(which, old_n, new_n);
	g_free(points);
	return NULL;
    }
    g_free(old_points);
    switch (which) {
    case 0:
	gtk_plot_surface_set_x(data, points);
	break;
    case 1:
	gtk_plot_surface_set_y(data, points);
	break;
    case 2:
	gtk_plot_surface_set_z(data, points);
	break;
    case 4:
	gtk_plot_surface_set_dx(data, points);
	break;
    case 5:
	gtk_plot_surface_set_dy(data, points);
	break;
    case 6:
	gtk_plot_surface_set_dz(data, points);
	break;
    }
    array_types[which] = array_type;
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *
pygtkextra_plot_surface_get_array(GtkPlotSurface *data, int which)
{
    gint n, nx, ny;
    gdouble *points;
    int *array_types;
    
    array_types = get_array_types(GTK_PLOT_DATA(data));
    if (!array_types)
	return NULL;
    switch (which) {
    case 0:
	points = gtk_plot_surface_get_x(data, &nx);
	break;
    case 1:
	points = gtk_plot_surface_get_y(data, &nx);
	break;
    case 2:
	points = gtk_plot_surface_get_z(data, &nx, &ny);
	break;
    case 4:
	points = gtk_plot_surface_get_dx(data);
	break;
    case 5:
	points = gtk_plot_surface_get_dy(data);
	break;
    case 6:
	points = gtk_plot_surface_get_dz(data);
	break;
    default:
	PyErr_SetString(PyExc_ValueError, "out of bounds");
	return NULL;
    }
    n = gtk_plot_surface_get_nx(data) * gtk_plot_surface_get_ny(data);
    return new_array(points, n, array_types[which]);
}

int
pygtkextra_plot_data_import_numpy(void)
{
#ifndef WITHOUT_NUMPY
    import_array();
#endif
    return 0;
}
