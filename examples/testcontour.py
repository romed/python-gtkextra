#!/usr/bin/env python

from gtk import *
from gtkextra import *
from math import cos

class Application(GtkWindow):

    def __init__(self):
        GtkWindow.__init__(self, title="Contour Demo")
        self.set_usize(550, 600)
        self.connect("destroy", mainquit)

        scrollwin = GtkScrolledWindow()
        scrollwin.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC)
        self.add(scrollwin)

        canvas = GtkPlotCanvas(PLOT_LETTER_W, PLOT_LETTER_H)
        canvas.plot_canvas_set_flags(PLOT_CANVAS_DND_FLAGS)
        scrollwin.add_with_viewport(canvas)

        plot = GtkPlot3D(width=0.5, height=0.5)
        plot.axis_set_minor_ticks(PLOT_AXIS_X, 3)
        plot.axis_set_minor_ticks(PLOT_AXIS_Y, 3)
        plot.minor_grids_set_visible(FALSE, FALSE, FALSE)
        canvas.add_plot(plot, 0.16, 0.02)

        surface = GtkPlotCSurface(self.function)
        surface.set_xstep(0.025)
        surface.set_ystep(0.025)
        surface.set_legend("cos ((r-r\\s0\\N)\\S2\\N)")
        surface.set_gradient(0.2, 0.8, 6)
        plot.add_data(surface)

        plot = GtkPlot(width=0.4, height=0.4)
        plot.axis_set_minor_ticks(PLOT_AXIS_X, 1)
        plot.axis_set_minor_ticks(PLOT_AXIS_Y, 1)
        canvas.add_plot(plot, 0.26, 0.56)

        surface = GtkPlotCSurface(self.function)
        surface.set_xstep(0.025)
        surface.set_ystep(0.025)
        surface.set_legend("cos ((r-r\\s0\\N)\\S2\\N)")
        surface.set_gradient(0.2, 0.8, 6)
        surface.set_grid_visible(FALSE)
        surface.set_lines_only(TRUE)
        plot.add_data(surface)
        
        self.show_all()

    def function(self, x, y):
        return cos(((x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5)) * 24.0) \
               / 3.0 + 0.5

    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
