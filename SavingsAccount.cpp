# Bank

#include "SavingsAccount.h"


SavingsAccount::SavingsAccount(int amount,
	const char* ownerId, const char* IBAN, double interestRate)
	: Account(amount, ownerId, IBAN), m_interestRate(interestRate){}

bool SavingsAccount::withdraw(int amount)
{
	if (amount > getBalance())return false;
	setAmount(getBalance() - amount);
	return true;
}


void SavingsAccount::display() const
{
	std::cout << "Savings account information :" << std::endl
		<< "IBAN : " << getIBAN() << std::endl
		<< "Owner's id : " << getOwnerId() << std::endl
		<< "Balance : " << getBalance() << std::endl
		<< "Interest rate : " << m_interestRate << std::endl;
}
