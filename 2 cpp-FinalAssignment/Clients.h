#ifndef _Clients_
#define _Clients_
#include"Books.h"
#include<iostream>
#include<iomanip>

using std::wstring;
using std::wstringstream;

const int MAX_SIZE = 10;

class buyer {
public:
	buyer(void);
	buyer(wstring n, wstring a, int _id, double _pay);
	~buyer(void);
	wstring getName(void)const;
	wstring getAddress(void)const;
	double getPay(void)const;
	int getID(void)const;
	int getNum(int index)const;
	void showBooks(ostream& os = cout)const;
	void setID(int _id);

	void add_Book(int index);
	void delete_Book(int index);

	virtual bool read(FILE*& is) = 0;
	virtual void write(FILE*& os)const = 0;

	virtual void display(ostream& os = cout)const = 0;
	virtual void setData(wstringstream& is) = 0;
	virtual void setPay(void) = 0;
	virtual void clear(void) = 0;
	virtual wstring get_typeName(void)const = 0;
	virtual bool operator==(const wchar_t* tmp)const = 0;
	virtual bool operator==(int id)const = 0;

	enum Client_type { err_type, _layfolk_, _member_, _honoured_guest_ };
	Client_type getType(void)const { return type; }
protected:
	wchar_t name[MAX_SIZE];
	wchar_t address[MAX_SIZE];
	double pay;
	int id;
	int* book;
	Client_type type;
};

class layfolk :public buyer {
public:
	layfolk(wstring _name = wstring(), wstring _address = wstring(), int _id = 1, double _pay = 0);
	layfolk(const layfolk& _layfolk);
	void display(ostream& os = cout)const;
	void setPay(void);
	void clear(void);

	void setData(wstringstream& is);
	wstring get_typeName(void)const;

	bool read(FILE*& is);
	void write(FILE*& os)const;

	bool operator==(const wchar_t* tmp)const;
	bool operator==(int id)const;
	bool operator<=(const layfolk&)const;
	bool operator>=(const layfolk&)const;
};

class member :public buyer {
public:
	member(wstring _name = wstring(), wstring _address = wstring(), int _id = 1, double _pay = 0, int _grade = 0);
	member(const member& _member);
	void display(ostream& os = cout)const;
	void setPay(void);
	void clear(void);

	int getGrade(void)const;
	void setData(wstringstream& is);
	wstring get_typeName(void)const;

	bool read(FILE*& is);
	void write(FILE*& os)const;

	bool operator==(const wchar_t* tmp)const;
	bool operator==(int id)const;
	bool operator<=(const member&)const;
	bool operator>=(const member&)const;
private:
	int leaguer_grade;
};

class honoured_guest :public buyer {
public:
	honoured_guest(wstring _name = wstring(), wstring _address = wstring(), int _id = 1, double _pay = 0, double _rate = 0);
	honoured_guest(const honoured_guest& _honoured_guest);
	void display(ostream& os = cout)const;
	void setPay(void);
	void clear(void);

	double getRate(void)const;
	void setData(wstringstream& is);
	wstring get_typeName(void)const;

	bool read(FILE*& is);
	void write(FILE*& os)const;

	bool operator==(const wchar_t* tmp)const;
	bool operator==(int id)const;
	bool operator<=(const honoured_guest&)const;
	bool operator>=(const honoured_guest&)const;
private:
	double discount_rate;
};
#endif