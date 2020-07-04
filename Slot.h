#ifndef SLOT_H
#define SLOT_H

using namespace std;

class Slot
{
    private:
        string _row;
        int _column;
    public:
        Slot(string, int);
        string SlotAssign(string row, int column);
};

#endif // SLOT_H
