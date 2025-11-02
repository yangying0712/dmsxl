class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() ; i++)
        {
            if(nums[i] > 0) {
                return result;
            } //因为已经排序好，当前数字大于0，则三数之和一定大于0，所以结束循环
        
            if(i > 0 && nums[i] == nums[i-1]) {
                continue;
            } //去重
            
            int left = i + 1, right = nums.size() - 1;
            while(left < right) {
                if (nums[i] + nums[left] + nums[right] > 0) right--;
                else if (nums[i] + nums[left] + nums[right] < 0) left++;
                else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while(left < right && nums[left] == nums[left + 1]) left++; //去重
                    while(left < right && nums[right] == nums[right - 1]) right--; //去重
                    left++;
                    right--;
                }
                
            }
        }
        return result;
    }
};