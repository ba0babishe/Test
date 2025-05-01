#include "check.h"

check::check() {

}

void check::setItemList(vector<itemCheck> itemList) {
	this->itemList = itemList; 
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
				cout << "\n--------\количество товара не может быть отрицательным\n--------\n";
			}
			calcSum();
			return;
		}
	}
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
		cout <<"\nтовар #" << i + 1;
		cout << " - Наименование: " << itemList.at(i).getName() << endl;
		cout << "Штрих-код: " << itemList.at(i).getBarcode() << endl;
		cout << "Цена за ед. товара: " << itemList.at(i).getPrice() << endl;
		cout << "Количество ед. товара: " << itemList.at(i).getCount() << endl;
	}
	calcSum();
	cout << "Итого: " << sum << endl;
	if (card) {
		cout << "Чек был оплачен картой" << endl;
	}
	else {
		cout << "Чек был оплачен наличными, сумма сдачи:" << back << endl;
	}
}
