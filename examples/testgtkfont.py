#!/usr/bin/env python

from gtk import *
from gtkextra import *

PREVIEW_TEXT = "ABCDEFGHI abcdefghi 0123456789"
    
class Application(GtkWindow):

    def __init__(self):
        GtkWindow.__init__(self, title="GtkFontCombo Demo")
        self.connect("destroy", mainquit)

        vbox = GtkVBox()
        self.add(vbox)

        font_combo = GtkFontCombo()
        vbox.pack_start(font_combo, FALSE, FALSE)

        preview_entry = GtkEntry()
        preview_entry.set_text(PREVIEW_TEXT)
        vbox.pack_start(preview_entry)

        self.new_font(font_combo, preview_entry)
        font_combo.connect("changed", self.new_font, preview_entry)

        self.show_all()

    def new_font(self, font_combo, preview_entry, *args):
        style = preview_entry.get_style().copy()
        style.font = font_combo.font
        preview_entry.set_style(style)
        if not preview_entry.get_text():
            preview_entry.set_text(PREVIEW_TEXT)
        preview_entry.set_position(0)
        
    def mainloop(self):
        mainloop()

if __name__ == '__main__':		
    app = Application()
    app.mainloop()
