#include <IRremote.h>
#include <LiquidCrystal.h>

//beep
int buzz_pin = 13;

// Motor Pins
const int leftMotorFWD = 30;
const int rightMotorFWD = 32;

const int proxBuzzer = 13;

// Sensor Pins
const int trigpin_OT = 46;
const int echopin_IN = 48;

// Turning Variables
int rightAngleTime = 0;
int twoseventydegreeTime = rightAngleTime * 3;
int fwdTime = 0; 

// System States
bool ultraSensor = false;
bool elevator_button = false; 
bool ecebElevator = false;

//########################

int distance, cm;
//############################

// ##### Bool Logic #####
bool bool_state;
int distance_to_detect = 16;  //in cm 
// ##########################

// // ##### multi tasking timer logic ####
unsigned long starting_time = 0;
int delay_int = 50;
unsigned long delay_time = delay_int; 
unsigned long current_time = 0;

// Variables for the non-blocking LCD animation
unsigned long previousLcdTime = 0;
int currentFrame = 1;
unsigned long frameDuration = 0; // Starts at 0 to draw the first frame immediately
//######### Remote vars ##########
//ALL the numbers E718FF00 number 2, A15EFF00 - #3, F708FF00 - #4, E31CFF00 - #5, A55AFF00 - #6, BD42FF00 - #7, AD52FF00 - #8, B54AFF00 - #9
// Playback BB44FF00, Play forword BC43FF00, Arrow with equals BF40FF00, read power button BA45FF00

int reciver_pin = 7;

unsigned long remotevalue = 0;

//#############################
//LCD Display

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte backSlash[8] = {
  B00000, B10000, B01000, B00100, B00010, B00001, B00000, B00000
};
byte forwardSlash[8] = {
  B00000, B00001, B00010, B00100, B01000, B10000, B00000, B00000
};
byte heart[8] = {
  B00000, B01010, B11111, B11111, B01110, B00100, B00000, B00000
};

//############################

// ### Bool Logic ###
  struct{
    int nodesConnected[3];
    int node0Dist;
    int node1Dist;
    int node2Dist;
    int node0Deg; //make 0-3
    int node1Deg;
    int node2Deg;
    ;
  } node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12, node13, node14, node15, node16, node17, node18;

//  #### Room logic ######
int room_number;

//##########################

