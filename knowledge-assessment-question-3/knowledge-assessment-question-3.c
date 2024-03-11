/**
 * @file knowledge-assessment-quention-3.c
 * @brief Calculate statistics and extract even numbers from an array.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Calculate average, maximum, and minimum values of an array.
 *
 * This function calculates the average, maximum, and minimum values of
 * an integer array and stores the results in the provided pointers.
 *
 * @param arr The input array
 * @param n Number of elements in the array
 * @param average Pointer to store the average value
 * @param max Pointer to store the maximum value
 * @param min Pointer to store the minimum value
 */
void calculateStats(int arr[], int n, float *average, int *max, int *min)
{
    *average = 0;
    *max = arr[0];
    *min = arr[0];

    for (int i = 0; i < n; i++) // Calculate average, maximum, and minimum values
    {
        *average += arr[i];
        if (arr[i] > *max)
        {
            *max = arr[i];
        }
        if (arr[i] < *min)
        {
            *min = arr[i];
        }
    }
    *average /= n;
}

/**
 * @brief Extract even numbers from an array.
 *
 * This function creates a new array containing only the even numbers
 * from the original array and returns its size.
 *
 * @param arr The input array
 * @param n Number of elements in the input array
 * @param newSize Pointer to store the size of the new array
 * @return Pointer to the new array containing even numbers
 */
int *extractEvenNumbers(int arr[], int n, int *newSize)
{
    int count = 0;
    for (int i = 0; i < n; i++) // Count the number of even numbers in the original array
    {
        if (arr[i] % 2 == 0)
        {
            count++;
        }
    }

    int *evenArr = (int *)malloc(count * sizeof(int)); // Create a new array to store even numbers
    if (evenArr == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy even numbers from the original array to the new array
    *newSize = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            evenArr[*newSize] = arr[i];
            (*newSize)++;
        }
    }

    return evenArr;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]); // Calculates the number of elements of arr

    float average;
    int max, min;
    calculateStats(arr, n, &average, &max, &min);

    printf("Average: %.2f\n", average);
    printf("Maximum value: %d\n", max);
    printf("Minimum value: %d\n", min);

    int newSize;
    int *evenArr = extractEvenNumbers(arr, n, &newSize);

    printf("\nNew array size: %d\n", newSize);

    free(evenArr); // Free dynamically allocated memory

    return 0;
}
