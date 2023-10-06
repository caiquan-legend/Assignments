#ifndef _System_
#define _System_
#include "Window.hpp"
#include "Table.hpp"
#include "Data.hpp"
class System {
public:
	System(void);
	~System(void);
	//主循环
	void MainLoop(void);
private:
	void AddEmployee(void);		//添加
	void DeleteEmployee(void);	//删除
	void ReviseEmployee(void);	//修改
	void SearchEmployee(void);	//查找
	void CountEmployee(void);	//统计
	void _Exit(void);			//退出

	void SaveData(void);	//保存
	void CopyData(void);	//复制
	void HideTable(void);	//隐藏表格
	void showInitButton(void)const;//按钮初始化

	//显示/隐藏表格
	bool tab;
	//是否选中员工
	pair<bool,int> is_point;
protected:
	//员工数据
	Data info;

	//窗口
	Window* window;
	//表格
	Table* table;

	//按钮
	Button* Add;
	Button* Delete;
	Button* Revise;
	Button* Search;
	Button* Count;
	Button* Exit;

	Button* Save;
	Button* Copy;
	Button* PageUp;
	Button* PageDown;
	Button* Hide;
};
#endif