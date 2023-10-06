#pragma once
#ifndef _Heap_
#define _Heap_
#include"Books.h"
using std::ostream;
using std::cout;

class minHeap {
public:
	minHeap(int cap = 10);
	minHeap(const minHeap&);
	~minHeap(void);
	bool empty(void)const;
	int size(void)const;
	const Book& top(void);
	void pop(void);
	void push(const Book&);
	void initialize(Book*, int);
	void output(ostream& ous = cout)const;
protected:
	void changeHeap(Book*&, int, int);
private:
	int heapSize;
	int arrayLength;
	Book* heap;
};
#endif