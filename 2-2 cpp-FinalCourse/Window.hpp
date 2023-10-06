#ifndef _WINDOW_
#define _WINDOW_
#include "Button.hpp"
constexpr auto _Pic = L"picture.jpg";

class Window :public Component {
public:
	Window(int width = 960, int height = 720);

	void show(void)const;	//显示绘图窗口
	bool close(void);		//关闭绘图窗口
	void edit(void);		//设定编辑状态
	bool is_edit(void)const;//是否进行过数据编辑
	void flash(void)const;	//刷新窗口
	enum class State{_Add, _Delete, _Revise, _Search, _Count, _Exit};
protected:
	bool isEdit;//是否编辑
	HWND hwnd;	//窗口句柄
};
#endif