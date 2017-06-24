#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;

void Usage(char* prog_name);
double f(double x);
void Trap(double a, double b, int n, double * globalResult);

int main(int argc, char*argv[]){
	double globalResult = 0.0;
	double a,b;
	int n;
	int threadCount;

	if(argc != 2) Usage(argv[0]);
	threadCount = strtol(argv[1],NULL,10);
	cout << "Enter a,b y n" << endl;
	cin >> a >> b >> n;

	if (n % threadCount != 0)
	{
		Usage(argv[0]);
	}
	# pragma omp parallel num_threads(threadCount)
	Trap(a,b,n, &globalResult);

	cout << "with n = " << n << " trapezoids our stimate" << endl;
	cout << "of the integral from " << a << " to " << b << " = " << globalResult << endl;

	cout << endl;

	cout << omp_get_wtime() << endl;
}

void Usage(char* prog_name){

	fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
	fprintf(stderr, "	number of trapezoids must be evenly divisible by\n");
	fprintf(stderr, "	number of threads\n");
	exit(0);
}

double f(double x){

	double returnVal;

	returnVal = x * x;
	return returnVal;
}

void Trap(double a, double b, int n, double * globalResult){
	double h,x,myResult;
	double localA,localB;
	int i, localN;
	int myRank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();

	h = (b-a)/n;
	localN = n / thread_count;
	localA = a + myRank * localN * h;
	localB = localA + localN * h;

	myResult = (f(localA) + f(localB)) / 2.0;
	for(i = 1; i <= localN -1; i++){
		x = localA + i * h;
		myResult += f(x);
	}
	myResult = myResult*h;

# pragma omp critical
	*globalResult += myResult;
}
