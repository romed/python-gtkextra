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

static const gchar *pygtkextra_plot_canvas_child_key =
"pygtkextra::plot_canvas_child";

void
pygtkextra_plot_canvas_register_child(GtkPlotCanvas *canvas, PyObject *child)
{
    pygtkextra_object_register(GTK_OBJECT(canvas),
			       pygtkextra_plot_canvas_child_key, child);
}

void
pygtkextra_plot_canvas_unregister_child(GtkPlotCanvas *canvas, PyObject *child)
{
    ((PyGtkPlotCanvasChild_Object *) child)->child = NULL;
    pygtkextra_object_unregister(GTK_OBJECT(canvas),
				 pygtkextra_plot_canvas_child_key, child);
}
