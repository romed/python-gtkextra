# Python bindings for the GtkExtra widget set
#
# Copyright (C) 2000-2002 Andreas Voegele
#
# The documentation is based on the GtkAda documentation and used by
# permission.  GtkAda is available at http://gtkada.eu.org/ and
# copyrighted by Emmanuel Briot, Joel Brobecker and Arnaud Charlet.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.

import gtk; _gtk = gtk; del gtk
import _gtkextra
import types

# sheet state
SHEET_NORMAL = 0
SHEET_ROW_SELECTED = 1
SHEET_COLUMN_SELECTED = 2
SHEET_RANGE_SELECTED = 3

# sheet border mask
SHEET_LEFT_BORDER = 1 << 0
SHEET_RIGHT_BORDER = 1 << 1
SHEET_TOP_BORDER = 1 << 2
SHEET_BOTTOM_BORDER = 1 << 3

# sheet flags
SHEET_IS_LOCKED = 1 << 0
SHEET_IS_FROZEN = 1 << 1
SHEET_IN_XDRAG = 1 << 2
SHEET_IN_YDRAG = 1 << 3
SHEET_IN_DRAG = 1 << 4
SHEET_IN_SELECTION = 1 << 5
SHEET_IN_RESIZE = 1 << 6
SHEET_IN_CLIP = 1 << 7
SHEET_ROW_FROZEN = 1 << 8
SHEET_COLUMN_FROZEN = 1 << 9
SHEET_AUTO_RESIZE = 1 << 10
SHEET_CLIP_TEXT = 1 << 11
SHEET_ROW_TITLES_VISIBLE = 1 << 12
SHEET_COLUMN_TITLES_VISIBLE = 1 << 13
SHEET_AUTO_SCROLL = 1 << 14
SHEET_JUSTIFY_ENTRY = 1 << 15

# plot bar units
PLOT_BAR_POINTS = 0
PLOT_BAR_RELATIVE = 1
PLOT_BAR_ABSOLUTE = 2

# plot data iterator mask
PLOT_DATA_X = 1 << 0
PLOT_DATA_Y = 1 << 1
PLOT_DATA_Z = 1 << 2
PLOT_DATA_A = 1 << 3
PLOT_DATA_DX = 1 << 4
PLOT_DATA_DY = 1 << 5
PLOT_DATA_DZ = 1 << 6
PLOT_DATA_DA = 1 << 7
PLOT_DATA_LABELS = 1 << 8

# plot scale type
PLOT_SCALE_LINEAR = 0
PLOT_SCALE_LOG10 = 1

# plot symbol type
PLOT_SYMBOL_NONE = 0
PLOT_SYMBOL_SQUARE = 1
PLOT_SYMBOL_CIRCLE = 2
PLOT_SYMBOL_UP_TRIANGLE = 3
PLOT_SYMBOL_DOWN_TRIANGLE = 4
PLOT_SYMBOL_RIGHT_TRIANGLE = 5
PLOT_SYMBOL_LEFT_TRIANGLE = 6
PLOT_SYMBOL_DIAMOND = 7
PLOT_SYMBOL_PLUS = 8
PLOT_SYMBOL_CROSS = 9
PLOT_SYMBOL_STAR = 10
PLOT_SYMBOL_DOT	= 11
PLOT_SYMBOL_IMPULSE = 12

# plot symbol style
PLOT_SYMBOL_EMPTY = 0
PLOT_SYMBOL_FILLED = 1
PLOT_SYMBOL_OPAQUE = 2

# plot border style
PLOT_BORDER_NONE = 0
PLOT_BORDER_LINE = 1
PLOT_BORDER_SHADOW = 2
  
# plot line style
PLOT_LINE_NONE = 0
PLOT_LINE_SOLID = 1
PLOT_LINE_DOTTED = 2
PLOT_LINE_DASHED = 3
PLOT_LINE_DOT_DASH = 4
PLOT_LINE_DOT_DOT_DASH = 5
PLOT_LINE_DOT_DASH_DASH = 6

# plot connector
PLOT_CONNECT_NONE = 0
PLOT_CONNECT_STRAIGHT = 1
PLOT_CONNECT_SPLINE = 2
PLOT_CONNECT_HV_STEP = 3
PLOT_CONNECT_VH_STEP = 4
PLOT_CONNECT_MIDDLE_STEP = 5

# plot label mask
PLOT_LABEL_NONE = 0
PLOT_LABEL_IN = 1 << 0
PLOT_LABEL_OUT = 1 << 1

# plot orientation
PLOT_AXIS_X = 0
PLOT_AXIS_Y = 1
PLOT_AXIS_Z = 2

# plot axis
PLOT_AXIS_LEFT = 0
PLOT_AXIS_RIGHT = 1
PLOT_AXIS_TOP = 2
PLOT_AXIS_BOTTOM = 3

# plot label style
PLOT_LABEL_FLOAT = 0
PLOT_LABEL_EXP = 1
PLOT_LABEL_POW = 2

# plot ticks mask
PLOT_TICKS_NONE = 0
PLOT_TICKS_IN = 1 << 0
PLOT_TICKS_OUT = 1 << 1

# plot gradient mask
PLOT_GRADIENT_H = 1 << 0
PLOT_GRADIENT_V = 1 << 1
PLOT_GRADIENT_S = 1 << 2

# plot plane
PLOT_PLANE_XY = 0
PLOT_PLANE_YX = 0
PLOT_PLANE_XZ = 1
PLOT_PLANE_ZX = 1
PLOT_PLANE_YZ = 2
PLOT_PLANE_ZY = 2

# plot side
PLOT_SIDE_XY = 1 << 0
PLOT_SIDE_XZ = 1 << 1
PLOT_SIDE_YX = 1 << 2
PLOT_SIDE_YZ = 1 << 3
PLOT_SIDE_ZX = 1 << 4
PLOT_SIDE_ZY = 1 << 5

# plot paper size
PLOT_LETTER = 0
PLOT_LEGAL = 1
PLOT_A4 = 2
PLOT_EXECUTIVE = 3

# plot paper widths and heights
PLOT_LETTER_W = 612
PLOT_LETTER_H = 792
PLOT_LEGAL_W = 612
PLOT_LEGAL_H = 1008
PLOT_A4_W = 595
PLOT_A4_H = 842
PLOT_EXECUTIVE_W = 540
PLOT_EXECUTIVE_H = 720

# plot paper orientation
PLOT_PORTRAIT = 0
PLOT_LANDSCAPE = 1

# plot paper size unit
PLOT_PSPOINTS = 0
PLOT_MM = 1
PLOT_CM = 2
PLOT_INCHES = 3

# plot canvas flags
PLOT_CANVAS_CAN_SELECT = 1 << 0
PLOT_CANVAS_CAN_SELECT_ITEM = 1 << 1
PLOT_CANVAS_CAN_SELECT_POINT = 1 << 2
PLOT_CANVAS_CAN_DND = 1 << 3
PLOT_CANVAS_CAN_DND_POINT = 1 << 4

PLOT_CANVAS_DND_FLAGS = (PLOT_CANVAS_CAN_SELECT_ITEM
                         | PLOT_CANVAS_CAN_SELECT_POINT
                         | PLOT_CANVAS_CAN_DND
                         | PLOT_CANVAS_CAN_DND_POINT)

# plot canvas child flags
PLOT_CANVAS_FROZEN = 0
PLOT_CANVAS_CAN_MOVE = 1 << 0
PLOT_CANVAS_CAN_X_RESIZE = 1 << 1
PLOT_CANVAS_CAN_Y_RESIZE = 1 << 2

# plot canvas arrow flags
PLOT_ARROW_NONE = 0
PLOT_ARROW_ORIGIN = 1 << 0
PLOT_ARROW_END = 1 << 1

# plot canvas selection
PLOT_CANVAS_SELECT_NONE = 0
PLOT_CANVAS_SELECT_MARKERS = 1
PLOT_CANVAS_SELECT_TARGET = 2

# plot canvas selection mode
PLOT_CANVAS_SELECT_CLICK_1 = 0
PLOT_CANVAS_SELECT_CLICK_2 = 2

# plot canvas item type
PLOT_CANVAS_NONE = 0
PLOT_CANVAS_PLOT = 1
PLOT_CANVAS_AXIS = 2
PLOT_CANVAS_LEGENDS = 3
PLOT_CANVAS_TITLE = 4
PLOT_CANVAS_TEXT = 5
PLOT_CANVAS_DATA = 6
PLOT_CANVAS_LINE = 7
PLOT_CANVAS_RECTANGLE = 8
PLOT_CANVAS_ELLIPSE = 9
PLOT_CANVAS_PIXMAP = 10
PLOT_CANVAS_MARKER = 11
PLOT_CANVAS_CUSTOM = 12

# icon list mode
ICON_LIST_ICON = 0
ICON_LIST_TEXT_RIGHT = 1
ICON_LIST_TEXT_BELOW = 2

