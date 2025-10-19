class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        if (n < 3) return n;
        int left = 0, right = 0;
        unordered_map<int, int> countMap; // 记录每种水果的数量
        int maxLength = 0; // 记录最大长度

        while (right < n) {
            countMap[fruits[right]]++;
            right++;

            // 当种类超过2时，移动左指针
            while (countMap.size() > 2) {
                countMap[fruits[left]]--;
                if (countMap[fruits[left]] == 0) {
                    countMap.erase(fruits[left]);
                }
                left++;
            }

            // 更新最大长度
            maxLength = max(maxLength, right - left);
        }

        return maxLength;   
    }
};

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int result = __INT32_MAX__;
        int left = 0;
        int right = 0;
        //int count = 0;
        unordered_map<int, int> countMap; //记录每种水果的数量
        for ( right = 0; right < nums.size(); right++) {
            countMap[fruits[right]]++; // 记录窗口内元素个数
            while (countMap.size() > 2) { // 当种类超过2时，移动左指针
                countMap[fruits[left]]--;
                if (countMap[fruits[left]] == 0) {
                    countMap.erase(fruits[left]);
                }
                left++;
    }
};

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> countMap; // 记录每种水果的数量
        int maxLength = 0; // 记录最大长度
        int subLength = 0; // 滑动窗口的长度
        int left=0;
        for (int right = 0; right < nums.size(); right++) {
            countMap[fruits[right]]++;
            right++;
            while (countMap.size() > 2) { // 当种类超过2时，移动左指针
                countMap[fruits[left]]--;
                if (countMap[fruits[left]] == 0) {
                    countMap.erase(fruits[left]);
                }
                subLength= (right - left+1); // 取子序列的长度
                maxLength = maxLength > subLength ? maxLength : subLength;
                left++;
            }
        }
        // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
        return maxLength;
    }
};