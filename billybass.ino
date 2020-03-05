/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent
*/

int ledPin = 9;    // LED connected to digital pin 9
int bodyPin = 8;    // body connected to digital pin 8
int mouthPin = 7;    // mouth connected to digital pin 7

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);

    if (inputString == "tailon\n");
    {
      Serial.println("moving the tail");
      digitalWrite(ledPin, HIGH);        
    }

    if (inputString == "tailflap\n");
    {
    int numFlaps = 0;
    while ( numFlaps <= 10 )
    {
    Serial.println("flapping the tail");
      digitalWrite(ledPin, HIGH);        
      delay(415);
     digitalWrite(ledPin, LOW);
      delay(415);
     numFlaps = numFlaps + 1;        
    } 
    }

    
    if (inputString == "tailoff\n")
    {
      Serial.println("stop the tail");
      digitalWrite(ledPin, LOW);
    }
    if (inputString == "bodyon\n")
    {
       Serial.println("start the body");
    analogWrite(bodyPin, 115);        
    }
    
    
    if (inputString == "bodyoff\n")
    {
      Serial.println("stop the body");
      analogWrite(bodyPin, 0);
    }

/*----------*/
    if (inputString == "mouthmove\n");
    {
     digitalWrite(ledPin, HIGH); 
    }
     if (inputString == "mouthclose\n");
    {
      digitalWrite(ledPin, LOW); 
    }
       

    
    
/*----------*/
    // clear the string:
    inputString = "";
    stringComplete = false;
    
  }

      
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
