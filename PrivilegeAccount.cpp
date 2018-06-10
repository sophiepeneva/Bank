# Bank

#include "PrivilegeAccount.h"


PrivilegeAccount::PrivilegeAccount(int amount,
	const char* ownerId, const char* IBAN, double overdraft)
	: Account(amount, ownerId, IBAN), m_overdraft(overdraft) {}

bool PrivilegeAccount::withdraw(int amount)
{
	if (amount > getBalance() + m_overdraft)return false;
	setAmount(getBalance() - amount);
	return true;
}


void PrivilegeAccount::display() const
{
	std::cout << "Privilege account information :" << std::endl
		<< "IBAN : " << getIBAN() << std::endl
		<< "Owner's id : " << getOwnerId() << std::endl
		<< "Balance : " << getBalance() << std::endl
		<< "Overdraft : " << m_overdraft << std::endl;
}
