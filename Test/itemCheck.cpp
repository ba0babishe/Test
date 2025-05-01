#include "itemCheck.h"
using namespace std;

itemCheck::itemCheck(string name, string barcode, int price, int count):items(name, barcode, price) {
	this->count = count;
}


int itemCheck::getCount() {
	return this->count;
}

void itemCheck::setCount(int count) {
	this->count = count;
}