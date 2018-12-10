/*
  NTU Garage@EEE
  Button.cpp - Arduino Library for button.
  Created by Jian Xian and Cong Sheng Dec 2018.
*/

#include "Button.h"



void Button::attach(int pin){
	pinMode(pin, INPUT_PULLUP);
}

void Button::set_State(int value) {
	btnState = value;
}

bool Button::get_State() {
	return btnState; 
}

bool Button::isPressed(int pin, int sample_Size) {
	int sum = 0;
	for (int j = 0; j < sample_Size ; j++) {
	   sum += digitalRead(pin);
	}
	if (sum == 0 && btnState == 0) { 
	   btnState = 1;
	   instance_Pressed = millis();
	return true;
	}
	else if (sum == sample_Size && btnState == 1) {  
	   btnState = 0;
	  return false;
	}
	else {
	  return false;
	}
}

bool Button::isReleased(int pin, int sample_Size) {
	int sum = 0;
	for (int j = 0; j < sample_Size; j++) {
		sum += digitalRead(pin);
	}
	if(sum == sample_Size && btnState == 1) { 
		btnState = 0;
		instance_Released = millis();
	  return true;
	}
	else if (sum == 0 && btnState == 0) { 
		btnState = 1;
	  return false;
	}
	else {
	  return false;
	}
}

bool Button::isHeld(int pin, int sample_Time){
	int sum = 0;
	for (int j = 0; j < sample_Time ; j++) {
	   isPressed(pin, sample_Time);
	   sum += digitalRead(pin);
	}
	if (sum == 0 && btnState == 1 ) {
	   current_Time = millis();
	   time_Press = current_Time - instance_Pressed;
	  return true;
	}
	else if (sum > 0) { 
	  return false;
	}
	else {
	  return false;
	}  
}

bool Button::isLeftopen(int pin, int sample_Time){
	int sum = 0;
	for (int j = 0; j < sample_Time ; j++) {
	   isReleased(pin, sample_Time);
	   sum += digitalRead(pin);
	}
	if (sum == sample_Time && btnState == 0 ) {
	   current_Time = millis();
	   time_Leftopen = current_Time - instance_Released;
	  return true;
	}
	else if (sum < sample_Time) { 
	  return false;
	}
	else {
	  return false;
	}
}



