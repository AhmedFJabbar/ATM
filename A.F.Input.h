#pragma once
#include <iostream>
#include <string>

#include <vector>
using namespace std;




namespace Input
{

	struct sClient
	{
		string AccountNum, Name;
		int PinCode, PhoneNumber;
		double AccountBalance;

	};

    int  ReadPositiveNumber(string message)
	{
		int number;
		do
		{
			cout << message;
			cin >> number;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
				cout << "Invalid Number , Enter a positive number : ";
				cin >> number;
				cout << endl;
			}
		} while (number < 0);
		
		return number;

	}

	int  ReadIntegerNumber(string message)
	{
		int number;
	    cout << message;
	    cin >> number;
	/*	while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
			cout << "Invalid Number , Enter a valid number : ";
			cin >> number;
			cout << endl;
		}*/
		return number;

	}

	double  ReadDoubleNumber(string message)
	{
		double number;
		cout << message;
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
			cout << "Invalid Number , Enter a valid number : ";
			cin >> number;
			cout << endl;
		}

		return number;

	}

	string ReadString(string message)
	{
		string str = "";
		cout << message;
		/*cin >> str;
		cin.ignore(0, '\n');*/
		getline(cin >> ws, str);

		return str;
	}

	char ReadCharcter(string message)
	{
		char ch;
		cout << message;
		cin >> ch;
		
		return ch;
	}

	void UserFillIntgerVector(vector <int>& vNumbers)
	{
		char repet = 'Y';

		while (repet == 'Y' || repet == 'y')
		{
			vNumbers.push_back(Input::ReadIntegerNumber("Please enter a number : "));
			repet = ReadCharcter("Do you want to add more numbers ? Y/N : ");
			cout << endl;
		}
	}

	void UserFillStringVector(vector <string>& vWords)
	{
		char repeat = 'Y';

		while (repeat == 'Y' || repeat == 'y')
		{
			vWords.push_back(ReadString("Please enter a string : "));
			repeat = ReadCharcter("Do you want to add more strings ? Y/N : ");		
			cout << endl;
		}
	}

	void ReadClientData(sClient& client)
	{
		client.AccountNum = Input::ReadString("Enter Account Number : ");
		client.PinCode = Input::ReadIntegerNumber("Enter PinCode : ");
		client.Name = Input::ReadString("Enter Name : ");
		client.PhoneNumber = Input::ReadIntegerNumber("Enter Phone : ");
		client.AccountBalance = Input::ReadDoubleNumber("Enter Account Balance : ");

	}

}