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

void
pygtkextra_icon_list_unref_links(GtkIconList *icon_list)
{
    int i;

    for (i = 0; i < icon_list->num_icons; ++i) {
	GtkIconListItem *item;

	item = gtk_icon_list_get_nth(icon_list, i);
	if (item && item->link)
	    pygtkextra_icon_list_unregister_link(item->link);
    }
}

void
pygtkextra_icon_list_destroy_cb(GtkIconList *icon_list, gpointer user_data)
{
    PyGtk_BlockThreads();
    pygtkextra_icon_list_unref_links(icon_list);
    PyGtk_UnblockThreads();
}
