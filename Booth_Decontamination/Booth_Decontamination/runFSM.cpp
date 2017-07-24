#include <iostream>
#include <string>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

enum class FSMstate { IDLE, DOOR_1_OPEN, DOOR_1_CLOSE, UV_LIGHT_ON, DOOR_2_OPEN };
enum class button { nonPressed, pressed };
enum class pressureSensor{ nonDetected, detected };

FSMstate state;
pressureSensor ps;
button b;

bool isProcessRunning = true;

button getButtonStatus(){
	bool buttonStatus = false;
	cout << "is the button pressed? (No -> 0 | Yes -> 1)" << endl;
	cin >> buttonStatus;
	if (!buttonStatus)
	{
		cout << "button is NOT pressed!" << endl;
		b = button::nonPressed;
	}
	else if (buttonStatus)
	{
		cout << "button is pressed!" << endl;
		b = button::pressed;
	}
	else
	{
		cout << "try again plz! (No -> 0 | Yes -> 1)" << endl;
	}
	return b;
}

pressureSensor getPressureSensorStatus(){
	bool pressSens = false;
	cout << "is pressure sensor sensing? (No -> 0 | Yes -> 1)" << endl;
	cin >> pressSens;
	if (!pressSens)
	{
		cout << "Pressure sensor NOT sensing!" << endl;
		ps = pressureSensor::nonDetected;
	}
	else if (pressSens)
	{
		cout << "Pressure sensor sensing!" << endl;
		ps = pressureSensor::detected;
	}
	else
	{
		cout << "try again plz! (No -> 0 | Yes -> 1)" << endl;
	}
	return ps;
}

void openDoor1(){
	cout << "Door 1 OPENING, You may enter the booth..." << endl;
	Sleep(4000);
}

void closeDoor1(){
	cout << "Door 1 CLOSING!" << endl;
	Sleep(2000);
}

void turnOnUV(){
	cout << "UV light ON -> Booth Decontamination started! Be patient please..." << endl;
	Sleep(10000);
}

void openDoor2(){
	cout << "Door 2 OPENING, You may leave the booth..." << endl;
	Sleep(4000);
}

int main(){
	cout << "Welcome to Security Booth Decontamination Program" << endl;
	while (isProcessRunning)
	{
		switch (state)
		{
		case FSMstate::IDLE:
			cout << "IDLE!" << endl;
			getButtonStatus();
			if (b == button::pressed)
			{
				state = FSMstate::DOOR_1_OPEN;
				//cout << "state = " << static_cast<underlying_type<FSMstate>::type>(state) << endl;
			}
			break;
		case FSMstate::DOOR_1_OPEN:
			openDoor1();
			state = FSMstate::DOOR_1_CLOSE;
			break;
		case FSMstate::DOOR_1_CLOSE:
			closeDoor1();
			getPressureSensorStatus();
			//cout << "pressure sensor = " << static_cast<underlying_type<pressureSensor>::type>(ps) << endl;
			if (ps == pressureSensor::detected)
			{
				state = FSMstate::UV_LIGHT_ON;
			}
			else
			{
				state = FSMstate::IDLE;
			}
			break;
		case FSMstate::UV_LIGHT_ON:
			turnOnUV();
			state = FSMstate::DOOR_2_OPEN;
			break;
		case FSMstate::DOOR_2_OPEN:
			openDoor2();
			getPressureSensorStatus();
			if (ps == pressureSensor::nonDetected)
			{
				cout << "Door 2 CLOSING, back to IDLE..." << endl;
				state = FSMstate::IDLE;

				isProcessRunning = false;
			}
			break;
		default:
			break;
		}
	}
	cout << "Booth decontamination successfully finished!" << endl;
	char ch;
	cin >> ch;
	return 0;
}
