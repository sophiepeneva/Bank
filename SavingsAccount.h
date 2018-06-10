# Bank

#pragma once

#include "Account.h"
#include<iostream>

class SavingsAccount :
	public Account
{
public:
	SavingsAccount(int amount = 0, const char* ownerId = "0x0",
		const char* IBAN = "No IBAN", double interestRate = 0);

	void setInterestRate(double interestRate) { m_interestRate = interestRate; }
	double getInterestRate() const { return m_interestRate; }

	void deposit(int amount) { setAmount(getBalance() + amount); }
	bool withdraw(int amount);
	void display() const;
private:
	double m_interestRate;
};
