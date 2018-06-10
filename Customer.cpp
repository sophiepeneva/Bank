# Bank

#include "Customer.h"


Customer::Customer(const char* id , const char* name , const char* address)
{
	setId(id);
	setName(name);
	setAddress(address);
}


Customer& Customer::operator=(const Customer& c)
{
	if(this!=&c)
	{
		Destroy();
		CopyFrom(c);
	}
	return *this;
}

Customer::~Customer()
{
	Destroy();
}

void Customer::Destroy()
{
	delete[] m_id;
	delete[] m_name;
	delete[] m_address;
}

void Customer::CopyFrom(const Customer& c)
{
	setId(c.m_id);
	setAddress(c.m_address);
	setName(c.m_name);
}


void Customer::setId(const char* id)
{
	m_id = new char[strlen(id) + 1];
	strcpy_s(m_id, strlen(id) + 1, id);
}


void Customer::setAddress(const char* address)
{
	m_address = new char[strlen(address) + 1];
	strcpy_s(m_address, strlen(address) + 1, address);
}


void Customer::setName(const char* name)
{
	m_name = new char[strlen(name) + 1];
	strcpy_s(m_name, strlen(name) + 1, name);
}


void Customer::display() const
{
	std::cout << m_name << "'s id is : " << m_id << " and their current address is "
		<< m_address << std::endl;
}
