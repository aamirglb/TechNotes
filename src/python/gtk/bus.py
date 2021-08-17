# import gi
# from gi.repository import GObject
import gobject
import dbus
import dbus.service

from dbus.mainloop.glib import DBusGMainLoop
DBusGMainLoop(set_as_default=True)


OPATH = "/temp/Test"
IFACE = "temp.Test"
BUS_NAME = "temp.Test"


class MyService(dbus.service.Object):
    def __init__(self):
        bus = dbus.SessionBus()
        bus.request_name(BUS_NAME, dbus.bus.NAME_FLAG_REPLACE_EXISTING)
        bus_name = dbus.service.BusName(BUS_NAME, bus=bus)
        dbus.service.Object.__init__(self, bus_name, OPATH)

    @dbus.service.method(dbus_interface=IFACE, in_signature="s")
    def Echo(self, message):
        return "received: " + message


if __name__ == "__main__":
    my_service = MyService()
    loop = gobject.MainLoop()
    loop.run()