#pragma once
#ifndef _Exception_
#define _Exception_
#include<iostream>
using std::string;
class level {
public:
	level(const char* str);
	level(string str);
	void output(void)const;
private:
	string message;
};

class illegalValue {
public:
	illegalValue(const char* str);
	illegalValue(string str);
	void output(void)const;
private:
	string message;
};

class ReadError {};
#endif