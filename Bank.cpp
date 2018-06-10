# Bank

#include "Bank.h"



Bank::Bank(const char* name, const char* address,
	std::vector<Customer> customers, std::vector<Account*> accounts)
{
	setName(name);
	setAddress(address);
	m_customers = customers;
	m_accounts = accounts;
}


Bank& Bank::operator=(const Bank& b)
{
	if (this != &b)
	{
		Destroy();
		CopyFrom(b);
	}
	return *this;
}

void Bank::Destroy()
{
	delete[] m_name;
	delete[] m_address;
}

void Bank::setAddress(const char* address)
{
	m_address = new char[strlen(address) + 1];
	strcpy_s(m_address, strlen(address) + 1, address);
}


void Bank::setName(const char* name)
{
	m_name = new char[strlen(name) + 1];
	strcpy_s(m_name, strlen(name) + 1, name);
}


void Bank::CopyFrom(const Bank& b)
{
	setName(b.m_name);
	setAddress(b.m_address);
	m_customers = b.m_customers;
	m_accounts = b.m_accounts;
}

void Bank::addNewAccount(const char* accountType, const char* IBAN, const char* ownerId, int amount) 
{
	int customerIndex = -1;
	for (int i = 0;i < m_customers.size();i++)
	{
		if (strcmp(m_customers[i].getId(), ownerId) == 0)
		{
			customerIndex = i;
		}
	}
	bool IbanAlreadyInSystem = false;
	for (int i = 0;i < m_accounts.size();i++)
	{
		if (strcmp(m_accounts[i]->getIBAN(), IBAN) == 0)
		{
			IbanAlreadyInSystem = true;
		}
	}
	if (customerIndex != -1 && IbanAlreadyInSystem == false)
	{
		if (strcmp(accountType, "current") == 0)
		{
			Account* cA = new CurrentAccount(amount, m_customers[customerIndex].getId(), IBAN);
			m_accounts.push_back(cA);
		}
		if (strcmp(accountType, "savings") == 0)
		{
			std::cout << "Enter the interest rate ? " << std::endl;
			double iR;
			std::cin >> iR;
			Account* sA = new SavingsAccount(amount, m_customers[customerIndex].getId(),IBAN);
			((SavingsAccount*)(sA))->setInterestRate(iR);
			m_accounts.push_back(sA);
		}
		if (strcmp(accountType, "privilege") == 0)
		{
			std::cout << "Enter the overdraft ? " << std::endl;
			double oD;
			std::cin >> oD;
			Account* pA = new PrivilegeAccount(amount, m_customers[customerIndex].getId(),IBAN);
			((PrivilegeAccount*)(pA))->setOverdraft(oD);
			m_accounts.push_back(pA);
		}
	}
}


void Bank::addNewAccount(const Customer& c)
{
	int customerIndex = 0;
	for (int i = 0;i < m_customers.size();i++)
	{
		if (strcmp(m_customers[i].getId(), c.getId()) == 0)
		{
			customerIndex = i;
		}
	}
	char* accountType = new char[10];
	int amount;
	std::cout << "What account would you like to open ? (current / savings / privilege) " << std::endl;
	std::cin >> accountType;
	std::cout << "How much money do you want to open that account with ? " << std::endl;
	std::cin >> amount;
	if (strcmp(accountType, "current") == 0)
	{
		Account* cA = new CurrentAccount(amount, m_customers[customerIndex].getId());
		cA->generateIBAN();
		m_accounts.push_back(cA);
	}
	if (strcmp(accountType, "savings") == 0)
	{
		std::cout << "Enter the interest rate ? " << std::endl;
		double iR;
		std::cin >> iR;
		Account* sA = new SavingsAccount(amount, m_customers[customerIndex].getId());
		sA->generateIBAN();
		((SavingsAccount*)(sA))->setInterestRate(iR);
		m_accounts.push_back(sA);
	}
	if (strcmp(accountType, "privilege") == 0)
	{
		std::cout << "Enter the overdraft ? " << std::endl;
		double oD;
		std::cin >> oD;
		Account* pA = new PrivilegeAccount(amount, m_customers[customerIndex].getId());
		pA->generateIBAN();
		((PrivilegeAccount*)(pA))->setOverdraft(oD);
		m_accounts.push_back(pA);
	}
	delete[] accountType;
}

void Bank::deleteAccount(const char* IBAN)
{
	int accountIndex = -1;
	for (int i = 0;i < m_accounts.size();i++)
	{
		if (strcmp(m_accounts[i]->getIBAN(), IBAN) == 0)accountIndex = i;
	}
	if (accountIndex != -1)
	{
		m_accounts.erase(m_accounts.begin() + accountIndex);
	}
	else { std::cout << "Action failed : There is no account with this IBAN"; }
}


void Bank::deleteCustomer(const char* id)
{
	int customerIndex = -1;
	for (int i = 0;i < m_customers.size();i++)
	{
		if (strcmp(m_customers[i].getId(), id) == 0)customerIndex = i;
	}
	if (customerIndex != -1)
	{
		for (int i = 0;i < m_accounts.size();i++)
		{
			if (strcmp(m_customers[customerIndex].getId(),m_accounts[i]->getOwnerId())==0)
			{
				deleteAccount(m_accounts[i]->getIBAN());
			}
		}
		m_customers.erase(m_customers.begin() + customerIndex);

	}
	else { std::cout << "Action failed : There is no customer with this id"; }
}

void Bank::listCustomerAccounts(const char* id) const 
{
	for (int i = 0;i < m_accounts.size();i++)
	{
		if (strcmp(m_accounts[i]->getOwnerId(),id)==0)
		{
			m_accounts[i]->display();
		}	
	}
}

int Bank::AccountExists(const char* IBAN) const
{
	int index = -1;
	for (int i = 0;i < m_accounts.size();i++)
	{
		if (strcmp(m_accounts[i]->getIBAN(), IBAN) == 0)
		{
			index = i;
		}
	}
	return index;
}

bool Bank::transfer(const char* fromIBAN, const char* toIBAN, int amount)
{
	if (AccountExists(fromIBAN) != -1 && AccountExists(toIBAN) != -1)
	{
		if (m_accounts[AccountExists(fromIBAN)]->withdraw(amount) == 1)
			m_accounts[AccountExists(toIBAN)]->deposit(amount);
		else {
			std::cout << "Transfer impossible : lack of funds." << std::endl; 
			return false;
		}
	}
	else
	{
		std::cout << "Error : attempt to transfer from or to a nonexistent account" << std::endl;
		return false;
	}
	std::cout << "Successful transaction" << std::endl;
	return true;
}

bool Bank::withdrawFromAccount(const char* IBAN, int amount)
{
	if (AccountExists(IBAN) != -1)
	{
		if (m_accounts[AccountExists(IBAN)]->withdraw(amount) == 1)
		{
			std::cout << "Action completed" << std::endl;
			return true;
		}
	}
	return false;
}

bool Bank::depositToAccount(const char* IBAN, int amount)
{
	if (AccountExists(IBAN) != -1)
	{
		m_accounts[AccountExists(IBAN)]->deposit(amount);
		return true;
	}
	return false;
}

void Bank::display() const 
{
	std::cout << "The bank's name is " << m_name << ". It's located in " << m_address
		<< "." << std::endl << "Currently there are " << m_customers.size() << " registered customers and "
		<< m_accounts.size() << " opened accounts." << std::endl;
}
