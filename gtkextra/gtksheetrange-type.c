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
 * GtkSheetRange
 *
 * The GtkSheetRange type behaves mostly like a list of four integers.
 * The four items can be accessed by index or with the attributes
 * row0, col0, rowi and coli.
 *
 * Ranges can be compared.  Ranges in the top-left corner of the sheet
 * are smaller than ranges in the right-bottom corner. If row0 and
 * col0 are equal the range with the smaller coli attribute is smaller
 * than the other range.
 *
 * All the wrapper functions that get a GtkSheetRange should parse the
 * range with the format string "(iiii)".
 */

PyObject *pygtkextra_sheet_range_new(GtkSheetRange *);

static void
PyGtkSheetRange_Dealloc(PyGtkSheetRange_Object *self)
{
    PyMem_DEL(self);
}

static PyObject *
PyGtkSheetRange_Repr(PyGtkSheetRange_Object *self)
{
    char buf[256];

    g_snprintf(buf, sizeof(buf), "(%d, %d, %d, %d)",
	       (int) self->range.row0, (int) self->range.col0,
	       (int) self->range.rowi, (int) self->range.coli);
    return PyString_FromString(buf);
}

static struct memberlist PyGtkSheetRange_members[] =
{
    { "row0", T_INT, offsetof(GtkSheetRange, row0) },
    { "col0", T_INT, offsetof(GtkSheetRange, col0) },
    { "rowi", T_INT, offsetof(GtkSheetRange, rowi) },
    { "coli", T_INT, offsetof(GtkSheetRange, coli) },
    { NULL }
};

static PyObject *
PyGtkSheetRange_GetAttr(PyGtkSheetRange_Object *self, char *attr)
{
    return PyMember_Get((char *) &self->range, PyGtkSheetRange_members, attr);
}

static int
PyGtkSheetRange_SetAttr(PyGtkSheetRange_Object *self, char *attr,
			PyObject *value)
{
    return PyMember_Set((char *) &self->range, PyGtkSheetRange_members, attr,
			value);
}

static int
PyGtkSheetRange_Compare(PyGtkSheetRange_Object *a, PyGtkSheetRange_Object *b)
{
    if (a->range.col0 < b->range.col0
	|| (a->range.col0 == b->range.col0
	    && a->range.row0 < b->range.row0)
	|| (a->range.col0 == b->range.col0
	    && a->range.row0 == b->range.row0
	    && a->range.coli < b->range.coli)
	|| (a->range.col0 == b->range.col0
	    && a->range.row0 == b->range.row0
	    && a->range.coli == b->range.coli
	    && a->range.rowi < b->range.rowi))
	return -1;
    if (a->range.row0 == b->range.row0
	&& a->range.col0 == b->range.col0
	&& a->range.rowi == b->range.rowi
	&& a->range.coli == b->range.coli)
	return 0;
    return 1;
}

static int
PyGtkSheetRange_Length(PyGtkSheetRange_Object *self)
{
    return 4;
}

static PyObject *
PyGtkSheetRange_GetItem(PyGtkSheetRange_Object *self, int i)
{
    switch (i) {
    case 0:
	return PyInt_FromLong(self->range.row0);
    case 1:
	return PyInt_FromLong(self->range.col0);
    case 2:
	return PyInt_FromLong(self->range.rowi);
    case 3:
	return PyInt_FromLong(self->range.coli);
    }
    PyErr_SetString(PyExc_IndexError, "GtkSheetRange index out of range");
    return NULL;
}

static PyObject *
PyGtkSheetRange_GetSlice(PyGtkSheetRange_Object *self, int ilow, int ihigh)
{
    PyObject *obj;

    if (ilow < 0) ilow = 0;
    if (ihigh > 4) ihigh = 4;
    if (ihigh < ilow) ihigh = ilow;
    if (ilow == 0 && ihigh == 4) {
	obj = pygtkextra_sheet_range_new(&self->range);
    } else {
	obj = PyTuple_New(ihigh - ilow);
	if (obj) {
	    int i = 0;
	    if (ilow == 0 && ihigh > 0)
		PyTuple_SET_ITEM(obj, i++, PyInt_FromLong(self->range.row0));
	    if (ilow <= 1 && ihigh > 1)
		PyTuple_SET_ITEM(obj, i++, PyInt_FromLong(self->range.col0));
	    if (ilow <= 2 && ihigh > 2)
		PyTuple_SET_ITEM(obj, i++, PyInt_FromLong(self->range.rowi));
	    if (ilow <= 3 && ihigh > 3)
		PyTuple_SET_ITEM(obj, i, PyInt_FromLong(self->range.coli));
	}
    }
    return obj;
}

static int
PyGtkSheetRange_SetItem(PyGtkSheetRange_Object *self, int i, PyObject *value)
{
    gint n;
    
    if (!PyInt_Check(value)) {
	PyErr_SetString(PyExc_TypeError, "GtkSheetRange item must be integer");
	return -1;
    }
    n = PyInt_AS_LONG(value);
    switch (i) {
    case 0:
	self->range.row0 = n;
	break;
    case 1:
	self->range.col0 = n;
	break;
    case 2:
	self->range.rowi = n;
	break;
    case 3:
	self->range.coli = n;
	break;
    default:
	PyErr_SetString(PyExc_IndexError,
			"GtkSheetRange assignment index out of range");
	return -1;
    }
    return 0;
}

static PySequenceMethods PyGtkSheetRange_Sequence = {
    (inquiry) PyGtkSheetRange_Length,
    (binaryfunc) 0,
    (intargfunc) 0,
    (intargfunc) PyGtkSheetRange_GetItem,
    (intintargfunc) PyGtkSheetRange_GetSlice,
    (intobjargproc) PyGtkSheetRange_SetItem,
    (intintobjargproc) 0
};

PyTypeObject PyGtkSheetRange_Type =
{
    PyObject_HEAD_INIT(NULL)
    0,
    "GtkSheetRange",
    sizeof(PyGtkSheetRange_Object),
    0,
    (destructor) PyGtkSheetRange_Dealloc,
    (printfunc) 0,
    (getattrfunc) PyGtkSheetRange_GetAttr,
    (setattrfunc) PyGtkSheetRange_SetAttr,
    (cmpfunc) PyGtkSheetRange_Compare,
    (reprfunc) PyGtkSheetRange_Repr,
    0,
    &PyGtkSheetRange_Sequence,
    0,
};

PyObject *
pygtkextra_sheet_range_new(GtkSheetRange *range)
{
    PyGtkSheetRange_Object *self;

    self = (PyGtkSheetRange_Object *)
	PyObject_NEW(PyGtkSheetRange_Object, &PyGtkSheetRange_Type);
    if (!self)
	return NULL;
    self->range = *range;
    return (PyObject *) self;
}

PyObject *
PyGtkSheetRange_New(PyObject *self, PyObject *args)
{
    GtkSheetRange range;
    
    if (!PyArg_ParseTuple(args, "iiii", &range.row0, &range.col0,
			  &range.rowi, &range.coli))
	return NULL;
    return pygtkextra_sheet_range_new(&range);
}
