#!/usr/bin/env python

from gtk import *
from gtkextra import *

class Application(GtkWindow):
    
    def __init__(self):
        GtkWindow.__init__(self, title="GtkPlotFlux Demo")
        self.set_usize(550, 340)
        self.connect("destroy", mainquit)

        colormap = self.get_colormap()
        red = colormap.alloc("red")
        
        scrollwin = GtkScrolledWindow()
        scrollwin.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC)
        self.add(scrollwin)

        canvas = GtkPlotCanvas(PLOT_LETTER_W, PLOT_LETTER_H)
        canvas.plot_canvas_set_flags(PLOT_CANVAS_CAN_SELECT_POINT
                                     | PLOT_CANVAS_CAN_DND_POINT)
        canvas.connect("select_item", self.select_item)
        scrollwin.add_with_viewport(canvas)

        plot = GtkPlot(width=0.5, height=0.25)
        plot.set_range(-1.0, 1.0, -1.0, 1.4)
        plot.legends_move(0.51, 0.05)
        plot.set_legends_border(0, 0)
        plot.axis_hide_title(PLOT_AXIS_TOP)
        plot.axis_show_ticks(PLOT_AXIS_BOTTOM, 15, 3)
        plot.axis_set_ticks(PLOT_AXIS_X, 1.0, 1)
        plot.axis_set_ticks(PLOT_AXIS_Y, 1.0, 1)
        plot.axis_set_visible(PLOT_AXIS_TOP, TRUE)
        plot.axis_set_visible(PLOT_AXIS_RIGHT, TRUE)
        plot.x0_set_visible(TRUE)
        plot.y0_set_visible(TRUE)
        canvas.add_plot(plot, 0.15, 0.06)

        px1 = [0., 0.2, 0.4, 0.6, 0.8, 1.0]
        py1 = [.2, .4, .5, .35, .30, .40]
        px2 = [.12, .22, .27, .12, .052, .42]
        py2 = [.0, .05, .12, .22, .16, .1]

        data = GtkPlotFlux()
        data.set_points(px1, py1, px2, py2)
        data.set_symbol(PLOT_SYMBOL_CIRCLE, PLOT_SYMBOL_OPAQUE, 10, 2, red)
        data.set_line_attributes(PLOT_LINE_NONE, 1, red)
        data.set_legend("Flux")
        plot.add_data(data)

        self.show_all()

    def select_item(self, canvas, event, item, *args):
        if item.type == PLOT_CANVAS_DATA:
            tuple = canvas.get_active_point()
            if tuple:
                print "Active point:", tuple[0], "->", tuple[1], tuple[2]
        return TRUE
        
    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
