#include"Component.h"
Component::Component(int _x, int _y, int _width, int _height) :
	x(_x), y(_y), width(_width), height(_height) {}
void Component::setRectangle(int _x, int _y, int _width, int _height) {
	x = _x, y = _y, width = _width, height = _height; show();
}
int Component::getX(void)const { return x; }
int Component::getY(void)const { return y; }
int Component::getWidth(void)const { return width; }
int Component::getHeight(void)const { return height; }
void Component::setX(int _x) { x = _x; show(); }
void Component::setY(int _y) { y = _y; show(); }
void Component::setWidth(int _width) { width = _width; show(); }
void Component::setHeight(int _height) { height = _height; show(); }