void initializeNodes() {
//node 1
    node1.nodesConnected[0] = 2; node1.nodesConnected[1] = 0; node1.nodesConnected[2] = 0; 
    node1.node0Dist = 1500;
    node1.node0Deg = 2; //make 1-3
  
    //node 2
    node2.nodesConnected[0] = 1; node2.nodesConnected[1] = 3; node2.nodesConnected[2] = 0; 
    node2.node0Dist = 1500;
    node2.node0Deg = 2; //make 1-3
    node2.node1Dist = 1500;
    node2.node1Deg = 0; //make 1-3
  
    //node 3
    node3.nodesConnected[0] = 2; node3.nodesConnected[1] = 4; node3.nodesConnected[2] = 0; 
    node3.node0Dist = 1500;
    node3.node0Deg = 0; //make 1-3
    node3.node1Dist = 730;
    node3.node1Deg = 2; //make 1-3
  
    //node 5
    node5.nodesConnected[0] = 4; node5.nodesConnected[1] = 6; node5.nodesConnected[2] = 0; 
    node5.node0Dist = 650;
    node5.node0Deg = 0; //make 1-3
    node5.node1Dist = 1470;
    node5.node1Deg = 3; //make 1-3
  
    //node 6 (Fixed typo: was written as node5)
    node6.nodesConnected[0] = 5; node6.nodesConnected[1] = 7; node6.nodesConnected[2] = 0; 
    node6.node0Dist = 1470;
    node6.node0Deg = 1; //make 1-3
    node6.node1Dist = 310;
    node6.node1Deg = 3; //make 1-3

    //node 7
    node7.nodesConnected[0] = 6; node7.nodesConnected[1] = 8; node7.nodesConnected[2] = 0; 
    node7.node0Dist = 310;
    node7.node0Deg = 1; //make 1-3
    node7.node1Dist = 730;
    node7.node1Deg = 3; //make 1-3
  
    //node 8
    node8.nodesConnected[0] = 6; node8.nodesConnected[1] = 8; node8.nodesConnected[2] = 0; 
    node8.node0Dist = 730;
    node8.node0Deg = 1; //make 1-3
    node8.node1Dist = 730;
    node8.node1Deg = 3; //make 1-3

    //node 13
    node13.nodesConnected[0] = 9; node13.nodesConnected[1] = 14; node13.nodesConnected[2] = 0; 
    node13.node0Dist = 60;
    node13.node0Deg = 2; //make 1-3
    node13.node1Dist = (750 + 710 + 500) - 144;
    node13.node1Deg = 3; //make 1-3
  
    //node 10
    node10.nodesConnected[0] = 9; node10.nodesConnected[1] = 11; node10.nodesConnected[2] = 0; 
    node10.node0Dist = 750 + 750 + 750 + 160;
    node10.node0Deg = 1; //make 1-3
    node10.node1Dist = 750;
    node10.node1Deg = 3; //make 1-3

    //node 11
    node11.nodesConnected[0] = 10; node11.nodesConnected[1] = 12; node11.nodesConnected[2] = 0; 
    node11.node0Dist = 750;
    node11.node0Deg = 1; //make 1-3
    node11.node1Dist = 710 + 500;
    node11.node1Deg = 3; //make 1-3
  
    //node 12
    node12.nodesConnected[0] = 11; node12.nodesConnected[1] = 15; node12.nodesConnected[2] = 0; 
    node12.node0Dist = 500 + 710;
    node12.node0Deg = 1; //make 1-3
    node12.node1Dist = 750 + 750 + 750 + 722;
    node12.node1Deg = 0; //make 1-3
  
    //node 16
    node16.nodesConnected[0] = 15; node16.nodesConnected[1] = 17; node16.nodesConnected[2] = 0; 
    node16.node0Dist = 270;
    node16.node0Deg = 2; //make 1-3
    node16.node1Dist = 270 + 750 + 750 + 500;
    node16.node1Deg = 0; //make 1-3
  
    //node 17
    node17.nodesConnected[0] = 16; node17.nodesConnected[1] = 18; node17.nodesConnected[2] = 0; 
    node17.node0Dist = 270 + 750 + 750 + 500;
    node17.node0Deg = 2; //make 1-3
    node17.node1Dist = 250 + 540;
    node17.node1Deg = 0; //make 1-3
  
    //node 18
    node18.nodesConnected[0] = 17; node18.nodesConnected[1] = 0; node18.nodesConnected[2] = 0; 
    node18.node0Dist = 250 + 540;
    node18.node0Deg = 2; //make 1-3
  
    //node 9
    node9.nodesConnected[0] = 8; node9.nodesConnected[1] = 10; node9.nodesConnected[2] = 13; 
    node9.node0Dist = 730;
    node9.node0Deg = 1; //make 1-3
    node9.node1Dist = 750 + 750 + 750 + 160;
    node9.node1Deg = 2; //make 1-3
    node9.node2Dist = 60;
    node9.node2Deg = 0; //make 1-3
  
    //node 15
    node15.nodesConnected[0] = 14; node15.nodesConnected[1] = 12; node15.nodesConnected[2] = 16; 
    node15.node0Dist = 144;
    node15.node0Deg = 1; //make 1-3
    node15.node1Dist = 750 + 750 + 750 + 722;
    node15.node1Deg = 2; //make 1-3
    node15.node2Dist = 270;
    node15.node2Deg = 0; //make 1-3
}

int currentNode = 7;      
int targetNode = 0;       
int currentHeading = 0;


