#include <specialization_algorithms.h>

using namespace std;

long unsigned int Spec_Algorithms_v1::_merge(int arr[], int temp[], unsigned int left, int mid, unsigned int right)
{
    int i, j, k;
    long unsigned int inv_count = 0;
  
    i = left; /* i is index for left subarray*/
    j = mid; /* j is index for right subarray*/
    k = left; /* k is index for resultant merged subarray*/
    while ((i <= (int)mid - 1) && (j <= (int)right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
  
            /* this is tricky -- see above
            explanation/diagram for merge()*/
            inv_count = inv_count + (mid - i);
        }
    }
  
    /* Copy the remaining elements of left subarray
(if there are any) to temp*/
    while (i <= mid - 1)
        temp[k++] = arr[i++];
  
    /* Copy the remaining elements of right subarray
       (if there are any) to temp*/
    while (j <= (int)right)
        temp[k++] = arr[j++];
  
    /*Copy back the merged elements to original array*/
    for (i = (int)left; i <= (int)right; i++)
        arr[i] = temp[i];
  
    return inv_count;
}

long unsigned int Spec_Algorithms_v1::_mergeSort(int arr[], int temp[], unsigned int left, unsigned int right)
{
    long unsigned int mid, inv_count = 0;
    if (right > left) {
        /* Divide the array into two parts and
        call _mergeSortAndCountInv()
        for each of the parts */
        mid = (right + left) / 2;
  
        /* Inversion count will be sum of
        inversions in left-part, right-part
        and number of inversions in merging */
        inv_count += _mergeSort(arr, temp, left, mid);
        inv_count += _mergeSort(arr, temp, mid + 1, right);
  
        /*Merge the two parts*/
        inv_count += _merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}
  
long unsigned int Spec_Algorithms_v1::mergeSort(int arr[], int array_size)
{
    int temp[array_size];
    return _mergeSort(arr, temp, 0, array_size - 1);
}

long unsigned int Spec_Algorithms_v1::naiveInvCount(int arr[], int n)
{
    long unsigned int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                inv_count++;
  
    return inv_count;
}
long unsigned int Spec_Algorithms_v1::naiveInvCount(vector<int> arr)
{
    return naiveInvCount(&arr[0], (int)arr.size());
}

long unsigned int Spec_Algorithms_v1::partialInvCount(vector<int> arr, int from_index, int to_index)
{
    long unsigned int inv_count = 0;
    for (int i = from_index; i <= min(to_index, (int)arr.size() - 1); i++)
        for (int j = min(i + 1, (int)arr.size() - 1); j < (int)arr.size(); j++)
            if (arr[i] > arr[j])
                inv_count++;
  
    return inv_count;
}
long unsigned int Spec_Algorithms_v1::partialInvCount(vector<int> arr, int from_index)
{
    return partialInvCount(arr, from_index, arr.size() - 1);
}

void Spec_Quicksort_v1::_lomuto_quicksort(vector<int>* arr, int low, int high, int* comps, Quicksort_Partition_Type ptype, bool use_median_of_three)
{
    if (high <= low || low < 0) return;

    int p;
    switch (ptype)
    {
    case FIRST:
        p =  _first_element_partition(arr, low, high, comps, use_median_of_three);
        break;
    case LAST:
        p =  _last_element_partition(arr, low, high, comps, use_median_of_three);
        break;
    default:
        p =  _first_element_partition(arr, low, high, comps, use_median_of_three);
        break;
    }

    _lomuto_quicksort(arr, low, p - 1, comps);
    _lomuto_quicksort(arr, p + 1, high, comps);
}

void Spec_Quicksort_v1::_lomuto_quicksort(vector<int>* arr, int low, int high, int* comps, Quicksort_Partition_Type ptype)
{
    return _lomuto_quicksort(arr, low, high, comps, ptype, false);
}

void Spec_Quicksort_v1::_lomuto_quicksort(vector<int>* arr, int low, int high, int* comps)
{
    return _lomuto_quicksort(arr, low, high, comps, FIRST);
}

void Spec_Quicksort_v1::_hoare_quicksort(vector<int>* arr, int low, int high, int* comps)
{
    if (low >= 0 && high >= 0 && low < high)
    {
        int p = _median_element_partition(arr, low, high, comps);
        _hoare_quicksort(arr, low, p, comps);
        _hoare_quicksort(arr, p + 1, high, comps);
    }
}

int Spec_Quicksort_v1::quicksort(vector<int>* arr, Quicksort_Type type)
{
    int comps = 0;
    switch (type)
    {
    case LOMUTO:
        _lomuto_quicksort(arr, 0, arr->size() - 1, &comps);
        break;
    case HOARE:
        _hoare_quicksort(arr, 0, arr->size() - 1, &comps);
        break;
    
    default:
        _lomuto_quicksort(arr, 0, arr->size() - 1, &comps);
        break;
    }
    return comps;
}

int Spec_Quicksort_v1::quicksort(vector<int>* arr)
{
    int comps = 0;
    _lomuto_quicksort(arr, 0, arr->size() - 1, &comps, LAST, true);
    return comps;
}

int Spec_Quicksort_v1::_first_element_partition(vector<int>* arr, int low, int high, int* comps, bool use_median_of_three)
{
    int p;
    if(use_median_of_three)
    {
        int mid = (int)floor(low/2 + high/2);
        if ((*arr)[mid] > (*arr)[low])
            _swap(arr, low, mid);
        if ((*arr)[high] < (*arr)[low])
            _swap(arr, low, high);
        if ((*arr)[mid] > (*arr)[high])
            _swap(arr, mid, high);
        p = (*arr)[low];
    } else 
        p = (*arr)[low];

    int i = low + 1;
    for (int j = low + 1; j <= high; j++)
    {
        (*comps)++;
        if ((*arr)[j] < p)
        {
            _swap<int>(arr, j, i);
            i++;
        }
    }
    _swap<int>(arr, low, i-1);
    return i-1;
}

int Spec_Quicksort_v1::_first_element_partition(vector<int>* arr, int low, int high, int* comps)
{
    return _first_element_partition(arr, low, high, comps, false);
}

int Spec_Quicksort_v1::_last_element_partition(vector<int>* arr, int low, int high, int* comps, bool use_median_of_three)
{
    int p;
    if(use_median_of_three)
    {
        int mid = (int)floor(low/2 + high/2);
        if ((*arr)[mid] < (*arr)[low])
            _swap(arr, low, mid);
        if ((*arr)[high] < (*arr)[low])
            _swap(arr, low, high);
        if ((*arr)[mid] < (*arr)[high])
            _swap(arr, mid, high);
        p = (*arr)[low];
    } else 
        p = (*arr)[low];

    int i = low + 1;
    for (int j = low + 1; j <= high; j++)
    {
        (*comps)++;
        if ((*arr)[j] < p)
        {
            _swap<int>(arr, j, i);
            i++;
        }
    }
    _swap<int>(arr, low, i-1);
    return i-1;
}

int Spec_Quicksort_v1::_last_element_partition(vector<int>* arr, int low, int high, int* comps)
{
    return _last_element_partition(arr, low, high, comps, false);
}

int Spec_Quicksort_v1::_median_element_partition(vector<int>* arr, int low, int high, int* comps)
{

    int mid = (int)floor(low/2 + high/2);
    int pivot = (*arr)[mid];

    // Left index
    int i = low - 1 ;
    // Right index
    int j = high + 1;

    while (true)
    {
    // Move the left index to the right at least once and while the element at
    // the left index is less than the pivot
    do {i++; (*comps)++;} while ((*arr)[i] < pivot);

    // Move the right index to the left at least once and while the element at
    // the right index is greater than the pivot
    do {--j; (*comps)++;} while ((*arr)[j] > pivot);

    // If the indices crossed, return
    if (i >= j) {return j;}

    // Swap the elements at the left and right indices
    _swap(arr, i, j);
    }
  
}

template<class T>
void Spec_Quicksort_v1::_swap(vector<T>* arr, int idx1, int idx2)
{
    if(!(idx1 < 0 || idx1 >= (int)arr->size() || idx2 < 0 || idx2 >= (int)arr->size()))
    {
        T _aux = (*arr)[idx1];
        (*arr)[idx1] = (*arr)[idx2];
        (*arr)[idx2] = _aux; 
    }

}