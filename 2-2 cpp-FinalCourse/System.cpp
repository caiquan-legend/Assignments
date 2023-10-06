#include "System.hpp"
System::System(void) :tab(true), is_point({ false,0 }) {
	info.read();

	window = new Window;
	table = new Table(info);

	Add = new Button(30, 24, 120, 60, L"添加");
	Delete = new Button(186, 24, 120, 60, L"删除");
	Revise = new Button(342, 24, 120, 60, L"修改");
	Search = new Button(498, 24, 120, 60, L"查找");
	Count = new Button(654, 24, 120, 60, L"统计");
	Exit = new Button(810, 24, 120, 60, L"退出");

	PageUp = new Button(15, 134, 120, 60, L"上一页");
	Save = new Button(15, 254, 120, 60, L"保存");
	Copy = new Button(15, 434, 120, 60, L"生成副本");
	PageDown = new Button(15, 606, 120, 60, L"下一页");
	Hide = new Button(15, 520, 120, 60, L"显示表格");
	showInitButton();
}
System::~System(void) {
	if (window->is_edit())
		if((MessageBox(GetHWnd(), L"是否保存所有操作?", L"退出程序", MB_YESNOCANCEL | MB_ICONQUESTION)) == IDYES)
			info.write();
	
	delete window, table,
		Add, Delete, Revise, Search, Count, Exit,
		Save, Copy, PageUp, PageDown;
}

void System::MainLoop(void) {
	ExMessage msg;
	while (1) {
		msg = getmessage();
		if (!tab) {
			if (PageUp->state(msg))table->pageUp();
			else if (PageDown->state(msg))table->pageDown();
		}
		if (Add->state(msg))AddEmployee();
		else if (Delete->state(msg))DeleteEmployee();
		else if (Revise->state(msg))ReviseEmployee();
		else if (Search->state(msg))SearchEmployee();
		else if (Count->state(msg))CountEmployee();
		else if (Exit->state(msg))_Exit();
		else if (Save->state(msg))SaveData();
		else if (Copy->state(msg))CopyData();
		else if (Hide->state(msg))HideTable();
	}
}

void System::_Exit(void) {
	if (window->close()) 
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void System::HideTable(void) {
	if (tab) {
		table->show();
		PageUp->show(), PageDown->show();
		Hide->setText(L"隐藏表格");
	}else {
		window->flash();
		showInitButton();
		Hide->setText(L"显示表格");
	}Hide->show(), tab ^= true, is_point.first = false;
}

void System::showInitButton(void)const {
	Add->show(), Delete->show(), Revise->show(), Search->show(), Count->show(), Exit->show();
	Save->show(), Copy->show(), Hide->show();
}