unsigned long starting_time;
unsigned long delay_time = 5000;

void setup() {
   starting_time = millis();
}

void loop() {

   unsigned long current_time = millis();

   if (current_time - starting_time >= delay_time) {

       Serial.println("5 seconds passed");

       // Example:
       distance = sensorfunction(trigpin_OT, echopin_IN);
       cm = convert_to_cm(distance);

       starting_time = current_time;   // reset timer
   }

   moveForward();  // keeps running smoothly
}