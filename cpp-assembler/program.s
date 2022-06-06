# Comment: The programm which get the integer and return the Fibonacci's number on that position.
MOV INPUT, R2
MOV 0, R4
MOV 1, R5

// Comment: Some demonstartion comment
LABEL loop
SUB R2,1,R2
MOV R4, R3
MOV R5, R4
ADD R3, R4, R5
LES 0, R2, loop
MOV R3, OUTPUT