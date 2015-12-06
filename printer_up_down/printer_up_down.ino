/*
  move printer's z axis in one direction or other.
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin1 = 2;     // the number of the pushbutton1 pin
const int buttonPin2 = 4;


// variables will change:
int button1State = 0;         // variable for reading the pushbutton status
int button2State = 0;
int zPosition    = 0;

// min and max for z position
int minZPosition = 0;
int maxZPosition = 200;
// we will keep incremeting or decrimenting the value of z 
// so command will become "G1 Zxxx S1", not taking care of going -ve or out of range right now
//String commandString = "G1 Z"; 

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(250000);
  Serial.println("G21"); // set units in mm
  Serial.println("G28 X0 Y0 Z0"); // move to home
  Serial.println("G90"); // set absolute positioning
}

void loop() {
  // read the state of the pushbutton value:
  button1State = digitalRead(buttonPin1);
  button2State = digitalRead(buttonPin2);
  String commandString = "G1 Z"; 

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (button1State == HIGH) {
    // move z-axis in one direction
    zPosition = min(++zPosition, maxZPosition);
    commandString = commandString + String(zPosition, DEC) + " S1";
    Serial.println(commandString);
  } else if (button2State == HIGH) {
    // move z-axis in other direction
    zPosition = max(--zPosition, minZPosition);
    commandString = commandString + String(zPosition, DEC) + " S1";
    Serial.println(commandString);
  }
  delay(100); // I think my printer takes that much time to move 1 mm
}
