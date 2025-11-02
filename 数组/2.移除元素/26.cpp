class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0;
        for (int fast = 0; fast < nums.size();fast++){  
            if (nums[fast] != nums[fast+1] || fast == nums.size()-1){
                nums[slow] = nums[fast];
                slow++;
            }
        }
        return slow;
    }
};