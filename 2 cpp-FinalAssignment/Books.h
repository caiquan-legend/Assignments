#ifndef _Books_
#define _Books_
#include<iostream>
#include<fstream>
using std::wstring;
using std::ostream;
using std::cout;

const int MAX_LENGTH = 25;
class Book {
public:
	friend void load_data(void);
	friend ostream& operator<<(ostream& os, const Book&);
	Book(void);
	Book(wstring _id, wstring _name, wstring _author, wstring _pub, double _price);

	void display(ostream& os = cout)const;

	const wchar_t* getID(void)const;
	const wchar_t* getName(void)const;
	const wchar_t* getAuthor(void)const;
	const wchar_t* getPub(void)const;
	double getPrice(void)const;

	bool operator>(const Book&)const;
	bool operator<=(const Book&)const;
protected:
	wchar_t id[MAX_LENGTH];
	wchar_t name[MAX_LENGTH];
	wchar_t author[MAX_LENGTH];
	wchar_t publish[MAX_LENGTH];
	double price;
};
ostream& operator<<(ostream& os, const Book&);
#endif