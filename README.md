# Pthreads & OpenMP - Image Dithering

-------------------------------------------------------
serial_code.cpp
-
make serial

* In the serial code I took 3 argumants (Input File, Mask File & Output File), the Input File (oimage.txt) & Mask File (mask.txt) were already given to be read, these 3 files were then opened using FILE and each file is stored to thier own variables (input,mask,output).

* I started by converting the mask file into a 2d array [3x3] for later comparison, using 2 for-loops and "fscanf" to complete this task.

* In the input file given (oimage.txt), the 1st line contains the number of rows and columns, using fscanf to read them and store each in row,col variables and print them to output file using fprintf.

* Then came main part of the code, following the instructions given in the assignment details, first I read each number and divide it by 28 to normalize it from (0-255) to (0-9), then to achieve image Dithering using the mask pattern I compared each number to its corresponding mask number position using "if( px > m[i%3][j%3])", this method allows me to loop over all the numbers in the input and compare them with the mask pattern without creating an additional 2 loops for the mask matrix as [i%3][j%3] will continue to loop across all numbers until the end. If the resulting number is larger than the mask number then the number output will be 1, otherwise it is a 0. At the end these values are stored in the output text file in order.


Time using "clock_t" function: 
(( Elapsed Time = 0.019418 ))


Time using "time ./serial_code oimage.txt mask.txt output-serial.txt":
real	0m0.015s
user	0m0.011s
sys	0m0.004s

-------------------------------------------------------
p_thread.cpp
-
make pthread

* A few modification were added to the previous serial code to make it pthread. inclding, a new argument that accept number of threads and declaration of thread and thread_count, creating 2 dynamic 2 arrays to store the input and output data,  pthread_create & pthread_join which are responsible for the main pthread operations,
the pth function were the main operation occurs, in it the work is divided as blocks per number of threads given, each thread will take aprox equal number of iterations in the main for-loop according to thread rank and thread count.

*The comparison method and storing the data is the same as in the serial code previously.*


Time using "clock_t" function: 
(( Elapsed Time = 0.019494 ))


Time using "time ./serial_code oimage.txt mask.txt output-serial.txt":
real	0m0.021s
user	0m0.008s
sys	0m0.001s

-------------------------------------------------------

open_mp.cpp
-
make openmp

* A few modification were added to the previous serial code to make it openmp. inclding, a new argument that accept number of threads and declaration of openmp (#pragma) thread_count, get rank variable "mp_get_thread_num();" , all of this work is divided as blocks per number of threads given, each thread will take aprox equal number of iterations in the  main for-loop according to thread rank and thread count.

*The comparison method and storing the data is the same as in the serial code previously.*


Time using "clock_t" function: 
(( Elapsed Time = 0.09845 ))


Time using "time ./serial_code oimage.txt mask.txt output-serial.txt":
real	0m0.064s
user	0m0.044s
sys	0m0.069s

-------------------------------------------------------

* At the end, after checking the code multiple times in a comparable situation were the serial code and the pthread code are similar in operations used, we can see that the pthread program preform more effecient and faster according to the number of theads in comparison to the serial program.

* As for ease of implementation, extendibility, Openmp is the clear winner here as it's straight forward and simpler to implement with many features ready to use in the #pragma line, as for performence, it depends on the use case and the data scale that we would to parallelize.

-------------------------------------------------------


