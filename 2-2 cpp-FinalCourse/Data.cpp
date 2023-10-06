#define _CRT_SECURE_NO_WARNINGS
#include "Data.hpp"
using std::wstring;

Employee::Employee(void): name(L""), phone(L""), number(1), salary(INT_MIN), sex(true), department(INT_MIN) {}
//Employee::Employee(wstring _name, wstring _phone, unsigned num, unsigned _salary, bool _sex, Department _Admin)
int Data::size(void)const { return u_data.size(); }
bool Data::empty(void)const { return u_data.empty(); }

void Data::read(std::string file) {
	FILE* fp;
	fopen_s(&fp, file.c_str(), "r, ccs=utf-8");
	if (!fp) {
		if (MessageBox(GetHWnd(), L"未读取到文件\"Data.txt\",是否重新生成?", L"询问",
			MB_YESNO | MB_ICONQUESTION) == IDYES) {
			fopen_s(&fp, file.c_str(), "w, ccs=utf-8"), fclose(fp);
			return;
		}else {
			MessageBox(GetHWnd(), L"\"Data.txt\"文件打开失败.", L"错误", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}

	int size; fwscanf(fp, L"%*s %d ", &size);
	Employee tmp;
	for (int i = 1; i <= size; ++i) {
		fwscanf(fp, L"%*s %u, %*s %s %*s %d, %*s %s %*s %d, %*s %lf ",
			&tmp.number, tmp.name, &tmp.sex, tmp.phone, &tmp.department, &tmp.salary);
		u_data[tmp.number] = tmp, n_data[tmp.name] = tmp;
		count_num[tmp.department].first++, count_num[tmp.department].second += tmp.salary;
	}fclose(fp);
}

void Data::write(std::string file)const {
	FILE* fp;
	fopen_s(&fp, file.c_str(), "w, ccs=utf-8");
	fwprintf(fp, L"员工总数: %d\n", size());

	for (auto& it : u_data)fwprintf(fp, L"工号: %u, 姓名: %s 性别: %d, 电话: %s 科室: %d, 工资: %lf\n",
		it.second.number, it.second.name, it.second.sex,
		it.second.phone, it.second.department, it.second.salary);

	fclose(fp);
}


bool Data::search(int id)const {
	return u_data.count(id);
}
int Data::search(wstring name)const {
	return n_data.count(name) ? n_data.find(name)->second.number : 0;
}

void Data::insert(pair<int,Employee>val) {
	u_data[val.first] = val.second;
	n_data[val.second.name] = val.second;
}
void Data::insert(pair<wstring, Employee>val) {
	n_data[val.first] = val.second;
	u_data[val.second.number] = val.second;
}

void Data::erase(int id) {
	n_data.erase(u_data.find(id)->second.name);
	u_data.erase(id);
}
void Data::erase(wstring name) {
	u_data.erase(n_data.find(name)->second.number);
	n_data.erase(name);
}

bool Data::edit(pair<int, pair<int, wstring>> pick) {
	int choice = pick.first;
	int id = pick.second.first;
	wstring& temp = pick.second.second;
	switch (choice) {
	case 1: {
		int num = _wtoi(temp.c_str());
		if (u_data.count(num)) {
			MessageBox(GetHWnd(), L"该工号已存在,修改失败", L"提示", MB_OK | MB_ICONINFORMATION);
			return false;
		} n_data[u_data[id].name].number = num, u_data[id].number = num, u_data[num] = u_data[id], u_data.erase(id);
	}break;
	case 2: {
		wchar_t _name[MAX_LENGTH];
		wcsncpy(_name, temp.c_str(), MAX_LENGTH);
		if (n_data.count(_name)) {
			MessageBox(GetHWnd(), L"该姓名已经存在,修改失败", L"提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}wcsncpy(n_data[u_data[id].name].name, _name, MAX_LENGTH), 
			n_data[_name] = n_data[u_data[id].name], n_data.erase(u_data[id].name),
			wcsncpy(u_data[id].name, _name, MAX_LENGTH);
	}break;
	case 3: {
		int flag = _wtoi(temp.c_str());
		if (flag < 0 || flag > 1) {
			MessageBox(GetHWnd(), L"性别应输入1/0(男/女)!", L"提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}u_data[id].sex = n_data[u_data[id].name].sex = flag;
	}break;
	case 4: {
		wcsncpy(u_data[id].phone, temp.c_str(), MAX_LENGTH),
		wcsncpy(n_data[u_data[id].name].phone, temp.c_str(), MAX_LENGTH);
	}break;
	case 5: {
		int depart = _wtoi(temp.c_str());
		if (depart < 0 || depart > 8) {
			MessageBox(GetHWnd(), L"该科室编号不存在,修改失败", L"提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}count_num[u_data[id].department].first--, count_num[u_data[id].department].second -= u_data[id].salary,
			u_data[id].department = depart, n_data[u_data[id].name].department = depart,
			count_num[depart].first++, count_num[depart].second += u_data[id].salary;
	}break;
	case 6: {
		double sal = _wtof(temp.c_str());
		u_data[id].salary = sal, n_data[u_data[id].name].salary = sal,
			count_num[u_data[id].department].second += sal - u_data[id].salary;
	}break;
	}return true;
}

Employee Data::get(int id)const {
	return u_data.find(id)->second;
}


map<unsigned, Employee>::const_iterator Data::begin(void)const {
	return u_data.begin();
}
map<unsigned, Employee>::const_iterator Data::end(void)const {
	return u_data.end();
}