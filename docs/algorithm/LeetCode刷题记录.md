# LeetCode 刷题笔记

[toc]

## 基础算法

### 排序

手写快排

```cpp
#include <iostream>

```



### 双指针

[11. 盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/)

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int res = 0;
        while (l < r) {
            res = max(res, (r - l) * (min(height[l], height[r])));
            if (height[l] < height[r]) l ++;
            else r --;
        }
        return res;
    }
};
```



[5. 最长回文子串](https://leetcode.cn/problems/longest-palindromic-substring/) --> 双指针 + 中心扩展算法

```cpp
class Solution {
    pair<int, int> extend(string &s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            -- l;
            ++ r;
        }
        return {l + 1, r - 1};
    }
    
public:
    string longestPalindrome(string s) {
        int res_start = 0, res_end = 0;
        for (int i = 0; i < s.size(); ++ i) {
            auto [left_1, right_1] = extend(s, i, i);
            auto [left_2, right_2] = extend(s, i, i + 1);
            if (right_1 - left_1 > res_end - res_start) {
                res_start = left_1;
                res_end = right_1;
            }
            if (right_2 - left_2 > res_end - res_start) {
                res_start = left_2;
                res_end = right_2;
            }
        }
        return s.substr(res_start, res_end - res_start + 1);
    }
};
```







### 其他题目

[48. 旋转图像](https://leetcode.cn/problems/rotate-image/)：[std::swap](https://en.cppreference.com/w/cpp/algorithm/swap.html)



[394. 字符串解码](https://leetcode.cn/problems/decode-string/) --> 栈



## 数据结构

### 链表

[148. 排序链表](https://leetcode.cn/problems/sort-list/)：链表归并排序、快慢指针

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;

        // find middle node
        ListNode* mid = findMiddle(head);
        ListNode* rightHead = mid->next;  // the head of the right list
        mid->next = nullptr;  // here, we have two lists, the left list and the right list

        // merge sort
        ListNode* left = sortList(head);
        ListNode* right = sortList(rightHead);
        return mergeTwoLists(left, right);
    }

    ListNode* findMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* mergeTwoLists(ListNode* left, ListNode* right) {
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;

        while (left != nullptr && right != nullptr) {
            if (left->val < right->val) {
                curr->next = left;
                left = left->next;
            } else {
                curr->next = right;
                right = right->next;
            }
            curr = curr->next;
        }

        if (left != nullptr) curr->next = left;
        if (right != nullptr) curr->next = right;
        return dummy->next;
    }
};
```



#### 快慢指针

[142. 环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/)

slow 和 fast 指针第一次相遇：
slow 走了 a + b 的长度
fast 走了 a + k * (b + c) + b 的长度，其中 k 表示走过几次完整的环
因为 fast 的速度是 slow 的两倍，所以可以得到：
2 * (a + b) = a + k * (b + c) + b
a + b = k * (b + c)
最后化简的到：
a = (k - 1) * (b + c) + c

所以考虑将 slow 移动到 head 位置，将 fast 保持在第一次相遇位置
当 slow 走 a 的长度时，fast 刚好走完 (k - 1) * (b + c) + c 的长度
slow 和 fast 刚好在环的入口处相遇

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return nullptr;

        ListNode *fast = head;
        ListNode *slow = head;
        do {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == nullptr || fast->next == nullptr) return nullptr;
        } while (fast != slow);

        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
```

### 优先队列

[239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)



### 单调队列

[239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)



### 208. 实现 Trie (前缀树)

链表实现

```cpp
class Trie {
private:
    vector<Trie*> children;
    bool isEnd;
    
