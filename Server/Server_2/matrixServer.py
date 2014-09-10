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
                 y7= 7 - ( int(y) )
                 x7= 7 - (int(x) )
                 grid.setPixel( int(y),int(x7), int(color) )
                 print y,x7

def Clear_col(col):
	for i in range(0,8):
	   grid.setPixel(i,col,0)

def Bargraph(col,row):
    col_pos = 7 - col  # no need to compute it on each loop
    Clear_col(col_pos)
    print("----------------------")
    if ( row >0 and row <8 ):
        index=0
    	while ( index <row ):
            grid.setPixel( ( 7 - index ) , col_pos, 1 )
            print("index : ",index," row ",row," 7-index: ",(7-index))
            index = index+1
    else :
            print ("Out of matrix range")



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
