;file myprog.as

.entry FNAME
.extern EXTR
mov r5,AGE
cmp AGE,#99 
sub r2,r5
add EXTR,EXTR
clr r5
jmp &FNAME
dec LNAME
inc r7
prn #1212
add EXTR,r3
lea FNAME,r1
bne STOP
.entry LNAME
STOP: stop

FNAME: .string "liel"
LNAME: .string "adir"
AGE: .data 27
.data -555,+14,344
.string "my asm program"
