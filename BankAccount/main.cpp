#include <iostream>
#include "Bank.h"
using namespace std;

int main()
{
	Bank FirstBank;

	while(true)
	{
		cout<<endl<<endl<<"Enter a number from the following options :"<<endl;
		cout<<"1: Open a bank account"<<endl;
		cout<<"2: Deposit Money in the bank account"<<endl;
		cout<<"3: Withdraw Money from the bank account"<<endl;
		cout<<"4: Transfer funds between two accounts"<<endl;

		int UserChoice = 0;
		cin>>UserChoice;

		switch(UserChoice)
		{
			case 1: FirstBank.OpenAccount();
			        break;
			case 2: FirstBank.DepositToAccount();
			        break;
			case 3: FirstBank.WithdrawFromAccount();
			        break;
			case 4: FirstBank.TransferBetweenTwoAccounts();
			        break;

			default:
			        cout<<"Wrong choice. Please enter either 1,2,3 or 4"<<endl;
			        break;
		}
	}

	return 0;
}