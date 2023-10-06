#include"Settings.h"

#include"Data.h"

vector<Book> _data_(1);
int _size_ = _data_.size() - 1;

void load_data(void) {
	Book tmp;
#ifdef _TEXT_MODE_
#define _BINARY_MODE_
	FILE* fin;
	fopen_s(&fin, "Data.txt", "r, ccs=utf-8");
	if(!fin) {
		initgraph(1024, 762);
		MessageBox(GetHWnd(), L"未读取到图书数据\"Data.txt\",程序已退出.", L"错误", MB_OK | MB_ICONERROR);
		closegraph();
		exit(EXIT_FAILURE);
	}
	int size; fwscanf(fin, L"%d ", &size);
	for (int i = 1; i <= size; ++i) {
		fwscanf(fin, L"%s %s %s %s %lf ", tmp.id, tmp.name, tmp.author, tmp.publish, &tmp.price);
		_data_.push_back(tmp);
	}	
	fclose(fin);
#endif

#ifndef _BINARY_MODE_
	ifstream file("Data.txt", std::ios::in | std::ios::binary);
	if (file.fail()) {
		initgraph(1024, 762);
		MessageBox(GetHWnd(), L"未读取到图书数据\"Data.txt\",程序已退出.", L"错误", MB_OK | MB_ICONERROR);
		closegraph();
		exit(EXIT_FAILURE);
	}
	while (file.read((char*)&tmp, sizeof(Book)))
		_data_.push_back(tmp);
	file.close();
#endif
	_size_ = _data_.size() - 1;
}

void output_data(void) {
	Book tmp;
#ifdef _TEXT_MODE_
	load_data();
	for (int i = 1; i < _data_.size(); ++i)
		_data_[i].display();
#endif

#ifndef _BINARY_MODE_
	ifstream file("Data.txt", std::ios::binary);
	if (file.fail()) {
		initgraph(1024, 762);
		MessageBox(GetHWnd(), L"未读取到图书数据\"Data.txt\",程序已退出.", L"错误", MB_OK | MB_ICONERROR);
		closegraph();
		exit(EXIT_FAILURE);
	}
	while (file.read((char*)&tmp, sizeof(Book)))
		tmp.display();
	file.close();
#endif
}

void write_data(void) {
#ifdef _RELOAD_BOOK_DATA_
	Book a(L"1", L"A", L"CusA", L"出版社A", 2514),
		b(L"2", L"B", L"CusB", L"出版社B", 996),
		c(L"3", L"C", L"CusC", L"出版社C", 955),
		d(L"4", L"D", L"CusD", L"出版社D", 2301),
		e(L"5", L"E", L"CusE", L"出版社E", 69),
		f(L"6", L"F", L"CusF", L"出版社F", 73),
		g(L"7", L"G", L"CusG", L"出版社G", 84),
		h(L"8", L"H", L"CusH", L"出版社H", 27),
		i(L"9", L"I", L"CusI", L"出版社I", 127),
		j(L"10", L"J", L"CusJ", L"出版社J", 325),
		k(L"11", L"K", L"CusK", L"出版社K", 42),
		l(L"12", L"L", L"CusL", L"出版社L", 95),
		m(L"13", L"M", L"CusM", L"出版社M", 27),
		n(L"13", L"M", L"CusM", L"出版社M", 44);

	vector<Book>tmp{ a,b,c,d,e,f,g,h ,i,j,k,l,m ,n};

#ifdef _TEXT_MODE_
	FILE* fout;
	fopen_s(&fout, "Data.txt", "w, ccs=utf-8");
	fwprintf(fout, L"%d\n", tmp.size());
	for (int i = 0; i < tmp.size(); ++i)
		fwprintf(fout, L"%s %s %s %s %lf\n",
			tmp[i].getID(), tmp[i].getName(), tmp[i].getAuthor(), tmp[i].getPub(), tmp[i].getPrice());
	fclose(fout);
#endif

#ifndef _BINARY_MODE_
	ofstream file("Data.txt", std::ios::out | std::ios::binary);
	for (Book r : tmp) file.write((const char*)&r, sizeof(Book));

	file.close();
#endif

#endif
}
