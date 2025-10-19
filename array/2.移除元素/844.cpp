/*
844. 比较含退格的字符串
简单
相关标签
premium lock icon
相关企业
给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回 true 。# 代表退格字符。

注意：如果对空文本输入退格字符，文本继续为空。

 

示例 1：

输入：s = "ab#c", t = "ad#c"
输出：true
解释：s 和 t 都会变成 "ac"。
示例 2：

输入：s = "ab##", t = "c#d#"
输出：true
解释：s 和 t 都会变成 ""。
示例 3：

输入：s = "a#c", t = "b"
输出：false
解释：s 会变成 "c"，但 t 仍然是 "b"。
 

提示：

1 <= s.length, t.length <= 200
s 和 t 只含有小写字母以及字符 '#'
 

进阶：

你可以用 O(n) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？
*/
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        removeElement(s);
        removeElement(t);
        return s == t;
    }
    void removeElement(string& nums) {
        int slow = 0;
        int flag = 0;
        for (int fast = 0; fast < nums.size();fast++){
            if (nums[fast+1]!= '#'&&nums[fast]!= '#'&&flag==0){
                nums[slow] = nums[fast];
                slow++;
            }else{
                flag = 1;
            }
        }
    }
};

class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int len_s = removeBackspaces(s); // 处理s并返回有效长度
        int len_t = removeBackspaces(t); // 处理t并返回有效长度
        // 比较有效部分
        if (len_s != len_t) return false;
        return s.substr(0, len_s) == t.substr(0, len_t);
    }

    int removeBackspaces(string& str) {
        int slow = 0; // 慢指针指向下一个有效字符的位置
        for (int fast = 0; fast < str.size(); fast++) {
            if (str[fast] != '#') {
                // 普通字符：保留并移动慢指针
                str[slow] = str[fast];
                slow++;
            } else {
                // 退格符：删除前一个字符（慢指针回退）
                if (slow > 0) {
                    slow--;
                }
            }
        }
        return slow; // 返回有效长度
    }
};