# Bank

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<iostream>
#include <stdlib.h>
#include <time.h>  

class Account
{
public:
	Account(int amount = 0, const char* ownerId = "0x0", const char* IBAN = "No IBAN");
	Account(const Account& a) { CopyFrom(a); }
	Account& operator=(const Account& a);
	virtual ~Account() { Destroy(); }

	int getBalance() const { return m_amount; }
	char* getIBAN() const { return m_IBAN; }
	char* getOwnerId() const { return m_ownerId; }

	void setAmount(int amount) { m_amount = amount; }
	void setIBAN(const char* IBAN);
	void setOwnerID(const char* ownerId);

	virtual void deposit(int amount) = 0;
	virtual bool withdraw(int amount) = 0;
	virtual void display() const = 0;

	void generateIBAN();

private:
	void Destroy();
	void CopyFrom(const Account& a);

	char* m_IBAN;
	int m_amount;
	char* m_ownerId;
};

#endif
