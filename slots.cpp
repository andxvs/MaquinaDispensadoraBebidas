#include "slots.h"

Slots::Slots(string fila, string columna)
{
    _fila = fila;
    _columna = columna;
}

string Slots::SlotAssign(string fila, string columna)
{
    fila.append(columna);
    return fila;
}

int Slots::SlotLocation(string slotid)
{
   if (slotid == "A1"){return 0;}
   if (slotid == "A2"){return 1;}
   if (slotid == "A3"){return 2;}
   if (slotid == "A4"){return 3;}
   if (slotid == "A5"){return 4;}
   if (slotid == "B1"){return 5;}
   if (slotid == "B2"){return 6;}
   if (slotid == "B3"){return 7;}
   if (slotid == "B4"){return 8;}
   if (slotid == "B5"){return 9;}
   if (slotid == "C1"){return 10;}
   if (slotid == "C2"){return 11;}
   if (slotid == "C3"){return 12;}
   if (slotid == "C4"){return 13;}
   if (slotid == "C5"){return 14;}
   if (slotid == "D1"){return 15;}
   if (slotid == "D2"){return 16;}
   if (slotid == "D3"){return 17;}
   if (slotid == "D4"){return 18;}
   if (slotid == "D5"){return 19;}
   if (slotid == "E1"){return 20;}
   if (slotid == "E2"){return 21;}
   if (slotid == "E3"){return 22;}
   if (slotid == "E4"){return 23;}
   if (slotid == "E5"){return 24;}
}

