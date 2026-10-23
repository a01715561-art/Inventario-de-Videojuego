# Inventario de Videojuego (Estilo Resident Evil 4)

Este proyecto es un sistema de inventario inspirado en el maletín de Resident Evil 4. Sirve para guardar, ver, buscar y ordenar objetos (Armas, Municiones, Curas, Tesoros) basándose en su nombre, tamaño y peso.

Para organizar el inventario rápido, el programa usa el algoritmo Merge Sort. Además, utilicé la estructura `std::vector` porque facilita iterar sobre los datos para mostrarlos en consola y hacer búsquedas al instante.

**Descripción del avance 1**
En la primera entrega me enfoqué en lo básico:

* Crear la estructura `Objeto` con los atributos: nombre, tamaño y peso.
* Leer los datos iniciales desde un archivo `objetos.txt`.
* Implementar Merge Sort para ordenar por nombre, tamaño o peso.
* Hacer un menú de consola sencillo.

**Descripción del avance 2**
Para este segundo avance agregué la parte de búsqueda y justifiqué las estructuras:

* **Uso de `std::vector`:** Dejé el vector como la estructura principal porque es muy fácil de recorrer y maneja la memoria de forma continua.
* **Búsqueda lineal:** Agregué la opción 5 en el menú para buscar un objeto por nombre y ver sus estadísticas.
* **Menú actualizado:** Ahora permite ver el inventario, ordenar por los 3 atributos, buscar un ítem en específico y salir.

**Cambios sobre el primer avance**

1. **Opción de búsqueda:** Antes solo se podía ordenar y ver el maletín. Ahora el usuario puede buscar un objeto en específico. La búsqueda es lineal O(n) porque revisa el vector hasta encontrar la coincidencia.
2. **Análisis de estructuras:** Se explicó a fondo por qué se eligió un vector en lugar de un arreglo estático tradicional, cubriendo la rúbrica de estructuras de datos.

**Instrucciones de compilación y ejecución**

1. Abre la terminal en la carpeta del proyecto.
2. Compila con: `g++ main.cpp -o maletin.exe`
3. Ejecuta con: `.\maletin.exe`

**Entradas del programa**
El programa lee un archivo llamado `objetos.txt`. Cada línea debe tener los datos separados por un espacio: `Nombre Tamaño Peso`.
Ejemplo:
`Pocion_Curacion 1 0.5`

**Salidas del programa**

1. **Ver inventario:** Imprime una tabla con todos los objetos, su tamaño y peso.
2. **Ordenar:** Muestra un mensaje confirmando el filtro usado y vuelve a imprimir la tabla ya ordenada.
3. **Buscar:** Si encuentra el objeto, imprime sus datos. Si no, lanza el mensaje "Objeto no encontrado en el maletin".

**Desarrollo de competencias**

**SICT0301: Evalúa los componentes**

* **Complejidad de algoritmos de ordenamiento:**
Implementé Merge Sort. Su complejidad temporal es de log n) en el mejor, promedio y peor caso. Esto pasa porque el algoritmo siempre divide el arreglo a la mitad log (n) y luego mezcla las partes O(n), sin importar si los datos ya estaban ordenados o no. Su complejidad espacial es O(n) porque necesita un vector temporal para hacer la mezcla.
* **Complejidad de la estructura de datos:**
Usé un `std::vector`.
* Acceder a un dato por índice es O(1).
* Insertar un dato al final (`push_back`) es O(1) casi siempre, aunque en el peor caso (cuando se llena y pide más memoria) es O(n).
* Buscar un elemento recorriendo el vector de inicio a fin es O(n).



**SICT0302: Toma decisiones**

* **Selección del algoritmo:**
Elegí Merge Sort porque es estable y siempre tarda lo mismo log (n). La estabilidad es clave aquí: si ordeno el maletín por tamaño, los objetos que miden lo mismo van a mantener el orden que ya tenían antes (por ejemplo, alfabético). Otros algoritmos como Quick Sort no aseguran esa estabilidad, y Bubble Sort es demasiado lento O(n^2).
* **Selección de la estructura:**
Elegí `std::vector` por encima de las listas ligadas o los arreglos estáticos porque los elementos están contiguos en la memoria. Como mi programa se la pasa imprimiendo el inventario completo en consola y buscando ítems, la lectura en un vector corre muy bien y aprovecha mejor el caché.

**SICT0303: Implementa acciones científicas**

* **Funciones de consulta:**
Hice una función de búsqueda lineal iterando directamente sobre el vector. Compara el texto que mete el usuario con el nombre de cada objeto. Si lo encuentra, rompe el ciclo (`break`) para no gastar recursos de más buscando en el resto del arreglo.
* **Lectura de archivos:**
Usé la librería `<fstream>`. Antes de intentar leer, el programa revisa si el archivo existe con `is_open()`. Si todo está bien, un ciclo `while` lee línea por línea y mete los datos al vector con `push_back()`. Esto hace que el código sea seguro y evita que el programa se cierre de golpe si falta el archivo `.txt`.
