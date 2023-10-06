#include"Table.h"
using std::wstringstream;
extern vector<Book>_data_;

Table::Table(const System& _system, int x, int y, int width, int height) :
	Component(x, y, width, height), system(_system), 
	viewClient_index(1), viewBook_index(1), editBook_index(1), search_index(-1) {}

void Table::show(void)const {
	setfillcolor(WHITE);

	fillrectangle(x, y, x + width, y + height);

	//竖线
	for (int i = _edgeX_ + _step; i < _width_ - _edgeX_; i += _step)
		line(i, _edgeY_, i, _height_ - 3 * _edgeY_);

	//横线
	for (int j = _edgeY_ + _stepY_; j <= _height_ - 3 * _edgeY_ - _stepY_; j += _stepY_)
		line(_edgeX_, j, _width_ - _edgeX_, j);

	RECT rect;

	wchar_t header[6][5] = { L"客户id", L"客户姓名" ,L"客户地址",L"客户类型",L"应付金额",L"图书" };
	for (int i = _edgeX_, j = 0; j < 5; i += _step, ++j) {
		rect = { i,_edgeX_,i + _step,_edgeY_ + _stepY_ };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	//调整偏移
	rect = { _edgeX_ + 5 * _step, _edgeX_, _width_ - _edgeX_, _edgeY_ + _stepY_ };
	drawtext(header[5], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wchar_t _id[10];

	for (int i = _edgeY_ + _stepY_, j = 1 + _times_ * (viewClient_index - 1);
		j < system.size() && i <= _height_ - 3 * _edgeY_ - _stepY_; i += _stepY_, j++) {

		rect = { _edgeX_,i, _edgeX_ + _step,i + _stepY_ };
		_itow_s(system.getClient(j)->getID(), _id, 10);
		drawtext(_id, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + _step,i,_edgeX_ + 2 * _step,i + _stepY_ };
		drawtext(system.getClient(j)->getName().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + 2 * _step,i,_edgeX_ + 3 * _step,i + _stepY_ };
		drawtext(system.getClient(j)->getAddress().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + 3 * _step,i,_edgeX_ + 4 * +_step,i + _stepY_ };
		drawtext(system.getClient(j)->get_typeName().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		wstringstream s; s << system.getClient(j)->getPay();
		rect = { _edgeX_ + 4 * _step,i,_edgeX_ + 5 * _step,i + _stepY_ };
		drawtext(s.str().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	wstringstream format;
	setbkmode(OPAQUE);
	format << L"第" << viewClient_index << L"页/共" << (system.size() - 2 + _times_) / _times_ << L"页";
	rect = { _edgeX_ + 3 * _view_width_ / 2 ,view_b1 ,_edgeX_ + 3 * _view_width_,_height_ };
	drawtext(format.str().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkmode(TRANSPARENT);
}

void Table::show_bookTable(void)const {
	setfillcolor(WHITE);

	fillrectangle(x, y, x + width, y + height);

	//竖线
	for (int i = _edgeX_ + _step; i < _width_ - _edgeX_; i += _step)
		line(i, _edgeY_, i, _height_ - 3 * _edgeY_);

	//横线
	for (int j = _edgeY_ + _stepY_; j <= _height_ - 3 * _edgeY_ - _stepY_; j += _stepY_)
		line(_edgeX_, j, _width_ - _edgeX_, j);

	RECT rect;

	LOGFONT f;
	gettextstyle(&f);
	settextstyle(25, 0, L"微软雅黑");

	//表头
	wchar_t header[6][5] = { L"图书id",L"图书名称",L"作者",L"出版社",L"单价",L"数量" };
	for (int i = _edgeX_, j = 0; j < 5; i += _step, ++j) {
		rect = { i,_edgeX_,i + _step,_edgeY_ + _stepY_ };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	//调整偏移
	rect = { _edgeX_ + 5 * _step, _edgeX_, _width_ - _edgeX_, _edgeY_ + _stepY_ };
	drawtext(header[5], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	for (int i = _edgeY_ + _stepY_, j = 1 + _times_*(editBook_index-1); 
		j < _data_.size() && i <= _height_ - 3 * _edgeY_ - _stepY_; i += _stepY_, j++) {

		rect = { _edgeX_,i, _edgeX_ + _step,i + _stepY_ };
		drawtext(_data_[j].getID(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + _step,i,_edgeX_ + 2 * _step,i + _stepY_ };
		drawtext(_data_[j].getName(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + 2 * _step,i,_edgeX_ + 3 * _step,i + _stepY_ };
		drawtext(_data_[j].getAuthor(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + 3 * _step,i,_edgeX_ + 4 * +_step,i + _stepY_ };
		drawtext(_data_[j].getPub(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
		wchar_t buffer[10];
		_itow_s(_data_[j].getPrice(), buffer, 10);
		rect = { _edgeX_ + 4 * _step,i,_edgeX_ + 5 * _step,i + _stepY_ };
		drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		_itow_s(system.getClient(search_index)->getNum(j), buffer, 10);
		rect = { _edgeX_ + 5 * _step,i,_width_-_edgeX_,i + _stepY_ };
		drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	}
	
	settextstyle(&f);

	wstringstream format;
	setbkmode(OPAQUE);
	int width = _height_ - _edgeY_ - _stepY_;
	format << L"第" << editBook_index << L"页/共" << (_data_.size()  - 2 + _times_) / _times_ << L"页";
	rect = { _edgeX_ + 3 * _view_width_ / 2 ,view_b1 ,_edgeX_ + 3 * _view_width_,_height_ };
	drawtext(format.str().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkmode(TRANSPARENT);
}

void Table::show_viewBookTable(void)const {
	setfillcolor(WHITE);

	fillrectangle(x, y, x + width, y + height);

	//竖线
	for (int i = _edgeX_ + _step; i < _width_ - _edgeX_; i += _step)
		line(i, _edgeY_, i, _height_ - 3 * _edgeY_);

	//横线
	for (int j = _edgeY_ + _stepY_; j <= _height_ - 3 * _edgeY_ - _stepY_; j += _stepY_)
		line(_edgeX_, j, _width_ - _edgeX_, j);

	RECT rect;

	//表头
	wchar_t header[6][5] = { L"图书id",L"图书名称",L"作者",L"出版社",L"单价",L"数量" };
	for (int i = _edgeX_, j = 0; j < 5; i += _step, ++j) {
		rect = { i,_edgeX_,i + _step,_edgeY_ + _stepY_ };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	//调整偏移
	rect = { _edgeX_ + 5 * _step, _edgeX_, _width_ - _edgeX_, _edgeY_ + _stepY_ };
	drawtext(header[5], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	for (int i = _edgeY_ + _stepY_,j = 1 + _times_ * (viewBook_index - 1);
		j < _data_.size() && i <= _height_ - 3 * _edgeY_ - _stepY_; j++) {
		if (!system.getClient(search_index)->getNum(j))continue;

		rect = { _edgeX_,i, _edgeX_ + _step,i + _stepY_ };
		drawtext(_data_[j].getID(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + _step,i,_edgeX_ + 2 * _step,i + _stepY_ };
		drawtext(_data_[j].getName(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + 2 * _step,i,_edgeX_ + 3 * _step,i + _stepY_ };
		drawtext(_data_[j].getAuthor(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rect = { _edgeX_ + 3 * _step,i,_edgeX_ + 4 * +_step,i + _stepY_ };
		drawtext(_data_[j].getPub(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		wchar_t buffer[10];
		_itow_s(_data_[j].getPrice(), buffer, 10);
		rect = { _edgeX_ + 4 * _step,i,_edgeX_ + 5 * _step,i + _stepY_ };
		drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		_itow_s(system.getClient(search_index)->getNum(j), buffer, 10);
		rect = { _edgeX_ + 5 * _step,i,_width_ - _edgeX_,i + _stepY_ };
		drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		i += _stepY_;
	}

	wstringstream format;
	setbkmode(OPAQUE);
	format << L"第" << viewBook_index << L"页/共" << (system.size() - 2 + _times_) / _times_ << L"页";
	rect = { _edgeX_ + 3 * _view_width_ / 2 ,view_b1 ,_edgeX_ + 3 * _view_width_,_height_ };
	drawtext(format.str().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkmode(TRANSPARENT);
}

void Table::viewClient_pageUp(void) {
	viewClient_index--;
	if (viewClient_index < 1) {
		viewClient_index++;
	}show();
}

void Table::viewClient_pageDown(void) {
	viewClient_index++;
	if ((viewClient_index - 1)*_times_ >= system.size() - 1) {
		viewClient_index--;
	}show();
}

void Table::editBook_pageUp(void) {
	editBook_index--;
	if (editBook_index < 1) {
		editBook_index++;
	}show_bookTable();
}

void Table::editBook_pageDown(void) {
	editBook_index++;
	if ((editBook_index - 1)*_times_ >= _data_.size() - 1) {
		editBook_index--;
	}show_bookTable();
}

void Table::viewBook_pageUp(void) {
	viewBook_index--;
	if (viewBook_index < 1) {
		viewBook_index++;
	}show_viewBookTable();
}

void Table::viewBook_pageDown(void) {
	viewBook_index++;
	if ((viewBook_index - 1)*_times_ >= system.size() - 1) {
		viewBook_index--;
	}show_viewBookTable();
}

void Table::show_editTable(const wchar_t* tmp) {
	int index = system.search(tmp);
	if (index != -1) {
		show_searchTable(index);
		search_index = index;
	}
	else search_index = -1;
}

void Table::show_editTable(int id) {
	int index = system.search(id);
	if (index != -1) {
		show_searchTable(index);
		search_index = index;
	}
	else search_index = -1;
}

void Table::show_searchTable(int index) {
	setfillcolor(WHITE);

	fillrectangle(x, y + 60, _width_ - _edgeX_, y + _stepY_ + 120);

	int step = (_width_ - 2 * _edgeX_) / 5;

	for (int i = _edgeX_ + step; i < _width_ - _edgeX_; i += step)
		line(i, _edgeY_ + 60, i, 3 * _edgeY_ + 120);

	line(_edgeX_ ,
		_edgeY_ + _stepY_+60,
		_width_ - _edgeX_, 
		_edgeY_ + _stepY_+60);

	RECT rect;
	settextstyle(25, 0, L"微软雅黑");

	wchar_t header[5][5] = { L"客户id",L"客户姓名",L"客户地址",L"客户类型",L"应付金额" };
	for (int i = _edgeX_, j = 0; j < 5; i += step, ++j) {
		rect = { i,_edgeY_ + 60,i + step,_edgeY_ + _stepY_ + 60 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	wchar_t buffer[10];
	_itow_s(system.getClient(index)->getID(), buffer, 10);

	rect = {
		_edgeX_ ,
		_edgeY_ + _stepY_ + 60,
		_edgeX_ + step,
		_edgeY_ + 2 * _stepY_ + 60 };
	drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = {
		_edgeX_ + step,
		_edgeY_ + _stepY_ + 60,
		_edgeX_ + 2 * step,
		_edgeY_ + 2 * _stepY_ + 60 };
	drawtext(system.getClient(index)->getName().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = {
		_edgeX_ + 2 * step,
		_edgeY_ + _stepY_ + 60,
		_edgeX_ + 3 * step,
		_edgeY_ + 2 * _stepY_ + 60 };
	drawtext(system.getClient(index)->getAddress().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = {
		_edgeX_ + 3 * step,
		_edgeY_ + _stepY_ + 60,
		_edgeX_ + 4 * +step,
		_edgeY_ + 2 * _stepY_ + 60 };
	drawtext(system.getClient(index)->get_typeName().c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	_itow_s(system.getClient(index)->getPay(), buffer, 10);
	rect = {
		_edgeX_ + 4 * step,
		_edgeY_ + _stepY_ + 60,
		_edgeX_ + 5 * step,
		_edgeY_ + 2 * _stepY_ + 60 };
	drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setSearchIndex(index);
}

int Table::getSearchIndex(void)const {
	return search_index;
}

int Table::getViewBookIndex(void)const {
	return viewClient_index;
}

int Table::getViewClientIndex(void)const {
	return viewClient_index;
}

int Table::getEditBookIndex(void)const {
	return editBook_index;
}

void Table::setSearchIndex(int index) {
	search_index = index;
}