// Hashing Algorithms Implementation
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Frequency Counter - O(n) time, O(k) space
unordered_map<int, int> frequencyCount(vector<int>& arr) {
    unordered_map<int, int> freq;
    
    for (int num : arr) {
        freq[num]++;
    }
    
    return freq;
}

// Unique Elements - O(n) time, O(k) space
int countUnique(vector<int>& arr) {
    unordered_set<int> uniqueSet(arr.begin(), arr.end());
    return uniqueSet.size();
}

// Two Sum - O(n) time, O(n) space
vector<int> twoSum(vector<int>& arr, int target) {
    unordered_map<int, int> numMap;
    
    for (int i = 0; i < arr.size(); i++) {
        int complement = target - arr[i];
        
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i};
        }
        
        numMap[arr[i]] = i;
    }
    
    return {};
}
