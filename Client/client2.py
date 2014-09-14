 """
 BeagleBone Black book code by David Lewin
    Client 2 version to use with the server 
   
    Start first matrixServer.py from the server before running this.


 This kivy App aims to show you how to interact with 
 the server (BeagleBone) which accepts to receive commands 
 for the leds matrix


 This kivy App aims to show you how to interact with 
 the server (BeagleBone) which accepts to receive commands 
 for the leds matrix
"""

#imports section
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.stacklayout import StackLayout
from kivy.uix.anchorlayout import AnchorLayout
from kivy.uix.button import Button
from kivy.uix.slider import Slider
from kivy.uix.spinner import Spinner
from kivy.support import install_twisted_reactor
install_twisted_reactor()
from twisted.internet import reactor, protocol

class EchoClient(protocol.Protocol):
    def connectionMade(self):                               # Event when on a connection
        self.factory.app.on_connection(self.transport)

    def dataReceived(self, data):                           # if the server wants to talk to us 
        self.factory.app.print_message(data)

class EchoFactory(protocol.ClientFactory):
    protocol = EchoClient
    def __init__(self, app):
        self.app = app

    def clientConnectionLost(self, conn, reason):           # We were on a connection and something happened
        self.app.print_message("connection lost")

    def clientConnectionFailed(self, conn, reason):         # We can't establish a connection
        self.app.print_message("connection failed")

class TwistedClientApp(App):
    connection = None

    def build(self):
        root = self.setup_gui()                             # Set up the controls
        self.connect_to_server()                            # try to connect to the board
        return root
        
    def send_message(self, *args):
        msg = self.textbox.text
        if msg and self.connection:
            self.connection.write(str(self.textbox.text))
            self.textbox.text = ""

    def print_message(self, msg):
        self.label.text += msg + "\n"
        
    def callback(self,instance):
        self.print_message('Button nb <%s> pressed' % instance.text)
        self.print_message(self.Colorspinner.text)
    
    def onMatrix_Row_Slidervalue(self,instance,value):
        self.print_message('slider = <%s>' % value)
        
    def setup_gui(self):     
        self.ParentLayout = GridLayout(cols=3, row_force_default=True, row_default_height=200)
        self.label = Label(text='connecting...\n')                
          
         # Additional code to exercise, so you can adapt related code on server for example       
        Matrix_Row_Slider = Slider(min=0, max=8, value=1)
        Matrix_Row_Slider.bind(value=self.onMatrix_Row_Slidervalue)  # handy to know what are the slider's position
        
        Matrix_Col_Slider = Slider(min=0, max=8, value=1)
        Matrix_Col_Slider = Slider(orientation='vertical')        
            
        self.ParentLayout.add_widget(Matrix_Row_Slider)                
        self.Matrix_Layout = GridLayout(cols=8)
        
        # Let's add a spinner to be able to select some colors
        self.Colorspinner = Spinner(text='Choose Color', values=('Green', 'Orange', 'Red'), size_hint=(None, None),size=(90, 44), pos_hint={'center_x': .5, 'center_y': .5})
        
        # We define the main buttons matrix here        
        for i in range(64):
            btn = Button(text=str(i), size_hint_x=None,size_hint_y=None, width=20, height=20 )
            btn.bind(on_press=self.callback)
            self.Matrix_Layout.add_widget(btn)       
       
        self.ParentLayout.add_widget(self.Matrix_Layout)        
        self.ParentLayout.add_widget(self.label) 
        self.ParentLayout.add_widget(self.Colorspinner)
        self.ParentLayout.add_widget(Matrix_Col_Slider)
        return self.ParentLayout

    def connect_to_server(self):
        reactor.connectTCP('192.168.0.15', 8000, EchoFactory(self))

    def on_connection(self, connection):
        self.print_message("connected succesfully!")
        self.connection = connection


if __name__ == '__main__':
    TwistedClientApp().run()
