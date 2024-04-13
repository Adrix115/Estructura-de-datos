#pragma once
#include"Dato.h"
class Nodo	
{
public:
    Dato dato;
    Nodo* puntero;
    Nodo() { 
        puntero = NULL;
    }
};