#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <vector>
#include <time.h>

using namespace std;

typedef vector< vector<float> > floatMatrix;





int main(int argc, char*argv[]){

    srand(time(nullptr));

	int threadCount;
	threadCount = strtol(argv[1],NULL,10);

	int matrixSize = 8;
	int matrix[matrixSize][matrixSize];

	for(int i = 0; i<matrixSize;++i)
        for(int j = 0; j <matrixSize;++j)
            matrix[i][j] = 1;

    double start = omp_get_wtime();

#   pragma omp parallel num_threads(threadCount)
cout << "Hola";

    double fin = omp_get_wtime();

    double resultTime = fin - start;

	//printfloatMatrix(resultMatrix);

	//double t = getValue(7999,7999,matrix,convolutionMatrix);
	//cout << t;

	cout << "El tiempo empleado es: "<< resultTime * 1000 << " ms" << endl;

} // fin de main


