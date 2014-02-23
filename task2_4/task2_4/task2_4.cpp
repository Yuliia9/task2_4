
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*maximum length of student's surname/name*/
const int LEN = 20;

struct stud
{
	char surname[LEN];
	char name[LEN];
	int *marks;
	double average;
};
/*checking entered data and return 0 if type doesn't match requirements*/
int Type_checking(int retCode, int val);

/*checking if string pstr involves only digits*/
int Is_digit(char* pstr);

/*sorted table of information about students by surname*/
void Sort_by_surname(struct stud* stud_table, int n);

/*evaluated the average mark*/
double Calc_average(int* marks, int exam);

/*sorted table of information about students by average mark*/
void Sort_by_mark(struct stud* stud_table, int n);

int main( )
{
	printf("Please enter integer number of how many students passed the examinations: ");
	int num_of_stud;
	int retCode;
	retCode = scanf("%i", &num_of_stud);
	if (0 == Type_checking(retCode, num_of_stud)) return 0;

	struct stud* student_list = (stud*)malloc(num_of_stud*sizeof(stud));

	printf("Enter how many exams did student pass: ");
	int num_of_marks;
	retCode = scanf("%i", &num_of_marks);
	if (0 == Type_checking(retCode, num_of_marks)) return 0;
	for (int i = 0; i < num_of_stud;i++)
	{
		student_list[i].marks = (int*)calloc(num_of_marks,sizeof(int));

	}

	const char separator = ',';
	int j;
	for (int i = 0; i < num_of_stud; i++)
	{
		printf("Enter information about %i student: \n", i + 1);
		char temp[LEN * 2 + 1];
		printf("surname, name separated by comma: ");
		scanf("%s", &temp);

		j = strchr(temp, separator) - temp;
		strcpy(student_list[i].name, temp + j + 1);
		temp[j] = '\0';
		strcpy(student_list[i].surname, temp);
		printf("enter %i marks separated by comma:  ", num_of_marks);
		scanf("%s",&temp);
		char* token; 
		int marks_count = 0;
		
		token = strtok(temp,",");

		while (token != NULL && marks_count < num_of_marks)
		{
			if (0 == Is_digit(token))
			{
				printf("Type mismatch. \n");
				return 0;
			}
			student_list[i].marks[marks_count] = atoi(token);
			token = strtok(NULL, ",");
			marks_count++;
		}
		if (marks_count != num_of_marks)
		{
			printf("Warning! Not all marks inputed, rest of marks will be zero. \n");
		}
		student_list[i].average = Calc_average(student_list[i].marks, num_of_marks);
	}
	Sort_by_surname(student_list, num_of_stud);
	printf("Information about student sorted by surname of student:\n");
	for (int i = 0; i < num_of_stud; i++)
	{
		
		printf("%s\t", student_list[i].surname);
		printf("%s\t", student_list[i].name);
		for (int j = 0; j < num_of_marks; j++)
		{
			printf("%i  ", student_list[i].marks[j]);
		}
		printf("\n");
	}
	printf("2 students with best average mark: \n");
	Sort_by_mark(student_list,num_of_stud);
	int a = num_of_stud < 2 ? 1 : 2;
	for (int i = 0; i < a; i++)
	{
		printf("Students surname %s and average mark %f \n", student_list[i].surname, student_list[i].average);
	}
	return 0;
}

int Type_checking(int retCode, int val)
{
	if (0 == retCode)
	{
		printf("Type mismatch.");
		return 0;
	}
	if (val < 0)
	{
		printf("The value can not be negative or null.");
		return 0;
	}
	return 1;
}

int Is_digit(char* pstr)
{
	char* psubstr;
	char key[] = "0123456789";
	psubstr = strpbrk(pstr, key);
	if (psubstr == NULL)
	{
		return 0;
	}
	int shift = 0;
	while (psubstr != NULL)
	{
		if (psubstr != (pstr + shift))
		{
			return 0;
		}
		psubstr = strpbrk(psubstr + 1, key);
		shift++;
	}
	return 1;
}

void Sort_by_surname(struct stud* stud_table, int n)
{
	struct stud temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n;j++)
		{
			if (1 == strcmp((stud_table+i)->surname, (stud_table+j)->surname))
			{
				temp = *(stud_table + i);
				*(stud_table + i) = *(stud_table + j);
				*(stud_table + j) = temp;
			}
		}
	}

}

double Calc_average(int* marks, int exam)
{
	double average = 0;
	for (int i = 0; i < exam;i++)
	{
		average += marks[i];
	}
	average /= exam;
	return average;
}

void Sort_by_mark(struct stud* stud_table, int n)
{
	struct stud temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if ((stud_table + i)->average <= (stud_table + j)->average)
			{
				temp = *(stud_table + i);
				*(stud_table + i) = *(stud_table + j);
				*(stud_table + j) = temp;
			}
		}
	}
}
