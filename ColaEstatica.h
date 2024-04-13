#pragma once
#include <iostream>

#define MAX 100

using namespace std;

class Cola
{
private:
    int info[MAX];
    int inicio, fin;

public:
    Cola();
    bool Encolar(int Valor);
    bool Desencolar();
    bool PrimeroCola(int& Valor);
    bool ColaVacia();
    void mostrar();
    void VaciarCola();
};

