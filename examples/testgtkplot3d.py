#!/usr/bin/env python

from gtk import *
from gtkextra import *
from math import cos

class Application(GtkWindow):

    def __init__(self):
        GtkWindow.__init__(self, title="GtkPlot3D Demo")
        self.set_usize(550, 650)
        self.connect("destroy", mainquit)

        scrollwin = GtkScrolledWindow()
        scrollwin.set_policy(POLICY_ALWAYS, POLICY_ALWAYS)
        self.add(scrollwin)

        canvas = GtkPlotCanvas(PLOT_LETTER_W, PLOT_LETTER_H)
        canvas.plot_canvas_set_flags(PLOT_CANVAS_DND_FLAGS)
        scrollwin.add_with_viewport(canvas)

        plot = GtkPlot3D(width=0.7, height=0.7)
        plot.axis_set_minor_ticks(PLOT_AXIS_X, 1)
        plot.axis_set_minor_ticks(PLOT_AXIS_Y, 1)
        plot.axis_show_ticks(PLOT_SIDE_XY, PLOT_TICKS_OUT, PLOT_TICKS_OUT)
        plot.axis_show_ticks(PLOT_SIDE_XZ, PLOT_TICKS_OUT, PLOT_TICKS_OUT)
        plot.axis_show_ticks(PLOT_SIDE_YX, PLOT_TICKS_OUT, PLOT_TICKS_OUT)
        plot.axis_show_ticks(PLOT_SIDE_YZ, PLOT_TICKS_OUT, PLOT_TICKS_OUT)
        plot.axis_show_ticks(PLOT_SIDE_ZX, PLOT_TICKS_OUT, PLOT_TICKS_OUT)
        plot.axis_show_ticks(PLOT_SIDE_ZY, PLOT_TICKS_OUT, PLOT_TICKS_OUT)
        canvas.add_plot(plot, 0.10, 0.06)

        surface = GtkPlotSurface(self.function)
        surface.set_xstep(0.025)
        surface.set_ystep(0.025)
        surface.set_legend("cos ((r-r\\s0\\N)\\S2\\N)")
        plot.add_data(surface)

        button = GtkButton("Rotate X")
        button.connect("clicked", self.rotate_x, canvas, plot)
        canvas.put(button, 150, 0)
        
        button = GtkButton("Rotate Y")
        button.connect("clicked", self.rotate_y, canvas, plot)
        canvas.put(button, 230, 0)
        
        button = GtkButton("Rotate Z")
        button.connect("clicked", self.rotate_z, canvas, plot)
        canvas.put(button, 310, 0)
        
        self.show_all()

        try:
            canvas.export_ps_with_size("demo3d.ps")
            print "Wrote demo3d.ps"
        except:
            pass

    def function(self, x, y, *extra):
        return cos(((x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5)) * 24.0) \
               / 4.0 + 0.5

    def rotate_x(self, button, canvas, plot, *extra):
        plot.rotate_x(10.0)
        canvas.paint()
        canvas.refresh()
        
    def rotate_y(self, button, canvas, plot, *extra):
        plot.rotate_y(10.0)
        canvas.paint()
        canvas.refresh()
        
    def rotate_z(self, button, canvas, plot, *extra):
        plot.rotate_z(10.0)
        canvas.paint()
        canvas.refresh()
        
    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
