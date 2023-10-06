#include "System.hpp"
#include "Exception.hpp"
#include<sstream>
#include<cwctype>
using std::iswdigit;
using std::wstringstream;
void operator>>(wstringstream& is, Employee& pos);
void System::AddEmployee(void) {
	wchar_t inputBox[3 * MAX_LENGTH];
	if (!InputBox(inputBox, 3 * MAX_LENGTH,
		L"请按照\"工号 姓名 性别 电话 科室 工资\"的格式输入数据:\n性别:1/0(男/女), 科室:编号0-8\n\
0:行政部 1:财务部 2:人力资源部 3:市场部 \n4:销售部5:技术部 6:质检部 7:生产部 8:研发部",
		L"添加员工", nullptr, 0, 0, false))return;
	wstringstream format(inputBox); Employee temp; 
	try {
		format >> temp;
		if(info.search(temp.number))throw NumberExist();
		if (info.search(temp.name))throw NameExist();
	}
	catch (NumberError e) { e.error(); return; }
	catch (NumberExist e) { e.error(); return; }
	catch (NameEmpty e) { e.error(); return; }
	catch (NameExist e) { e.error(); return; }
	catch (SexError e) { e.error(); return; }
	catch (PhoneError e) { e.error(); return; }
	catch (PhoneEmpty e) { e.error(); return; }
	catch (DepartmentError e) { e.error(); return; }
	catch (DepartmentEmpty e) { e.error(); return; }
	catch (SalaryError e) { e.error(); return; }
	catch (SalaryEmpty e) { e.error(); return; }
	catch (SalaryInvalid e) { e.error(); return; }

	info.insert({ temp.name,temp }), window->edit();
	count_num[temp.department].first++, count_num[temp.department].second += temp.salary;
	if (tab)HideTable(); else table->show();
}

void System::DeleteEmployee(void) {
	if (!is_point.first)
		MessageBox(GetHWnd(), L"请先进行查找以选中员工!", L"提示", MB_OK | MB_ICONINFORMATION);
	else if (MessageBox(GetHWnd(), L"确定要删除此员工吗?", L"确定删除", MB_YESNO | MB_ICONQUESTION) == IDYES)
		info.erase(is_point.second), window->edit(), window->flash(), showInitButton();
}

void System::ReviseEmployee(void) {
	if (!is_point.first) {
		MessageBox(GetHWnd(), L"请先进行查找以选中员工!", L"提示", MB_OK | MB_ICONINFORMATION);
		return;
	}wchar_t inputBox[2];
	if (InputBox(inputBox, 2,
		L"请输入修改项:1-6:\n(1:工号 2:姓名 3:性别 4: 电话 5: 科室 6:工资)", L"修改员工信息", nullptr, 0, 0, false)) {
		int it = _wtoi(inputBox);
		if (it > 6 || it < 1) {
			MessageBox(GetHWnd(), L"输入不符合要求,修改失败.", L"提示", MB_OK | MB_ICONINFORMATION);
			return;
		}
		wchar_t choice[7][3]{ L"",L"工号",L"姓名",L"性别",L"电话",L"科室",L"工资" };
		wstring tip(L"请输入修改后的"); tip += choice[it];
		wstring title(L"修改"); title += choice[it];
		wchar_t format[MAX_LENGTH];
		if (InputBox(format, MAX_LENGTH, tip.c_str(), title.c_str(), nullptr, 0, 0, false)) {
			if (info.edit({ it,{is_point.second, format} }))
				if (it == 1)is_point.second = _wtoi(format);
		}
	}table->showSearchTable(is_point.second), window->edit();
}

void System::SearchEmployee(void) {
	wchar_t inputBox[MAX_LENGTH];
	if (!InputBox(inputBox, MAX_LENGTH, L"请输入员工id或员工姓名进行查找", L"查找员工", nullptr, 0, 0, false)) return;
	if (!tab)HideTable();
	int num = _wtoi(inputBox);
	if (!num) {
		if (!info.search(inputBox)) {
			MessageBox(GetHWnd(), L"未找到员工", L"提示", MB_OK | MB_ICONINFORMATION);
			return;
		}is_point.second = info.search(inputBox);
	}else {
		if (!info.search(num)) {
			MessageBox(GetHWnd(), L"未找到员工", L"提示", MB_OK | MB_ICONINFORMATION);
			return;
		}is_point.second = num;
	}table->showSearchTable(is_point.second), is_point.first = true;
}

void System::CountEmployee(void) {
	if(tab)HideTable();
	table->showCountTable();
}

void System::SaveData(void) {
	info.write("Data.txt");
	MessageBox(GetHWnd(), L"保存成功.", L"提示", MB_OK | MB_ICONINFORMATION);
}

void System::CopyData(void) {
	FILE* fp;
	fopen_s(&fp, "Data(1).txt", "r, ccs=utf-8");
	if (!fp) {
		info.write("Data(1).txt");
		MessageBox(GetHWnd(), L"副本\"Data(1).txt\"生成成功!", L"提示", MB_OK | MB_ICONINFORMATION);
	}else if (MessageBox(GetHWnd(), L"副本\"Data(1).txt\"已经存在,是否覆盖?", L"询问",
		MB_YESNO | MB_ICONQUESTION) == IDYES) fclose(fp), info.write("Data(1).txt");
}

void operator>>(std::wstringstream& is, Employee& pos) {
	wstring temp; is >> temp;
	//工号数字检测
	for (auto c : temp)if (!iswdigit(c))
		throw NumberError();
	pos.number = _wtoi(temp.c_str());

	//姓名空检测
	is >> pos.name >> temp;
	if (!wcscmp(pos.name, L""))
		throw NameEmpty();

	//性别区间检测
	if (temp != L"0" && temp != L"1")
		throw SexError();

	//电话号数字检测与空检测
	is >> pos.phone >> temp;
	for (auto c : pos.phone)if (!iswdigit(c))
		throw PhoneError();
	if (!wcscmp(pos.phone, L""))
		throw PhoneEmpty();

	//部门区间检测
	for (wchar_t c : temp)if (c < L'0' || c > L'8')
		throw DepartmentError();
	pos.department = _wtoi(temp.c_str()); is >> temp;

	//工资数字检测与非负检测
	for (wchar_t c : temp)if (!iswdigit(c) && c != L'.')
		throw SalaryError();
	pos.salary = _wtof(temp.c_str());
	if (pos.salary < 0)throw SalaryInvalid();
}