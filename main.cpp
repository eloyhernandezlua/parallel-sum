#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 10000
#define chunk 100
#define show 10

void printArray(float *d);

int main(){
    cout << "Sumando arreglos en paralelo\n";
    float a[N], b[N], c[N];
    
    srand(time(0));
    
    for(int i = 0; i < N; i++){
        a[i] = (float)rand() / RAND_MAX * 10000.0; 
        b[i] = (float)rand() / RAND_MAX * 10000.0;
    }

    int pieces = chunk;

    #pragma omp parallel for \
    shared(a,b,c, pieces)\
    schedule(static, pieces)

    for(int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }

    cout << "Imprimiendo los primeros " << show << " valores de a:\n";
    printArray(a);
    cout << "Imprimiendo los primeros " << show << " valores de b:\n";
    printArray(b);
    cout << "Imprimiendo los primeros " << show << " valores de c:\n";
    printArray(c);
}

void printArray(float *d){
    for (int i=0; i < show; i++){
        cout << d[i] << " - ";
    }
    cout << "\n";
}