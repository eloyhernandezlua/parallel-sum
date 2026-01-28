#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 100000000  
#define chunk 10000
#define show 10

void printArray(float *d);

int main(){
    cout << "Comparando ejecución secuencial vs paralela\n";
    cout << "Tamaño del arreglo: " << N << "\n\n";
    
    float *a = new float[N];
    float *b = new float[N];
    float *c = new float[N];
    
    srand(time(0));
    
    cout << "Inicializando arreglos...\n";
    for(int i = 0; i < N; i++){
        a[i] = (float)rand() / RAND_MAX * 100.0;
        b[i] = (float)rand() / RAND_MAX * 100.0;
    }

    // Secuencial
    double start_seq = omp_get_wtime();
    
    for(int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }
    
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;
    
    cout << "SECUENCIAL - Tiempo: " << time_seq << " segundos\n";
    cout << "Primeros " << show << " valores de c (secuencial):\n";
    printArray(c);
    cout << "\n";

    // Paralelo
    int pieces = chunk;
    int num_threads = omp_get_max_threads();
    cout << "PARALELO - Usando " << num_threads << " hilos\n";
    
    double start_par = omp_get_wtime();
    
    #pragma omp parallel for \
    shared(a, b, c, pieces) \
    schedule(static, pieces)
    for(int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }
    
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;
    
    cout << "PARALELO - Tiempo: " << time_par << " segundos\n";
    cout << "Primeros " << show << " valores de c (paralelo):\n";
    printArray(c);
    cout << "\n";

    cout << "========== RESULTADOS ==========\n";
    cout << "Tiempo secuencial: " << time_seq << " s\n";
    cout << "Tiempo paralelo:   " << time_par << " s\n";
    cout << "Speedup:           " << time_seq / time_par << "x\n";
    cout << "Mejora:            " << ((time_seq - time_par) / time_seq) * 100 << "%\n";
    
    delete[] a;
    delete[] b;
    delete[] c;
    
    return 0;
}

void printArray(float *d){
    for (int i=0; i < show; i++){
        cout << d[i] << " - ";
    }
    cout << "\n";
}