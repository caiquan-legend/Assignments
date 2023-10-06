#include "Window.h"

int main(void) {
#ifdef _RELOAD_BOOK_DATA_
	write_data();
#endif
	load_data();
	Window res(_width_, _height_);
	res.show();
	res.messageLoop();
	return 0;
}