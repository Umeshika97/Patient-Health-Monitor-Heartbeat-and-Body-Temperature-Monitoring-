#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library.
#include<LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
// Variables
const int PulseWire = 0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13; // The on-board Arduino LED, close to PIN 13.
int Threshold = 550; // Determine which Signal to "count as a beat" and which to ignore.
float temp = 0;
int blinkPin = 9; // pin to blink led at each beat( orange colourLED)
int blinkPingreen = 12; // pin to blink green for warning of low heart beat rate or warning of low temperature
int blinkPinblue = 11; // pin to blink blue for warning of high temperature
int blinkPinred = 10; // pin to blink red at warning of high heart beat rate
int fadeRate = 0; // used to fade LED on with PWM on fadePin
int var=0;
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.
 
PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
void setup() {

Serial.begin(9600); // For Serial Monitor
pinMode(blinkPin,OUTPUT); // pin that will blink to your heartbeat!
pinMode(blinkPingreen,OUTPUT); // pin to blink led for warning of low heart beat rate
pinMode(blinkPinblue,OUTPUT); // pin to blink led for warning of high temperature
pinMode(blinkPinred,OUTPUT);// pin to blink led at warning of high heart beat rate
//pinMode(blinkPinyellow,OUTPUT);// pin to blink led for warning of low temperature
lcd.begin(16,2);
 
// Configure the PulseSensor object, by assigning our variables to it.
pulseSensor.analogInput(PulseWire);
pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.
pulseSensor.setThreshold(Threshold);
 
// Double-check the "pulseSensor" object was created and "began" seeing a signal.
if (pulseSensor.begin()) {
Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.
lcd.setCursor(0,0);
lcd.print("Patient Health");
lcd.setCursor(0,1);
lcd.print("Monitor..!");

 
}
}
 
void loop() {
 while (var < 20){

int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
// "myBPM" hold this BPM value now.
if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
Serial.print("BPM: "); // Print phrase "BPM: "
Serial.println(myBPM); // Print the value inside of myBPM.
digitalWrite(blinkPin,HIGH); // turn on pin 9 LED
delay(100);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("HeartBeat Happened !"); // If test is "true", print a message "a heartbeat happened".
lcd.setCursor(0,1);
lcd.print("BPM: "); // Print phrase "BPM: "
lcd.print(myBPM);
tone(8,900,250); // pin,f,duration
delay(1000);
if ((myBPM) < 50){digitalWrite( blinkPingreen,HIGH); // turn on pin 12 LED
                  tone(8,1000,250);
                  delay(150);
                  noTone(8);     
                  Serial.println("Low heart beat rate!!!");
                  // pin to blink green for warning of low heart beat rate
                  }
if ((myBPM) > 150){digitalWrite( blinkPinred,HIGH); // turn on pin 10 LED
                  tone(8,1000,250);
                  delay(150);
                  noTone(8);
                  Serial.println("High heart beat rate!!!");
                  // pin to blink red for warning of high heart beat rate
                  }
int temp_val = analogRead(A1);
float mv = (temp_val/1024.0)*5000;
float cel = mv/10;
temp = (cel*9)/5 + 32;
Serial.print("Temperature:");
Serial.print(temp);
Serial.println("F");
lcd.setCursor(8,1);
lcd.print("T:");
lcd.setCursor(10,1);
lcd.print(temp);
lcd.setCursor(15,1);
lcd.print("F");
if ((temp) > 205){digitalWrite( blinkPinblue,HIGH); // turn on pin 11 LED
                  tone(8,1000,250);
                  delay(250);
                  noTone(8);
                  Serial.println("High body temperature!!!");
                  // pin to blink blue for warning of high temperature
                  }    
if ((temp) < 150){digitalWrite( blinkPingreen,HIGH); // turn on pin 2 LED
                  tone(8,1000,250);
                  delay(250);
                  noTone(8);
                  Serial.println("Low body temperature!!!");
                  // pin to blink yellow for warning of low temperature
                  }     
}
//var=0;
 }
digitalWrite(blinkPin,LOW); // turn off pin 9 LED
digitalWrite(blinkPingreen,LOW); // turn off pin 12 LED
digitalWrite(blinkPinred,LOW); // turn off pin 10 LED
digitalWrite(blinkPinblue,LOW); // turn off pin 11 LED

noTone(8);              
delay(2000); // considered best practice in a simple sketch.                     
}
