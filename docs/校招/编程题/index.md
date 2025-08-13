# 算法笔记

## 输入输出

### C语言

首先需要包含头文件`stdio.h`

```c
#include <stdio.h>
```



#### 1. 读入单个数据(数字/字符/字符串)

```c
// 1. 单个读入
int num;
scanf("%d", &num);
char ch;
scanf("%c", &ch);
char str[N];
scanf("%s", str);  // 遇到空行或换行符停止，如果想要读取整行字符串，可以使用gets()
```

因为`scanf()`读入字符的时候也可能会读入空格、换行符等符号，需要注意，可以使用`getchar()`来读入用于间隔的符号。`scanf()`的返回值是成功读取的项数，如果遇到文件结束符则返回的EOF。



#### 2. 读入多个数据(数组/字符串/字符串数组)

```c
int a[N], n;
scanf("%d", &n);  // 数组长度
for (int i = 0; i < n; ++ i) scanf("%d", &a[i]);
```

读取一行整数(未知数量)

```c
#include <stdio.h>
#define MAX_SIZE 1000

int main() {
    int arr[MAX_SIZE];
    int count = 0;
    char c;
    
    // 方式1：使用字符判断
    while (1) {
        scanf("%d%c", &arr[count], &c);
        count++;
        if (c == '\n') break;
    }
    
    // 方式2：使用fgets+sscanf（更健壮）
    char buffer[5000];
    fgets(buffer, sizeof(buffer), stdin);
    
    char *p = buffer;
    int offset;
    while (sscanf(p, "%d%n", &arr[count], &offset) == 1) {
        count++;
        p += offset;
    }
    
    return 0;
}
```



#### 3. 不定数量的读入

有的时候一个样例有多次输入，每次输入需要计算一次，所以需要用while一直读，直到读到文件停止符号或约定的停止符号。

```cpp
#include <stdio.h>

int main() {
    int a, b;
    // 方式1：检查返回值
    while (scanf("%d %d", &a, &b) == 2) {
        printf("%d\n", a + b);
    }
    
    // 方式2：检查EOF
    while (scanf("%d %d", &a, &b) != EOF) {
        printf("%d\n", a + b);
    }
    
    return 0;
}
```



#### 4. 读取字符串

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[100];
    // 读取不带空格的字符串
    scanf("%s", str1);
    printf("String: %s\n", str1);
    
    // 读取带空格的字符串
    char str2[100];
    getchar(); // 吸收前一个换行符
    fgets(str2, sizeof(str2), stdin);
    
    // 去除末尾的换行符
    if (str2[strlen(str2) - 1] == '\n') {
        str2[strlen(str2) - 1] = '\0';
    }
    printf("Full line: %s\n", str2);
    
    return 0;
}
```

#### 5. 特殊格式输入

```c
#include <stdio.h>

int main() {
    // 格式：10:30:45
    int hour, minute, second;
    scanf("%d:%d:%d", &hour, &minute, &second);
    printf("Time: %02d:%02d:%02d\n", hour, minute, second);
    
    // 格式：1,2,3,4
    int nums[10];
    int count = 0;
    char sep;
    do {
        scanf("%d%c", &nums[count], &sep);
        count++;
    } while (sep == ',');
    
    return 0;
}
```



### CPP

#### 1. 基本输入输出模式

```cpp
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    std::cout << "Read n: " << n << std::endl;
    
    int a, b;
    std::cin >> a >> b;
    std::cout << "a=" << a << ", b=" << b << std::endl;
    
    return 0;
}
```

#### 2. 多组测试数据（未知组数）

```cpp
#include <iostream>

int main() {    
    int a, b;
    while (std::cin >> a >> b) {
        std::cout << a + b << '\n';
    }
    
    return 0;
}
```

#### 3. 读取一行整数(未知数量)

```cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

int main() {
    std::string line;
    getline(std::cin, line);
    
    std::stringstream ss(line);
    std::vector<int> nums;
    int num;
    
    while (ss >> num) {
        nums.push_back(num);
    }
    
    // 输出
    for (int x : nums) {
        std::cout << x << " ";
    }
    std::cout << '\n';
    
    return 0;
}
```

#### 4. 读取字符串

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // 读取不带空格的字符串
    string word;
    cin >> word;
    cout << "Word: " << word << endl;
    
    // 读取带空格的整行
    cin.ignore(); // 忽略之前的换行符，也可以用getchar()读入前面的空格或者换行符
    string fullLine;
    getline(cin, fullLine);
    cout << "Full line: " << fullLine << endl;
    
    return 0;
}
```

