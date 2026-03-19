// ATM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include "A.F.Input.h"
using namespace std;

struct stClient
{
	string AccountNum, Name, PinCode, PhoneNumber;
	double AccountBalance;
};

enum enAtmOption {eQuickWithdrw = 1, eNormalwithdraw, eDeposit, eCheckBalance, eLogout};

stClient CurrentClient;
void AtmMainMenu();
void QuickWithdrawScreen();
void ShowLoginScreen();

vector <string> SplitEachWord(string Line, string delim = "#//#")
{
	vector <string> vWords;
	string word = "";
	short pos = 0;
	while ((pos = Line.find(delim)) != std::string::npos)
	{
		word = Line.substr(0, pos);

		if (word != "")
			vWords.push_back(word);

		Line.erase(0, pos + delim.length());
	}

	if (Line != "")
		vWords.push_back(Line);

	return vWords;
}

stClient ClientLineToRecord(string line)
{
	vector <string> vData = SplitEachWord(line);
	stClient client;
	client.AccountNum = vData[0];
	client.PinCode = vData[1];
	client.Name = vData[2];
	client.PhoneNumber = vData[3];
	client.AccountBalance = stod(vData[4]);

	return client;

}

vector <stClient> LoadClientsDataFromFile(string fileName = "Clients")
{
	vector <stClient> vClientData;
	string line = "";
	fstream ClientFile;
	ClientFile.open(fileName, ios::in);
	if (ClientFile.is_open())
	{
		while (getline(ClientFile, line))
		{
			vClientData.push_back(ClientLineToRecord(line));
		}
		ClientFile.close();
	}
    
	return vClientData;
}

string ClientRecordToLine(stClient client, string delim = "#//#")
{
	return (client.AccountNum + delim + client.PinCode + delim + client.Name + delim
		+ client.PhoneNumber + delim + to_string(client.AccountBalance));
}

void SaveClientsDataToFile(vector <stClient> vClients, string fileName = "Clients")
{
	fstream clientFile;
	clientFile.open(fileName, ios::out);
	if (clientFile.is_open())
	{
		for (stClient client : vClients)
		{
			if (client.AccountNum == CurrentClient.AccountNum)
				client = CurrentClient;

			clientFile << ClientRecordToLine(client) << endl;			
		}
		clientFile.close();
	}
}

bool FindClientByAccountNumber(string accountNum, stClient& client)
{
	vector <stClient> vClients = LoadClientsDataFromFile();
	for (stClient& C : vClients)
		if (C.AccountNum == accountNum)
		{
			client = C;
			return true;
		}
	return false;
}

string ReadAccountNumber()
{
	string accNum = "";
	cout << "Please Enter the account Number : ";
	getline(cin >> ws, accNum);
	cout << endl;
	return accNum;
}

short UserInput(short From, short To)
{
	short input = 0;
	do
	{
		input = Input::ReadPositiveNumber("Choose what do you want to do? [" + to_string(From) + " to " + to_string(To) + "] ? ");
	} while (input > To || input < From);

	return input;
}

void BackToMainMenu()
{
	cout << "press any key to go back to main menu...";
	system("pause>0");
	AtmMainMenu();
}

void Deposit(int amount)
{
	char sure = 'n';
	sure = Input::ReadCharcter("\nAre you sure you want to perform this transaction? y/n ? : ");
	if (tolower(sure) == 'y')
	{
		vector <stClient> vClients = LoadClientsDataFromFile();
		CurrentClient.AccountBalance += amount;
	    cout << "\nDone successfully new balance is : " << CurrentClient.AccountBalance << endl;
		
		SaveClientsDataToFile(vClients);
	}
	BackToMainMenu();
}

void ShowClientBalance()
{
	cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
}

short GetQuickWithdrawAmount(short choice)
{
	switch (choice)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;
	}
}

void ExcuteQuickWithdraw()
{
	short choice = UserInput(1, 9);
	
	if (choice == 9)
		AtmMainMenu();
	
	short amount = GetQuickWithdrawAmount(choice);

	if (amount > CurrentClient.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance,, make another choice." << endl;
		ExcuteQuickWithdraw();
	}

	Deposit((amount * -1));
}

void QuickWithdrawScreen()
{
	system("cls");
	cout << "\n-----------------------------------------------\n";
	cout << "\t\tQuick Withdraw\n";
	cout << "\n-----------------------------------------------\n";
	cout << "[1] 20        [2] 50\n";
	cout << "[3] 100       [4] 200\n";
	cout << "[5] 400       [6] 600\n";
	cout << "[7] 800       [8] 1000\n";
	cout << "[9] Exit\n";
	cout << "-----------------------------------------------\n";
	ShowClientBalance();
	ExcuteQuickWithdraw();
}

void NormalWithdrawScreen()
{
	system("cls");
	cout << "\n-----------------------------------------------\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "\n-----------------------------------------------\n";

input:
	int amount = Input::ReadIntegerNumber("Please enter an amount multiple of 5's ? ");

	if (amount % 5 != 0)
		goto input;

	if (amount > CurrentClient.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance << endl;
		goto input;
	}

	Deposit((amount * -1));
}

void DepositScreen()
{
	system("cls");
	cout << "\n-----------------------------------------------\n";
	cout << "\t\tDeposit Screen\n";
	cout << "\n-----------------------------------------------\n";
	int amount = Input::ReadPositiveNumber("Please Enter a positive Amount? ");
	Deposit(amount);
}

void ExcuteAtmOption()
{
	short option = UserInput(1, 5);
	if (option == enAtmOption::eQuickWithdrw)
	{
		QuickWithdrawScreen();
	}
	else if (option == enAtmOption::eNormalwithdraw)
	{
		NormalWithdrawScreen();
	}
	else if (option == enAtmOption::eDeposit)
	{
		DepositScreen();
	}
	else if (option == enAtmOption::eCheckBalance)
	{
		ShowClientBalance();
		BackToMainMenu();
	}
	else if (option == enAtmOption::eLogout)
	{
		ShowLoginScreen();
	}
}

void AtmMainMenu()
{
	system("cls");
	cout << "======================================================\n";
	cout << "\t\tATM Main Menu Screen\n";
	cout << "======================================================\n";
	cout << "\t[1] Quick withdraw.\n";
	cout << "\t[2] Normal withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "======================================================\n";
	ExcuteAtmOption();
}

bool IsClient(string accountNumber, string PinCode)
{
	vector <stClient> vClientData = LoadClientsDataFromFile();
	for (stClient client : vClientData)
	{
		if (client.AccountNum == accountNumber && client.PinCode == PinCode)
		{
			CurrentClient = client;
			return true;
		}
	}
	return false;

}

void Login()
{
	string accountNumber, PinCode;
	accountNumber = Input::ReadString("Enter Account Number? ");
	PinCode = Input::ReadString("Enter PinCode? ");
	if (IsClient(accountNumber, PinCode))
		AtmMainMenu();
	else
	{
		system("cls");
		cout << "\nInvalid Account Number/PinCode! \n";
		Login();
	}
}

void ShowLoginScreen()
{
	system("cls");
	cout << "======================================================\n";
	cout << "\t\tLogin Screen\n";
	cout << "======================================================\n";
	Login();
}

int main()
{
	ShowLoginScreen();
	return 0;
}

