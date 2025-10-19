class Solution {
public:
    vector<int> spiralArray(vector<vector<int>>& array) {
        
        if (array.empty() || array[0].empty()) {
            return {}; // 如果数组为空，直接返回空结果
        }

        int m = array.size();
        int startx = 0, starty = 0; // 定义每循环一个圈的起始位置
        int n = array[0].size();
        vector<int> res(m*n); // 使用vector定义一个一维数组
        int loop = n / 2; // 需要循环的圈数
        int mid = n / 2; // 矩阵中间的位置，例如：n为3， 中间的位置就是(1，1)，n为5，中间位置为(2, 2)
        int num = 0; // 用来给矩阵中每一个空格赋值
        int offset = 1; // 需要控制每一条边遍历的长度，每次循环右边界收缩一位
        int i,j;
        while (loop --) {
            i = startx;
            j = starty;

            // 下面开始的四个for就是模拟转了一圈
            // 模拟填充上行从左到右(左闭右开)
            for (j; j < n - offset; j++) {
                res[num++]=array[i][j] ;
            }
            // 模拟填充右列从上到下(左闭右开)
            for (i; i < n - offset; i++) {
                res[num++]=array[i][j] ;
            }
            // 模拟填充下行从右到左(左闭右开)
            for (; j > starty; j--) {
                res[num++]=array[i][j] ;
            }
            // 模拟填充左列从下到上(左闭右开)
            for (; i > startx; i--) {
                res[num++]=array[i][j] ;
            }

            // 第二圈开始的时候，起始位置要各自加1， 例如：第一圈起始位置是(0, 0)，第二圈起始位置是(1, 1)
            startx++;
            starty++;

            // offset 控制每一圈里每一条边遍历的长度
            offset += 1;
        }

        // 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
        if (n % 2) {
            res[num]=array[mid][mid];
        }
        return res;

    }
};

/*
1 2 3
8 9 4
7 6 5

1 2 3 4 5 6 7 8 9
示例 1：

输入：array = [[1,2,3],[8,9,4],[7,6,5]]
输出：[1,2,3,4,5,6,7,8,9]
示例 2：

输入：array  = [[1,2,3,4],[12,13,14,5],[11,16,15,6],[10,9,8,7]]
输出：[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
*/
class Solution {
public:
    vector<int> spiralArray(vector<vector<int>>& array) {
        // --- 关键修复1：检查输入是否为空 ---
        if (array.empty() || array[0].empty()) {
            return {};
        }

        int m = array.size();    // 行数
        int n = array[0].size(); // 列数
        vector<int> res;
        res.reserve(m * n); // 预分配空间，提高效率

        // --- 关键修复2：初始化四个边界 ---
        int top = 0, bottom = m - 1;     // 上下边界（行）
        int left = 0, right = n - 1;     // 左右边界（列）

        // --- 关键修复3：使用边界是否交错作为循环终止条件 ---
        while (top <= bottom && left <= right) {
            // 1. 从左到右遍历上边界
            for (int j = left; j <= right; j++) {
                res.push_back(array[top][j]);
            }
            top++; // 上边界下移

            // 2. 从上到下遍历右边界 (确保还有行可以遍历)
            for (int i = top; i <= bottom; i++) {
                res.push_back(array[i][right]);
            }
            right--; // 右边界左移

            // 3. 从右到左遍历下边界 (确保还有行可以遍历，防止单行情况下的重复)
            if (top <= bottom) {
                for (int j = right; j >= left; j--) {
                    res.push_back(array[bottom][j]);
                }
                bottom--; // 下边界上移
            }

            // 4. 从下到上遍历左边界 (确保还有列可以遍历，防止单列情况下的重复)
            if (left <= right) {
                for (int i = bottom; i >= top; i--) {
                    res.push_back(array[i][left]);
                }
                left++; // 左边界右移
            }
        }
        return res;
    }
};