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

struct objects
{
    GSList *list;
};

/*
 * pygtkextra_object_destroy
 *
 * This function is called when a GtkObject, that has been registered
 * with pygtkextra_object_register(), is destroyed.  It decrements the
 * reference count of all the Python objects associated with the
 * GtkObject.
 */
static void
pygtkextra_object_destroy(GtkObject *o, struct objects *objects)
{
    GSList *list = objects->list;

    PyGtk_BlockThreads();
    while (list) {
	GSList *prev = list;
	list = g_slist_next(list);
	Py_DECREF((PyObject *) prev->data);
	g_slist_free_1(prev);
    }
    g_free(objects);
    PyGtk_UnblockThreads();
}

/*
 * pygtkextra_object_register
 * 
 * Associates a Python object with a GtkObject and increments the
 * Python object's reference count.
 */
void
pygtkextra_object_register(GtkObject *o, const gchar *key, PyObject *object)
{
    struct objects *objects;
    
    objects = gtk_object_get_data(o, key);
    if (!objects) {
	objects = g_malloc(sizeof(*objects));
	objects->list = NULL;
	gtk_object_set_data(o, key, objects);
	gtk_signal_connect(o, "destroy",
			   GTK_SIGNAL_FUNC(pygtkextra_object_destroy),
			   objects);
    }
    Py_INCREF(object);
    objects->list = g_slist_prepend(objects->list, object);
}

/*
 * pygtkextra_object_unregister
 *
 * Removes a Python object from a GtkObject and decrements the Python
 * object's reference count.
 */
void
pygtkextra_object_unregister(GtkObject *o, const gchar *key, PyObject *object)
{
    struct objects *objects;

    objects = gtk_object_get_data(o, key);
    if (objects) {
	objects->list = g_slist_remove(objects->list, object);
	Py_DECREF(object);
    }
}

/*
 * pygtkextra_try_fopen
 *
 * Checks if it is possible to open a file and returns 0 on success or
 * -1 on failure.  The Python error indicator will be set if the file
 * cannot be opened.
 */
int
pygtkextra_try_fopen(const char *filename, const char *mode)
{
    FILE *fp;

    fp = fopen(filename, mode);
    if (!fp) {
	PyErr_SetFromErrno(PyExc_IOError);
	return -1;
    }
    fclose(fp);
    return 0;
}

/*
 * pygtkextra_convert_pixmap_data_to_vector
 *
 * Takes a list of pixmap data strings and puts them into a C vector.
 * The vector must be freed by the caller.  If the pixmap data cannot
 * be converted the Python error indicator will be set and NULL will
 * be returned.
 */
char **
pygtkextra_convert_pixmap_data_to_vector(PyObject *data)
{
    int len, i;
    char **vector;

    if (!PySequence_Check(data)) {
	PyErr_SetString(PyExc_TypeError, "pixmap data must be a sequence");
	return NULL;
    }
    len = PySequence_Length(data);
    vector = g_new(char *, len);
    for (i = 0; i < len; ++i) {
	PyObject *string;

	string = PySequence_GetItem(data, i);
	if (!PyString_Check(string)) {
	    PyErr_SetString(PyExc_TypeError, "sequence items must be strings");
	    g_free(vector);
	    Py_DECREF(string);
	    return NULL;
	}
	vector[i] = PyString_AS_STRING(string);
	Py_DECREF(string);
    }
    return vector;
}

/*
 * _pygtkextra_register_boxed_types
 */
void
_pygtkextra_register_boxed_types(PyObject *d)
{
#define register_tp(x) Py##x##_Type.ob_type = &PyType_Type; \
    PyDict_SetItemString(d, #x "Type", (PyObject *)&Py##x##_Type);

    pygtkextra_plot_data_import_numpy();
    pygtkextra_icon_list_init_links();

    PyGtk_RegisterBoxed(GTK_TYPE_SHEET_RANGE, (PyObject *(*)(gpointer))
			pygtkextra_sheet_range_new, NULL);
    PyGtk_RegisterBoxed(GTK_TYPE_PLOT_CANVAS_CHILD, (PyObject *(*)(gpointer))
			pygtkextra_plot_canvas_child_new, NULL);
    PyGtk_RegisterBoxed(GTK_TYPE_ICON_LIST_ITEM, (PyObject *(*)(gpointer))
			pygtkextra_icon_list_item_new, NULL);
	
    register_tp(GtkSheetChild);
    register_tp(GtkSheetCellBorder);
    register_tp(GtkSheetCellAttr);
    register_tp(GtkSheetRange);
    register_tp(GtkPlotText);
    register_tp(GtkPlotLine);
    register_tp(GtkPlotCanvasChild);
    register_tp(GtkPSFont);
}
