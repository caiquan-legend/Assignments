#include"Window.h"

using std::wstringstream;
extern vector<Book>_data_;
extern int _size_;

Window::Window(int width, int height) :
	Component(0, 0, width, height),
	is_edit(false),
	hwnd(initgraph(width, height, EX_NOCLOSE))
{
	//背景预处理
	SetWindowText(hwnd, L"网上购书结账系统");
	setbkcolor(WHITE);
	cleardevice();
	ShowWindow(hwnd, SW_HIDE);

	//样式设置
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);

	//数据读取
	if (!system.read("Clients.txt")) {
		if (MessageBox(GetHWnd(), L"未读取到文件\"Clients.txt\",是否重新生成?", L"询问",
			MB_YESNO | MB_ICONQUESTION) == IDYES) {
			ofstream temp("Clients.txt");
			temp.close();
		}
		else {
			MessageBox(GetHWnd(), L"\"Clients.txt\"文件打开失败.", L"错误", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}

//	//按钮创建
	mainWindow_view = new Button(
		(_width_ - _main_width_) / 4, main_up, _main_width_, _main_height_, L"查看客户信息");
	mainWindow_edit = new Button(
		3 * (_width_ - _main_width_) / 4, main_up, _main_width_, _main_height_, L"编辑客户信息");
	mainWindow_clear = new Button(
		(_width_ - _main_width_) / 4, main_down, _main_width_, _main_height_, L"清空所有数据");
	mainWindow_exit = new Button(
		3 * (_width_ - _main_width_) / 4, main_down, _main_width_, _main_height_, L"退出");



#define _NOT_SORT_

	viewClient_pageUp = new Button(
		_edgeX_, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"上一页");
	viewClient_pageDown = new Button(
		3 * (_width_ - _view_width_) / 8, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"下一页");
#ifndef _NOT_SORT_
	viewClient_sort = new Button(
		7 * (_width_ - _view_width_) / 12, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"按购书总价排序");
#endif
	viewClient_back = new Button(
		_width_ - 1.5 * _view_width_ - _edgeX_ / 4, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"返回上一级菜单");

	viewClient_book.resize(system.size() - 1);
	for(int i = 0, j = _edgeY_ + _stepY_;
	i < (system.size() - 1 >(_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ ? 
		(_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ :
		system.size() - 1);
	++i, j += _stepY_)
	viewClient_book[i] = new Button(_edgeX_ + 5 * _step, j, _width_ - 2 * _edgeX_ - 5 * _step, _stepY_, L"查看");

	viewBook_back = new Button(
		_width_ - 1.5 * _view_width_ - _edgeX_ / 4, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"返回上一级菜单");
	viewBook_pageUp = new Button(
		_edgeX_, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"上一页");
	viewBook_pageDown = new Button(
		3 * (_width_ - _view_width_) / 8, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"下一页");



	addClient_layfolk = new Button(
		(_width_ - _main_width_) / 2, _height_/4-_main_height_, _main_width_, _main_height_, L"普通客户");
	addClient_member = new Button(
		(_width_ - _main_width_) / 2, _height_/2 - _main_height_, _main_width_, _main_height_, L"会员");
	addClient_honoured_guest = new Button(
		(_width_ - _main_width_) / 2, 3*_height_/4 - _main_height_ , _main_width_, _main_height_, L"贵宾");
	addClient_back = new Button(
		0, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"返回上一级菜单");



	editClient_add = new Button(
		(_width_ - _main_width_) / 4, main_up, _main_width_, _main_height_, L"新增客户信息");
	editClient_delete = new Button(
		3 * (_width_ - _main_width_) / 4, main_up, _main_width_, _main_height_, L"删除客户信息");
	editClient_search = new Button(
		(_width_ - _main_width_) / 4, main_down, _main_width_, _main_height_, L"查找并选中客户");
	editClient_book = new Button(
		3 * (_width_ - _main_width_) / 4, main_down, _main_width_, _main_height_, L"编辑图书信息");
	editClient_back = new Button(0, 0, 150, 60, L"返回上一级菜单");


#ifndef _NOT_SHOW_EDIT_BOOK_BUTTON_
	editBook_add.resize(
		_size_> (_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ ?
		(_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ :
		_size_);

	for (int i = 0, j = _edgeY_ + _stepY_;
		i < (_size_ >= (_height_- 3 * _edgeY_ - _stepY_) / _stepY_ ? (_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ : _size_);
		++i, j += _stepY_)
		editBook_add[i] = new Button(_edgeX_ + 5 * _step+_step/2, j, _step/4, _stepY_, L"+");


	editBook_delete.resize(
		_size_ > (_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ ?
		(_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ :
		_size_);

	for (int i = 0, j = _edgeY_ + _stepY_;
		i < (_size_ >= (_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ ? (_height_ - 3 * _edgeY_ - _stepY_) / _stepY_ : _size_);
		++i, j += _stepY_)
		editBook_delete[i] = new Button(_width_ - _edgeX_ - _step / 2 - _step / 4, j, _step / 4, _stepY_, L"-");
#endif

#ifndef _NOT_SORT_
	editBook_sort = new Button(
		7 * (_width_ - _view_width_) / 12, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"按单价排序");
#endif
	editBook_back = new Button(
		_width_ - 1.5 * _view_width_ - _edgeX_ / 4, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"返回上一级菜单");
	editBook_pageUp = new Button(
		_edgeX_, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"上一页");
	editBook_pageDown = new Button(
		3 * (_width_ - _view_width_) / 8, view_b1, 1.5 * _view_width_, 2 * _view_height_, L"下一页");

	showMainWindow();

	table = new Table(system, _edgeX_, _edgeY_, _width_ - 2 * _edgeX_, _height_ - 4 * _edgeY_);
}

Window::~Window(void) {
	//销毁,释放空间
	delete mainWindow_view;
	delete mainWindow_edit;
	delete mainWindow_clear;
	delete mainWindow_exit;



	delete addClient_layfolk;
	delete addClient_member;
	delete addClient_honoured_guest;
	delete addClient_back;



	for (auto tmp : viewClient_book)delete tmp;
	viewClient_book.clear();

	delete viewClient_pageUp;
	delete viewClient_pageDown;
	delete viewClient_back;

	delete viewBook_pageUp;
	delete viewBook_pageDown;
	delete viewBook_back;
#ifndef _NOT_SORT_
	delete viewClient_sort;
#endif



	delete editClient_add;
	delete editClient_delete;
	delete editClient_search;
	delete editClient_back;



	for (auto tmp : editBook_add)delete tmp;
	for (auto tmp : editBook_delete)delete tmp;
	editBook_add.clear(), editBook_delete.clear();

#ifndef _NOT_SORT_
	delete editBook_sort;
#endif
	delete editBook_back;
	delete editBook_pageUp;
	delete editBook_pageDown;



	delete table;
}

void Window::show(void)const {
	ShowWindow(hwnd, SW_SHOW);
}

void Window::messageLoop(void) {
	ExMessage msg;
	while (1) {
		msg = getmessage();
		if (state == WindowState::mainWindow) {
			if (mainWindow_view->state(msg))
				showViewWindow();
			else if (mainWindow_edit->state(msg))
				showEditClientWindow();
			else if (mainWindow_clear->state(msg) && msg.message != WM_LBUTTONUP) {
				if (MessageBox(GetHWnd(), L"确定要清空所有客户数据?", L"清空数据", MB_YESNO | MB_ICONQUESTION) == IDYES) {
					system.clear();
					is_edit = true;
				}
			}
			else if (mainWindow_exit->state(msg)) 
				if (close())return;
		}
		else if (state == WindowState::viewClients) {
			if (viewClient_pageUp->state(msg) && msg.message != WM_LBUTTONUP) {
				table->viewClient_pageUp();
				int index = table->getViewClientIndex();
				int page = index * _times_ < system.size() ? _times_ : system.size() - _times_ * (index - 1) - 1;
				for (int i = 0; i < page; ++i)
					viewClient_book[i]->show();

			}
			else if (viewClient_pageDown->state(msg) && msg.message != WM_LBUTTONUP) {
				table->viewClient_pageDown();
				int index = table->getViewClientIndex();
				int page = index * _times_ < system.size() ? _times_ : system.size() - _times_ * (index - 1) - 1;
				for (int i = 0; i < page; ++i)
					viewClient_book[i]->show();
			}
			else if (viewClient_back->state(msg) && msg.message != WM_LBUTTONUP) {
				table->setSearchIndex(-1);
				showMainWindow();
			}
#ifndef _NOT_SORT_
			else if(viewClient_sort->state(msg)&&msg.message!=WM_LBUTTONUP)
				if (viewClient_sort->getText() == L"按购书总价排序") {
					system.sort_id();
					table->show();
					viewClient_sort->setText(L"按id排序");
					viewClient_sort->state(msg);
				}
				else {
					system.sort_price();
					table->show();
					viewClient_sort->setText(L"按购书总价排序");
					viewClient_sort->state(msg);
				}
#endif
			else if (viewClientBook(msg)) {
				int pos = getClientID(msg);
				table->setSearchIndex(pos);
				showViewBookWindow();
			}
		}
		else if (state == WindowState::viewBooks) {
			if (viewBook_back->state(msg) && msg.message != WM_LBUTTONUP)
				showViewWindow();
			else if (viewBook_pageUp->state(msg) && msg.message != WM_LBUTTONUP)
				table->viewBook_pageUp();
			else if (viewBook_pageDown->state(msg) && msg.message != WM_LBUTTONUP)
				table->viewBook_pageDown();
		}
		else if (state == WindowState::editBooks) {
			if (editBook_back->state(msg) && msg.message != WM_LBUTTONUP) {
				showEditClientWindow();
				int pos = table->getSearchIndex();
				system.set_pay(pos);
#ifdef _NOT_CHECK_BOOK_
				int pos = table->getSearchIndex();
				if(pos!=-1)
#endif
				table->show_editTable(system.getClient(pos)->getID());
			}
			else if (editBook_pageUp->state(msg) && msg.message != WM_LBUTTONUP) {
				table->editBook_pageUp();
				int index = table->getEditBookIndex();
				int page = index * _times_ < _size_ ? _times_ : _size_ - _times_ * (index - 1);
				for (int i = 0; i < page; ++i)
					editBook_add[i]->show();
				for (int i = 0; i < page; ++i)
					editBook_delete[i]->show();
			}
			else if (editBook_pageDown->state(msg) && msg.message != WM_LBUTTONUP) {
				table->editBook_pageDown();
				int index = table->getEditBookIndex();
				int page = index * _times_ < _size_ ? _times_ : _size_ - _times_ * (index - 1);
				for (int i = 0; i < page; ++i)
					editBook_add[i]->show();
				for (int i = 0; i < page; ++i)
					editBook_delete[i]->show();
			}
#pragma omp parallel else if
			else if (editBookAdd(msg)) {
				int pos = table->getSearchIndex(), index = getEditBookID(msg);
				system.add_Book(pos, index);
				showEditBookWindow();
				is_edit = true;
			}
#pragma omp parallel else if
			else if (editBookDelete(msg)) {
				int pos = table->getSearchIndex(), index = getEditBookID(msg);
				system.delete_Book(pos, index);
				showEditBookWindow();
				is_edit = true;
			}
#ifndef _NOT_SORT_
			else if (editBook_sort->state(msg) && msg.message != WM_LBUTTONUP) {
				if (editBook_sort->getText() == L"按单价排序") {
					sort(_data_.begin(), _data_.end(), [&](Book& a, Book& b)->bool {return a > b; });
					table->show_bookTable();
					editBook_sort->setText(L"按id排序");
					editBook_sort->state(msg);
				}
				else {
					sort(_data_.begin(), _data_.end(), [&](Book& a, Book& b)->bool {return a <= b; });
					table->show_bookTable();
					editBook_sort->setText(L"按单价排序");
					editBook_sort->state(msg);
				}
			}
#endif
		}
		else if(state == WindowState::editClients){
			if (editClient_back->state(msg)) {
				showMainWindow();
				table->setSearchIndex(-1);
			}
			else if (editClient_add->state(msg) && msg.message != WM_LBUTTONUP) 
				showAddWindow();
			else if (editClient_delete->state(msg) && msg.message != WM_LBUTTONUP) {
				int pos = table->getSearchIndex();
				if (pos != -1) {
					wstringstream format;
					if (MessageBox(GetHWnd(), L"确定要删除此客户吗?", L"确定删除", MB_YESNO | MB_ICONQUESTION) == IDYES) {
						system.deleteClient(pos);
						showEditClientWindow();
						is_edit = true;
						table->setSearchIndex(-1);
					}
				}
				else MessageBox(GetHWnd(), L"请先搜索以选中客户!", L"提示", MB_OK | MB_ICONINFORMATION);
			}
			else if (editClient_search->state(msg) && msg.message != WM_LBUTTONUP) {
				wchar_t tmp[MAX_SIZE];
				if (InputBox(tmp, MAX_SIZE / 2, L"请输入客户id或姓名进行搜索", L"查找并选中客户", nullptr, 0, 0, false)) {
					int num = _wtoi(tmp);
					if (!num) {
						table->show_editTable(tmp);
						if (table->getSearchIndex() == -1)
							MessageBox(GetHWnd(), L"未找到客户.", L"提示", MB_OK | MB_ICONINFORMATION);
					}
					else {
						table->show_editTable(num);
						if (table->getSearchIndex() == -1)
							MessageBox(GetHWnd(), L"未找到客户.", L"提示", MB_OK | MB_ICONINFORMATION);
					}
				}
			}
			else if (editClient_book->state(msg) && msg.message != WM_LBUTTONUP) {
				int pos = table->getSearchIndex();
#ifndef _NOT_CHECK_BOOK_
				if (pos != -1)
#endif
					showEditBookWindow();
#ifndef _NOT_CHECK_BOOK_
				else MessageBox(GetHWnd(), L"请先搜索以选中客户!", L"提示", MB_OK | MB_ICONINFORMATION);
#endif
			}
		}
		else if(state == WindowState::addClients){
			wchar_t tmp[2 * MAX_SIZE];
			if (addClient_back->state(msg) && msg.message != WM_LBUTTONUP) {
				showEditClientWindow();
				//int index = table->getSearchIndex();
				//if (index != -1)table->show_editTable(index);
			}
			else if (addClient_layfolk->state(msg) && msg.message != WM_LBUTTONUP) {
				if (InputBox(tmp, 2 * MAX_SIZE,
					L"请按照\"姓名 地址\"的格式输入数据:", L"添加普通客户", nullptr, 0, 0, false)) {

					wstringstream format(tmp);
					layfolk _A;
					_A.setData(format);

					if (system.search(_A.getName().c_str()) != -1) {
						MessageBox(GetHWnd(), L"该姓名已存在!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					if (_A.getName() == L"") {
						MessageBox(GetHWnd(), L"姓名不能为空!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					if (_A.getAddress() == L"") {
						MessageBox(GetHWnd(), L"地址不能为空!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}

					system.addClient(_A);
					showEditClientWindow();
					table->show_editTable(_A.getName().c_str());
					is_edit = true;

					int pos_y = _edgeY_ + _stepY_;
					if (!viewClient_book.empty()) {
						pos_y = viewClient_book.back()->getY() + _stepY_;
					}

					if (pos_y <= _height_ - 3 * _edgeY_ - _stepY_){
						viewClient_book.push_back(new Button(
							_edgeX_ + 5 * _step, pos_y, 
							_width_ - 2 * _edgeX_ - 5 * _step, _stepY_, L"查看"));
					}
#ifndef _NOT_SORT_
					system.sort_id();
#endif
				}
			}
			else if (addClient_member->state(msg) && msg.message != WM_LBUTTONUP) {
				if (InputBox(tmp, 2 * MAX_SIZE,
					L"请按照\"姓名 地址 会员等级(1-5)\"的格式输入数据:", L"添加会员客户", nullptr, 0, 0, false)) {

					wstringstream format(tmp);
					member _B;
					_B.setData(format);

					if (system.search(_B.getName().c_str()) != -1) {
						MessageBox(GetHWnd(), L"该姓名已存在!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					if (_B.getName() == L"") {
						MessageBox(GetHWnd(), L"姓名不能为空!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					if (_B.getAddress() == L"") {
						MessageBox(GetHWnd(), L"地址不能为空!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					if (_B.getGrade() < 1 || _B.getGrade() > 5) {
						MessageBox(GetHWnd(), L"输入的会员等级应为1-5!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}

					system.addClient(_B);
					showEditClientWindow();
					table->show_editTable(_B.getName().c_str());
					is_edit = true;

					int pos_y = _edgeY_ + _stepY_;
					if (!viewClient_book.empty()) {
						pos_y = viewClient_book.back()->getY() + _stepY_;
				}

					if (pos_y <= _height_ - 3 * _edgeY_ - _stepY_) {
						viewClient_book.push_back(new Button(
							_edgeX_ + 5 * _step, pos_y,
							_width_ - 2 * _edgeX_ - 5 * _step, _stepY_, L"查看"));
					}
#ifndef _NOT_SORT_
					system.sort_id();
#endif
				}
			}
			else if (addClient_honoured_guest->state(msg) && msg.message != WM_LBUTTONUP) {
				if (InputBox(tmp, 2 * MAX_SIZE,
					L"请按照\"姓名 地址 折扣率(1-99)\"的格式输入数据:", L"添加贵宾客户", nullptr, 0, 0, false)) {

					wstringstream format(tmp);
					honoured_guest _C;
					_C.setData(format);

					if (system.search(_C.getName().c_str()) != -1) {
						MessageBox(GetHWnd(), L"该姓名已存在!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					if (_C.getName() == L"") {
						MessageBox(GetHWnd(), L"姓名不能为空!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					if (_C.getAddress() == L"") {
						MessageBox(GetHWnd(), L"地址不能为空!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					if (_C.getRate() < 1 || _C.getRate() > 99) {
						MessageBox(GetHWnd(), L"折扣率应为1-99!", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}

					system.addClient(_C);
					showEditClientWindow();
					table->show_editTable(_C.getName().c_str());
					is_edit = true;

					int pos_y = _edgeY_ + _stepY_;
					if (!viewClient_book.empty()) {
						pos_y = viewClient_book.back()->getY() + _stepY_;
					}

					if (pos_y <= _height_ - 3 * _edgeY_ - _stepY_) {
						viewClient_book.push_back(new Button(
							_edgeX_ + 5 * _step, pos_y,
							_width_ - 2 * _edgeX_ - 5 * _step, _stepY_, L"查看"));
					}   
#ifndef _NOT_SORT_
					system.sort_id();
#endif
				}
			}
		}
	}
}

bool Window::close(void) {
	if (is_edit) {
		int id = MessageBox(GetHWnd(), L"是否保存所有操作?", L"退出程序", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES) {
#ifndef _NOT_SORT_
			system.sort_id();
#endif
			system.write("Clients.txt");
			closegraph();
		}
		return true;
	}
	else return true;
	return false;
}

void Window::showMainWindow(void) {
	state = WindowState::mainWindow;
	cleardevice();

	loadimage(nullptr, _Main, _width_, _height_);

	RECT rect = { 0,0,width,200 };
	settextstyle(50, 0, L"微软雅黑");
	drawtext(L"网上购书结账系统", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	mainWindow_view->show();
	mainWindow_edit->show();
	mainWindow_clear->show();
	mainWindow_exit->show();
}

void Window::showViewWindow(void) {
	state = WindowState::viewClients;
	cleardevice();

	loadimage(nullptr, _View, _width_, _height_);

	table->show();
	viewClient_pageUp->show();
	viewClient_pageDown->show();
	viewClient_back->show();
	int index = table->getViewClientIndex();
	int page = index * _times_ < system.size() ? _times_ : system.size() - _times_ * (index - 1) - 1;
	for (int i = 0; i < page; ++i)
		viewClient_book[i]->show();

#ifndef _NOT_SORT_
	viewClient_sort->show();
#endif
}

void Window::showAddWindow(void) {
	state = WindowState::addClients;
	cleardevice();

	loadimage(nullptr, _Add, _width_, _height_);

	addClient_layfolk->show();
	addClient_member->show();
	addClient_honoured_guest->show();
	addClient_back->show();
}

void Window::showEditClientWindow(void) {
	state = WindowState::editClients;
	cleardevice();

	loadimage(nullptr, _Edit_Client, _width_, _height_);

	editClient_add->show();
	editClient_delete->show();
	editClient_search->show();
	editClient_book->show();
	editClient_back->show();
}

void Window::showEditBookWindow(void) {
	state = WindowState::editBooks;
	cleardevice();

	loadimage(nullptr, _Edit_Book, _width_, _height_);

	table->show_bookTable();

#ifndef _NOT_SHOW_EDIT_BOOK_BUTTON_
	int index = table->getEditBookIndex();
	int page = index * _times_ < _size_ ? _times_ : _size_ - _times_ * (index - 1);
	for (int i = 0; i < page; ++i)
		editBook_add[i]->show();
	for (int i = 0; i < page; ++i)
		editBook_delete[i]->show();
#endif
#ifndef _NOT_SORT_
	editBook_sort->show();
#endif
	editBook_back->show();
	editBook_pageUp->show();
	editBook_pageDown->show();
}

void Window::showViewBookWindow(void) {
	state = WindowState::viewBooks;
	cleardevice();

	loadimage(nullptr, _Edit_Book, _width_, _height_);

	table->show_viewBookTable();

	viewBook_back->show();
	viewBook_pageUp->show();
	viewBook_pageDown->show();
}

bool Window::isNumber(const wstring& str) {
	if (!_wtoi(str.c_str()))return false;
	return true;
}

bool Window::viewClientBook(ExMessage& msg) {
	int index = table->getViewClientIndex();
	int page = index * _times_ < system.size() ? _times_ : system.size() - _times_ * (index - 1) - 1;
 	for (int i = 0; i < page; ++i)
		if (viewClient_book[i]->state(msg) && msg.message != WM_LBUTTONUP) {
			current = viewClient_book[i];
			return true;
		}
	return false;
}

bool Window::editBookAdd(ExMessage& msg) {
#pragma omp parallel for
	int index = table->getEditBookIndex();
	int page = index * _times_ < _size_ ? _times_ : _size_ - _times_ * (index - 1);
	for (int i = 0; i < page; ++i)
		if (editBook_add[i]->state(msg) && msg.message != WM_LBUTTONUP) {
			current = editBook_add[i];
			return true;
		}
	return false;
}

bool Window::editBookDelete(ExMessage& msg) {
#pragma omp parallel for
	int index = table->getEditBookIndex();
	int page = index * _times_ < _size_ ? _times_ : _size_ - _times_ * (index - 1);
	for (int i = 0; i < page; ++i)
		if (editBook_delete[i]->state(msg) && msg.message != WM_LBUTTONUP) {
			current = editBook_delete[i];
			return true;
		}
	return false;
}

int Window::getEditBookID(ExMessage& msg) {
	int Ypos = msg.y,
		res = (Ypos - _edgeY_) / _stepY_ + _times_ * (table->getEditBookIndex() - 1);
	return res;
}

int Window::getClientID(ExMessage& msg) {
	int Ypos = msg.y,
		res = (Ypos - _edgeY_) / _stepY_ + _times_ * (table->getViewClientIndex() - 1);
	return res;
}