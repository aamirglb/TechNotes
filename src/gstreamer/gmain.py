import sys
import gi
gi.require_version('GLib', '2.0')

from gi.repository import GLib

counter = 0

def timeout_cb(max_cnt, loop):
    global counter
    counter += 1

    if counter > max_cnt:
        loop.quit()
        return False
    
    print("Timeout callback: {}".format(counter))
    return True
    

def main(args):
    if len(args) > 1:
        max_cnt = int(args[1])
    else:
        max_cnt = 10

    loop = GLib.MainLoop()
    # GLib.timeout_add_seconds(1, timeout_cb, max_cnt, loop)
    GLib.timeout_add(500, timeout_cb, max_cnt, loop)
    try:
      loop.run()
    except:
      pass

if __name__ == '__main__':
    sys.exit(main(sys.argv))
