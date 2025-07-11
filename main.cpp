// # Project-C--Problem-12.1---Heily-Cabrera

/**The median m of a sequence of n elements is the element that would fall in the middle if the sequence was sorted. That is, e ≤ m for half the elements, and m ≤ e for the others. 
Clearly, one can obtain the median by sorting the sequence, but one can do quite a bit better with the following algorithm that finds the kth element of a sequence between a (inclusive) and b (exclusive).
(For the median, use k = n/2, a = 0, and b = n.)
Implement this algorithm and measure how much faster it is for computing the median of a random large sequence, when compared to sorting the sequence and taking the middle element. **/

//Programmer: Heily Cabrera
//Tester: Audrey Tapia

// Group Project C //
/***** Members *****/
/***** Ashley Jacobson *****/
/***** Giannfranco Brance *****/
/***** Audrey Tapia *****/
/***** Heily Cabrera Guerrero *****/

#include <iostream>
#include <vector>
#include <algorithm> 
#include <random>    
#include <chrono>    

using namespace std;

int select_kth(vector<int> arr, int k) 
{
    while (true) 
        {
        if (arr.size() == 1) 
        {
            return arr[0];
        }

        int pivot = arr[rand() % arr.size()];

        vector<int> low, equal, high;

        for (int num : arr) 
        {
            if (num < pivot) low.push_back(num);
            else if (num > pivot) high.push_back(num);
            else equal.push_back(num);
        }

        if (k < low.size())
        {
            arr = low;
        }
        else if (k < low.size() + equal.size()) 
        {
            return pivot;
        }
        else
        {
            k = k - (low.size() + equal.size());
            arr = high;
        }
    }
}

int median_select(const vector<int>& data) 
{
    vector<int> copy = data; 
    int n = copy.size();
    return select_kth(copy, n / 2);
}

int median_sorting(vector<int> data) 
{
    sort(data.begin(), data.end());
    return data[data.size() / 2];
}


int main() {
    const int SIZE = 1000001; 
    vector<int> data(SIZE);


    random_num rd;
    mt19937 gen(rd());
    uniform_distribution<> dis(1, 1000000);

    for (int i = 0; i < SIZE; i++) 
    {
        data[i] = dis(gen);
    }

    
    auto start1 = chrono::high_resolution_clock::now();
    int med1 = median_select(data);
    auto end1 = chrono::high_resolution_clock::now();

    auto start2 = chrono::high_resolution_clock::now();
    int med2 = median_sorting(data);
    auto end2 = chrono::high_resolution_clock::now();

    cout << "Median select: " << med1 << endl;
    cout << "Median sorting: " << med2 << endl;

    auto time1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
    auto time2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);

    cout << "Time select: " << time1.count() << " ms\n";
    cout << "Time sorting: " << time2.count() << " ms\n";

    return 0;
}
