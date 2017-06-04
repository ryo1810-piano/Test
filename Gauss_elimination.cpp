//
//	test.cpp ... n次連立方程式の解法
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define EPS 1e-6

double my_rand(int low, int high)
{
	double r_num;
	int num;
	int range;
	
	range = high-low+1;
	num = rand()%range;
	num += low;
	
	r_num = (double)num;
	return r_num;
}

double** create_matrix(int N)
{
	double **a = new double* [N];
	
	for( int i=0; i<N+1; i++){
		a[i] = new double[N+1];
	}
	
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N+1;j++){
			a[i][j] = my_rand(-10,10);
		}
	}
	
	return a;
}

void print_matrix(double **a, int N)
{
	printf("\n");
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N+1;j++){
			if(j==N) printf("|");
			printf("%6.2f\t", a[i][j]);
		}
		printf("\n\n");
	}
	printf("\n------------------------------------------------------------------------------------\n");
}

void swap_array(double a[], double b[], int N)
{
	double *tmp= new double[N+1];
	for(int i = 0;i<N+1;i++){
		tmp[i] = a[i];
	}
	for(int i = 0;i<N+1;i++){
		a[i] = b[i];
	}
	for(int i = 0;i<N+1;i++){
		b[i] = tmp[i];
	}
	delete tmp;
}

void solve_equation(double **a, int N)
{
	double pivot;
	double plot;
	
	for(int i = 0;i<N;i++){
		if(abs(a[i][i])<EPS){
			for(int j = i;j<N;j++){
				if(a[j][i]!=0){
					swap_array(a[i],a[j], N);
				}
			}
		}
		pivot = a[i][i];
		//printf("pivot = %8.2f\n", pivot);
			for(int j = 0;j<N+1;j++){ //i行目の要素をピボットで割っていく(=0であるときの対処が必要)
			a[i][j] /= pivot;
		}
		for(int j = 0;j<N;j++){
			if(j!=i){
				plot = a[j][i];
				for(int k = 0;k<N+1;k++){
					a[j][k] -= plot*a[i][k];
				}
			}
		}
		print_matrix(a, N);
	}
	printf("\n\n解析解：");
	for(int i = 0;i<N;i++){
		printf("%5.2f\t", a[i][N]);
	}
	printf("\n");
}

void main(int argc, char* argv[])
{
	double **a;
	
	if(argc!=2){
		printf("行列の大きさを指定してください.\n");
		exit(1);
	}
	
	int N = atoi(argv[1]);
	create_matrix(N);
	 
	srand((unsigned)time(NULL));
	
	a = create_matrix(N);
	
	print_matrix(a, N);
	printf("\nSolution will start!!\n\n");
	
	solve_equation(a, N);
}