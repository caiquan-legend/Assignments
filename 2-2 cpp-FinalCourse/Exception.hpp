#ifndef _Exception_
#define _Exception_
#include "Settings.hpp"
//基类异常
class Error {
public:
	Error(std::wstring mess = L"");
#ifdef _NOT_MULTIERROR_
	void error(void)const;
#endif
#ifndef _NOT_MULTIERROR_
	virtual void error(void)const = 0;
#endif
protected:
	std::wstring message;
};
class NumberError : public Error {
public:
	NumberError(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class NumberExist : public Error {
public:
	NumberExist(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class NameEmpty : public Error {
public:
	NameEmpty(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class NameExist : public Error {
public:
	NameExist(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class SexError : public Error {
public:
	SexError(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class PhoneError : public Error {
public:
	PhoneError(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class PhoneEmpty : public Error {
public:
	PhoneEmpty(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class DepartmentError : public Error {
public:
	DepartmentError(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class DepartmentEmpty : public Error {
public:
	DepartmentEmpty(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class SalaryError : public Error {
public:
	SalaryError(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class SalaryEmpty : public Error {
public:
	SalaryEmpty(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
class SalaryInvalid :public Error {
public:
	SalaryInvalid(void);
#ifndef _NOT_MULTIERROR_
	void error(void)const;
#endif
};
#endif