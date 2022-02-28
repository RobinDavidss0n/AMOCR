//LED BUILT_IN is GPIO 33 
#define LED_BUILTIN 4
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set the pin as output
}

// Remember that the pin work with inverted logic
// LOW to Turn on and HIGH to turn off
void loop() {
  digitalWrite(LED_BUILTIN, LOW); //Turn on
  delay (1000); //Wait 1 sec
  digitalWrite(LED_BUILTIN, HIGH); //Turn off
  delay (1000); //Wait 1 sec
}
