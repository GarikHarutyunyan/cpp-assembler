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

### Instructions
The <code>ADD</code> instruction adds the values in V1 and V2.

The <code>SUB</code> instruction subtracts V2 from V1.
