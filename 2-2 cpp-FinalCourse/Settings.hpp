#ifndef _Settings_
#define _Settings_
#include <easyx.h>
#include<iostream>
//禁用数据函数
#define _NOT_EMPLOYEE_

//禁用多态异常
#define _NOT_MULTIERROR_


constexpr unsigned
_Move_Color = LIGHTBLUE,		//鼠标移动时按钮颜色
_Click_Color = RED | LIGHTBLUE;	//鼠标点击时按钮颜色

//表格竖线
extern const int const line_y[8];

//部门Hashmap
extern const wchar_t const _Department[9][6];

//<部门,工资>统计
extern std::pair<unsigned, double> count_num[9];

//COLORREF _color = HSLtoRGB(300, 10, 5.7f);
#endif