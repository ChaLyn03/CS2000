// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Initialize R0 with a large number.
@32767  // 32767 is the maximum positive value in 16-bit two's complement.
D=A
@0
M=D

// Load base address (R1) into A register.
@1
D=M
@BASE
M=D

// Load counter (R2) into R3.
@2
D=M
@3
M=D

// Label for the loop.
(LOOP)

// Check if counter is zero, exit if it is.
@3
D=M
@END
D;JEQ

// Load the next value from the array into D.
@BASE
A=M
D=M

// Compare with the current minimum in R0.
@0
D=D-M
@CONTINUE
D;JGE

// If the number is smaller, update R0.
@BASE
A=M
D=M
@0
M=D

// CONTINUE Label.
(CONTINUE)

// Increment the base address.
@BASE
M=M+1

// Decrement the counter.
@3
M=M-1

// Jump to the loop start.
@LOOP
0;JMP

// END Label.
(END)