void setup() {


    lcd.begin(16, 2);
  lcd.createChar(0, backSlash);
  lcd.createChar(1, forwardSlash);
  lcd.createChar(2, heart);

pinMode(proxBuzzer, OUTPUT);


Serial.begin(9600); // set up the monitor FIRST
  delay(200);
  starting_time = millis(); //set a time at the begining of arduing
  //remote setup
  IrReceiver.begin(reciver_pin);
  Serial.println("IR Receiver Enabled");  // activate the reciver
  
  // setting the modes high/low of the ultra sensor pin
  sensorsetup();

// Motor Functions
pinMode(leftMotorFWD, OUTPUT);
pinMode(rightMotorFWD, OUTPUT);

initializeNodes();

}

void loop() {
  updateLCD();

  // 1. Ultrasonic Sensor Logic
  current_time = millis(); 

  if (current_time - starting_time >= delay_time) {
    distance = sensorfunction(trigpin_OT, echopin_IN);
    cm = convert_to_cm(distance);
    bool_state = detect_object(cm);
    
    print_info(cm);
    remote_print_info(); 
    starting_time = current_time;
  }
  
  // 2. Read the Remote and Assign Target
  room_number = remote_function();
  if (room_number > 0) {
      targetNode = room_number; 
      Serial.print("New Destination Set: Room ");
      Serial.println(targetNode);
  }

  // 3. Movement Logic
  if (bool_state == true) {
      stopBlock(); // Object detected
  } 
  else { 
      // If we have a destination and haven't arrived yet...
      if (targetNode > 0 && currentNode != targetNode) {
          
          // Use our new GPS function to find the immediate next step
          int nextStep = getNextNodeOnPath(currentNode, targetNode);
          
          // Use our new Driving function to physically move there
          if (nextStep != 0) {
              executeNodeTransfer(currentNode, nextStep);
          }

          // Check if we arrived
          if (currentNode == targetNode) {
              Serial.println("Arrived at Destination!");
              targetNode = 0; 
              stopBlock();    
          }
      }
  }
}



// ###### remote functions #########
int remote_function () {
  if (IrReceiver.decode()) {
    // If a button is pressed and it's NOT just being held down
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
      remotevalue = IrReceiver.decodedIRData.decodedRawData;
      // do buz
      beep();
      IrReceiver.resume(); // Reset receiver for the next signal immediately
      
      switch (remotevalue) {
        case 0xF30CFF00: return 1;
        case 0xE718FF00: return 2;
        case 0xA15EFF00: return 3;
        case 0xF708FF00: return 4;
        case 0xE31CFF00: return 5;
        case 0xA55AFF00: return 6;
      }
    }
    IrReceiver.resume(); // Catch-all to reset receiver if it was a repeat flag
  } else {
    // IF NO BUTTON IS PRESSED: Clear the global variable
    remotevalue = 0; 
  }
  
  return 0; // Return 0 if nothing happened
}

void remote_print_info()
{ 
  Serial.print(" Remote: "); 

  if (remotevalue == 0) 
  {
    Serial.print("None");
  }
  else
  {
    Serial.print(remotevalue, HEX);
  }
  Serial.println(); //make new line
};



//  ############# logic ###############
bool detect_object(int cm) 
{
  // if see object
  if (cm >= 0 && cm < distance_to_detect) 
  { 
    Serial.print("STOPED: ");
    Serial.print("True");
    Serial.print(" | ");
    return true;
  } 
  else
  {
    // if further than the distance do nothing
    Serial.print("STOPED: ");
    Serial.print("False");
    Serial.print(" | ");
    return false; 

  }

};

void print_logic(bool bool_state)  //might not be use anymore
{
  Serial.print("STOPED: ");
  Serial.print(bool_state);
  delay(200);  //might cause problems
  
}

//###################################

//#### converstions funcitons ########
void print_info(int cm) 
{
  Serial.print("CM: ");
  Serial.print(cm);
  Serial.print(" | ");
};

