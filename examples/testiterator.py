#!/usr/bin/env python

from gtk import *
from gtkextra import *
from random import randint

class Application(GtkWindow):

    def __init__(self):
        GtkWindow.__init__(self, title="GtkPlot Iterator Demo")
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
        plot.axis_set_title(PLOT_AXIS_BOTTOM, "Point")
        plot.set_legends_border(PLOT_BORDER_SHADOW, 3)
        plot.legends_move(0.60, 0.10)
        canvas.add_plot(plot, 0.15, 0.15)

        canvas.put_text(0.45, 0.05, "Times-BoldItalic", 20, 0, None, None,
                        TRUE, JUSTIFY_CENTER, "Iterator Demo")

        mask = PLOT_DATA_X | PLOT_DATA_Y | PLOT_DATA_LABELS
        data = GtkPlotData((self.iterator, 20, mask))
        data.show_labels(TRUE)
        plot.add_data(data)
        data.set_legend("Iterator")
        data.set_symbol(PLOT_SYMBOL_DIAMOND, PLOT_SYMBOL_OPAQUE, 10, 2, red)
        data.set_line_attributes(PLOT_LINE_SOLID, 1, red)
        
        self.show_all()

    def iterator(self, i, *args):
        x = i
        y = randint(0, 9) / 10.0
        label = str(i)
        return (x, y, None, None, None, None, None, None, label)

    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
