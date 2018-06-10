# Bank

#ifndef BANK_H
#define BANK_H

#include"Customer.h"
#include "Account.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"
#include "PrivilegeAccount.h"
#include<iostream>
#include<vector>
class Bank
{
public:
	Bank(const char* name = "No name", const char* address = "No address",
		std::vector<Customer> customers = std::vector<Customer>(),
		std::vector<Account*> accounts = std::vector<Account*> ());
	Bank(const Bank& b) { CopyFrom(b); }
	Bank& operator=(const Bank& b);
	~Bank() { Destroy(); }

	void setName(const char* name);
	void setAddress(const char* address);

	char* getName() const { return m_name; }
	char* getAddress() const { return m_address; }

	void listCustomers() const { for (int i = 0;i < m_customers.size();i++) m_customers[i].display(); }
	void listAllAccounts() const { for (int i = 0;i < m_accounts.size();i++) m_accounts[i]->display(); }
	void listCustomerAccounts(const char* id) const;

	void addNewCustomer(const Customer& c) { m_customers.push_back(c); }
	void addNewAccount(const Customer& c);
	void addNewAccount(const char* accountType, const char* IBAN, const char* ownerId, int amount);
	void deleteAccount(const char* IBAN);
	void deleteCustomer(const char* id);

	int AccountExists(const char* IBAN) const;
	bool transfer(const char* fromIBAN, const char* toIBAN, int amount);
	bool withdrawFromAccount(const char* IBAN, int amount);
	bool depositToAccount(const char* IBAN, int amount);


	void display() const;
private:
	void Destroy();
	void CopyFrom(const Bank& b);

	char* m_name;
	char* m_address;
	std::vector<Customer> m_customers;
	std::vector<Account*> m_accounts;
};

#endif
