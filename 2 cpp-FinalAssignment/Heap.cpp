#include"Heap.h"
#include"Exception.h"
#include <iomanip>

using std::setw;
using std::copy;
using std::min;

bool minHeap::empty(void)const { return heapSize == 0; }

int minHeap::size(void)const { return heapSize; }

void minHeap::changeHeap(Book*& arr, int _old, int _new) {
	if (_new < 0)return;
	Book* tmp = new Book[_new];
	int number = min(_old, _new);
	copy(arr, arr + number, tmp);
	delete[]arr; arr = tmp;
}

minHeap::minHeap(int Cap) {
	heapSize = 0;
	arrayLength = Cap + 1;
	heap = new Book[arrayLength];
}
minHeap::minHeap(const minHeap& theHeap) {
	arrayLength = theHeap.arrayLength;
	heapSize = theHeap.heapSize;
	heap = new Book[arrayLength];
	copy(theHeap.heap, theHeap.heap + heapSize, heap);
}
minHeap::~minHeap(void) { delete[]heap; }

const Book& minHeap::top(void) {
	if (heapSize == 0)
		throw illegalValue("");

	return heap[1];
}

void minHeap::output(ostream& out)const {
	for (int i = 1, n = 0; i <= heapSize; ++i) {
		if (i == (1 << n)) {
			out << "\n";
			out << ++n;
			out << setw(6) << std::left << heap[i];
		}
	}
}

void minHeap::push(const Book& val) {
	if (heapSize == arrayLength - 1) {
		changeHeap(heap, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] > val) {
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = val;
}

void minHeap::pop(void) {
	if (!heapSize)return;
	Book last = heap[heapSize--];
	int current = 1, child = 2;
	while (child <= heapSize) {
		if (child<heapSize && heap[child]>heap[child + 1])child++;
		if (last <= heap[child])break;
		heap[current] = heap[child];
		current = child;
		child *= 2;
	}
	heap[current] = last;
}

void minHeap::initialize(Book* theHeap, int Size) {
	delete[]heap;
	heap = theHeap;
	heapSize = Size;
	for (int root = heapSize / 2; root >= 1; root--) {
		Book element = heap[root];
		int child = 2 * root;
		while (child <= heapSize) {
			if (child<heapSize && heap[child]>heap[child + 1])child++;
			if (element <= heap[child])break;
			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = element;
	}
}