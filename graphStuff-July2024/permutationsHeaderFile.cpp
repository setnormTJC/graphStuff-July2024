//#pragma once
//
//#include<vector> 
//#include<iostream> 
//
//using std::cout;
//using std::vector;
//
//
//template<typename T>
//void mySwap(vector<T>& things, int firstIndex, int secondIndex)
//{
//    T temp = things[firstIndex];
//
//    things[firstIndex] = things[secondIndex];
//
//    things[secondIndex] = temp;
//}
//
//
//void myShuffle(vector<int>& nums)
//{
//
//    for (int i = 0; i < nums.size(); ++i)
//    {
//        int randomIndex = rand() % nums.size();
//        //should be updated to std::uniform_int_distribution eventually...                    
//        mySwap(nums, i, randomIndex);
//    }
//}
//
//template<typename T>
//void myPartialReverse(vector<T>& things, int startIndex, int endIndex)
//{
//    while (startIndex < endIndex)
//    {
//        mySwap(things, startIndex, endIndex);
//        startIndex++;
//        endIndex--;
//    }
//}
//
///*an in-place algorithm is used for this function */
//void myReverse(vector<int>& nums)
//{
//    for (int i = 0; i < nums.size() / 2; ++i)
//    {
//        int firstIndex = i;
//        int secondIndex = nums.size() - 1 - i;
//        //if nums = {1, 2, 3, 4}
//        //on iter 1: 
//        // swaps 1 and 4
//        // on iter 2 (final): 
//        //swaps 2 and 3 
//
//        //now suppose nums = {1, 2, 3, 4, 5} 
//        //on iter 1, swaps 1 and 5
//        //on iter 2, swaps 2 and 4
//        //iter 2 was final iter since 5/ 2 = 2 (not 2.5) 
//        //element = 3 (middle element) does not need to move since we have: 
//        //{5, 4, 3, 2, 1} 
//        mySwap(nums, firstIndex, secondIndex);
//    }
//}
//
//
///*NOTE: the input vector MUST be sorted (ascending) in order to generate
//all N! permutations of a set of N distinct values*/
////bool myNextPermutation(vector<int>& nums)
////{
////    //suppose input = {1, 2, 3, 4}
////    int k = -1;
////
////    //step 1: find LARGEST index 'k' s.t. nums[k] < nums[k + 1] 
////    for (int i = nums.size() - 2; i >= 0; --i)
////    {
////        if (nums[i] < nums[i + 1])
////        {
////            k = i; //on first iter, k will get set to 2
////            break;
////        }
////    }
////
////    if (k == -1)
////    {
////        //cout << "Sequence is in descending order!\n";
////
////        return false; //no (more) permutations will get found using this algo
////    }
////
////    //step 2: find largest index 'l' s.t. nums[k] < nums [l] 
////    int l = -1;
////    for (int i = nums.size() - 1; i > k; --i)
////    {
////        if (nums[k] < nums[i])
////        {
////            l = i; //in first iter, l gets set to 3 
////            break;
////        }
////    }
////    //step 3: swap nums[k] and nums[l]
////    mySwap(nums, k, l);
////
////    //step 4: reverse the array elements from index (k + 1) to (size - 1)
////    myPartialReverse(nums, k + 1, nums.size() - 1);
////
////}
//
//template <typename T>
//bool myNextPermutation(vector<T>& things)
//{
//    static int runCount = 1;
//    if (runCount == 1)
//    {
//        //cout << "NOTE: this function (myNextPermutation) is only going " <<
//        //    "to generate all permutations if you passed in a list in sorted, ascending order!\n";
//    }
//    runCount++;
//    //suppose input = {1, 2, 3, 4}
//    int k = -1;
//
//    //step 1: find LARGEST index 'k' s.t. nums[k] < nums[k + 1] 
//    for (int i = things.size() - 2; i >= 0; --i)
//    {
//        if (things[i] < things[i + 1])
//        {
//            k = i; //on first iter, k will get set to 2
//            break;
//        }
//    }
//
//    if (k == -1)
//    {
//        //cout << "Sequence is in descending order!\n";
//
//        return false; //no (more) permutations will get found using this algo
//    }
//
//    //step 2: find largest index 'l' s.t. nums[k] < nums [l] 
//    int l = -1;
//    for (int i = things.size() - 1; i > k; --i)
//    {
//        if (things[k] < things[i])
//        {
//            l = i; //in first iter, l gets set to 3 
//            break;
//        }
//    }
//    //step 3: swap nums[k] and nums[l]
//    mySwap(things, k, l);
//
//    //step 4: reverse the array elements from index (k + 1) to (size - 1)
//    myPartialReverse(things, k + 1, things.size() - 1);
//
//}