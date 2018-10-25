/* 
 * CS:APP Data Lab 
 * 
 * Luke Wuri, lwuri, 445002
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
       int newx = (~x+1); //invert x and add 1 making everything to the right of the 
       //smallest digit position to be all 0s.
       return (x &(newx));
       // the only digit x and newx will have in common will be in the
       // smallest bit as news will have all 0s to the right of the smallest bit
       // everything to the left will be opposite as well since we took the inverse of x
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
  return ((!x)|y);
  // from cse 240: x->y is equivalent to "not x or y"
  // if x were true (x=non zero), then !x = 0, so y would be only returned
  // if x were false (x=0), then !x = 1, so y would not be returned, !x would be returned
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  //int values have sign stored in the 32nd bit so we have to shift 31 digit places 
  //in binary to reach the sign value. 0 = positive, 1 = negatiive. 
  int sx = x>>31;
  int sy = y>>31;
 
  int signCheck = ((sx)&(!sy)); //equals 0 when x is positive, or when y is negative 
  int lesser = (~(sx^sy)&((~y+x)>>31));//flip bits of y and add to x;
  //- if x and y is positive
  // then we will obtain a negative value for the right side of the & expression
  //only if y is greater than x which will make the entire 'equal' value to be 0 automatically.

  //-if x and y is postive
  //then lesser will be 1 if y is less than x   
  return ((!lesser)&(!signCheck));//greater and signCheck must both be 0/false for x to be greater
    }
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  //x is the whole series of bytes
  //n is the chunk of bytes/the 'address' essentially  needing replacement
  //c is the actual set of digits that we put into n 
  //it seems each byte is two digits of hex, or 8 bits of binary
  int shiftedC = (c<<(n<<3));//shifts c's digits over to wherever n is located inside x 
  // note that everything "left" of the two c digits is 0s
 
  int mask =~(0xff<<(n<<3));//shifts 1111 1111 or 'ff'  all the way to where n is located and then
  //creates an empty area of 0s where we will place the digits from c
  return ((mask&x)|shiftedC); //takes the mask and x and "carves" out a series of 0s from x where we will then
  //place our c into.
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  //from msdn.microsoft.com database:
  //First x is converted to bool (!!), if true then y is evaluated
  //if false then z is evaluated

  int newx = (!!x); //check if x contains only 0s or nonzero digits
  int a =(~newx +1);//if newx is true(x is nonzero), then ~newx = 1111...1110 and adding 1
  //to it will make it all 1s so when we & it with y, we will only return y.
  //similar logic is applied for when x is 0, then ~a is all 1s instead, leaving just z
  //when we & it.
  return ((a&y)|((~a)&z));
    }
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  //bang returns a 1 ONLY when x=0 and a 0 for everything else
  
  int leastBitPos =(x & (~x+1)); //uses the first function to get smallest bit
  int b = 1+(~leastBitPos); //if x were 0, then ~leastBitPos = 1111...1111
  //adding a 1 to it would make the most significant, sign bit, become 1.
  //if x were nonzero, then the sign bit of b would be 0.

  int signB = b>>31;//extract the sign
  return ((~(signB))&1); //returns 1 if signB is 0 (x=0), or returns 0 if sign B is 1
  //this method deals with negative x (treats them the same as positives essentially) compared to another method I had in mind that was much simpler.
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  //the largest two's complement integer is all 1s except for the sign bit, which is 0
  //construct this by bring 1 to the MSB/sign bit then inverting it
  int a = ~(1<<31); //0111 1111 1111 1111 1111 1111 1111 1111
  return a;
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
  // similar to addOK except this wants actual values returned so ~ is used 
  int y = x+x;
  int sum = x+y;
  int signy = y>>31;
  int signsum = sum>>31;
  int signx = x>>31;
 
  int min = (1<<31)+~signx;//the tmin value

  int signCheck =(signx^signy)|(signx^signsum); //returns 1 if x is different sign from the final sum and the 
  //partial sum. returns 1 if there is overflow
  return ((~signCheck)&sum)+(signCheck&(min));//left hand side turns to 0 if there is overflow, right hand 
  //side turns to 0 if there is not overflow.
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  //the important part is the most significant bit of each value
  //x and y, x+y
  int sum = x+y;  
  int signsum = sum>>31;
  int signx = x>>31; 
  int signy = y >>31;

  //if signx and sign y are opposite in sign, they cannot overflow
  //when overflow occurs the Most Significant Bit when signs are different
  //ideally an infinite data size would never change sign bit if signs are the same
  //but in reality, when signs are the same and the sign bit suddenly changes, we know that overflow must
  //have occurred, which is why ^ is used.
  //!! to make boolean
  return !!((signx^signy)|(!(signx^signsum)&!(signy^signsum))); 
 
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  unsigned max = ~(1<<31);
  unsigned NaN = 0x7F800001;//exp bits are 1s and fracs are 0
  unsigned val = (uf&max); //sign becomes 0, positive
  if (val >= NaN) return uf; //already pos, so return uf
  return val;//return val otherwise
  //
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  //we need the individual signs, exp, and frac bits and use the respective masks
  //to isolate them
  unsigned expmask =0xFF;
  unsigned fracmask =0x7FFFFF;
  
  unsigned signuf = uf >> 31;
  unsigned expuf = (uf >> 23) & expmask;
  unsigned fracuf =(uf & fracmask);
  unsigned answer = fracuf;
  
  //we then follow a series of if statements to translate the digits
  //into int value
  
  if (expuf == expmask)//edge case 
    {
      return 0x80000000u;
    } 

  if (expuf < 0x7F) 
    {
      return 0x0;
    } 


   expuf -= (0x7F);
  

  if (expuf>=31) //edge case 
    {
      return 0x80000000u;
    } 
  if (expuf > 22) 
    {
      answer=(fracuf << (expuf-23));
    } 
  else 
    {
      answer=(answer >> (23 - expuf));
    }

  answer+=(1<<expuf); 
  
  if (signuf ==1) {//if negative, make positive
    answer = (-answer);
  }
   return answer;
}
