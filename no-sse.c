#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//gcc -O2 -Wall ergasia.c -o ergasia -DN=1000 -DM=1000

//ths deinoume enan deikth se enan double pinaka kai ekeinh topothetei thn twrinh wra

void get_walltime(double *wct) //wct: pointer
{
	struct timeval tp;
	gettimeofday(&tp,NULL);
	*wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0); //tv_sec, tv_usec etoima ulopoihmena

}

int main() 
{

	double *a,*b; //orizontai oi pinakes ws double
	double ts,te; //ts: time_start, te: time_end
	int i, j;

	// desmeush pinakwn
	a = (double *)malloc(N*M*sizeof(double));
	if (a==NULL){
		exit(1);
	}

	b = (double *)malloc(N*M*sizeof(double));
	if (b==NULL){ 
		free(a); 
		exit(1);
	}  

	//arxikopoihsh pinakwn
	for (i=0; i<N*M; i++){
		a[i]= rand()%100;
	}

	get_walltime(&ts); // get starting time (double, seconds) 
	
	float s=0.5;
	float t=5.0;
	for (i=1;i<N;i++) {
		for (j=1;j<M;j++) {
			b[i] = s*(a[i-1-M]+a[i-M]+a[i+1-M]+a[i-1]+a[i+1]+a[i-1+M]+a[i+M]+a[i+1+M])+t*a[i]; //o metasxhmatismos ginetai kata grammh
		}
	}

 	get_walltime(&te); // get ending time

	//kratame ton xrono ekkinhshs kai lhkshs gia na metrhsoume meta ta mflops kata th diarkeia tou metasxhmatismou

	//elegxos fortiou
	for (i=0; i<N*M ; i++){
		if (a[i]!=b[i]){
			printf ("Egine o metasxhmatismos!\n");
			break;
		}
	}  

	// upologismos kai emfanish twn mflops
	double mflops;
	mflops = (N*M*2.0)/((te-ts)*1e6);  //1e6: 1 ekatommurio
	printf("%f\n",mflops);

  	// apodesmeush olwn
	free(a); 
	free(b);   
	
	return 0;

}
