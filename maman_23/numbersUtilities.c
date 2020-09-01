#include "numbers.h"
/*          ##### Method Description #####
 setFiles received from main the type of input (Zero = no files ; ONE = only input files insert ; TWO = input&output files insert)
 the method open the relevant files and send it to inputdigits(), in the end close files*/
void setfiles(int numFile, ...)
{
    va_list pArg;             /*pointer to function argumnets*/
    FILE *inputFD, *outputFD; /*pointers to input & output files*/

    va_start(pArg, numFile); /*set argumnet function pointer to the next argument after "numFile"*/

    switch (numFile)
    {
    case ZERO:                           /*input file from stdin & output to stdout*/
        inputFD = va_arg(pArg, FILE *);  /*set pointer to input file*/
        outputFD = va_arg(pArg, FILE *); /*set pointer to output file*/
        inputdigits(ZERO, inputFD, outputFD);
        va_end(pArg); /*free function pointer argument*/
        break;
    case ONE:                                              /*input from inputFile & output to stdout*/
        if (!(inputFD = fopen(va_arg(pArg, char *), "r"))) /*open input file and verify opening passed successfully*/
        {
            fprintf(stderr, "cann't open your input file\n");
            exit(0);
        }
        outputFD = va_arg(pArg, FILE *); /*set pointer to output file*/
        inputdigits(ONE, inputFD, outputFD);
        va_end(pArg);    /*free function pointer argument*/
        fclose(inputFD); /*close input file*/
        break;
    case TWO:                                              /*input from inputF & output from outputF*/
        if (!(inputFD = fopen(va_arg(pArg, char *), "r"))) /*open input file and verify opening passed successfully*/
        {
            fprintf(stderr, "cann't open your input file\n");
            exit(0);
        }
        if (!(outputFD = fopen(va_arg(pArg, char *), "w"))) /*open output file and verify opening passed successfully*/
        {
            fprintf(stderr, "cann't open your output file\n");
            exit(0);
        }
        inputdigits(TWO, inputFD, outputFD);
        va_end(pArg);     /*free function pointer argument*/
        fclose(inputFD);  /*close input file*/
        fclose(outputFD); /*close output file*/
        break;
    default:
        break;
    }
}

/*          ##### Method Description #####
 inputdigits received from setfiles the type of input (Zero = no files ; ONE = only input files insert ; TWO = input&output files insert)
 the method catch the numbers from input file - convert it from char to integer and send only the number to convertDigitsToWords()*/
void inputdigits(int numFile, ...)
{
    FILE *inputFD, *outputFD; /*pointers to input & output files*/
    va_list pArg;             /*pointer to function argumnets*/
    int i, num;
    char digit;
    char digitArr[MAX_SIZE_DIGITARR];

    va_start(pArg, numFile);         /*set argumnet function pointer to the next argument after "numFile"*/
    inputFD = va_arg(pArg, FILE *);  /*set pointer to input file*/
    outputFD = va_arg(pArg, FILE *); /*set pointer to output file*/

    if (numFile == ZERO) /*if input is from srdin and output to stdout*/
        puts("\nPlease enter natural numbers between 0-99:\n");
    while (!feof(inputFD) && digit != '\n')
    {
        digit = fgetc(inputFD);
        if (digit >= '0' && digit <= '9' && !(digit == ' ' || digit == '\t')) /*if char is digit and not white space*/
        {
            digitArr[i] = digit;
            i++;
        }
        else if ((digit == ' ' || digit == '\t' || digit == '\n') && strlen(digitArr) > ZERO) /*if char is white space or new line and at least one digit is found*/
        {
            sscanf(digitArr, "%d", &num); /*convert char to int - save in num*/
            convertDigitsToWords(num, outputFD);
            va_end(pArg); /*free function pointer argument*/
            i = 0;
            memset(digitArr, ZERO, MAX_SIZE_DIGITARR); /*initialize digitarr - for new number*/
            if (digit == '\n')
                break;
        }
    }
    fputs("\n", outputFD);
}

/*          ##### Method Description #####
 convertDigitsToWords received from inputdigits the number to convert as integer - and print it to the user as words (10 ==> ten)
 the prinitg execute in output file the user insert as argimnet*/
void convertDigitsToWords(int num, ...)
{
    FILE *outputFD; /*pointers to input & output files*/
    va_list pArg;   /*pointer to function argumnets*/

    va_start(pArg, num);             /*set argumnet function pointer to the next argument after "num"*/
    outputFD = va_arg(pArg, FILE *); /*set pointer to output file*/

    fputs("\n", outputFD);
    if (num >= TEN && num <= NINETEEN) /*if number between 10 to 19*/
    {
        switch (num)
        {
        case TEN:
            fputs("ten", outputFD);
            break;
        case ELEVEN:
            fputs("eleven", outputFD);
            break;
        case TWELVE:
            fputs("tewelve", outputFD);
            break;
        case THIRTEEN:
            fputs("thirteen", outputFD);
            break;
        case FOURTEEN:
            fputs("fourteen", outputFD);
            break;
        case FIFTEEN:
            fputs("fifteen", outputFD);
            break;
        case SIXTEEN:
            fputs("sixteen", outputFD);
            break;
        case SEVENTEEN:
            fputs("seventeen", outputFD);
            break;
        case EIGHTEEN:
            fputs("eighteen", outputFD);
            break;
        case NINETEEN:
            fputs("nineteen", outputFD);
            break;
        }
    }
    else
    {
        if (num > NINETEEN) /*if number between 20 to 99*/
        {
            switch (num / TEN)
            {
            case TWO:
                fputs("twenty ", outputFD);
                break;
            case THREE:
                fputs("thirty ", outputFD);
                break;
            case FOUR:
                fputs("fourty ", outputFD);
                break;
            case FIVE:
                fputs("fifty ", outputFD);
                break;
            case SIX:
                fputs("sixty ", outputFD);
                break;
            case SEVEN:
                fputs("seventy ", outputFD);
                break;
            case EIGHT:
                fputs("eighty ", outputFD);
                break;
            case NINE:
                fputs("ninety ", outputFD);
                break;
            }
            printDigit(num % TEN, outputFD); /*also printing digit number*/
        }
        else
        {
            if (num == ZERO)
                fputs("zero", outputFD);
            else
                printDigit(num, outputFD); /*if number between 0 to 9*/
        }
    }
    va_end(pArg); /*free function pointer argument*/
}

/*          ##### Method Description #####
 printDigit received from convertDigitsToWords only the digit number to convert as integer - and print it to the user as words (10 ==> ten)
 the prinitg execute in output file the user insert as argimnet*/
void printDigit(int num, FILE *outputFD)
{
    switch (num)
    {
    case ONE:
        fputs("one", outputFD);
        break;
    case TWO:
        fputs("two", outputFD);
        break;
    case THREE:
        fputs("three", outputFD);
        break;
    case FOUR:
        fputs("four", outputFD);
        break;
    case FIVE:
        fputs("five", outputFD);
        break;
    case SIX:
        fputs("six", outputFD);
        break;
    case SEVEN:
        fputs("seven", outputFD);
        break;
    case EIGHT:
        fputs("eight", outputFD);
        break;
    case NINE:
        fputs("nine", outputFD);
        break;
    default:
        break;
    }
}