#pragma once
#include"Nodo.h"
class Cola	
{
private:
    Nodo* inicio;
    Nodo* fin;
public:
    Cola();
    void Encolar(Nodo*& inicio, Nodo*& fin);
    void Desencolar(Nodo*& inicio);
    void MostrarCola(Nodo*& inicio);
};