
#include <iostream>

using namespace std;

    int factorial(int n);
    int potencia(int base, int exponente);
    double calcularSerie(int x, int n);

    int main(){
    int opcion;
    do {
        cout << "MENU:" << endl;
        cout << "1. Calcular factorial" << endl;
        cout << "2. Calcular potencia" << endl;
        cout << "3. Calcular serie" << endl;
        cout << "0. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int num;
                cout << "Ingresa un número para calcular su factorial: ";
                cin >> num;
                cout << "El factorial de " << num << " es " << factorial(num) << endl;
                break;
            }
            case 2: {
                int base, exp;
                cout << "Ingresa la base: ";
                cin >> base;
                cout << "Ingresa el exponente: ";
                cin >> exp;
                cout << base << " elevado a la " << exp << " es " << potencia(base, exp) << endl;
                break;
            }
            case 3: {
                int x, n;
                cout << "Ingresa el valor de x: ";
                cin >> x;
                cout << "Ingresa el valor de n: ";
                cin >> n;
                cout << "El resultado de la serie es: " << calcularSerie(x, n) << endl;
                break;
            }
            case 0:
                cout << "¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, selecciona una opción válida." << endl;
        }
    } while (opcion != 0);
    
        return 0;
    }
    
    int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; i++) 
        fact *= i;
    return fact;
    }

    int potencia(int base, int exponente) {
    int result = 1; 
    for (int i = 0; i < exponente; i++) 
        result *= base;
    return result;
    }

    double calcularSerie(int x, int n) {
    double suma = 0.0;
    for (int i = 1; i <= n; i++) 
        suma += potencia(x, i) / (factorial(i));
    return suma;
    }
    