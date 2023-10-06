#ifndef _COMPONENT_
#define _COMPONENT_
#include "Settings.hpp"
//组件基类
class Component {
public:
	Component(int _x = 0, int _y = 0, int _width = 80, int _height = 60);
	void set(int x, int y, int width, int height);	//重设坐标与宽高
	int getX(void)const;	//api接口
	int getY(void)const;
	int getWidth(void)const;
	int getHeight(void)const;
	void setX(int x);		//单项设置
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	virtual void show(void)const = 0;
protected:
	int x, y,			//坐标,宽高
		width, height;
};
#endif