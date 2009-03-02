#include "WProgram.h"
void readSerialString(char *strArray);
void printSerialString(char *strArray);
boolean isStringEmpty(char *strArray);
void sendStringToFlash(char *s);
void ArduinoConversation(int i);
/* ------------------------------------------------
* ARDUINO CONVERSATION
* by beltran berrocal, b@progetto25zero1.com
*
* This program is the most useless program ever ;-) 
* it just establishes a "conversation" between Flash and Arduino. 
* Please upload and run the program once, before reading the code..it'll be funnier ;-)
* for the flash part grab the example on www.progetto25zero1.com/b/tools/Arduino
*
* It will teach you how to send, receive and handle long strings or other data to and from Flash.
* it requires the serialProxy, which is basically an XMLSocket server, a small program that runs
* on your pc and keeps a live connection between the serial port and Flash.
* The serial proxy is developed by Stefano Busti(1999) and David A. Mellis(2005) and can be found
* either on the arduino site (www.arduino.cc) or attached to this example 
* www.progetto25zero1.com/b/tools/Arduino
* 
* it has a usefull reusable function to send strings to flash
* sendStringToFlash - which is basically the same as printString but it adds at the end 
* a byte(0) to inform the XMLSocket that the communication is over 
* (read the flash documentation on the XMLSocket class to better understand what this means)
* 
*
* created 30 Decembre 2005;
* copyleft 2005 Progetto25zero1  <http://www.progetto25zero1.com>
*
* --------------------------------------------------- */

char serInString[100];  // array that will hold the different bytes of the string. 100=100characters;
                        // -> you must state how long the array will be else it won't work properly
int sentenceNum = 0;    //tracks the sentences sent to flash in order to answer properly


//---------------------------------------------------------
// read (and print back) full strings from the serial port
// for more info www.progetto2501.com/b/tools/Arduino
//----------------------------------------------------------
void readSerialString (char *strArray) {
    int i = 0;
    if(serialAvailable()) {    
       while (serialAvailable()){            
          strArray[i] = serialRead();
          i++;
       }
    }      
}

void printSerialString(char *strArray) {
     int i=0;
     if (strArray[i] != 0) {     
         while(strArray[i] != 0) {
            serialWrite( strArray[i] );
            strArray[i] = 0;                  // optional: flush the content
            i++;          
         }
     }
} 

//utility function to know wither an array is empty or not
boolean isStringEmpty(char *strArray) {
     if (strArray[0] == 0) {
         return true;
     } else {
         return false;
     }
}
//----------------------------------------------------------


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

/* this is the core of the Arduino conversation
* I had to implement a function because there is no way to store long strings by default
* in an array and output them out accessing them with an index
* this function is a mix between an array and a function: provide an index as parameter
* and it will print out a string "recorded at that index"
*/
void ArduinoConversation(int i) {
  if(i==0)        {sendStringToFlash("Arduino: Mamma mia Flash, Yes I can hear yu!");
  } else if(i==1) {sendStringToFlash("Arduino: well, let's go have a BIRRA together, wat do yu tink?");
  } else if(i==2) {sendStringToFlash("Arduino: don't worry! it'll just make my pins go analog analog ;-)");
  } else if(i==3) {sendStringToFlash("Arduino: glu glu glu! your turn now dude, insted of just lurking... ask me something!");
  } else if(i>=4)  {
      printString("Arduino: unfortunately for you my master is smart as one of my digital pins ;-) ,");
      printString(" which means that I don't have an answer for that yet!");
      printString(" I'll ask babbo 'touring' natale to give me a neural network for handeling natural speaking next time");
      printByte(0); //end of communications in XMLSocket
  }
}

//----------------------------------------------------------



void setup() {
  beginSerial(19200);  //setup serial conversation at 9600 bauds
}


void loop () {
  //try to read the serial port and create a string out of what you read
  readSerialString(serInString);
  
  // prints the sentence only if Flash actually said something
  if( isStringEmpty(serInString) == false) {
  
      //first send feedback to flash that it's sentence has been heard
      printString("Arduino heard you saying: ");
      printSerialString(serInString);
            
      //optional: separate confirmation and reply in two different serial strings
      //by passing a byte(0) that informs the XMLSocket that the comunication is over
       printByte(0);
      
      //now answer to Flash continuing the conversation, sending the appropriate reply
      ArduinoConversation( sentenceNum );
      
      //update the conversation index so that it will answer the next sentence
      //you will have to reset the board by hand if you will want to re-sincronize the board
      sentenceNum++;
  }
  
  //slows down the visualization: each sentence will be emitted every 2 seconds
  delay(2000);
  
}
