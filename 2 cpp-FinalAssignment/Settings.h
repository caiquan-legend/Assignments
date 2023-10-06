#ifndef _Settings_
#define _Settings_

//跳过安全检测异常
#define _CRT_SECURE_NO_WARNINGS

//不展示排序功能
#define _NOT_SORT_

//文本模式/二进制模式读写
#define _TEXT_MODE_

//修复读写问题
//#define _RELOAD_BOOK_DATA_

//测试宏
//#define _NOT_SHOW_EDIT_BOOK_BUTTON_

//测试宏
//#define _NOT_CHECK_BOOK_



//控制窗口大小
constexpr int _width_ = 1024, _height_ = 792;

//主窗口按钮大小
constexpr int _main_width_ = 256, _main_height_ = 99;

//主窗口按钮位置量
constexpr int main_up = _height_ / 3, main_down = _height_ / 3 + 2.5 * _main_height_;

//显示窗口按钮大小
constexpr int _view_width_ = 96, _view_height_ = 33;

//显示窗口按钮位置量
constexpr int view_b1 = 11 * _height_ / 12;

//表格边距
constexpr int _edgeX_ = _width_ / 64, _edgeY_ = _height_/32;
//表格横纵间距
constexpr int _stepX_ = _width_ / 32, _stepY_ = _height_ / 16;
constexpr int _step = _width_ / 6;

//每个表格中的实际行数
constexpr int _times_ = (_height_ - 4 * _edgeY_ - _stepY_) / _stepY_;

#endif