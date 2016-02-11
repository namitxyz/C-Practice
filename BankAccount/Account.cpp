#include <iostream>
#include "Account.h"
#include <sstream>

using namespace std;

Account::Account(std::string &szEmail, std::string szPassword, std::string szBalance)
{
	Email = szEmail;
	Password = szPassword;

	stringstream ss;

	ss<<szBalance;

	ss>>Balance;

}