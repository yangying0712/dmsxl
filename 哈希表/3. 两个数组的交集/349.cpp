#include<vector>
#include<unordered_set>
using namespace std;
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        int hash[1002] = {0};
        vector<int> res;
        for(int i=0;i<nums1.size();i++){
            hash[nums1[i]]=1;
        }
        for(int i=0;i<nums2.size();i++){
            if(hash[nums2[i]]==1){
                res.push_back(nums2[i]);
                hash[nums2[i]]=0; // 防止重复
            }
        }
        return res;
    }
};
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
        int hash[1005] = {0}; // 默认数值为0
        for (int num : nums1) { // nums1中出现的字母在hash数组中做记录
            hash[num] = 1;
        }
        for (int num : nums2) { // nums2中出现话，result记录
            if (hash[num] == 1) {
                result_set.insert(num);
            }
        }
        return vector<int>(result_set.begin(), result_set.end());
    }
};

#include<vector>
using namespace std;
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        unordered_set<int> set1(nums1.begin(),nums1.end());
        for(int i=0;i<nums2.size();i++){
            if(set1.find(nums2[i])!=set1.end()){
                res.push_back(nums2[i]);
                set1.erase(nums2[i]); // 防止重复   
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
        unordered_set<int> nums_set(nums1.begin(), nums1.end());
        for (int num : nums2) {
            // 发现nums2的元素 在nums_set里又出现过
            if (nums_set.find(num) != nums_set.end()) {
                result_set.insert(num);
            }
        }
        return vector<int>(result_set.begin(), result_set.end());
    }
};