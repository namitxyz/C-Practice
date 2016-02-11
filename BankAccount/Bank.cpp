#include "Bank.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits>

using namespace std;

static void SplitString(string &input, char delim, vector<string> &tokens);

Bank::Bank()
{
	if(ReloadFile())
		return;
}

bool Bank::ReloadFile()
{
	ifstream BankRecords("BankRecords.txt");

	if(!BankRecords.is_open())
	{
		ofstream OpenFile("BankRecords.txt");
		OpenFile.close();
		return true;
	}

	std::string line;
	IdToAccountMap.clear();

	while(getline(BankRecords, line))
	{
		vector<string> tokens;

		SplitString(line, ',', tokens);

		Account SingleAccount(tokens[0], tokens[1], tokens[2]);
		IdToAccountMap[tokens[0]] = SingleAccount;
	}

	BankRecords.close();

	return false;
}
void Bank::OpenAccount()
{
	cout<<"*************OPENING A NEW BANK ACCOUNT****************"<<endl;

	cout<<"Enter a unique email id which represents your identity :";

	string emailid;

	cin>>emailid;

	cout<<"Enter a password which you will use later to login :";

	string passwd;

	cin>>passwd;

	if(emailid.find(',') != string::npos || passwd.find(',') != string::npos)
	{
		cout<<"The email id and password cannot contain commas. Try Again!"<<endl;
		return;
	}

	Account acc(emailid, passwd, "0");

	if(ReloadFile())
		return;

	if(IdToAccountMap.find(emailid) != IdToAccountMap.end())
	{
		cout<<"This email id already exists. Try a new email ID."<<endl;
		return;
	}

	IdToAccountMap[emailid] = acc;

	cout<<"Account created with an opening balance of $0 for email ID :"<<emailid<<endl;

	UpdateRecordsInDatabase();
}

void Bank::DepositToAccount()
{
	cout<<"*************DEPOSIT MONEY TO BANK ACCOUNT****************"<<endl;
	
	string emailid, passwd;
	if(GetUserLogin(emailid, passwd))
		return;

	double Amount = -1;
	
	do{
		cout<<"Enter the deposit amount :";

		while(!(cin >> Amount))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout <<"Please enter a valid deposit amount. "<<endl;
		}

		if(Amount < 0)
		{
			cout<<endl<<"Please enter a valid deposit amount. "<<endl;
			Amount = -1;
		}
		
	}while(Amount < 0);

	if(ReloadFile())
		return;

	(IdToAccountMap.find(emailid)->second).addBalance(Amount);

	UpdateRecordsInDatabase();
}

void Bank::WithdrawFromAccount()
{
	cout<<"*************WITHDRAW MONEY FROM BANK ACCOUNT****************"<<endl;

	string emailid, passwd;
	if(GetUserLogin(emailid, passwd))
		return;

	double Amount = -1;
	
	do{
		cout<<"Enter the withdrawal amount :";

		while(!(cin >> Amount))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout <<"Please enter a valid withdrawal amount. "<<endl;
		}

		if(Amount < 0)
		{
			cout<<endl<<"Please enter a valid withdrawal amount. "<<endl;
			Amount = -1;
		}
		
	}while(Amount < 0);

	if(ReloadFile())
		return;

	if((IdToAccountMap.find(emailid)->second).checkNewBalance(Amount))
	{
		cout<<"Withdrawn $"<<Amount<<" from your account"<<endl;
		(IdToAccountMap.find(emailid)->second).addBalance(Amount*-1);
	}
	else
	{
		cout<<"The bank will not let you withdraw $"<<Amount<<" because you will end up with negative balance"<<endl;
		return;
	}

	UpdateRecordsInDatabase();

}
void Bank::TransferBetweenTwoAccounts()
{
	cout<<"*************TRANSFER MONEY TO ANOTHER BANK ACCOUNT****************"<<endl;
	
	string emailid, passwd;
	if(GetUserLogin(emailid, passwd))
		return;

	string emailid_p2;

	cout<<"Enter the email id of the person you would like to transfer funds to :";

	cin>>emailid_p2;

	double Amount = -1;

	do{
		cout<<"Enter the transfer amount :";

		while(!(cin >> Amount))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout <<"Please enter a valid transfer amount. "<<endl;
		}

		if(Amount < 0)
		{
			cout<<endl<<"Please enter a valid transfer amount. "<<endl;
			Amount = -1;
		}
		
	}while(Amount < 0);

	if(ReloadFile())
		return;

	if(IdToAccountMap.find(emailid_p2) == IdToAccountMap.end())
	{
		cout<<"User record for the recepient not found"<<endl;
		return;
	}

	if((IdToAccountMap.find(emailid)->second).checkNewBalance(Amount))
	{
		cout<<"Transferred $"<<Amount<<" from your account to account belonging to :"<<emailid_p2<<endl;
		(IdToAccountMap.find(emailid)->second).addBalance(Amount*-1);
		(IdToAccountMap.find(emailid_p2)->second).addBalance(Amount);
	}
	else
	{
		cout<<"The bank will not let you transfer $"<<Amount<<" because you will end up with negative balance"<<endl;
		return;
	}

	UpdateRecordsInDatabase();
}
void Bank::UpdateRecordsInDatabase()
{
	ofstream BankRecords("BankRecords.txt");

	for(map<string, Account>::iterator it = IdToAccountMap.begin(); it != IdToAccountMap.end(); ++it)
		BankRecords << (it->second).getEmail()<<","<<(it->second).getPassword()<<","<<(it->second).getBalance()<<endl;
	
	BankRecords.close();

}
bool Bank::GetUserLogin(string &emailid, string &passwd)
{
	cout<<"Enter a unique email id which represents your identity :";

	cin>>emailid;

	cout<<"Enter a password associated with your account :";

	cin>>passwd;

	if(IdToAccountMap.find(emailid) == IdToAccountMap.end())
	{
		cout<<"User record not found"<<endl;
		return true;
	}
		
	else
	{
		if((IdToAccountMap.find(emailid)->second).getPassword() != passwd)
		{
			cout<<"Invalid Password"<<endl;
			return true;
		}
	}
	return false;
}
static void SplitString(string &input, char delim, vector<string> &tokens)
{
	stringstream ss;
	ss<<input;
	string SingleElement;
	string NewOutput;

	while(getline(ss, SingleElement, delim))
	{
		if(!SingleElement.empty())
			tokens.push_back(SingleElement);
	}
}