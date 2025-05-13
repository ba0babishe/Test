#pragma once
#include "items.h"
#include <iostream>
using namespace std;
class itemCheck :
    public items
{
private:
    int count;
public:
    itemCheck(string name, string barcode, int price, int count);
    int getCount();
    void setCount(int count);
};

