#include "algor.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

vector<int> generateRandomArray(int N) {
    vector<int> arr(N);
    generate(arr.begin(), arr.end(), rand);
    return arr;
}

vector<int> generateSortedArray(int N) {
    vector<int> arr = generateRandomArray(N);
    sort(arr.begin(), arr.end());
    return arr;
}

vector<int> generateReversedArray(int N) {
    vector<int> arr = generateSortedArray(N);
    reverse(arr.begin(), arr.end());
    return arr;
}

template <typename Func>
void benchmarkSort(Func sortFunction, vector<int> &arr, const string &algoName, const string &caseType) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << algoName << " (" << caseType << ") tomo " << duration << " microsegundos" << endl;
}

void benchmarkLinkedListSearch(SortedLinkedList &list, int value, const string &caseType) {
    auto start = high_resolution_clock::now();
    bool found = list.search(value);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "LinkedList Search (" << caseType << ") tomo " << duration << " microsegundos" << endl;
}

void benchmarkBSTInsert(BinarySearchTree &bst, int value, const string &caseType) {
    auto start = high_resolution_clock::now();
    bst.insert(value);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Binary Search Tree Insert (" << caseType << ") tomo " << duration << " microsegundos" << endl;
}

int main() {
    vector<int> N_values = {1000, 5000, 10000};

    for (int N : N_values) {
        cout << "\n--- N = " << N << " ---" << endl;

        vector<int> randomArray = generateRandomArray(N);
        benchmarkSort(bubbleSort, randomArray, "Bubble Sort", "Caso Promedio");
        randomArray = generateRandomArray(N);
        benchmarkSort(selectionSort, randomArray, "Selection Sort", "Caso Promedio");
        randomArray = generateRandomArray(N);
        benchmarkSort([&](vector<int> &arr){ mergeSort(arr, 0, arr.size() - 1); }, randomArray, "Merge Sort", "Caso Promedio");

        vector<int> reversedArray = generateReversedArray(N);
        benchmarkSort(bubbleSort, reversedArray, "Bubble Sort", "Peor Caso");
        reversedArray = generateReversedArray(N);
        benchmarkSort(selectionSort, reversedArray, "Selection Sort", "Peor Caso");
        reversedArray = generateReversedArray(N);
        benchmarkSort([&](vector<int> &arr){ mergeSort(arr, 0, arr.size() - 1); }, reversedArray, "Merge Sort", "Peor Caso");

        vector<int> sortedArray = generateSortedArray(N);
        benchmarkSort(bubbleSort, sortedArray, "Bubble Sort", "Mejor Caso");
        sortedArray = generateSortedArray(N);
        benchmarkSort(selectionSort, sortedArray, "Selection Sort", "Mejor Caso");
        sortedArray = generateSortedArray(N);
        benchmarkSort([&](vector<int> &arr){ mergeSort(arr, 0, arr.size() - 1); }, sortedArray, "Merge Sort", "Mejor Caso");

        cout << "\n--- LinkedList y Binary Search Tree para N = " << N << " ---" << endl;

        SortedLinkedList linkedList;
        for (int i = 0; i < N; i++) {
            linkedList.insert(i);
        }
        benchmarkLinkedListSearch(linkedList, N/2, "Mejor Caso");
        benchmarkLinkedListSearch(linkedList, N+1, "Peor Caso");

        BinarySearchTree bst;
        for (int i = 0; i < N; i++) {
            bst.insert(i);
        }
        benchmarkBSTInsert(bst, N+1, "Caso Promedio");
    }

    return 0;
}
