#include <math.h>


// Sleep coach using ATTiny 85




const int LEDPin = 5;                  // IC leg 6 (PB1), output to red channel

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

int button_state = 0;
int button_pushed = 0; // This is the indicator that the button was pushed and released
int button_press_initiate[1];     // storage for button press function
int button_press_completed[1];    // storage for button press function


void setup() {                
  // initialize the digital pin as an output.
  pinMode(LEDPin, OUTPUT);
  Serial.begin(9600);  
}


void loop() {
  
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
}
if (x*k >= 2*3.14159){x=0;}
//else if (brightness <= 0){brightincrease = 1;}
  analogWrite(LEDPin,brightness);
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
