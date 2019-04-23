const int buttonPin = 1;     // pushbutton connected to pin 1
const int ledPin =  13;      // LED connected to pin 13

int button;
int oldbutton = 0;
int buttonpin = 2;
int state = 0;

void setup(){
 pinMode(buttonPin, INPUT);
 pinMode(ledPin, OUTPUT);
}
void loop()
{
 digitalRead(buttonpin);
 if(button && !oldbutton) // same as if(button == high && oldbutton == low)
 {
   //we have a new button press
   if(state == 0) // if the state is off, turn it on
   {
     //do stuff
     state = 1;
   }
   else // if the state is on, turn it off
   {
     //do stuff
     state = 0;
   }
   oldbutton = 1;
 }
 else if(!button && oldbutton) // same as if(button == low && oldbutton == high)
 {
   // the button was released
   oldbutton = 0;
 }
}
