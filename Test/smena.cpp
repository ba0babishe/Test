#include <iostream>
#include "smena.h"
#include "money.h"
using namespace std;


smena::smena(bool openOr_close, string nameEmployee) {
	sum = 0;
	this->openOr_close = openOr_close;
	this->nameEmployee = nameEmployee;
	money *oneR = new money(1, 25);
	this->moneyList.push_back(oneR);
	money* twoR = new money(2, 25);
	this->moneyList.push_back(twoR);
	money* fiveR = new money(5, 25);
	this->moneyList.push_back(fiveR);
	money* tenR = new money(10, 25);
	this->moneyList.push_back(tenR);
	money* half_hundredR = new money(50, 30);
	this->moneyList.push_back(half_hundredR);
	money* hundredR = new money(100, 20);
	this->moneyList.push_back(hundredR);
	money* twoHundredR = new money(200, 10);
	this->moneyList.push_back(twoHundredR);
	money* fiveHundredR = new money(500, 10);
	this->moneyList.push_back(fiveHundredR);
	money* thousandR = new money(1000, 10);
	this->moneyList.push_back(thousandR);
	money* twoThousandR = new money(2000, 5);
	this->moneyList.push_back(twoThousandR);
	money* fiveThousandR = new money(5000, 1);
	this->moneyList.push_back(fiveThousandR);
	for (int i = 0; i < moneyList.size(); i++) {
		sum += moneyList.at(i)->getCost() * moneyList.at(i)->getCount();
	}
}

void smena::addCheck(check Check) {
	checkList.push_back(Check);
}

void smena::setSum() {
	sum = 0;
	for (int i = 0; i < moneyList.size(); i++) {
		sum += moneyList.at(i)->getCost() * moneyList.at(i)->getCount();
	}
}

void smena::setOpenOr_close(bool status) {
	this->openOr_close = status;
}

void smena::moneyClear() {
	moneyList.clear();
}

void smena::setName_employee(string name) {
	this->nameEmployee = name;
}

void smena::addMoney_Type(int cost, int count) {
	for (int i = 0; i < moneyList.size(); i++) {
		if (moneyList.at(i)->getCost() == cost) {
			if (count + moneyList.at(i)->getCount() <= 0) {
				auto ii = moneyList.cbegin();
				moneyList.erase(ii + i);
			}
			moneyList.at(i)->setCount(count + moneyList.at(i)->getCount());
			return;
		}
	}
	money* temp = new money(cost, count);
	moneyList.push_back(temp);
	for (int i = moneyList.size() - 2; i >= 0; i--) {
		if (moneyList.at(i)->getCost() > moneyList.at(i + 1)->getCost()) {
			swap(moneyList.at(i), moneyList.at(i + 1));
			continue;
		}
		break;
	}
}

string smena::getName_employee() {
	return this->nameEmployee;
}

void smena::showMoney_list() {
	cout << "\n-----\nИнформация о деньгах в кассе:\n";
	for (int i = 0; i < moneyList.size(); i++) {
		cout << "\nНоминал: " << moneyList.at(i)->getCost();
		cout << "\nКоличество: " << moneyList.at(i)->getCount() << endl << endl;
	}
	setSum();
	cout << "Общая сумма: " << sum;
	cout << "\n----------------\n----------------\n";
}

bool smena::getOpenOr_close() {
	return this->openOr_close;
}

int smena::getSum() {
	return sum;
}

void smena::showCheck_List() {
	int sum = 0;
	cout << "\n-----\nИнформация о чеках за смену:\n";
	for (int i = 0; i < checkList.size(); i++) {
		cout << "\n\nЧек #" << i + 1;
		checkList.at(i).showItem_List();
	}
	cout << "\n----------------\n----------------\n";
}

bool smena::giveBack(int amountFirst) {
	vector<money*> moneyTemp_list;
	int amount = amountFirst;
	int index = moneyList.size()-1;
	if (amountFirst == 0) {
		cout << "Сдача не нужна" << endl;
		return true;
	}
	while (amount != 0 and index > 0) {
		if (amount % moneyList.at(index)->getCost() >= 0 and amount % moneyList.at(index)->getCost() != amount) {
			if (amount / moneyList.at(index)->getCost() > moneyList.at(index)->getCount()) {
				money * moneyTemp = new money(moneyList.at(index)->getCost(), moneyList.at(index)->getCount());
				moneyTemp_list.push_back(moneyTemp);
				amount -= moneyTemp->getCost() * moneyTemp->getCount();
				index--;
				continue;
			}
			else {
				int count = amount / moneyList.at(index)->getCost();
				money* moneyTemp = new money(moneyList.at(index)->getCost(), count);
				moneyTemp_list.push_back(moneyTemp);
				amount -= moneyTemp->getCost() * moneyTemp->getCount();
				index--;
				continue;
			}
		}
		index--;
	}
	cout << "\namount: " << amount << endl;
	if (amount != 0) {
		return false;
	}
	else {
		cout << "\nБыла выдана сдача" << amountFirst << " :\n";
		for (int i = 0; i < moneyTemp_list.size(); i++) {
			if (moneyTemp_list.at(i)->getCount() != 0) {
				cout << "Номинал: " << moneyTemp_list.at(i)->getCost() << "  Количество купюр: " << moneyTemp_list.at(i)->getCount() << endl;
			}
		}
		for (int i = 0; i < moneyList.size(); i++) {
			for (int i2 = 0; i2 < moneyTemp_list.size(); i2++) {
				if (moneyList.at(i)->getCost() == moneyTemp_list.at(i2)->getCost()) {
					moneyList.at(i)->setCount(moneyList.at(i)->getCount() - moneyTemp_list.at(i2)->getCount());
				}
			}
		}
	}
}