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
 * GtkSheetCellBorder
 *
 * This type is used by the GtkSheetCellAttr type.
 */

static void
PyGtkSheetCellBorder_Dealloc(PyGtkSheetCellBorder_Object *self)
{
    PyMem_DEL(self);
}

static struct memberlist PyGtkSheetCellBorder_members[] =
{
    { "mask", T_BYTE, offsetof(GtkSheetCellBorder, mask), RO },
    { "width", T_UINT, offsetof(GtkSheetCellBorder, width), RO },
    { "line_style", T_INT, offsetof(GtkSheetCellBorder, line_style), RO },
    { "cap_style", T_INT, offsetof(GtkSheetCellBorder, cap_style), RO },
    { "join_style", T_INT, offsetof(GtkSheetCellBorder, join_style), RO },
    { "color", -1, 0, RO },
    { NULL }
};

static PyObject *
PyGtkSheetCellBorder_GetAttr(PyGtkSheetCellBorder_Object *self, char *attr)
{
    if (strcmp(attr, "color") == 0)
	return PyGdkColor_New(&self->cell_border.color);
    return PyMember_Get((char *) &self->cell_border,
			PyGtkSheetCellBorder_members, attr);
}

static int
PyGtkSheetCellBorder_SetAttr(PyGtkSheetCellBorder_Object *self, char *attr,
			PyObject *value)
{
    return PyMember_Set((char *) &self->cell_border,
			PyGtkSheetCellBorder_members, attr, value);
}

PyTypeObject PyGtkSheetCellBorder_Type =
{
    PyObject_HEAD_INIT(NULL)
    0,
    "GtkSheetCellBorder",
    sizeof(PyGtkSheetCellBorder_Object),
    0,
    (destructor) PyGtkSheetCellBorder_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkSheetCellBorder_GetAttr,
    (setattrfunc) PyGtkSheetCellBorder_SetAttr,
    (cmpfunc) 0,
    (reprfunc) 0,
    0,
    0,
    0,
};

PyObject *
pygtkextra_sheet_cell_border_new(GtkSheetCellBorder *cell_border) 
{
    PyGtkSheetCellBorder_Object *self;

    if (!cell_border) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    
    self = (PyGtkSheetCellBorder_Object *)
	PyObject_NEW(PyGtkSheetCellBorder_Object, &PyGtkSheetCellBorder_Type);
    if (!self)
	return NULL;
    self->cell_border = *cell_border;
    return (PyObject *) self;
}
