# STL

[toc]

### 1. 什么是STL？

C++的STL（Standard Template Library，标准模板库）是C++编程语言中的一个功能强大且广泛使用的库，它提供了一系列通用的模板类和函数，可以帮助程序员更高效地处理各种数据结构和算法问题。STL主要包含以下几个组件：

-   **容器（Containers）**：容器是用来存储和管理数据的数据结构，例如向量（vector）、列表（list）、队列（queue）、栈（stack）、集合（set）和映射（map）等。
-   **迭代器（Iterators）**：迭代器是一种类似于指针的对象，可以用来遍历容器中的元素。迭代器为容器中的数据提供了统一的访问接口，使得算法可以与容器无缝地协同工作。
-   **算法（Algorithms）**：STL提供了许多通用的算法，如排序、查找、合并等，这些算法可以直接应用于容器和迭代器。
-   **函数对象（Function Objects）**：函数对象是实现了函数调用操作符（operator()）的类的对象。它们通常用作算法的自定义操作，使得算法可以具有更高的灵活性和可扩展性。函数对象有时被称为“仿函数”（functors）。STL还提供了一些预定义的函数对象，例如less、greater、plus等，它们可以用于算法中的比较和运算操作。
-   **适配器（Adapters）**：适配器是一种特殊的容器或函数对象，它们可以修改或扩展其他容器或函数对象的行为。例如，队列（queue）和栈（stack）就是容器适配器，它们分别基于deque和vector容器实现。函数适配器包括bind、mem_fn等，可以用来组合和修改函数对象。
-   **分配器（Allocators）**：分配器是一种管理内存分配和释放的机制，它们可以用于自定义容器的内存管理策略。STL中默认使用的分配器是std::allocator，但用户可以根据需要提供自定义的分配器。

### 2. vector与list的区别与应用？

vector和list是C++ STL中两种常用的序列容器，它们用于存储和管理线性数据，但在底层实现、性能特点和适用场景上有一些区别。

**底层实现**

-   vector：vector是基于动态数组实现的，内存空间是连续的。当vector需要扩容时，它会分配一块更大的内存空间，将原有的数据拷贝到新的空间，并释放原有的内存。
-   list：list是基于双向链表实现的，内存空间是非连续的。每个元素都是一个节点，节点之间通过指针相互连接。

**性能**

-   vector
    -   访问元素：由于内存连续，vector支持随机访问，可以使用下标直接访问任意元素，时间复杂度为O(1)。
    -   插入和删除：在vector的末尾插入和删除元素非常高效，时间复杂度为O(1)；但在中间或开头插入和删除元素需要移动后面的元素，时间复杂度为O(n)。
    -   内存使用：vector可能会预留一些额外的内存空间用于扩容，因此在某些情况下可能会浪费一些内存。但由于内存连续，vector通常对缓存友好，有更好的空间局部性。
-   list
    -   访问元素：list不支持随机访问，访问任意元素需要从头节点开始遍历链表，时间复杂度为O(n)。
    -   插入和删除：在list的任意位置插入和删除元素非常高效，只需要修改相邻节点的指针，时间复杂度为O(1)。但需要注意的是，要定位到插入或删除的位置仍然需要O(n)的时间。

**应用场景**

-   vector：当需要频繁访问元素，且插入和删除操作主要发生在容器末尾时，vector是一个好的选择。由于其连续内存特性，vector通常更适用于需要高缓存友好性的场景。
-   list：当需要频繁在容器中间或开头进行插入和删除操作，且对随机访问性能要求不高时，list是一个更合适的选择。list也适用于那些不支持或不方便进行内存移动的数据类型的场景，因为list在插入和删除时不会引起元素的内存移动。





### 4. `std::set` 与 `std::unordered_set` 的区别？

`std::set` 和 `std::unordered_set` 都是用于存储不重复元素的关联容器 (associative container)，但它们之间有一些关键区别。`std::set` 是一个基于红黑树实现的有序容器，而 `std::unordered_set`是一个基于哈希表实现的无序容器。下面列出了它们之间的主要区别：

**底层数据结构**

-   `set`：基于红黑树实现。元素在容器中按照一定的顺序排列（通过比较运算符 `<` 或自定义比较函数）。
-   `unordered_set`：基于哈希表实现。元素在容器中的位置由其哈希值决定，因此元素在容器中的顺序是无序的。

**时间复杂度**

-   `set`：插入、删除和查找操作的平均时间复杂度为 O(log n)，其中 n 为元素个数。
-   `unordered_set`：插入、删除和查找操作的平均时间复杂度为 O(1)，但在最坏情况下（所有元素都在同一个哈希桶中）时间复杂度可能退化为 O(n)。

**空间复杂度**