class GtkSheet(_gtk.GtkContainer):
	"""A GtkSheet is a table like the one you can find in most
	spreadsheets.  Each cell can contain some text or a widget.
	"""
	get_type = _gtkextra.gtk_sheet_get_type
	"""Return the internal value associated with a GtkSheet."""
	###############################
	## Creation and modification ##
	###############################
	def __init__(self, rows=1, columns=1, title=None, entry_type=None,
		     editable=1, _obj=None):
		"""Create a new sheet with a specific number of rows and
		columns.  You can fully specify which type the entry used to
		modify the value of cells should have.  The value of
		entry_type can be found by using the get_type method of a
		GtkWidget.  The title is internal, and does not appear on the
		screen.  If editable is set to FALSE the sheet is read-only.
		"""
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_sheet_new(rows, columns, title,
						  entry_type, editable)
	def connect(self, name, f, *extra):
		signals = {
		'traverse': _gtkextra._gtk_sheet_callback_wrapper,
		}
		if signals.has_key(name):
			extra = extra + (f,)
			f = signals[name]
		return apply(_gtk.GtkContainer.connect,
			     (self, name, f) + extra)
	def set_hadjustment(self, adjustment):
		"""Change the horizontal adjustment.
		It indicates what range	of columns is visible.
		"""
		_gtkextra.gtk_sheet_set_hadjustment(self._o, adjustment._o)
	def set_vadjustment(self, adjustment):
		"""Change the vertical adjustment.
		It indicates what range of rows is visible.
		"""
		_gtkextra.gtk_sheet_set_vadjustment(self._o, adjustment._o)
	def get_vadjustment(self):
		"""Return the adjustment used to indicate the range of visible
		rows.
		"""
		adjustment = _gtkextra.gtk_sheet_get_vadjustment(self._o)
		if adjustment:
			adjustment = _gtk._obj2inst(adjustment)
		return adjustment
	def get_hadjustment(self):
		"""Return the adjustment used to indicate the range of visible
		columns.
		"""
		adjustment = _gtkextra.gtk_sheet_get_hadjustment(self._o)
		if adjustment:
			adjustment = _gtk._obj2inst(adjustment)
		return adjustment
	def change_entry(self, entry_type):
		"""Change the type of widget used to interactively modify the
		value of the cells.
		"""
		_gtkextra.gtk_sheet_change_entry(self._o, entry_type)
	def get_entry(self):
		"""Return the entry widget used to modify the contents of the
		cells.  The parent of the entry widget, eg a combo box, can
		be found with get_ancestor().
		"""
		entry_widget = _gtkextra.gtk_sheet_get_entry(self._o)
		if entry_widget:
			entry_widget = _gtk._obj2inst(entry_widget)
		return entry_widget
	def get_entry_widget(self):
		"""Return the widget used to modify the contents of the cells.
		"""
		entry_widget = _gtkextra.gtk_sheet_get_entry_widget(self._o)
		if entry_widget:
			entry_widget = _gtk._obj2inst(entry_widget)
		return entry_widget
	def set_title(self, title):
		"""Change the title of the sheet."""
		_gtkextra.gtk_sheet_set_title(self._o, title)
	def set_background(self, color):
		"""Set the sheet's background color."""
		_gtkextra.gtk_sheet_set_background(self._o, color)
	def set_grid(self, color):
		"""Set the sheet's grid color."""
		_gtkextra.gtk_sheet_set_grid(self._o, color)
	def show_grid(self, visible):
		"""Change the visibility of the grid."""
		_gtkextra.gtk_sheet_show_grid(self._o, visible)
	def grid_visible(self):
		"""Check if the grid is visible."""
		return _gtkextra.gtk_sheet_grid_visible(self._o)
	def freeze(self):
		"""Freeze all visual updates of the sheet until you thaw it.
		The update will occur in a more efficient way.
		"""
		_gtkextra.gtk_sheet_freeze(self._o)
	def thaw(self):
		"""Thaw the sheet so that visual updates occur again.
		Note that you have to call thaw() as many times as you have
		called freeze() to actually thaw the widget.
		"""
		_gtkextra.gtk_sheet_thaw(self._o)
	def moveto(self, row, column, row_align, column_align):
		"""Scroll the viewing area to row and column.
		The row_align and column_align arguments represent the
		location on the screen that the cell should appear at.
		0.0, 0.0 is at the top-left of the screen, whereas 1.0, 1.0
		is at the bottom-right corner.  If row or column is negative,
		there is no change.
		"""
		_gtkextra.gtk_sheet_moveto(self._o, row, column, row_align,
					   column_align)
	############################
	## Selection and Clipping ##
	############################
	def get_state(self):
		"""Return the status of the sheet's selection.
		The status can be SHEET_NORMAL, SHEET_ROW_SELECTED,
		SHEET_COLUMN_SELECTED or SHEET_RANGE_SELECTED.
		"""
		return _gtkextra.gtk_sheet_get_state(self._o)
	def get_range(self):
		"""Return the selected range."""
		return _gtkextra.gtk_sheet_get_range(self._o)
	def get_visible_range(self):
		"""Return the range visible on the screen."""
		return _gtkextra.gtk_sheet_get_visible_range(self._o)
	def set_selection_mode(self, mode):
		"""Change the selection mode.
		Valid selection modes are SELECTION_SINGLE
		and SELECTION_BROWSE.
		"""
		_gtkextra.gtk_sheet_set_selection_mode(self._o, mode)
	def select_column(self, column):
		"""Replace the current selection with a specific column.
		The selected range is highlighted.
		"""
		_gtkextra.gtk_sheet_select_column(self._o, column)
	def select_row(self, row):
		"""Replace the current selection with a specific row.
		The selected range is highlighted.
		"""
		_gtkextra.gtk_sheet_select_row(self._o, row)
	def select_range(self, range):
		"""Select a new range of cells."""
		_gtkextra.gtk_sheet_select_range(self._o, range)
	def unselect_range(self):
		"""Unselect the current selected range."""
		_gtkextra.gtk_sheet_unselect_range(self._o)
	def clip_range(self, range):
		"""Create a new clip range.
		That range is flashed on the screen.
		"""
		_gtkextra.gtk_sheet_clip_range(self._o, range)
	def unclip_range(self):
		"""Destroy the clip range."""
		_gtkextra.gtk_sheet_unclip_range(self._o)
	def set_active_cell(self, row, column):
		"""Set active cell where the entry will be displayed.
		Returns FALSE if the current cell can not be deactivated
		or if the requested cell can't be activated.
		"""
		return _gtkextra.gtk_sheet_set_active_cell(self._o, row,
							   column)
	def get_active_cell(self):
		"""Return the coordinates of the active cell or None if no
		cell is active.  The active cell is the cell that the user is
		currently editing.
		"""
		return _gtkextra.gtk_sheet_get_active_cell(self._o)
	#############
	## Columns ##
	#############
	def set_column_title(self, column, title):
		"""Modify the title of a column.
		The first column on the left has the number 0.
		Note that this title does not appear on the screen, and can
		only be used internally to find a specific column.
		"""
		_gtkextra.gtk_sheet_set_column_title(self._o, column, title)
	def get_column_title(self, column):
		"""Return the title of a specific column."""
		return _gtkextra.gtk_sheet_get_column_title(self._o, column)
	def set_column_titles_height(self, height):
		"""Modify the height of the row in which the column titles
		appear.
		"""
		_gtkextra.gtk_sheet_set_column_titles_height(self._o, height)

	def column_button_add_label(self, column, label):
		"""Modify the label of the button that appears at the top of
		each column.
		"""
		_gtkextra.gtk_sheet_column_button_add_label(self._o, column,
							    label)
	def column_button_justify(self, column, justification):
		"""Modify the justification for the label in the column button.
		"""
		_gtkextra.gtk_sheet_column_button_justify(self._o, column,
							  justification)
	def show_column_titles(self):
		"""Show the row in which the column titles appear."""
		_gtkextra.gtk_sheet_show_column_titles(self._o)
	def hide_column_titles(self):
		"""Hide the row in which the column titles appear."""
		_gtkextra.gtk_sheet_hide_column_titles(self._o)
	def columns_set_sensitivity(self, sensitive):
		"""Modify the sensitivity of all the columns.
		If sensitive is FALSE, the columns can not be resized
		dynamically.  This also modifies the sensitivity of the button
		at the top of the columns.
		"""
		_gtkextra.gtk_sheet_columns_set_sensitivity(self._o, sensitive)
	def column_set_sensitivity(self, column, sensitive):
		"""Modify the sensitivity of a specific column and its title
		button.  If sensitive is FALSE, the column can not be
		dynamically resized.
		"""
		_gtkextra.gtk_sheet_column_set_sensitivity(self._o, column,
							   sensitive)
	def column_set_visibility(self, column, visible):
		"""Change the visibility of a column."""
		_gtkextra.gtk_sheet_column_set_visibility(self._o, column,
							  visible)
	def column_label_set_visibility(self, column, visible):
		"""Change the visibility of the label in a given column."""
		_gtkextra.gtk_sheet_column_label_set_visibility(self._o,
								column,
								visible)
	def columns_labels_set_visibility(self, visible):
		"""Change the visibility for all the column labels."""
		_gtkextra.gtk_sheet_columns_labels_set_visibility(self._o,
								  visible)
	def set_column_width(self, column, width):
		"""Modify the width in pixels of a specific column."""
		_gtkextra.gtk_sheet_set_column_width(self._o, column, width)
	def get_column_width(self, column):
		"""Return the width in pixels of the sheet's n-th column."""
		return _gtkextra.gtk_sheet_get_column_width(self._o, column)
	def add_column(self, n):
		"""Add n empty columns at the end of the sheet."""
		_gtkextra.gtk_sheet_add_column(self._o, n)
	def insert_columns(self, column, n):
		"""Add n empty columns just before column."""
		_gtkextra.gtk_sheet_insert_columns(self._o, column, n)
	def delete_columns(self, column, n):
		"""Delete n columns starting with column."""
		_gtkextra.gtk_sheet_delete_columns(self._o, column, n)
	def column_set_justification(self, column, justification):
		"""Set the default justification for the cells in the specific
		column.
		"""
		_gtkextra.gtk_sheet_column_set_justification(self._o, column,
							     justification)
	def get_columns_count(self):
		"""Return the number of columns."""
		return _gtkextra.gtk_sheet_get_columns_count(self._o)
	##########
	## Rows ##
	##########
	def set_row_title(self, row, title):
		"""Modify the title of a row.
		The first row at the top has the number 0.
		Note that this title does not appear on the screen, and can
		only be used internally to find a specific row.
		"""
		_gtkextra.gtk_sheet_set_row_title(self._o, row, title)
	def get_row_title(self, row):
		"""Return the title of a specific row."""
		return _gtkextra.gtk_sheet_get_row_title(self._o, row)
	def set_row_titles_width(self, width):
		"""Modify the width of the column that has the row titles."""
		_gtkextra.gtk_sheet_set_row_titles_width(self._o, width)
	def row_button_add_label(self, row, label):
		""" Modify the label of the button that appears at the left of
		each row.
		"""
		_gtkextra.gtk_sheet_row_button_add_label(self._o, row, label)
	def row_button_justify(self, row, justification):
		"""Modify the justification for the label of the row button."""
		_gtkextra.gtk_sheet_row_button_justify(self._o, row,
						       justification)
	def show_row_titles(self):
		"""Show the column in which the row titles appear."""
		_gtkextra.gtk_sheet_show_row_titles(self._o)
	def hide_row_titles(self):
		"""Hide the column in which the row titles appear."""
		_gtkextra.gtk_sheet_hide_row_titles(self._o)
	def rows_set_sensitivity(self, sensitive):
		"""Modify the sensitivity of all the rows.
		If sensitive is FALSE, the rows can not be resized dynamically.
		This also modifies the sensitivity of the button at the left
		of the row.
		"""
		_gtkextra.gtk_sheet_rows_set_sensitivity(self._o, sensitive)
	def row_set_sensitivity(self, row, sensitive):
		"""Modify the sensitivity of a specific row and its title
		button.  If sensitive is FALSE, the row can not be
		dynamically resized.
		"""
		_gtkextra.gtk_sheet_row_set_sensitivity(self._o, row,
							sensitive)
	def row_set_visibility(self, row, visible):
		"""Modify the visibility of a specific row."""
		_gtkextra.gtk_sheet_row_set_visibility(self._o, row, visible)
	def row_label_set_visibility(self, row, visible):
		"""Change the visibility of the label in a given row."""
		_gtkextra.gtk_sheet_row_label_set_visibility(self._o, row,
							     visible)
	def rows_labels_set_visibility(self, visible):
		"""Change the visibility for all the row labels."""
		_gtkextra.gtk_sheet_rows_labels_set_visibility(self._o,
							       visible)
	def set_row_height(self, row, height):
		"""Set the height in pixels of a specific row."""
		_gtkextra.gtk_sheet_set_row_height(self._o, row, height)
	def get_row_height(self, row):
		"""Return the height in pixels of the sheet's n-th row."""
		return _gtkextra.gtk_sheet_get_row_height(self._o, row)
	def add_row(self, n):
		"""Append n rows at the end of the sheet."""
		_gtkextra.gtk_sheet_add_row(self._o, n)
	def insert_rows(self, row, n):
		"""Add n empty rows just before row."""
		_gtkextra.gtk_sheet_insert_rows(self._o, row, n)
	def delete_rows(self, row, n):
		"""Delete n rows starting with row."""
		_gtkextra.gtk_sheet_delete_rows(self._o, row, n)
	def get_rows_count(self):
		"""Return the number of rows."""
		return _gtkextra.gtk_sheet_get_rows_count(self._o)
	###########
	## Range ##
	###########
	def range_clear(self, range):
		"""Clear the content of the range."""
		_gtkextra.gtk_sheet_range_clear(self._o, range)
	def range_delete(self, range):
		"""Clear the content of the range and delete all the links
		(user data).
		"""
		_gtkextra.gtk_sheet_range_delete(self._o, range)
	def range_set_background(self, range, color):
		"""Set the background color for the cells in a specific range.
		"""
		_gtkextra.gtk_sheet_range_set_background(self._o, range, color)
	def range_set_foreground(self, range, color):
		"""Set the foreground color for the cells in a specific range.
		"""
		_gtkextra.gtk_sheet_range_set_foreground(self._o, range, color)
	def range_set_justification(self, range, justification):
		"""Set the text justification for the cells in the range."""
		_gtkextra.gtk_sheet_range_set_justification(self._o, range,
							    justification)
	def range_set_editable(self, range, editable):
		"""Set whether the cells in the range are editable."""
		_gtkextra.gtk_sheet_range_set_editable(self._o, range,
						       editable)
	def range_set_visible(self, range, visible):
		"""Set whether the cells in the range are visible."""
		_gtkextra.gtk_sheet_range_set_visible(self._o, range, visible)
	def range_set_border(self, range, mask, width, line_style=0):
		"""Set the border style for the cells in the range."""
		_gtkextra.gtk_sheet_range_set_border(self._o, range, mask,
						     width, line_style)
	def range_set_border_color(self, range, color):
		"""Change the color for the borders of the cells in the range.
		"""
		_gtkextra.gtk_sheet_range_set_border_color(self._o, range,
							   color)
	def range_set_font(self, range, font):
		"""Change the font of the cells in the range. The program has
		to keep a reference to the GdkFont object."""
		_gtkextra.gtk_sheet_range_set_font(self._o, range, font)
	###########
	## Cells ##
	###########
	def set_cell(self, row, column, justification, string):
		"""Set the cell contents.  Use the empty string to delete the
		content of the cell.
		"""
		_gtkextra.gtk_sheet_set_cell(self._o, row, column,
					     justification, string)
	def set_cell_text(self, row, column, string):
		"""Set the cell contents.  The justification used is the
		previous one used in that cell."""
		_gtkextra.gtk_sheet_set_cell_text(self._o, row, column, string)
	def cell_get_text(self, row, column):
		"""Return the text put in a specific cell.  The empty string
		is returned if there is no text in that cell."""
		return _gtkextra.gtk_sheet_cell_get_text(self._o, row, column)
	def cell_clear(self, row, column):
		"""Clear the contents of the cell."""
		_gtkextra.gtk_sheet_cell_clear(self._o, row, column)
	def cell_delete(self, row, column):
		"""Clear the contents of the cell and remove the user data
		associated with it.
		"""
		_gtkextra.gtk_sheet_cell_delete(self._o, row, column)
	def cell_get_state(self, row, column):
		"""Return the state of the cell (normal or selected)."""
		return _gtkextra.gtk_sheet_cell_get_state(self._o, row, column)
	def get_pixel_info(self, x, y):
		"""Return the row and column matching a given pixel on the
		screen in a 2-tuple.  Returns None if no such cell exists.
		"""
		return _gtkextra.gtk_sheet_get_pixel_info(self._o, x, y)
	def get_cell_area(self, row, column):
		"""Get the area of the screen that a cell is mapped to.
		Returns a 4-tuple of the form (x, y, width, height).
		"""
		return _gtkextra.gtk_sheet_get_cell_area(self._o, row, column)
	def get_attributes(self, row, column):
		# TODO
		return _gtkextra.gtk_sheet_get_attributes(self._o, row, column)
	##############
	## Children ##
	##############
	def put(self, widget, x, y):
		"""Put a new child at a specific location (in pixels) in the
		sheet."""
		return _gtkextra.gtk_sheet_put(self._o, widget._o, x, y)
	def attach(self, widget, row, column, x_align, y_align):
		"""Attach a child to a specific cell in the sheet.
		x_align and y_align should be between 0.0 and 1.0, indicating
		that the child should be aligned from the left (resp. top) to
		the right (resp. bottom) of the cell.
		"""
		_gtkextra.gtk_sheet_attach(self._o, widget._o, row, column,
					   x_align, y_align)
	def move_child(self, widget, x, y):
		"""Move a child of the table to a specific location in pixels.
		A warning is printed if widget is not already a child of the
		sheet.
		"""
		_gtkextra.gtk_sheet_move_child(self._o, widget._o, x, y)
	def get_child_at(self, row, column):
		"""Return the widget associated with the cell."""
		return _gtkextra.gtk_sheet_get_child_at(self._o, row, column)
	def button_attach(self, widget, row, column, x_align, y_align):
		"""Attach a new button in the row or column title.
		One of row or column must be negative (but only one).
		This can be used to modify the standard buttons that appear at
		the top of each column, or on the left of each row.
		"""
		_gtkextra.gtk_sheet_button_attach(self._o, widget._o, row,
						  column, x_align, y_align)
	#######################
	## Links / User Data ##
	#######################
	def link_cell(self, row, column, object):
		"""Associate some user specific data with a given cell."""
		_gtkextra.gtk_sheet_link_cell(self._o, row, column, object)
	def get_link(self, row, column):
		"""Return the user data associated with the cell.
		None is returned if the cell has no user data.
		"""
		return _gtkextra.gtk_sheet_get_link(self._o, row, column)
	def remove_link(self, row, column):
		"""Delete the user data associated with the cell."""
		_gtkextra.gtk_sheet_remove_link(self._o, row, column)
	###########
	## Flags ##
	###########
	def sheet_set_flags(self, flags):
		_gtkextra.GTK_SHEET_SET_FLAGS(self._o, flags)
	def sheet_unset_flags(self, flags):
		_gtkextra.GTK_SHEET_UNSET_FLAGS(self._o, flags)
