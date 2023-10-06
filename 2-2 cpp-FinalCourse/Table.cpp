#define _CRT_SECURE_NO_WARNINGS
#include "Table.hpp"
#include<sstream>
using std::wstringstream;

Table::Table(const Data& _data, int x, int y, int width, int height) :
	Component(x, y, width, height), data(_data), index(1) {}

void Table::show(void)const {
	setfillcolor(WHITE);
	fillrectangle(150, 104, 930, 696);
	//横线
	for (int i = 104; i <= 696; i += 60) line(line_y[1], i, line_y[7], i);
	for (int i = 1; i < 8; ++i) line(line_y[i], 104, line_y[i], 696);//竖线

	RECT rect;
	wchar_t head[6][3] = { L"工号",L"姓名",L"性别",L"电话",L"科室",L"工资" };
	for (int i = 1; i < 7; ++i) {
		rect = { line_y[i],104,line_y[i + 1],164 };
		drawtext(head[i - 1], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}showPage();
	if (data.empty())return;

	auto it = data.begin();
	for (int i = 0; i < 9 * (index - 1); ++i, ++it);

	for (int i = 1 + 9 * (index - 1), j = 164; i <= data.size(); ++i, j += 60, ++it) {
		wchar_t buffer[MAX_LENGTH];
		rect = { line_y[1],j,line_y[2],j + 60 };
		drawtext(std::to_wstring(it->second.number).c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { line_y[2],j,line_y[3],j + 60 };
		drawtext(it->second.name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { line_y[3],j,line_y[4],j + 60 };
		drawtext(it->second.sex ? L"男" : L"女", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { line_y[4],j,line_y[5],j + 60 };
		drawtext(it->second.phone, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { line_y[5],j,line_y[6],j + 60 };
		drawtext(_Department[it->second.department], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { line_y[6],j,line_y[7],j + 60 };
		drawtext(std::to_wstring(it->second.salary).substr(0, 7).c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

void Table::showSearchTable(int id) {
	setfillcolor(WHITE);
	fillrectangle(150, 284, 930, 404);
	settextstyle(25, 0, L"微软雅黑");

	line(150, 344, 930, 344);
	for (int i = 1; i < 8; ++i) line(line_y[i], 284, line_y[i], 404);
	RECT rect;
	wchar_t head[6][3] = { L"工号",L"姓名",L"性别",L"电话",L"科室",L"工资" };
	for (int i = 1; i <= 6; ++i) {
		rect = { line_y[i],284,line_y[i + 1],344 };
		drawtext(head[i - 1], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	auto it = data.get(id);
	rect = { line_y[1],344,line_y[2],404 };
	drawtext(std::to_wstring(it.number).c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { line_y[2],344,line_y[3],404 };
	drawtext(it.name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { line_y[3],344,line_y[4],404 };
	drawtext(it.sex ? L"男" : L"女", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { line_y[4],344,line_y[5],404 };
	drawtext(it.phone, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { line_y[5],344,line_y[6],404 };
	drawtext(_Department[it.department], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { line_y[6],344,line_y[7],404 };
	drawtext(std::to_wstring(it.salary).substr(0, 7).c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

void Table::showCountTable(void) {
	setfillcolor(WHITE);
	fillrectangle(150, 104, 930, 696);
	settextstyle(25, 0, L"微软雅黑");
	//横线
	for (int i = 104; i < 696; i += 60) line(line_y[1], i, line_y[7], i);
	for (int i = 1; i <= 3; ++i) line(line_y[2 * i], 104, line_y[2 * i], 696);

	RECT rect;
	wchar_t head[4][5] = { L"科室",L"平均工资",L"总计工资",L"人数"};
	short pos[5]{ 1,2,4,6,7 };
	for (int i = 1; i <= 4; ++i) {
		rect = { line_y[pos[i - 1]],104,line_y[pos[i]],164 };
		drawtext(head[i - 1], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	wchar_t buffer[MAX_LENGTH];
	for (int i = 1; i <= 9; ++i) {
		rect = { 150,104 + 60 * i,300,164 + 60 * i };
		drawtext(_Department[i - 1], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}for (int i = 1; i <= 9; ++i) {
		rect = { 300,104 + 60 * i,500,164 + 60 * i };
		if (!count_num[i - 1].second)wcscpy(buffer, L"0.000000");
		else wcscpy(buffer, std::to_wstring(count_num[i - 1].second / count_num[i - 1].first).substr(0, 8).c_str());
		drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}for (int i = 1; i <= 9; ++i) {
		rect = { 500,104 + 60 * i,830,164 + 60 * i };
		drawtext(std::to_wstring(count_num[i - 1].second).substr(0, 8).c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}for (int i = 1; i <= 9; ++i) {
		rect = { 830,104 + 60 * i,930,164 + 60 * i };
		_itow_s(count_num[i - 1].first, buffer, MAX_LENGTH);
		drawtext(std::to_wstring(count_num[i - 1].first).substr(0, 8).c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

void Table::showPage(void)const {
	setbkmode(OPAQUE);
	wstringstream format;
	format << index << L"页/" << (data.size() - 1) / 9 + 1 << L"页";
	RECT rect = { 15,344,135,404 };
	drawtext(format.str().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkmode(TRANSPARENT);
}

void Table::pageUp(void) {
	index--;
	if (index < 1) index++;
	show();
}

void Table::pageDown(void) {
	index++;
	if (index > (data.size() - 1) / 9 + 1)
		index--;
	show();
}