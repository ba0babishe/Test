#pragma once
#include <iostream>
#include <vector>
#include "itemCheck.h"
using namespace std;


class check
{
private:
	bool card;
	vector<itemCheck> itemList;
	int sum;
	int back;
public:
	check();
	void setItemList(vector<itemCheck> itemList);
	void addItem(itemCheck item);
	int getSum();
	int getBack();
	void showItem_List();
	void setCard(bool card);
	void setSum(int sum);
	void setBack(int back);
	void calcSum();
};

