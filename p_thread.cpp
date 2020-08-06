#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <pthread.h>

using namespace std;

// g++ -Wall -pthread -o p_thread p_thread.cpp
// time ./p_thread oimage.txt mask.txt output-pthread.txt 10

long thread_count;
int m[3][3];
int **in;
int **out;
int row,col,px;


void *pth ( void *rank )
{
	long my_rank = (long) rank;
	int i,j;
	for (i=row*my_rank/thread_count ; i<row*(my_rank+1)/thread_count ; i++)
	{	for (j=0 ; j<col ; j++)
		{	px = in[i][j];
			if( px > m[i%3][j%3] )
				px = 1;
			else
				px = 0;
			out[i][j]=px;
		}
	}

	return NULL;
}



int main(int argc, char** argv) 
{
	if (argc != 5) 
	{	cout<<" You Need to Pass 4 Parameteres (Input File, Mask File, Output File & Threads Number) "<<endl;
        return 0;
    }
	
	clock_t Start = clock();
		
		long thread;
		thread_count = atoi(argv[4]);
		pthread_t *t = new pthread_t [thread_count];

		string input_file(argv[1]), mask_file(argv[2]), output_file(argv[3]);
		FILE *input = fopen (input_file.c_str(), "r");
		FILE *mask = fopen (mask_file.c_str(), "r");
		FILE *output = fopen (output_file.c_str(),"w");
		
		if (input == NULL || mask == NULL)
		{
			cout << "Input File or Mask File not found" << endl;
			return 0;
		}
		
		for (int i=0 ; i<3 ; i++)
			for (int j=0 ; j<3 ; j++)
				fscanf(mask, "%d ", &m[i][j]);
		
		fscanf(input, "%d %d", &row, &col);
		fprintf(output, "%d %d\n", row, col);
		int r=row,c=col;
		
		in=new  int* [r];
		out=new  int* [r];
		for (int i=0; i<r; i++)
		{	in[i]=new int [c];
			out[i]=new int [c];
		}
			
		for (int i=0 ; i<r ; i++)
			for (int j=0 ; j<c ; j++)
			{	fscanf(input, "%d", &in[i][j]);
				in[i][j]/= 28;
			}
			
		for(thread=0 ; thread<thread_count ; thread++)
			pthread_create(&t[thread], NULL, pth, (void*) thread);
		
		//cout<<"MAIN THREAD";
		
		for(thread=0 ; thread<thread_count ; thread++)
			pthread_join(t[thread], NULL);

		for (int i=0 ; i<r ; i++)
		{	for (int j=0 ; j<c ; j++)
			{	fprintf (output, "%d ", out[i][j]);
			}
				fprintf (output ,"\n");
		}

		
		for (int i=0; i<r ;i++)
		{	delete [] in[i];
			delete [] out[i];
		}
			delete []in;
			delete []out;
		
		fcloseall();
	
	clock_t Finish = clock();
	cout << "\n\n Elapsed Time = " << float(Finish-Start)/CLOCKS_PER_SEC << endl;
	
	cout<<endl<<endl;
	
	free(t);
	return 0;
}