int convert_to_cm(int distance) {return (distance / 29) /2;};

//####################################

 // ########### sensor funcitons ################

void sensorsetup() 
{
  pinMode(trigpin_OT, OUTPUT);
  pinMode(echopin_IN, INPUT);
};

// get the time in ms and converst 
long sensorfunction(int trigpin_OT, int echopin_IT) 
{
 
  // want the sensor to first begin off
  // then shoot a pulse from the trig pin 
  // after waits
  // then get the input / distance it was recived using pulse in
  // then conver the pulse in to the uniters
  // turn off an repeate

  digitalWrite(trigpin_OT, LOW);  // turn off the pin first
  delayMicroseconds(2); // short_ delay

  digitalWrite(trigpin_OT, HIGH); // send the signal
  delayMicroseconds(10);
  digitalWrite(trigpin_OT, LOW); // turn off


  // get the trig pin infomation
  // when the echopin goes hight it recived the signal from trigpin im 'mili seconds'
  return pulseIn(echopin_IN, HIGH, 30000);

};



void turnToHeading(int targetDeg) {
    if (currentHeading == targetDeg) {
        return; 
    }

    int diff = (targetDeg - currentHeading + 4) % 4;

    if (diff == 1) {
        rightTurnBlock();
    } 
    else if (diff == 2) {
        backwardBlock();
    } 
    else if (diff == 3) {
        leftTurnBlock();
    }
    currentHeading = targetDeg;
}




void enterElevator(){
  //I hate my life
    if (elevator_button == true){
      forwardBlock();

      //hexadecimal value for elevator function

      backwardBlock();
    }
    else{
      delay(100);
    }

}

void exitElevator(){
  //I love my life
    if (elevator_button == true){
      forwardBlock();
    }
    else{
      delay(100);
    }
}

void stopBlock(){
    digitalWrite(rightMotorFWD, LOW);
    digitalWrite(leftMotorFWD, LOW);
}

void leftTurnBlock(){
    digitalWrite(rightMotorFWD, HIGH);
    delay(rightAngleTime);
    digitalWrite(rightMotorFWD, LOW);
}

void rightTurnBlock(){
    digitalWrite(leftMotorFWD, HIGH);
    delay(rightAngleTime);
    digitalWrite(leftMotorFWD, LOW);
}

void forwardBlock(){
    digitalWrite(rightMotorFWD, HIGH);
    digitalWrite(leftMotorFWD, HIGH);
    delay(fwdTime);
    digitalWrite(rightMotorFWD, LOW);
    digitalWrite(leftMotorFWD, LOW);
}

void backwardBlock(){
    digitalWrite(leftMotorFWD, HIGH);
    digitalWrite(rightMotorFWD, LOW);
    delay(twoseventydegreeTime);
    digitalWrite(leftMotorFWD, LOW);
    digitalWrite(rightMotorFWD, HIGH);
    delay(rightAngleTime);

}

void updateLCD() {
  unsigned long currentMillis = millis();

  // If the required time for the current frame has passed, draw the next one
  if (currentMillis - previousLcdTime >= frameDuration) {
    previousLcdTime = currentMillis; // Reset the stopwatch
    lcd.clear();

    switch(currentFrame) {
      case 1:
        lcd.setCursor(4, 0); lcd.print("(O    O)"); 
        lcd.setCursor(6, 1); lcd.print("____");
        frameDuration = 1500; 
        currentFrame = 2; // Queue up the next frame
        break;
      case 2:
        lcd.setCursor(4, 0); lcd.print("(-    -)"); 
        lcd.setCursor(6, 1); lcd.print("____");
        frameDuration = 200;
        currentFrame = 3;
        break;
      case 3:
        lcd.setCursor(4, 0); lcd.print("(^    ^)"); 
        lcd.setCursor(6, 1); lcd.write(byte(0)); 
        lcd.print("__");     lcd.write(byte(1));
        frameDuration = 2000;
        currentFrame = 4;
        break;
      case 4:
        lcd.setCursor(4, 0); lcd.print("(>    <)"); 
        lcd.setCursor(6, 1); lcd.write(byte(0)); 
        lcd.print("____");   lcd.write(byte(1));
        frameDuration = 2000;
        currentFrame = 5;
        break;
      case 5:
        lcd.setCursor(3, 0); lcd.print("(-  ");
        lcd.write(byte(2));  lcd.print("  -)");
        lcd.setCursor(7, 1); lcd.print("ww");
        frameDuration = 1500;
        currentFrame = 1; // Loop back to the beginning
        break;
    }
  }
}
// ==========================================
// ANCILLARY NAVIGATION ENGINE
// ==========================================

