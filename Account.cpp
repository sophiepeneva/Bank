# Bank

#include "Account.h"


Account::Account(int amount, const char* ownerId, const char* IBAN) : m_amount(amount)
{
	setOwnerID(ownerId);
	setIBAN(IBAN);
}

Account& Account::operator=(const Account& c)
{
	if (this != &c)
	{
		Destroy();
		CopyFrom(c);
	}
	return *this;
}

void Account::Destroy()
{
	delete[] m_ownerId;
	delete[] m_IBAN;
}


void Account::CopyFrom(const Account& a)
{
	setAmount(a.m_amount);
	setOwnerID(a.m_ownerId);
	setIBAN(a.getIBAN());
}

void Account::setIBAN(const char* IBAN)
{
	m_IBAN = new char[strlen(IBAN) + 1];
	strcpy_s(m_IBAN, strlen(IBAN) + 1, IBAN);
}
void Account::setOwnerID(const char* ownerId)
{
	m_ownerId = new char[strlen(ownerId) + 1];
	strcpy_s(m_ownerId, strlen(ownerId) + 1, ownerId);
}


void Account::generateIBAN()
{
	//generates random IBAN
	srand(time(0));
	m_IBAN = new char[29];
	int randX;
	char* cAbrev = new char[4];
	std::cout << "Enter your country's abbreviation ( ex : BG) " << std::endl;
	std::cin >> cAbrev;
	int lenght = strlen(cAbrev);
	for (int i = 0;i < lenght;i++)
	{
		m_IBAN[i] = cAbrev[i];
	}
	for(int i=strlen(cAbrev);i<28;i++)
	{
		randX = rand() % 10;
		m_IBAN[i] = (randX + '0');
	}
	m_IBAN[28] = '\0';
	delete[] cAbrev;
}