_gtk._name2cls['GtkSheet'] = GtkSheet

class GtkPlotData(_gtk.GtkWidget):
	def __init__(self, function=None, _obj=None, *extra):
		if _obj:
			if function is not None:
				extra = (_obj,) + extra
			else:
				self._o = _obj; return
		self._o = _gtkextra.gtk_plot_data_new(function, extra)
	def paint(self):
		_gtkextra.gtk_plot_data_paint(self._o)
	def update(self):
		_gtkextra.gtk_plot_data_update(self._o)
	def draw_points(self, n):
		_gtkextra.gtk_plot_data_draw_points(self._o, n)
	def draw_symbol(self, x, y):
		_gtkextra.gtk_plot_data_draw_symbol(self._o, x, y)
	def set_points(self, *args):
		"""Set the X, Y, DX and DY arrays and the number of points.
		The arguments can be passed individually or in a 5-tuple.
		"""
		apply(_gtkextra.gtk_plot_data_set_points, (self._o,) + args)
	def get_points(self):
		"""Return a 5-tuple that contains the X, Y, DX and DY arrays
		and the number of points.
		"""
		return _gtkextra.gtk_plot_data_get_points(self._o)
	def get_point(self, i):
		return _gtkextra.gtk_plot_data_get_point(self._o, i)
	def set_numpoints(self, n):
		_gtkextra.gtk_plot_data_set_numpoints(self._o, n)
	def get_numpoints(self):
		return _gtkextra.gtk_plot_data_get_numpoints(self._o)
	def set_x(self, array):
		_gtkextra.gtk_plot_data_set_x(self._o, array)
	def get_x(self):
		return _gtkextra.gtk_plot_data_get_x(self._o)
	def set_y(self, array):
		_gtkextra.gtk_plot_data_set_y(self._o, array)
	def get_y(self):
		return _gtkextra.gtk_plot_data_get_y(self._o)
	def set_z(self, array):
		_gtkextra.gtk_plot_data_set_z(self._o, array)
	def get_z(self):
		return _gtkextra.gtk_plot_data_get_z(self._o)
	def set_a(self, array):
		_gtkextra.gtk_plot_data_set_a(self._o, array)
	def get_a(self):
		return _gtkextra.gtk_plot_data_get_a(self._o)
	def set_dx(self, array):
		_gtkextra.gtk_plot_data_set_dx(self._o, array)
	def get_dx(self):
		return _gtkextra.gtk_plot_data_get_dx(self._o)
	def set_dy(self, array):
		_gtkextra.gtk_plot_data_set_dy(self._o, array)
	def get_dy(self):
		return _gtkextra.gtk_plot_data_get_dy(self._o)
	def set_dz(self, array):
		_gtkextra.gtk_plot_data_set_dz(self._o, array)
	def get_dz(self):
		return _gtkextra.gtk_plot_data_get_dz(self._o)
	def set_da(self, array):
		_gtkextra.gtk_plot_data_set_da(self._o, array)
	def get_da(self):
		return _gtkextra.gtk_plot_data_get_da(self._o)
	def set_a_scale(self, scale):
		_gtkextra.gtk_plot_data_set_a_scale(self._o, scale)
	def get_a_scale(self):
		return _gtkextra.gtk_plot_data_get_a_scale(self._o)
	def set_labels(self, labels):
		_gtkextra.gtk_plot_data_set_da(self._o, labels)
	def get_labels(self):
		return _gtkextra.gtk_plot_data_get_labels(self._o)
	def show_labels(self, visible):
		return _gtkextra.gtk_plot_data_show_labels(self._o, visible)
	def labels_set_attributes(self, fontname, height, angle, foreground,
				  background):
		_gtkextra.gtk_plot_data_labels_set_attributes(self._o,
							      fontname, height,
							      angle,
							      foreground,
							      background)
	def set_symbol(self, symbol_type, symbol_style, size, line_width,
		       color, border_color=None):
		_gtkextra.gtk_plot_data_set_symbol(self._o, symbol_type,
						   symbol_style, size,
						   line_width, color,
						   border_color)
	def get_symbol(self):
		return _gtkextra.gtk_plot_data_get_symbol(self._o)
	def set_connector(self, connector):
		_gtkextra.gtk_plot_data_set_connector(self._o, connector)
	def get_connector(self):
		return _gtkextra.gtk_plot_data_get_connector(self._o)
	def set_line_attributes(self, line_style, width, color):
		_gtkextra.gtk_plot_data_set_line_attributes(self._o,
							    line_style,
							    width, color)
	def get_line_attributes(self):
		return _gtkextra.gtk_plot_data_get_line_attributes(self._o)
	def set_x_attributes(self, line_style, width, color):
		_gtkextra.gtk_plot_data_set_x_attributes(self._o, line_style,
							 width, color)
	def set_y_attributes(self, line_style, width, color):
		_gtkextra.gtk_plot_data_set_y_attributes(self._o, line_style,
							 width, color)
	def set_z_attributes(self, line_style, width, color):
		_gtkextra.gtk_plot_data_set_z_attributes(self._o, line_style,
							 width, color)
	def show_xerrbars(self):
		_gtkextra.gtk_plot_data_show_xerrbars(self._o)
	def hide_xerrbars(self):
		_gtkextra.gtk_plot_data_hide_xerrbars(self._o)
	def show_yerrbars(self):
		_gtkextra.gtk_plot_data_show_yerrbars(self._o)
	def hide_yerrbars(self):
		_gtkextra.gtk_plot_data_hide_yerrbars(self._o)
	def show_zerrbars(self):
		_gtkextra.gtk_plot_data_show_zerrbars(self._o)
	def hide_zerrbars(self):
		_gtkextra.gtk_plot_data_hide_zerrbars(self._o)
	def fill_area(self, fill):
		_gtkextra.gtk_plot_data_fill_area(self._o, fill)
	def area_is_filled(self):
		return _gtkextra.gtk_plot_data_area_is_filled(self._o)
	def show_legend(self):
		_gtkextra.gtk_plot_data_show_legend(self._o)
	def hide_legend(self):
		_gtkextra.gtk_plot_data_hide_legend(self._o)
	def set_legend(self, string):
		_gtkextra.gtk_plot_data_set_legend(self._o, string)
	def set_name(self, name):
		_gtkextra.gtk_plot_data_set_name(self._o, name)
	def set_gradient_mask(self, mask):
		"""Valid flags are PLOT_GRADIENT_H, PLOT_GRADIENT_V and
		PLOT_GRADIENT_S.
		"""
		_gtkextra.gtk_plot_data_set_gradient_mask(self._o, mask)
	def gradient_set_mask(self, mask):
		"""Obsolete, use set_gradient_mask() instead."""
		self.set_gradient_mask(mask)
	def get_gradient_mask(self):
		return _gtkextra.gtk_plot_data_get_gradient_mask(self._o)
	def gradient_get_mask(self):
		"""Obsolete, use get_gradient_mask() instead."""
		return self.gradient_get_mask()
	def gradient_set_visible(self, visible):
		_gtkextra.gtk_plot_data_gradient_set_visible(self._o, visible)
	def gradient_visible(self):
		return _gtkextra.gtk_plot_data_gradient_visible(self._o)
	def draw_gradient(self, x, y):
		_gtkextra.gtk_plot_data_draw_gradient(self._o, x, y)
	def gradient_autoscale_a(self):
		_gtkextra.gtk_plot_data_gradient_autoscale_a(self._o)
	def gradient_autoscale_da(self):
		_gtkextra.gtk_plot_data_gradient_autoscale_da(self._o)
	def gradient_autoscale_z(self):
		_gtkextra.gtk_plot_data_gradient_autoscale_z(self._o)
	def gradient_get_visible(self):
		return self.gradient_visible()
	def set_gradient_colors(self, min_color, max_color):
		_gtkextra.gtk_plot_data_set_gradient_colors(self._o,
							    min_color,
							    max_color)
	def get_gradient_colors(self):
		return _gtkextra.gtk_plot_data_get_gradient_colors(self._o)
	def set_gradient(self, min, max, levels, sublevels=0):
		_gtkextra.gtk_plot_data_set_gradient(self._o, min, max, levels,
						     sublevels)
	def get_gradient(self):
		return _gtkextra.gtk_plot_data_get_gradient(self._o)
	def get_gradient_level(self, level):
		return _gtkextra.gtk_plot_data_get_gradient_level(self._o,
								  level)
	def set_link(self, object):
		_gtkextra.gtk_plot_data_set_link(self._o, object);
	def get_link(self):
		return _gtkextra.gtk_plot_data_get_link(self._o);
	def remove_link(self):
		_gtkextra.gtk_plot_data_remove_link(self._o);
	def add_marker(self, i):
		return _gtkextra.gtk_plot_data_add_marker(self._o, i)
	def remove_marker(self, marker):
		return _gtkextra.gtk_plot_data_remove_marker(self._o, marker)
	def remove_markers(self):
		_gtkextra.gtk_plot_data_remove_markers(self._o)
	def show_markers(self, visible):
		_gtkextra.gtk_plot_data_show_markers(self._o, visible)
	def markers_visible(self):
		return _gtkextra.gtk_plot_data_markers_visible(self._o)
