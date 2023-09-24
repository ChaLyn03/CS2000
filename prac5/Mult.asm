// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Initialization
@2  // Load R2 into D register
D=M
@R2_COPY
M=D  // Store R2 into R2_COPY
@R1
D=A  // Load the address of R1 into D
@i
M=D  // Store the address of R1 into i
@0
D=A  // Load the address of R0 into D
@result
M=D  // Store the address of R0 into result
@R0
M=0  // Initialize R0 to 0

// Main multiplication loop
(LOOP)
@R2_COPY  // Load the copy of R2 into D register
D=M
@END
D;JEQ  // If R2 is 0, exit the loop
@i  // Load the address of R1 into A register
A=M
D=M  // Load the value of R1 into D register
@result  // Load the address of R0 into A register
A=M
M=D+M  // Add the value of R1 to R0
@R2_COPY  // Decrement the value of R2 copy
M=M-1
@LOOP  // Jump back to the start of the loop
0;JMP

// End of the program
(END)
