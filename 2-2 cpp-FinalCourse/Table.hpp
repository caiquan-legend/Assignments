#ifndef _Table_
#define _Table_
#include "Component.hpp"
#include "Data.hpp"
class Table :public Component {
public:
	Table(const Data& system, int x = 0, int y = 0, int width = 120, int height = 60);
	void show(void)const;		//显示主表格
	void showSearchTable(int);	//显示查找表格
	void showCountTable(void);	//显示统计表格
	void showPage(void)const;	//显示页数(左侧)

	void pageUp(void);	//上一页
	void pageDown();	//下一页
private:
	const Data& data;	//数据
	int index;			//当前页面
};
#endif