编程题

第一题

![QQ20250816-192201](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508162027426.png)

第二题

一道字符串交换的问题，给定一个字符串 s1，现在只能交换其中任意两个位置的字符，请问可以得到多少种不同的字符串？ 我的代码如下，但是超内存了，输入字符串的长度大于等于1小于等于10的5次方：

```cpp
#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    std::string s;
    std::cin >> s;
    std::unordered_set<std::string> hash;

    int n = s.size();
    if (n == 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    int flag = 1;
    std::string temp = s;
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            if (flag && temp[i] == temp[j]) {
                flag = 0;
                continue;
            }
            
            // 交换
            char ch = temp[i];
            temp[i] = temp[j];
            temp[j] = ch;
            hash.insert(temp);

            // 还原
            ch = temp[i];
            temp[i] = temp[j];
            temp[j] = ch;
        }
    }

    std::cout << hash.size() << std::endl;

    return 0;
}
```

你这个程序超内存的根本原因是：**你真的在生成所有交换结果的字符串**，而字符串长度最大是 $10^5$，两两交换的数量是 $\frac{n(n-1)}{2}$，数量级可达 $10^{10}$，根本存不下。

其实题目并不需要你枚举字符串，而是要**数学地计算**不同交换能得到的结果数。

---

### 思路推导

1. **交换操作**：选择两个位置 $i, j$，交换 $s[i], s[j]$。
   得到的新串只和 **交换的两个字符是否相同** 有关：

   * 如果相同，交换后还是原串；
   * 如果不同，就会得到一个新的字符串。

2. **总的可能交换对数**：

   $$
   \binom{n}{2} = \frac{n(n-1)}{2}
   $$

3. **无效交换（字符相同）**：
   假设字符 $c$ 在字符串里出现了 $f_c$ 次，那么这些相同字符之间的交换不会产生新串，数量是：

   $$
   \sum_c \binom{f_c}{2}
   $$

4. **因此，不同的新字符串数** 就是：

   $$
   \binom{n}{2} - \sum_c \binom{f_c}{2}
   $$

5. 但别忘了！
   这里是“新字符串数”，题目问的是“不同的字符串数”，是否要包含原串？
   你代码输出的是 `hash.size()`，只统计新串，不含原串，所以公式就是上面那个。
   如果题意是包含原串，再加 1。

---

### 示例验证

* 输入：`abc`

  * $n=3$，总交换数 = 3
  * 各字符频率=1,1,1，$\sum \binom{f}{2} = 0$
  * 新串数 = 3
    实际交换得到：`bac, cba, acb` → 3 ✔️

* 输入：`aaa`

  * $n=3$，总交换数=3
  * 频率 f=3 → $\binom{3}{2}=3$
  * 新串数=0 ✔️

* 输入：`aab`

  * $n=3$，总交换数=3
  * 频率：a=2 → $\binom{2}{2}=1$
  * 新串数=2
    实际交换：`aab` (原串)，`aba`，`baa`，除原串外 2 ✔️

---

### 高效实现（O(n)）

```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string s;
    std::cin >> s;
    int n = s.size();

    std::vector<long long> freq(256, 0); // 统计频率
    for (char c : s) freq[c]++;

    long long total = 1LL * n * (n - 1) / 2;
    long long same = 0;
    for (long long f : freq) {
        same += f * (f - 1) / 2;
    }

    std::cout << total - same << std::endl;
    return 0;
}
```

复杂度：

* 时间：O(n)
* 空间：O(字符集大小)，常数级。
  绝对不会爆内存。

---

要我帮你确认一下**到底要不要包含原串**吗？你代码逻辑是不包含的（因为原串没有被插入哈希表），所以公式不用 `+1`。但有些题会问“所有不同的字符串”，那就要 `+1`。

要不要我帮你改成两个版本（包含原串/不包含原串）的输出？