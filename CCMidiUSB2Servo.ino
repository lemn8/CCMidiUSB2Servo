/*
 * CCMidiUSB2Servo.ino
 * Board: Arduino Leonardo 
 * Created: 18/March/2023 19:20
 * Author: Lemn8.com
 * Inspired by: @onehackerband (youtube)
*/

#include "MIDIUSB.h"
#include "Servo.h"

//---Make up some for you easy to remember servo labels/names. I call the first one servo1 because
//---its connected to pin 1. I will create 3 for you.
Servo servo1;
Servo servo2;
Servo servo3;

//---Dont touch this is just to label the midi-info output.
midiEventPacket_t l8;

//--- Define on which pin you connect a led. You can also use to connect it to a servo output then
//--- the brightness will change! And you can connect more then one.
int led0 = 0;

//--- Label the pins. i call the first one servo1pin because servo1 is going to be connected blablabla...
int servo1Pin = 1;
int servo2Pin = 2;
int servo3Pin = 3;

void setup() {
  pinMode(led0, OUTPUT);  //---To set this pin to output only.

  //--- Connect each servo to a pin and define a starting angle. They're now on 0 Degrees. (BEWARE!!!
  //--- Decouple all the mechanical attachments from the servo because it could break your animatronic!)
  servo1.attach(servo1Pin);
  servo1.write(0);
  servo2.attach(servo2Pin);
  servo2.write(0);
  servo3.attach(servo3Pin);
  servo3.write(0);
}

void loop() {
  l8 = MidiUSB.read();

  //--- This part wil make your LED blink when receiving info.
  if (l8.header != 0) {
    digitalWrite(led0, HIGH);
    delay(10);
    digitalWrite(led0, LOW);

    //--- See it as some labeled temporary memory banks that can be read
    //--- later easily by just calling the labels.
    byte poep, kak;

    poep = l8.byte2;  //--- Midi-Note
    kak = l8.byte3;   //--- Value (0 - 127 which will be translated into Servo-Angle)

    //--- This defines which note each servo needs to listen to. BEWARE!!! Too much midi-sliders-input will result into
    //--- slow movements and sync problems, because of the amount of data you send. Thats why i present you 2 different methods.

    //--- Method 1: Connect servo1 to midi-slider on CC channel/tone 5 and read slide/rotation knob values (a lot of midi data!)
    if (poep == 5) {
      servo1.write(kak);
    }

    //--- Method 2: when i press piano button 6 it will set servo2 to an 90 degrees angle and when i press button 7 too 100 degrees.
    //--- This method will have less midi-data-traffic. This can me used for mouth and eyes. make a few for closed, open and less open or more.
    if (poep == 6) {
      servo2.write(90);
    }
    if (poep == 7) {
      servo2.write(100);
    }

    if (poep == 15) {
      servo3.write(kak);
    }

    //--- This is a handy tool for you. If you dont know what kind of specific data is send bij your midi controller
    //--- Then this part will make it show up on the "Serial Monitor". Move your midi sliders and check the feedback!
    Serial.print(l8.byte2);
    Serial.print("-");
    Serial.println(l8.byte3);
  }
}
//--- If you liked the code please give me some credit, it took me a while to figure out because i have no programming skills, just trial and error!
