// Author: Jason Zhou
#include "../../../general_include.h"

using namespace std;

class sortAlgorithm{
    public:
        // Bubble Sort
        // stable sorting algorithm
        // time complexity O(n^2)
        // space complexity O(1)
        void bubbleSort(int arr[], int n){
            int i, j;
            bool swapped;
            for (int i = 0; i < n; i++){
                swapped = false;
                for (int j = 0; j < n - i - 1; j++){
                    if (arr[j] > arr[j+1]){
                        int temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;
                        swapped = true;
                    }
                }

                if(!swapped){
                    break;
                }
            }
        }

        // Insertion Sort
        // stable sorting algorithm
        // time complexity O(n^2)
        // space complexity O(1)
        void insertionSort(int arr[], int n){
            for(int i = 1; i < n; i++){
                int key = arr[i];
                int j = i-1;
                while(j>=0 && key<arr[j]){
                    arr[j+1] = arr[j];
                    j--;
                }
                arr[j+1] = key; 
            }
        }

        // Merge Sort
        // stable sorting algorithm
        // time complexity O(n*logn)
        // space complexity O(n)
        void merge(int arr[], int l, int m, int r){ 
            int i, j, k;
            int n1 = m - l + 1;
            int n2 = r - m;

            int temp_l[n1];
            int temp_r[n2];

            for (int a = 0; a < n1; a++){
                temp_l[a] = arr[l+a];
            }

            for (int a = 0; a < n2; a++){
                temp_r[a] = arr[m+1+a];
            }

            i = 0;
            j = 0;
            k = l;

            while(i < n1 && j < n2){
                if(temp_r[j] < temp_l[i]){
                    arr[k] = temp_r[j];
                    j++;
                }else{
                    arr[k] = temp_l[i];
                    i++;
                }
                k++;
            }

            // copying the remaining in temp_l
            while(i < n1){
                arr[k] = temp_l[i];
                k++;
                i++;
            }

            while(j < n2){
                arr[k] = temp_r[j];
                k++;
                j++;
            }
        }

        void mergeSort(int arr[], int l, int r){
            if (l < r){
                int m = l + (r-l)/2;
                
                mergeSort(arr, l, m);
                mergeSort(arr, m+1, r);

                merge(arr, l, m, r);
            }
        }
};

int main(){
    // Set the seed for the random number generator
    std::srand(std::time(0));

    const int length = 100;
    int array[length];

    // Fill the array with random integers
    for (int i = 0; i < length; ++i) {
        array[i] = std::rand()%100;
    }

    // Print the initial unsorted array
    cout << "Initial Random Array: "<< endl;
    for (int i = 0; i < length; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // Call sorting algorithm
    sortAlgorithm a;
    // a.bubbleSort(array, length);
    // a.insertionSort(array, length);
    a.mergeSort(array, 0, length-1);

    // Print the sorted array
    cout << "Sorted Array: "<< endl;
    for (int i = 0; i < length; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    

    return 0;
}