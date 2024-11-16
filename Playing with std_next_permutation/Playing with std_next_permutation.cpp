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
    if (N > 0)
    {
        return 1; 
    }

    return N * myFactorial(N - 1);

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

void myPartialReverse(vector<int>& nums, int startIndex, int endIndex)
{
    while (startIndex < endIndex)
    {
        mySwap(nums, startIndex, endIndex); 
        startIndex++; 
        endIndex--; 
    }
}

/*an in-place algorithm is used for this function */
void myReverse(vector<int>& nums)
{
    for (int i = 0; i < nums.size()/2; ++i)
    {
        int firstIndex = i; 
        int secondIndex = nums.size() - 1 - i; 
        //if nums = {1, 2, 3, 4}
        //on iter 1: 
        // swaps 1 and 4
        // on iter 2 (final): 
        //swaps 2 and 3 

        //now suppose nums = {1, 2, 3, 4, 5} 
        //on iter 1, swaps 1 and 5
        //on iter 2, swaps 2 and 4
        //iter 2 was final iter since 5/ 2 = 2 (not 2.5) 
        //element = 3 (middle element) does not need to move since we have: 
        //{5, 4, 3, 2, 1} 
        mySwap(nums, firstIndex, secondIndex);
    }
}

/*NOTE: the input vector MUST be sorted (ascending) in order to generate
all N! permutations of a set of N distinct values*/
bool myNextPermutation(vector<int>& nums)
{
    //suppose input = {1, 2, 3, 4}
    int k = -1;

    //step 1: find LARGEST index 'k' s.t. nums[k] < nums[k + 1] 
    for (int i = nums.size() - 2; i >= 0; --i)
    {
        if (nums[i] < nums[i + 1])
        {
            k = i; //on first iter, k will get set to 2
            break;
        }
    }

    if (k == -1)
    {
        //cout << "Sequence is in descending order!\n";

        return false; //no (more) permutations will get found using this algo
    }

    //step 2: find largest index 'l' s.t. nums[k] < nums [l] 
    int l = -1;
    for (int i = nums.size() - 1; i > k; --i)
    {
        if (nums[k] < nums[i])
        {
            l = i; //in first iter, l gets set to 3 
            break;
        }
    }
    //step 3: swap nums[k] and nums[l]
    mySwap(nums, k, l);

    //step 4: reverse the array elements from index (k + 1) to (size - 1)
    myPartialReverse(nums, k + 1, nums.size() - 1);

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
    vector<int> nums = { 1,  2, 3, 4 };

    int permutationCount = 1; 
    cout << "Initial array:\n";
    printVec(nums); 

    while (myNextPermutation(nums))
    {
        permutationCount++; 
        cout << "Permutation #" << permutationCount << " ";
        printVec(nums); 
        //cout << "}"
    }
    //printAllUNIQUEPermutations(nums); 

    //int permutationCount = 0; 
    //while (std::next_permutation(nums.begin(), nums.end()))
    //{
    //    permutationCount++; 
    //}

    //cout << "total permuations: " << permutationCount << "\n";



    //std::cout << "Hello World!\n";
}
