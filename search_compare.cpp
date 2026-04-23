#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// --- Helper for Timing ---
void printTime(steady_clock::time_point start, steady_clock::time_point end) {
    auto duration = duration_cast<microseconds>(end - start);
    cout << "\n[Time Taken: " << duration.count() << " microseconds]" << endl;
}

// --- 1. Linear Search ---
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// --- 2. Binary Search ---
int binarySearch(vector<int> arr, int target) {
    sort(arr.begin(), arr.end()); // Binary search requires sorting
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// --- 3. Hashing (Modulo Method) ---
int hashSearch(const vector<int>& arr, int target, int tableSize) {
    vector<int> hashTable(tableSize, -1);
    for (int x : arr) {
        int index = x % tableSize;
        while (hashTable[index] != -1) index = (index + 1) % tableSize; // Collision handling
        hashTable[index] = x;
    }
    int idx = target % tableSize;
    int start = idx;
    while (hashTable[idx] != -1) {
        if (hashTable[idx] == target) return idx;
        idx = (idx + 1) % tableSize;
        if (idx == start) break;
    }
    return -1;
}

int main() {
    int n, choice, target;
    cout << "Enter number of elements: "; cin >> n;
    vector<int> data(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> data[i];

    do {
        cout << "\n--- SEARCH MENU ---\n1. Linear Search\n2. Binary Search\n3. Hashing\n4. Exit\nChoice: ";
        cin >> choice;
        if (choice == 4) break;
        cout << "Enter target: "; cin >> target;

        auto start = steady_clock::now();
        int res = -1;

        if (choice == 1) res = linearSearch(data, target);
        else if (choice == 2) res = binarySearch(data, target);
        else if (choice == 3) res = hashSearch(data, target, n * 2);

        auto end = steady_clock::now();

        if (res != -1) cout << "Found!";
        else cout << "Not found.";
        printTime(start, end);

    } while (choice != 4);
    return 0;
}
