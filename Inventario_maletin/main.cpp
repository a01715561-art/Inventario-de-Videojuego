#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "sorts.h"

struct Objeto {
    std::string nombre;
    int tamano;    // Slots ocupados
    double peso;   // Peso en kg

    // Complejidad Temporal: O(1)
    void imprimir() const {
        std::cout << std::left << std::setw(25) << nombre
                  << std::setw(12) << tamano
                  << std::setw(10) << peso << "\n";
    }
};

// Criterios de comparación (Complejidad Temporal: O(1) para cada comparación)
bool compNombre(const Objeto& a, const Objeto& b) {
    return a.nombre < b.nombre;
}

bool compTamano(const Objeto& a, const Objeto& b) {
    if (a.tamano != b.tamano) return a.tamano < b.tamano;
    if (a.peso != b.peso) return a.peso < b.peso;
    return a.nombre < b.nombre;
}

bool compPeso(const Objeto& a, const Objeto& b) {
    if (a.peso != b.peso) return a.peso < b.peso;
    if (a.tamano != b.tamano) return a.tamano < b.tamano;
    return a.nombre < b.nombre;
}

// Cargar inventario desde archivo .txt
// Complejidad Temporal: O(n), donde n es el número de líneas/objetos en el archivo
// Complejidad Espacial: O(n) para almacenar los objetos en el vector
bool cargarInventario(const std::string& ruta, std::vector<Objeto>& inventario) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << ruta << "\n";
        return false;
    }

    inventario.clear();
    Objeto obj;
    while (archivo >> obj.nombre >> obj.tamano >> obj.peso) { // O(n)
        inventario.push_back(obj);
    }

    archivo.close();
    return true;
}

// Desplegar inventario
// Complejidad Temporal: O(n) -> Recorre linealmente los n elementos del vector
void mostrarInventario(const std::vector<Objeto>& inventario) {
    std::cout << "\n===================================================\n";
    std::cout << std::left << std::setw(25) << "Nombre"
              << std::setw(12) << "Tamano"
              << std::setw(10) << "Peso (kg)" << "\n";
    std::cout << "---------------------------------------------------\n";
    for (const auto& item : inventario) { // O(n)
        item.imprimir();
    }
    std::cout << "===================================================\n";
}

int main() {
    std::vector<Objeto> inventario;
    Sorts<Objeto> ordenador;

    // Cargar datos: O(n)
    if (!cargarInventario("objetos.txt", inventario)) {
        return 1;
    }

    int opcion = 0;
    while (opcion != 5) {
        std::cout << "\n==== Maletin ====\n";
        std::cout << "1. Ver inventario actual\n";
        std::cout << "2. Ordenar por nombre\n";
        std::cout << "3. Ordenar por tamano\n";
        std::cout << "4. Ordenar por peso\n";
        std::cout << "5. Salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarInventario(inventario); // O(n)
                break;
            case 2:
                // MergeSort: O(n log n)
                ordenador.mergeSort(inventario, compNombre);
                std::cout << "\n[!] Inventario ordenado por NOMBRE.\n";
                mostrarInventario(inventario);
                break;
            case 3:
                // MergeSort: O(n log n)
                ordenador.mergeSort(inventario, compTamano);
                std::cout << "\n[!] Inventario ordenado por TAMANO.\n";
                mostrarInventario(inventario);
                break;
            case 4:
                // MergeSort: O(n log n)
                ordenador.mergeSort(inventario, compPeso);
                std::cout << "\n[!] Inventario ordenado por PESO.\n";
                mostrarInventario(inventario);
                break;
            case 5:
                std::cout << "\nSaliendo...\n";
                break;
            default:
                std::cout << "\nOpcion no valida.\n";
        }
    }

    return 0;
}