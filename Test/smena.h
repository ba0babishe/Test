#pragma once
#include <iostream>
#include <vector>
#include "check.h"
#include "money.h"
using namespace std;
class smena
{
private:
	bool openOr_close;
	string nameEmployee;
	int sum;
	vector<money*> moneyList;
	vector<check> checkList;
public:
	smena(bool openOr_close, string nameEmployee);
	void addCheck(check Check);
	string getName_employee();
	void showMoney_list();
	bool getOpenOr_close();
	void setOpenOr_close(bool status);
	void setName_employee(string name);
	void addMoney_Type(int cost, int count);
	void showCheck_List();
	int getSum();
	void setSum();
	void moneyClear();
	bool giveBack(int amountFirst);
};

