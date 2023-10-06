#ifndef _BUTTON_
#define _BUTTON_
#include "Component.hpp"
using std::wstring;
class Button :public Component {
public:
	Button(int x = 0, int y = 0, int width = 80, int height = 60, const wstring& text = L"按钮");
	//显示按钮
	void show(void)const;
	//状态
	bool state(const ExMessage& msg);
	//获取文本
	const wstring& getText(void)const;
	//修改文本
	void setText(const wstring& text);
private:
	bool isIn(const ExMessage& msg)const;	//鼠标指针是否在按钮内部
	wstring text;	//按钮文本
	bool isChange;	//刷新,防止屏闪
};
#endif