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

#ifndef _PYGTKEXTRA_PRIVATE_H_
#define _PYGTKEXTRA_PRIVATE_H_

#include "pygtkextra.h"
#include <pygtk/pygtk.h>
#include <structmember.h>
#include <math.h> /* ceil(), sqrt() */
#include <stdio.h> /* fopen() */
#include <locale.h> /* LC_NUMERIC, setlocale() */

/*
 * Objects
 */

typedef struct
{
    PyObject_HEAD
    GtkSheetChild child;
} PyGtkSheetChild_Object;

typedef struct
{
    PyObject_HEAD
    GtkSheetCellBorder cell_border;
} PyGtkSheetCellBorder_Object;

typedef struct
{
    PyObject_HEAD
    GtkSheetCellAttr cell_attr;
    gboolean is_allocated;
} PyGtkSheetCellAttr_Object;

typedef struct
{
    PyObject_HEAD
    GtkSheetRange range;
} PyGtkSheetRange_Object;

typedef struct
{
    PyObject_HEAD
    GtkPlotText *text;
} PyGtkPlotText_Object;

typedef struct
{
    PyObject_HEAD
    GtkPlotLine line;
} PyGtkPlotLine_Object;

typedef struct
{
    PyObject_HEAD
    GtkPlotCanvasChild *child;
} PyGtkPlotCanvasChild_Object;

typedef struct
{
    PyObject_HEAD
    GtkIconListItem *item;
} PyGtkIconListItem_Object;

typedef struct
{
    PyObject_HEAD
    GtkPSFont *psfont;
} PyGtkPSFont_Object;

/*
 * Types
 */

extern PyTypeObject PyGtkSheetChild_Type;
extern PyTypeObject PyGtkSheetCellBorder_Type;
extern PyTypeObject PyGtkSheetCellAttr_Type;
extern PyTypeObject PyGtkSheetRange_Type;
extern PyTypeObject PyGtkPlotText_Type;
extern PyTypeObject PyGtkPlotLine_Type;
extern PyTypeObject PyGtkPlotCanvasChild_Type;
extern PyTypeObject PyGtkIconListItem_Type;
extern PyTypeObject PyGtkPSFont_Type;

/*
 * General functions
 */

extern void _pygtkextra_register_boxed_types(PyObject *);
extern void pygtkextra_object_register(GtkObject *, const gchar *, PyObject *);
extern void pygtkextra_object_unregister(GtkObject *, const gchar *,
					 PyObject *);
extern int pygtkextra_try_fopen(const char *, const char *);
extern char **pygtkextra_convert_pixmap_data_to_vector(PyObject *);

/*
 * GtkSheetChild functions
 */
extern PyObject *pygtkextra_sheet_child_new(GtkSheetChild *);

/*
 * GtkSheetCellBorder functions
 */
extern PyObject * pygtkextra_sheet_cell_border_new(GtkSheetCellBorder *);

/*
 * GtkSheetCellAttr functions
 */
extern PyObject *pygtkextra_sheet_cell_attr_new(GtkSheetCellAttr *, gboolean);

/*
 * GtkSheetRange functions
 */
extern PyObject *pygtkextra_sheet_range_new(GtkSheetRange *);

/*
 * GtkSheet functions
 */
extern void pygtkextra_sheet_unref_links(GtkSheet *, GtkSheetRange *);
extern void pygtkextra_sheet_destroy_cb(GtkSheet *, gpointer);

/*
 * GtkPlotText functions
 */
extern PyObject *pygtkextra_plot_text_new(GtkPlotText *);

/*
 * GtkPlotLine functions
 */
extern PyObject *pygtkextra_plot_line_new(GtkPlotLineStyle, gfloat,
					  GdkColor *);

/*
 * GtkPlotData functions
 */
extern void pygtkextra_plot_data_destroy_cb(GtkPlotData *, gpointer *);
extern gboolean pygtkextra_plot_data_register_plot_function(GtkPlotData *,
							    PyObject *,
							    PyObject *);
extern gboolean pygtkextra_plot_data_register_plot3d_function(GtkPlotData *,
							      PyObject *,
							      PyObject *);
extern gdouble pygtkextra_plot_data_call_plot_function(GtkPlot *,
						       GtkPlotData *,
						       gdouble, gboolean *);
extern gdouble pygtkextra_plot_data_call_plot3d_function(GtkPlot *,
							 GtkPlotData *,
							 gdouble, gdouble,
							 gboolean *);
extern PyObject *pygtkextra_plot_data_set_points(GtkPlotData *, PyObject *,
						 PyObject *, PyObject *,
						 PyObject *, gint);
extern PyObject *pygtkextra_plot_data_get_points(GtkPlotData *);
extern PyObject *pygtkextra_plot_data_set_numpoints(GtkPlotData *, gint);
extern PyObject *pygtkextra_plot_data_set_array(GtkPlotData *, int,
						PyObject *);
extern PyObject *pygtkextra_plot_data_get_array(GtkPlotData *, int);
extern PyObject *pygtkextra_plot_data_set_labels(GtkPlotData *, PyObject *);
extern PyObject *pygtkextra_plot_data_get_labels(GtkPlotData *);
extern int pygtkextra_plot_data_import_numpy(void);

/*
 * GtkPlotSurface functions
 */
extern PyObject *pygtkextra_plot_surface_set_points(GtkPlotSurface *,
						    PyObject *, PyObject *,
						    PyObject *, PyObject *,
						    PyObject *, PyObject *,
						    gint, gint);
extern PyObject *pygtkextra_plot_surface_get_points(GtkPlotSurface *);
extern PyObject *pygtkextra_plot_surface_set_nx(GtkPlotSurface *, gint);
extern PyObject *pygtkextra_plot_surface_set_ny(GtkPlotSurface *, gint);
extern PyObject *pygtkextra_plot_surface_set_array(GtkPlotSurface *, int,
						   PyObject *);
extern PyObject *pygtkextra_plot_surface_get_array(GtkPlotSurface *, int);

/*
 * GtkPlot functions
 */
extern void pygtkextra_plot_register_plot_data(GtkPlot *, PyObject *);
extern void pygtkextra_plot_unregister_plot_data(GtkPlot *, PyObject *);

/*
 * GtkPlotCanvasChild functions
 */
extern PyObject *pygtkextra_plot_canvas_child_new(GtkPlotCanvasChild *);

/*
 * GtkPlotCanvas functions
 */
extern void pygtkextra_plot_canvas_register_child(GtkPlotCanvas *, PyObject *);
extern void pygtkextra_plot_canvas_unregister_child(GtkPlotCanvas *,
						    PyObject *);

/*
 * GtkIconListItem functions
 */
extern PyObject *pygtkextra_icon_list_item_new(GtkIconListItem *);
extern void pygtkextra_icon_list_init_links(void);
extern gpointer pygtkextra_icon_list_register_link(PyObject *);
extern gpointer pygtkextra_icon_list_get_link(PyObject *);
extern int pygtkextra_icon_list_unregister_link(gpointer);

/*
 * GtkIconList functions
 */
extern void pygtkextra_icon_list_unref_links(GtkIconList *);
extern void pygtkextra_icon_list_destroy_cb(GtkIconList *, gpointer);

/*
 * GtkPSFont functions
 */
extern PyObject *pygtkextra_psfont_new(GtkPSFont *);

/*
 * GtkColorCombo functions
 */
extern int pygtkextra_color_combo_get_size(int, int *, int *);
extern char *pygtkextra_get_colorname(PyObject *);

#endif /* !_PYGTKEXTRA_PRIVATE_H_ */
