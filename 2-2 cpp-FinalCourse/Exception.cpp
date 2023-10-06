#include "Exception.hpp"
Error::Error(std::wstring _message) :message(_message) {}
NumberError::NumberError(void) :Error(L"工号输入格式错误.(全为数字)") {}
NumberExist::NumberExist(void) :Error(L"该工号已存在") {}
NameEmpty::NameEmpty(void) :Error(L"姓名不能为空") {}
NameExist::NameExist(void) :Error(L"该姓名已存在") {}
SexError::SexError(void) :Error(L"性别应输入1/0(男/女)!") {}
PhoneError::PhoneError(void) :Error(L"电话号输入格式错误.(全为数字)") {}
PhoneEmpty::PhoneEmpty(void) :Error(L"电话号不能为空!") {}
DepartmentError::DepartmentError(void) :
	Error(L"科室编号应为0-8!\n0:行政部 1:财务部 2:人力资源部 3:市场部 4:销售部\n5:技术部 6:质检部 7:生产部 8:研发部") {}
DepartmentEmpty::DepartmentEmpty(void) :Error(L"部门不能为空!") {}
SalaryError::SalaryError(void) :Error(L"工资输入格式错误.") {}
SalaryEmpty::SalaryEmpty(void) :Error(L"工资不能为空!") {}
SalaryInvalid::SalaryInvalid(void) :Error(L"工资不能为负数!") {}

#ifdef _NOT_MULTIERROR_
void Error::error(void)const{ MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
#endif
#ifndef _NOT_MULTIERROR_
void NumberError::error(void)const{ MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void NumberExist::error(void)const{ MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void NameEmpty::error(void)const{ MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void NameExist::error(void)const{ MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void SexError::error(void)const{ MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void PhoneError::error(void)const { MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void PhoneEmpty::error(void)const { MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void DepartmentError::error(void)const{ MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void DepartmentEmpty::error(void)const { MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION; }
void SalaryError::error(void)const{ MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
void SalaryEmpty::error(void)const { MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION; }
void SalaryInvalid::error(void)const { MessageBox(GetHWnd(), message.c_str(), L"提示", MB_OK | MB_ICONINFORMATION); }
#endif