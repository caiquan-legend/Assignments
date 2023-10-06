#include "Exception.h"
using std::cout;
using std::endl;

level::level(const char* str) :message(str) {}
level::level(string str) :message(str) {}
void level::output(void)const { cout << message << endl; }



illegalValue::illegalValue(const char* str) :message(str) {}
illegalValue::illegalValue(string str) :message(str) {}
void illegalValue::output(void)const { cout << message << endl; }