#pragma once
#ifndef _System_
#define _System_
#include"Settings.h"

#include"Clients.h"
#include<algorithm>
#include<vector>
using std::string;
using std::vector;

class System {
public:
	System(void);
	bool read(const string& fileName);
	void write(const string& fileName)const;

	void addClient(const layfolk& _layfolk);
	void addClient(const member& _member);
	void addClient(const honoured_guest& _honoured_guest);
	void deleteClient(int index);
	int search(const wchar_t* _name)const;
	int search(int id)const;
	const buyer* getClient(int index)const;
	void setClient(int index, buyer*& _clinet);

	void add_Book(int pos, int index);
	void delete_Book(int pos, int index);
	void set_pay(int pos);

#ifndef _NOT_SORT_
	void sort_id(void);
	void sort_price(void);
#endif

	bool empty(void)const;
	int size(void)const;
	void clear(void);
private:
	vector<buyer*>res;
};
#endif