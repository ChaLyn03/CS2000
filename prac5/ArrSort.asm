// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Load base address (R1) into R4.
@1
D=M
@4
M=D

// Load the length of the array (R2) into R5.
@2
D=M
@5
M=D

// Start of the outer loop.
(OUTERLOOP)

// Check if R5 (length) is 1, jump to END if yes.
@5
D=M
@END
D;JEQ

// Load base address (R4) into A register.
@4
A=M
D=A
@6
M=D // store the base address in R6 for inner loop use

// Start of the inner loop.
(INNERLOOP)

// Load next value from array into D.
@6
A=M
D=M

// Load the next address into A and compare with next value in the array.
@6
A=M+1
D=D-M // D now holds the difference between the two adjacent elements

// If the previous element is greater than the next element, swap them.
@SWAP
D;JGT

// Go to CONTINUE if no need to swap.
@CONTINUE
0;JMP

// Swap the two adjacent elements.
(SWAP)
@6
A=M
D=M // D holds the value of the current element
@6
A=M+1
M=D // put the value of the current element in the next address
@6
A=M
D=A+1
A=D
D=M // D holds the value of the next element
@6
A=M
M=D // put the value of the next element in the current address

// CONTINUE label.
(CONTINUE)

// Increment the address for the inner loop.
@6
M=M+1

// Decrement R5 (length) by 1 for the inner loop.
@5
M=M-1

// Jump to the start of the inner loop.
@INNERLOOP
0;JMP

// End of the outer loop, reload the length (R2) into R5.
@2
D=M
@5
M=D

// Restart the base address (R4) for outer loop use.
@4
D=M
@6
M=D

// Jump to the start of the outer loop.
@OUTERLOOP
0;JMP

// End of the sorting algorithm.
(END)

// Set R0 to True (-1) to indicate completion.
@0
M=-1
