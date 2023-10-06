#ifndef _Button_
#define _Button_
#include"Component.h"
#include<iostream>
using std::wstring;

class Button : public Component {
public:
	Button(int x = 0, int y = 0, int width = 100, int height = 60, const wstring& _text = L"按钮", int size = 0);
	//显示按钮
	void show(void)const;
	//按钮状态(按下为true)
	bool state(const ExMessage& msg);
	//获取按钮文本
	const wstring& getText(void)const;
	//修改按钮文本
	void setText(const wstring& _text);
protected:
	//判断区间
	bool isIn(const ExMessage& msg)const;
	wstring text;
	bool isChange;
	int size;
};
#endif