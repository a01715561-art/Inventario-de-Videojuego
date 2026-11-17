# Sistema de Inventario - Maletín (Estilo Resident Evil 4)

## Descripción

Este proyecto es un sistema de inventario inspirado en el clásico maletín de Resident Evil 4, desarrollado en C++ para almacenar, organizar, buscar y consultar objetos (Armas, Municiones, Curas, Tesoros).
Cada objeto contiene:

* Nombre
* Tamaño
* Peso

En este avance, el programa carga los registros desde el archivo `objetos.txt`, los almacena como objetos de tipo `Objeto` dentro de una lista ligada dinámica (ej. `LinkedList<Objeto>`) y permite mostrarlos, ordenarlos (por nombre, tamaño o peso), realizar búsquedas específicas por nombre, y guardar el estado actual.

Como corrección del primer avance, se reemplazó la estructura estática/contigua (`std::vector`) por una estructura de datos dinámica propia basada en nodos enlazados, cumpliendo con los estándares de manejo de memoria requeridos.

## Cómo usar el programa

Compilar desde la terminal:
`g++ main.cpp -o maletin`

Ejecutar:
`./maletin`

Al iniciar, el programa carga automáticamente la información almacenada en `objetos.txt` y muestra el siguiente menú:

```text
===== MALETÍN RE4 =====
1. Ver inventario
2. Ordenar por Nombre
3. Ordenar por Tamaño
4. Ordenar por Peso
5. Buscar objeto
6. Guardar inventario y Salir
Selecciona una opcion:

```

Las opciones permiten visualizar los ítems, organizarlos bajo tres criterios distintos utilizando el algoritmo Merge Sort, buscar un elemento específico en tiempo real, y exportar los datos al salir.

## Estructura de datos

Para almacenar los objetos del maletín se utiliza una lista ligada (Linked List):
`LinkedList<Objeto> inventario;`

Cada nodo de la lista contiene un objeto y un apuntador al siguiente elemento:
`T value;`
`Node<T>* next;`

La lista también mantiene un control de sus extremos y tamaño:
`Node<T>* head;`
`Node<T>* tail;`
`int size;`

Se seleccionó una lista ligada dinámica porque el inventario necesita instanciar objetos en memoria bajo demanda sin requerir bloques contiguos pre-asignados, simulando la flexibilidad de meter y sacar objetos del maletín.

## Complejidad de la LinkedList

### insertion()

La inserción se realiza directamente al final utilizando el apuntador `tail`.

* Mejor caso: O(1)
* Caso promedio: O(1)
* Peor caso: O(1)
No es necesario recorrer la lista completa para insertar un nuevo nodo al final del inventario.

### search()

La búsqueda comienza desde `head` y avanza nodo por nodo comparando el string del nombre.

* Mejor caso: O(1)
* Caso promedio: O(n)
* Peor caso: O(n)
El mejor caso ocurre cuando el objeto es el primero en el maletín. El peor caso ocurre cuando está al final o no existe.

### clear()

La función elimina todos los nodos de la lista liberando la memoria dinámica.

* Mejor caso: O(n)
* Caso promedio: O(n)
* Peor caso: O(n)

### printInventory() (Mostrar)

Recorre todos los nodos desde el inicio hasta el fin para imprimir la tabla.

* O(n)

### getSize(), getHead()

Estas funciones regresan directamente un valor o apuntador almacenado.

* O(1)

## Carga de información

Los registros iniciales se cargan desde:
`objetos.txt`

Cada línea contiene un objeto y sus datos están separados por espacios.
Ejemplo:
`Pocion_Curacion 1 0.5`

La función de carga crea un objeto `Objeto` por cada línea y lo inserta en la lista mediante:
`inventario.insertion(nuevoObjeto);`

Como se recorren los *n* registros del archivo y cada inserción cuesta O(1):

* Mejor caso: O(n)
* Caso promedio: O(n)
* Peor caso: O(n)

## Algoritmo de ordenamiento

Para organizar el maletín se utiliza **Merge Sort** adaptado para funcionar sobre nodos enlazados.
La misma implementación recursiva se utiliza para tres criterios distintos:
1 -> Nombre (Alfabético)
2 -> Tamaño (Entero)
3 -> Peso (Flotante)
Esto centraliza la lógica y evita tener múltiples funciones de ordenamiento duplicadas.

### Complejidad de Merge Sort

Merge Sort divide recursivamente la lista en dos mitades y posteriormente vuelve a unirlas ordenadamente.
La relación de recurrencia es:
`T(n) = 2T(n/2) + O(n)`

Por lo tanto:

* Mejor caso: O(n log n)
* Caso promedio: O(n log n)
* Peor caso: O(n log n)

La función de división (encontrar el punto medio de la lista ligada mediante punteros rápido/lento) toma:

* O(n)
La función que combina (hace el *merge*) de las mitades ordenadas toma:
* O(n)
La función recursiva completa mantiene siempre una complejidad asintótica de:
* O(n log n)

### Justificación del algoritmo

Se eligió Merge Sort en lugar de Quick Sort o Bubble Sort principalmente por dos razones:

1. **Rendimiento constante:** Mantiene un tiempo de ejecución garantizado de O(n log n) independientemente de si el maletín ya estaba parcialmente ordenado o completamente desordenado.
2. **Estabilidad:** Merge Sort es un algoritmo estable. En el contexto de un inventario, esto es vital. Si los objetos ya están ordenados alfabéticamente (por nombre) y el usuario decide ordenarlos por "Tamaño", los objetos que tengan exactamente el mismo tamaño conservarán su orden alfabético original. Algoritmos inestables romperían esta coherencia visual.

