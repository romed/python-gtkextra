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

#ifndef _PYGTKEXTRA_H_
#define _PYGTKEXTRA_H_

#include <Python.h>
#include <gtkextra/gtkextra.h>

extern PyObject *PyGtkSheetRange_New(PyObject *, PyObject *);

extern int PyGtkPlotText_Check(PyObject *);
extern GtkPlotText *PyGtkPlotText_Get(PyObject *);

extern PyObject *PyGtkPlotLine_New(PyObject *, PyObject *);

extern int PyGtkPlotCanvasChild_Check(PyObject *);
extern GtkPlotCanvasChild *PyGtkPlotCanvasChild_Get(PyObject *);

extern int PyGtkIconListItem_Check(PyObject *);
extern GtkIconListItem *PyGtkIconListItem_Get(PyObject *);

#endif /* !_PYGTKEXTRA_H_ */
