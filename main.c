/*  This program keeps records, and perform statistical analysis for a class of students.
    The class may have up to 40 students. There are five quizzes during the term. 
    Each student is identified by a four digit student number. 
    The program will print the students scores and calculate and print the statistical for each quiz. 
    The output is in the same order as the input. All the data is on a file. 
    The program reads the file and store the data into arrays.
	Written by: Joshua Johnston
	Date: 11/12/2014
*/



#include<stdio.h>


#define MAX_QUIZZES_COLS 5
#define MAX_STUDENTS_ROWS 40

//   Function Declarations
void getData(int Student_ID[ ], int Quiz_scores[ ][MAX_QUIZZES_COLS], int* number_students);

void calculate(int Student_ID[], int Quiz_scores[][MAX_QUIZZES_COLS], int quiz_count, int number_students, 
	       int low_score[], int high_score[], double Avg_score[]);

int calculateLowScore(int Quiz_scores[][MAX_QUIZZES_COLS], int quiz_count, int number_students);

int calculateHiScore(int Quiz_scores[][MAX_QUIZZES_COLS], int quiz_count, int number_students);

double calcAverage(int Quiz_scores[][MAX_QUIZZES_COLS], int quiz_count, int number_students);

void print_results(int Student_ID[ ],int Quiz_scores[ ][MAX_QUIZZES_COLS], int number_students, 
	           int low_score[], int high_score[], double Avg_score[]); 

int main(void)
{
//  Local Declarations
    int Student_ID[MAX_STUDENTS_ROWS];
    int Quiz_scores[MAX_STUDENTS_ROWS][MAX_QUIZZES_COLS];
    int number_students = 0;
    int high_score[MAX_QUIZZES_COLS];	
    int low_score[MAX_QUIZZES_COLS];
    int quiz_count = 0;
    double Avg_score[MAX_QUIZZES_COLS];


//  Statements
    getData(Student_ID, Quiz_scores, &number_students);
    calculate(Student_ID, Quiz_scores, quiz_count, number_students, low_score, high_score, Avg_score);	
    print_results(Student_ID, Quiz_scores, number_students, low_score, high_score, Avg_score);		
	
    return 0;
} //main

/* ===================================getData====================================
   This function opens up a file, and extract data from the file. 
   The data is read and stored into arrays specified in the parameter list.
   Pre: nothing
   Post: Data read and placed in calling function.
*/
void getData(int Student_ID[], int Quiz_scores[][MAX_QUIZZES_COLS], int* number_students)
{
//  Local Declarations
    FILE* spIn;
    int close_file;
    int student_count = 0;
    

//  Statements	
    spIn = fopen("myfile.dat", "r");

    if(!(spIn = fopen("myfile.dat", "r")))
	{
	   printf("Error opening file.\n");
	   exit(101);
	} //if

    while(fscanf (spIn, "%d", &Student_ID[student_count]) != EOF)
	 {					
	    for (int quiz_count = 0; quiz_count < MAX_QUIZZES_COLS; quiz_count++)			
	          fscanf (spIn, "%d", &Quiz_scores[student_count][quiz_count]);
		
	     student_count++;
	     *number_students = student_count;
	  } //while


    close_file = fclose(spIn);
    return;
} //getData

/* ========================calculate==========================
   This function calls three sub functions to do calculations.

*/

void calculate(int Student_ID[], int Quiz_scores[][MAX_QUIZZES_COLS], int quiz_count, 
	       int number_students, int low_score[], int high_score[], double Avg_score[])
{
// Statements		
   for(int quiz_count = 0; quiz_count < MAX_QUIZZES_COLS; quiz_count++)
      {   
         high_score[quiz_count] = calculateHiScore(Quiz_scores, quiz_count, number_students);
         low_score[quiz_count] = calculateLowScore(Quiz_scores, quiz_count, number_students);
         Avg_score[quiz_count] = calcAverage(Quiz_scores, quiz_count, number_students);
       } //for      
   return;
} //calculate


/* ==============================calculateLowScore===============================
   This function finds the lowest quiz score in the 2D-array and returns it to 
   the calling function.

*/

int calculateLowScore(int Quiz_scores[][MAX_QUIZZES_COLS], int quiz_count, int number_students)
{
// Local Declarations
   int result;    

// Statements
   result = Quiz_scores[MAX_STUDENTS_ROWS][MAX_QUIZZES_COLS];
   for (int student_count = 0; student_count < number_students; student_count++)
       {
          if (Quiz_scores[student_count][quiz_count] < result)
              result = Quiz_scores[student_count][quiz_count];
       } // for

    return result;
} //calculateLowScore 

/* ===========================calculateHiScore===================================
   This function finds the highest quiz score in the 2D-array and returns it to
   the calling function.

*/
	
int calculateHiScore(int Quiz_scores[][MAX_QUIZZES_COLS], int quiz_count, int number_students)
{
// Local Declarations
   int result; 

// Statements
   result = Quiz_scores[0][quiz_count];
   for (int student_count = 1; student_count < number_students; student_count++)
       {
          if (Quiz_scores[student_count][quiz_count] > result)
	       result = Quiz_scores[student_count][quiz_count];
        } //for

   return result;
} //calculateHighScore

/* =======================rowAverage===========================
	This function calculates the averages in a 2D array.
	Pre:  2D array has been filled with values
	Post: averages calculated and returned to calling function
*/

double calcAverage(int Quiz_scores[][MAX_QUIZZES_COLS], int quiz_count, int number_students)
{
// Local Declarations   
   int sum = 0;
   double results;

// Statements
   for (int student_count = 0; student_count < number_students; student_count++)
        {
	   sum += Quiz_scores[student_count][quiz_count]; 
	            				 
         } // for
   results = ((double)sum / (double)number_students);
   return results;
} //calcAverage

/* =============print_results==============
   This function prints all the results.
*/
void print_results(int Student_ID[ ],int Quiz_scores[ ][MAX_QUIZZES_COLS], int number_students, 
	           int low_score[], int high_score[], double Avg_score[]) 
{
// Statements
   printf(" Student         Quiz 1  Quiz 2  Quiz 3  Quiz 4  Quiz 5\n");
   
   for (int row = 0; row < number_students; row++)
       {
          printf("   %5d", Student_ID[row]);
	     for (int col = 0; col < MAX_QUIZZES_COLS; col++)
		 {         
	            printf("\t%5d", Quiz_scores[row][col]);	             
		       
		  } //for inner
          printf(" \n");
       } // for outer

   printf("--------------------------------------------------------\n");
   printf("High Score");
   for (int col = 0; col < MAX_QUIZZES_COLS; col++)
	 printf("\t%5d", high_score[col]);
	
   printf("\n Low score");
   for (int col = 0; col < MAX_QUIZZES_COLS; col++)
        printf("\t%5d", low_score[col]);

   printf("\n  Average");
   for (int col = 0; col < MAX_QUIZZES_COLS; col++)
	 printf("\t %5.1lf", Avg_score[col]);
	
	
   printf("\n");
		
   return;
} //print_results
