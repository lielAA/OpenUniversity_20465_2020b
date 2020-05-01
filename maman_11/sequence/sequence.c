/*Author: Liel Adir
  Student ID: 20-280253
  Date: 12/04/2020 */

/* 						####### Program Description #######
   This program include main method that received from the user string
   in addition include f_sequence method that received from the main the relevant string.
   f_sequence method send to the user a relevant message if his string is:
   1) strictly ascending 2) only ascending 3) strictly descending 4) only descending 5) mismatch */
#include <stdio.h>
#include <string.h>
#define STRING_MAX_SIZE 100 /*defnie max array string size*/
#define ZERO 0
#define ONE 1

int f_sequence(char[]);

			/* ##### Method Description ###### 
main method received from the user string of chars (by max size of 100 chars),
and send it to f_sequence method */

int  main()
{
	char str[STRING_MAX_SIZE];
	printf("\nPlease insert your string: \n");
	scanf("%s",str);
	f_sequence(str);
	return 0;
}

			/* ##### Method Description ######
f_sequence method received  from main method string of chars,
send to the user a relevant message if his string is:
1)Strictly ascending, e.g: "abcd".
2)Only ascending, e.g: "abbcd".
3)Strictly descending, e.g: "dcba".
4)Only descending, e.g: "dcbba".
5)Mismatch string, e.g: "suddenly".
Note: all decisions above are defined by ascii codes.*/

int f_sequence(char str1[])
{
	int i, asciiCode=str1[ZERO], desStatusF = ZERO,/*This flag representing if inside the string there is following descending chars: True=1 ; False=0 */
							  ascStatusF= ZERO,/*This flag representing if inside the string there is following asecending chars: True=1 ; False=0*/
							  compStatusF= ZERO ;/*This flag representing if inside the string there is following comparing chars: True=1 ; False=0*/

	for(i=1 ; i<strlen(str1) ; i++)
	{
		if(asciiCode == str1[i]) /*if following chars are compare*/
			compStatusF = ONE;
		else if(asciiCode < str1[i])/*if following chars are ascending*/
			ascStatusF = ONE;
		else /*if following chars are descending*/
			desStatusF = ONE;
		asciiCode=str1[i];
	}
	printf("\nYour string is: \n%s",str1);
	if(compStatusF == ZERO && ascStatusF == ONE && desStatusF == ZERO) /*If only the ascStatusF = 1 its mean the string is strictly ascending*/
		printf("\nYour string is strictly ascending");
	else if(desStatusF == ONE && compStatusF == ZERO && ascStatusF == ZERO)/* If only the desStatusF = 1 its mean the string is strictly descending*/
		printf("\nYour string is strictly descending");
	else if((compStatusF == ONE && ascStatusF == ONE && desStatusF == ZERO) || 
			(compStatusF == ONE && ascStatusF == ZERO && desStatusF == ZERO)) /*If (compStatusF ==1 && ascStatusF ==1) OR only (compStatusF ==1) its mean the string is only ascending*/
		printf("\nYour string is ascending");
	else if(compStatusF == ONE && ascStatusF == ZERO && desStatusF == ONE) /*If (compStatusF ==1 && desStatusF == 1) its mean the string is only descending*/
		printf("\nYour string is descending");
	else
		printf("\nYour string is mismatch");
	return 0;
}