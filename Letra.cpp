#include "Letra.h"
#include <iostream>
#include <string>
using namespace std;
Letra::Letra() {}
Letra::~Letra() {}
void Letra::setcadena() {
	getline(cin, c1);
}
void Letra::setcadena2() {
	getline(cin, c2);
}

int Letra::longitud() {
	return c1.size();
}

int Letra::comparacion() {
	if (c1 != c2) return 77;
	else return 0;
}

int Letra::contarvocal()
{
	int cont = 0;
	cout << endl << "Contar vocales" << endl << endl;
	for (int i = 0; i < c1.size(); i++)
		if (c1[i] == 'a' || c1[i] == 'e' || c1[i] == 'i' || c1[i] == 'o' || c1[i] == 'u')
		{
			cont++;
		}
	return cont;

}

void Letra::sacarsbtr()
{
	int pos;
	cout << endl << "Ingrese desde donde desea extraer el sbstring: ";
	cin >> pos;
	cin.ignore();
	cout << c1.substr(pos, c1.size() - pos);
}
void Letra::intercambiar() {
	string aux = c1;
	c1.swap(c2);
	c2.swap(aux);
	cout << "LA NUEVA CADENA 1 ES: " << c1 << endl;
	cout << "LA NUEVA CADENA 2 ES: " << c2 << endl;
	system("pause");
}

void Letra::encontrarchar() {
	if (c1.find(c2) >= 0) cout << "APARECE DENTRO DE LA FRASE DESDE EL CARACTER: " << c1.find(c2) << "hasta el caracter " << c1.find(c2) + size(c2) << endl;

}
void Letra::invertirfrase() {
	int longitud;
	char aux;
	longitud = c1.length();
	for (int i = 0; i < longitud / 2; i++)
	{
		aux = c1[i];
		c1[i] = c1[longitud - 1 - i];
		c1[longitud - 1 - i] = aux;
	}
	cout << "La cadena invertida es: " << c1 << endl;

}
void Letra::determinarpal() {
	string var2;
	var2 = c1;
	if (var2.compare(c1) == 0)
		cout << "Es un palindromo ";
}
