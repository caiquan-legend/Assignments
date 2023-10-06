#include"System.h"
#include"Exception.h"
using std::ifstream;
using std::ofstream;
using std::find;

System::System(void) { res.resize(1); }
bool System::read(const string& _file) {
	FILE* fin;
	fopen_s(&fin, "Clients.txt", "r, ccs=utf-8");
	if (!fin)return false;

	int _type ,size;
	fwscanf(fin, L"%d ", &size);

	for (int i = 0; i < size; ++ i) {
		fwscanf(fin, L"%d ", &_type);
		try {
			switch (_type) {
			case buyer::Client_type::_layfolk_: {
				layfolk A; A.read(fin);
				addClient(A);
			}break;
			case buyer::Client_type::_member_: {
				member B; B.read(fin);
				addClient(B);
			}break;
			case buyer::Client_type::_honoured_guest_:{
				honoured_guest C; C.read(fin);
				addClient(C);
			}break;
			default:throw ReadError();
			}
		}catch (ReadError) { break; }
		catch (...) { return false; }
	}
	fclose(fin);
	return true;
}

void System::write(const string& _file)const {
	FILE* fout;
	fopen_s(&fout, _file.c_str(), "w, ccs=utf-8");

	fwprintf(fout, L"%d\n", res.size() - 1);
	for (int i = 1; i < res.size(); ++i)
		res[i]->write(fout);
	fclose(fout);
}



void System::addClient(const layfolk& _layfolk) {
	layfolk* tmp = new layfolk(_layfolk);
	tmp->setID(res.size());
	res.push_back(tmp);
}

void System::addClient(const member& _member) {
	member* tmp = new member(_member);
	tmp->setID(res.size());
	res.push_back(tmp);
}

void System::addClient(const honoured_guest& _honoured_guest) {
	honoured_guest* tmp = new honoured_guest(_honoured_guest);
	tmp->setID(res.size());
	res.push_back(tmp);
}

void System::deleteClient(int index) {
	delete res[index];
	res.erase(res.begin() + index);
}



void System::add_Book(int pos, int index) {
	res[pos]->add_Book(index);
}

void System::delete_Book(int pos, int index) {
	res[pos]->delete_Book(index);
}
void System::set_pay(int pos) {
	res[pos]->setPay();
}



int System::search(const wchar_t* _name)const {
	if (empty())return -1;
	for (int i = 1; i < res.size(); ++i)
		if (res[i]->getName() == _name)return i;
	return -1;
}

int System::search(int id)const {
	if (empty())return -1;
	int l = 1, r = res.size() - 1;
	while (l < r) {
		int mid = l + r >> 1;
		if (res[mid]->getID() >= id)r = mid;
		else l = mid + 1;
	}
	if (res[r]->getID() == id)return r;
	return -1;
}

const buyer* System::getClient(int index)const {
	if (index < 1 || index >= res.size())return nullptr;
	return res[index];
}

void System::setClient(int index, buyer*& _client) {
	res[index] = _client;
}


#ifndef _NOT_SORT_
void System::sort_id(void) {
	sort(res.begin(), res.end(), [&](buyer*& a, buyer*& b) {return a->getID() < b->getID(); });
}

void System::sort_price(void) {
	sort(res.begin(), res.end(), [&](buyer*& a, buyer*& b) {return a->getPay() > b->getPay(); });
}
#endif


bool System::empty(void)const {
	return res.size() == 1;
}

int System::size(void)const {
	return res.size();
}

void System::clear(void) {
	for (int i = 1; i < res.size(); ++i) {
		//res[i]->clear();
		delete res[i];
	}
	res.resize(1);
}