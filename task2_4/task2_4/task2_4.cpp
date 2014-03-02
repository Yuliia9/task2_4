
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task2_4.h"

const unsigned char ERROR = 0;
const unsigned char SUCCESS = 1;
const unsigned char MAIN_SUCCESS = 0;


int main( )
{
	Interface();
	unsigned int num;
	unsigned char  retCode;
	unsigned int num_marks, i;

	do 
	{
		printf("Please enter integer number of how many students passed the examinations: ");
		retCode = scanf("%u", &num);
		fflush(stdin); // Flush the input buffer
	} while (Type_checking(retCode, (int) num) == ERROR);
	
	printf("List will consist of %u students", num);


	struct stud* students = (stud*)malloc(num*sizeof(stud));
	if (students == NULL)
	{
		printf("Error occurs while trying to allocate memory for list of points. \n");
		return (int)ERROR;
	}
	
	
	do
	{
		printf("Enter how many exams did student pass: ");
		retCode = scanf("%u", &num_marks);
		fflush(stdin); // Flush the input buffer
	} while (Type_checking(retCode, (int)num_marks) == ERROR);


	for (i = 0; i < num; ++i)
	{
		students[i].marks = (unsigned int*)calloc(num_marks,sizeof(unsigned int));

	}

	retCode = Input(students, num, num_marks);
	if (retCode == ERROR)
	{
		free(students);
		return (int)ERROR;
	}

	retCode = Sort_by_surname(students, num);
	if (retCode == ERROR)
	{
		free(students);
		return (int)ERROR;
	}

	retCode = Output(students, num, num_marks);
	if (retCode == ERROR)
	{
		free(students);
		return (int)ERROR;
	}

	retCode = Get_2_best(students, num); 
	if (retCode == ERROR)
	{
		free(students);
		return (int)ERROR;
	}


	free(students);
	system("pause");
	return MAIN_SUCCESS;
}

void Interface()
{
	printf("Hi! Please welcome to your personal students rang handler.\n");
	printf("You can store list of students surnames and names and their marks on exams.\n");
	printf("Program will define for you two smartest students.\n");
	printf("Program made by Yuliia Lyubchik;)\n");
}

unsigned char Type_checking(unsigned char retCode, int val)
{
	if (retCode == ERROR)
	{
		printf("Type mismatch. Please next time check the number. \n");
		return ERROR;
	}
	if (val <= 0)
	{
		printf("The value can not be negative or zero.\n");
		return ERROR;
	}
	return SUCCESS;
}
unsigned char Input(struct stud* students, unsigned int num, unsigned int marks)
{
	if (students == NULL)
	{
		printf("Error occurs trying to get access to memory.\n");
		return ERROR;
	}
	const char separator = ',';
	unsigned int i, j;
	unsigned char retCode;
	for (i = 0; i < num; ++i)
	{
		printf("Enter information about %i student: \n", i + 1);
		char temp[LEN * 2 + 1];
		do
		{
			printf("surname, name separated by comma: ");
			gets(temp);
		} while (strlen(temp) == 0);
		

		j = strchr(temp, separator) - temp;
		strcpy(students[i].name, temp + j + 1);
		temp[j] = '\0';
		strcpy(students[i].surname, temp);
		do
		{
			printf("enter %i marks separated by comma:  ", marks);
			gets(temp);
			char* token;
			unsigned int marks_count = 0;

			token = strtok(temp, ",");

			while (token != NULL && marks_count < marks)
			{
				if (Is_digit(token) == ERROR)
				{
					printf("Type mismatch. Next time please check if you entered integer numbers \n");
					fflush(stdin);
					retCode = ERROR;
					break;
				}
				students[i].marks[marks_count] = atoi(token);
				token = strtok(NULL, ",");
				marks_count++;
				retCode = SUCCESS;
			}
			if (marks_count != marks)
			{
				printf("Marks weren't inputed . \n");
				retCode = ERROR;
			}
		} while (retCode == ERROR);
		students[i].average = Calc_average(students[i].marks, marks);
	}
	return SUCCESS;
}
unsigned char Is_digit(const char* pstr)
{
	if (pstr == NULL)
	{
		return ERROR;
	}
	unsigned int i;
	for (i = 0; i < strlen(pstr); ++i)
	{
		if (pstr[i] >= 48 && pstr[i] <= 57)
		{
			continue;
		}
		else
			{
				return ERROR;
			}

	}
	return SUCCESS;
}

unsigned char Sort_by_surname(struct stud* students, unsigned int n)
{
	if (students == NULL)
	{
		printf("Error occurs trying to get access to date to sort it.\n");
		return ERROR;
	}
	unsigned int i, j;
	struct stud temp;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n;j++)
		{
			if (1 == strcmp((students+i)->surname, (students+j)->surname))
			{

				memcpy(&temp, students + j, sizeof(stud));
				memcpy(students + j, students + i, sizeof(stud));
				memcpy(students + i, &temp, sizeof(stud));
				
			}
		}
	}
	return SUCCESS;

}

double Calc_average(const unsigned int* marks, unsigned int exam)
{
	double average = 0;
	unsigned int i;
	for (i = 0; i < exam ; ++i)
	{
		average += marks[i];
	}
	average /= exam;
	return average;
}

unsigned char Output(const struct stud* students, unsigned int num, unsigned int marks)
{
	if (students == NULL)
	{
		printf("Error occurs trying to get access to data to display it.\n");
		return ERROR;
	}
	unsigned int i, j;
	printf("Information about student sorted by surname of student:\n");
	for (i = 0; i < num; ++i)
	{
		printf("%s\t", students[i].surname);
		printf("%s\t", students[i].name);

		for (j = 0; j < marks; ++j)
		{
			printf("%i,", students[i].marks[j]);
		}
		printf("\n");
	}
	return SUCCESS;
}

unsigned char Get_2_best(const struct stud* students, unsigned int n)
{
	if (students == NULL)
	{
		printf("Error occurs trying to get access to data to provide estimation.\n");
		return ERROR;
	}
	
	unsigned int i = 0, j;
	int best[2] = {i,0};
	unsigned int stud1, stud2;
	for (i = 0; i < 2; ++i)
	{
		for (j = i + 1; j < n; ++j)
		{
			if (((students + best[i])->average >(students + j)->average))
			{
				if (i > 0)
				{
					if (best[i -1] != j)
					{
						best[i] = j;
					}
					else continue;
				}
				else best[i] = j;
			}

		}
	}
	printf("Students with best average mark: \n");
	unsigned int a = n < 2 ? 1 : 2;
	for (int i = 0; i < a; ++i)
	{
		printf("%s\n", (students + best[i])->surname);
	}
	return SUCCESS;
}
