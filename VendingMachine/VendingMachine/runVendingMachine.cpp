#include <iostream>
#include <string>
#include <Windows.h>
#include <stdlib.h>


using namespace std;

enum class VendingMachineStates { IDLE, SELECT, WATER, COLA };

VendingMachineStates vmState;
int ncola = 2, nwater = 2;
bool isRefillRequired = false;


void deliverCola(){
	cout << "Your Cola is being delivered, Be Patient Please..." << endl;
	Sleep(4000);
	cout << "Enjoy Your Cola & Thanks for your Shopping!" << endl;
	Sleep(4000);
}


void deliverWater(){
	cout << "Your Water is being delivered, Be Patient Please..." << endl;
	Sleep(4000);
	cout << "Enjoy Your Water & Thanks for your Shopping!" << endl;
	Sleep(4000);
}

int main(){

	while (!isRefillRequired)
	{
		switch (vmState)
		{
		case VendingMachineStates::IDLE:

			if (ncola == 0 && nwater == 0)
			{
				isRefillRequired = true;
			}
			else
			{
				cout << "Please insert the coin (1$)!" << endl;
				Sleep(2000);
				cout << "Please Select Your Product: Cola -> 1, Water -> 2" << endl;
				vmState = VendingMachineStates::SELECT;
				//cout << "state = " << static_cast<underlying_type<FSMstate>::type>(state) << endl;
			}
			break;
		case VendingMachineStates::SELECT:
			int userInp;
			cin >> userInp;
			if (userInp == 1)
			{
				if (ncola > 0)
				{
					vmState = VendingMachineStates::COLA;
				}
				else
				{
					cout << "Currently no Cola is available! Water -> 2:" << endl;
				}
			}
			else if (userInp == 2)
			{
				if (nwater > 0)
				{
					vmState = VendingMachineStates::WATER;
				}
				else
				{
					cout << "Currently no Water is available! Cola -> 1:" << endl;
				}
			}
			else
			{
				cout << "Wrong Input, please try again, Cola -> 1, Water -> 2" << endl;
			}

			break;
		case VendingMachineStates::COLA:
			ncola = ncola - 1;
			deliverCola();
			vmState = VendingMachineStates::IDLE;
			break;
		case VendingMachineStates::WATER:
			nwater = nwater - 1;
			deliverWater();
			vmState = VendingMachineStates::IDLE;
			break;
		default:
			break;
		}
	}
	cout << "The Machine is Temporary Unavailable" << endl;
	char ch;
	cin >> ch;
	return 0;
}
