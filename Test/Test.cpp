#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "money.h"
#include "items.h"
#include "smena.h"
#include "check.h"
#include "itemCheck.h"

using namespace std;

vector<items> jsonParser() {
    string json;
    string line;
    ifstream in("token.json"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            json += line; // добавляем строку из файла к строке программы 
        }
    }
    in.close(); //закрываем файл
    vector<items> it; //объявление вектора

    int nameId = 0, barcodeId = 0, priceId = 0; //указатели (хранят в себе номер символа после которого идет имя/штрих-код/цена)

    while (true) {
        int First, Last; // номера символов(первого и последнего) значения параметра

        string name, barcode;
        double price;

        nameId = json.find("\"name\":", nameId); // Поиск параметра имени в json файле
        if (nameId == -1) {
            break;
        }
        First = json.find("\"", nameId + 7); //первый символ имени
        Last = json.find("\"", json.find("\"", nameId + 7) + 1); //последний символ имени
        name = json.substr(First + 1, Last - First - 1); // создание подстроки имени

        barcodeId = json.find("\"barcode\":", barcodeId); // Поиск параметра штрих-кода в json файле
        First = json.find("\"", barcodeId + 11); //первый символ штрих-кода
        Last = json.find("\"", json.find("\"", barcodeId + 11) + 1); //прследний символ штрих-кода
        barcode = json.substr(First + 1, Last - First - 1); // создание подстроки штрих-кода

        priceId = json.find("\"price\":", priceId); // Поиск параметра цены в json файле
        First = json.find("\"", priceId + 8); //первый символ цены
        Last = json.find("\"", json.find("\"", priceId + 8) + 1); //последний символ цены
        price = stoi(json.substr(First + 1, Last - First - 1)); //создание подстроки цены

        nameId += 7; //добавление числа к "указателю" для продолжения поиска по файлу
        barcodeId += 11; //добавление числа к "указателю" для продолжения поиска по файлу
        priceId += 8; //добавление числа к "указателю" для продолжения поиска по файлу

        items* item;
        item = new items(name, barcode, price); //объявляем и определяем экземпляра класса, вызвав конструктор

        it.push_back(*item); //добавление объекта в вектор


    }
    return it; // возвращаем полученный вектор
}


items findBy_barcode(vector<items> itemList, string barcode) {
    for (int i = 0; i < itemList.size(); i++) { // цикл перебора всех элементов вектора с товарами
        if (itemList.at(i).getBarcode() == barcode) { // проверяем штрих-код элемента i на совпадение с требуемым штрих-кодом
            return itemList.at(i);
        }
    }
}

items findBy_name(vector<items> itemList, string name) {
    for (int i = 0; i < itemList.size(); i++) { // цикл перебора всех элементов вектора с товарами
        if (itemList.at(i).getName() == name) { // проверяем имя элемента i на совпадение с требуемым именем
            return itemList.at(i);
        }
    }
}

