# Bank

#include "CurrentAccount.h"


CurrentAccount::CurrentAccount(int amount, const char* ownerId, const char* IBAN) 
	: Account(amount, ownerId, IBAN)
{
}


bool CurrentAccount::withdraw(int amount)
{
	if (amount > getBalance())return false;
	setAmount(getBalance() - amount);
	return true;
}


void CurrentAccount::display() const
{
	std::cout << "Current account information :" << std::endl
		<< "IBAN : " << getIBAN() << std::endl
		<< "Owner's id : " << getOwnerId() << std::endl
		<< "Balance : " << getBalance() << std::endl;
}
