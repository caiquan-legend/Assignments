#pragma once
#ifndef _Component_
#define _Component_
#include"Settings.h"
#include<easyx.h>
class Component {
public:
	Component(int _x = 0, int _y = 0, int _width = 100, int _height = 60);
	//控件矩形
	void setRectangle(int _x, int _y, int _width, int _height);
	int getX(void)const;
	int getY(void)const;
	int getWidth(void)const;
	int getHeight(void)const;
	void setX(int _x);
	void setY(int _y);
	void setWidth(int _width);
	void setHeight(int _height);
	//显示
	virtual void show(void)const = 0;
protected:
	int x, y;			//坐标
	int width, height;	//宽，高
};

#endif