// 1. The "GPS" Algorithm
// Calculates the shortest path through your graph, handling the branches at 9 and 15
int getNextNodeOnPath(int current, int target) {
    if (current == target) return 0;

    // RULE 1: Moving towards the start of the hallway (Nodes 1-8)
    if (target <= 8) {
        if (current > 8 && current != 9) { // Funnel everything back to Junction 9
            if (current == 10 || current == 13) return 9;
            if (current == 11) return 10;
            if (current == 12) return 11;
            if (current == 14) return 13;
            if (current >= 15) return 14; 
        }
        if (current == 9) return 8;
        if (current > target) return current - 1; // Drive down
        if (current < target) return current + 1; // Drive up
    }

    // RULE 2: Moving towards the end of the hallway (Nodes 16-18)
    if (target >= 16) {
        if (current < 15) { // Funnel everything to Junction 15
            if (current <= 8) return current + 1;
            if (current == 9) return 13; // Take the bottom path (13) by default
            if (current == 10) return 11;
            if (current == 11) return 12;
            if (current == 12) return 15;
            if (current == 13) return 14;
            if (current == 14) return 15;
        }
        if (current == 15) return 16;
        if (current < target) return current + 1;
        if (current > target) return current - 1;
    }

    // RULE 3: Navigating within the split paths (Nodes 9 to 15)
    if (target >= 9 && target <= 15) {
        if (current < 9) return current + 1; // Below 9, drive up
        if (current > 15) return current - 1; // Above 15, drive down

        // Junction 9 Logic
        if (current == 9) {
            if (target == 10 || target == 11 || target == 12) return 10; // Top Path
            if (target == 13 || target == 14 || target == 15) return 13; // Bottom Path
        }
        // Junction 15 Logic
        if (current == 15) {
            if (target == 12 || target == 11 || target == 10) return 12; // Top Path Reverse
            if (target == 14 || target == 13 || target == 9) return 14; // Bottom Path Reverse
        }

        // Inside Top Path (10, 11, 12)
        if (current >= 10 && current <= 12) {
            if (target >= 10 && target <= 12) {
                if (current < target) return current + 1;
                if (current > target) return current - 1;
            }
            if (target == 9) return current - 1; 
            if (target == 15 || target == 13 || target == 14) return current + 1; 
        }

        // Inside Bottom Path (13, 14)
        if (current == 13 || current == 14) {
            if (target == 14 && current == 13) return 14;
            if (target == 13 && current == 14) return 13;
            if (target == 9) return current - 1; 
            if (target == 15 || target == 10 || target == 11 || target == 12) return current + 1; 
        }
    }
    return 0; // Failsafe
}

