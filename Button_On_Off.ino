const int buttonPin = 1;      // button connected to pin 1
const int displayScreen = 13; // display connected to pin 13

int button;                   // the button is variable
int oldButton = 0;            // the button's initial state is zero
int state = 0;

void setup(){
 pinMode(buttonPin, INPUT);
 pinMode(displayScreen, OUTPUT);
}
void loop()
{
 digitalRead(buttonPin);
 if(button && !oldButton)      // same as if(button == high && oldbutton == low)
 {                             // ^comment from forum I got the code from. think it means
                                   // the button used to be inactive and is now active
                                   // so the button was pushed
   if(state == 0)              // if the state was "off"
   {
     digitalWrite (13, HIGH);  // sends voltage to the screen
     state = 1;                // turns the state "on"
   }
   else                        // if the state was "on"
   {
     digitalWrite (13, LOW);   // sends no voltage to the screen
     state = 0;                // turns the state "off"
   }
   oldButton = 1;              // changes button's state from 0 to 1. becomes the "old" state
 }
 else if(!button && oldButton) // same as if(button == low && oldbutton == high)
 {                             // ^from forum. based on the if statement, think it means
                                   // the button used to be active and is now inactive
                                   // so the button was released
   oldButton = 0;              // returns the button state to its initial state
 }
}
