#include <Key.h>
#include <Keypad.h>
#include <Servo.h>
int servoPin = 5;
int LED = 9;
int LDR = A0;
// Create a servo object
Servo Servo1;

// Listing 9-1
// Beginning of necessary code
#include "Keypad.h"
char* secretCode = "123A";
int position = 0;

const byte ROWS = 4; // set display to four rows
const byte COLS = 4; // set display to three columns
char keys[ROWS][COLS] =
{{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
 {'*','0','#','D'}};
 //byte rowPins[ROWS] = {5, 4, 3, 2};
 //byte colPins[COLS] = {8, 7, 6, 9};
 byte rowPins[ROWS] = {A1, A2, A3, A4};
 byte colPins[COLS] = { A5, 4, 3, 2};

 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 // End of necessary code
int redPin = 10;
int greenPin = 11;
 
void setup()
{
Serial.begin(9600);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
setLocked(true);
Servo1.attach(servoPin);
pinMode(LED, OUTPUT);
pinMode(LDR, INPUT);
}
void loop()
{
char key = keypad.getKey();
//dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
int LDRValue = analogRead(LDR);
//Serial.print("sensor = ");
//Serial.print(LDRValue);
if (LDRValue <=700) 
{
digitalWrite(LED, HIGH);
//Serial.println("It's Dark Outside; Lights status: ON");
}
else 
{
digitalWrite(LED, LOW);
//Serial.println("It's Bright Outside; Lights status: OFF");
}


//ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
if (key != NO_KEY)
{
Serial.print(key);
}
if (key == '*' || key == '#')
{
position = 0;
setLocked(true);
}
if (key == secretCode[position])
{
position ++;
}
if (position == 4)
{
setLocked(false);
}
delay(100);
}
void setLocked(int locked)
{
if (locked)
{
digitalWrite(redPin, HIGH);
digitalWrite(greenPin, LOW);
Servo1.write(0);
delay(1000);

}
else
{
digitalWrite(redPin, LOW);
digitalWrite(greenPin, HIGH);
Servo1.write(90);
delay(1000);




}
}
