#include <vector>
using namespace std;
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n=nums.size();
        int left=0;
        int right=n-1;
        vector<int> targets={};
        if (n == 0) return {-1, -1};  // 处理空数组的情况
        if (nums[0]==nums[n-1] && nums[0]==target) return {0, n-1};
        while(left<=right){
            int middle = left + ((right - left) / 2);  // 防止整数溢出
            if(nums[middle]>target)
                right=middle-1;
            else if(nums[middle]<target)
                left=middle+1;
            else{
                if (nums[0]== target){
                    targets.push_back(0);
                }
                else{
                    while(nums[middle]==target){
                        middle--;
                    }
                    targets.push_back(middle+1);
                }
                int i=0;
                if(nums[n-1]==target){
                    targets.push_back(n-1);
                }else{
                    for(i=0;nums[middle+i]<=target;i++){
                    }
                    targets.push_back(middle+i-1);
                }
                return targets;
            }
                
        }
        return {-1, -1};
    }
};