# Assembler for 32 bit CPU.

Assembler for 32 bit CPU Virtual Machine (GitHub project: https://github.com/GarikHarutyunyan/cpp-virtual-machine-32bit/)

Assembler read 'program.s' file and generates binary instructions for 32 bit CPU, after execution the result saves on 'program.bin' file, which can be used as a source for 
Virtual Machine.

## Assembly language:
Keywords in assembly language are case-insensitive. The assembler doesn't care whether you write MOV , mov, or mOv ; so, in theory, you can write however you like.
</br>

### Comments
Comments can be added by starting line with <code>//</code> or <code>#</code> symbols.
<pre>// Comment example 1</pre>
<pre># Comment example 2</pre>
</br>

### Labels
Label is a name given to to the address of an instruction. A label can be any string that starts with a non-numeric value at the start of a line. 
Make sure there are no spaces that proceed a label.
Labels can be used only after definition.
<pre>LABEL EXAMPLE1</pre>
<pre>label example2</pre>
</br></br></br>

### Registers
Registers' names is also case-insensitive, besides that they can be used in three different ways.
There are 15 registers(R0-R14), R0 and R1 have alias names input and output which can also be used in code.
</br>
<pre>R2,R3,R4</pre>
<pre>r2,r3,r4</pre>
<pre>REG2,R3,REGISTER4</pre>
<pre>R2,reg3,register4</pre>
<pre>INPUT,R3,R4</pre>
<pre>INPUT,INPUT,OUTPUT</pre>

</br></br></br>

### Instructions

* INSTRUCTION ARGUMENT1,[ARGUMENT2],ARGUMENT3
</br>Where: 
</br>ARGUMENT1 and ARGUMENT2 are registers or immediate values. 
</br>ARGUMENT2 is optional for some insturctions. 
</br>ARGUMENT3 is label's name when instruction is conditional and it is register in all other cases.
</br>

* The <code>MOV</code> instruction moves the value from ARGUMENT1 to ARGUMENT3.
 <pre>MOV R2,R4</pre>
* The <code>ADD</code> instruction adds the values in ARGUMENT1, ARGUMENT2 and save result in ARGUMENT3.
 <pre>ADD R2,R3,R4</pre>
* The <code>SUB</code> instruction subtracts ARGUMENT2 from ARGUMENT1 and save result in ARGUMENT3.
<pre>SUB 17,R3,R4</pre>
* The <code>AND</code>, <code>XOR</code>, and <code>ORR</code> instructions perform bitwise AND, XOR, and OR operations on ARGUMENT1 and ARGUMENT2, and save result in ARGUMENT3.
<pre>AND r4,r8,output</pre>
<pre>ORR r4,r8,output</pre>
<pre>XOR r4,r8,output</pre>
* The <code>NOT</code> instruction perform bitwise NOT operation on ARGUMENT1 and save result in ARGUMENT3.
<pre>NOT INPUT,OUTPUT,output</pre>
* The <code>EQL</code> instruction checks if ARGUMENT1 is equal to ARGUMENT2, if it is true start execution from label which name is ARGUMENT3.
<pre>EQL 11,11,labelName</pre>
* The <code>NEQ</code> instruction checks if ARGUMENT1 is not equal to ARGUMENT2, if it is true start execution from label which name is ARGUMENT3.
<pre>NEQ 12,11,labelName</pre>
* The <code>LES</code> instruction checks if ARGUMENT1 is less than ARGUMENT2, if it is true start execution from label which name is ARGUMENT3.
<pre>LES 11,13,labelName</pre>
* The <code>LOE</code> instruction checks if ARGUMENT1 is less than or equal to ARGUMENT2, if it is true start execution from label which name is ARGUMENT3.
<pre>LOE 11,14,labelName</pre>
* The <code>MOR</code> instruction checks if ARGUMENT1 is more than ARGUMENT2, if it is true start execution from label which name is ARGUMENT3.
<pre>MOR 11,14,labelName</pre>
* The <code>MOE</code> instruction checks if ARGUMENT1 is more than or equal to ARGUMENT2, if it is true start execution from label which name is ARGUMENT3.
<pre>MOE 14,14,labelName</pre>


### Code Example

* The programm which get the integer and return the Fibonacci's number on that position.
```
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
```
