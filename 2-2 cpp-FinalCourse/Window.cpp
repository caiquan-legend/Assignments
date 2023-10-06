#include "Window.hpp"
Window::Window(int width, int height) :
	Component(0, 0, width, height),
	isEdit(false),
	hwnd(initgraph(width, height, EX_NOCLOSE)) //以无控制台模式打开窗口
{
	//样式设置，加载图片
	SetWindowText(hwnd, L"公司员工信息管理系统");
	setbkcolor(WHITE);
	cleardevice();
	loadimage(nullptr, _Pic, 960, 720);
	
	//设置字号
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
}

void Window::show(void)const {
	ShowWindow(hwnd, SW_SHOW);
}

void Window::edit(void) {
	isEdit = true;
}

bool Window::is_edit(void)const {
	return isEdit;
}

void Window::flash(void)const {
	cleardevice();
	loadimage(nullptr, _Pic, 960, 720);
}

bool Window::close(void) {
	if (isEdit) {
		int id = MessageBox(GetHWnd(), L"是否保存所有操作?", L"退出程序", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES) {
			closegraph();
		}return true;
	}else return true;
	return false;
}