# Bank

#pragma once

#include "Account.h"
#include<iostream>

class PrivilegeAccount :
	public Account
{
public:
	PrivilegeAccount(int amount = 0, const char* ownerId = "0x0",
		const char* IBAN = "No IBAN", double overdraft = 0);

	void setOverdraft(double overdraft) { m_overdraft = overdraft; }
	double getOverdraft() const { return m_overdraft; }

	void deposit(int amount) { setAmount(getBalance() + amount); }
	bool withdraw(int amount);
	void display() const;
private:
	double m_overdraft;
};
