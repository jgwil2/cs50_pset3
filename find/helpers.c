/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/*
 * Implements a recursive binary search algorithm.
 */
bool binary_search(int value, int values[], int min, int max)
{
    if(max < min)
    {   
        return false;
    }   
    
    int mid = min + (max - min) / 2;

    // search left
    if(values[mid] > value)
    {   
        return binary_search(value, values, min, mid - 1); 
    }   
    // search right
    else if(values[mid] < value)
    {   
        return binary_search(value, values, mid + 1, max);
    }   
    // value found, return true
    else
    {   
        return true;
    }   
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // if array size is 1 or less, check for value
    if(n <= 1)
    {   
        if(values[n] == value)
        {   
            return true;
        }   
         else
        {   
            return false;
        }   
    }   
    
    return binary_search(value, values, 0, n); 
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // if array length is 1 or less, array is already sorted
    if(n <= 1)
    {   
        return;
    }   
			 
    // bubble sort
    bool swapped = false;
    do  
    {   
        swapped = false;
        for(int i = 0; i < n; i++)
        {   
            if(values[i] > values[i + 1]) 
            {   
                int temp = values[i];
                values[i] = values[i + 1]; 
                values[i + 1] = temp;
                swapped = true;
            }
        }   
        n--; // on nth pass nth largest element is sorted
    }
    while(swapped == true);
    return;
}