_gtk._name2cls['GtkPlotData'] = GtkPlotData

class GtkPlotBar(GtkPlotData):
	get_type = _gtkextra.gtk_plot_bar_get_type
	"""Return the internal value associated with a GtkPlotBar."""
	def __init__(self, orientation=1, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_plot_bar_new(orientation)
	def set_width(self, width):
		_gtkextra.gtk_plot_bar_set_width(self._o, width)
	def get_width(self):
		return _gtkextra.gtk_plot_bar_get_width(self._o)
_gtk._name2cls['GtkPlotBar'] = GtkPlotBar

class GtkPlotBox(GtkPlotData):
	get_type = _gtkextra.gtk_plot_box_get_type
	"""Return the internal value associated with a GtkPlotBox."""
	def __init__(self, orientation=1, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_plot_box_new(orientation)
_gtk._name2cls['GtkPlotBox'] = GtkPlotBox

class GtkPlotFlux(GtkPlotData):
	get_type = _gtkextra.gtk_plot_flux_get_type
	"""Return the internal value associated with a GtkPlotFlux."""
	def __init__(self, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_plot_flux_new()
	def set_arrow(self, arrow_length, arrow_width, symbol_style):
		_gtkextra.gtk_plot_flux_set_arrow(self._o, arrow_length,
						  arrow_width, symbol_style)
	def get_arrow(self):
		return _gtkextra.gtk_plot_flux_get_arrow(self._o)
	def center(self, center):
		_gtkextra.gtk_plot_flux_center(self._o, center)
	def is_centered(self):
		return _gtkextra.gtk_plot_flux_is_centered(self._o)
_gtk._name2cls['GtkPlotFlux'] = GtkPlotFlux

class GtkPlotSurface(GtkPlotData):
	get_type = _gtkextra.gtk_plot_surface_get_type
	"""Return the internal value associated with a GtkPlotSurface."""
	def __init__(self, function=None, _obj=None, *extra):
		if _obj:
			if function is not None:
				extra = (_obj,) + extra
			else:
				self._o = _obj; return
		self._o = _gtkextra.gtk_plot_surface_new(function, extra)
	def set_numpoints(self, n):
		raise AttributeError
	def get_numpoints(self):
		raise AttributeError
	def set_color(self, color):
		_gtkextra.gtk_plot_surface_set_color(self._o, color)
	def set_shadow(self, color):
		_gtkextra.gtk_plot_surface_set_shadow(self._o, color)
	def set_grid_foreground(self, color):
		_gtkextra.gtk_plot_surface_set_grid_foreground(self._o, color)
	def set_grid_background(self, color):
		_gtkextra.gtk_plot_surface_set_grid_background(self._o, color)
	def set_grid_visible(self, visible):
		_gtkextra.gtk_plot_surface_set_grid_visible(self._o, visible)
	def get_grid_visible(self):
		return _gtkextra.gtk_plot_surface_get_grid_visible(self._o)
	def set_mesh_visible(self, visible):
		_gtkextra.gtk_plot_surface_set_mesh_visible(self._o, visible)
	def get_mesh_visible(self):
		return _gtkextra.gtk_plot_surface_get_mesh_visible(self._o)
	def set_light(self, x, y, z):
		_gtkextra.gtk_plot_surface_set_light(self._o, x, y, z)
	def set_ambient(self, ambient):
		_gtkextra.gtk_plot_surface_set_ambient(self._o, ambient)
	def use_height_gradient(self, use_gradient):
		_gtkextra.gtk_plot_surface_use_height_gradient(self._o,
							       use_gradient)
	def set_transparent(self, transparent):
		_gtkextra.gtk_plot_surface_set_transparent(self._o,
							   transparent)
	def set_points(self, *args):
		"""Set the X, Y, Z, DX, DY and DY arrays and the number of
		points on the X and the Y axis.  The arguments can be passed
		individually or in a 8-tuple.
		"""
		apply(_gtkextra.gtk_plot_surface_set_points, (self._o,) + args)
	def get_points(self):
		"""Return a 8-tuple that contains the X, Y, Z, DX, DY and DZ
		arrays and the number of points on the X and the Y axis.
		"""
		return _gtkextra.gtk_plot_surface_get_points(self._o)
	def set_nx(self, nx):
		_gtkextra.gtk_plot_surface_set_nx(self._o, nx)
	def get_nx(self):
		return _gtkextra.gtk_plot_surface_get_nx(self._o)
	def set_ny(self, ny):
		_gtkextra.gtk_plot_surface_set_ny(self._o, ny)
	def get_ny(self):
		return _gtkextra.gtk_plot_surface_get_ny(self._o)
	def set_x(self, array):
		_gtkextra.gtk_plot_surface_set_x(self._o, array)
	def set_y(self, array):
		_gtkextra.gtk_plot_surface_set_y(self._o, array)
	def set_z(self, array):
		_gtkextra.gtk_plot_surface_set_z(self._o, array)
	def set_dx(self, array):
		_gtkextra.gtk_plot_surface_set_dx(self._o, array)
	def set_dy(self, array):
		_gtkextra.gtk_plot_surface_set_dy(self._o, array)
	def set_dz(self, array):
		_gtkextra.gtk_plot_surface_set_dz(self._o, array)
	def get_x(self):
		return _gtkextra.gtk_plot_surface_get_x(self._o)
	def get_y(self):
		return _gtkextra.gtk_plot_surface_get_y(self._o)
	def get_z(self):
		return _gtkextra.gtk_plot_surface_get_z(self._o)
	def get_dx(self):
		return _gtkextra.gtk_plot_surface_get_dx(self._o)
	def get_dy(self):
		return _gtkextra.gtk_plot_surface_get_dy(self._o)
	def get_dz(self):
		return _gtkextra.gtk_plot_surface_get_dz(self._o)
	def set_xstep(self, xstep):
		_gtkextra.gtk_plot_surface_set_xstep(self._o, xstep)
	def get_xstep(self):
		_gtkextra.gtk_plot_surface_get_xstep(self._o)
	def set_ystep(self, ystep):
		_gtkextra.gtk_plot_surface_set_ystep(self._o, ystep)
	def get_ystep(self):
		_gtkextra.gtk_plot_surface_get_ystep(self._o)
	def build_mesh(self):
		_gtkextra.gtk_plot_surface_build_mesh(self._o)
	def recalc_nodes(self):
		_gtkextra.gtk_plot_surface_recalc_nodes(self._o)
_gtk._name2cls['GtkPlotSurface'] = GtkPlotSurface

class GtkPlotCSurface(GtkPlotSurface):
	get_type = _gtkextra.gtk_plot_csurface_get_type
	"""Return the internal value associated with a GtkPlotCSurface."""
	def __init__(self, function=None, _obj=None, *extra):
		if _obj:
			if function is not None:
				extra = (_obj,) + extra
			else:
				self._o = _obj; return
		self._o = _gtkextra.gtk_plot_csurface_new(function, extra)
	def set_lines_visible(self, visible):
		_gtkextra.gtk_plot_csurface_set_lines_visible(self._o, visible)
	def get_lines_visible(self):
		return _gtkextra.gtk_plot_csurface_set_lines_visible(self._o)
	def set_lines_only(self, lines_only):
		_gtkextra.gtk_plot_csurface_set_lines_only(self._o, lines_only)
	def lines_only(self):
		return _gtkextra.gtk_plot_csurface_lines_only(self._o)
	def set_labels_visible(self, visible):
		_gtkextra.gtk_plot_csurface_set_labels_visible(self._o, visible)
	def labels_visible(self):
		return _gtkextra.gtk_plot_csurface_labels_visible(self._o)
_gtk._name2cls['GtkPlotCSurface'] = GtkPlotCSurface

class GtkPlotPixmap(GtkPlotData):
	get_type = _gtkextra.gtk_plot_pixmap_get_type
	"""Return the internal value associated with a GtkPlotPixmap."""
	def __init__(self, pixmap=None, mask=None, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_plot_pixmap_new(pixmap, mask)
	def get_pixmap(self):
		return _gtkextra.gtk_plot_pixmap_get_pixmap(self._o)
	def get_mask(self):
		return _gtkextra.gtk_plot_pixmap_get_mask(self._o)
_gtk._name2cls['GtkPlotPixmap'] = GtkPlotPixmap

class GtkPlot(_gtk.GtkWidget):
	"""This class implements a high-level, general purpose plotting
	widget.  You can display any set of data (set of points, curve defined
	by a parametric function, ...).  This widget can automatically display
	them as a curve, along with labelled axis, axis tick marks, legends,...

	It fully supports the drag-and-drop protocol for all of its children,
	which means that the user can interactively move them in the GtkPlot
	area.

	A GtkPlot is closely associated with a GdkDrawable, on which all the
	drawings are done. It can be done anywhere within that drawable, its
	"position" is indicated by a tuple (X, Y), which are two values between
	0.0 and 1.0 (from left to right, or from top to bottom).
	Its size is also given as a ratio other the drawable's size.
	
	Most points in the plot have also this relative coordinates systems,
	which makes it really easy to handle resizing of a plot window.
	"""
	get_type = _gtkextra.gtk_plot_get_type
	"""Return the internal value associated with a GtkPlot."""
	def __init__(self, drawable=None, width=None, height=None, _obj=None):
		"""Create a new plot, that will be displayed in drawable.
		All the datasets, labels, axis,... associated with the plot
		will be drawn in that drawable, which must have been created
		beforehand.  Note that the drawable can also be set later with
		set_drawable.
		"""
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_plot_new(drawable, width, height)
	def connect(self, name, f, *extra):
		signals = {
		'moved': _gtkextra._gtk_plot_callback_wrapper,
		'resized': _gtkextra._gtk_plot_callback_wrapper,
		}
		if signals.has_key(name):
			extra = extra + (f,)
			f = signals[name]
		return apply(_gtk.GtkWidget.connect, (self, name, f) + extra)
	def set_drawable(self, drawable):
		"""Modify the drawable on which the graphs are displayed.
		From now on, all the drawings will be done on that drawable.
		Note that they are not automatically copied to the new
		drawable until the plot needs to be redrawn.
		"""
		_gtkextra.gtk_plot_set_drawable(self._o, drawable)
	def get_drawable(self):
		"""Return the drawable on which the graphs are plotted."""
		return _gtkextra.gtk_plot_get_drawable(self._o)
	def set_background(self, color):
		"""Change the plot's background color.
		Note that this has no effect if the plot has been set to
		transparent.
		The plot is also redrawn as soon as you modify this color.
		"""
		_gtkextra.gtk_plot_set_background(self._o, color)
	def set_background_pixmap(self, pixmap):
		"""Change the plot's background pixmap."""
		_gtkextra.gtk_plot_set_background_pixmap(self._o, pixmap)
	def set_transparent(self, transparent):
		"""Indicate whether the background should be transparent
		or not.
		"""
		_gtkextra.gtk_plot_set_transparent(self._o, transparent)
	def is_transparent(self, transparent):
		"""Return whether the background is transparent or not."""
		return _gtkextra.gtk_plot_is_transparent(self._o)
	def paint(self):
		"""Force an immediate repaint of the widget in its pixmap.
		The modification won't appear on the screen until you call
		refresh().
		It is probably not a good idea to call this function directly,
		and it is more efficient to queue a draw request (see the
		GtkWidget class for related functions).
		"""
		_gtkextra.gtk_plot_paint(self._o)
	def refresh(self, area=None):
		"""Copy the plot's pixmap to the screen.
		The same comment as for paint() applies here, and you probably
		don't have to call this function yourself, since queuing a
		draw request is more efficient.
		"""
		_gtkextra.gtk_plot_refresh(self._o, area)
	def set_magnification(self, magnification):
		"""Change the magnification level of the plot.
		1.0 is the default magnification, higher values will zoom in
		while lower values will zoom out.
		"""
		_gtkextra.gtk_plot_set_magnification(self._o, magnification)
	############################
	##  Coordinates and sizes ##
	############################
	def get_position(self):
		"""Return the position of the plot within its drawable
		as a 2-tuple.  x and y are in the range 0.0 .. 1.0, where
		(0.0, 0.0) is the top-left corner and (1.0, 1.0)
		the bottom-right corner.  The position can be changed with
		move().
		"""
		return _gtkextra.gtk_plot_get_position(self._o)
	def get_size(self):
		"""Return the size of the plot as a 2-tuple.  width and height
		are both in the range 0.0 .. 1.0, where 1.0 means they
		occupy all the space available in the drawable, 0.5 means they
		only occupy half of it.
		"""
		return _gtkextra.gtk_plot_get_size(self._o)

	def get_internal_allocation(self):
		"""Return the real position/size of the plot inside its parent
		container.  You should use this function instead of converting
		yourself the result of get_position() and get_size().
		"""
		return _gtkextra.gtk_plot_get_internal_allocation(self._o)
	def move(self, x, y):
		"""Move the plot widget inside its drawable.
		x and y should both be in the range 0.0 .. 1.0 (from
		top-left corner to bottom-right corner).
		"""
		_gtkextra.gtk_plot_move(self._o, x, y)
	def resize(self, width, height):
		"""Resize the widget.
		width and height should both be in the range 0.0 .. 1.0,
		this indicates which ratio of the drawable's screen
		real-estate they should use.
		"""
		_gtkextra.gtk_plot_resize(self._o, width, height)
	def move_resize(self, x, y, width, height):
		"""Move and resize the widget in a single operation.
		This is faster than doing each operation separately.
		"""
		_gtkextra.gtk_plot_move_resize(self._o, x, y, width, height)
	def get_pixel(self, x, y):
		"""Return the screen coordinates (relative to plot's parent)
		of a point.  The initial coordinates x and y should be in the
		range 0.0 .. 1.0.
		"""
		return _gtkextra.gtk_plot_get_pixel(self._o, x, y)
	def get_point(self, ix, iy):
		"""Convert from an absolute screen coordinate to a relative
		one.  x and y should be relative to plot's parent.
		This function is the opposite of get_pixel.
		"""
		return _gtkextra.gtk_plot_get_point(self._o, ix, iy)
	def set_xrange(self, xmin, xmax):
		"""Set the range of visible points for this plot.
		Only the points of the graph those coordinates are in the
		range xmin .. xmax will be visible.
		"""
		_gtkextra.gtk_plot_set_xrange(self._o, xmin, xmax)
	def set_yrange(self, ymin, ymax):
		"""Set the range of visible points for this plot.
		Only the points of the graph those coordinates are in the
		range Xmin .. Xmax will be visible.
		"""
		_gtkextra.gtk_plot_set_yrange(self._o, ymin, ymax)
	def set_range(self, xmin, xmax, ymin, ymax):
		"""Set both ranges at the same time."""
		_gtkextra.gtk_plot_set_range(self._o, xmin, xmax, ymin, ymax)
	def autoscale(self):
		"""Calculate automatically the appropriate ranges for the
		plot.
		"""
		_gtkextra.gtk_plot_autoscale(self._o)
	def get_xrange(self):
		"""Get the current range of the X axis."""
		return _gtkextra.gtk_plot_get_xrange(self._o)
	def get_yrange(self):
		"""Get the current range of the Y axis."""
		return _gtkextra.gtk_plot_get_yrange(self._o)
	def set_xscale(self, scale_type):
		"""Set the type of the X axis (logarithmic, linear, ...)."""
		_gtkextra.gtk_plot_set_xscale(self._o, scale_type)
	def set_yscale(self, scale_type):
		"""Set the type of the Y axis (logarithmic, linear, ...)."""
		_gtkextra.gtk_plot_set_yscale(self._o, scale_type)
	def get_xscale(self):
		"""Get the type of the X axis."""
		return _gtkextra.gtk_plot_get_xscale(self._o)
	def get_yscale(self):
		"""Get the type of the Y axis."""
		return _gtkextra.gtk_plot_get_yscale(self._o)
	def get_axis(self, axis):
		"""Get a pointer to an axis."""
		return _gtkextra.gtk_plot_get_axis(self._o, axis)
	def axis_set_visible(self, axis, visible):
		"""Indicate whether the axis should be visible or not."""
		_gtkextra.gtk_plot_axis_set_visible(self._o, axis, visible)
	def axis_visible(self, axis):
		"""Return the visibility state of the axis."""
		return _gtkextra.gtk_plot_axis_visible(self._o, axis)
	def axis_get_visible(self, axis):
		return self.axis_visible()
	def axis_set_title(self, axis, title):
		"""Modify the title of the axis.
		Each axis has a title that is displayed along its line
		(vertically for the left and right sides).
		"""
		_gtkextra.gtk_plot_axis_set_title(self._o, axis, title)
	def axis_show_title(self, axis):
		"""Show the title associated with the axis."""
		_gtkextra.gtk_plot_axis_show_title(self._o, axis)
	def axis_hide_title(self, axis):
		"""Hide the title associated with the axis."""
		_gtkextra.gtk_plot_axis_hide_title(self._o, axis)
	def axis_move_title(self, axis, angle, x, y):
		"""Modify the position and orientation of the axis' title.
		x and y indicate a position relative to the location of the
		axis (0.0 to display it to the left (resp. top) of the axis,
		1.0 to display it to the right (resp. bottom) of the axis.
		"""
		_gtkextra.gtk_plot_axis_move_title(self._o, axis, angle, x, y)
	def axis_justify_title(self, axis, justification):
		"""Modify the justification for the axis."""
		_gtkextra.gtk_plot_axis_justify_title(self._o, axis,
						      justification)
	def axis_set_attributes(self, axis, width, color):
		"""Modify the attributes of the lines of the axis."""
		_gtkextra.gtk_plot_axis_set_attributes(self._o, axis, width,
						       color)
	def axis_get_attributes(self, axis):
		"""Get the attributes of the axis."""
		return _gtkextra.gtk_plot_axis_get_attributes(self._o, axis)
	def axis_set_ticks(self, orientation, major_step, num_minor):
		"""Set up ticks for a specific axis.
		PLOT_AXIS_X will match the left and right sides, whereas
		PLOT_AXIS_Y will match the top and bottom sides.
		major_step is a percentage value of the widget size,
		and indicates the step between each big ticks. For instance,
		if major_step has a value of 0.2, there will be 5 big ticks
		drawn along the axis.  num_minor is the number of minor ticks
		between each major one.
		"""
		_gtkextra.gtk_plot_axis_set_ticks(self._o, orientation,
						  major_step, num_minor)
	def axis_set_major_ticks(self, orientation, major_step):
		"""Modify the step for major ticks.
		This is a percentage value that indicates how many major ticks
		are drawn along the axis. See also axis_set_ticks().
		"""
		_gtkextra.gtk_plot_axis_set_major_ticks(self._o, orientation,
							major_step)
	def axis_set_minor_ticks(self, orientation, num_minor):
		"""Modify the number of minor ticks between each major one.
		See also axis_set_ticks().
		"""
		_gtkextra.gtk_plot_axis_set_minor_ticks(self._o, orientation,
							num_minor)
	def axis_set_ticks_length(self, axis, length):
		"""Set the length (in pixels) of the big ticks.
		The small ticks will have half this length.
		"""
		_gtkextra.gtk_plot_axis_set_ticks_length(self._o, axis, length)
	def axis_set_ticks_width(self, axis, width):
		"""Set the width (in pixels) of the ticks.
		This width is common to both the long and short ticks.
		"""
		_gtkextra.gtk_plot_axis_set_ticks_width(self._o, axis, width)
	def axis_show_ticks(self, axis, major_mask, minor_mask):
		"""Set the style of the ticks."""
		_gtkextra.gtk_plot_axis_show_ticks(self._o, axis, major_mask,
						   minor_mask)
	def axis_set_ticks_limits(self, orientation, ticks_beg, ticks_end):
		"""Indicate the area of the axis that should have ticks.
		Ticks will be displayed only from ticks_beg to ticks_end.
		"""
		_gtkextra.gtk_plot_axis_set_ticks_limits(self._o, orientation,
							 ticks_beg, ticks_end)
	def axis_unset_ticks_limits(self, orientation):
		"""Cancel the ticks limits set by a previous call to
		axis_set_ticks_limits().
		"""
		_gtkextra.gtk_plot_axis_unset_ticks_limits(self._o,
							   orientation)
	def axis_show_labels(self, axis, label_mask):
		"""Indicate whether a label should be drawn at each ticks to
		indicate its value.
		"""
		_gtkextra.gtk_plot_axis_show_labels(self._o, axis, label_mask)
	def axis_set_labels_suffix(self, axis, string):
		_gtkextra.gtk_plot_axis_set_labels_suffix(self._o, axis,
							  string)
	def axis_get_labels_suffix(self, axis):
		return _gtkextra.gtk_plot_axis_get_labels_suffix(self._o,
								 axis)
	def axis_set_labels_prefix(self, axis, string):
		_gtkextra.gtk_plot_axis_set_labels_prefix(self._o, axis,
							  string)
	def axis_get_labels_prefix(self, axis):
		return _gtkextra.gtk_plot_axis_get_labels_prefix(self._o,
								 axis)
	def axis_title_set_attributes(self, axis, fontname, height, angle,
				      foreground, background, transparent=1,
				      justification=2):
		"""Set the attributes to be used for the title of the axis.
		fontname should be the name of a PostScript font or None."""
		_gtkextra.gtk_plot_axis_title_set_attributes(self._o, axis,
							     fontname, height,
							     angle,
							     foreground,
							     background,
							     transparent,
							     justification)
	def axis_set_labels_attributes(self, axis, fontname, height, angle,
				       foreground, background, transparent=1,
				       justification=2):
		"""Set the attributes to be used for the ticks labels.
		fontname should be the name of a PostScript font or None.
		"""
		_gtkextra.gtk_plot_axis_set_labels_attributes(self._o, axis,
							      fontname, height,
							      angle,
							      foreground,
							      background,
							      transparent,
							      justification)
	def axis_labels_set_attributes(self, axis, fontname, height, angle,
				       foreground, background):
		"""Obsolete, use axis_set_labels_attributes() instead."""
		self.axis_set_labels_attributes(axis, fontname, height, angle,
						foreground, background)
	def axis_set_labels_numbers(self, axis, label_style, precision):
		"""Set the style of labels.
		This indicates whether the labels should be displayed as
		floating point values or in the scientific notation.
		precision is the number of digits to be printed.
		"""
		_gtkextra.gtk_plot_axis_set_labels_numbers(self._o, axis,
							   label_style,
							   precision)
	def axis_set_labels_offset(self, axis, offset):
		_gtkextra.gtk_plot_axis_set_labels_offset(self._o, axis,
							  offset)
	def axis_get_labels_offset(self, axis):
		return _gtkextra.gtk_plot_axis_get_labels_offset(self._o, axis)
	def axis_labels_set_numbers(self, axis, label_style, precision):
		"""Obsolete, use axis_set_labels_numbers() instead."""
		self.axis_set_labels_numbers(axis, label_style, precision)
	def axis_set_tick_labels(self, axis, labels):
		"""Modify the labels associated with the major ticks.
		There should be as many items in labels as there are major
		ticks along that axis, although this is not checked.
		Note also that for these items to be visible you should call
		axis_use_custom_tick_labels().
		"""
		_gtkextra.gtk_plot_axis_set_tick_labels(self._o, axis, labels)
	def axis_use_custom_tick_labels(self, axis, custom):
		"""Indicate which kind of labels should be used for major
		ticks.  If custom is TRUE, then the labels set by
		axis_set_tick_labels() will  be used.
		"""
		_gtkextra.gtk_plot_axis_use_custom_tick_labels(self._o, axis,
							       custom)
	def x0_set_visible(self, visible):
		"""Indicate whether the line at x==0 should be displayed."""
		_gtkextra.gtk_plot_x0_set_visible(self._o, visible)
	def x0_visible(self):
		"""Return the visibility state of the line at x==0."""
		return _gtkextra.gtk_plot_x0_visible(self._o)
	def x0_get_visible(self):
		return self.x0_visible()
	def y0_set_visible(self, visible):
		"""Indicate whether the line at y==0 should be displayed."""
		_gtkextra.gtk_plot_y0_set_visible(self._o, visible)
	def y0_visible(self):
		"""Return the visibility state of the line at y==0."""
		return _gtkextra.gtk_plot_y0_visible(self._o)
	def y0_get_visible(self):
		return self.y0_visible()
	def x0line_set_attributes(self, line_style, width, color):
		"""Set the attributes of the line at x==0."""
		_gtkextra.gtk_plot_x0line_set_attributes(self._o, line_style,
							 width, color)
	def y0line_set_attributes(self, line_style, width, color):
		"""Set the attributes of the line at y==0."""
		_gtkextra.gtk_plot_y0line_set_attributes(self._o, line_style,
							 width, color)
	def grids_set_on_top(self, on_top):
		_gtkextra.gtk_plot_grids_set_on_top(self._o, on_top)
	def grids_on_top(self):
		return _gtkextra.gtk_plot_grids_on_top(self._o)
	def grids_set_visible(self, vmajor, vminor, hmajor, hminor):
		"""Indicate whether the lines of the grids should be displayed.
		You can decide separately whether the major and minor lines
		should be displayed.
		"""
		_gtkextra.gtk_plot_grids_set_visible(self._o, vmajor, vminor,
						     hmajor, hminor)
	def grids_visible(self):
		"""Return the visibility state of the grid."""
		return _gtkextra.gtk_plot_grids_visible(self._o)
	def grids_get_visible(self):
		return self.grids_visible()
	def major_hgrid_set_attributes(self, line_style, width, color):
		"""Set the attributes for the major horizontal lines in the
		grid.
		"""
		_gtkextra.gtk_plot_major_hgrid_set_attributes(self._o,
							      line_style,
							      width, color)
	def major_vgrid_set_attributes(self, line_style, width, color):
		"""Set the attributes for the major vertical lines in the
		grid.
		"""
		_gtkextra.gtk_plot_major_vgrid_set_attributes(self._o,
							      line_style,
							      width, color)
	def minor_hgrid_set_attributes(self, line_style, width, color):
		"""Set the attributes for the minor horizontal lines in the
		grid.
		"""
		_gtkextra.gtk_plot_minor_hgrid_set_attributes(self._o,
							      line_style,
							      width, color)
	def minor_vgrid_set_attributes(self, line_style, width, color):
		"""Set the attributes for the minor vertical lines in the
		grid.
		"""
		_gtkextra.gtk_plot_minor_vgrid_set_attributes(self._o,
							      line_style,
							      width, color)
	def show_legends(self):
		"""Indicate that the legend should be displayed."""
		_gtkextra.gtk_plot_show_legends(self._o)
	def hide_legends(self):
		"""Indicate that the legend should not be displayed."""
		_gtkextra.gtk_plot_hide_legends(self._o)
	def set_legends_border(self, border_style, shadow_width=0):
		"""Modify the way the borders of the legend look like."""
		_gtkextra.gtk_plot_set_legends_border(self._o, border_style,
						      shadow_width)
	def legends_move(self, x, y):
		"""Move the legend relative to the widget's area.
		x and y are percentage values. (0.0, 0.0) indicates the
		top-left corner of the plot, (1.0, 1.0) indicates the
		bottom-right corner.
		"""
		_gtkextra.gtk_plot_legends_move(self._o, x, y)
	def legends_get_position(self):
		"""Return the current position of the legend."""
		return _gtkextra.gtk_plot_legends_get_position(self._o)
	def legends_get_allocation(self):
		"""Return the exact coordinates and size in pixels of the
		legend.  The coordinates are relative to the widget's parent
		container.
		"""
		return _gtkextra.gtk_plot_legends_get_allocation(self._o)
	def legends_set_attributes(self, fontname, height, foreground=None,
				   background=None):
		"""Set the attributes to use when displaying the legend.
		fontname is the name of a PostScript font or None.
		"""
		_gtkextra.gtk_plot_legends_set_attributes(self._o, fontname,
							  height, foreground,
							  background)
	def set_line_attributes(self, line):
		_gtkextra.gtk_plot_set_line_attributes(self._o, line)
	def put_text(self, x, y, fontname, height, angle, foreground,
		     background, transparent, justification, string):
		"""Print some text in the plot.
		The text will be drawn at the relative coordinates (x, y),
		with a specified angle.  fontname should be the name of a
		PostScript font or None. If fontname is None a default font
		and default height will be used. Likewise, default colors will
		be used if you don't specify any.
		If transparent is TRUE, then no background will be drawn for
		the text.
		"""
		return _gtkextra.gtk_plot_put_text(self._o, x, y,
						   fontname, height, angle,
						   foreground, background,
						   transparent, justification,
						   string)
	def remove_text(self, text):
		"""Remove some text that is currently visible on the plot.
		Nothing is done if text is currently not visible.
		"""
		return _gtkextra.gtk_plot_remove_text(self._o, text)
	def add_data(self, data):
		"""Add an existing set of data to the plot.
		This set will automatically be drawn the next time the plot
		itself is drawn.
		"""
		_gtkextra.gtk_plot_add_data(self._o, data._o)
	def remove_data(self, data):
		"""Remove the dataset from plot.
		This function returns TRUE if the dataset was indeed found
		and could be removed, FALSE otherwise.
		"""
		return _gtkextra.gtk_plot_remove_data(self._o, data._o)
	def add_function(self, function, *extra):
		"""Allocate a new dataset, whose point are automatically
		calculated.  function is a callable object that takes the X
		coordinate value, and should return the Y coordinate value.
		The set is automatically added to the plot, so you don't need
		to explicitly call add_data().
		"""
		data = _gtkextra.gtk_plot_add_function(self._o, function,
						       extra)
		if data:
			data = _gtk._obj2inst(data)
		return data
	def clip_data(self, clip):
		"""If the argument is TRUE the plot data is clipped to fit
		the frame.
		"""
		_gtkextra.gtk_plot_clip_data(self._o, clip)
	def export_ps(self, filename, orientation=PLOT_PORTRAIT, eps=0,
		      paper_size=PLOT_LETTER):
		"""Create a new PostScript file with the content of the plot.
		eps should be TRUE if the generated file should be in
		Encapsulated PostScript format instead of simple PostScript.
		"""
		return _gtkextra.gtk_plot_export_ps(self._o, filename,
						    orientation, eps,
						    paper_size)
	def export_ps_with_size(self, filename, orientation=PLOT_PORTRAIT,
				eps=0, units=PLOT_PSPOINTS,
				width=PLOT_LETTER_W, height=PLOT_LETTER_H):
		"""Create a new PostScript file with the content of the
		plot. eps should be TRUE if the generated file should be in
		Encapsulated PostScript format instead of simple PostScript.
		The page has a custom size.
		"""
		return _gtkextra.gtk_plot_export_ps_with_size(self._o,
							      filename,
							      orientation, eps,
							      units, width,
							      height)
_gtk._name2cls['GtkPlot'] = GtkPlot

class GtkPlotPolar(GtkPlot):
	get_type = _gtkextra.gtk_plot_polar_get_type
	def __init__(self, drawable=None, width=None, height=None, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_plot_polar_new(drawable, width, height)
	def rotate(self, angle):
		_gtkextra.gtk_plot_polar_rotate(self._o, angle)
_gtk._name2cls['GtkPlotPolar'] = GtkPlotPolar

class GtkPlot3D(GtkPlot):
	get_type = _gtkextra.gtk_plot3d_get_type
	def __init__(self, drawable=None, width=None, height=None, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_plot3d_new(drawable, width, height)
	def autoscale(self):
		_gtkextra.gtk_plot3d_autoscale(self._o)
	def rotate(self, angle_x, angle_y, angle_z):
		_gtkextra.gtk_plot3d_rotate(self._o, angle_x, angle_y, angle_z)
	def rotate_vector(self, vector, a1, a2, a3):
		_gtkextra.gtk_plot3d_rotate_vector(self._o, a1, a2, a3)
	def reset_angles(self):
		_gtkextra.gtk_plot3d_reset_angles(self._o)
	def rotate_x(self, angle):
		_gtkextra.gtk_plot3d_rotate_x(self._o, angle)
	def rotate_y(self, angle):
		_gtkextra.gtk_plot3d_rotate_y(self._o, angle)
	def rotate_z(self, angle):
		_gtkextra.gtk_plot3d_rotate_z(self._o, angle)
	def get_pixel(self, x, y, z):
		return _gtkextra.gtk_plot3d_get_pixel(self._o, x, y, z)
	def set_xrange(self, xmin, xmax):
		_gtkextra.gtk_plot3d_set_xrange(self._o, xmin, xmax)
	def set_yrange(self, ymin, ymax):
		_gtkextra.gtk_plot3d_set_yrange(self._o, ymin, ymax)
	def set_zrange(self, zmin, zmax):
		_gtkextra.gtk_plot3d_set_zrange(self._o, zmin, zmax)
	def set_xfactor(self, xmin, xmax):
		_gtkextra.gtk_plot3d_set_xfactor(self._o, xfactor)
	def get_xfactor(self):
		return _gtkextra.gtk_plot3d_get_xfactor(self._o)
	def set_yfactor(self, ymin, ymax):
		_gtkextra.gtk_plot3d_set_yfactor(self._o, yfactor)
	def get_yfactor(self):
		return _gtkextra.gtk_plot3d_get_yfactor(self._o)
	def set_zfactor(self, zmin, zmax):
		_gtkextra.gtk_plot3d_set_zfactor(self._o, zfactor)
	def get_zfactor(self):
		return _gtkextra.gtk_plot3d_get_zfactor(self._o)
	def plane_set_color(self, plane, color):
		_gtkextra.gtk_plot3d_plane_set_color(self._o, plane, color)
	def plane_set_visible(self, plane, visible):
		_gtkextra.gtk_plot3d_plane_set_visible(self._o, plane, visible)
	def plane_visible(self, plane):
		return _gtkextra.gtk_plot3d_plane_visible(self._o, plane)
	def plane_get_visible(self, plane):
		return self.plane_visible(plane)
	def corner_set_visible(self, visible):
		_gtkextra.gtk_plot3d_corner_set_visible(self._o, visible)
	def corner_visible(self):
		return _gtkextra.gtk_plot3d_corner_visible(self._o)
	def corner_get_visible(self):
		return self.corner_visible()
	def corner_set_attributes(self, line_style, width, color):
		_gtkextra.gtk_plot3d_corner_set_attributes(self._o, line_style,
							   width, color)
	def corner_get_attributes(self):
		return _gtkextra.gtk_plot3d_corner_get_attributes(self._o)
	def frame_set_attributes(self, line_style, width, color):
		_gtkextra.gtk_plot3d_frame_set_attributes(self._o, line_style,
							  width, color)
	def frame_get_attributes(self):
		return _gtkextra.gtk_plot3d_frame_get_attributes(self._o)
	def get_axis(self, orientation):
		return _gtkextra.gtk_plot3d_get_axis(self._o)
	def get_side(self, side):
		return _gtkextra.gtk_plot3d_get_side(self._o)
	def axis_show_major_ticks(self, side, ticks_mask):
		_gtkextra.gtk_plot3d_axis_show_major_ticks(self._o, side,
							   ticks_mask)
	def axis_show_minor_ticks(self, side, ticks_mask):
		_gtkextra.gtk_plot3d_axis_show_minor_ticks(self._o, side,
							   ticks_mask)
	def axis_show_labels(self, side, label_mask):
		_gtkextra.gtk_plot3d_axis_show_labels(self._o, side,
						      label_mask)
	def axis_show_title(self, side):
		_gtkextra.gtk_plot3d_axis_show_title(self._o, side)
	def axis_hide_title(self, side):
		_gtkextra.gtk_plot3d_axis_hide_title(self._o, side)
	def axis_set_ticks(self, orientation, major_step, num_minor):
		_gtkextra.gtk_plot3d_axis_set_ticks(self._o, orientation,
						    major_step, num_minor)
	def axis_set_major_ticks(self, orientation, major_step):
		_gtkextra.gtk_plot3d_axis_set_major_ticks(self._o, orientation,
							  major_step)
	def axis_set_minor_ticks(self, orientation, num_minor):
		_gtkextra.gtk_plot3d_axis_set_minor_ticks(self._o, orientation,
							  num_minor)
	def axis_set_ticks_length(self, orientation, length):
		_gtkextra.gtk_plot3d_axis_set_ticks_length(self._o,
							   orientation, length)
	def axis_set_ticks_width(self, orientation, width):
		_gtkextra.gtk_plot3d_axis_set_ticks_width(self._o, orientation,
							  width)
	def axis_show_ticks(self, side, major_mask, minor_mask):
		_gtkextra.gtk_plot3d_axis_show_ticks(self._o, side,
						     major_mask, minor_mask)
	def set_titles_offset(self, offset):
		_gtkextra.gtk_plot3d_set_titles_offset(self._o, offset)
	def get_titles_offset(self):
		return _gtkextra.gtk_plot3d_get_titles_offset(self._o)
	def major_grids_set_visible(self, x, y ,z):
		_gtkextra.gtk_plot3d_major_grids_set_visible(self._o, x, y ,z)
	def major_grids_visible(self):
		return _gtkextra.gtk_plot3d_major_grids_visible(self._o)
	def major_grids_get_visible(self):
		return self.major_grids_visible()
	def minor_grids_set_visible(self, x, y ,z):
		_gtkextra.gtk_plot3d_minor_grids_set_visible(self._o, x, y ,z)
	def minor_grids_visible(self):
		return _gtkextra.gtk_plot3d_minor_grids_visible(self._o)
	def minor_grids_get_visible(self):
		return self.minor_grids_visible()
	def major_zgrid_set_attributes(self, line_style, width, color):
		_gtkextra.gtk_plot3d_major_zgrid_set_attributes(self._o,
								line_style,
								width, color)
	def major_zgrid_get_attributes(self):
		return _gtkextra.gtk_plot3d_major_zgrid_get_attributes(self._o)
	def minor_zgrid_set_attributes(self, line_style, width, color):
		_gtkextra.gtk_plot3d_minor_zgrid_set_attributes(self._o,
								line_style,
								width, color)
	def minor_zgrid_get_attributes(self):
		return _gtkextra.gtk_plot3d_minor_zgrid_get_attributes(self._o)
_gtk._name2cls['GtkPlot3D'] = GtkPlot3D
	
class GtkPlotCanvas(_gtk.GtkFixed):
	get_type = _gtkextra.gtk_plot_canvas_get_type
	def __init__(self, width=None, height=None, magnification=1.0,
		     _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_plot_canvas_new(width, height,
							magnification)
	def __getattr__(self, attr):
		attrs = {
		'pixmap': _gtkextra.gtk_plot_canvas_get_pixmap,
		}
		if attrs.has_key(attr):
			return attrs[attr](self._o)
		return _gtk.GtkFixed.__getattr__(self, attr)
	def add_plot(self, plot, x, y):
		_gtkextra.gtk_plot_canvas_add_plot(self._o, plot._o, x, y)
	def cancel_action(self):
		_gtkextra.gtk_plot_canvas_cancel_action(self._o)
	def child_move(self, child, x1, y1):
		_gtkextra.gtk_plot_canvas_child_move(self._o, child, x1, y1)
	def child_move_resize(self, child, x1, y1, x2, y2):
		_gtkextra.gtk_plot_canvas_child_move_resize(self._o, child,
							    x1, y1, x2, y2)
	def export_ps(self, filename, orientation=PLOT_PORTRAIT, eps=0,
		      paper_size=PLOT_LETTER):
		return _gtkextra.gtk_plot_canvas_export_ps(self._o, filename,
							   orientation, eps,
							   paper_size)
	def export_ps_with_size(self, filename, orientation=PLOT_PORTRAIT,
				eps=0, units=PLOT_PSPOINTS,
				width=PLOT_LETTER_W, height=PLOT_LETTER_H):
		return _gtkextra.gtk_plot_canvas_export_ps_with_size(self._o,
								     filename,
								     orientation,
								     eps,
								     units,
								     width,
								     height)
	def get_active_plot(self):
		plot = _gtkextra.gtk_plot_canvas_get_active_plot(self._o)
		if plot:
			plot = _gtk._obj2inst(plot)
		return plot
	def get_active_data(self):
		plot_data =  _gtkextra.gtk_plot_canvas_get_active_data(self._o)
		if plot_data:
			plot_data = _gtk._obj2inst(plot_data)
		return plot_data
	def get_active_point(self):
		"""Return a tuple with the active point's data offset and
		coordinates.  Return None if no point is active.
		"""
		return _gtkextra.gtk_plot_canvas_get_active_point(self._o)
	def get_active_item(self):
		return _gtkextra.gtk_plot_canvas_get_active_item(self._o)
	def get_pixel(self, x, y):
		return _gtkextra.gtk_plot_canvas_get_pixel(self._o, x, y)
	def get_position(self, ix, iy):
		return _gtkextra.gtk_plot_canvas_get_position(self._o, ix, iy)
	def grid_set_attributes(self, line_style, width, color=None):
		_gtkextra.gtk_plot_canvas_grid_set_attributes(self._o,
							      line_style,
							      width, color)
	def grid_set_step(self, step):
		_gtkextra.gtk_plot_canvas_grid_set_step(self._o, step)
	def grid_set_visible(self, visible):
		_gtkextra.gtk_plot_canvas_grid_set_visible(self._o, visible)
	def put_text(self, x, y, angle, fontname, height, foreground,
		     background, trans, just, string):
		return _gtkextra.gtk_plot_canvas_put_text(self._o, x, y, angle,
							  fontname, height,
							  foreground,
							  background,
							  trans, just,
							  string)
	def put_line(self, x1, y1, x2, y2, line_style, width, color,
		     arrow_mask):
		return _gtkextra.gtk_plot_canvas_put_line(self._o, x1, y1, x2,
							  y2, line_style,
							  width, color,
							  arrow_mask)
	def put_rectangle(self, x1, y1, x2, y2, line_style, width,
			  foreground, background, border_style, fill):
		return _gtkextra.gtk_plot_canvas_put_rectangle(self._o, x1, y1,
							       x2, y2,
							       line_style,
							       width,
							       foreground,
							       background,
							       border_style,
							       fill)
	def put_ellipse(self, x1, y1, x2, y2, line_style, width,
			foreground, background, fill):
		return _gtkextra.gtk_plot_canvas_put_ellipse(self._o, x1, y1,
							     x2, y2,
							     line_style, width,
							     foreground,
							     background, fill)
	def put_pixmap(self, pixmap, x1, y1):
		return _gtkextra.gtk_plot_canvas_put_pixmap(self._o, pixmap,
							    x1, y1)
	def put_child(self, child, x1, y1, x2, y2):
		_gtkextra.gtk_plot_canvas_put_child(self._o, child, x1, y1,
						    x2, y2)
	def paint(self):
		_gtkextra.gtk_plot_canvas_paint(self._o)
	def refresh(self):
		_gtkextra.gtk_plot_canvas_refresh(self._o)
	def freeze(self):
		"""Freeze all visual updates of the canvas until you thaw it.
		"""
		_gtkextra.gtk_plot_canvas_freeze(self._o)
	def thaw(self):
		"""Thaw the sheet so that visual updates occur again.
		"""
	def remove_child(self, child):
		return _gtkextra.gtk_plot_canvas_remove_child(self._o, child)
	def set_active_plot(self, plot):
		_gtkextra.gtk_plot_canvas_set_active_plot(self._o, plot._o)
	def set_background(self, color):
		_gtkextra.gtk_plot_canvas_set_background(self._o, color)
	def set_magnification(self, magnification):
		_gtkextra.gtk_plot_canvas_set_magnification(self._o,
							    magnification)
	def set_size(self, width, height):
		_gtkextra.gtk_plot_canvas_set_size(self._o, width, height)
	def unselect(self):
		_gtkextra.gtk_plot_canvas_unselect(self._o)
	def plot_canvas_set_flags(self, flags):
		_gtkextra.GTK_PLOT_CANVAS_SET_FLAGS(self._o, flags)
	def plot_canvas_unset_flags(self, flags):
		_gtkextra.GTK_PLOT_CANVAS_UNSET_FLAGS(self._o, flags)
_gtk._name2cls['GtkPlotCanvas'] = GtkPlotCanvas

class GtkIconList(_gtk.GtkFixed):
	get_type = _gtkextra.gtk_icon_list_get_type
	def __init__(self, icon_width=48, mode=ICON_LIST_TEXT_BELOW,
		     _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_icon_list_new(icon_width, mode)
	def __getattr__(self, attr):
		attrs = {
		'num_icons': _gtkextra.gtk_icon_list_get_num_icons,
		}
		if attrs.has_key(attr):
			return attrs[attr](self._o)
		return _gtk.GtkFixed.__getattr__(self, attr)
	def __len__(self):
		return self.num_icons
	def __getitem__(self, key):
		return self.get_nth(key)
	def add(self, filename, label=None, object=None):
		return _gtkextra.gtk_icon_list_add(self._o, filename, label,
						   object)
	def add_from_data(self, data, label=None, object=None):
		return _gtkextra.gtk_icon_list_add_from_data(self._o, data,
							     label, object)
	def add_from_pixmap(self, pixmap, mask=None, label=None, object=None):
		return _gtkextra.gtk_icon_list_add_from_pixmap(self._o, pixmap,
							       mask, label,
							       object)
	def clear(self):
		_gtkextra.gtk_icon_list_clear(self._o)
	def freeze(self):
		_gtkextra.gtk_icon_list_freeze(self._o)
	def get_active_icon(self):
		return _gtkextra.gtk_icon_list_get_active_icon(self._o)
	def get_icon_at(self, x, y):
		return _gtkextra.gtk_icon_list_get_icon_at(self._o, x, y)
	def get_icon_from_link(self, object):
		return _gtkextra.gtk_icon_list_get_icon_from_link(self._o,
								  object)
	def get_index(self, item):
		return _gtkextra.gtk_icon_list_get_index(self._o, item)
	def get_nth(self, n):
		return _gtkextra.gtk_icon_list_get_nth(self._o, n)
	def remove(self, item):
		_gtkextra.gtk_icon_list_remove(self._o, item)
	def remove_nth(self, n):
		_gtkextra.gtk_icon_list_remove_nth(self._o, n)
	def select_icon(self, item):
		_gtkextra.gtk_icon_list_select_icon(self._o, item)
	def set_active_icon(self, item):
		_gtkextra.gtk_icon_list_set_active_icon(self._o, item)
	def set_background(self, color):
		_gtkextra.gtk_icon_list_set_background(self._o, color)
	def set_label(self, item, label):
		_gtkextra.gtk_icon_list_set_label(self._o, item, label)
	def set_selection_mode(self, mode):
		_gtkextra.gtk_icon_list_set_selection_mode(self._o, mode)
	def thaw(self):
		_gtkextra.gtk_icon_list_thaw(self._o)
	def unselect_all(self):
		_gtkextra.gtk_icon_list_unselect_all(self._o)
	def unselect_icon(self, item):
		_gtkextra.gtk_icon_list_unselect_icon(self._o, item)
	def update(self):
		_gtkextra.gtk_icon_list_update(self._o)
	def set_mode(self, mode):
		_gtkextra.gtk_icon_list_set_mode(self._o, mode)
	def get_mode(self):
		return _gtkextra.gtk_icon_list_get_mode(self._o)
	def set_editable(self, set_editable):
		_gtkextra.gtk_icon_list_set_editable(self._o, set_editable)
	def is_editable(self):
		return _gtkextra.gtk_icon_list_is_editable(self._o)
	def set_row_spacing(self, spacing):
		_gtkextra.gtk_icon_list_set_row_spacing(self._o, spacing)
	def get_row_spacing(self):
		return _gtkextra.gtk_icon_list_get_row_spacing(self._o)
	def set_col_spacing(self, spacing):
		_gtkextra.gtk_icon_list_set_col_spacing(self._o, spacing)
	def get_col_spacing(self):
		return _gtkextra.gtk_icon_list_get_col_spacing(self._o)
	def set_text_space(self, size):
		_gtkextra.gtk_icon_list_set_text_space(self._o, size)
	def get_text_space(self):
		return _gtkextra.gtk_icon_list_get_text_space(self._o)
	def set_icon_border(self, width):
		_gtkextra.gtk_icon_list_set_icon_border(self._o, width)
	def get_icon_border(self):
		return _gtkextra.gtk_icon_list_get_icon_border(self._o)
	def set_icon_width(self, width):
		_gtkextra.gtk_icon_list_set_icon_width(self._o, width)
	def get_icon_width(self):
		return _gtkextra.gtk_icon_list_get_icon_width(self._o)
_gtk._name2cls['GtkIconList'] = GtkIconList

class GtkDirTree(_gtk.GtkCTree):
	get_type = _gtkextra.gtk_dir_tree_get_type
	def __init__(self, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_dir_tree_new()
	def open_dir(self, path):
		return _gtkextra.gtk_dir_tree_open_dir(self._o, path)
_gtk._name2cls['GtkDirTree'] = GtkDirTree

class GtkFileList(GtkIconList):
	get_type = _gtkextra.gtk_file_list_get_type
	def __init__(self, icon_width=20, mode=ICON_LIST_TEXT_RIGHT, path=None,
		     _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_file_list_new(icon_width, mode, path)
	def add_type(self, data):
		"""Add a pixmap for a new file type.
		Returns the type number.
		"""
		return _gtkextra.gtk_file_list_add_type(self._o, data)
	def add_type_filter(self, type, pattern):
		"""Associate a shell wildcard pattern with a file type."""
		_gtkextra.gtk_file_list_add_type_filter(self._o, type, pattern)
	def get_filename(self):
		"""Return the name of the selected file or an empty string."""
		return _gtkextra.gtk_file_list_get_filename(self._o)
	def get_filetype(self):
		"""Return the file type or -1 if no file is selected."""
		return _gtkextra.gtk_file_list_get_filetype(self._o)
	def get_path(self):
		"""Return the path."""
		return _gtkextra.gtk_file_list_get_path(self._o)
	def open_dir(self, path):
		"""Open a directory."""
		return _gtkextra.gtk_file_list_open_dir(self._o, path)
	def set_filter(self, pattern):
		_gtkextra.gtk_file_list_set_filter(self._o, pattern)
_gtk._name2cls['GtkFileList'] = GtkFileList

class GtkIconFileSelection(_gtk.GtkWindow):
	get_type = _gtkextra.gtk_icon_file_selection_get_type
	def __init__(self, title='', _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_icon_file_selection_new(title)
	def __getattr__(self, attr):
		attrs = {
		'path_label': _gtkextra.gtk_icon_file_selection_get_path_label,
		'dir_tree': _gtkextra.gtk_icon_file_selection_get_dir_tree,
		'file_list': _gtkextra.gtk_icon_file_selection_get_file_list,
		'history_combo': _gtkextra.gtk_icon_file_selection_get_history_combo,
		'file_entry': _gtkextra.gtk_icon_file_selection_get_file_entry,
		'filter_entry': _gtkextra.gtk_icon_file_selection_get_filter_entry,
		'ok_button': _gtkextra.gtk_icon_file_selection_get_ok_button,
		'cancel_button': _gtkextra.gtk_icon_file_selection_get_cancel_button,
		'action_area': _gtkextra.gtk_icon_file_selection_get_action_area,
		}
		if attrs.has_key(attr):
			return _gtk._obj2inst(attrs[attr](self._o))
		return _gtk.GtkWindow.__getattr__(self, attr)
	def open_dir(self, path):
		return _gtkextra.gtk_icon_file_selection_open_dir(self._o, path)
	def show_hidden(self, visible):
		_gtkextra.gtk_icon_file_selection_show_hidden(self._o, visible)
	def show_tree(self, visible):
		_gtkextra.gtk_icon_file_selection_show_tree(self._o, visible)
	def set_filter(self, pattern):
		_gtkextra.gtk_icon_file_selection_set_filter(self._o, pattern)
_gtk._name2cls['GtkIconFileSel'] = GtkIconFileSelection

class GtkItemEntry(_gtk.GtkEntry):
	get_type = _gtkextra.gtk_item_entry_get_type
	def __init__(self, maxlen=-1, _obj=None):
		if _obj: self._o = _obj; return
		if maxlen == -1:
			self._o = _gtkextra.gtk_item_entry_new()
		else:
			self._o = _gtkextra.gtk_item_entry_new_with_max_length(maxlen)
	def set_text(self, string, justification=None):
		if justification is None:
			_gtk.GtkEntry.set_text(self, string)
		else:
			_gtkextra.gtk_item_entry_set_text(self._o, string,
							  justification)
	def set_justification(self, justification):
		_gtkextra.gtk_item_entry_set_justification(self._o,
							   justification)
	def get_justification(self):
		return _gtkextra.gtk_item_entry_get_justification(self._o)
_gtk._name2cls['GtkItemEntry'] = GtkItemEntry

class GtkFontCombo(_gtk.GtkToolbar):
	get_type = _gtkextra.gtk_font_combo_get_type
	def __init__(self, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_font_combo_new()
	def __getattr__(self, attr):
		attrs = {
		'name_combo': _gtkextra.gtk_font_combo_get_name_combo,
		'size_combo': _gtkextra.gtk_font_combo_get_size_combo,
		'bold_button': _gtkextra.gtk_font_combo_get_bold_button,
		'italic_button': _gtkextra.gtk_font_combo_get_italic_button,
		'psfont': _gtkextra.gtk_font_combo_get_psfont,
		'font': _gtkextra.gtk_font_combo_get_font,
		'height': _gtkextra.gtk_font_combo_get_height,
		'italic': _gtkextra.gtk_font_combo_get_italic,
		'bold': _gtkextra.gtk_font_combo_get_bold
		}
		if attrs.has_key(attr):
			ret = attrs[attr](self._o)
			if type(ret) == _gtk._gtk.GtkObjectType:
				return _gtk._obj2inst(ret)
			return ret
		return _gtk.GtkToolbar.__getattr__(self, attr)
	def select(self, family, bold, italic, height):
		_gtkextra.gtk_font_combo_select(self._o, family, bold, italic,
						height)
	def select_nth(self, n, bold, italic, height):
		_gtkextra.gtk_font_combo_select(self._o, n, bold, italic,
						height)
_gtk._name2cls['GtkFontCombo'] = GtkFontCombo

class GtkComboBox(_gtk.GtkHBox):
	get_type = _gtkextra.gtk_combo_box_get_type
	def __init__(self, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_combo_box_new()
	def __getattr__(self, attr):
		attrs = {
		'button': _gtkextra.gtk_combo_box_get_button,
		'arrow': _gtkextra.gtk_combo_box_get_arrow,
		'popup': _gtkextra.gtk_combo_box_get_popup,
		'popwin': _gtkextra.gtk_combo_box_get_popwin,
		'frame': _gtkextra.gtk_combo_box_get_frame
		}
		if attrs.has_key(attr):
			return _gtk._obj2inst(attrs[attr](self._o))
		return _gtk.GtkHBox.__getattr__(self, attr)
	def hide_popdown_window(self):
		_gtkextra.gtk_combo_box_hide_popdown_window(self._o)
_gtk._name2cls['GtkComboBox'] = GtkComboBox

class GtkBorderCombo(GtkComboBox):
	get_type = _gtkextra.gtk_border_combo_get_type
	def __init__(self, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_border_combo_new()
_gtk._name2cls['GtkBorderCombo'] = GtkBorderCombo

class GtkColorCombo(GtkComboBox):
	get_type = _gtkextra.gtk_color_combo_get_type
	def __init__(self, rows=0, columns=0, colors=None, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_color_combo_new(rows, columns, colors)
	def find_color(color):
		return _gtkextra.gtk_color_combo_find_color(self._o, color)
	def get_color_at(self, row, column):
		return _gtkextra.gtk_color_combo_get_color_at(self._o, row,
							      column)
_gtk._name2cls['GtkColorCombo'] = GtkColorCombo

class GtkToggleCombo(GtkComboBox):
	get_type = _gtkextra.gtk_toggle_combo_get_type
	def __init__(self, rows=0, columns=0, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_toggle_combo_new(rows, columns)
	def get_nrows(self):
		return _gtkextra.gtk_toggle_combo_get_nrows(self._o)
	def get_ncols(self):
		return _gtkextra.gtk_toggle_combo_ncols(self._o)
	def select(self, row, column):
		_gtkextra.gtk_toggle_combo_select(self._o, row, column)
	def get_selection(self):
		return _gtkextra.gtk_toggle_combo_get_selection(self._o)
_gtk._name2cls['GtkToggleCombo'] = GtkToggleCombo
	
class GtkCharSelection(_gtk.GtkWindow):
	get_type = _gtkextra.gtk_char_selection_get_type
	def __init__(self, _obj=None):
		if _obj: self._o = _obj; return
		self._o = _gtkextra.gtk_char_selection_new()
	def __getattr__(self, attr):
		attrs = {
		'font_combo': _gtkextra.gtk_char_selection_get_font_combo,
		'ok_button': _gtkextra.gtk_char_selection_get_ok_button,
		'cancel_button': _gtkextra.gtk_char_selection_get_cancel_button,
		}
		if attrs.has_key(attr):
			return _gtk._obj2inst(attrs[attr](self._o))
		return _gtk.GtkWindow.__getattr__(self, attr)
	def set_selection(self, code):
		_gtkextra.gtk_char_selection_set_selection(self._o, code)
	def get_selection(self):
		return _gtkextra.gtk_char_selection_get_selection(self._o)
_gtk._name2cls['GtkCharSelection'] = GtkCharSelection

GtkCheckItem = _gtk.GtkCheckButton

GtkSheetRange = _gtkextra.GtkSheetRange
GtkPlotLine = _gtkextra.GtkPlotLine

def psfont_init():
	return _gtkextra.gtk_psfont_init()

def psfont_unref():
	_gtkextra.gtk_psfont_unref()
	
def psfont_get_font(fontname):
	return _gtkextra.gtk_psfont_get_font(fontname)

def psfont_get_gdkfont(fontname, height):
	return _gtkextra.gtk_psfont_get_gdkfont(fontname, height)

def psfont_get_psfontname(fontname):
	return _gtkextra.gtk_psfont_get_psfontname(fontname)

def psfont_add_font(fontname, psfont, family, xfont, italic, bold):
	_gtkextra.gtk_psfont_add_font(fontname, psfont, family, xfont, italic,
				      bold)

def psfont_add_i18n_font(fontname, psfont, family, i18n_latinfamily, xfont,
			 italic, bold, vertical):
	_gtkextra.gtk_psfont_add_i18n_font(fontname, psfont, family,
					   i18n_latinfamily, xfont, italic,
					   bold, vertical)

def psfont_find_by_family(family, italic, bold):
	return _gtkextra.gtk_psfont_find_by_family(family, italic, bold)

def psfont_get_families():
	return _gtkextra.gtk_psfont_get_families()
