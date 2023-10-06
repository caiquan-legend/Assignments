#include"Button.h"
Button::Button(int x, int y, int width, int height, const wstring& _text, int _size) :
	Component(x, y, width, height), text(_text), isChange(false), size(_size) {}
const wstring& Button::getText(void)const { return text; }
void Button::setText(const wstring& _text) { text = _text; }

bool Button::isIn(const ExMessage& msg)const {
	if (msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height)return true;
	return false;
}

void Button::show(void)const {
	//设置样式
	setlinestyle(PS_SOLID, 2);
	setfillcolor(CYAN);
	settextstyle(size ? width / 8 : size, 0, L"微软雅黑");

	fillrectangle(x, y, x + width, y + height);

	RECT rect = { x,y,x + width,y + height };
	drawtext(text.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

bool Button::state(const ExMessage& msg) {
	//鼠标在按钮内
	if (msg.message == WM_MOUSEMOVE && isIn(msg)) {
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(size ? width / 6 : size, 0, L"微软雅黑");

		fillrectangle(x, y, x + width, y + height);

		RECT rect = { x, y, x + width,y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		isChange = true;
		return false;
	}
	//左键点击
	else if ((msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) && isIn(msg)) {
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(size ? width / 6 : size, 0, L"微软雅黑");

		fillrectangle(x, y, x + width, y + height);

		RECT rect = { x,y,x + width,y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		isChange = true;
		return true;
	}
	//按钮状态改变时,保持原状,防止屏闪
	else {
		if (isChange) {
			show();
			isChange = false;
		}
		return false;
	}
}