#### 5. 格式化输出

格式化输出还是推荐使用`printf()`

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi = 3.141592653589793;
    
    // 设置精度
    cout << fixed << setprecision(2) << pi << endl; // 输出 3.14
    
    // 设置宽度和对齐
    cout << setw(10) << "Hello" << setw(10) << "World" << endl;
    
    // 填充字符
    cout << setfill('*') << setw(10) << 123 << endl; // 输出 *******123
    
    // 十六进制输出
    cout << hex << 255 << endl; // 输出 ff
    
    return 0;
}
```



### 常用模板

C模板

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000

int main() {
    // 读取多组测试数据
    int n;
    while (scanf("%d", &n) != EOF) {
        // 读取n个整数
        int arr[MAX_N];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        // 输出结果
        for (int i = 0; i < n; i++) {
            printf("%d%c", arr[i], " \n"[i == n-1]);
        }
    }
    
    return 0;
}
```

CPP模板

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        
        // 输出结果
        for (int i = 0; i < n; i++) {
            cout << nums[i] << (i == n-1 ? '\n' : ' ');
        }
    }
    
    return 0;
}
```



:warning:注意输出的行末是否允许空格或空行。



### 重定向标准输入输出

将输入重定向到 `in.txt` 文件中，这样就不用在调试的时候手动输入数据：

```cpp
#include <iostream>

int main() {
    freopen("in.txt", "rt", stdin);
    freopen("out.txt", "wt", stdout);
    
    return 0;
}
```

也可以进一步使用预处理指令

```cpp
#include <iostream>

int main() {
#ifdef ONLINE_JUDGE
#else
    freopen("in.txt", "rt", stdin);
#endif
    
    return 0;
}
```



## 基础算法

### 排序

#### `std::sort`

```cpp
// 默认排序
std::sort(nums.begin(), nums.end());

// 使用 std::greater<T>() 降序排序或使用 std::less<T>()
std::sort(nums.begin(), nums.end(), std::greator<int>());
std::sort(nums.begin(), nums.end(), std::less<int>());

// 使用 lambda 表达式
std::sort(nums.begin(), nums.end(), []() {
   return a > b; 
});
```

[Sorting](https://hackingcpp.com/cpp/std/algorithms.html)



#### 整数快排

C++写法

```cpp
#include <iostream>
#include <vector>

void quick_sort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, q = arr[(l + r) / 2];
    while (i < j) {
        do i ++; while (arr[i] < q);
        do j --; while (arr[j] > q);
        if (i < j) std::swap(arr[i], arr[j]);
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}
int main() {
    std::vector<int> nums = {1, 5, 3, 7, 9, 8, 2, 6, 4, 0};
    for (auto num:nums) std::cout << num << " ";
    std::cout << "\n";
    quick_sort(nums, 0, nums.size() - 1);
    for (auto num:nums) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}
```

C写法

```c
#include<stdio.h>
#define N 20

