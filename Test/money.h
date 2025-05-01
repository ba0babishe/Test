#pragma once
#include <iostream>
using namespace std;
class money
{
private:
	int cost;
	int count;
public:
	money(int cost, int count);
	money();
	int getCost();
	void setCost(int cost);
	void setCount(int count);
	int getCount();
};

