## Program Description

<br>This program recieved numbers as digits in one line, every number seperate by one or more white space(s) and print the numbers in words (every word print in new line).
<br>The user can operate the program by 3 different modes from the command line:
<br>1. Input data (digits) received from stdin(keyboard) & output data send to stdout(screen).
<br>2. Input data (digits) received from destined input file & output data send to stdout(screen).
<br>3. Input data (digits) received from destined input file & output data send to destined output file(if output data not exist - the system create it).
<br>Note1: If destined input file not exist error message print to stderr and program stop 
<br>Note2: if user insert more than 2 files - error message print to stderr and program stop 

<br>Different exapmles for program executing:
<br>./numbers                                   input data = stdin ; output data = stdout 
<br>./numbers file_I                            input data = file_I ; output data = stdout 
<br>./numbers file_I file_O                     input data = file_I ; output data = file_O
<br>./numbers file_I file_O fileError           Error message
