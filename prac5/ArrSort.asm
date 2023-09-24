// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// ArrSort.asm
// Sorts an array in-place using the bubble sort algorithm

// Initialize registers
@0
D=M          // D = 0 (false)
@R2
D=D+A        // D = length of array + 1
@SP
M=D          // SP = length of array + 1
@R1
D=M
@SP
M=M-1
A=M
M=D          // *(SP-1) = RAM address of first element in array
@0
D=A
@SP
M=M-1
A=M
M=D          // *(SP-2) = 0

// Outer loop (n times)
(LOOP1)
  @0
  D=A
  @SP
  M=M-1
  A=M
  D=D-M       // D = n-i-1
  @END
  D;JEQ       // if D=0, jump to END
  @0
  D=A
  @SP
  M=M-1
  A=M
  M=D         // *(SP-2) = 0
  @R1
  D=M
  @SP
  M=M-1
  A=M
  M=D         // *(SP-1) = RAM address of first element in array

  // Inner loop (n-i-1 times)
  (LOOP2)
    @0
    D=A
    @SP
    M=M-1
    A=M
    D=D-M     // D = n-i-j-2
    @END2
    D;JEQ     // if D=0, jump to END2
    @R1
    D=M
    @SP
    M=M-1
    A=M
    D=D-M     // D = *(R1+j+1) - *(R1+j)
    @TEMP
    M=D       // TEMP = *(R1+j+1) - *(R1+j)
    @0
    D=A
    @SP
    M=M-1
    A=M
    D=D-M     // D = j
    @1
    D=D+A
    @SP
    A=M
    D=D+M     // D = RAM address of *(R1+j)
    @TEMP
    D;JGE     // if TEMP >= 0, jump to ELSE
    @R1
    D=M
    @SP
    M=M-1
    A=M
    D=D-M     // D = j
    @1
    D=D+A
    @SP
    A=M
    D=D+M     // D = RAM address of *(R1+j)
    @R1
    A=M
    M=D       // swap *(R1+j) with *(R1+j+1)
    @1
    D=A
    @SP
    M=M-1
    A=M
    D=D+A     // D = RAM address of *(R1+j+1)
    @TEMP
    A=M
    M=D
    @0
    D=A
    @SP
    M=M-1
    A=M
    D=D-M     // D = j
    @1
    D=D+A
    @SP
    A=M
    D=D+M     // D = RAM address of *(R1+j+1)
