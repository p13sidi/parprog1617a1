#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h>


//define N 10
//Compile: gcc -O2 -msse2 ergasia_sse.c -o ergasia_sse -DN=1000 -DM=1000

//ta -msse2 exoun megaluterh apodosh apo ta -wall

//ths deinoume enan deikth se enan double pinaka kai ekeinh topothetei thn twrinh wra

void get_walltime(double *wct) //wct: pointer
{
	struct timeval tp;
	gettimeofday (&tp, NULL);
	*wct= (double)(tp.tv_sec + tp.tv_usec/10000000.0); //tv_sec & tv_usec etoima ulopoihmena
}

int main()
{
	int o;
	float *a, *b; //orizontai oi pinakes ws float
	double ts, te; //ts: time_start, te: time_end
	int i, j;
	float k=0.5;
	float kk=5.0;


	__m128 *va, *vb; //entoles -sse
	
	
	//desmeush pinakwn	

	o=posix_memalign((void**)&a, 16, M*sizeof(float)); //euthugrammish sta 16 bytes	
	if (o!=0)	
	{
		printf ("Error");
		exit (1);
	}

	o=posix_memalign((void**)&b, 16, M*sizeof(float)); //euthugrammish sta 16 bytes
	if (o!=0)	
	{
		printf ("Error");
		free (a);
		exit (1);
	}

	
	//arxikopoihsh pinaka a
	for (i=0; i<M; i++)
	{
		a[i]= rand()%100;
	}

	get_walltime(&ts); // get starting time (double, seconds)

	va=(__m128 *)a;

	for (j=1; j<M; j++)
	{
		va=(__m128 *)a;
		vb=(__m128 *)b; //sse pointers
		
		for (i=1; i<N; i++)
		{
			*vb=_mm_add_ps(_mm_mul_ps(kk,*va), _mm_mul_ps(k,_mm_add_ps(a[i*M-M+(j-1)], a[i*M-M+j], a[i*M-M+(j+1)], a[i*M+(j-1)], a[i*M+j], a[i*M+(j+1)], a[i*M+M+(j-1)], a[i*M+M+j],a[i*M+M+(j+1)]))); //o metasxhmatismos ginetai kata grammh
			va++;
			vb++;		
		}
	}
	get_walltime(&te); // get ending time

	//elegxos fortiou
	for (i=0; i<N*M; i++)
	{
		if (a[i]!=b[i])
		{
			printf ("Egine o metasxhmatismos!\n");
			break;
		}
	}

	//ypologismos kai emfanish twn mflops
	double mflops;
	mflops= (N*M*2.0)/((te-ts)*1e6); //1e6: 1 ekatommyrio
	printf("%f", mflops);

	//apodesmeysh olwn
	free(a);
	free(b);

	return 0;
}


	//ypologismos kai emfanish twn mflops
	double mflops;
	mflops= (N*M*2.0)/((te-ts)*1e6); //1e6: 1 ekatommyrio
	printf("%f", mflops);

	//apodesmeysh olwn
	free(a);
	free(b);

	return 0;
}
