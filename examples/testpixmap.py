#!/usr/bin/env python

from gtk import *
from gtkextra import *

class Application(GtkWindow):
    
    cloud_xpm = [
        "24 24 5 1",
        " 	c None",
        "x	c #FFFFFFFFFFFF",
        ".	c #6E6E6E6E6E6E",
        "X	c #000000000000",
        "o	c #CCCCCCCCCCCC",
        "                        ",
        "                        ",
        "                        ",
        "                        ",
        "                        ",
        "         .....          ",
        "        .xxxxxX         ",
        "      ...xxxxxxX        ",
        "     .xxxxxxxxxxX       ",
        "    .xxxxoxxxoxx.XXX    ",
        "    .xxxxxooxxo.xxxXX   ",
        "  ..xxxoxxxoxoxxxxxxXX  ",
        " ..xxxxoxxxxxxxoxxxoxX  ",
        " .xxxxxoxxxxxxooxoxxxX  ",
        " XxxxxxoxoXxxooXoxoxXXX ",
        " Xxooooooooooo.XoooxXoX ",
        " XXooxooXXoo..Xooo.Xo.X ",
        "  XX....XXo..XX...XX.XX ",
        "   XX..XXX.XXXX..XXXXX  ",
        "    XXXX XXX XXXXX      ",
        "                        ",
        "                        ",
        "                        ",
        "                        "]

    suncloud_xpm = [
        "24 24 7 1",
        " 	c None",
        "x	c #FFFFFFFFFFFF",
        ".	c #F7F7BABA3C3C",
        "X	c #FFFFFFFF0000",
        "o	c #AAAAAAAAAAAA",
        "O	c #000000000000",
        "+	c #CCCCCCCCCCCC",
        "@	c #6E6E6E6E6E6E",
        "                        ",
        "        .  .            ",
        "     .  .  .  .         ",
        "      .XX..XX.          ",
        "   .  X......X  .       ",
        "    .X..XXXX..X.        ",
        "    X.XXXXXXXX.X        ",
        "  ..X.XXXXXXXX.X..      ",
        "   X.XXXXoooooX.X       ",
        "   X.XXXoxxxxxO.X       ",
        " ....XoooxxxxxxO...     ",
        "   X.oxxxxxxxxxxO       ",
        "   Xooxxx+xxx+xx@OOO    ",
        "   .oxxxxx++xx+@xxxOO   ",
        "  @@xxx+xxx+x+xxxxxxOO  ",
        " @@xxxx+xxxxxxx+xxx+xO  ",
        " @xxxxx+xxxxxx++x+xxxO  ",
        " Oxxxxx+x+Oxx++O+x+xOOO ",
        " Ox+++++++++++@O+++xO+O ",
        " OO++x++OO++@@O+++@O+@O ",
        "  OO@@@@OO+@@OO@@@OO@OO ",
        "   OO@@OOO@OOOO@@OOOOO  ",
        "    OOOO OOO OOOOO      ",
        "                        "]

    def __init__(self):
        GtkWindow.__init__(self, title="GtkPlotPixmap Demo")
        self.set_usize(500, 320)
        self.connect("destroy", mainquit)

        colormap = self.get_colormap()
        
        canvas = GtkPlotCanvas(PLOT_LETTER_W, PLOT_LETTER_H)
        canvas.plot_canvas_set_flags(PLOT_CANVAS_DND_FLAGS)
        self.add(canvas)

        plot = GtkPlot(width=0.5, height=0.25)
        plot.set_range(0.0, 1.0, 0.0, 1.4)
        plot.legends_move(0.5, 0.05)
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
        px2 = [.0, .2, .4, .6, .8, 1.0]
        py2 = [.12, .22, .27, .12, .52, .62]

        (pixmap, mask) = create_pixmap_from_xpm_d(colormap, None,
                                                  self.cloud_xpm)
        data = GtkPlotPixmap(pixmap, mask)
        data.set_points(px1, py1, px2, py2)
        data.set_legend("Pixmap 1")
        plot.add_data(data)

        (pixmap, mask) = create_pixmap_from_xpm_d(colormap, None,
                                                  self.suncloud_xpm)
        data = GtkPlotPixmap(pixmap, mask)
        data.set_points(px2, py2)
        data.set_legend("Pixmap 2")
        plot.add_data(data)

        self.show_all()

        try:
            canvas.export_ps("demopixmap.ps")
            print "Wrote demopixmap.ps"
        except:
            pass

    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
