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
void convolute(const floatMatrix &matrix,floatMatrix &resultMatrix, const boolMatrix& convolution);
float getValue(int i,int j,const floatMatrix &matrix,const boolMatrix &convolution);

int main(int argc, char*argv[]){

    srand(time(NULL));

	int threadCount;
	threadCount = strtol(argv[1],NULL,10);

	int matrixSize = 8000;

	vector<vector<bool>> convolutionMatrix = {
		{1,1,1,1,1},
		{1,1,1,1,1},
		{1,1,1,1,1},
		{1,1,1,1,1},
		{1,1,1,1,1},
	};

	floatMatrix matrix = generateMatrix(matrixSize,1);
	//printfloatMatrix(matrix);
	floatMatrix resultMatrix = generateMatrix(matrix.size(),0);

    double start = omp_get_wtime();
#   pragma omp parallel num_threads(threadCount)
	convolute(matrix,resultMatrix,convolutionMatrix);
    double end = omp_get_wtime();

    double resultTime = end - start;

	//printfloatMatrix(resultMatrix);

	//double t = getValue(7999,7999,matrix,convolutionMatrix);
	//cout << t;

	cout << endl;

	cout << "El tiempo empleado es: "<< resultTime * 1000 << " ms" << endl;

} // fin de main

void convolute(const floatMatrix &matrix, floatMatrix &resultMatrix, const boolMatrix& convolution){
    int local_a, local_b, local_n;
    int myRank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();

	local_n = matrix.size()/thread_count;
	local_a = local_n * myRank;
	local_b = local_a + local_n;

	for(int i = local_a; i < local_b;i++)
        for(int j = 0; j < matrix.size();j++){
                resultMatrix[i][j] += getValue(i,j,matrix,convolution);
        }
}

float getValue(int i,int j,const floatMatrix &matrix,const boolMatrix &convolution){
    float result = 0.0;
    float n = convolution.size() * convolution.size();
    int radius = (convolution.size()-1)/2;

    for(int x = i - radius, xC = 0; x <= i + radius;x++,xC++){
        for(int y = j -radius, yC = 0; y <= j + radius;y++,yC++){
            if(x < 0 || y < 0 || x >= matrix.size() || y >= matrix.size()){}
            else{
                if(convolution[xC][yC]) result += matrix[x][y];
            }
        }
    }

    result /= n;
    //cout << "(" << result << ")";
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

