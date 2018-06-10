# Bank

#pragma once

#include "Account.h"
#include<iostream>

class CurrentAccount :
	public Account
{
public:
	CurrentAccount(int amount = 0, const char* ownerId = "0x0", const char* IBAN = "No IBAN");

	void deposit(int amount) { setAmount(getBalance() + amount); }
	bool withdraw(int amount);
	void display() const;
};
