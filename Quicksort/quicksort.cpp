#include <iostream>

//Powtórka AISD1
//2.Zaimplementuj algorytm sortujący tablicę 2D metodą Quicksort

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define ROWS 4
#define COL 5

using namespace std;

void quicksort(int arr[], int start, int end) {
    int pivot, i, j, temp;
    if (start < end) {
        pivot = start;
        i = start;
        j = end;
        while (i < j) {
            while (arr[i] <= arr[pivot] && i < end)
                i++;
            while (arr[j] > arr[pivot])
                j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;
        quicksort(arr, start, j - 1);
        quicksort(arr, j + 1, end);
    }
}


int main() {
	
    //deklaracja tablicy 2D
    int** array2D = new int* [ROWS];
    for (int i = 0; i < ROWS; ++i)
        array2D[i] = new int[COL];

    //wypelnienie tablicy 2d:
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COL; j++)
            array2D[i][j] = rand() % 100;
    }

    cout << "Przed (2D): " << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COL; j++)
            printf("%2d ", array2D[i][j]);
        cout << endl;
    }
    cout << endl;

    //zaalokowanie pamieci  dla tablicy 1D o wymiarach wiersze x kolumny
    int* array1D = (int*)malloc(ROWS * COL * sizeof(int));

    //mapowanie wartosci z tablicy 2D do 1D
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COL; ++j) {
            array1D[i * COL + j] = array2D[i][j];
        }
    }

    cout << "Przed (1D): " << endl;
    for (int i = 0; i < ROWS * COL; i++) {
        printf("%2d ", array1D[i]);
    }

    cout << endl;
    cout << endl;

    quicksort(array1D, 0, ROWS * COL - 1);

    int k = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COL; j++) {
            array2D[i][j] = array1D[k];
            k++;
        }
    }
	
    cout<< "Po sortowaniu (2D): "<<endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COL; j++)
            printf("%2d ", array2D[i][j]);
        cout << endl;
    }

    return 0;
}



