/*
69. x 的平方根 
简单
相关标签
premium lock icon
相关企业
提示
给你一个非负整数 x ，计算并返回 x 的 算术平方根 。

由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。

 

示例 1：

输入：x = 4
输出：2
示例 2：

输入：x = 8
输出：2
解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
 

提示：

0 <= x <= 231 - 1
*/
class Solution {
public:
    int mySqrt(int x) {
        int left = 0;
        int right = x;
        while (left <= right) {     
            int mid = left + (right - left) / 2;
            if (mid * mid == x) {
                return mid;
            }
            if (mid * mid < x) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return right;
    }
};
/*
Line 8: Char 21: runtime error: signed integer overflow: 1073697799 * 1073697799 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:17:21
*/
class Solution {
public:
    int mySqrt(int x) {
        int left = 0;
        int right = x;
        long long x1 = x;
        while (left <= right) {     
            long long mid = left + (right - left) / 2;
            if (mid * mid == x1) {
                return (int)mid;
            }
            if (mid * mid < x1) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return right;
    }
};

class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = x, ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if ((long long)mid * mid <= x) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
