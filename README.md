# Inventario-de-Videojuego

Este proyecto consiste en un sistema de gestion de inventario inspirado en el maletin de Resident Evil 4
Permite almacenar, desplegar, filtrar y ordenar diferentes tipos de objetos como: (Armas, Municiones, Curas, Tesoros)
según el tamaño del objeto, peso o nombre 

El programa esta desarrollado bajo buenas prácticas en C++ 

# Descripción del proyecto 

1. Carga y Almacenamiento de Datos
   Carga dinámica de objetos en el inventario desde un archivo.txt
   Representacion mediante ina estructura de clase objeto con atributos clave
   
   - nombre (string)
   - tamaño (float)
   - peso (float)
   - categoria (string)

3. Filtros y despliegue de información
   Visualizacion organizada del despliegue del maletin
   Filtros que permiten ordenar los items por distintos criterios

4. Algoritmos de ordenamiento modular
   Implementación del algoritmo Merge Sort adaptado para ordenación de los objetos

# Como usar el programa 

1. Clonar el repo o descargar los archivos
2. Abrir la carpeta main.cpp y compilar

   Menu de uso
Al ejecutar el programa se despliega un menú interactivo
1. Ver inventario actual: Muestra la lista de ítems en el maletín
2. Ordenar por nombre: Ordena con la primera letra del item de A - Z
3. Ordenar por tamaño: Organiza de mayor a menor o de menor a mayor el espacio ocupado en el maletin
4. Ordenar por Peso: Ordena los ítems por su peso ya antes definido

Si el usuario introduce una opción que no existe el programa muestra:

Opción invalida.

# Menú del programa 
   ==== Maletin ==== 
   1. Ver inventario actual
   2. Ordenar por nombre
   3. Ordenar por tamaño
   4. Ordenar por peso

# Sub-competencias 

Se utilizo el algoritmo Merge Sort para ordenar los elementos del inventario
Peor, promedio y mejor caso 
el algoritmo aplica la estrategia de divide y venceras, la funcion se divide a la mitad y luego otra vez a la mitad 
y asi recursivamente en O (long n) niveles de profundidad, en cada nivel la funcion, merge array compara y fusiona los 
elementos recorriendo los subarreglos en tiempo lineal O (n)

Se selecciono el algoritmo porque es un algoritmo de ordenamiento estable para el sistema de gestion de inventario 
donde los objetos se pueden filtrar por varios criterios

El algoritmo se implemento mediante una pantalla de una clase desacomplada que recibe como parametro de entrada una funcion
comparadora para poder reutilizar el mismo codigo de ordenamiento con diferentes filtros.
