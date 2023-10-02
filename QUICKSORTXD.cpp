#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void intercambiar(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void quicksort(int arr[], int primero, int ultimo) {
    if (primero < ultimo) {
        int pivote = arr[(primero + ultimo) / 2];
        int i = primero;
        int j = ultimo;

        while (i <= j) {
            while (arr[i] < pivote) i++;
            while (arr[j] > pivote) j--;

            if (i <= j) {
                intercambiar(arr[i], arr[j]);
                i++;
                j--;
            }
        }

        if (primero < j) {
            quicksort(arr, primero, j);
        }
        if (i < ultimo) {
            quicksort(arr, i, ultimo);
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    int numeros_aleatorios[30];

    cout << "NÚMEROS GENERADOS:" << endl;
    for (int i = 0; i < 30; i++) {
        numeros_aleatorios[i] = rand() % 100;  // Cambiar el 100 al rango deseado
        cout << numeros_aleatorios[i] << ", ";
    }

    quicksort(numeros_aleatorios, 0, 29);

    cout << "\nNÚMEROS ORDENADOS:" << endl;
    for (int i = 0; i < 30; i++) {
        cout << numeros_aleatorios[i] << ", ";
    }

    cout << "\nPROCESO COMPLETADO " << endl;

    return 0;
}

