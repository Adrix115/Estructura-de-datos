#pragma once
#include<iostream>
#include<string>
using namespace std;

class Dato	
{
public:
    int Codigo;
    string Nombre;
    string Carrera;
    Dato() {
        Codigo = 0;
        Nombre = "Unknown";
        Carrera = "Unknown";
    }
    friend ostream& operator<<(ostream& os, const Dato& dato) {
        os << "Codigo: " << dato.Codigo << ", Nombre: " << dato.Nombre << ", Carrera: " << dato.Carrera;
        return os;
    }
};

