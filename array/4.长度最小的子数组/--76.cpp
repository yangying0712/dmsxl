/*
76. 最小覆盖子串
困难
相关标签
premium lock icon
相关企业
提示
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

 

注意：

对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
如果 s 中存在这样的子串，我们保证它是唯一的答案。
 

示例 1：

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
示例 2：

输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。
示例 3:

输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。
 

提示：

m == s.length
n == t.length
1 <= m, n <= 105
s 和 t 由英文字母组成
 

进阶：你能设计一个在 o(m+n) 时间内解决此问题的算法吗？
*/
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> tMap;
        for (char c : t) {
            tMap[c]++;
        }
        int required = tMap.size();
        int minLength = INT_MAX;
        int start = 0;
        int left = 0;
        int right = 0;
        while (right < s.size()) {
            char c = s[right];
            if (tMap.find(c) != tMap.end()) {
                tMap[c]--;
                if (tMap[c] == 0) {
                    required--;
                }
            }
            right++;
            while (required == 0) {
                if (right - left < minLength) {
                    minLength = right - left;
                    start = left;
                }
                char leftChar = s[left];
                if (tMap.find(leftChar) != tMap.end()) {
                    tMap[leftChar]++;
                    if (tMap[leftChar] > 0) {
                        required++;
                    }
                }
                left++;
            }
        }
        return minLength == INT_MAX ? "" : s.substr(start, minLength);
    }
};