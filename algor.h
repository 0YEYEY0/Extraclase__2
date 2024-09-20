#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <iostream>

// Función para intercambiar dos elementos
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Implementación de Bubble Sort
void bubbleSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Implementación de Selection Sort
void selectionSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[minIndex], arr[i]);
    }
}

// Implementación de Merge Sort
void merge(std::vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Estructura de lista enlazada ordenada
struct Node {
    int data;
    Node* next;
    Node* prev;
};

class SortedLinkedList {
private:
    Node* head;

public:
    SortedLinkedList() : head(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node{value, nullptr, nullptr};

        if (!head || head->data >= value) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && current->next->data < value)
            current = current->next;

        newNode->next = current->next;
        if (current->next) current->next->prev = newNode;
        current->next = newNode;
        newNode->prev = current;
    }

    bool search(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }
};

// Árbol binario de búsqueda
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    BSTNode* root;

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRec(root, value);
    }

    BSTNode* insertRec(BSTNode* node, int value) {
        if (!node) return new BSTNode(value);

        if (value < node->data)
            node->left = insertRec(node->left, value);
        else if (value > node->data)
            node->right = insertRec(node->right, value);

        return node;
    }
};

#endif // ALGORITHMS_H
