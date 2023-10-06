#ifndef _EMPLOYEE_
#define _EMPLOYEE_

#include "Settings.hpp"
#ifndef _NOT_EMPLOYEE_
#include<iostream>
using std::wstring;
#endif

const int MAX_LENGTH = 16;
struct Employee {
	Employee(void);
	enum class Department { _Admin, _Finance, _HR, _Market, _Sale, _Tech, _Production, _QI, _Design };
#ifndef _NOT_EMPLOYEE_
	unsigned getNumber(void)const;
	double getSalary(void)const;
	wstring getName(void)const;
	wstring getPhone(void)const;
	bool getSex(void)const;
	Department getDep(void)const;
#endif
	
	wchar_t name[MAX_LENGTH];	//姓名
	wchar_t phone[MAX_LENGTH];	//电话号
	unsigned number;			//工号
	double salary;				//工资
	int department;				//部门(枚举)
	bool sex;					//性别
};
#endif