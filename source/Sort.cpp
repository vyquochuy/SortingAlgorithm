#include "Sort.h"
using namespace std;

void PrintArr(int *a, int n){
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
}

void SelectionSort(int arr[], int n, long long &comparisons) {
    for (int i = 0; ++comparisons && i < n - 1; i++) {
        int min_indx = i;
        for (int j = i + 1;++comparisons && j < n; j++) {
            if (++comparisons && arr[min_indx] > arr[j])
                min_indx = j;
        }
        swap(arr[min_indx], arr[i]);
    }
}

void InsertionSort(int a[], int n, long long &comparisons) {
    int key, j;
    for (int i = 1; ++comparisons && i < n; i++) {
        key = a[i];
        j = i - 1;
        while (++comparisons && j >= 0 && ++comparisons && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void BubbleSort(int a[], int n, long long &comparisons) {
    for (int i = 0; ++comparisons && i < n - 1; ++i) {
        for (int j = i + 1;++comparisons && j < n; ++j) {
            if (++comparisons && a[i] > a[j] ) {
                swap(a[i], a[j]);
            }
        }
    }
}

void Heapify(int arr[], int n, int i, long long &comparisons) {
    int largest = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;

    comparisons++; // Tăng số lần so sánh ở dòng if trên
    if (left < n) {
        comparisons++;  // Tăng số lần so sánh ở dòng if dưới
        if (arr[left] > arr[largest]){
            largest = left;
        }
    }

    comparisons++; // Tăng số lần so sánh
    if (right < n) {
        comparisons++;
        if (arr[right] > arr[largest]){
            largest = right;
        }
    }

    comparisons++;
    if (largest != i) {
        swap(arr[largest], arr[i]);
        Heapify(arr, n, largest, comparisons);
    }
}

void HeapSort(int arr[], int n, long long &comparisons) {
    for (int i = n / 2 - 1; i >= 0 && ++comparisons ; i-- )
        Heapify(arr, n, i, comparisons);

    for (int i = n - 1; i > 0 && ++comparisons ; i--) {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0, comparisons);
    }
}

void Merge(int arr[], int l, int m, int r, long long &comparisons) {
    int length1 = m - l + 1;
    int length2 = r - m;

    int *leftArr = new int[length1];
    int *rightArr = new int[length2];

    for (int i = 0; ++comparisons && i < length1; i++)
        leftArr[i] = arr[l + i];

    for (int i = 0; ++comparisons && i < length2; i++)
        rightArr[i] = arr[m + i + 1];

    int indexOfArr1 = 0, indexOfArr2 = 0, i = l;

    while (++comparisons && indexOfArr1 < length1 && ++comparisons && indexOfArr2 < length2) {
        if (++comparisons && leftArr[indexOfArr1] < rightArr[indexOfArr2]) {
            arr[i] = leftArr[indexOfArr1++];
        } 
        else if (++comparisons && leftArr[indexOfArr1] >= rightArr[indexOfArr2]) {
            arr[i] = rightArr[indexOfArr2++];
        }
        i++;
    }

    while (++comparisons && indexOfArr1 < length1 ) {
        arr[i++] = leftArr[indexOfArr1++];
    }
    while (++comparisons && indexOfArr2 < length2) {
        arr[i++] = rightArr[indexOfArr2++];
    }
    delete[] leftArr;
    delete[] rightArr;
}

void MergeSort(int arr[], int l, int r, long long &comparisons) {
    if (l >= r)
        return;
    int m = (r + l) / 2;
    MergeSort(arr, l, m, comparisons);
    MergeSort(arr, m + 1, r, comparisons);
    Merge(arr, l, m, r, comparisons);
}

int MedianOfThree(int arr[], int l, int r, long long &comparisons) {
    int mid = l + (r - l) / 2;
    if (++comparisons && arr[mid] < arr[l]) {
        swap(arr[mid], arr[l]);
    }
    if (++comparisons && arr[r] < arr[l]) {
        swap(arr[r], arr[l]);
    }
    if (++comparisons && arr[r] < arr[mid]) {
        swap(arr[r], arr[mid]);
    }
    return mid;
}

int Partition(int arr[], int l, int r, long long &comparisons) {
    int pivotIndex = MedianOfThree(arr, l, r, comparisons);
    int pivot = arr[pivotIndex];
    swap(arr[pivotIndex], arr[r]);

    int i = l - 1;
    for (int j = l; ++comparisons && j < r; j++) {
        if (++comparisons && arr[j] < pivot)
            swap(arr[++i], arr[j]);
    }
    i++;
    swap(arr[i], arr[r]);
    return i;
}

void QuickSort(int arr[], int l, int r, long long &comparisons) {
    if (++comparisons && l < r) {
        comparisons++;
        int pivot = Partition(arr, l, r, comparisons);
        QuickSort(arr, l, pivot - 1, comparisons);
        QuickSort(arr, pivot + 1, r, comparisons);
    }
}

int GetMax(int a[], int n, long long &comparisons) {
    int mx = a[0];
    for (int i = 0; i < n && ++comparisons; i++) {
        comparisons++; // Tăng số lần so sánh
        mx = std::max(mx, a[i]);
    }
    return mx;
}

void CountSort(int a[], int n, int exp, long long &comparisons) {
    int i, count[10] = {0};
    int OutPutArray[500000];

    for (i = 0; ++comparisons && i < n; i++) {
        count[(a[i] / exp) % 10]++;
    }

    for (i = 1; ++comparisons && i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (i = n - 1; ++comparisons && i >= 0; i--) {
        OutPutArray[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }

    for (i = 0;++comparisons && i < n; i++) {
        a[i] = OutPutArray[i];
    }
}

void RadixSort(int a[], int n, long long &comparisons) {
    int mx = GetMax(a, n, comparisons);
    for (int exp = 1;++comparisons && mx / exp > 0; exp *= 10) {
        CountSort(a, n, exp, comparisons);
    }
}