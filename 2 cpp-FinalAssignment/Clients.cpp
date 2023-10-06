#define _CRT_SECURE_NO_WARNINGS 1
#include "Clients.h"
#include "Exception.h"
#include<sstream>
#include<vector>

using std::wcout;
using std::cin;
using std::cout;
using std::endl;
using std::copy;
using std::setw;
using std::wstring;
using std::wstringstream;

extern std::vector<Book>_data_;
extern int _size_;

buyer::buyer(void) :name(), address(), pay(0), id(0), type(err_type) { book = new int[_size_ + 1](); }
buyer::buyer(wstring _name, wstring _address, int _id, double _pay) :id(_id), pay(_pay), type(err_type) {
	wcsncpy(name, _name.c_str(), MAX_SIZE); wcsncpy(address, _address.c_str(), MAX_SIZE);
	book = new int[_size_ + 1]();
}
buyer::~buyer(void) { delete[]book; }
wstring buyer::getName(void)const { 
	return name;
}

wstring buyer::getAddress(void)const { 
	return address; 
}

double buyer::getPay(void)const { 
	return pay; 
}

int buyer::getID(void)const { 
	return id;
}

int buyer::getNum(int index)const { 
	return book[index]; 
}

void buyer::showBooks(ostream& os)const {
	
}

void buyer::setID(int _id) { 
	id = _id;
}

void buyer::add_Book(int index) {
	book[index]++;
}

void buyer::delete_Book(int index) {
	if (book[index] > 0)book[index]--;
}



layfolk::layfolk(wstring _name, wstring _address, int _id, double _pay) :
	buyer(_name, _address, _id, _pay) { type = _layfolk_; }
layfolk::layfolk(const layfolk& _layfolk) {
	wcsncpy(name, _layfolk.name, MAX_SIZE); wcsncpy(address, _layfolk.address, MAX_SIZE);
	pay = _layfolk.pay; id = _layfolk.id; type = _layfolk.type;
	book = new int[_size_ + 1];
	copy(_layfolk.book, _layfolk.book + _size_ + 1, book);
}

void layfolk::display(ostream& os)const {
	os << "购书人姓名:" << setw(8) << std::left <<name;
	os << "\t购书人为普通客户" << endl;
	os << "购书人编号:" << setw(4) << std::left << id;
	os << "\t地址:" << setw(8) << address << endl;
	os << "以下是该客户购买的图书:" << endl; showBooks();
}

void layfolk::setPay(void) { 
	double res = 0;
	for (int i = 1; i <= _size_; ++i)
		if (book[i]) res += book[i] * _data_[i].getPrice();
	pay = res;
}

void layfolk::clear(void) { buyer::~buyer(); }

wstring layfolk::get_typeName(void)const {
	return wstring(L"普通客户");
}

void layfolk::setData(wstringstream& is) {
	is >> name >> address;
}

bool layfolk::operator==(const wchar_t* tmp)const {
	return wstring(name) == tmp;
}
bool layfolk::operator==(int _id)const {
	return id == _id;
}

bool layfolk::operator<=(const layfolk& lay)const {
	return id <= lay.id;
}
bool layfolk::operator>=(const layfolk& lay)const {
	return pay >= lay.pay;
}

bool layfolk::read(FILE*& is) {
	try {
		fwscanf(is, L"%ls %ls\n", name, address);
		for (int i = 1; i <= _size_; ++i)fwscanf(is, L"%d ", &book[i]);
		setPay();
	}catch (...) { return false; }
	return true;
}

void layfolk::write(FILE*& os)const {
	fwprintf(os, L"%d %s %s\n", type, name, address);
	for (int i = 1; i <= _size_; ++i)fwprintf(os, L"%d ", book[i]);
	fwprintf(os, L"\n");
}



member::member(wstring _name, wstring _address, int _id, double _pay, int grade) :
	buyer(_name, _address, _id, _pay), leaguer_grade(grade) { type = _member_; }
member::member(const member& _member) {
	wcsncpy(name, _member.name, MAX_SIZE); wcsncpy(address, _member.address, MAX_SIZE);
	pay = _member.pay; id = _member.id; type = _member.type; leaguer_grade = _member.leaguer_grade;
	book = new int[_size_ + 1];
	copy(_member.book, _member.book + _size_ + 1, book);
}

void member::display(ostream& os)const {
	os << "购书人姓名:" << setw(8) << std::left << name;
	os << "\t购书人为会员,级别:" << setw(4) << std::left << leaguer_grade << endl;
	os << "购书人编号:" << setw(4) << std::left << id;
	os << "\t地址:" << setw(8) << address << endl;
	os << "以下是该客户购买的图书:" << endl; showBooks();
}

