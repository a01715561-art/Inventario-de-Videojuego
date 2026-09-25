#ifndef SORTS_H_
#define SORTS_H_

#include <vector>

template <class T>
class Sorts {
private:
    // Complejidad Temporal: O(n) -> Recorre y combina los subarreglos intercalando sus elementos
    // Complejidad Espacial: O(n) -> Utiliza el arreglo auxiliar B para realizar la mezcla
    void mergeArray(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high, bool (*comp)(const T&, const T&));

    // Complejidad Temporal: O(log n) niveles de división recursiva (Divide y Vencerás)
    void mergeSplit(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high, bool (*comp)(const T&, const T&));

public:
    // Complejidad Temporal Total: O(n log n) en el mejor, promedio y peor de los casos
    // Complejidad Espacial Total: O(n) por la memoria auxiliar del vector temporal
    void mergeSort(std::vector<T>& v, bool (*comp)(const T&, const T&));
};

template <class T>
void Sorts<T>::mergeArray(std::vector<T>& A, std::vector<T>& B, int low, int mid, int high, bool (*comp)(const T&, const T&)) {
    int i = low;
    int j = mid + 1;
    int k = low;

    // O(n) en cada nivel de mezcla
    while (i <= mid && j <= high) {
        if (comp(A[i], A[j])) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        B[k] = A[i];
        i++;
        k++;
    }

    while (j <= high) {
        B[k] = A[j];
        j++;
        k++;
    }

    // Copiar elementos mezclados de regreso al vector original: O(n)
    for (int idx = low; idx <= high; idx++) {
        A[idx] = B[idx];
    }
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T>& A, std::vector<T>& B, int low, int high, bool (*comp)(const T&, const T&)) {
    if (high - low < 1) {
        return; // Caso base: O(1)
    }
    int mid = low + (high - low) / 2;
    
    // División en dos mitades: O(log n) llamadas
    mergeSplit(A, B, low, mid, comp);
    mergeSplit(A, B, mid + 1, high, comp);
    
    // Mezcla de las partes: O(n)
    mergeArray(A, B, low, mid, high, comp);
}

template <class T>
void Sorts<T>::mergeSort(std::vector<T>& v, bool (*comp)(const T&, const T&)) {
    if (v.empty()) return;
    
    // Asignación del vector auxiliar en memoria: O(n)
    std::vector<T> tmp(v.size());
    
    // Inicia el proceso de división y mezcla: O(n log n)
    mergeSplit(v, tmp, 0, v.size() - 1, comp);
}

#endif // SORTS_H_