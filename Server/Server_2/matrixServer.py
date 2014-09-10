#!/usr/bin/python -O

import sys
sys.path.append('..')                          # Adafruit libs are in previous dir

from Adafruit_8x8 import ColorEightByEight     # import the color version of the matrix lib
from twisted.internet import reactor, protocol # we use the twisted matrix lib
import time

grid = ColorEightByEight(address=0x70)         # create a grid object to represent the matrix

class Echo(protocol.Protocol ):
    def dataReceived(self, data):
        if data.find("cls") <> -1 :
            print "clear matrix"
            clear_matrix()
        else:                                  # a data has been received, let's use it
             x= iter(data)                     # iterate over the received data
             for x, y, color in zip(*([x] * 3)): # the data itself relies on x,y and a color attribute
                 y7= 7 - ( int(y) )            # an adapation to represent the same coordinates 
                 x7= 7 - (int(x) )             # as on the client screen (letft/top)
                 grid.setPixel( int(y),int(x7), int(color) )  # light the led

def Clear_col(col):
	for i in range(0,8):
	   grid.setPixel(i,col,0)

def Bargraph(col,row):
    col_pos = 7 - col  				# no need to compute it on each loop
    Clear_col(col_pos)
    
    if ( row >0 and row <8 ):
        index=0
    	while ( index <row ):
            grid.setPixel( ( 7 - index ) , col_pos, 1 )
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
