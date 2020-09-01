## Program Description

This program is interactive program, that received from the user different commands for different operations on complex numbers.
<br>First the user enter his command (taken from defined command), this command pass through validation process (based on definition for every command).
<br>In the end if validation process passed successfully its move to calculation process (following to user request).
<br>Any command contain: 1.string command 2.complex variable(s) 3. comma(s) 4.double number(s).
Command Description & Explanation:
<br>1. String command could be only one of the next nine commands: 
  <br>1.read_comp 
  <br>2.print_comp 
  <br>3.add_comp 
  <br>4.sub_comp 
  <br>5.mult_comp_comp 
  <br>6.mult_comp_real 
  <br>7.miult_comp_img 
  <br>8.abs_comp 
  <br>9.stop
  <br>Any command execute different operation on his variables. The program stop only when the user enter "stop" command, othewise - an       <br>additional command request will be made.
<br>2.Complex variable(s) - each of variable is type of structure that contain real double number and image double number, there is only 6 complex variables that represent by chars A-F (A,B,C,D,E,F).
<br>3.The variables in the command seperated by comma(s).
<br>4.double number represent the real and image number, and also some operation on complex variables
<br>commads examples: read_comp A,2,3         --> command description: this command set real_number of A var to 2 and image_number to 3, <br>and print A var at next structure: A = 2 + (3)i
<br>                  print_comp    C         --> command description: this command print (for example) C complex var at next structure: <br>-3.12 + 153.8  
<br>                 add_comp E,   C         --> command description: this command sum real_number of E and real_number of C ; and sum <br>image_number of E and image_number of C ; and print the result at next structure: 9.12 + (6.12)i
<br>                  mult_comp_real D,-21.33
<br>                  read_comp B,  -8.12,  32.14
