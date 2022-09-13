/*
 * 
 * PIE Mini-Project 1: Bike Light
 * Diana Garcia & Gia-Uyen Tran
 * Submitted September 13, 2022
 * 
 * As required by the assignment guidelines, this program switches 
 * between a group of 4 LEDs between 5 modes (see functions below) 
 * when a push button is pressed.
 * 
 * Functions:
 * all_off() - turns all LEDs off
 * all_on() - turns all LEDs on
 * all_blinking() - blinks all LEDs on and off in unison
 * bouncing() - alternates LEDs in consecutive order (by location), 
 *    then reverse direction
 * binary() - blinks binary numbers up to 15 as if each LED were a 
 *    bit in a binary number
 * 
 * Hardware Connections:
 * Yellow LED - Pin 5
 * Red LED - Pin 6
 * Button - Pin 8
 * Blue LED - Pin 10
 * Green LED - Pin 11
 * 
 */


// Connect components to pins
const int RED_LED = 6;
const int YELLOW_LED = 5;
const int GREEN_LED = 11;
const int BLUE_LED = 10;  
const int BUTTON = 8;

// intialize counting variables
int mode = 0;
int counter = 0;
int button_state = 0;
int previous_button = 0;
int button_count = 0;
int ledstate = 0;

// Global variable to store the time that LED last changed state
uint32_t blink_time;


void setup() {  

  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  // Turn LEDs off initially
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW); 
  digitalWrite(YELLOW_LED, LOW); 
  digitalWrite(RED_LED, LOW); 

  // Remember the current value of the millis timer
  blink_time = millis();
}


void loop() {
  
  // Change mode when button is pressed
  button_state = digitalRead(BUTTON);
  
  if (button_state != previous_button) {
    if (button_state == HIGH) {
      button_count++;
      mode = button_count % 5;
    } 
  } 
  previous_button = button_state;
  
  if (mode == 0) {
      all_off();
    } else if (mode == 1) {
      all_on();
    } else if (mode == 2) {
      all_blinking();
    } else if (mode == 3) {
      bouncing();
    } else if (mode == 4) {
      binary();
    }
    
 delay(50);
 
}


// ------------- FUNCTIONS ------------- //


void all_on() { 
 
  // Turn all LEDs on
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(YELLOW_LED, HIGH);
 
}


void all_off() {
  
  // Turn all LEDs off
  digitalWrite(RED_LED,LOW);
  digitalWrite(YELLOW_LED,LOW);
  digitalWrite(BLUE_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
  
}


void all_blinking() {
 
  uint32_t t;                         
  t = millis();    

  int speed = 250;
  
  if (t >= blink_time + speed) {
    // Switch states (1: on, 0: off)
    if (ledstate == 1) {
      ledstate = 0;
    } else {
      ledstate = 1;
    }

    if (ledstate == 1) {
      
      // Turn on all LEDs
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      
    } else {
      
      // Turn off all LEDs
      digitalWrite(RED_LED,LOW);
      digitalWrite(YELLOW_LED,LOW);
      digitalWrite(BLUE_LED,LOW);
      digitalWrite(GREEN_LED,LOW);
      
    }
    blink_time = t;            
  }
 
}


void bouncing() {

  int32_t t;                         
  t = millis();   

  int speed = 250;
  
  if (t >= blink_time + speed) {
    
    counter++;
    counter = counter % 6;
    
    if (counter == 0) {
      
      // Turn on only red light
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      
    } else if (counter == 1 || counter == 5) {
      
      // Turn on only yellow light
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      
    } else if (counter == 2 || counter == 4) {

      // Turn on only green light
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
      
    } else if (counter == 3) {

      // Turn on only blue light
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);
      
    } 
    
    blink_time = t;
    
   }
}


void binary() {

  int32_t t;  
  t = millis();   

  int speed = 250;

  all_off();
 
  if (t >= blink_time + speed) {
   
    if (counter <= 15){
      
      counter++;
    
      if((counter % 2) > 0) {digitalWrite(RED_LED, HIGH);
        } else { digitalWrite(RED_LED, LOW); }
      if((counter % 4) > 1) { digitalWrite(YELLOW_LED, HIGH);
        } else { digitalWrite(YELLOW_LED, LOW); }
      if((counter % 8) > 3) { digitalWrite(GREEN_LED, HIGH);
        } else { digitalWrite(GREEN_LED, LOW); }
      if((counter % 16) > 7) { digitalWrite(BLUE_LED, HIGH);
        } else { digitalWrite(BLUE_LED, LOW); } 
    
    } else {
      counter = 0;
    }
    
    blink_time = t;
  }

}
