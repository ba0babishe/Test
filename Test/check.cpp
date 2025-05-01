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
				cout << "\n--------\nÂ ÷åêå íå ìîæåò áûòü îòðèöàòåëüíîå êîëè÷åñòâî òîâàðà, äîáàâëåíèå îòìåíåíî\n--------\n";
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
		cout <<"\nÒîâàð #" << i + 1;
		cout << " - Íàçâàíèå: " << itemList.at(i).getName() << endl;
		cout << "Íîìåð øòðèõ-êîäà: " << itemList.at(i).getBarcode() << endl;
		cout << "Öåíà çà åä. òîâàðà: " << itemList.at(i).getPrice() << endl;
		cout << "Êîëè÷åñòâî åä. òîâàðà: " << itemList.at(i).getCount() << endl;
	}
	calcSum();
	cout << "Îáùàÿ ñóììà ÷åêà: " << sum << endl;
	if (card) {
		cout << "×åê áûë îïëà÷åí êàðòîé" << endl;
	}
	else {
		cout << "×åê áûë îïëà÷åí íàëè÷íûìè, ñóììà ñäà÷è: " << back << endl;
	}
}
