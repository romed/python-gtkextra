#!/usr/bin/env python

from gtk import *
from gtkextra import *

class Application(GtkWindow):
    
    def __init__(self):
        GtkWindow.__init__(self, title="Bubbles Demo")
        self.set_usize(550, 650)
        self.connect("destroy", mainquit)

        colormap = self.get_colormap()
        blue = colormap.alloc("blue")
        
        scrollwin = GtkScrolledWindow()
        scrollwin.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC)
        self.add(scrollwin)

        canvas = GtkPlotCanvas(PLOT_LETTER_W, PLOT_LETTER_H)
        canvas.plot_canvas_set_flags(PLOT_CANVAS_DND_FLAGS)
        scrollwin.add_with_viewport(canvas)

        plot = GtkPlot(width=0.5, height=0.25)
        plot.legends_move(0.05, 0.05)
        plot.set_legends_border(0, 0)
        plot.axis_hide_title(PLOT_AXIS_TOP)
        plot.axis_show_ticks(PLOT_AXIS_BOTTOM, 15, 3)
        plot.axis_set_visible(PLOT_AXIS_TOP, TRUE)
        plot.axis_set_visible(PLOT_AXIS_RIGHT, TRUE)
        plot.grids_set_visible(TRUE, TRUE, TRUE, TRUE)
        canvas.add_plot(plot, 0.15, 0.06)

        px1 = [0., 0.1, 0.2, 0.3, 0.4, 0.5, .6, .7, .8, .9]
        py1 = [.2, .4, .5, .35, .30, .40, .45, .56, .76, .87]
        pa1 = [.12, .22, .27, .12, .052, .12, .045, .214, .123, .088]
        pda1 = [.132, .23, .432, .34, .46, .56, .785, .76, .86, .89]

        data = GtkPlotData()
        data.set_points(px1, py1)
        data.set_a(pa1)
        data.set_da(pda1)
        data.set_symbol(PLOT_SYMBOL_CIRCLE, PLOT_SYMBOL_OPAQUE, 10, 2, blue)
        data.set_line_attributes(PLOT_LINE_NONE, 1, blue)
        data.set_legend("Bubbles")
        data.gradient_set_visible(TRUE)
        plot.add_data(data)

        self.show_all()

    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