-   `set`：空间复杂度相对较低，因为它基于平衡二叉搜索树。
-   `unordered_set`：空间复杂度相对较高，因为哈希表需要分配额外的空间来存储桶和处理冲突。

**元素顺序**

-   `set`：元素在容器中按照排序顺序存储，因此遍历 `set` 时，元素将按照顺序输出。
-   `unordered_set`：元素在容器中是无序的。遍历时，元素的输出顺序将是随机的。

**自定义哈希函数和比较函数**

-   `set`：需要自定义比较函数（通常为 `operator<` 或 `std::less` 的自定义版本），以便在平衡二叉搜索树中对元素进行排序。
-   `unordered_set`：需要自定义哈希函数（用于计算元素的哈希值）和相等函数（用于比较元素是否相等）。

**适用场景**

-   `set`：当需要一个有序容器时，或者当对元素的插入、删除和查找时间复杂度要求为对数级别时，使用 `set` 是一个不错的选择。
-   `unordered_set`：当不需要关心元素顺序，且需要更快速的插入、删除和查找操作时，使用 `hash_set` 或 `unordered_set` 更为合适。



### 5. unordered_map与map的区别？

`map` 和 `unordered_map`都是 C++ 中常用的关联容器，它们允许使用键（key）来存储和检索值（value）。尽管它们有相似的功能，但它们的底层实现和性能特点有很大的不同。

**底层数据结构**

-   `map`：基于平衡二叉搜索树（通常是红黑树）实现。键值对按照键的顺序（通过比较运算符 `<` 或自定义比较函数）排列。
-   `unordered_map`：基于哈希表实现。键值对在容器中的位置由键的哈希值决定，因此键值对在容器中的顺序是无序的。

**时间复杂度**

-   `map`：插入、删除和查找操作的平均时间复杂度为 O(log n)，其中 n 为元素个数。
-   `unordered_map`：插入、删除和查找操作的平均时间复杂度为 O(1)，但在最坏情况下（所有元素都在同一个哈希桶中）时间复杂度可能退化为 O(n)。

**空间复杂度**

-   `map`：空间复杂度相对较低，因为它基于平衡二叉搜索树。
-   `unordered_map`：空间复杂度相对较高，因为哈希表需要分配额外的空间来存储桶和处理冲突。

**元素顺序**

-   `map`：键值对按照键的顺序排列，因此遍历 `map` 时，键值对按照键的顺序输出。
-   `unordered_map`：键值对在容器中是无序的。遍历时，键值对的输出顺序将是随机的。

**自定义哈希函数和比较函数**

-   `map`：需要自定义比较函数（通常为 `operator<` 或 `std::less` 的自定义版本），以便在平衡二叉搜索树中对键进行排序。
-   `unordered_map`：需要自定义哈希函数（用于计算键的哈希值）和相等函数（用于比较键是否相等）。

**适用场景**

-   `map`：当需要一个有序容器时，或者当对键值对的插入、删除和查找时间复杂度要求为对数级别时，使用 `map` 是一个不错的选择。
-   `unordered_map`：当不需要关心键值对顺序，且需要更快速的插入、删除和查找操作时，使用 `unordered_map` 更为合适。

### 6. map、set是怎么实现的，红黑树是怎么能够同时实现这两种容器？ 为什么使用红黑树？

`map` 和 `set` 都是基于红黑树实现的关联容器。红黑树是一种自平衡的二叉搜索树，它通过在每个节点上添加一个颜色属性（红色或黑色）来确保树保持大致平衡。红黑树的平衡特性可以保证插入、删除和查找操作具有较好的时间复杂度（O(log n)）。

红黑树如何实现 `map` 和 `set`：

-   实现 `set`：红黑树中的每个节点存储一个键，节点之间通过比较键的大小进行排序。红黑树的节点之间的顺序关系满足二叉搜索树的特性。因此，通过将元素作为红黑树的键，我们可以实现一个 `set` 容器。
-   实现 `map`：为了实现 `map` 容器，需要同时存储键和值。在红黑树中，每个节点除了存储键之外，还可以存储一个对应的值。通常将键和值封装成一个 `pair` 对象。这样，红黑树的
-   节点就包含了键值对，并且键之间的顺序关系依然满足二叉搜索树的特性。因此，通过将键值对作为红黑树的节点，我们可以实现一个 `map` 容器。

为什么使用红黑树？