    Trie* searchPrefix(string prefix) {
        Trie* node = this;
        for (char ch: prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }
public:
    Trie() : children(26), isEnd(false) {}
    
    void insert(string word) {
        Trie* node = this;
        for (char ch: word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }
    
    bool startsWith(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

数组模拟

[835. Trie字符串统计](https://www.acwing.com/problem/content/837/)

### 哈希表

[128. 最长连续序列](https://leetcode.cn/problems/longest-consecutive-sequence/)

[560. 和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/) --> 前缀和 + 哈希表优化

```cpp
# 前缀和实现
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;
        vector<int> prefix_sum(n + 1, 0);
        for (int i = 1; i <= n; ++ i) {
            prefix_sum[i] = prefix_sum[i - 1] + nums[i - 1];
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 0; j < i; ++ j) {
                if (prefix_sum[i] - prefix_sum[j] == k) ++ count;
            }
        }
        return count;
    }
};
```

```cpp
# 哈希表优化
# 存储以第 i 个元素结尾的数组中前缀和为 prefix_sum - k 的数量
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        int count = 0, prefix_sum = 0;
        mp[0] = 1;
        for (auto& num: nums) {
            prefix_sum += num;
            if (mp.find(prefix_sum - k) != mp.end()) {
                count += mp[prefix_sum - k];
            }
            mp[prefix_sum] ++;
        }
        return count;
    }
};
```







## 搜索与图论

### DFS

[22. 括号生成](https://leetcode.cn/problems/generate-parentheses/)

[494. 目标和](https://leetcode.cn/problems/target-sum/)

```cpp
class Solution {
public:
    // dfs
    int count = 0;
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (auto& num: nums) sum += num;
        if (sum < abs(target)) return 0;
        if ((sum + target) % 2 == 1) return 0;

        dfs(nums, target, 0, 0);
        return count;
    }

    void dfs(vector<int>& nums, int target, int index, int sum) {
        if (index == nums.size()) {
            if (sum == target) ++ count;
            return;
        }
        dfs(nums, target, index + 1, sum + nums[index]);  // 添加 '+'
        dfs(nums, target, index + 1, sum - nums[index]);  // 添加 '-'
    }
};
```



[17. 电话号码的字母组合](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/)

```cpp
# DFS
class Solution {
private:
    map<char, string> dict_;
    vector<string> res_;
public:
    vector<string> letterCombinations(string digits) {
        if (digits == "") return res_;
        dict_ = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
        
        string s;
        dfs(s, 0, digits);
        return res_;
    }

    void dfs(string& s, int index, string& digits) {
        if (index == digits.size()) {
            res_.push_back(s);
            return;
        }
        for (auto& ch: dict_[digits[index]]) {
            s.push_back(ch);
            dfs(s, index + 1, digits);
            s.pop_back();
        }
    }
};
```

```cpp
# BFS
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        map<char, string> dict_ = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
        vector<string> res;
        if (digits.size() == 0) return res;
        queue<string> temp;
        temp.push("");
        for (int i = 0; i < digits.size(); ++ i) {
            while (!temp.empty()) {
                string s = temp.front();
                if (s.size() >= i + 1) break;
                temp.pop();
                for (auto& ch: dict_[digits[i]]) {
                    temp.push(s + ch);
                }
            }
        }
        while (!temp.empty()) {
            res.push_back(temp.front());
            temp.pop();
        }
        return res;
    }
};
```

[46. 全排列](https://leetcode.cn/problems/permutations/)

[39. 组合总和](https://leetcode.cn/problems/combination-sum/) --> DFS + 剪枝

```cpp
// 无剪枝的朴素版本
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> temp;
        dfs(res, candidates, temp, target);
        return res;
    }

    void dfs(vector<vector<int>> &res, vector<int>& candidates, vector<int> &temp, int remain) {
        if (remain == 0) {
            vector<int> temp_temp(temp);
            sort(temp_temp.begin(), temp_temp.end());
            for (auto &a: res) {
                if (a.size() == temp_temp.size() && a == temp_temp) return;
            }
            res.push_back(temp_temp);
            return;
        } else if (remain < 0) return;

        for (int i = 0; i < candidates.size(); ++ i) {
            temp.push_back(candidates[i]);
            dfs(res, candidates, temp, remain - candidates[i]);
            temp.pop_back();
        }
    }
};
```

```cpp
// 剪枝版本，将 candidates 数组从小到大排序，保证每次搜索的时候只搜索当前值或者比当前值更大的值，这样可以保证 temp 是一个升序序列，从而不会出现 [2, 3, 2, 2] 和 [2, 2, 3, 2] 这样冲突的结果。
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end(), std::less<int>());
        vector<vector<int>> res;
        vector<int> temp;
        dfs(res, candidates, temp, target);
        return res;
    }

    void dfs(vector<vector<int>> &res, vector<int>& candidates, vector<int> &temp, int remain) {
        if (remain == 0) {
            res.push_back(temp);
            return;
        } else if (remain < 0) return;

        for (int i = 0; i < candidates.size(); ++ i) {
            if (temp.size() && candidates[i] < temp.back()) continue;
            if (remain - candidates[i] < 0) continue; 
            temp.push_back(candidates[i]);
            dfs(res, candidates, temp, remain - candidates[i]);
            temp.pop_back();
        }
    }
};
```





## 动态规划

[322. 零钱兑换](https://leetcode.cn/problems/coin-change/)

[494. 目标和](https://leetcode.cn/problems/target-sum/)

```cpp
class Solution {
public:
    // dp 解法
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;
        for (auto& i: nums) sum += i;

        if (sum < abs(target)) return 0;  // 全正或全负都无法达到 target
        if ((sum + target) % 2 == 1) return 0;  // 如果 sum + target 为奇数，则无解

        int MAX_WEIGHT = (sum + target) >> 1;  // 背包的最大容量 (承重)

        vector<vector<int>> dp(n + 1, vector<int>(MAX_WEIGHT + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++ i) {
            for (int j = 0; j <= MAX_WEIGHT; ++ j) {
                dp[i][j] = dp[i - 1][j];  // 不装物品i
                if (j < nums[i - 1]) continue;
                dp[i][j] += dp[i - 1][j - nums[i - 1]];  // 装物品i
            }
        }
        return dp[n][MAX_WEIGHT];
    }
};
```

[279. 完全平方数](https://leetcode.cn/problems/perfect-squares/)

[64. 最小路径和](https://leetcode.cn/problems/minimum-path-sum/)

[53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/)

[62. 不同路径](https://leetcode.cn/problems/unique-paths/)

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[1][1] = 1;
        for (int i = 1; i <= m; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                if (i > 1) dp[i][j] += dp[i - 1][j];
                if (j > 1) dp[i][j] += dp[i][j - 1];
            }
        }
        return dp[m][n];
    }
};
```

[72. 编辑距离](https://leetcode.cn/problems/edit-distance/)

[300. 最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)

[309. 买卖股票的最佳时机含冷冻期](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

```cpp
// 用 dp[i] 表示第 i 天结束时的最大累积收益，将购入股票视为负收入，卖出股票视为正收入。
// 因此，用户对于股票存在两种状态，一种是持有股票，一种是未持有股票，分别用 dp[i][0] 和 dp[i][1] 表示。
// 状态转移方程分别为：
// 1. 持有股票：
// 1.1 保持持有股票状态 dp[i][0] = dp[i - 1][0];
// 1.2 购入股票，考虑到冷却期 dp[i][0] = dp[i - 2][0] - prices[i];
// 2. 未持有股票：
// 2.1 保持未持有股票状态 dp[i][1] = dp[i - 1][1];
// 2.2 卖出股票 dp[i][1] = dp[i - 1][0] + prices[i];
// 边界条件：
// 第 0 天，持有股票 dp[0][0] = -prices[0], 未持有股票 dp[0][1] = 0;
// 第 1 天，持有股票 dp[1][0] = max(dp[0][0], - prices[1]), 未持有股票 dp[1][1] = max(dp[0][1], dp[0][0] + prices[1]);
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n < 2) return 0;
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        dp[0][0] = -prices[0];  // 持有股票
        dp[0][1] = 0;  // 未持有股票
        dp[1][0] = max(dp[0][0], - prices[1]);  // 持有股票
        dp[1][1] = max(dp[0][1], prices[1] - prices[0]);  // 未持有股票
        for (int i = 2; i < n; ++ i) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 2][1] - prices[i]);  // 持有股票
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);  // 未持有股票
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};
```



[96. 不同的二叉搜索树](https://leetcode.cn/problems/unique-binary-search-trees/) --> 动态规划 + 数学推导

```cpp
```



[416. 分割等和子集](https://leetcode.cn/problems/partition-equal-subset-sum/) --> 特殊的 0-1 背包

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 一些特判
        int sum = 0, n = nums.size();
        for (auto &num: nums) sum += num;
        if (sum % 2 != 0 || n < 2) return false;

        int target = sum / 2;
        vector<vector<bool>> dp(n, vector<bool>(target + 1));
        for (int i = 0; i < n; ++ i) dp[i][0] = true;
        for (int i = 1; i < n; ++ i) {
            for (int j = 1; j <= target; ++ j) {
                if (j >= nums[i]) dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
                else dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[n - 1][target];
    }
};
```

[198. 打家劫舍](https://leetcode.cn/problems/house-robber/)

[213. 打家劫舍 II](https://leetcode.cn/problems/house-robber-ii/)

[337. 打家劫舍 III](https://leetcode.cn/problems/house-robber-iii/)

[2560. 打家劫舍 IV](https://leetcode.cn/problems/house-robber-iv/)

[树形 DP：打家劫舍III【基础算法精讲 24】](https://www.bilibili.com/video/BV1vu4y1f7dn/?vd_source=f4cc25a44af6631d6f4db023b3bb88e4)



## 贪心

[55. 跳跃游戏](https://leetcode.cn/problems/jump-game/)

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int max_length = 0;
        for (int i = 0; i < n; ++ i) {
            if (max_length >= i) {
                max_length = max(max_length, i + nums[i]);
                if (max_length >= n - 1) return true;
            }
        }
        return false;
    }
};
```









### 类的实现

[146. LRU 缓存](https://leetcode.cn/problems/lru-cache/)：双向链表，LRU 缓存 (Least Recently Used Cache)，unordered_map 和 map 的用法与区别，结构体。

```cpp
class LRUCache {
private:
    int capacity_;
    int size_;
    struct DoubleLinkedNode {
        int key, value;
        DoubleLinkedNode* prev;
        DoubleLinkedNode* next;
        DoubleLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
        DoubleLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
    };
    map<int, DoubleLinkedNode*> cache_;
    DoubleLinkedNode* head_;
    DoubleLinkedNode* tail_;

public:
    LRUCache(int capacity) {
        size_ = 0;
        capacity_ = capacity;
        head_ = new DoubleLinkedNode();
        tail_ = new DoubleLinkedNode();
        head_->next = tail_;
        tail_->prev = head_;
    }
    
    int get(int key) {
        if (!cache_.count(key)) return -1;
        DoubleLinkedNode* node = cache_[key];
        moveNodeToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (!cache_.count(key)) {
            // if key is not exist
            DoubleLinkedNode* node = new DoubleLinkedNode(key, value);
            cache_[key] = node;
            addNodeToHead(node);
            ++ size_;
            if (size_ > capacity_) {
                DoubleLinkedNode* node = tail_->prev;
                removeNode(node);
                cache_.erase(node->key);
                delete node;
                -- size_;
            }
        } else {
            // if key is exist
            DoubleLinkedNode* node = cache_[key];
            node->value = value;
            moveNodeToHead(node);
        }
    }

    void addNodeToHead(DoubleLinkedNode* node) {
        node->prev = head_;
        node->next = head_->next;
        head_->next->prev = node;
        head_->next = node;
    }

    void removeNode(DoubleLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveNodeToHead(DoubleLinkedNode* node) {
        removeNode(node);
        addNodeToHead(node);
    }
};
```





### 并查集

基础教程

[399. 除法求值](https://leetcode.cn/problems/evaluate-division/)

