char *ReplyArray[13] = {
  "It is certain.", "It is decidedly so.", "Withough a doubt.", "Most likely.", "Outlook good.", "Yes.","Reply hazy, try again.", "Ask again later.", "Cannot predict now.", "Don't count on it.", "My reply is no.", "Very doubtful", "Ask Dr. Dvorak"
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
