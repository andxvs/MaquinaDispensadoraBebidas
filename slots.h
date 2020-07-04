#ifndef SLOTS_H
#define SLOTS_H
#include <string>
#include <iostream>

using namespace std;

class Slots
{

private:
    string _columna;
    string _fila;
    string _slot_id;

public:
    Slots(string, string);
    Slots(string);
    string SlotAssign(string fila, string columna);
    int SlotLocation(string slot_id);
};

#endif // SLOTS_H
