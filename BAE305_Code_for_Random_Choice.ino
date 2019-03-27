char *ReplyArray[12] = {
  "It is certain.", "It is decidedly so.", "Withough a doubt.", "Most likely.", "Outlook good.", "Yes.","Reply hazy, try again.", "Ask again later.", "Cannot predict now.", "Don't count on it.", "My reply is no.", "Very doubtful"
};                      // these are all the replies it should be able to give

char *ReplyChoice = ReplyArray[random(12)];
                        // just assigning "ReplyChoice" variable to be a random choice from the list in the array
void setup() {
  Serial.begin(9600);   // i still don't fully understand what this means
}

void loop() {           // eventually we'll add that it prints when the accelerometer is pushed past threshold
                        // i just focused on the random bit right now because i'm stupid
                        
Serial.println (*ReplyChoice);
delay (2000);           // delay won't stay because it'll be activated by shaking, not time. i was just trying to see if it works
}                       // it kind of doesn't? i keep getting the error "Serial port not selected." but the port option is grayed out
                        // it verifies fine. i think this code would work
                        // does it work for you guys?
