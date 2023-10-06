#include "Button.hpp"
Button::Button(int _x, int _y, int _width, int _height, const wstring& _text) :
	Component(_x, _y, _width, _height), text(_text), isChange(false) {}

const wstring& Button::getText(void)const { return text; }
void Button::setText(const wstring& _text) { text = _text; }

bool Button::isIn(const ExMessage& msg)const {
	return msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height;
}

void Button::show(void)const {
	setlinestyle(PS_SOLID, 2);
	setfillcolor(_Move_Color);
	settextstyle(20, 0, L"微软雅黑");

	fillrectangle(x, y, x + width, y + height);
	RECT rect = { x,y,x + width, y + height };
	drawtext(text.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

bool Button::state(const ExMessage& msg) {
	if (msg.message == WM_MOUSEMOVE && isIn(msg)) {
		setlinestyle(PS_SOLID, 2);
		setfillcolor(_Click_Color);
		settextstyle(25, 0, L"微软雅黑");

		fillrectangle(x, y, x + width, y + height);
		RECT rect = { x,y,x + width, y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		isChange = true;
		return false;
	}
	else if (msg.message == WM_LBUTTONUP && isIn(msg)) {
		setlinestyle(PS_SOLID, 2);
		setfillcolor(_Click_Color);
		settextstyle(25, 0, L"微软雅黑");
		fillrectangle(x, y, x + width, y + height);
		RECT rect = { x,y,x + width, y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		isChange = true;
		return true;
	}
	else if (msg.message == WM_LBUTTONDOWN && isIn(msg)) {
		setlinestyle(PS_SOLID, 2);
		setfillcolor(_Click_Color);
		settextstyle(28, 0, L"微软雅黑");
		fillrectangle(x, y, x + width, y + height);
		RECT rect = { x,y,x + width, y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		isChange = false;
		return false;
	}
	else {
		if (isChange) {
			show(), isChange = false;
		}return false;
	}
}