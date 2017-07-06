#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <vector>
#include <time.h>

using namespace std;

typedef vector< vector<float> > floatMatrix;
typedef vector< vector<bool> > boolMatrix;

floatMatrix generateMatrix(int size,bool flag);
void printfloatMatrix(floatMatrix matrix);
void convolute(const floatMatrix &matrix,floatMatrix &resultMatrix);
double getValue(const int&,const int&,const int&,const floatMatrix&);


int main(int argc, char*argv[]){

    srand(time(NULL));

	int threadCount;
	threadCount = strtol(argv[1],NULL,10);

	int matrixSize = 8000;

	floatMatrix matrix = generateMatrix(matrixSize,1);
	//printfloatMatrix(matrix);
	floatMatrix resultMatrix = generateMatrix(matrix.size(),0);

    double start = omp_get_wtime();


#   pragma omp parallel num_threads(threadCount)
	convolute(matrix,resultMatrix);

    double end = omp_get_wtime();

    double resultTime = end - start;

	//printfloatMatrix(resultMatrix);

	//double t = getValue(7999,7999,matrix,convolutionMatrix);
	//cout << t;

	cout << "El tiempo empleado es: "<< resultTime * 1000 << " ms" << endl;

} // fin de main

void convolute(const floatMatrix &matrix,floatMatrix &resultMatrix){
    int local_a, local_b, local_n;
    int myRank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	const int local_size = matrix.size();
	//printf("Hello from thread %d of %d\n",myRank,thread_count);

	local_n = local_size/thread_count;
	local_a = local_n * myRank;
	local_b = local_a + local_n;

	for(int i = local_a; i < local_b;++i)
        for(int j = 0; j < local_size;++j){
                resultMatrix[i][j] = getValue(i,j,local_size,matrix);
                //resultMatrix[i][j] = matrix[i][j]*matrix[i][j];
                //resultMatrix[i][j] = func(i,j,matrix);
                /*for(int y = i - radius; y <= i+radius;y++)
                    for(int x = j-radius;x <= j+radius;x++){
                            if(x >= 0 && x < local_size && y >= 0 && y < local_size){
                                resultMatrix[i][j] += matrix[y][x];

                            }
                    }
                resultMatrix[i][j] /= 25;*/

        }
}

double getValue(const int &i,const int &j,const int &size,const floatMatrix &matrix){
	const int radius = 2;
	double result = 0.0;
	int c = 0;
	for(int y = i - radius; y <= i+radius;++y)
        for(int x = j-radius;x <= j+radius;++x){
                if(x >= 0 && x < size && y >= 0 && y < size){
                    result += matrix[y][x];
                    ++c;
                }
        }
    result /= c;
    return result;
}



floatMatrix generateMatrix(int size,bool flag){
    if(flag){
        std::vector<float> v;
        for(int i = 0; i < size; i++)
            v.push_back(rand()%10 +1);
        std::vector<vector<float>> matrix;
        for(int i = 0; i < size; i++)
            matrix.push_back(v);
        return matrix;
    }
    std::vector<float> v;
	for(int i = 0; i < size; i++)
		v.push_back(0);
	std::vector<vector<float>> matrix;
	for(int i = 0; i < size; i++)
		matrix.push_back(v);
    return matrix;
}

void printfloatMatrix(floatMatrix matrix){
    for(auto x:matrix) {
		for(auto y:x) cout << y << " ";
		cout << endl;
	}
}

