/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/*
 * 使用 ~ 和 & 实现异或，先用 |、&、~ 表示 ^
 * x ^ y == (x & ~y) | (~x & y)
 *
 * 两次取反，拼凑出 ~(a & b) == ~a | ~b 的形式
 * ~(~(x & ~y)) | ~(~(~x & y))
 *
 * 再利用 De Morgan's laws 消除 |
 * ~(~(x & ~y) & ~(~x & y))
 *
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    return ~(~(x & ~y) & ~(~x & y));
    // ~(~x & ~y) & ~(x & y);
}

/*
 * 获取对 2 补码的最小 int 值（TMin2）
 * C 语言 int 型是 32bits（4bytes），对 0x1 左移 31 位可得到最小值（补码最小值就是符号位为 1，其余全为 0）。
 *
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 0x1 << 31;
}
//2
/* 判断 x 是否补码最大值（TMax）
 * TMax 的符号位为 0，其余位为 1。
 *
 * isTmax - returns 1 if x is the maximum, two's complement number, and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {

    // TMin, 1000
    // 如果 x 是 TMax，+1 溢出则会变成 TMin
    int i = x + 1;

    // -1,1111
    // 由于 TMin 的绝对值比 TMax 大 1，TMax + TMin == -1
    x += i;

    // 0,0000
    // 逐位取反，-1 == (1111)2，~(1111)2 == (0000)2
    x = ~x;

    // exclude x = 0xffff
    // 需要排除转换过程仲的其他值，比如 0xffff... 也满足上述这种处理
    i = !i;
    x += i;

    // 最后对 x 做逻辑取反，只有当 x 为 000.。 时 !x 才为 1，否则为 0。
    return !x;
}

/*
 * 判断所有奇数位是否都为 1
 *
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    // 0xAA == [00000000 00000000 00000000 10101010]

    // 构造 32 位的、奇数位全为 1 的掩码：
    // <<8  [00000000 00000000 00000000 10101010]
    // ------------------------------------------
    //      [00000000 00000000 10101010 00000000]
    // +    [00000000 00000000 00000000 10101010]
    // ------------------------------------------
    // <<16 [00000000 00000000 10101010 10101010]
    // ------------------------------------------
    //      [10101010 10101010 00000000 00000000]
    // +    [00000000 00000000 10101010 10101010]
    // ------------------------------------------
    //      [10101010 10101010 10101010 10101010]
    int mask = 0xAA + (0xAA << 8);
    mask = mask + (mask << 16);

    // 利用掩码取 x 值的奇数位、其他位清零（过滤出相同的部分）；再与 mask 进行异或操作，相同则最终结果为 0，因此最后取一次逻辑非。

    // 当 x 奇数位全为 1
    // mask & x
    //      [10101010 10101010 10101010 10101010]     mask
    // &    [10101010 10101010 10101010 10101010]     x
    // ------------------------------------------
    //      [10101010 10101010 10101010 10101010]     mask & x
    // ^    [10101010 10101010 10101010 10101010]     mask
    // ------------------------------------------
    //      [00000000 00000000 00000000 00000000]     (mask & x) ^ mask
    // !((mask & x) ^ mask) == 1，判断为 T

    // 当 x 奇数位不全为 1
    // mask & x
    //      [10101010 10101010 10101010 10101010]     mask
    // &    [10101010 10101010 10101010 10000000]     x
    // ------------------------------------------
    //      [10101010 10101010 10101010 10000000]     mask & x
    // ^    [10101010 10101010 10101010 10101010]     mask
    // ------------------------------------------
    //      [00000000 00000000 00000000 00101010]     (mask & x) ^ mask
    // !((mask & x) ^ mask) == 0，判断为 F

    return !((mask & x) ^ mask);
}

/*
 * 不使用 - 操作符，求 -x 值
 *
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    // 补码是阿贝尔群，对于 x，-x 是其补码，所以 -x 可以通过对 x 取反 +1 得到。

    // x            [0101]2 == [5]10
    // ~x           [1010]2 == [-6]10
    // ~x + 1       [1011]2 == [-5]10
    // x == ~x + 1
    return ~x + 1;
}
//3
/*
 * 判断输入值是否数字 0 ~ 9 的 ASCII 值
 * TODO
 *
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    // 通过位级计算 x 是否在 0x30 ~ 0x39 范围内。

    // <<31 [00000000 00000000 00000000 00000001]
    // -----------------------------------------
    //      [10000000 00000000 00000000 00000000]
    int sign = 0x1 << 31;

    //      [10000000 00000000 00000000 00000000]
    // |    [00000000 00000000 00000000 00111001]
    // ------------------------------------------
    // ~    [10000000 00000000 00000000 00111001]
    // ------------------------------------------
    //      [11111111 11111111 11111111 11000110]
    int upperBound = ~(sign | 0x39);

    // ~    [00000000 00000000 00000000 00110000]
    // ------------------------------------------
    //      [11111111 11111111 11111111 11001111]
    int lowerBound = ~0x30;

    // 使用两个数，一个数是加上比 0x39 大的数后符号由正变负，另一个数是加上比 0x30 小的值时是负数。
    upperBound = sign & (upperBound + x) >> 31;
    lowerBound = sign & (lowerBound + 1 + x) >> 31;

    // 只有这两个数都为负数才成立。
    return !(upperBound | lowerBound);
}

/*
 * 使用位级运算实现 x? y: z 三目运算符
 *
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    // x = !!x;

    // 根据 x 的布尔值转换为全 0 或全 1，即 x == 0 时位表示是全 0，x != 0 时位表示是全 1。
    // 通过获取其布尔值 0 或 1，然后求其补码（0 的补码是本身，位表示全 0；1 的补码是 -1，位表示全 1）得到想要的结果。
    // 然后通过位运算获取最终值。

    // 当 x == 3，y == 2，z == 1：

    // 先对 x 取反。
    // ~    [0011]
    // -----------
    //      [1100]
    // +    [0001]
    // -----------
    //      [1101]
    x = ~x + 1;

    // 则 x & y：
    //      [1101]
    // &    [0010]
    // -----------
    //      [0000]

    // ~x & z：
    //      [0010]
    // &    [0001]
    // -----------
    //      [0000]

    return (x & y) | (~x & z);
}

/*
 * 使用位级运算符实现 <=
 *
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // -x
    int negX = ~x + 1;

    // y - x
    int addX = negX + y;

    // y - x 的符号
    int checkSign = addX >> 31 & 1;

    // 最大位为 1 的 32 位有符号数
    int leftBit = 1 << 31;

    // x 的符号
    int xLeft = x & leftBit;

    // y 的符号
    int yLeft = y & leftBit;

    // x 和 y 符号相同标志位，相同为 0 不同为 1
    int bitXor = xLeft ^yLeft;

    // 符号相同标志位格式化为 0 或 1
    bitXor = (bitXor >> 31) & 1;

    // 返回 1 有两种情况：符号相同标志位为 0（相同）位与 y - x 的符号为 0（y - x >= 0）结果为1；符号相同标志位为 1（不同）位与 x 的符号位为 1（x < 0）
    return ((!bitXor) & (!checkSign)) | (bitXor & (xLeft >> 31));
}

//4
/* 使用位级运算求逻辑非 !
 *
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    // 逻辑非就是非 0 为 1，非非 0 为 0。
    // 利用其补码（取反 + 1）的性质，除了 0 和最小数（符号位为 1，其余全为 0）外，其他数都是相反数关系（符号位取位或为 1）。
    // 0 和最后数的补码是本身，0 的符号位与其补码符号位或为 0，最小数为 1。
    return ((x | (~x + 1)) >> 31) + 1;
}

/* howManyBits - return the minimum number of bits required to represent x in two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int b16, b8, b4, b2, b1, b0;
    int sign = x >> 31;
    // 如果 x 为正则不变，否则按位取反（这样好找最高位为 1 的，原来是最高位为 0 的，将符号位去掉
    x = (sign & ~x) | (~sign & x);

    // 不断缩小范围
    // 高十六位是否有 1
    b16 = !!(x >> 16) << 4;

    //如果有（至少需要 16 位），则将原数右移 16 位
    x = x >> b16;

    // 剩余位高 8 位是否有 1
    b8 = !!(x >> 8) << 3;

    //如果有（至少需要 16 + 8 = 24 位），则右移 8 位
    x = x >> b8;

    // 同理
    b4 = !!(x >> 4) << 2;
    x = x >> b4;
    b2 = !!(x >> 2) << 1;
    x = x >> b2;
    b1 = !!(x >> 1);
    x = x >> b1;
    b0 = x;

    // +1 表示加上符号位
    return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    return 2;
}

/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
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
int floatFloat2Int(unsigned uf) {
    return 2;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
