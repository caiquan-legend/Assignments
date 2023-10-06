#define _CRT_SECURE_NO_WARNINGS
#include "Books.h"
#include<iomanip>
using std::wcsncpy;
using std::setw;
using std::cout;
using std::endl;

Book::Book(void) :id(), name(), author(), publish(), price(0) {}
Book::Book(wstring _id, wstring _name, wstring _author, wstring _pub, double _price) :price(_price) {
	wcsncpy(id, _id.c_str(), MAX_LENGTH); wcsncpy(name, _name.c_str(), MAX_LENGTH);
	wcsncpy(author, _author.c_str(), MAX_LENGTH); wcsncpy(publish, _pub.c_str(), MAX_LENGTH);
}



void Book::display(ostream& os)const {
	os << "书号:" << setw(8) << std::left << id;
	os << "\t书名:" << setw(8) << std::left << name;
	os << "\t作者:" << setw(8) << std::left << author << endl;
	os << "出版社:" << setw(8) << std::left << publish;
	os << "\t定价:" << setw(8) << std::left << price << endl;
}



const wchar_t* Book::getID(void)const {
	const wchar_t* pos = id; return pos;
}

const wchar_t* Book::getName(void)const {
	const wchar_t* pos = name; return pos;
}

const wchar_t* Book::getAuthor(void)const {
	const wchar_t* pos = author; return pos; 
}

const wchar_t* Book::getPub(void)const {
	const wchar_t* pos = publish; return pos;
}

double Book::getPrice(void)const {
	return price;
}



bool Book::operator>(const Book& tmp)const {
	return price > tmp.price;
}

bool Book::operator<=(const Book& tmp)const {
	int a = _wtoi(id), b = _wtoi(tmp.id);
	return a <= b;
}

ostream& operator<<(ostream& os, const Book& val) {
	val.display(os); return os;
}