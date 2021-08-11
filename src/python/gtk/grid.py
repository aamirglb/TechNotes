#!/usr/bin/env python3
import gi

gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class GridWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title='Grid Example')

        self.buttons = []
        for i in range(6):
            self.buttons.append(Gtk.Button(label=f'Button {i+1}'))
            self.buttons[i].connect('clicked', lambda w, x=i: print(f'Button {x+1} clicked!!'))

        # self.button1 = Gtk.Button(label='Button 1')
        # self.button2 = Gtk.Button(label='Button 2')
        # self.button3 = Gtk.Button(label='Button 3')
        # self.button4 = Gtk.Button(label='Button 4')
        # self.button5 = Gtk.Button(label='Button 5')
        # self.button6 = Gtk.Button(label='Button 6')

        # self.button1.connect('clicked', lambda i=1: print(f'Button {i} clicked!!'))
        # self.button2.connect('clicked', lambda i=2: print(f'Button {i} clicked!!'))
        # self.button3.connect('clicked', lambda i=3: print(f'Button {i} clicked!!'))
        # self.button4.connect('clicked', lambda i=4: print(f'Button {i} clicked!!'))
        # self.button5.connect('clicked', lambda i=5: print(f'Button {i} clicked!!'))
        # self.button6.connect('clicked', lambda i=6: print(f'Button {i} clicked!!'))

        grid = Gtk.Grid()
        grid.add(self.buttons[0])
        grid.attach(self.buttons[1], 1, 0, 2, 1)
        grid.attach_next_to(self.buttons[2], self.buttons[0], Gtk.PositionType.BOTTOM, 1, 2)
        grid.attach_next_to(self.buttons[3], self.buttons[2], Gtk.PositionType.RIGHT, 2, 1)
        grid.attach(self.buttons[4], 1, 2, 1, 1)
        grid.attach_next_to(self.buttons[5], self.buttons[4], Gtk.PositionType.RIGHT, 1, 1)
        self.add(grid)

win = GridWindow()
win.connect('destroy', Gtk.main_quit)
win.show_all()
Gtk.main()
