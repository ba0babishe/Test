#pragma once
#include <iostream>
using namespace std;

class items;

class items
{
private:
	string name;
	string barcode;
	int price;
public:
	items(string name, string barcode, int price); //конструктор класса товаров
	items();
	void setName(string name);
	string getName();
	void setBarcode(string barcode);
	string getBarcode();
	void setPrice(int price);
	int getPrice();
	void show(); // метод вывода имени, штрих-кода и цены
};

