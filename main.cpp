#include <iostream>
#include "SkipList.h"
#include <chrono>
#include "time.h"
void test(int countOfExperiments)
{
    for(int i = 10; i <= 100000; i *= 10)  // Testing on 50, 100...250 elements
    {
        int allTime = 0;
        for(int k = 0; k < countOfExperiments; k++) {
            SkipList list((int) log2(i), 0.5);

            /* Create an array to have an opportunity of quick choice of elements for searching and deleting */
            int *arr = new int[i];
            for (int j = 0; j < i; j++) {
                arr[j] = j + 1;
            }

            /* Shuffle the array */
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(arr, arr + i, std::default_random_engine(seed));

            int time = clock();
            for (int j = 0; j < i; j++)  // Fill the list
            {
                list.insertElement(arr[j]);
            }
            for (int j = 0; j < i; j++)  // Search every element
            {
                list.Search(arr[j]);
            }
            for (int j = 0; j < i; j++) // Remove all elements
            {
                list.Remove(arr[j]);
            }
            allTime += clock() - time;
            delete[] arr;
        }
        cout << "Count of elements: " << i << " time = " << ((double)allTime/countOfExperiments)/CLOCKS_PER_SEC << endl;
    }
}

int main()
{
    srand((unsigned)time(0));
    int n = 100; // count of experiments
    test(n);
}