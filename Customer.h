# Bank

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<iostream>

class Customer
{
public:
	Customer(const char* id = "0x0", const char* name = "No name", const char* address = "No address");
	~Customer();
	Customer(const Customer& c) { CopyFrom(c); }
	Customer& operator=(const Customer& c);

	void setId(const char* id);
	void setAddress(const char* address);
	void setName(const char* name);

	char* getId() const { return m_id; }
	char* getName() const { return m_name; }
	char* getAddress() const { return m_address; }

	void display() const;
private:
	void Destroy();
	void CopyFrom(const Customer& c);

	char* m_id;
	char* m_name;
	char* m_address;
};

#endif
