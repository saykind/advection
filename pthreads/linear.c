#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <pthread.h>

double  linear(double x1, double y1, double x2, double y2, double x0);
double  U(double t, double x);
double 	residual(double *u, int N);
FILE   *gpinit(void);
void 	plot(FILE *gpp, double *a, int N);

#define A -1.0
#define B 1.0
#define C 1
#define K 0.2
#define MN 10	// MN*K ?= 1
#define X(i,N) (A+1.0*i*(B-A)/N) 
#define O(i,N) (i>0 ? (i): (i+N))
#define ABS(a) ((a)>0 ? (a) : (-a))
#define rank pthread_self()

int nt;
int const N = 10000;
double dx;
double *u;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *parallel(void *n_void) {
	//pthread_mutex_lock(&m);
	int n = *((int *) n_void);
	int from = n*(N/nt);
	int to = (n+1)*(N/nt);
	int i = 0;
	for (i = from; i < to; i++) {
		u[i] = linear(-dx, u[O(i,N)-1], 0, u[i], -K*dx);
	}
	//pthread_mutex_unlock(&m);
	return NULL;
}	

int main(int argc, char *argv[]) {
	int i, j;
	int const M = MN*N;
	dx = (B-A)/N;	
	if (argc > 1) {sscanf(argv[1],"%d", &nt);} else {nt = 4;}
	printf("%d\t",nt);
	
	u = (double *) malloc(N*sizeof(double));
	for (i = 0; i < N; i++) {u[i] = U(0, X(i,N));}
	//FILE *gpp = NULL;
	//gpp = gpinit();
	//plot(gpp, u, N);
	int a[nt-1];	
	for (i = 0; i < nt-1; i++) a[i] = i;
	pthread_t threads[nt-1];

	double time = omp_get_wtime();
	for (j = 0; j < M; j++) {
		for (i = 0; i < nt-1; i++)
			pthread_create(threads+i, NULL, parallel, a+i); 
		for (i = (nt-1)*(N/nt); i < N; i++) {
			//pthread_mutex_lock(&m);
			u[i] = linear(-dx, u[O(i,N)-1], 0, u[i], -K*dx);
			//pthread_mutex_unlock(&m);
		}
		for (i = 0; i < nt-1; i++)
			pthread_join(threads[i], (void **) NULL);
		//plot(gpp, u, N);
	}		
	time = omp_get_wtime() - time;
	printf("%.3lf\n", time);

	//printf("%.2lfe-3\n", 1e3*dx*residual(u, N));
	//plot(gpp, u, N);
	//pclose(gpp);
	return 0;
}

double linear(double x1, double y1, double x2, double y2, double x0) {
	double k = (y2-y1)/(x2-x1);
	double b =  y1-k*x1;
	return (k*x0+b);
}
double U(double t, double x) {
	if (t == -1) {
		if ((x>=-0.5)&&(x<=0.5)){return 1;} 
		else 	{return 0;}
	}
	if (t == 1) {return sin(M_PI*x);}
	if (t == 0) {return pow(sin(M_PI*x),4);}
	return 0.0;
}
double 	residual(double *u, int N) {
	double sum = 0.0, x = 0.0;
	int i;
	for (i = 0; i < N; i++) 
		if ((x = U(0,X(i,N)-u[i])) > 0) sum += x;
		else sum -= x;
	return sum;
}

/* GNUPlot functions */
FILE *gpinit(void) {
	FILE *gpp = popen("gnuplot --persist", "w");
	if (gpp == NULL) {return NULL;}
	fprintf(gpp, "set term x11\n");
	fprintf(gpp, "unset key\n");
	fprintf(gpp, "unset border\n");
	fprintf(gpp, "set style fill solid\n");
	fprintf(gpp, "set yrange [-0.01:1.01]\n");
	fprintf(gpp, "set xrange [-1.01:1.01]\n");
	//fprintf(gpp, "set multiplot\n");
	return gpp;
}
void plot(FILE *gpp, double *a, int N) {
	int i;
	fprintf(gpp, "plot '-' w lines\n");
	for (i = 0; i < N; i++) {
		fprintf(gpp, "%.6f %.6f\n", X(i,N), a[i]);
	}
	fprintf(gpp,"e\n");
	fflush(gpp);
}