void member::setPay(void) {
	double  res = 0, rate[6] = { 0,0.95,0.9,0.85,0.8,0.7 };
	for (int i = 1; i <= _size_; ++i)
		if (book[i])res += book[i] * _data_[i].getPrice();
	pay = res * rate[leaguer_grade];
}

void member::clear(void) { buyer::~buyer(); }

int member::getGrade(void)const { return leaguer_grade; }

wstring member::get_typeName(void)const {
	switch (leaguer_grade) {
	case 1:return wstring(L"1级会员");
	case 2:return wstring(L"2级会员");
	case 3:return wstring(L"3级会员");
	case 4:return wstring(L"4级会员");
	case 5:return wstring(L"5级会员");
	}
}

void member::setData(wstringstream& is) {
	is >> name >> address >> leaguer_grade;
}

bool member::operator==(const wchar_t* tmp)const {
	return wstring(name) == tmp;
}
bool member::operator==(int _id)const {
	return id == _id;
}

bool member::operator<=(const member& mem)const {
	return id <= mem.id;
}
bool member::operator>=(const member& mem)const {
	return pay >= mem.pay;
}

bool member::read(FILE*& is) {
	try {
		fwscanf(is, L"%s %s %d\n", name, address, &leaguer_grade);
		for (int i = 1; i <= _size_; ++i)fwscanf(is, L"%d ", &book[i]);
		setPay();
	}catch (...) { return false; }
	return true;
}

void member::write(FILE*& os)const {
	fwprintf(os, L"%d %s %s %d\n", type, name, address, leaguer_grade);
	for (int i = 1; i <= _size_; ++i)fwprintf(os, L"%d ", book[i]);
	fwprintf(os, L"\n");
}



honoured_guest::honoured_guest(wstring _name, wstring _address, int _id, double _pay, double rate) :
	buyer(_name, _address, _id, _pay), discount_rate(rate) { type = _honoured_guest_; }
honoured_guest::honoured_guest(const honoured_guest& _honoured_guest) {
	wcsncpy(name, _honoured_guest.name, MAX_SIZE); wcsncpy(address, _honoured_guest.address, MAX_SIZE);
	pay = _honoured_guest.pay; id = _honoured_guest.id; type = _honoured_guest.type;
	discount_rate = _honoured_guest.discount_rate;
	book = new int[_size_ + 1];
	copy(_honoured_guest.book, _honoured_guest.book + _size_ + 1, book);
}

void honoured_guest::display(ostream& os)const {
	os << "购书人姓名:" << setw(8) << std::left << name;
	os << "\t购书人为贵宾!折扣率为" << setw(4) << std::left << discount_rate << endl;
	os << "购书人编号:" << setw(4) << std::left << id;
	os << "\t地址:" << setw(8) << address << endl;
	os << "以下是该客户购买的图书:" << endl; showBooks();
}

void honoured_guest::setPay(void) {
	double res = 0;
	for (int i = 1; i <= _size_; ++i)
		if (book[i]) res += book[i] * _data_[i].getPrice();
	pay = res * (100 - discount_rate) / 100;
}

void honoured_guest::clear(void) { buyer::~buyer(); }

double honoured_guest::getRate(void)const { return discount_rate; }

wstring honoured_guest::get_typeName(void)const {
	return wstring(L"贵宾");
}

void honoured_guest::setData(wstringstream& is) {
	is >> name >> address >> discount_rate;
}

bool honoured_guest::operator==(const wchar_t* tmp)const {
	return wstring(name) == tmp;
}
bool honoured_guest::operator==(int _id)const {
	return id == _id;
}
bool honoured_guest::operator<=(const honoured_guest& hou)const {
	return id <= hou.id;
}
bool honoured_guest::operator>=(const honoured_guest& hou)const {
	return pay >= hou.pay;
}

bool honoured_guest::read(FILE*& is) {
	try {
		fwscanf(is, L"%s %s %lf\n", name, address, &discount_rate);
		for (int i = 1; i <= _size_; ++i)fwscanf(is, L"%d ", &book[i]);
		setPay();
	}catch (...) { return false; }
	return true;
}

void honoured_guest::write(FILE*& os)const {
	fwprintf(os, L"%d %s %s %.2lf\n", type, name, address, discount_rate);
	for (int i = 1; i <= _size_; ++i)fwprintf(os, L"%d ", book[i]);
	fwprintf(os, L"\n");
}