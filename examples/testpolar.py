#!/usr/bin/env python

from gtk import *
from gtkextra import *

class Application(GtkWindow):

    def __init__(self):
        GtkWindow.__init__(self, title="GtkPlotPolar Demo")
        self.set_usize(500, 320)
        self.connect("destroy", mainquit)

        colormap = self.get_colormap()
        red = colormap.alloc("red")
        
        scrollwin = GtkScrolledWindow()
        scrollwin.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC)
        self.add(scrollwin)

        canvas = GtkPlotCanvas(PLOT_LETTER_W, PLOT_LETTER_H)
        canvas.plot_canvas_set_flags(PLOT_CANVAS_DND_FLAGS)
        scrollwin.add_with_viewport(canvas)

        plot = GtkPlotPolar(width=0.5, height=0.25)
        canvas.add_plot(plot, 0.15, 0.06)

        r = [0.2, 0.34, 0.45, 0.6, 0.75, 0.81]
        angle = [15.0, 20.0, 43.0, 67.0, 84.0, 106.0]
    
        data = GtkPlotData()
        data.set_points(r, angle)
        data.set_symbol(PLOT_SYMBOL_DIAMOND, PLOT_SYMBOL_OPAQUE, 10, 2, red)
        data.set_line_attributes(PLOT_LINE_SOLID, 1, red)
        data.set_legend("Example")
        plot.add_data(data)

        self.show_all()

    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
