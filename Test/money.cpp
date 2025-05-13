#include "money.h"
#include <iostream>
using namespace std;

money::money(int cost, int count) {
	this->cost = cost;
	this->count = count;
}

money::money() {};

int money::getCost() {
	return this->cost;
}

void money::setCost(int cost) {
	this->cost = cost;
}

void money::setCount(int count) {
	this->count = count;
}

int money::getCount() {
	return this->count;
}