// 2. The Physical Driver Function
// Connects the math algorithm to your pre-existing physical struct data
void executeNodeTransfer(int current, int next) {
    switch(current) {
        case 1:
            if (next == 2) { turnToHeading(node1.node0Deg); fwdTime = node1.node0Dist; }
            break;
        case 2:
            if (next == 1) { turnToHeading(node2.node0Deg); fwdTime = node2.node0Dist; }
            if (next == 3) { turnToHeading(node2.node1Deg); fwdTime = node2.node1Dist; }
            break;
        case 3:
            if (next == 2) { turnToHeading(node3.node0Deg); fwdTime = node3.node0Dist; }
            if (next == 4) { turnToHeading(node3.node1Deg); fwdTime = node3.node1Dist; }
            break;
        case 4:
            // Placeholder: Node 4 was missing from initializeNodes(), assuming basic routing
            fwdTime = 700; // Default generic forward time
            break; 
        case 5:
            if (next == 4) { turnToHeading(node5.node0Deg); fwdTime = node5.node0Dist; }
            if (next == 6) { turnToHeading(node5.node1Deg); fwdTime = node5.node1Dist; }
            break;
        case 6:
            if (next == 5) { turnToHeading(node6.node0Deg); fwdTime = node6.node0Dist; }
            if (next == 7) { turnToHeading(node6.node1Deg); fwdTime = node6.node1Dist; }
            break;
        case 7:
            if (next == 6) { turnToHeading(node7.node0Deg); fwdTime = node7.node0Dist; }
            if (next == 8) { turnToHeading(node7.node1Deg); fwdTime = node7.node1Dist; }
            break;
        case 8:
            if (next == 6) { turnToHeading(node8.node0Deg); fwdTime = node8.node0Dist; }
            if (next == 9) { turnToHeading(node8.node1Deg); fwdTime = node8.node1Dist; } // Corrected typo in your init
            break;
        case 9:
            if (next == 8) { turnToHeading(node9.node0Deg); fwdTime = node9.node0Dist; }
            if (next == 10){ turnToHeading(node9.node1Deg); fwdTime = node9.node1Dist; }
            if (next == 13){ turnToHeading(node9.node2Deg); fwdTime = node9.node2Dist; }
            break;
        case 10:
            if (next == 9) { turnToHeading(node10.node0Deg); fwdTime = node10.node0Dist; }
            if (next == 11){ turnToHeading(node10.node1Deg); fwdTime = node10.node1Dist; }
            break;
        case 11:
            if (next == 10){ turnToHeading(node11.node0Deg); fwdTime = node11.node0Dist; }
            if (next == 12){ turnToHeading(node11.node1Deg); fwdTime = node11.node1Dist; }
            break;
        case 12:
            if (next == 11){ turnToHeading(node12.node0Deg); fwdTime = node12.node0Dist; }
            if (next == 15){ turnToHeading(node12.node1Deg); fwdTime = node12.node1Dist; }
            break;
        case 13:
            if (next == 9) { turnToHeading(node13.node0Deg); fwdTime = node13.node0Dist; }
            if (next == 14){ turnToHeading(node13.node1Deg); fwdTime = node13.node1Dist; }
            break;
        case 14:
            // Placeholder: Node 14 was missing from initializeNodes(), assuming generic
            fwdTime = 700;
            break;
        case 15:
            if (next == 14){ turnToHeading(node15.node0Deg); fwdTime = node15.node0Dist; }
            if (next == 12){ turnToHeading(node15.node1Deg); fwdTime = node15.node1Dist; }
            if (next == 16){ turnToHeading(node15.node2Deg); fwdTime = node15.node2Dist; }
            break;
        case 16:
            if (next == 15){ turnToHeading(node16.node0Deg); fwdTime = node16.node0Dist; }
            if (next == 17){ turnToHeading(node16.node1Deg); fwdTime = node16.node1Dist; }
            break;
        case 17:
            if (next == 16){ turnToHeading(node17.node0Deg); fwdTime = node17.node0Dist; }
            if (next == 18){ turnToHeading(node17.node1Deg); fwdTime = node17.node1Dist; }
            break;
        case 18:
            if (next == 17){ turnToHeading(node18.node0Deg); fwdTime = node18.node0Dist; }
            break;
    }
    
    // Execute the physical movement
    forwardBlock(); 
    
    // Update our position
    currentNode = next;
}

 void beep() 
 {
    tone(buzz_pin, 3000);
    delay(500);

    noTone(buzz_pin);
    delay(500);  //might cause problems
 
 };
