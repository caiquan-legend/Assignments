#ifndef _Window_
#define _Window_
#include"Button.h"
#include"Table.h"
using std::pair;

constexpr auto 
_Main = L"main.jpg",
_View = L"view.jpg",
_Add = L"add.jpg", 
_Edit_Client = L"client.jpg", 
_Edit_Book = L"book.jpg";

class Window :public Component {
public:
	Window(int width = 1024, int height = 792);
	~Window(void);

	void show(void)const;
	void messageLoop(void);
	bool close(void);
	enum class WindowState { mainWindow, viewClients, addClients, editClients, editBooks, viewBooks };
private:
	void showMainWindow(void);
	void showViewWindow(void);
	void showAddWindow(void);
	void showEditClientWindow(void);
	void showEditBookWindow(void);
	void showViewBookWindow(void);
	bool isNumber(const wstring& str);

	bool viewClientBook(ExMessage& msg);
	bool editBookAdd(ExMessage& msg);
	bool editBookDelete(ExMessage& msg);

	int getEditBookID(ExMessage& msg);
	int getClientID(ExMessage& msg);

	WindowState state;	//窗口状态
	Table* table;		//客户数据表格
	System system;		//管理器
	HWND hwnd;			//窗口句柄
	bool is_edit;		//是否编辑

	Button* current;

//	//主窗口
	Button* mainWindow_view;
	Button* mainWindow_edit;
	Button* mainWindow_exit;
	Button* mainWindow_clear;

	//添加选择
	Button* addClient_layfolk;
	Button* addClient_member;
	Button* addClient_honoured_guest;
	Button* addClient_back;

	//查看
	vector<Button*>viewClient_book;

	Button* viewClient_pageUp;
	Button* viewClient_pageDown;
	Button* viewClient_back;

	Button* viewBook_pageUp;
	Button* viewBook_pageDown;
	Button* viewBook_back;
#ifndef _NOT_SORT_
	Button* viewClient_sort;
#endif

	//编辑客户信息
	Button* editClient_add;
	Button* editClient_delete;
	Button* editClient_search;
	Button* editClient_book;
	Button* editClient_back;

	//编辑图书信息
	vector<Button*> editBook_add;
	vector<Button*> editBook_delete;

#ifndef _NOT_SORT_
	Button* editBook_sort;
#endif
	Button* editBook_back;
	Button* editBook_pageUp;
	Button* editBook_pageDown;
};
#endif