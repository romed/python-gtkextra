#!/usr/bin/env python

from gtk import *
from gtkextra import *
from math import exp, pow, sin
import icons

class Application(GtkWindow):

    scale = 1.0
    
    def __init__(self):
        self.nlayers = 0
        self.buttons = []
        self.plots = []
        
        page_width = PLOT_LETTER_W * self.scale
        page_height = PLOT_LETTER_H * self.scale
    
        GtkWindow.__init__(self, title="GtkPlot Demo")
        self.set_usize(550, 650)
        self.connect("destroy", mainquit)

        scrollwin = GtkScrolledWindow()
        scrollwin.set_policy(POLICY_ALWAYS, POLICY_ALWAYS)
        self.add(scrollwin)

        colormap = self.get_colormap()
        light_yellow = colormap.alloc("light yellow")
        light_blue = colormap.alloc("light blue")

        canvas = GtkPlotCanvas(page_width, page_height)
        canvas.plot_canvas_set_flags(PLOT_CANVAS_DND_FLAGS)
        scrollwin.add_with_viewport(canvas)
        canvas.set_size(page_width, page_height)

        plot = self.new_layer(canvas)
        plot.set_range(-1.0, 1.0, -1.0, 1.4)
        plot.legends_move(0.51, 0.05)
        plot.set_legends_border(PLOT_BORDER_NONE)
        plot.axis_hide_title(PLOT_AXIS_TOP)
        plot.axis_set_ticks(PLOT_AXIS_X, 1.0, 1)
        plot.axis_set_ticks(PLOT_AXIS_Y, 1.0, 1)
        plot.axis_set_visible(PLOT_AXIS_TOP, TRUE)
        plot.axis_set_visible(PLOT_AXIS_RIGHT, TRUE)
        plot.x0_set_visible(TRUE)
        plot.y0_set_visible(TRUE)
        plot.axis_set_labels_suffix(PLOT_AXIS_LEFT, "%");
        canvas.add_plot(plot, 0.15, 0.06)
        self.build_example1(plot)

        plot = self.new_layer(canvas)
        plot.set_background(light_yellow)
        plot.legends_set_attributes(None, 0, None, light_blue)
        plot.set_range(0.0, 1.0, 0.0, 0.85)
        plot.axis_set_visible(PLOT_AXIS_TOP, TRUE)
        plot.axis_set_visible(PLOT_AXIS_RIGHT, TRUE)
        plot.axis_hide_title(PLOT_AXIS_TOP)
        plot.axis_hide_title(PLOT_AXIS_RIGHT)
        plot.grids_set_visible(TRUE, TRUE, TRUE, TRUE)
        plot.set_legends_border(PLOT_BORDER_SHADOW, 3)
        plot.legends_move(0.58, 0.05)
        canvas.add_plot(plot, 0.15, 0.4)
        self.build_example2(plot)
        canvas.connect("select_item", self.select_item)

        canvas.put_text(0.40, 0.02, "Times-BoldItalic", 16, 0, None, None,
                        TRUE, JUSTIFY_CENTER, "DnD titles, legends and plots")
        canvas.put_text(0.40, 0.72, "Times-Roman", 16, 0, None, None,
                        TRUE, JUSTIFY_CENTER,
                        "You can use \\ssubscripts\\b\\b\\b\\b\\b\\b\\b"\
                        "\\b\\b\\b\\N\\Ssuperscripts")
        child = canvas.put_text(0.40, 0.755, "Times-Roman", 16, 0, None, None,
                                TRUE, JUSTIFY_CENTER,
                                "Format text mixing \\Bbold \\N\\i, italics, "\
                                "\\ggreek \\4\\N and \\+different fonts")
        child.data.set_border(PLOT_BORDER_SHADOW, 2, 0, 2)

        self.show_all()

        try:
            canvas.export_ps_with_size("plotdemo.ps", eps=TRUE)
            print "Wrote plotdemo.ps"
        except:
            pass

    def select_item(self, canvas, event, item, *args):
        if item.type == PLOT_CANVAS_TEXT:
            print "Item selected: TEXT"
        elif item.type == PLOT_CANVAS_TITLE:
            print "Item selected: TITLE"
        elif item.type == PLOT_CANVAS_LEGENDS:
            print "Item selected: LEGENDS"
        elif item.type == PLOT_CANVAS_PLOT:
            print "Item selected: PLOT"
        elif item.type == PLOT_CANVAS_AXIS:
            print "Item selected: AXIS"
        elif item.type == PLOT_CANVAS_PIXMAP:
            print "Item selected: PIXMAP"
        elif item.type == PLOT_CANVAS_DATA:
            print "Item selected: DATA"
        elif item.type == PLOT_CANVAS_NONE:
            print "Item selected: NONE"
        plot = canvas.get_active_plot()
        for n in xrange(self.nlayers):
            if plot == self.plots[n]:
                canvas.set_active_plot(plot)
                self.buttons[n].set_active(TRUE)
            else:
                self.buttons[n].set_active(FALSE)
        return TRUE

    def activate_plot(self, button, canvas, *args):
        if button.get_active():
            for n in xrange(self.nlayers):
                if button == self.buttons[n]:
                    canvas.set_active_plot(self.plots[n])
                else:
                    self.buttons[n].set_active(FALSE) 
        return TRUE

    def activate_button(self, canvas, *args):
        plot = canvas.get_active_plot()
        for n in xrange(self.nlayers):
            if plot == self.plots[n]:
                self.buttons[n].set_active(TRUE)
            else:
                self.buttons[n].set_active(FALSE)
        return TRUE
        
    def new_layer(self, canvas):
        self.nlayers = self.nlayers + 1
        button = GtkToggleButton(str(self.nlayers))
        button.set_usize(20, 20)
        canvas.put(button, (self.nlayers - 1) * 20, 0)
        button.connect("toggled", self.activate_plot, canvas)
        plot = GtkPlot(width=0.5, height=0.25)
        self.buttons.append(button)
        self.plots.append(plot)
        button.set_active(TRUE)
        return plot

    def build_example1(self, plot):
        px1 = [0., .2, .4, .6, .8, 1.]
        py1 = [.2, .4, .5, .35, .30, .40]
        dx1 = [.2, .2, .2, .2, .2, .2]
        dy1 = [.1, .1, .1, .1, .1, .1]

        px2 = [0., -.2, -.4, -.6, -.8, -1.]
        py2 = [.2, .4, .5, .35, .30, .40]
        dx2 = [.2, .2, .2, .2, .2, .2]
        dy2 = [.1, .1, .1, .1, .1, .1]

        colormap = self.get_colormap()
        red = colormap.alloc("red")
        black = colormap.alloc("black")
        blue = colormap.alloc("blue")

        data = GtkPlotData()
        plot.add_data(data)
        data.set_points(px1, py1, dx1, dy1)
        data.set_symbol(PLOT_SYMBOL_DIAMOND, PLOT_SYMBOL_EMPTY, 10, 2, red)
        data.set_line_attributes(PLOT_LINE_SOLID, 1, red)
        data.set_connector(PLOT_CONNECT_SPLINE)
        data.show_yerrbars()
        data.set_legend("Spline + EY")

        data = GtkPlotData()
        plot.add_data(data)
        data.set_points(px2, py2, dx2, dy2)
        data.set_symbol(PLOT_SYMBOL_SQUARE, PLOT_SYMBOL_OPAQUE, 8, 2, black)
        data.set_line_attributes(PLOT_LINE_SOLID, 4, red)
        data.set_connector(PLOT_CONNECT_STRAIGHT)
        data.set_x_attributes(PLOT_LINE_SOLID, 0, black)
        data.set_y_attributes(PLOT_LINE_SOLID, 0, black)
        data.set_legend("Line + Symbol")
        
        data = plot.add_function(self.function)
        data.set_line_attributes(PLOT_LINE_SOLID, 0, blue)
        data.set_legend("Function Plot")

    def build_example2(self, plot):
        px2 = [.1, .2, .3, .4, .5, .6, .7, .8]
        py2 = [.012, .067, .24, .5, .65, .5, .24, .067]
        dx2 = [.1, .1, .1, .1, .1, .1, .1, .1]

        colormap = self.get_colormap()
        dark_green = colormap.alloc("dark green")
        blue = colormap.alloc("blue")
        
        data = plot.add_function(self.gaussian)
        data.set_line_attributes(PLOT_LINE_DASHED, 2, dark_green)
        data.set_legend("Gaussian")

        data = GtkPlotBar(ORIENTATION_VERTICAL)
        plot.add_data(data)
        data.set_points(px2, py2, dx2)
        data.set_symbol(PLOT_SYMBOL_NONE, PLOT_SYMBOL_OPAQUE, 10, 2, blue)
        data.set_line_attributes(PLOT_LINE_NONE, 1, blue)
        data.set_connector(PLOT_CONNECT_NONE)
        data.set_legend("V Bars")
        
    def function(self, x, *extra):
        try:
            return -0.5 + 0.3 * sin(3.0 * x) * sin(50.0 * x)
        except:
            return None

    def gaussian(self, x, *extra):
        try:
            return 0.65 * exp(-0.5 * pow(x - 0.5, 2) / 0.02)
        except:
            return None

    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
