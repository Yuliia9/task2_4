/**
* @file		task2_4.h
* @brief	header file for task2_4.cpp
			defines data types and prototypes for functions used in task2_4.cpp
*/

#include "stdafx.h"


const int LEN = 20;		/* maximum length of student's surname/name  */

/*defines data type for holding student's surname, name, examination marks and average mark */
struct stud
{
	char surname[LEN];
	char name[LEN];
	unsigned int* marks;
	double average;
};



/**
* @brief				This function displays general information about program to users
* @param	void
* @return	void
*/
void Interface();


/**
* @brief						Checking if data match requirements set to that data types or functions return values

* @param	[in]				unsigned char retCode - return value of other functions for checking if functions ended properly
			[in]				int val - number for checking if it's negative or zero
* @return	unsigned char		Return ERROR if data doesn't match requirements
								Return SUCCESS if inputed data match requirements
*/
unsigned char  Type_checking(unsigned char retCode, int val);



/**
* @brief					Function for input information about students
* @param	[in/out]		struct stud* students - pointer to array of structures that holds information about students
			[in]			unsigned int num - the number of students in created  database
			[in]			unsigned int marks - the number of exams passed by students
* @return	unsigned char	Return ERROR if pointer to array of structure is NULL
							Return SUCCESS if data was inputed
*/
unsigned char Input(struct stud* students, unsigned int num, unsigned int marks);



/**
* @brief					Function for checking if inputed string involves only digits
* @param	[in]			const char* pstr - pointer to, checking for numbers, string
* @return	unsigned char	Return ERROR if string contains not only numbers
							Return SUCCESS if string contains only numbers
*/
unsigned char Is_digit(const char* pstr);



/**
* @brief					Function sorts list of students by their surnames
* @param	[in/out]		struct stud* students - pointer to array of structures that holds information about students
			[in]			unsigned int n - the number of students in created  database
* @return	unsigned char	Return ERROR if pointer to array of structures students is NULL
							Return SUCCESS if list was sorted
*/
unsigned char  Sort_by_surname(struct stud* students, unsigned int n);



/**
* @brief					Function estimates student's average mark 
* @param	[in]			const unsigned int* marks - pointer to array of student's marks  
			[in]			unsigned int exam - the number of exams passed by students
* @return	double			Return ERROR if pointer to array of marks is NULL
							Otherwise: return average mark 
*/
double Calc_average(const unsigned int* marks, unsigned int exam);



/**
* @brief					Function for displaying information about students and their marks
* @param	[in]			const struct stud* students - pointer to array of structures that holds information
			[in]			unsigned int num - the number of students stored in created database
			[in]			unsigned int marks - the number of exams passed by students
* @return	unsigned char	Return ERROR if pointer to array of structures is NULL
							Return SUCCESS if data was displayed
*/
unsigned char Output(const struct stud* students, unsigned int num, unsigned int marks);


/**
* @brief					Function finds two students with best average mark and show their surnames on display
* @param	[in]			const struct stud* students - pointer to array of structures that holds information about students
			[in]			unsigned int n - the number of students in created  database
* @return	unsigned char	Return ERROR if pointer to array of structures is NULL
							Return SUCCESS if best students were shown
*/
unsigned char Get_2_best(const struct stud* students, unsigned int n);

