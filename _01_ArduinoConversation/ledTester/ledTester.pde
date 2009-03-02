/* ------------------------------------------------
* Flash + Arduino LED Tester
* by Jonah Model <jmodel@parsaons.edu>
* modified from ARDUINO CONVERSATION, by beltran berrocal, b@progetto25zero1.com 
* ------------------------------------------------ */
int activeLED ;              // What LED has Flash requested we turn on? Numbers 2-9, for a total of 8 possible LEDs
int switchState = 0;        // What is the current switch state?
int lastSwitchState = 0;    // Was the switch previously on, or off?
int switchPin = 13;         // Which digital i/o pin is setup for the switch?

//----------------------------------------------------------
void setup() {
  Serial.begin(19200);  //setup serial conversation at 19200 bauds
  pinMode(switchPin, INPUT);  // sets the switch pin as input
  for (int i=2; i<=9; i++) {
      pinMode(i, OUTPUT);      // sets the digital pins 2-9 as output
  }
}

void loop () {
  
  //------------------------------------------------------------------------ SWITCH LOGIC
  // get the current state of the switch from our board
  switchState = digitalRead(switchPin);
  // if the switch has changed states, then let Flash know about it
  if (switchState != lastSwitchState) {
    if (switchState == 1){
      sendStringToFlash("switchOff");
    }
    else if (switchState == 0){
      sendStringToFlash("switchOn");
    }
  } 
  // now store the state for later comparison
  lastSwitchState = switchState;
  
  
  //------------------------------------------------------------------------ LED LOGIC
  
  // checks if a serial message has arrived to the board
   if(Serial.available() > 0) {      
          //must be a request to light up an LED   
          //activeLED should be a number 2-9, but in binary it will come in as 50-57 
          activeLED = Serial.read();
    }    
    

    
    if(activeLED >= 50 && activeLED <= 57) {
      //a valid LED signal has been received from Flash
      // convert the byte to an int - getting ready for digitalWrite()
      int outputPort = activeLED-48;
      
      Serial.print("Requesting LED port:");
      Serial.println(outputPort);
      
      if(outputPort >= 2 && outputPort <= 9) {
            // turns all the LEDs OFF
            for (int i=2; i<=10; i++) {
             digitalWrite(i,LOW); 
            }
            // then turns your selected LED ON
            digitalWrite(outputPort, HIGH);
      }
       
      
      // when we're done, default the activeLED to nothing
      activeLED = 0;
  }
  else if (activeLED) {
        Serial.print("Requesting invalid LED port:");
        Serial.println(activeLED,BYTE);
  }
 
  
  //slows down the visualization: each sentence will be emitted every .5 seconds
  delay(50);
  
}

//----------------------------------------------------------

/*send to flash
* inspired by D.Mellis printString function. it simply adds the byte(0) at the end 
* needed by the XMLSocket to know that the transmission is over.
* read the XMLSocket Actionscript Class documentation for more details
*/
void sendStringToFlash (char *s) {
	while (*s) {
	    printByte(*s++);
        }
        printByte(0); //notify the XMLSocket that the comunication is over
}