-   时间复杂度：红黑树的自平衡特性保证了树的高度大致保持在 O(log n)，这意味着插入、删除和查找操作的时间复杂度都是 O(log n)。相比其他的数据结构（如普通的二叉搜索树），红黑树在最坏情况下仍然具有较好的性能。
-   内存效率：红黑树只需要在每个节点上存储一个额外的颜色属性，因此与其他自平衡二叉搜索树（如 AVL 树）相比，红黑树具有较好的内存效率。
-   灵活性：红黑树可以用于实现多种关联容器，例如 `set`、`multiset`、`map`和`multimap`。同时，红黑树支持范围查询、查找前驱和后继等高级操作，这使得它成为实现这些容器的理想选择。
-   良好的实时性：红黑树的插入、删除和调整操作都具有较好的实时性，因为它们的时间复杂度可以保证在 O(log n)。相比其他数据结构，红黑树能够更好地满足实时性的需求。



### 12. STL中list与queue之间的区别？

`std::list`： `std::list` 是一个双向链表容器，支持在常数时间内在任何位置插入和删除元素。它提供了随机访问迭代器，这意味着你可以在链表中向前和向后移动，但不能直接访问任意位置的元素。`std::list` 是一种非连续存储的数据结构，这意味着它的元素可能分散在内存中的不同位置。

`std::list` 主要用途：

-   当需要在容器中间插入或删除元素时，使用 `std::list` 效率较高。
-   当不需要随机访问元素时，可以考虑使用 `std::list`。

`std::queue`： `std::queue` 是一个容器适配器，它基于其他容器（如 `std::deque`、`std::list` 或 `std::vector`）实现了一个先进先出（FIFO）的队列。`std::queue` 提供了有限的接口，仅支持在队列尾部插入元素（`push`），在队列头部移除元素（`pop`）以及访问队列头部元素（`front`）和尾部元素（`back`）。`std::queue` 的底层容器决定了它的存储方式和性能特性。

`std::queue` 主要用途：

-   当需要实现先进先出（FIFO）策略时，使用 `std::queue` 是很自然的选择。
-   当不需要在容器中间插入或删除元素时，可以使用 `std::queue`。





### `std::priority_queue`

>   The [priority queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)) is a [container adaptor](https://en.cppreference.com/w/cpp/container.html#Container_adaptors) that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.

#### 基本特性

1. **容器适配器**：`priority_queue` 不是一个独立的容器，而是构建在其他容器（如 `vector` 或 `deque`）之上的适配器
2. **最大堆实现**：默认情况下，`priority_queue` 实现为**最大堆**，即队列顶部（`top()`）总是最大元素
3. **时间复杂度**：
   - 插入元素（`push()`）：O(log n)
   - 访问顶部元素（`top()`）：O(1)
   - 删除顶部元素（`pop()`）：O(log n)

#### 基本用法

1. 包含头文件

```cpp
#include <queue>
```

2. 声明和初始化

```cpp
// 默认使用 vector 作为容器，最大堆
std::priority_queue<int> max_heap;

// 使用 vector 作为容器，大根堆
std::priority_queue<int, std::vector<int>, std::less<int> > max_heap;

// 使用 vector 作为容器，小根堆
std::priority_queue<int, std::vector<int>, std::greater<int> > min_heap;

// 使用 deque 作为容器
std::priority_queue<int, std::deque<int>> pq_deque;

// 使用自定义比较函数
auto cmp = [](int left, int right) { return left > right; };
std::priority_queue<int, std::vector<int>, decltype(cmp)> custom_heap(cmp);

// 使用pair和自定义比较函数
auto cmp = [](std::pair<int, int> &a, std::pair<int, int> &b) { return a.second > b.second; };
std::priority_queue<pair<int, int>, std::vector<pair<int, int> >, decltype(cmp)> custom_heap(cmp);

// 使用自定义数据类型和自定义比较函数
struct Count {
    int key;
    int value;
};
auto cmp = [](const Count &a, const Count &b) { return a.value > b.value; };
std::priority_queue<Count, std::vector<Count>, decltype(cmp)> custom_heap(cmp);

// 使用自定义数据类型和运算符重载
struct Count {
    int key;
    int value;
    // 成员函数只需一个参数（另一个是this）
    bool operator<(const Count& other) {
        return value < other.value;
    }
}
std::priority_queue<Count, std::vector<Count>, std::less<Count> > custom_heap;
```

#### 注意事项

1. **自定义类型**：如果使用自定义类型，需要提供比较函数或重载 `<` 运算符
2. **迭代器**：`priority_queue` 不提供迭代器访问元素（只能访问顶部）
3. **底层容器**：默认使用 `vector`，但可以通过模板参数指定其他容器（如 `deque`）
4. **线程安全**：标准库中的 `priority_queue` 不是线程安全的
5. **元素相等**：当多个元素优先级相同时，出队顺序取决于底层容器和比较函数

#### 关于优先队列的堆类型

| 堆类型 | 比较函数            | 顶部元素 |
| ------ | ------------------- | -------- |
| 最大堆 | `a.value < b.value` | 最大值   |
| 最小堆 | `a.value > b.value` | 最小值   |