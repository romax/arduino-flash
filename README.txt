----------------------------------------------------------------------
                   Simple Serial Communication
                    An Intro to Flash+Arduino                    
----------------------------------------------------------------------
by Jonah Model <jmodel@parsons.edu>


Goals
----------------------------------------------------------------------

a) translate physical switches into "digital leds" in a Flash movie
b) allow a Flash button to control real LEDs off the board


Synopsis
----------------------------------------------------------------------

This demo extends and simplifies Beltran Berrocal's Flash samples for Arduino. The original build uses serial data to send sentences back and forth between computer and board, forming a fully automatic conversation. You can also configure the Flash app to send arbitrary messages to Arduino. Beltran's work can be found here: http://www.progetto25zero1.com/b/tools/Arduino/

Rather than send a full conversation, we will be sending simple on/off messages. The FlashLEDs app can trigger any 1 of 8 total LEDs on a breadboard, while a physical switch on the breadboard will change the state of a virtual toggle switch in Flash. It's easier to understand using visuals. Please take a look at the Images folder contained here to get a quick preview.


Components
----------------------------------------------------------------------

a. Arduino Sketch
		-  Receives LED light-up requests
		-  Turns button triggers from the board into serial data
	
b. SerialProxy (socket server)
		- Handles send & receive data between Arduino and Flash
		- The translator program, establishes a listening socket that both interfaces can bind to
	
c. Flash App 
		- Lets you activate a breadboard LED by clicking on one of the 8 LED movieclips
		- Shows you the status of the physical toggle switch by changing the state of a movieclip
	
d. Flash Class
		- Wraps around the Flash XMLSocket class
		- Provides debugging information and a clean object to load into your app
		- Doesn't really do much (you could use XMLSocket directly, if you prefer, or modify it for custom use)
	


Warnings / Notes
----------------------------------------------------------------------

1. Don't use either port 0 RX or 1 TX for digital i/o, they are needed for serial comm

2. When uploading, your serial tester in Arduino software should ideally be closed. This avoids conflicting usage of the serial port. If possible, do not open the tester or try sending data again until 15 seconds later, or when the the AREF LED lights up
	
3. Use the CU (not TTY) for serial communication. It's more reliable and won't crash your computer (see #4)

4. Occasionally closing the SerialProxy while it's in the middle of sending data, this will crash your computer (possibly just Macs) - save all files before starting to test

5. You will need to modify the serproxy.cfg file for your individual use - the Mac version is configured but needs to be setup for use with your unique Arduino board


Parts List
----------------------------------------------------------------------

1. 9 LEDs  

2. 8 220-ohm resistors (for the LEDs)

3. 1 momentary switch or maintained switch

4. 1 10K-ohm resistor (for the switch)

5. wires, and whatever else you want to test out