void quick_sort(int q[], int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[(l + r) / 2];
    while (i < j) {
        do i ++; while (i <= r && q[i] < x);
        do j --; while (j >= l && q[j] > x);
        if (i < j) {
            int temp = q[i];
            q[i] = q[j];
            q[j] = temp;
        }
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main() {
    int n = 10;
    int nums[N] = {1, 5, 3, 7, 9, 8, 2, 6, 4, 0};
    for (int i = 0; i < n; ++ i) printf("%d ", nums[i]);
    printf("\n");
    quick_sort(nums, 0, n - 1);
    for (int i = 0; i < n; ++ i) printf("%d ", nums[i]);
    printf("\n");
    
    return 0;
}
```

y总：[AcWing 785. 快速排序](https://www.acwing.com/activity/content/code/content/39784/)





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



### 区间合并

[803. 区间合并](https://www.acwing.com/problem/content/description/805/)

将所有区间按照左边界升序排列，然后从前往后遍历，判断区间是否重合，区间合并的时候，右边界为两个区间右边界的最大值。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::vector<std::pair<int, int>> intervals;
    std::cin >> n;
    for (int i = 0; i < n; ++ i) {
        int a, b;
        std::cin >> a >> b;
        intervals.push_back({a, b});
    }
    std::sort(intervals.begin(), intervals.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
        return a.first < b.first;
    });
    int cnt = 1, pre_right = intervals[0].second;
    for (auto interval : intervals) {
        if (pre_right < interval.first) {
            ++ cnt;
        }
        pre_right = std::max(pre_right, interval.second);
    }
    std::cout << cnt << std::endl;

    return 0;
}
```



## 数据结构

### 指针



### 链表

#### 链表基础



#### 例题

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

### KMP



### 优先队列

[239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)

使用大根堆来解决，构建 `(index, value)` 的 pair，每次滑动窗口向后滑动的时候判断堆顶的元素是否在窗口内，若在窗口内则符合条件，若不存在，则需要从堆中移出直到堆顶的元素在窗口内。

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pair<int, int>> max_heap;
        for (int i = 0; i < k; ++ i) max_heap.push({nums[i], i});

        vector<int> res;
        res.push_back(max_heap.top().first);
        for (int i = k; i < n; ++ i) {
            max_heap.push({nums[i], i});
            while (max_heap.top().second <= i - k) max_heap.pop();
            res.push_back(max_heap.top().first);
        }
        return res;
    }
};
```



#### 大根堆(Max-Heap)

直接声明：

```cpp
std::priority_queue<int, std::vector<int>, std::less<int>> max_heap;
```

或者使用 `std::make_heap()` 从已有数据中建堆：

```cpp
std::vector<int> max_heap;  // 已有数据
std::make_heap(max_heap.begin(), max_heap.end(), std::less<int>());  // 构建大根堆

// 删除元素
std::pop_heap(max_heap.begin(), max_heap.end(), std::less<int>());  // 将堆顶元素移动到 vector 的末尾
max_heap.pop_back();  // 然后使用 pop_back() 删除该元素

// 添加元素
max_heap.push_back(9);  // 将新元素放到 vector 的末尾
std::push_heap(max_heap.begin(), max_heap.end(), std::less<int>());  // 使用 push_heap() 将元素放到合适的位置
```



#### 小根堆(Min-Heap)

直接声明：

```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
```

或者直接使用 `std::make_heap()` 从已有数据中建堆：

```cpp
std::vector<int> min_heap;  // 已有数据
std::make_heap(min_heap.begin(), min_heap.end(), std::greater<int>());  // 构建小根堆

// 删除元素
std::pop_heap(min_heap.begin(), min_heap.end(), std::greater<int>());  // 将堆顶元素移动到 vector 的末尾
min_heap.pop_back();  // 然后使用 pop_back() 删除该元素

// 添加元素
min_heap.push_back(9);  // 将新元素放到 vector 的末尾
std::push_heap(min_heap.begin(), min_heap.end(), std::greater<int>());  // 使用 push_heap() 将元素放到合适的位置
```

[Standard Library Heap Operations](https://hackingcpp.com/cpp/std/algorithms/heap_operations.html)



#### 模拟堆

[839. 模拟堆](https://www.acwing.com/problem/content/description/841/)

使用惰性删除方法，将 "D k" 操作中标明的第 k 个插入的元素标示为删除，即从 dict 中删除。

关键语句：
```cpp
while (!dict.count(min_heap.top().second) || dict[min_heap.top().second] != min_heap.top().first) min_heap.pop();
```

其中第一项，若堆顶元素 (value, index) pair 在 min_heap 中存在，但是在 dict 中不存在，则表明该元素已经被删除了，现在需要从 min_heap 的顶部删除所有不存在 dict 中的元素，直到堆顶的元素在 dict 中存在。
其中第二项，因为 dict 中始终保持最新的 (value, index) pair，若堆顶元素中 index 对应的 value 不等于该 index 在 dict 中对应的 value，则表示这个 value 已经被修改过了不是最新的，需要删除该元素，直到堆顶元素中 index 对应的 value 与在 index 中对应的 value 相同。
其实还应该加上 min_heap 的判空，不过从题目分析可以分析出 min_heap 不为空。

```cpp
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <unordered_map>

