#include <stdio.h>
#include <string.h> // Include for memset


void matrixMultiplication(const float *matrixA, const float *matrixB, float *result, int size) {
    int remaining_size=0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            float *res = result + i * size + j;
            const float *rowA = matrixA + i * size;
            const float *colB = matrixB + j * size;

            float result_float_register=0;

            *res = 0.0f;
            float temp_res = 0.0f;

            // Perform dot product using the custom instruction
            for (int k = 0; k < size; k += 128) {
                asm volatile (
                     "optic  %[resrd], %[val1], %[val2], %[val3]\n"
                     : [resrd] "=f" (result_float_register)
                     : [val1] "r" (rowA + k), [val2]"r" (colB + k), [val3] "r" (res)
                );
                temp_res = temp_res + *res;
            }
            *res = temp_res;
        }
    }
}


int main() {
    const int size = 128;

    float matrixA[size][size];

    float matrixB[size][size];

    float result[size][size];

    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++)
        {
            matrixA[i][j] = 1;
            matrixB[i][j] = 1;
        }
    memset(result, 0, sizeof(result)); // Initialize the result matrix to zeros

    matrixMultiplication(&matrixA[0][0], &matrixB[0][0], &result[0][0], size);

    return 0;
}


/*
void custom_dot_product_instruction(const float *matrixA, const float *matrixB, float *result) {
    // Simulating parallel processing for 128 elements in your custom instruction
    for (int i = 0; i < 128; ++i) {
        // Here, *matrixA and *matrixB represent elements from matrixA and matrixB
        // Perform the dot product operation for the corresponding elements
        *result += (*matrixA) * (*matrixB);

        // Move pointers to the next elements for matrixA, matrixB, and result
        ++matrixA;
        ++matrixB;
    }
}

// Function to perform matrix multiplication using custom instruction
void matrixMultiplication(const float *matrixA, const float *matrixB, float *result, int size) {
    int remaining_size=0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            float *res = result + i * size + j;
            const float *rowA = matrixA + i * size;
            const float *colB = matrixB + j*size;

            *res = 0.0f;

            // Perform dot product using the custom instruction
            for (int k = 0; k < size; k += 128) {
                custom_dot_product_instruction(rowA + k, colB + k, res);
            }
        }
    }
}

int main() {
    const int size = 256; // Change this to your desired matrix dimension

    // Example matrices (size x size)
    float matrixA[size][size];

    float matrixB[size][size];

    float result[size][size];

    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++)
        {
            matrixA[i][j] = 1;
            matrixB[i][j] = 1;
        }
    memset(result, 0, sizeof(result)); // Initialize the result matrix to zeros

    // Perform matrix multiplication
    matrixMultiplication(&matrixA[0][0], &matrixB[0][0], &result[0][0], size);

    // Display the result
    printf("Resultant Matrix:\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%.2f ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
*/

/*
#include <stdio.h>
#include <string.h> // Include for memset

// Function to perform matrix multiplication
void matrixMultiplication(const float *matrixA, const float *matrixB, float *result, int size) {
    // Initialize result matrix to zeros
    memset(result, 0, sizeof(float) * size * size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                result[i * size + j] += matrixA[i * size + k] * matrixB[k * size + j];
            }
        }
    }
}

int main() {
    const int size = 4; // Change this to your desired matrix dimension

    // Example matrices (size x size)
    float matrixA[4][4] = {
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 10.0f, 11.0f, 12.0f},
        {13.0f, 14.0f, 15.0f, 16.0f}
    };

    float matrixB[4][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    float result[4][4];

    // Perform matrix multiplication
    matrixMultiplication(&matrixA[0][0], &matrixB[0][0], &result[0][0], size);

    // Display the result
    printf("Resultant Matrix:\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%.2f ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
*/
