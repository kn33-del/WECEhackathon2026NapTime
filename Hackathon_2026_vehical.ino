//# make the ultra sonic sensor functions
//# maby make the led display funciotn

//#####     sensor pins ####
int trigpin_OT = 8;
int echopin_IN = 9;

int distance, cm;
//############################

// ##### Bool Logic #####
bool bool_state;
int distance_to_detect = 16  //in cm 



void setup() {
 
  // setting the modes high/low of the ultra sensor pin
  sensorsetup();
  Serial.begin(9600); // set up the monitor

}

void loop() {
 
  distance = sensorfunction(trigpin_OT, echopin_IN);
  // need to conver to respective units
  // converst and prints
 
  print_info(cm);

  cm = convert_to_cm(distance);
  
  //print_logic(bool_state);
  //bool_state = detect_object(cm);
 

}




//  ############# logic ###############
bool detect_object(int cm) 
{
  // if see object
  if (cm >= 0 && cm < distance_to_detect) 
  { 
    return true;
  } 
  else
  {
    // if further than the distance do nothing
    return false; 
  }

};

void print_logic(bool bool_state) 
{

  Serial.print(bool_state);
  Serial.println(" ");
}

//###################################

//#### converstions funcitons ########
void print_info(int cm) 
{
  Serial.print("CM: " );
  Serial.println(cm);
  delay(200);  //might cause problems
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
  return pulseIn(echopin_IN, HIGH);

};
