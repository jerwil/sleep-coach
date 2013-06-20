#include <math.h>


// Sleep coach using ATTiny 85


char* mode = "time_choose"; // Modes are time_choose, sleep_coach, and off
// Time choose mode is where the user choses between 7, 14, 21, and 28 minutes of sleep coaching
// sleep coach mode is the mode with pulsating light
// off is when the sleep coaching is complete. A button press will bring it into time choose mode

int time_choice = 7;

const int LED1Pin = 5;
const int LED2Pin = 9;
const int LED3Pin = 6;
const int LED4Pin = 10;

const int ButtonPin = 11;
int button_state = 0;
int button_pushed = 0; // This is the indicator that the button was pushed and released

int blink_pattern[4] = {1,0,0,0}; // This is the indicator for the current time setting. It will blink 1 of 4 LEDs
int blink = 1; // This is used for blinking the LEDs


unsigned long currentTime;
double milis_timer[1] = {0}; // This is use dto keep track of the timer used to tick for each second
double second_timer[1] = {0}; // This is use dto keep track of the timer used to tick for each second
int ticked = 0;

int delay_int = 1;
int brightness = 0;
double brightincrease = 1;
double k = .028;
double k_initial = 0.028;
double k_final = 0.016;
double x = 3*3.14159/2/k; // This starts it at 0 brightness

double total_time = 420; // seconds for entire breathing coaching
double current_time = 0;

int button_press_initiate[1];     // storage for button press function
int button_press_completed[1];    // storage for button press function


void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED1Pin, OUTPUT);
  pinMode(LED2Pin, OUTPUT);
  pinMode(LED3Pin, OUTPUT);
  pinMode(LED4Pin, OUTPUT);
  pinMode(ButtonPin, INPUT);
  Serial.begin(9600);  
}


void loop() {
  
button_state = digitalRead(ButtonPin);
button_pushed = button_press (button_state, button_press_initiate, button_press_completed);
  
if (mode == "time_choose"){
  
delay(1);

if (button_pushed == 1){
time_choice += 7;
//Serial.println("Time changed!");
button_pushed = 0;
}
if (time_choice > 28){time_choice = 7;}
  
  if (time_choice == 7){
    blink_pattern[0] = 254;
    blink_pattern[1] = 0;
    blink_pattern[2] = 0;
    blink_pattern[3] = 0;
  }
  if (time_choice == 14){
    blink_pattern[0] = 0;
    blink_pattern[1] = 254;
    blink_pattern[2] = 0;
    blink_pattern[3] = 0;
  }
  if (time_choice == 21){
    blink_pattern[0] = 0;
    blink_pattern[1] = 0;
    blink_pattern[2] = 254;
    blink_pattern[3] = 0;
  }
  if (time_choice == 28){
    blink_pattern[0] = 0;
    blink_pattern[1] = 0;
    blink_pattern[2] = 0;
    blink_pattern[3] = 254;
  }
 
if (tick(1000,second_timer) == 1){
 if (blink == 1){blink = 0;}
 else if (blink == 0){blink = 1;} 
}

if (button_state == 1){blink = 1;}

if (blink == 0){
  
  blink_pattern[0] = 0;
  blink_pattern[1] = 0;
  blink_pattern[2] = 0;
  blink_pattern[3] = 0;

}

analogWrite(LED1Pin,  blink_pattern[0]);
analogWrite(LED2Pin,  blink_pattern[1]);
analogWrite(LED3Pin,  blink_pattern[2]);
analogWrite(LED4Pin,  blink_pattern[3]);
 
}
  
if (mode == "sleep_coach"){
  
if (current_time >= total_time){mode = "off";}
  
brightness = 127*(1 + sin(k*x));
Serial.print("Brightness:");
Serial.println(brightness);
Serial.print("X:");
Serial.println(x);
  
if (tick(delay_int,milis_timer) == 1){
  x += brightincrease;
}
if (tick(1000,second_timer) == 1){
  current_time += 1;
  Serial.print("current_time:");
  Serial.println(current_time); 
  k = k_initial + current_time*(k_final-k_initial)/total_time;
}
if (x*k >= 2*3.14159){x=0;}
//else if (brightness <= 0){brightincrease = 1;}
  analogWrite(LED1Pin,brightness);
  analogWrite(LED2Pin,brightness);
  analogWrite(LED3Pin,brightness);
  analogWrite(LED4Pin,brightness);
}

if (mode == "off"){
  
button_pushed = button_press (button_state, button_press_initiate, button_press_completed);
  
}

}

int button_press (int button_indicator, int button_press_initiated[1], int button_press_complete[1]){
	if (button_indicator == 0 && button_press_initiated[0] == 1) {
	button_press_complete[0] = 1;
	button_press_initiated[0] = 0;
	}
	else if (button_indicator == 1){
	button_press_initiated[0] = 1;
	button_press_complete[0] = 0;
	}
	else {button_press_complete[0] = 0;}
return button_press_complete[0];
}

int tick(int delay, double timekeeper[1]){
currentTime = millis();
if(currentTime >= (timekeeper[0] + delay)){
	timekeeper[0] = currentTime;
	return 1;
  }
else {return 0;}
}
