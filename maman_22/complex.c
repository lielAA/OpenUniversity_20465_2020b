/*Author: Liel Adir
  Student ID: 20-280253
  Date: 30/05/2020
                                    ################ File  Description ################ 
                        This complex.c file intended only to execute operations (as defined) on complex Vars.
                        Its execute operation only after user command(s) passed successfully validation process*/
#include "complex.h"

/*          ##### Method Description #####
read_comp method received complexVar, and two double number from the user command,
and set first double number as real number at complexVar location in the memory, 
and second double number as image number at complexVar location in the memory*/
void read_comp(complexP complexVar, double realNum_1, double realNum_2)
{
    complexVar->reNum = realNum_1; /*set real number from the command to relevant complexVar*/
    complexVar->imNum = realNum_2; /*set image number from the command to relevant complexVar*/
}

/*          ##### Method Description #####
print_comp method received complexVar from user command and print the content from this complexVar(real and image number)
For example: 2.42 + (-18.74)i */
void print_comp(complexP complexVar)
{
    printf("\n%.2f + (%.2f)i", complexVar->reNum, complexVar->imNum);
}

/*          ##### Method Description #####
add_comp method received two complexVars from user command and sum both complexVars at the next structure:
sum_real_num = real_num_1 + real_num_2
sum_image_num = image_num_1 + image_num_2
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP add_comp(complexP temp, complexP complexVar_1, complexP complexVar_2)
{
    temp->reNum = complexVar_1->reNum + complexVar_2->reNum; /*sum real_num_1 + real_num_2*/
    temp->imNum = complexVar_1->imNum + complexVar_2->imNum; /*sum image_num_1 + image_num_2*/
    return temp;
}

/*          ##### Method Description #####
sub_comp method received two complexVars from user command and subtraction both complexVars at the next structure:
sub_real_num = real_num_1 - real_num_2
sub_image_num = image_num_1 - image_num_2
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP sub_comp(complexP temp, complexP complexVar_1, complexP complexVar_2)
{
    temp->reNum = complexVar_1->reNum - complexVar_2->reNum; /*sub real_num_1 + real_num_2*/
    temp->imNum = complexVar_1->imNum - complexVar_2->imNum; /*sub image_num_1 + image_num_2*/

    return temp;
}

/*          ##### Method Description #####
mult_comp_comp method received two complexVars from user command and multiple both complexVars at the next structure:
mult_real_num = (real_num_1 * real_num_2) - (image_num_1 * image_num_2)
mult_image_num = (real_num_1 * image_num_2) + (image_num_1 * real_num_2)
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP mult_comp_comp(complexP temp, complexP complexVar_1, complexP complexVar_2)
{
    temp->reNum = ((/*a*/ complexVar_1->reNum * /*c*/ complexVar_2->reNum) - (/*b*/ complexVar_1->imNum * /*d*/ complexVar_2->imNum));
    temp->imNum = ((/*a*/ complexVar_1->reNum * /*d*/ complexVar_2->imNum) + (/*b*/ complexVar_1->imNum * /*c*/ complexVar_2->reNum));
    return temp;
}

/*          ##### Method Description #####
mult_comp_real method received one complexVar from user command and multiple complexVars with real number from the command at the next structure:
mult_real_num = complexVar->real_num * real_num(user input)
mult_image_num = complexVar->image_num * real_num(user input)
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP mult_comp_real(complexP temp, complexP complexVar_1, double realNum_1)
{
    temp->reNum = (realNum_1 * complexVar_1->reNum); /*mult complexVar->real_num * real_num (user input)*/
    temp->imNum = (realNum_1 * complexVar_1->imNum); /*mult complexVar->image_num * real_num (user input)*/
    return temp;
}

/*          ##### Method Description #####
mult_comp_img method received one complexVar from user command and multiple complexVars with image number from the command at the next structure:
mult_real_num = (-1) * (complexVar->img_num * image_num(user input))
mult_image_num = complexVar->real_num * image_num(user input)
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP mult_comp_img(complexP temp, complexP complexVar_1, double imgNum_1)
{
    temp->reNum = (NEGATIVE) * (imgNum_1 * complexVar_1->imNum); /*mult (-1) * (complexVar->img_num * image_num(user input))*/
    temp->imNum = (imgNum_1 * complexVar_1->reNum);              /*mult complexVar->real_num * image_num(user input)*/

    return temp;
}

/*          ##### Method Description #####
abs_comp method received one complexVar from user command and calculate the absulte value of complexVar at the next structure:
complexVar->reNum = sqrt(pow(complexVar_1->reNum, TWO))
complexVar->imNum = sqrt(pow(complexVar_1->imNum, TWO))
Save it in temp complexVar (not run over existing complexVar) and return temp complexVar to main()*/
complexP abs_comp(complexP temp, complexP complexVar_1)
{

    temp->reNum = sqrt(pow(complexVar_1->reNum, TWO));
    temp->imNum = sqrt(pow(complexVar_1->imNum, TWO));
    return temp;
}

/*          ##### Method Description #####
allocate 1 temp complexVar (sizeof 1 item) to save all methos calculation*/
complexP tempMemAllocate()
{
    complexP temp;
    temp = (complexP)malloc(1 * sizeof(item)); /*allocate 1 temp complexVar*/
    if (!temp)                                 /*if mamory allocation Failed*/
    {
        printf("Memory Allocation Failed");
        return NULL;
    }
    return temp;
}
