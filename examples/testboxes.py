#!/usr/bin/env python

from gtk import *
from gtkextra import *

class Application(GtkWindow):

    def __init__(self):
        GtkWindow.__init__(self, title="GtkPlotBox Demo")
        self.set_usize(550, 360)
        self.connect("destroy", mainquit)

        scrollwin = GtkScrolledWindow()
        scrollwin.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC)
        self.add(scrollwin)

        canvas = GtkPlotCanvas(PLOT_LETTER_W, PLOT_LETTER_H)
        canvas.plot_canvas_set_flags(PLOT_CANVAS_DND_FLAGS)
        scrollwin.add_with_viewport(canvas)

        plot = GtkPlot(width=0.5, height=0.25)
        plot.set_range(-1.0, 1.0, -1.0, 1.4)
        plot.legends_move(0.51, 0.05)
        plot.set_legends_border(PLOT_BORDER_NONE)
        plot.axis_hide_title(PLOT_AXIS_TOP)
        plot.axis_show_ticks(PLOT_AXIS_BOTTOM, 15, 3)
        plot.axis_set_ticks(PLOT_AXIS_X, 1.0, 1)
        plot.axis_set_ticks(PLOT_AXIS_Y, 1.0, 1)
        plot.x0_set_visible(TRUE);
        plot.y0_set_visible(TRUE);
        canvas.add_plot(plot, 0.15, 0.06)

        self.build_example1(plot)
        
        self.show_all()

    def build_example1(self, plot):
        px1 = [0.0, 0.2, 0.4, 0.6, 0.8, 1.0]
        py1 = [0.56, 0.12, 0.123, 0.5, 0.2, 0.21]
        pz1 = [0.12, 0.22, 0.27, 0.12, 0.052, 0.42]
        dz1 = [0.0243, 0.045, 0.075, 0.0213, 0.05, 0.0324]

        colormap = self.get_colormap()
        red = colormap.alloc("red")
        yellow = colormap.alloc("yellow")
        
        data = GtkPlotBox(ORIENTATION_VERTICAL)
        plot.add_data(data)
        data.set_points(px1, py1)
        data.set_z(pz1)
        data.set_dz(dz1)
        data.show_zerrbars()
        data.set_symbol(PLOT_SYMBOL_CIRCLE, PLOT_SYMBOL_FILLED, 10, 2,
                        yellow, red)
        data.set_line_attributes(PLOT_LINE_NONE, 1, red)
        data.set_legend("Boxes")
        
    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
