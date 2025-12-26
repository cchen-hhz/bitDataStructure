#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int CUTOFF = 5;
vector<int> median3Values;  

void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && temp < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

int median3(vector<int>& arr, int left, int right) {
    int center = left + (right - left) / 2;
    
    if (arr[left] > arr[center])
        swap(arr[left], arr[center]);
    if (arr[left] > arr[right])
        swap(arr[left], arr[right]);
    if (arr[center] > arr[right])
        swap(arr[center], arr[right]);
    
    
    swap(arr[center], arr[right - 1]);
    
    median3Values.push_back(arr[right - 1]);
    
    return arr[right - 1];
}

int partition(vector<int>& arr, int left, int right) {
    int pivot = median3(arr, left, right);
    
    int i = left;
    int j = right - 1;
    
    while (true) {
        while (arr[++i] < pivot) {}
        
        while (arr[--j] > pivot) {}
        
        if (i < j) {
            swap(arr[i], arr[j]);
        } else {
            break;
        }
    }
    
    swap(arr[i], arr[right - 1]);
    
    return i;
}

void quickSort(vector<int>& arr, int left, int right) {
    if (right - left + 1 <= CUTOFF) {
        insertionSort(arr, left, right);
    } else {
        int pivotPos = partition(arr, left, right);

        if (left < pivotPos - 1) {
            quickSort(arr, left, pivotPos - 1);
        }
        
        if (pivotPos + 1 < right) {
            quickSort(arr, pivotPos + 1, right);
        }
    }
}

int main() {
    vector<int> arr;
    int num;
    
    while (cin >> num) {
        arr.push_back(num);
        
        if (cin.peek() == '#') {
            break;
        }
    }
    
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
        
        cout << "After Sorting:" << endl;
        for (int i = 0; i < arr.size(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        cout << "Median3 Value:" << endl;
        if (median3Values.empty()) {
            cout << "none" << endl;
        } else {
            for (int i = 0; i < median3Values.size(); i++) {
                cout << median3Values[i] << " ";
            }
            cout << endl;
        }
    }
    
    return 0;
}