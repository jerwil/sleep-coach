
// Sleep coach using ATTiny 85


const int LEDPin = 5;                  // IC leg 6 (PB1), output to red channel

unsigned long currentTime;
double second_timer[1] = {0}; // This is use dto keep track of the timer used to tick for each second
int ticked = 0;


void setup() {                
  // initialize the digital pin as an output.
  pinMode(LEDPin, OUTPUT);      
}


void loop() {
  
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
