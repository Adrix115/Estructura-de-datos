#pragma once
#include <string>
using namespace std;
class Letra
{
private:
	string c1;
	string c2;
public:
	Letra();
	~Letra();
	void setcadena();
	void setcadena2();
	int longitud();
	int comparacion();
	int contarvocal();
	void sacarsbtr();
	void intercambiar();
	void encontrarchar();
	void invertirfrase();
	void determinarpal();
};
