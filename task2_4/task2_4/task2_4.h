#include "stdafx.h"
/*maximum length of student's surname/name*/
const int LEN = 20;

struct stud
{
	char surname[LEN];
	char name[LEN];
	unsigned int* marks;
	double average;
};
/*displays some general information about program*/
void Interface();

/*checking entered data and return 0 if type doesn't match requirements*/
unsigned char  Type_checking(unsigned char retCode, int val);

/*input information about students and their rang*/
unsigned char Input(struct stud* students, unsigned int num, unsigned int marks);

/*checking if string pstr involves only digits*/
unsigned char Is_digit(const char* pstr);

/*sorted table of information about students by surname*/
unsigned char  Sort_by_surname(struct stud* stud_table, unsigned int n);

/*evaluated the average mark*/
double Calc_average(const unsigned int* marks, unsigned int exam);

/*displays information about students on display*/
unsigned char Output(const struct stud* students, unsigned int num, unsigned int marks);

/*show two students with best average mark*/
unsigned char Get_2_best(const struct stud* students, unsigned int n);

