#!/usr/bin/env python

from gtk import *
from gtkextra import *
import icons

class Application(GtkWindow):

    def __init__(self):
        GtkWindow.__init__(self, title="GtkIconList Demo")
        self.set_usize(400, 400)
        self.connect("destroy", mainquit)

        hbox1 = GtkHBox()
        self.add(hbox1)

        table = GtkTable(4, 2)
        hbox1.pack_start(table, FALSE, FALSE)

        notebook = GtkNotebook()
        hbox1.pack_start(notebook)

        scrollw1 = GtkScrolledWindow()
        scrollw1.set_border_width(0)
        scrollw1.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC)
        label1 = GtkLabel("Worksheets")
        notebook.append_page(scrollw1, label1)

        scrollw2 = GtkScrolledWindow()
        scrollw2.set_border_width(0)
        scrollw2.set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC)
        label2 = GtkLabel("Plots")
        notebook.append_page(scrollw2, label2)

        iconlist1 = GtkIconList(48, ICON_LIST_TEXT_BELOW)
        iconlist1.set_selection_mode(SELECTION_SINGLE)
        iconlist1.connect("select_icon", self.select_icon)
        scrollw1.add_with_viewport(iconlist1)
        for i in xrange(20):
            iconlist1.add_from_data(icons.sheet_icon2, "Data %02d" % i)

        iconlist2 = GtkIconList(48, ICON_LIST_TEXT_RIGHT)
        iconlist2.set_selection_mode(SELECTION_MULTIPLE)
        scrollw2.add_with_viewport(iconlist2)
        for i in xrange(20):
            iconlist2.add_from_data(icons.plot_icon2, "Plot %02d" % i)

        self.show_all()

    def select_icon(self, widget, item, event, *args):
        print "SELECTION:", item.label
        return TRUE
    
    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
