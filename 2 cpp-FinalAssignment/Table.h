#ifndef _Table_
#define _Table_
#include"Component.h"
#include"System.h"
#include"Data.h"
#include<sstream>

constexpr int _stepx = 120, _stepy = 10;

class Table :public Component {
public:
	Table(const System& _system, int x = 0, int y = 0, int width = 100, int height = 60);

	void show(void)const;
	void show_bookTable(void)const;
	void show_viewBookTable(void)const;
	void show_editTable(const wchar_t* searchTerms);
	void show_editTable(int id);

	void viewClient_pageUp(void);
	void viewClient_pageDown(void);
	void editBook_pageUp(void);
	void editBook_pageDown(void);
	void viewBook_pageUp(void);
	void viewBook_pageDown(void);

	void show_searchTable(int index);

	int getSearchIndex(void)const;
	int getEditBookIndex(void)const;
	int getViewBookIndex(void)const;
	int getViewClientIndex(void)const;

	void setSearchIndex(int index);
private:
	int viewClient_index;
	int viewBook_index;
	int editBook_index;

	int search_index;
	const System& system;
};
#endif