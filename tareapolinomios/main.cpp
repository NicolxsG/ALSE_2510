#include <iostream>
#include <string.h>
#include <vector>
#include <ctype.h>

using namespace std;

// Función para recorrer el polinomio y convertirlo a un vector de coeficientes
vector<int> recorrerpolinomio(const char* polinomio) {
    vector<int> coeficientes(100, 0); // Estoy asumiendo que el máximo coeficiente es 100
    int i = 0, n = strlen(polinomio);
    int signo = 1, coef = 0, exponente = 0;

    while (i < n) {
        switch (polinomio[i]) {
            case '-':
                if (coef != 0 || exponente != 0) {
                    coeficientes[exponente] = signo * coef;
                    coef = 0; exponente = 0;
                }
                signo = -1;
                break;
            case '+':
                if (coef != 0 || exponente != 0) {
                    coeficientes[exponente] = signo * coef;
                    coef = 0; exponente = 0;
                }
                signo = 1;
                break;
            case 'x':
                if (coef == 0) coef = 1;
                exponente = 1;
                i++;
                if (i < n && polinomio[i] == '^') {
                    i++;
                    exponente = 0;
                    while (i < n && isdigit(polinomio[i])) {
                        exponente = exponente * 10 + (polinomio[i] - '0');
                        i++;
                    }
                }
                break;
            default:
                if (isdigit(polinomio[i])) {
                    int num = 0;
                    while (i < n && isdigit(polinomio[i])) {
                        num = num * 10 + (polinomio[i] - '0');
                        i++;
                    }
                    if (exponente == 0) {
                        coef = num;
                    } else {
                        exponente = num;
                    }
                }
                break;
        }
        i++;
    }
    if (coef != 0 || exponente != 0) {
        coeficientes[exponente] = signo * coef;
    }
    return coeficientes;
}

vector<int> SumarPolinomios(const vector<vector<int>>& polinomios) {
    int gradoMax = 0;
    for (const auto& polinomio : polinomios) {
        gradoMax = max(gradoMax, (int)polinomio.size());
    }
    vector<int> resultado(gradoMax, 0);
    for (const auto& polinomio : polinomios) {
        for (int i = 0; i < polinomio.size(); i++) {
            resultado[i] += polinomio[i];
        }
    }
    return resultado;
}

void imprimir(const vector<int>& polinomio) {
    bool PrimerTermino = true;
    for (int i = polinomio.size() - 1; i >= 0; i--) {
        if (polinomio[i] != 0) {
            if (!PrimerTermino) {
                cout << (polinomio[i] > 0 ? " + " : " - ");
            } else {
                if (polinomio[i] < 0) cout << "-";
                PrimerTermino = false;
            }
            if (abs(polinomio[i]) != 1 || i == 0) {
                cout << abs(polinomio[i]);
            }
            if (i > 0) {
                cout << "x";
                if (i > 1) {
                    cout << "^" << i;
                }
            }
        }
    }
    if (PrimerTermino) cout << "0";
    cout << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Uso: ./sumapolinomios \"polinomio1\" \"polinomio2\" ... \"polinomioN\"" << endl;
        return 1;
    }
    cout << "He recibido " << argc - 1 << " polinomios" << endl;
    vector<vector<int>> polinomios;
    for (int i = 1; i < argc; i++) {
        polinomios.push_back(recorrerpolinomio(argv[i]));
    }

    vector<int> resultado = SumarPolinomios(polinomios);

    cout << "\nEl resultado de la suma es: ";
    imprimir(resultado);

    return 0;
}
