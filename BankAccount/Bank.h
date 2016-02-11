#ifndef BANK
#define BANK

#include <iostream>
#include "Account.h"
#include <map>
class Bank{

	std::map<std::string, Account> IdToAccountMap;

    public:

    	Bank();
    	void OpenAccount();
    	void DepositToAccount();
    	void WithdrawFromAccount();
    	void TransferBetweenTwoAccounts();
    	void UpdateRecordsInDatabase();	
    	bool GetUserLogin(std::string &emailid, std::string &passwd);
    	bool ReloadFile();
};

#endif

