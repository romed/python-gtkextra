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
 * GtkIconListItem
 */

/*
 * Since GtkFileList uses the link element of the GtkIconListItem
 * structure to store pointers to C objects, we have to make sure that
 * only NULL pointers and Python objects are replaced by other Python
 * objects and that only the reference count of Python objects is
 * modified.
 */

static GTree *Links;

static gint
compare_pointers(gconstpointer a, gconstpointer b)
{
    if (a == b) return 0;
    if (a > b) return 1;
    return -1;
}

void
pygtkextra_icon_list_init_links(void)
{
    Links = g_tree_new(compare_pointers);
}

static gpointer
pygtkextra_icon_list_handle_link(PyObject *obj, int add)
{
    gpointer link;

    if (obj == Py_None)
	link = NULL;
    else if (PyCObject_Check(obj))
	link = (gpointer) PyCObject_AsVoidPtr(obj);
    else {
	link = (gpointer) obj;
	if (add) {
	    guint count;

	    count = GPOINTER_TO_UINT(g_tree_lookup(Links, link));
	    ++count;
	    g_tree_insert(Links, link, GUINT_TO_POINTER(count));
	    Py_INCREF(obj);
	}
    }
    return link;
}

gpointer
pygtkextra_icon_list_register_link(PyObject *obj)
{
    return pygtkextra_icon_list_handle_link(obj, 1);
}

gpointer
pygtkextra_icon_list_get_link(PyObject *obj)
{
    return pygtkextra_icon_list_handle_link(obj, 0);
}

int
pygtkextra_icon_list_unregister_link(gpointer link)
{
    int success = 0;
    guint count;
    
    if ((count = GPOINTER_TO_UINT(g_tree_lookup(Links, link)))) {
	--count;
	if (count)
	    g_tree_insert(Links, link, GUINT_TO_POINTER(count));
	else
	    g_tree_remove(Links, link);
	Py_DECREF((PyObject *) link);
	success = 1;
    }
    return success;
}

static void
incref_link(gpointer link)
{
    if (g_tree_lookup(Links, link)) {
	Py_INCREF((PyObject *) link);
    }
}

static void
decref_link(gpointer link)
{
    if (g_tree_lookup(Links, link)) {
	Py_DECREF((PyObject *) link);
    }
}

static PyObject *
get_object_from_link(gpointer link)
{
    PyObject *obj;

    if (link) {
	if (g_tree_lookup(Links, link)) {
	    obj = (PyObject *) link;
	    Py_INCREF(obj);
	} else
	    obj = PyCObject_FromVoidPtr(link, NULL);
    } else {
	obj = Py_None;
	Py_INCREF(obj);
    }
    return obj;
}

static void
PyGtkIconListItem_Dealloc(PyGtkIconListItem_Object *self)
{
    if (self->item->link)
	decref_link(self->item->link);
    PyMem_DEL(self);
}

static PyObject *
PyGtkIconListItem_get_entry(PyGtkIconListItem_Object *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":GtkIconListItem.get_entry"))
	return NULL;
    if (self->item->entry)
	return PyGtk_New(GTK_OBJECT(self->item->entry));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
PyGtkIconListItem_get_pixmap(PyGtkIconListItem_Object *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":GtkIconListItem.get_pixmap"))
	return NULL;
    if (self->item->pixmap)
	return PyGtk_New(GTK_OBJECT(self->item->pixmap));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
PyGtkIconListItem_set_pixmap(PyGtkIconListItem_Object *self, PyObject *args)
{
    GdkBitmap *bitmap;
    PyObject *pixmap, *mask;
    
    if (!PyArg_ParseTuple(args, "O!O:GtkIconListItem.set_pixmap",
			  &PyGdkWindow_Type, &pixmap, &mask))
	return NULL;
    if (PyGdkWindow_Check(mask))
	bitmap = PyGdkWindow_Get(mask);
    else if (mask == Py_None)
	bitmap = NULL;
    else {
	PyErr_SetString(PyExc_TypeError,
			"mask argument must be a GdkBitmap or None");
	return NULL;
    }
    gtk_icon_list_set_pixmap(self->item, PyGdkWindow_Get(pixmap), bitmap);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
PyGtkIconListItem_get_link(PyGtkIconListItem_Object *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":GtkIconListItem.get_link"))
	return NULL;
    return get_object_from_link(self->item->link);
}

