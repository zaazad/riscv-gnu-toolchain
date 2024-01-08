#include <stdio.h>

int main() {
    float array1[128];
    float array2[128];
    float array3=0;
    float result=0;

    // Initialize the arrays...
    for (int i=0; i<128; i++)
    {
    	array1[i] = 1;
	    array2[i] = 1;
    }

    asm volatile (
        "optic  %[res], %[val1], %[val2], %[val3]\n"
        : [res] "=f" (result)
        : [val1] "r" (array1), [val2]"r" (array2), [val3] "r" (&array3)
    );

    printf("Result: %f     %f\n", result, array3);

    return 0;
}