## Mostrar Inventario

La función que imprime el maletín recorre todos los nodos de la estructura desde `head` hasta `nullptr`.

* Mejor caso: O(n)
* Caso promedio: O(n)
* Peor caso: O(n)

## Búsqueda por Nombre

El programa permite buscar un objeto específico ingresando su nombre. Al encontrar coincidencias exactas, se detiene para ahorrar recursos.
Sin embargo, teóricamente la evaluación del recorrido es secuencial:

* Mejor caso: O(1) (Si está al inicio)
* Caso promedio: O(n)
* Peor caso: O(n) (Si está al final o no existe)

## Escritura de archivos

La función de guardado recorre todos los nodos de la lista ligada y escribe las propiedades de cada objeto en `inventario_guardado.txt` (o sobreescribe el original).

* Mejor caso: O(n)
* Caso promedio: O(n)
* Peor caso: O(n)
El archivo se actualiza para asegurar la persistencia de los datos procesados durante la sesión.

## Complejidad final del programa

Las principales operaciones del maletín tienen las siguientes complejidades:

* Cargar objetos: O(n)
* Mostrar inventario: O(n)
* Buscar objeto: O(n)
* Guardar inventario: O(n)
* Ordenar con Merge Sort: O(n log n)

Para un flujo típico donde el usuario carga el archivo, ordena el maletín, y visualiza la tabla resultante:
`O(n) + O(n log n) + O(n)`

El término dominante matemático es:
`O(n log n)`

Por lo tanto, la complejidad final de ese flujo operativo es:
`O(n log n)`

---

## SICT0301 - Evalúa los componentes

Se realizó el análisis de complejidad exhaustivo de la estructura dinámica de datos (Linked List) y de sus principales operaciones.
También se analizaron las funciones:

* Lectura y carga desde archivo (.txt)
* Impresión a consola (Mostrar inventario)
* Búsqueda iterativa de strings
* Escritura hacia archivo local
* Algoritmo Merge Sort (mejor, promedio y peor caso)
Se concluyó correctamente que la operación asintótica con mayor crecimiento (el cuello de botella) en el sistema es el ordenamiento de los objetos, estableciéndose en:
`O(n log n)`

## SICT0302 - Toma decisiones

Se seleccionó una Lista Ligada Dinámica en lugar de un `std::vector` porque el objetivo arquitectónico es gestionar la memoria en tiempo de ejecución sin depender de bloques contiguos.
Una primera ventaja de esta estructura es que permite crecer el maletín teóricamente sin la necesidad de redimensionar arreglos costosos (como ocurre cuando un vector estalla su capacidad máxima).
Además, mantener apuntadores a la cabeza (`head`) y la cola (`tail`) permite registrar nuevos objetos encontrados en el juego directamente al final del inventario con una complejidad temporal de:
`O(1)`

La razón principal para adaptar esta estructura es que las mecánicas de un inventario suelen ser de acceso secuencial. Mostrar todos los objetos, buscar un ítem por nombre, o guardar la partida, son todas operaciones de recorrido directo, las cuales calzan a la perfección con la naturaleza O(n) de las listas enlazadas. Al estar trabajando en memoria principal (RAM), el impacto por *overhead* de no tener acceso contiguo en caché es imperceptible para este caso de uso.

También se justificó fuertemente la selección de **Merge Sort** para la estructura, logrando en todos los escenarios posibles:
`O(n log n)`
Esta elección no solo provee excelente escalabilidad, sino que su cualidad de algoritmo **estable** garantiza que los múltiples criterios de filtrado (nombre, luego tamaño, luego peso) funcionen armónicamente en cascada sin mezclar caóticamente a los ítems que empatan en valor.

## SICT0303 - Implementa acciones científicas

El sistema carga los datos puros desde un documento externo físico:
`objetos.txt`
directamente hacia el ecosistema de la estructura de datos dinámica mediante `ifstream`, validando la preexistencia del archivo con `is_open()` para evitar colapsos.
El programa provee robustos mecanismos para consultar los datos, tales como:

* Despliegue tabulado de todos los nodos.
* Búsqueda por coincidencia de cadenas (strings).
Finalmente, cuando el usuario termina de gestionar su maletín, el software extrae los datos de la lista dinámica y utiliza `ofstream` para serializarlos y escribirlos de nuevo en un archivo de texto. Esta acción cumple íntegramente con el ciclo científico de obtención de datos, procesamiento de estructuras, y exportación/persistencia de resultados.

---

## Estado actual del proyecto

El sistema del Maletín RE4 actualmente permite:

* Cargar un inventario inicial desde `objetos.txt` previniendo errores de lectura.
* Almacenar los objetos de forma no contigua usando una Lista Ligada propia.
* Mostrar todo el contenido estructuradamente.
* Ordenar los ítems por **Nombre** usando Merge Sort.
* Ordenar los ítems por **Tamaño** usando Merge Sort.
* Ordenar los ítems por **Peso** usando Merge Sort.
* Efectuar búsquedas lineales por nombre de objeto.
* Guardar de manera persistente el estado actual (ordenamiento) del inventario en un documento externo de salida.
* Evaluar correctamente y de forma desglosada la complejidad espacial y temporal (Mejor, Promedio y Peor Caso) de todas las facetas del software.
