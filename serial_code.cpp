#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

// g++ -Wall -o serial_code serial_code.cpp
// time ./serial_code oimage.txt mask.txt output-serial.txt

int main(int argc, char** argv) 
{
	if (argc != 4) 
	{	cout<<" You Need to Pass 3 Parameteres (Input File, Mask File & Output File) "<<endl;
        return 0;
    }
	
	clock_t Start = clock();
	
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
		
		for (int i=0 ; i<row ; i++)
		{	for (int j=0 ; j<col ; j++)
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

		fcloseall();
	
	clock_t Finish = clock();
	cout << "\n\n Elapsed Time = " << float(Finish-Start)/CLOCKS_PER_SEC << endl;
	
	cout<<endl<<endl;
	return 0;
}
