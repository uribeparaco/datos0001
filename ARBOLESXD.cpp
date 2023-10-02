#include <iostream>

using namespace std;

struct Nodo {
    int valor;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo* padre;
};

Nodo* arbol = NULL;

Nodo* crearNodo(int valor, Nodo* padre = NULL) {
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->valor = valor;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    nuevoNodo->padre = padre;
    return nuevoNodo;
}

// Declaración adelantada de eliminarNodo
void eliminarNodo(Nodo*& nodo);

// Declaración de minimoNodo antes de su uso
Nodo* minimoNodo(Nodo*& nodo);

void insertarNodo(Nodo*& arbol, int valor, Nodo* padre = NULL) {
    if (!arbol) {
        arbol = crearNodo(valor, padre);
    } else if (valor < arbol->valor) {
        insertarNodo(arbol->izquierda, valor, arbol);
    } else {
        insertarNodo(arbol->derecha, valor, arbol);
    }
}

void mostrarArbol(Nodo*& arbol, int nivel = 0) {
    if (!arbol) return;
    
    mostrarArbol(arbol->derecha, nivel + 1);
    
    for (int i = 0; i < nivel; i++) {
        cout << "  ";
    }
    cout << arbol->valor << endl;
    
    mostrarArbol(arbol->izquierda, nivel + 1);
}

bool buscarNodoArbol(Nodo*& arbol, int valor) {
    if (!arbol) return false;
    
    if (arbol->valor == valor) return true;
    
    if (valor < arbol->valor) {
        return buscarNodoArbol(arbol->izquierda, valor);
    } else {
        return buscarNodoArbol(arbol->derecha, valor);
    }
}

void preorden(Nodo*& arbol) {
    if (!arbol) return;
    
    cout << arbol->valor << " ";
    preorden(arbol->izquierda);
    preorden(arbol->derecha);
}

void inorden(Nodo*& arbol) {
    if (!arbol) return;
    
    inorden(arbol->izquierda);
    cout << arbol->valor << " ";
    inorden(arbol->derecha);
}

void postorden(Nodo*& arbol) {
    if (!arbol) return;
    
    postorden(arbol->izquierda);
    postorden(arbol->derecha);
    cout << arbol->valor << " ";
}

void buscarParaEliminar(Nodo*& arbol, int valor) {
    if (!arbol) return;
    
    if (arbol->valor == valor) {
        eliminarNodo(arbol);
    } else if (valor < arbol->valor) {
        buscarParaEliminar(arbol->izquierda, valor);
    } else {
        buscarParaEliminar(arbol->derecha, valor);
    }
}

void eliminarNodo(Nodo*& nodo) {
    if (!nodo) return;
    
    if (!nodo->izquierda && !nodo->derecha) {
        if (nodo->padre) {
            if (nodo->padre->izquierda == nodo) {
                nodo->padre->izquierda = NULL;
            } else {
                nodo->padre->derecha = NULL;
            }
        }
        delete nodo;
        nodo = NULL;
    } else if (!nodo->izquierda) {
        Nodo* temp = nodo;
        nodo = nodo->derecha;
        nodo->padre = temp->padre;
        delete temp;
    } else if (!nodo->derecha) {
        Nodo* temp = nodo;
        nodo = nodo->izquierda;
        nodo->padre = temp->padre;
        delete temp;
    } else {
        Nodo* minNodo = minimoNodo(nodo->derecha);
        nodo->valor = minNodo->valor;
        eliminarNodo(minNodo);
    }
}

Nodo* minimoNodo(Nodo*& nodo) {
    while (nodo->izquierda) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

void menu() {
    int opcion;
    do {
        cout << "\nMENU:\n";
        cout << "1. Insertar nodo\n";
        cout << "2. Mostrar árbol\n";
        cout << "3. Buscar nodo\n";
        cout << "4. Recorrido preorden\n";
        cout << "5. Recorrido inorden\n";
        cout << "6. Recorrido postorden\n";
        cout << "7. Eliminar nodo\n";
        cout << "0. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                int valor;
                cout << "Ingrese el valor del nodo a insertar: ";
                cin >> valor;
                insertarNodo(arbol, valor);
                break;
            case 2:
                cout << "ÁRBOL BINARIO DE BÚSQUEDA:\n";
                mostrarArbol(arbol);
                break;
            case 3:
                cout << "Ingrese el valor a buscar: ";
                cin >> valor;
                if (buscarNodoArbol(arbol, valor)) {
                    cout << "El valor " << valor << " se encuentra en el árbol.\n";
                } else {
                    cout << "El valor " << valor << " no se encuentra en el árbol.\n";
                }
                break;
            case 4:
                cout << "Recorrido preorden: ";
                preorden(arbol);
                cout << endl;
                break;
            case 5:
                cout << "Recorrido inorden: ";
                inorden(arbol);
                cout << endl;
                break;
            case 6:
                cout << "Recorrido postorden: ";
                postorden(arbol);
                cout << endl;
                break;
            case 7:
                cout << "Ingrese el valor del nodo a eliminar: ";
                cin >> valor;
                buscarParaEliminar(arbol, valor);
                break;
            case 0:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

int main() {
    menu();
    return 0;
}

