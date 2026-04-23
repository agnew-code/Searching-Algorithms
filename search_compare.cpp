#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime> // Changed from <chrono> for better compatibility

using namespace std;

// --- Helper for Timing (Using ctime) ---
void printTime(clock_t start, clock_t end) {
    // Calculate difference and convert to microseconds
    // (1,000,000 microseconds in 1 second)
    double duration = (double(end - start) / CLOCKS_PER_SEC) * 1000000;
    cout << "\n[Time Taken: " << duration << " microseconds]" << endl;
}

// --- 1. Linear Search ---
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// --- 2. Binary Search ---
int binarySearch(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    int low = 0, high = (int)arr.size() - 1;
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
    // Standard for loop used instead of range-based for compatibility
    for (int i = 0; i < (int)arr.size(); i++) {
        int x = arr[i];
        int index = x % tableSize;
        while (hashTable[index] != -1) index = (index + 1) % tableSize;
        hashTable[index] = x;
    }
    int idx = target % tableSize;
    int startIdx = idx;
    while (hashTable[idx] != -1) {
        if (hashTable[idx] == target) return idx;
        idx = (idx + 1) % tableSize;
        if (idx == startIdx) break;
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

        // Use clock_t instead of steady_clock
        clock_t start = clock();
        int res = -1;

        if (choice == 1) res = linearSearch(data, target);
        else if (choice == 2) res = binarySearch(data, target);
        else if (choice == 3) res = hashSearch(data, target, n * 2);

        clock_t end = clock();

        if (res != -1) cout << "Found!";
        else cout << "Not found.";

        printTime(start, end);

    } while (choice != 4);
    return 0;
}
