/*Author: Liel Adir
  Student ID: 20-280253
  Date: 12/04/2020
  
 						####### Program Description #######
   This program include main method that received from the user two strings(pattern & text)
   in addition include match method that received from the main that two string.
   match method find the position inside text string that represent the minimum 
   un-matching of pattetrn string and return it to main method*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STRING_MAX_SIZE 100
#define NEGATIVE -1
#define ZERO 0

int match(char[], char[]);/*match method decleration*/

					/* ##### Method Description ###### 
main method received from the user two strings (pattern & text) of chars that including white letters(by max size of 100 chars),
and send it to match method. 
The main method print original pattern and text string, send them to match method, 
and finaly print the best matching position including: the string himself and index location*/

int main()
{
	int i, unMatch_cnt = ZERO; /*counter that represent how many un-matchimg between pattern and text strings*/
	char pattern[STRING_MAX_SIZE];
	char text[STRING_MAX_SIZE];
	char position[STRING_MAX_SIZE]; /*contain new string with the best matching position*/
	
	printf("\nPlease insert your pattern string\n");
	scanf("%[^\n]%*c",pattern); /*Received pattern string from the user including white letters*/
	printf("\nPlease insert your text string\n");
	scanf("%[^\n]%*c",text); /*Received text string from the user including white letters*/
	printf("\nYour pattern is: %s\nYour text is: %s\n",pattern,text);
	
	unMatch_cnt = match(pattern,text);
	
	if(unMatch_cnt == NEGATIVE) /*if pattern biggers than text*/
		printf("\nYour pattern string is longest than text string\n");
	else
	{
		strncpy(position, text+unMatch_cnt, strlen(pattern)); /*copy text(from the correct position) to position string, but only up to pattern string length*/
		printf("\nThe best matching position is : ");
		for(i=0 ;  i<strlen(pattern) ; i++) /*print position string*/
			printf("%c",position[i]);
		printf(" ; that start at index %d.\n",unMatch_cnt); 
	}
	return 0;
}
					/* ##### Method Description ###### 
match method received from main method two strings (pattern & text) and return to main integer number 
that represent the index of text string which start the minimum un-matching of pattetrn string.
By inside for loop we check if pattern char compare to text char (up to patten length).
By outside for loop we start the checking text string from +i location and up to the difference between text length to pattern length (text - pattern)*/

int match(char pattern[], char text[])
{
	int i, j, best_match_idx = ZERO, /*represent the index that the best matching string start from*/ 
	final_unMatch_cnt = STRING_MAX_SIZE, /*counter that contain the min final un-matching between the strings*/ 
	tmp_unMatch_cnt = ZERO; /*counter that contain temporary min final un-matching between the strings*/
	
	if(strlen(pattern) > strlen(text)) /*if pattern length bigger than text*/
		return NEGATIVE;
	else if(strcmp(pattern,text) == ZERO) /*if pattern and text are compare (compare content)*/
		return ZERO;
	else
	{
		for(j=0 ; j <= (strlen(text)-strlen(pattern)) ; j++)
		{
			for(i = 0 ; i < strlen(pattern) ; i++)
			{
				if(pattern[i] != text[j+i]) /*while chars are different*/
					tmp_unMatch_cnt++;	
			}
			if(tmp_unMatch_cnt < final_unMatch_cnt)
			{
				final_unMatch_cnt = tmp_unMatch_cnt;/*save the min un-matching*/
				best_match_idx = j; /*save the index that the min is start from*/
			}
			tmp_unMatch_cnt=0; /*equate to zero*/
		}
		return best_match_idx;
	}
}