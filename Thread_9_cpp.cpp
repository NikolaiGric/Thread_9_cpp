#include <iostream>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

class MergeSort {
public:
    void Sort(vector<int>& arr) {
        if (arr.size() > 1) {
            size_t mid = arr.size() / 2;
            vector<int> left(arr.begin(), arr.begin() + mid);
            vector<int> right(arr.begin() + mid, arr.end());

            Sort(left);
            Sort(right);

            Merge(arr, left, right);
        }
    }

private:
    void Merge(vector<int>& arr, const vector<int>& left, const vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                arr[k++] = left[i++];
            }
            else {
                arr[k++] = right[j++];
            }
        }

        while (i < left.size()) {
            arr[k++] = left[i++];
        }

        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    MergeSort sorter;
    vector<int> arr(10);

    cout << "Введите 10 чисел для сортировки:" << endl;
    for (int i = 0; i < 10; ++i) {
        cin >> arr[i];
    }

    auto sortFunc = [&sorter](vector<int>& array) {
        sorter.Sort(array);
        };

    thread mergeSortThread(sortFunc, ref(arr));

    mergeSortThread.join();

    cout << "Отсортированный массив:" << endl;
    for (const int& num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
