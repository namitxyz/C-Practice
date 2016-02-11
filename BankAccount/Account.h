#ifndef ACCOUNT
#define ACCOUNT
#include <sstream>

class Account{

	std::string Email;
	std::string Password;
	double Balance;

	public:
		Account(){Balance = 0;}
		Account(std::string &szEmail, std::string szPassword, std::string szBalance)
		{
			Email = szEmail;
			Password = szPassword;

			std::stringstream ss;
			ss<<szBalance;
			ss>>Balance;
		}

		std::string getEmail(){return Email;}
		std::string getPassword(){return Password;}
		double      getBalance(){return Balance;}
		void        addBalance(double amt){Balance += amt;}
		bool        checkNewBalance(double amt)
		{ 
			if(Balance - amt >=0) 
				return true;
			else
				return false;
		}

};

#endif