static PyObject *
PyGtkIconListItem_set_link(PyGtkIconListItem_Object *self, PyObject *args)
{
    PyObject *object;
    
    if (!PyArg_ParseTuple(args, "O:GtkIconListItem.set_link", &object))
	return NULL;
    if (self->item->link) {
	if (!(pygtkextra_icon_list_unregister_link(self->item->link)
	      || PyCObject_Check(object))) {
	    PyErr_SetString(PyExc_RuntimeError, "cannot overwrite link");
	    return NULL;
	}
	decref_link(self->item->link);
    }
    if ((self->item->link = pygtkextra_icon_list_register_link(object)))
	incref_link(self->item->link);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef PyGtkIconListItem_methods[] =
{
    { "get_entry", (PyCFunction) PyGtkIconListItem_get_entry, METH_VARARGS },
    { "get_pixmap", (PyCFunction) PyGtkIconListItem_get_pixmap, METH_VARARGS },
    { "set_pixmap", (PyCFunction) PyGtkIconListItem_set_pixmap, METH_VARARGS },
    { "get_link", (PyCFunction) PyGtkIconListItem_get_link, METH_VARARGS },
    { "set_link", (PyCFunction) PyGtkIconListItem_set_link, METH_VARARGS },
    { NULL, NULL, 0 }
};

static struct memberlist PyGtkIconListItem_members[] =
{
    { "x", T_UINT, offsetof(GtkIconListItem, x), RO },
    { "y", T_UINT, offsetof(GtkIconListItem, y), RO },
    { "state", T_INT, offsetof(GtkIconListItem, state), RO },
    { "entry_label", T_STRING, offsetof(GtkIconListItem, entry_label), RO },
    { "label", T_STRING, offsetof(GtkIconListItem, label), RO },
    { "pixmap", -1, 0, RO },
    { "entry", -1, 0, RO },
    { "link", -1, 0 },
    { NULL }
};

static PyObject *
PyGtkIconListItem_GetAttr(PyGtkIconListItem_Object *self, char *attr)
{
    PyObject *value;
    
    if (strcmp(attr, "pixmap") == 0) {
	if (self->item->pixmap)
	    return PyGtk_New(GTK_OBJECT(self->item->pixmap));
	Py_INCREF(Py_None);
	return Py_None;
    }
    if (strcmp(attr, "entry") == 0) {
	if (self->item->entry)
	    return PyGtk_New(GTK_OBJECT(self->item->entry));
	Py_INCREF(Py_None);
	return Py_None;
    }
    if (strcmp(attr, "link") == 0)
	return get_object_from_link(self->item->link);
    value = PyMember_Get((char *) self->item, PyGtkIconListItem_members, attr);
    if (!value) {
	if (PyErr_ExceptionMatches(PyExc_AttributeError)) {
	    PyErr_Clear();
	    value = Py_FindMethod(PyGtkIconListItem_methods,
				  (PyObject *) self, attr);
	}
    }
    return value;
}

static int
PyGtkIconListItem_SetAttr(PyGtkIconListItem_Object *self, char *attr,
			  PyObject *value)
{
    if (strcmp(attr, "link") == 0) {
	if (!value) {
	    PyErr_SetString(PyExc_TypeError, "cannot delete attribute");
	    return -1;
	}
	if (self->item->link) {
	    if (!(pygtkextra_icon_list_unregister_link(self->item->link)
		  || PyCObject_Check(value))) {
		PyErr_SetString(PyExc_RuntimeError, "cannot overwrite link");
		return -1;
	    }
	    decref_link(self->item->link);
	}
	if ((self->item->link = pygtkextra_icon_list_register_link(value)))
	    incref_link(self->item->link);
	return 0;
    }
    return PyMember_Set((char *) self->item, PyGtkIconListItem_members,
			attr, value);
}

static int
PyGtkIconListItem_Compare(PyGtkIconListItem_Object *self,
			  PyGtkIconListItem_Object *v)
{
    if (self->item == v->item) return 0;
    if (self->item > v->item) return -1;
    return 1;
}

PyTypeObject PyGtkIconListItem_Type =
{
    PyObject_HEAD_INIT(&PyType_Type)
    0,
    "GtkIconListItem",
    sizeof(PyGtkIconListItem_Object),
    0,
    (destructor) PyGtkIconListItem_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkIconListItem_GetAttr,
    (setattrfunc) PyGtkIconListItem_SetAttr,
    (cmpfunc) PyGtkIconListItem_Compare,
    (reprfunc) 0,
    0,
    0,
    0,
};

PyObject *
pygtkextra_icon_list_item_new(GtkIconListItem *item)
{
    PyGtkIconListItem_Object *self;

    if (!item) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    
    self = (PyGtkIconListItem_Object *)
	PyObject_NEW(PyGtkIconListItem_Object, &PyGtkIconListItem_Type);
    if (!self)
	return NULL;
    self->item = item;
    if (self->item->link)
	incref_link(self->item->link);
    return (PyObject *) self;
}

int
PyGtkIconListItem_Check(PyObject *obj)
{
    return (obj->ob_type == &PyGtkIconListItem_Type);
}

GtkIconListItem *
PyGtkIconListItem_Get(PyObject *obj)
{
    return ((PyGtkIconListItem_Object *) obj)->item;
}
