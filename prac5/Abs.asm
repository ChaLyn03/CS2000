// Calculates the absolute value of R1 and stores the result in R0.
// (R0, R1 refer to RAM[0], and RAM[1], respectively.)

// Put your code here.
// Load R1 into D register
@1
D=M

// Check if R1 is non-negative, jump to LABEL1
@LABEL1
D;JGE

// If R1 is negative, negate D to get absolute value
D=-D

// LABEL1
(LABEL1)
// Store the absolute value (D) into R0
@0
M=D
