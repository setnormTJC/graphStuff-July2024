// Playing with std_next_permutation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector> 
#include<algorithm> 
#include <set>

using std::cout; 
using std::vector; 

void printVec(const vector<int>& nums)
{
    for (auto& num : nums)
    {
        cout << num << " ";
    }
    cout << "\n";
}

int myFactorial(int N)
{
    while (N > 0)
    {
        return N * myFactorial(N - 1);
    }
}

void mySwap(vector<int>& nums, int firstIndex, int secondIndex)
{
    int temp = nums[firstIndex]; 

    nums[firstIndex] = nums[secondIndex]; 

    nums[secondIndex] = temp; 
}

void myShuffle(vector<int>& nums)
{

    for (int i = 0; i < nums.size(); ++i)
    {
        int randomIndex = rand() % nums.size();
        mySwap(nums, i, randomIndex);
    }
}

void printAllUNIQUEPermutations(vector<int>& nums)
{
    //int permutationCount = 0; 
    std::set<vector<int> > permutations;

    while (permutations.size() < myFactorial(nums.size()))
    {
        myShuffle(nums); //dumb way to do this ...
        permutations.insert(nums);
    }

    cout << "List of permutations of input vector:\n";

    for (auto& permutation : permutations)
    {
        printVec(permutation); 
    }

    cout << "Count (N!): " << nums.size() << "! = " << permutations.size() << "\n";
}

int main()
{
    srand(time(0)); 

    //cout << myFactorial(5) << "\n";
    //cout << myFactorial(6) << "\n";
    vector<int> nums = { 1, 2, 3, 4 };


    printAllUNIQUEPermutations(nums); 

    //int permutationCount = 0; 
    //while (std::next_permutation(nums.begin(), nums.end()))
    //{
    //    permutationCount++; 
    //}

    //cout << "total permuations: " << permutationCount << "\n";



    //std::cout << "Hello World!\n";
}
