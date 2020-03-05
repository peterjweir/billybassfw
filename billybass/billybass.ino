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

int tailPin = 9;    // LED connected to digital pin 9
int bodyPin = 8;    // body connected to digital pin 8
int mouthPin = 7;    // mouth connected to digital pin 7
int AudioPin = A0;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

bool talkingNow = false;

int motionIntervalCounter = 0;

enum alexaStates {
  FISH_IDLE,
  FISH_THINKING,
  FISH_TALKING,
  FISH_LISTENING,
  FISH_TESTING,

};

alexaStates current_state = FISH_IDLE;
alexaStates next_state = FISH_IDLE;




void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(tailPin, OUTPUT);
  digitalWrite(tailPin, LOW);

    pinMode(bodyPin, OUTPUT);
  digitalWrite(bodyPin, LOW);

    pinMode(mouthPin, OUTPUT);
  digitalWrite(mouthPin, LOW);
}


void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    handleCommands();
    
  }

  executeState();
  handleMouth();

  delay(1);
  
}

void handleCommands(){
    if (inputString == "IDLE")
    {
       next_state = FISH_IDLE;
    }

    if (inputString == "THINKING")
    {
       next_state = FISH_THINKING;
    }

    if (inputString == "TALKING")
    {
       next_state = FISH_TALKING;
    }

    if (inputString == "LISTENING")
    {
       next_state = FISH_LISTENING;
    }

    if (inputString == "TESTING")
    {
       next_state = FISH_TESTING;
    }

    
    
    if (inputString == "tailon\n")
    {
      Serial.println("moving the tail");
      digitalWrite(tailPin, HIGH);        
    }

    if (inputString == "tailflap\n")
    {
      int numFlaps = 0;
      while ( numFlaps <= 10 )
      {
        Serial.println("flapping the tail");
        digitalWrite(tailPin, HIGH);        
        delay(415);
        digitalWrite(tailPin, LOW);
        delay(415);
        numFlaps = numFlaps + 1;        
      } 
    }

    
    if (inputString == "tailoff\n")
    {
      Serial.println("stop the tail");
      digitalWrite(tailPin, LOW);
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
     digitalWrite(mouthPin, HIGH); 
    }
     if (inputString == "mouthclose\n");
    {
      digitalWrite(mouthPin, LOW); 
    }
       

    
    
/*----------*/
    // clear the string:
    inputString = "";
    stringComplete = false;


}

void handleMouth() {
  if (talkingNow == true)
  {
    int sensorVal = analogRead(AudioPin);
    sensorVal = map(sensorVal,0,512,0,180);
    if (sensorVal > 10)
    {
      digitalWrite(mouthPin, HIGH);
    }
    else 
    {
      digitalWrite(mouthPin, LOW);
    }
  }
  else
  {
    digitalWrite(mouthPin, LOW);
  }
}


void executeState() {
  

  if (next_state != current_state)
  {
    motionIntervalCounter = 0;
    current_state = next_state;
  }

  switch(current_state){

    case FISH_TALKING:
      //we can flap the tail here, but for now we'll just stick it out.
      digitalWrite(tailPin, LOW);
      digitalWrite(bodyPin, HIGH);
      talkingNow = true;
      break;
      
    case FISH_LISTENING:
      //we can flap the tail here, but for now we'll just stick it out.
      digitalWrite(tailPin, LOW);
      digitalWrite(bodyPin, HIGH);
      talkingNow = false;
      break;

    case FISH_THINKING:
      //we can flap the tail here, but for now we'll just stick it out.
      digitalWrite(tailPin, HIGH);
      digitalWrite(bodyPin, LOW);
      talkingNow = false;
      break;
    case FISH_TESTING:
      //don't alter any pin states here, so we can run the manual commands like tail flap
      break;
     
    case FISH_IDLE:
    default:
      talkingNow = false;
      digitalWrite(tailPin, LOW);
      digitalWrite(bodyPin, LOW);
      break;

  
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
