// QUESTION 2
//The program will read in the students' answers and the correct answers from files and prints out the result onto the screen and also the file output
//GROUP MEMBERS :
//Eissa	A19EE4031	
//Audrey	A19EE0454
//Anas    A19EE0450	
// moaz magdi

//INCLUDE THE LIBRARIES
#include<stdio.h>
#include <stdlib.h>
#include<string.h>


struct input                        //intializing Struct
{
	char name[20];
	char id[15];
	char answer[21];
	float percentage;
	char grade;
	char incorrect[21];
	int incorrectnum;
};

typedef struct node                     //struct pointer to next struct
{

	input student;
    struct node* next;
}list;

//declaring functions 
void write_out(list* top, char correct[]);                             
float compare_answers(list* top, char correct[], char incorrect[]);     
void read_correct(char correct[]);
list* create_list(void);
char gradeing(float percentage);
void search(list* top,char studentid[], char correct[]);


int main(void)
{
	//variables declearation
	char correct[21], grade, grades[21], studentid[21];              
	int j = 0;

	//Calling functions
	list* top = create_list();                               //get entire list of students
	read_correct(correct);                                   //get correct answers
	for( list* i = top; i != NULL ; i = i->next)             //get student percentage based on correct answers
	{
		i->student.percentage = compare_answers(i, correct, i->student.incorrect);
		i->student.grade = gradeing(i->student.percentage);
	}
	write_out(top, correct);                                 
	printf("Enter the student ID: ");                        //prompt user for Input
	scanf("%s", studentid);                                  //Assign input to variable
	search(top, studentid, correct);	                     //Search for student using id



}
//function to search for Student ID
void search(list* top,char studentid[], char correct[])
{
	for( list* i = top; i != NULL ; i = i->next)
	{
		if(strcmp(i->student.id, studentid) == 0)
		{
			printf("\nEXAM RESULT\n");                                                      //displaying student Information
			printf("NAME :\t%s\n", i->student.name);
			printf("Student ID :\t%s\n", i->student.id);
			printf("Number of questions missed: %d\n", i->student.incorrectnum);
			if(i->student.incorrectnum > 0)
			{
				printf("List of the questions missed: \n");                                        
				printf("Question\tCorrect Answer\tStudent Answer\n");
				for (int j = 0; j < 20; j++)
				{
					if(i->student.incorrect[j] != 'T')
					{
						printf("%d\t\t%c\t\t%c\n", j+1, correct[j], i->student.incorrect[j]);
					}
				}
			}	
			printf("Percentage:%.0f%%   , GRED : %c\n", i->student.percentage, i->student.grade);
		}
	}
}


//read the input file and store its values in a list
list* create_list(void)                                                     
{
	FILE* studentinfo;
	studentinfo = fopen("student.dat","r");
	input terminal = {};
	list *pre = NULL, *cur = NULL, *top = NULL;
	while(fscanf(studentinfo, "%s %s", terminal.name, terminal.id) != EOF)               // loop to read the file contents until it reachs EOF
	{
		char answer[2];
		int i = 0;
		while(i < 20)
		{
			fscanf(studentinfo, "%s", answer);                                        
			terminal.answer[i++] = answer[0];            
		}
		cur = (list *) malloc(sizeof(list));
		cur->student = terminal;
		if(!top)                       
		{
			top = pre = cur;
			cur = NULL;
		}
		else
		{
			pre->next = cur;
			pre = cur;
			cur = NULL;
		}
	}
	pre->next = NULL;
	fclose(studentinfo);
	return top;
}

//read correct answer
void read_correct(char correct[])                                      
{
	FILE* correctanswer;
	correctanswer = fopen("correctanswers.txt","r");              //open Correct answers file for Reading    
	if(correctanswer == NULL)                                  
	{
		printf("error");
		exit(0);
	}
	char answer[2] ;
	int i = 0;
	while(fscanf(correctanswer, "%s", answer) != EOF)                     //continue reading till you reach EOF
	{
		correct[i++] = answer[0];
	}
	fclose(correctanswer);
}

//write to outputfile
void write_out(list* top, char correct[])                                 
{
	FILE* writeout;
	writeout = fopen("output.txt","w");                               //open output file for writing
	fprintf(writeout, "Question 2\nGROUP MEMBERS:\neissa sharaf\naudery\nmoaz magdi\nanas eslam\n\n\n");
	fprintf(writeout, "LIST OF STUDENTS AND GRADES:\n");                 
	fprintf(writeout, "name \t\t ID \t\t percentage \t\tgrade\n");          //print all of the student's info
	for(list* i = top; i != NULL; i = i->next)                                          
	{
		fprintf(writeout, "%s \t\t %s \t %6.2f  \t\t%c\n", i->student.name, i->student.id, i->student.percentage, i->student.grade );
	}
	fclose(writeout);
	
}

//compare answers 
float compare_answers(list* top, char correct[], char incorrect[])         
{
	int counter = 0;                                                   
	float percentage = 0; 
	for(int j = 0; j < 20 ;j++)                                                     
		{
 			if(top->student.answer[j] == correct[j])                      //check if each answer is correct
			{
				counter++;
				incorrect[j] = 'T';
			}
			else
			{
				incorrect[j] = 	top->student.answer[j];      //if not, store incorrect answers
			}
		}
	top->student.incorrectnum = 20 - counter;	
	percentage = ((float)counter / 20) * 100;
	return percentage;
}


char gradeing(float percentage)                            //function to determine grade
{
	char grade;
	if(percentage >= 80)
	{
		grade = 'A';
	}
	else if (percentage >= 70)
	{
		grade = 'B';
	}
	else if (percentage >= 60)
	{
		grade = 'C';
	}
	else
	{
		grade = 'f';
	}
	return grade;
}
