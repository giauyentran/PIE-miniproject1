/*
 * PIE Mini-Project 1: Bike Light
 * Diana Garcia & Gia-Uyen Tran
 * 
 */

const uint16_t BLINK_INTERVAL = 500;  // Time interval between toggling LED in milliseconds
const uint8_t blue = 10;               // LED is connected to D13
const uint8_t green = 11;
const uint8_t yellow = 12;
const uint8_t red = 13;
int button = 8;
int i = 0;
int state = 0;
int counter = 0;
int button_state = 0;
int previous_state = 0;
int button_count = 0;

uint32_t blink_time;                  // Global variable to store the time that LED last changed state

void setup() {
  Serial.begin(9600); // for testing purposes
  
  pinMode(blue, OUTPUT);               // Configure LED pin as a digital output
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(button, INPUT);
  
  digitalWrite(blue, LOW);            // Set LED low initially
  digitalWrite(green, LOW); 
  digitalWrite(yellow, LOW); 
  digitalWrite(red, LOW); 

  blink_time = millis();              // Remember the current value of the millis timer
}

void loop() {

  button_state = digitalRead(button);
  
  if (button_state != previous_state) {
    if (button_state == HIGH) {
      button_count++;
      state = button_count % 5;
      Serial.print(state);
    } 
  }
  
  previous_state = button_state;

  if (state == 0) {
    all_off();
    } else if (state == 1) {
      all_on();
    } else if (state == 2) {
      all_blinking();
    } else if (state == 3) {
      bouncing();
    } else if (state == 4) {
      binary();
    }
 
}

// FUNCTIONS

void all_on() {
  digitalWrite(red,HIGH);
  digitalWrite(yellow,HIGH);
  digitalWrite(blue,HIGH);
  digitalWrite(green,HIGH);
}

void all_off() {
  digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
}


void all_blinking() { // from Brad's tutorial. may want to refactor

  uint32_t t;                         

  t = millis();                       
  if (t >= blink_time + BLINK_INTERVAL) { // If BLINK_INTERVAL milliseconds have elapsed since blink_time,
    digitalWrite(blue, !digitalRead(blue));
    digitalWrite(green, !digitalRead(green));
    digitalWrite(yellow, !digitalRead(yellow));
    digitalWrite(red, !digitalRead(red));
    blink_time = t;            
  }
}


void bouncing() {

    if (counter == 0) {
      digitalWrite(red, HIGH);
      delay(250);
      digitalWrite(red, LOW);
    } else if (counter == 1 || counter == 5){
      digitalWrite(yellow, HIGH);
      delay(250);
      digitalWrite(yellow, LOW);
    } else if (counter == 2 || counter == 4) {
      digitalWrite(green, HIGH);
      delay(250);
      digitalWrite(green, LOW);
    } else if (counter == 3) {
      digitalWrite(blue, HIGH);
      delay(250);
      digitalWrite(blue, LOW);
    } 
    
  counter++;
  counter = counter % 6;
}


void binary(){
  
  int speed = 250;
  
  all_off();
  delay(speed);
  
  if (i <= 15){
    i++; //We start the counter:
    if((i % 2) > 0) { digitalWrite(red, HIGH); 
      } else { digitalWrite(red, LOW); }
    if((i % 4) > 1) { digitalWrite(yellow, HIGH); 
      } else { digitalWrite(yellow, LOW); }
    if((i % 8) > 3) { digitalWrite(green, HIGH); 
      } else { digitalWrite(green, LOW); }
    if((i % 16) > 7) { digitalWrite(blue, HIGH); 
      } else { digitalWrite(blue, LOW); } 
    } else {
        i = 0;
    }
    
  delay(speed);
}
