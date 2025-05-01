#include "items.h"
#include <iostream>
#include <string>
using namespace std;

items::items(string name, string barcode, int price) {
	this->name = name;
	this->barcode = barcode;
	this->price = price;
}
items::items() {
	name = "";
	barcode = "";
};
void items::setName(string name) {
	this->name = name;
};
string items::getName() {
	return this->name;
};
void items::setBarcode(string barcode) {
	this->barcode = barcode;
};
string items::getBarcode() {
	return this->barcode;
};
void items::setPrice(int price) {
	this->price = price;
};
int items::getPrice() {
	return this->price;
};

void items::show() {
	cout << "\n-----\nname: " << name << "\nbarcode: " << barcode << "\nprice: " << price << "\n-----\n";
}