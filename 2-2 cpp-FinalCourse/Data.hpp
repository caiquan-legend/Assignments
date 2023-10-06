#ifndef _Data_
#define _Data_
#include "Employee.hpp"
#include<sstream>
#include<map>

using std::map;
using std::pair;
//typedef std::pair<std::wstring, Employee> pir;

class Data {
public:
	void read(std::string = "Data.txt");		//读取数据
	void write(std::string = "Data.txt")const;	//写出数据

	bool search(int id)const;					//id查找
	int search(std::wstring)const;				//姓名查找
	void insert(pair<int, Employee>);			//id插入
	void insert(pair<std::wstring, Employee>);	//姓名插入
	void erase(int id);							//id删除
	void erase(std::wstring);					//姓名删除
	bool edit(pair<int, pair<int,std::wstring>>);	//修改数据信息
	Employee get(int id)const;					//返回指定id员工数据

	int size(void)const;	//员工总数
	bool empty(void)const;	//数据是否为空
	map<unsigned, Employee>::const_iterator begin(void)const;//迭代器首
	map<unsigned, Employee>::const_iterator end(void)const;	//迭代器尾
private:
	//id前缀树(红黑树)
	map<unsigned, Employee>u_data;
	//姓名前缀树(红黑树)
	map<std::wstring, Employee>n_data;
};
#endif