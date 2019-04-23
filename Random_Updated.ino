char *ReplyArray[12] = {
  "Yes! For sure", "Nope. Never", "Maybe?", "Stop shaking me", "Would you ask a paper fortune teller that?", "Oh definitely not", "Abso-freaking-lutely", "I'm not sure, but I believe in you!", "You should have learned that in EE305", "Ask Dr. Dvorak", "Ask Toby-I mean Robbie", "6d 61 64 65 20 79 6f 75 20 6c 6f 6f 6b 20 68 61 68 61"
};                      //the array of possible replies
const int ACC = A1;     //the accelerometer is connected to pin A1
float threshold = 700;  //threshold the sensor must surpass to activate reply

void setup() {
  Serial.begin(9600);
}

void loop() {

float sensorValueAccelerometer = analogRead(A1); //naming a variable for what the sensor is reading
Serial.println (sensorValueAccelerometer);       //printing what the sensor is reading
String Reply = ReplyArray[random(12)];           //assigning "Reply" variable to be random choice from array
if (sensorValueAccelerometer > threshold){
  Serial.println (Reply);                        //printing "Reply" if sensor reads beyond threshold
}
delay (1000);                                    //delay for testing
}