int main()
{
    vector<items> item_list;
    setlocale(LC_ALL, "Russian");
    item_list = jsonParser();
    vector<smena*> smenaList;
    while (true) {
        cout << "Что вы хотите сделать? (Введите нужную цифру)\n1.Посмотреть список закрытых смен\n2.Открыть смену\nДля выхода из программы введите любой другой символ\n";
        int o;
        cin >> o;
        if (o == 1) {
            if (smenaList.empty()) {
                cout << "Нет информации о сменах" << endl;
            }
            else {
                cout << "\n-------------\nСписок смен:\n";
                for (int i = 0; i < smenaList.size();i++) {
                    cout << i << ": Смена была открыта сотрудником по имени ";
                    cout << smenaList.at(i)->getName_employee() << "; В данный момент смена ";
                    if (smenaList.at(i)->getOpenOr_close()) {
                        cout << "Открыта";
                    }
                    else {
                        cout << "Закрыта";
                    }
                }
                cout << "\n\nХотите посмотреть подробную информацию о какой либо смене?\nВведите цифру 1, чтобы посмотреть информацию о сменах\n";
                int ii;
                cin >> ii;
                switch (ii) {
                case 1:
                    cout << "\n\nВведите номер смены для просмотра подробной информации:\n";
                    cin >> ii;
                    try {
                        smenaList.at(ii)->showCheck_List();
                        smenaList.at(ii)->showMoney_list();
                    }
                    catch (int code) {
                        cerr << "Ошибка! Введен неверный номер смены";
                    }
                    break;
                default:
                    break;
                }
            }
        }
        else if (o == 2) {
            cout << "Для открытия смены требуется ваше имя, введите его далее: ";
            string name;
            cin >> name;
            cout << "Если в кассе нестандартное количество наличных, то введите цифру 1, иначе введите любое другое число: ";
            smena *Smena = new smena(true,name);
            smenaList.push_back(Smena);
            int o;
            cin >> o;
            if (o == 1) {
                while (true) {
                    smenaList.back()->showMoney_list();
                    cout << "Введите номинал, который хотите изменить/добавить (Для выхода из редактирования количества наличных введите -1)\n";
                    int tempNominal, tempCount;
                    cin >> tempNominal;
                    if (tempNominal == -1) {
                        break;
                    }
                    cout << "Введите количество купюр, которые хотите добавить(Чтобы взять деньги из кассы пишите отрицательные числа, если взять больше чем есть, то номинал пропадет из кассы)\n";
                    cin >> tempCount;
                    try {
                        smenaList.back()->addMoney_Type(tempNominal, tempCount);
                    }
                    catch (int code) {
                        cerr << "Ошибка! Введен некорректный тип номинала или количества купюр";
                    }
                }
            }
            cout << "Вы успешно открыли смену.\n";
            while (true) {
                cout << "\n\n------\n------\nЧто вы хотите сделать?\n1)Сформировать чек(Продажа товара)\n2)Посмотреть чеки смены\n3)Посмотреть кассу\n4)Закрыть смену\nДля выхода из программы сначала закройте смену\n";
                int ii2;
                vector<itemCheck> tempItemCheck;
                check tempCheck;
                cin >> ii2;
                if (ii2 == 1) {
                    while (true) {
                        items tempItem;
                        int i2;
                        cout << "Как вы хотите найти товар?\n1)По штрих-коду\n2)По имени\n3)Закрыть чек\n4)Вывести базу товаров";
                        cin >> i2;
                        if (i2 == 1) {
                            string barcode;
                            cout << "Введите штрих-код" << endl;
                            cin >> barcode;
                            for (int i = 0; i < item_list.size(); i++) {
                                if (item_list.at(i).getBarcode() == barcode) {
                                    tempItem = item_list.at(i);
                                }
                            }
                            if (tempItem.getBarcode() == "") {
                                continue;
                            }
                            cout << "Сколько товара вы хотите добавить в чек?(Для того чтобы убрать товар из чека введите отрицательное число)\n";
                            int i3;
                            cin >> i3;
                            itemCheck tem(tempItem.getName(), tempItem.getBarcode(), tempItem.getPrice(), i3);
                            tempCheck.addItem(tem);
                        }
                        else if (i2 == 2) {
                            string name;
                            cout << "Введите название товара" << endl;
                            cin >> name;
                            for (int i = 0; i < item_list.size(); i++) {
                                if (item_list.at(i).getName() == name) {
                                    tempItem = item_list.at(i);
                                }
                            }
                            if (tempItem.getBarcode() == "") {
                                continue;
                            }
                            cout << "Сколько товара вы хотите добавить в чек?(Для того чтобы убрать товар из чека введите отрицательное число)\n";
                            int i3;
                            cin >> i3;
                            itemCheck tem(tempItem.getName(), tempItem.getBarcode(), tempItem.getPrice(), i3);
                            tempCheck.addItem(tem);
                        }
                        else if (i2 == 3) {
                            cout << "Обшая сумма чека: " << tempCheck.getSum();
                            cout << endl << "Каким способом будет произведена оплата?\n1)Картой\n2)Наличными\nДля отмены закрытия чека введите любое другое число\n";
                            int i3;
                            cin >> i3;
                            if (i3 == 1) {

                                tempCheck.setCard(true);
                                smenaList.back()->addCheck(tempCheck);
                                break;
                            }
                            else if (i3 == 2) {
                                cout << endl << "Введите сумму предоставленную для оплаты: ";
                                int sumPurch;
                                cin >> sumPurch;
                                if (!smenaList.back()->giveBack(sumPurch - tempCheck.getSum())) {
                                    cout << "\n-----\nСдачи не хватает, возвращение к редактированию чека\n-----\n";
                                }
                                else {
                                    tempCheck.setBack(sumPurch - tempCheck.getSum());
                                    smenaList.back()->addCheck(tempCheck);
                                    while (true) {
                                        cout << "Добавьте наличные, которыми была произведена оплата:\n введите номинал, который хотите изменить/добавить (Для выхода из редактирования количества наличных введите -1)\n";
                                        int tempNominal, tempCount;
                                        cin >> tempNominal;
                                        if (tempNominal == -1) {
                                            break;
                                        }
                                        cout << "Введите количество купюр, которые хотите добавить(Чтобы взять деньги из кассы пишите отрицательные числа, если взять больше чем есть, то номинал пропадет из кассы)\n";
                                        cin >> tempCount;
                                        try {
                                            smenaList.back()->addMoney_Type(tempNominal, tempCount);
                                        }
                                        catch (int code) {
                                            cerr << "Ошибка! Введен некорректный тип номинала или количества купюр";
                                        }
                                    }
                                    break;
                                }
                            }

                        }
                        else if (i2 == 4) {
                            cout << "Список товаров: " << endl;
                            for (int i = 0; i < 4; i++) {
                                item_list.at(i).show();
                            }
                        }
                    }
                }
                else if (ii2 == 2) {
                    smenaList.back()->showCheck_List();
                }
                else if (ii2 == 3) {
                    smenaList.back()->showMoney_list();
                }
                else if (ii2 == 4) {
                    smenaList.back()->setOpenOr_close(false);
                    break;
                }

            }

        }
        else {
            return 0;
        }
    }
}
