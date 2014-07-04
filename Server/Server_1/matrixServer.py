#!/usr/bin/python -O

import sys
sys.path.append('..')                       # Adafruit libs are in previous dir

from Adafruit_8x8 import ColorEightByEight
from twisted.internet import reactor, protocol
import time

grid = ColorEightByEight(address=0x70)

class Echo(protocol.Protocol ):
    def dataReceived(self, data):
        if data.find("cls") <> -1 :
            print "clear matrix"
            clear_matrix()
        else:           
             x= iter(data)
             for x, y, color in zip(*([x] * 3)):
                 grid.setPixel(int(x),int(y), 1 )
                 time.sleep(0.02)

def clear_matrix():
    for x in range(0, 8):
       for y in range(0, 8):
          grid.setPixel(x, y, 0)

def main():
    """This runs the protocol on port 8000"""
    factory = protocol.ServerFactory()
    factory.protocol = Echo
    reactor.listenTCP(8000,factory)
    reactor.run()

# this only runs if the module was *not* imported
if __name__ == '__main__':
    main()
