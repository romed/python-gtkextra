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
 * GtkSheetCellAttr
 *
 * This type is returned by gtk_sheet_get_attributes().  In Python it has an
 * additional attribute called "is_allocated".
 */

static void
PyGtkSheetCellAttr_Dealloc(PyGtkSheetCellAttr_Object *self)
{
    gdk_font_unref(self->cell_attr.font);
    PyMem_DEL(self);
}

static struct memberlist PyGtkSheetCellAttr_members[] =
{
    { "justification", T_INT, offsetof(GtkSheetCellAttr, justification), RO },
    { "font", -1, 0, RO },
    { "foreground", -1, 0, RO },
    { "background", -1, 0, RO },
    { "border", -1, 0, RO },
    { "is_editable", T_INT, offsetof(GtkSheetCellAttr, is_editable), RO },
    { "is_visible", T_INT, offsetof(GtkSheetCellAttr, is_visible), RO },
    { "is_allocated", -1, 0, RO },
    { NULL }
};

static PyObject *
PyGtkSheetCellAttr_GetAttr(PyGtkSheetCellAttr_Object *self, char *attr)
{
    if (strcmp(attr, "font") == 0)
	return PyGdkFont_New(self->cell_attr.font);
    if (strcmp(attr, "foreground") == 0)
	return PyGdkColor_New(&self->cell_attr.foreground);
    if (strcmp(attr, "background") == 0)
	return PyGdkColor_New(&self->cell_attr.background);
    if (strcmp(attr, "border") == 0)
	return pygtkextra_sheet_cell_border_new(&self->cell_attr.border);
    if (strcmp(attr, "is_allocated") == 0)
	return PyInt_FromLong(self->is_allocated);
    return PyMember_Get((char *) &self->cell_attr, PyGtkSheetCellAttr_members,
			attr);
}

static int
PyGtkSheetCellAttr_SetAttr(PyGtkSheetCellAttr_Object *self, char *attr,
			   PyObject *value)
{
    return PyMember_Set((char *) &self->cell_attr, PyGtkSheetCellAttr_members,
			attr, value);
}

PyTypeObject PyGtkSheetCellAttr_Type =
{
    PyObject_HEAD_INIT(NULL)
    0,
    "GtkSheetCellAttr",
    sizeof(PyGtkSheetCellAttr_Object),
    0,
    (destructor) PyGtkSheetCellAttr_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkSheetCellAttr_GetAttr,
    (setattrfunc) PyGtkSheetCellAttr_SetAttr,
    (cmpfunc) 0,
    (reprfunc) 0,
    0,
    0,
    0,
};

PyObject *
pygtkextra_sheet_cell_attr_new(GtkSheetCellAttr *cell_attr,
			       gboolean is_allocated)
{
    PyGtkSheetCellAttr_Object *self;

    if (!cell_attr) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    
    self = (PyGtkSheetCellAttr_Object *)
	PyObject_NEW(PyGtkSheetCellAttr_Object, &PyGtkSheetCellAttr_Type);
    if (!self)
	return NULL;
    self->cell_attr = *cell_attr;
    gdk_font_ref(self->cell_attr.font);
    self->is_allocated = is_allocated;
    return (PyObject *) self;
}
