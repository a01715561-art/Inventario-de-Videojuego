#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "sorts.h"

struct Objeto {
    std::string nombre;
    int tamano;
    double peso;

    Objeto() : nombre( "" ), tamano( 0 ), peso( 0.0 ) {}
    Objeto( std::string n, int t, double p ) : nombre( n ), tamano( t ), peso( p ) {}

    // Complejidad de imprimir:
    // Mejor caso: O(1)
    // Caso promedio: O(1)
    // Peor caso: O(1)
    // Imprime directamente los tres atributos del objeto en consola.
    void imprimir() const {
        std::cout << std::left << std::setw( 25 ) << nombre
                  << std::setw( 12 ) << tamano
                  << std::setw( 10 ) << peso << "\n";
    }

    friend std::ostream& operator<<( std::ostream& os, const Objeto& obj ) {
        os << obj.nombre << "(" << obj.tamano << " slots, " << obj.peso << "kg)";
        return os;
    }

    bool operator==( const Objeto& otro ) const {
        return nombre == otro.nombre;
    }
};

// Complejidad de compararObjetos:
// Mejor caso: O(1)
// Caso promedio: O(1)
// Peor caso: O(1)
// Realiza comparaciones directas entre los atributos de dos objetos
// segun el criterio seleccionado (1: Nombre, 2: Tamano, 3: Peso).
bool compararObjetos( Objeto a, Objeto b, int criterio ) {
    if ( criterio == 1 ) return a.nombre <= b.nombre;
    if ( criterio == 2 ) {
        if ( a.tamano != b.tamano ) return a.tamano <= b.tamano;
        return a.nombre <= b.nombre;
    }
    if ( criterio == 3 ) {
        if ( a.peso != b.peso ) return a.peso <= b.peso;
        return a.nombre <= b.nombre;
    }
    return true;
}

// Complejidad de cargarInventario:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion lee los n registros almacenados en el archivo.
// Cada objeto se inserta al final de la DList mediante
// insertion(), cuya complejidad es O(1).
// n * O(1) = O(n)
// Por lo tanto, la complejidad de cargarInventario es O(n).
bool cargarInventario( const std::string& ruta, DList<Objeto>& inventario ) {
    std::ifstream archivo( ruta );
    if ( !archivo.is_open() ) {
        std::cerr << "Error: No se pudo abrir el archivo " << ruta << "\n";
        return false;
    }

    inventario.clear();
    Objeto obj;
    while ( archivo >> obj.nombre >> obj.tamano >> obj.peso ) {
        inventario.insertion( obj );
    }

    archivo.close();
    return true;
}

// Complejidad de guardarInventario:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion recorre todos los nodos de la DList
// y escribe cada objeto una sola vez en el archivo.
// Por lo tanto, la complejidad de guardarInventario es O(n).
void guardarInventario( const std::string& ruta, const DList<Objeto>& inventario ) {
    std::ofstream archivo( ruta );
    if ( !archivo.is_open() ) {
        std::cerr << "Error al abrir el archivo para guardar.\n";
        return;
    }
    
    DLink<Objeto>* current = inventario.getHead();
    while ( current != 0 ) {
        archivo << current->getValue().nombre << " " 
                << current->getValue().tamano << " " 
                << current->getValue().peso << "\n";
        current = current->getNext();
    }
    archivo.close();
    std::cout << "\n[!] Inventario guardado exitosamente en " << ruta << ".\n";
}

// Complejidad de mostrarInventario:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion recorre todos los nodos de la DList
// desde head hasta llegar al final.
// Cada objeto se consulta e imprime una sola vez.
// Por lo tanto, la complejidad de mostrarInventario es O(n).
void mostrarInventario( const DList<Objeto>& inventario ) {
    std::cout << "\n===================================================\n";
    std::cout << std::left << std::setw( 25 ) << "Nombre"
              << std::setw( 12 ) << "Tamano"
              << std::setw( 10 ) << "Peso (kg)" << "\n";
    std::cout << "---------------------------------------------------\n";
    
    DLink<Objeto>* current = inventario.getHead();
    while ( current != 0 ) {
        current->getValue().imprimir();
        current = current->getNext();
    }
    std::cout << "===================================================\n";
}

// Complejidad de buscarObjeto:
// Mejor caso: O(1)
// Caso promedio: O(n)
// Peor caso: O(n)
// Utiliza search() que recorre la lista desde head hasta encontrar
// el nombre buscado. Si esta al inicio es O(1), pero si esta al final
// o no existe recorre hasta n nodos. Luego avanza hasta el indice
// para imprimirlo, manteniendo una complejidad lineal O(n).
void buscarObjeto( const DList<Objeto>& inventario, const std::string& nombre ) {
    Objeto dummyBusqueda( nombre, 0, 0 );
    int index = inventario.search( dummyBusqueda );
    
    if ( index != -1 ) {
        std::cout << "\n[!] Objeto encontrado en el indice " << index << ":\n";
        std::cout << std::left << std::setw( 25 ) << "Nombre" << std::setw( 12 ) << "Tamano" << std::setw( 10 ) << "Peso (kg)" << "\n";
        
        DLink<Objeto>* current = inventario.getHead();
        for ( int i = 0; i < index; i++ ) {
            current = current->getNext();
        }
        current->getValue().imprimir();
    } else {
        std::cout << "\n[x] Objeto no encontrado en el maletin.\n";
    }
}

int main() {
    DList<Objeto> inventario;

    if ( !cargarInventario( "objetos.txt", inventario ) ) {
        return 1;
    }

    int opcion = 0;
    while ( opcion != 6 ) {
        std::cout << "\n==== Maletin ====\n";
        std::cout << "1. Ver inventario actual\n";
        std::cout << "2. Ordenar por nombre\n";
        std::cout << "3. Ordenar por tamano\n";
        std::cout << "4. Ordenar por peso\n";
        std::cout << "5. Buscar objeto por nombre\n";
        std::cout << "6. Guardar y Salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        switch ( opcion ) {
            case 1:
                mostrarInventario( inventario );
                break;
            case 2:
                inventario.mergeSort( 1, compararObjetos );
                std::cout << "\n[!] Inventario ordenado por NOMBRE.\n";
                mostrarInventario( inventario );
                break;
            case 3:
                inventario.mergeSort( 2, compararObjetos );
                std::cout << "\n[!] Inventario ordenado por TAMANO.\n";
                mostrarInventario( inventario );
                break;
            case 4:
                inventario.mergeSort( 3, compararObjetos );
                std::cout << "\n[!] Inventario ordenado por PESO.\n";
                mostrarInventario( inventario );
                break;
            case 5: {
                std::string nombreBuscar;
                std::cout << "Ingresa el nombre del objeto a buscar (Primera MAYUSCULA): ";
                std::cin >> nombreBuscar;
                buscarObjeto( inventario, nombreBuscar );
                break;
            }
            case 6:
                guardarInventario( "inventario_guardado.txt", inventario );
                std::cout << "\nSaliendo...\n";
                break;
            default:
                std::cout << "\nOpcion no valida.\n";
        }
    }

    return 0;
}