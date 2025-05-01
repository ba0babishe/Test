#include "check.h"

check::check() {

}

void check::setItemList(vector<itemCheck> itemList) {
	cout << "\aaaaa\n";
	for (int i = 0; i < itemList.size(); i++) {
		cout << "   " << itemList.size() << itemList.at(i).getName() << "   " << itemList.at(i).getCount() << "   " << itemList.at(i).getBarcode() << "   " << itemList.at(i).getPrice() << endl;
	}
	this->itemList = itemList;
	cout << "\nfffff\n";
	for (int i = 0; i < this->itemList.size(); i++) {
		cout << "   " << this->itemList.size() << this->itemList.at(i).getName() << "   " << this->itemList.at(i).getCount() << "   " << this->itemList.at(i).getBarcode() << "   " << this->itemList.at(i).getPrice() << endl;
	}
	cout << "\dddddd\n";
}

void check::addItem(itemCheck item) {
	for (int i = 0; i < itemList.size(); i++) {
		if (item.getBarcode() == itemList.at(i).getBarcode()) {
			if (itemList.at(i).getCount() + item.getCount() > 0) {
				itemList.at(i).setCount(itemList.at(i).getCount() + item.getCount());
			}
			else if (itemList.at(i).getCount() + item.getCount() == 0) {
				auto iter = itemList.cbegin();
				itemList.erase(iter + i);
			}
			else {
				cout << "\n--------\nВ чеке не может быть отрицательное количество товара, добавление отменено\n--------\n";
			}
			cout << "\nADSFASF\n";
			calcSum();
			return;
		}
	}
	cout << "\n-----ADSFASF-------\n";
	itemList.push_back(item);
	calcSum();
}

int check::getSum() {
	calcSum();
	return this->sum;
}

int check::getBack() {
	return this->back;
}

void check::setCard(bool card) {
	this->card = card;
}

void check::calcSum() {
	sum = 0;
	for (int i = 0; i < itemList.size(); i++) {
		sum += itemList.at(i).getCount() * itemList.at(i).getPrice();
	}
}

void check::setSum(int sum) {
	this->sum = sum;
}

void check::setBack(int back) {
	this->back = back;
}

void check::showItem_List() {
	for (int i = 0; i < itemList.size(); i++) {
		cout <<"\nТовар #" << i + 1;
		cout << " - Название: " << itemList.at(i).getName() << endl;
		cout << "Номер штрих-кода: " << itemList.at(i).getBarcode() << endl;
		cout << "Цена за ед. товара: " << itemList.at(i).getPrice() << endl;
		cout << "Количество ед. товара: " << itemList.at(i).getCount() << endl;
	}
	calcSum();
	cout << "Общая сумма чека: " << sum << endl;
	if (card) {
		cout << "Чек был оплачен картой" << endl;
	}
	else {
		cout << "Чек был оплачен наличными, сумма сдачи: " << back << endl;
	}
}