#!/usr/bin/env python

from gtk import *
from gtkextra import *

class Application(GtkIconFileSelection):

    def __init__(self):
        GtkIconFileSelection.__init__(self, "Open File")
        hbox = GtkHBox()
        show_button = GtkButton("Show Tree")
        hbox.pack_start(show_button)
        hide_button = GtkButton("Hide Tree")
        hbox.pack_start(hide_button)
        hbox.show_all()
        vbox = self.children()[0]
        vbox.pack_start(hbox)
        self.connect("destroy", mainquit)
        self.cancel_button.connect("clicked", mainquit)
        self.ok_button.connect("clicked", self.ok_clicked)
        show_button.connect("clicked", self.show_tree_clicked)
        hide_button.connect("clicked", self.hide_tree_clicked)
        self.show()

    def ok_clicked(self, *args):
        path = self.file_list.get_path()
        file = self.file_list.get_filename()
        if path:
            print "PATH:", path
        if file:
            print "FILE:", file

    def show_tree_clicked(self, *args):
        self.show_tree(TRUE)

    def hide_tree_clicked(self, *args):
        self.show_tree(FALSE)

    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
