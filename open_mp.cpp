#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <omp.h>

using namespace std;

// g++ -Wall -fopenmp -o open_mp open_mp.cpp
// time ./open_mp oimage.txt mask.txt output-openmp.txt 20

int main(int argc, char** argv) 
{
	if (argc != 5) 
	{	cout<<" You Need to Pass 4 Parameteres (Input File, Mask File, Output File & Threads Number) "<<endl;
        return 0;
    }
	
	clock_t Start = clock();
	
		int thread_c = atoi(argv[4]);
		string input_file(argv[1]), mask_file(argv[2]), output_file(argv[3]);
		FILE *input = fopen (input_file.c_str(), "r");
		FILE *mask = fopen (mask_file.c_str(), "r");
		FILE *output = fopen (output_file.c_str(),"w");
		
		if (input == NULL || mask == NULL)
		{
			cout << "Input File or Mask File not found" << endl;
			return 0;
		}
		
		int m[3][3];
		for (int i=0 ; i<3 ; i++)
			for (int j=0 ; j<3 ; j++)
				fscanf(mask, "%d ", &m[i][j]);
		
		int row,col,px;
		fscanf(input, "%d %d", &row, &col);
		fprintf(output, "%d %d\n", row, col);
		
		#pragma omp parallel num_threads(thread_c)
		{
			long my_rank = omp_get_thread_num();
			int thread_count = thread_c;
			int i,j;
			for (i=row*my_rank/thread_count ; i<row*(my_rank+1)/thread_count ; i++)
			{	for (j=0 ; j<col ; j++)
				{	fscanf (input, "%d", &px);
					px /= 28;
					if( px > m[i%3][j%3] )
						px = 1;
					else
						px = 0;
					fprintf (output, "%d ", px);
				}
				fprintf (output ,"\n");
			}	
		}

		fcloseall();
	
	clock_t Finish = clock();
	cout << "\n\n Elapsed Time = " << float(Finish-Start)/CLOCKS_PER_SEC << endl;
	
	cout<<endl<<endl;
	return 0;
}

		
