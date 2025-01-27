#include <iostream>
#include <omp.h>
#include "time.h"
#include <vector>

#define N 25600000
#define chunk 1024
#define mostrar 10

void imprimeArreglo(const std::vector<float>& d);

int main() {
    std::cout << "Sumando Arreglos en Paralelo!\n";

    std::vector<float> a(N), b(N), c(N);
    int i;

    for (int i = 0; i < N; i++) {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    int pedazos = chunk;

#pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a:\n";
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b:\n";
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c:\n";
    imprimeArreglo(c);

    return 0;
}

void imprimeArreglo(const std::vector<float>& d) {
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}