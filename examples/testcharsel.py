#!/usr/bin/env python

from gtk import *
from gtkextra import *

class Application(GtkCharSelection):

    def __init__(self):
        GtkCharSelection.__init__(self)
        self.connect("destroy", mainquit)
        self.cancel_button.connect("clicked", mainquit)
        self.ok_button.connect("clicked", self.ok_clicked)
        self.show()

    def ok_clicked(self, *args):
        psfont = self.font_combo.psfont
        psname = psfont.psname
        code = self.get_selection()
        print "%s, %d" % (psname, code)
        
    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