int main() {
    int n, index = 1, k, x;
    std::cin >> n;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> min_heap;
    std::unordered_map<int, int> dict;
    while (n --) {
        std::string option;
        std::cin >> option;
        if (option == "I") {
            int x;
            std::cin >> x;
            min_heap.push({x, index});
            dict[index ++] = x;
        } else if (option == "PM") {
            while (!dict.count(min_heap.top().second) || dict[min_heap.top().second] != min_heap.top().first) min_heap.pop();
            std::cout << min_heap.top().first << "\n";
        } else if (option == "DM") {
            while (!dict.count(min_heap.top().second) || dict[min_heap.top().second] != min_heap.top().first) min_heap.pop();
            dict.erase(min_heap.top().second);
            min_heap.pop();
        } else if (option == "D") {
            std::cin >> k;
            dict.erase(k);
        } else if (option == "C") {
            std::cin >> k >> x;
            dict[k] = x;
            min_heap.push({x, k});
        }
    }

    return 0;
}
```



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

前缀和实现：

```cpp
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

哈希表优化，存储以第 i 个元素结尾的数组中前缀和为 prefix_sum - k 的数量：

```cpp
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



### 并查集

基础教程

[合并集合](https://www.acwing.com/problem/content/description/838/)

初始化的时候，所有节点的父母节点是其自身，每次在查找当前节点的祖先结点的时候做路径压缩

```cpp
#include <iostream>
int parent[100050];  // parent[index] 存储当前节点 index 的父结点

int find(int index) {
    if (parent[index] != index)
        parent[index] = find(parent[index]);
    return parent[index];
}

int main() {
    int n, m, a, b;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++ i) parent[i] = i;
    char ch;
    while (m --) {
        getchar();
        scanf("%c %d %d", &ch, &a, &b);
        if (ch == 'M') {
            parent[find(a)] = parent[find(b)];
        } else if (ch == 'Q') {
            if (find(a) == find(b)) std::cout << "Yes\n";
            else std::cout << "No\n";
        }
    }

    return 0;
}
```



[399. 除法求值](https://leetcode.cn/problems/evaluate-division/)

从示例可知：

```
输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
```

其中，a = 2b，b = 3c，

所以，有权重的并查集：

```cpp
class Solution {
private:
    vector<int> parents;
    vector<double> weights;
    int count = 0;
    unordered_map<string, int> dict;

    int find(int index) {
        if (parents[index] != index) {
            int parent = parents[index];
            parents[index] = find(parent);
            weights[index] = weights[index] * weights[parent];
        }
        return parents[index];
    }

    void merge(int x, int y, double value) {
        int parent_x = find(x);
        int parent_y = find(y);
        if (parent_x == parent_y) return;

        parents[parent_x] = parent_y;
        weights[parent_x] = weights[y] * value / weights[x];
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        parents.resize(2 * equations.size());
        weights.resize(2 * equations.size());
        
        // init
        for (int i = 0; i < parents.size(); ++ i) parents[i] = i, weights[i] = 1.0;

        // build
        for (int i = 0; i < equations.size(); ++ i) {
            string a = equations[i][0], b = equations[i][1];
            double value = values[i];

            if (!dict.count(a)) dict[a] = count ++;
            if (!dict.count(b)) dict[b] = count ++;

            int id_a = dict[a], id_b = dict[b];
            merge(id_a, id_b, value);
        }

        // query
        vector<double> res;
        for (int i = 0; i < queries.size(); ++ i) {
            string c = queries[i][0], d = queries[i][1];
            if (!dict.count(c) || !dict.count(d)) {
                res.push_back(-1.0);
                continue;
            }

            int id_c = dict[c], id_d = dict[d];
            int parent_c = find(id_c), parent_d = find(id_d);

            if (parent_c != parent_d) res.push_back(-1.0);
            else res.push_back(weights[id_c] / weights[id_d]);
        }

        return res;
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



https://www.nowcoder.com/share/jump/null

https://www.nowcoder.com/share/jump/1486178631754138659829



## 类的实现

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







