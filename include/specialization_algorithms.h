#if !defined(SPECIALIZATION_ALGORITHM_V1_H)
#define SPECIALIZATION_ALGORITHM_V1_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


class Spec_Algorithms_v1
{
    /* This function merges two sorted arrays
    and returns inversion count in the arrays.*/
    static long unsigned int _merge(int arr[], int temp[], unsigned int left, int mid, unsigned int right);
    /* An auxiliary recursive function
    that sorts the input array and
    returns the number of inversions in the array. */
    static long unsigned int _mergeSort(int arr[], int temp[], unsigned int left, unsigned int right);
    
    public:

        /* This function sorts the
        input array and returns the
        number of inversions in the array */
        static long unsigned int mergeSort(int arr[], int array_size);
        static long unsigned int naiveInvCount(int arr[], int n);
        static long unsigned int naiveInvCount(vector<int> arr);
        static long unsigned int partialInvCount(vector<int> arr, int from_index, int to_index);
        static long unsigned int partialInvCount(vector<int> arr, int from_index);

};

enum Quicksort_Type {LOMUTO, HOARE};
enum Quicksort_Partition_Type {FIRST,MEDIAN, LAST};


class Spec_Quicksort_v1
{
    template<class T>
    static void _swap(vector<T>* arr, int idx1, int idx2);

    // Returns the number of comparisons 
    // algorithm quicksort(A, lo, hi) is 
    //   if lo >= hi || lo < 0 then 
    //     return
        
    //   p := partition(A, lo, hi) 
        
    //   quicksort(A, lo, p - 1) // Left side of pivot
    //   quicksort(A, p + 1, hi) // Right side of pivot
    static int _lomuto_quicksort(vector<int>* arr, int low, int high, Quicksort_Partition_Type ptype);
    static int _lomuto_quicksort(vector<int>* arr, int low, int high);

    // Sorts a (portion of an) array, divides it into partitions, then sorts those
    // algorithm quicksort(A, lo, hi) is 
    //   if lo >= 0 && hi >= 0 && lo < hi then
    //     p := partition(A, lo, hi) 
    //     quicksort(A, lo, p) // Note: the pivot is now included
    // quicksort(A, p + 1, hi) 
    static int _hoare_quicksort(vector<int>* arr, int low, int high);
    // algorithm partition(A, lo, hi) is 
    //   pivot := A[hi] // Choose the last element as the pivot

    //   i := lo - 1

    //   for j := lo to hi - 1 do 
    //     if A[j] <= pivot then 
    //       i := i + 1
    //       swap A[i] with A[j]

    //   i := i + 1
    //   swap A[i] with A[hi]
    //   return i // the pivot index
    static int _partition(vector<int>* arr, int low, int high, int pindex);
    static int _first_element_partition(vector<int>* arr, int low, int high);
    static int _last_element_partition(vector<int>* arr, int low, int high);

    static int _use_median_of_three(vector<int>* arr, int low, int high);

    static int _hoare_partition(vector<int>* arr, int low, int high);
    
    public:
        static int quicksort(vector<int>* arr, Quicksort_Type type, Quicksort_Partition_Type partition);
        static int quicksort(vector<int>* arr);
};

#endif // SPECIALIZATION_ALGORITHM_V1_H

