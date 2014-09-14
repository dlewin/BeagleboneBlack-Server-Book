"""
    BeagleBone Black book code by David Lewin
    Client 1 version to use with the server 
   
    Start first matrixServer.py from the server before running this.
    
    
This simple code aims to show you how to send data packets to
 the server (BeagleBone) which accepts to receive commands 
 for the leds matrix    
    
"""

from twisted.internet import reactor, protocol
from twisted.protocols import basic

# a client protocol

class EchoClient(protocol.Protocol):
    """Once connected, send a message, then print the result."""
    
    def connectionMade(self):
        for i in range(0,8):
           for j in range(0,8):
               conct = str(i) + str(j) + str(1)
               #self.transport.write(conct +'\r\n')            
               self.transport.write(conct)            
               print conct
    def dataReceived(self, data):
        "As soon as any data is received, write it back."
        print "Server said:", data
        self.transport.loseConnection()
    
    def connectionLost(self, reason):
        print "connection lost"

class EchoFactory(protocol.ClientFactory):
    protocol = EchoClient

    def clientConnectionFailed(self, connector, reason):
        print "Connection failed - goodbye!"
        reactor.stop()
    
    def clientConnectionLost(self, connector, reason):
        print "Connection lost - goodbye!"
        reactor.stop()


# this connects the protocol to a server runing on port 8000
def main():
    f = EchoFactory()
    reactor.connectTCP("192.168.0.15", 8000, f)
    reactor.run()

# this only runs if the module was *not* imported
if __name__ == '__main__':
    main()
