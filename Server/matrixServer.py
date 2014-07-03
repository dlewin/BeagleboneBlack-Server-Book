#!/usr/bin/python -O
# source: https://github.com/pdp7/beaglebackpack/blob/master/README.md

from Adafruit_8x8 import ColorEightByEight
from twisted.internet import reactor, protocol


grid = ColorEightByEight(address=0x70)

class Echo(protocol.Protocol ):
    def dataReceived(self, data):
        if data.find("cls") <> -1 :
            print "clear matrix"
            clear_matrix()
        else:           
            print "received:"
            received=  data.split() 
            print ( received )
            #print (  received[0]+ '/' + received[1] ) 
        #echo:        self.transport.write(data)

#        grid.setPixel(x, y, color % 4)

'''for x in range(0, 8):
    for y in range(0, 8):
        grid.setPixel(x, y, color % 4)'''

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
