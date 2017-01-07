#include<stdio.h>

int main(){
  int32_t a = 3, b = -5, c = 3, d = 11;
  a -= b >> 31;
  c -= d >> 31;

  printf("b: 0x%x\td: 0x%x\n", b, d);  
  printf("a: %d\tc: %d\n", a, c);

  return 0;

}

/*

This snippet is used to optimize the conditional accumulation:

  if(b < 0) a++;

The above code can be optimized to:

  a -= b >> 31;

This is the reason:

 a = 1
 b = n
 c = -n

  No matter what value n is, 
    b >> 31 must be 0x0000 = 0 (positive value shift right will get 0 on the leftmost)
    c >> 31 must be 0xffff = -1 (negative value shift right will get 1 on the rightmost)

  As a result, 
    a -= b >> 31 equals to a -= 0  => a = a - 0
    a -= c >> 31 equals to a -= -1 => a = a - (-1) => a = a + 1

Where to optimize?

  In assembly, if..else.. statements will be compile to branch instruction which cost more stack and time. Bitwise operation can reduce such branch insructions.

*/
