#!/usr/bin/env python

from gtk import *
from gtkextra import *
from random import randint

class Application(GtkWindow):

    def __init__(self):
        GtkWindow.__init__(self, title="GtkPlot Real Time Demo")
        self.set_usize(550, 600)
        self.connect("destroy", mainquit)

        colormap = self.get_colormap()
        red = colormap.alloc("red")
        light_blue = colormap.alloc("light blue")
        light_yellow = colormap.alloc("light yellow")
        white = colormap.alloc("white")

        scrollwin = GtkScrolledWindow()
        scrollwin.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC)
        self.add(scrollwin)

        canvas = GtkPlotCanvas(PLOT_LETTER_W, PLOT_LETTER_H)
        canvas.set_background(light_blue)
        canvas.connect("button_press_event", self.button_press_handler)
        scrollwin.add_with_viewport(canvas)

        plot = GtkPlot(width=0.65, height=0.45)
        plot.set_background(light_yellow)
        plot.legends_set_attributes(None, 0, None, white)
        plot.set_range(0.0, 20.0, 0.0, 1.0)
        plot.axis_set_ticks(PLOT_AXIS_X, 2.0, 1)
        plot.axis_set_ticks(PLOT_AXIS_Y, 0.1, 1)
        plot.axis_set_labels_numbers(PLOT_AXIS_TOP, PLOT_LABEL_FLOAT, 0)
        plot.axis_set_labels_numbers(PLOT_AXIS_BOTTOM, PLOT_LABEL_FLOAT, 0)
        plot.axis_set_visible(PLOT_AXIS_TOP, TRUE)
        plot.axis_set_visible(PLOT_AXIS_RIGHT, TRUE)
        plot.grids_set_visible(TRUE, TRUE, TRUE, TRUE)
        plot.axis_hide_title(PLOT_AXIS_TOP)
        plot.axis_hide_title(PLOT_AXIS_RIGHT)
        plot.axis_set_title(PLOT_AXIS_LEFT, "Intensity")
        plot.axis_set_title(PLOT_AXIS_BOTTOM, "Time (s)")
        plot.set_legends_border(PLOT_BORDER_SHADOW, 3)
        plot.legends_move(0.60, 0.10)
        canvas.add_plot(plot, 0.15, 0.15)

        canvas.put_text(0.45, 0.05, "Times-BoldItalic", 20, 0, None, None,
                        TRUE, JUSTIFY_CENTER, "Real Time Demo")

        data = GtkPlotData()
        plot.add_data(data)
        data.set_legend("Random pulse")
        data.set_symbol(PLOT_SYMBOL_DIAMOND, PLOT_SYMBOL_OPAQUE, 10, 2, red)
        data.set_line_attributes(PLOT_LINE_SOLID, 1, red)
        
        plot.clip_data(TRUE)

        self.show_all()

        timeout_add(1000, self.update, canvas, plot, data)

    def update(self, canvas, plot, data, *args):
        y = randint(0, 9) / 10.0

        px = data.get_x()
        py = data.get_y()
        
        n = data.get_numpoints()
        if n == 0:
            x = 1.0
        else:
            x = px[n - 1] + 1.0

        px.append(x)
        py.append(y)

        data.set_points(px, py)

        (xmin, xmax) = plot.get_xrange()
        if x > xmax:
            plot.set_xrange(xmin + 5.0, xmax + 5.0)

        canvas.paint()
        canvas.refresh()

        return TRUE
        
    def button_press_handler(self, canvas, event, *extra):
        (x, y) = canvas.get_pointer()
        position = canvas.get_position(x, y)
        print "Canvas position:", position[0], position[1] 

    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
