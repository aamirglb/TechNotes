import gi

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class MyWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title='Hello World!!')

        self.vbox = Gtk.VBox(spacing=6)
        self.add(self.vbox)

        self.button = Gtk.Button(label='Click Me')
        self.button.connect('clicked', self.on_button_clicked)
        self.vbox.add(self.button)

        self.quit = Gtk.Button(label='Quit')
        # self.quit.connect('clicked', self.on_quit)
        self.quit.connect('clicked', lambda x: Gtk.main_quit())
        self.vbox.add(self.quit)

        self.label = Gtk.Label()
        self.label.set_label("Hello GTK+!!")
        self.label.set_angle(25)
        self.label.set_halign(Gtk.Align.CENTER)
        self.vbox.add(self.label)

    def on_button_clicked(self, widget):
        w = Gtk.Label()
        for i, p in enumerate(dir(w.props)):
            print(f'{i}. {p}')
        # print('Hello World')

    def on_quit(self, widget):
        print('Quiting application')
        Gtk.main_quit()

win = MyWindow()
win.connect('destroy', Gtk.main_quit)
win.show_all()
Gtk.main()