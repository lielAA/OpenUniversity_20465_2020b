/* "######  Author: Liel Adir
   "######  Student ID: 20-280253
   "#####   Date: 19/08/2020 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#define MAX_ASM_LINE 81
#define MAX_LABEL 31
#define MEM_SIZE 2097151
#define WORD_SIZE 24
#define FOUR_DIGIT 4
#define WORD_WITHOUT_ARE 21
#define HEX_WORD_SIZE 6
#define MEM_BEGIN_ADDRESS 100
#define MAX_DATA_SIZE 8388607
#define MIN_DATA_SIZE -8388608
#define MAX_IMEDIATE_DATA_SIZE 1048575
#define MIN_IMEDIATE_DATA_SIZE -1048576
#define EXTENSSION_LEN 4
#define TWO 2
/*command names*/
typedef enum Command
{
    unRecognized_C = -1,
    mov = 0,
    cmp = 1,
    add = 2,
    sub = 3,
    lea = 4,
    clr = 5,
    not = 6,
    inc = 7,
    dec = 8,
    jmp = 9,
    bne = 10,
    jsr = 11,
    red = 12,
    prn = 13,
    rts = 14,
    stop = 15
} TofC;
/*type of funct*/
typedef enum funct
{
    funct0 = 0,
    funct1 = 1,
    funct2 = 2,
    funct3 = 3,
    funct4 = 4
}functType;
/*type of opcode*/
typedef enum opcode
{
    opcode2 =2,
    opcode5 =5,
    opcode9 =9   
}opcodeType;
/*directive type*/
typedef enum typeOfDirective
{
    unRecognized_LT = 0,
    extD = 1,
    entD = 2,
    stringD = 3,
    dataD = 4
} TofD;
/*errors names*/
typedef enum
{
    err = -1,
    label_duplicate = 1,
    label_duplicate_command = 2,
    label_duplicate_register = 3,
    missing_command = 4,
    not_belong_char_to_command = 5,
    unmatch_command_num_of_var = 6,
    missing_num_in_data = 7,
    multiple_commas_in_data = 8,
    unrecognized_comma_in_data = 9,
    unrecognized_command = 10,
    label_first_char = 11,
    label_alpha = 12,
    unmatching_num_of_param_for_instruction = 13,
    missing_params_for_instruction = 14,
    too_many_vars_for_string = 15,
    unrecognized_var_for_string = 16,
    missing_label_for_extern = 17,
    unrecognized_label_for_extern = 18,
    unrecognized_label_for_entry = 19,
    unmatching_var_for_extern = 20,
    entery_defined_as_extern = 21,
    missing_vars_after_label = 22,
    missing_apostrophes_at_end_of_string = 23,
    missing_apostrophes_at_start_of_string = 24,
    unrecognized_var_for_data = 25,
    unrecognized_Method_for_command =26,
    unmatch_method_for_commad = 27,
    too_long_label_length = 28,
    missing_comma_in_data = 29,
    missing_entry_label = 30,
    missing_string = 31,
    ilegal_number_in_data = 32,
    data_size_out_of_range = 33,
    imediate_data_size_out_of_range = 34,
    extern_defined_as_local = 35
} errType;
/*files type*/
typedef enum
{
    inputFile = 0,
    objFile = 1,
    entFile = 2,
    extFile = 3
} typeOfFile;
/*ARE types - absolute,relative,externl*/
typedef enum
{
    ABS = 4,
    REL = 2,
    EXT = 1
} typeOfARE;
/*methods types*/
typedef enum
{
    unknownM = -1,
    registerM = 3,
    directM = 1,
    imediateM = 0,
    relativeM = 2
} typeOFMethod;
/*registers names*/
typedef enum typeOfRegister
{
    unRecognized_R = 0,
    r0 = 1,
    r1 = 2,
    r2 = 3,
    r3 = 4,
    r4 = 5,
    r5 = 6,
    r6 = 7,
    r7 = 8
} TofR;
/*size of first word sections: opcode, funct etc.*/
typedef enum sizeOfBitField
{
    AREregisterSize = 3,
    methodSize = 2,
    functSize = 5,
    opcodeSize = 6
} size;
/*first word structure*/
typedef struct word *wordP;
struct word
{
    unsigned int ARE:AREregisterSize;
    unsigned int funct:functSize;
    unsigned int targetR:AREregisterSize; /*target register*/
    unsigned int targetMethod:methodSize; /*target method*/
    unsigned int sourceR:AREregisterSize; /*source register*/
    unsigned int sourceMethod:methodSize; /*source method*/
    unsigned int opcode:opcodeSize;
}wordS;

#endif
