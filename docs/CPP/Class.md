# Class

## 构造函数

在C++中，构造函数（Constructor）是一种特殊的成员函数，用于初始化对象的成员变量。它在对象创建时自动调用，与类同名且无返回类型。以下是主要的构造函数类型及其详细介绍：

---

### 1. 默认构造函数（Default Constructor）

- **作用**：创建对象时不提供任何参数时调用。

- **特点**：

    - 无参数（或所有参数都有默认值）。
    - 若用户未定义任何构造函数，编译器会自动生成一个**隐式默认构造函数**（但不会初始化内置类型成员）。

- **示例**：

    ```cpp
    class MyClass {
    public:
        // 显式定义默认构造函数
        MyClass() {
            data = 0;  // 初始化成员
        }
    private:
        int data;
    };
    // 使用：MyClass obj;
    ```

---

### 2. 参数化构造函数（Parameterized Constructor）

- **作用**：通过传递参数初始化对象。

- **特点**：

    - 带有一个或多个参数。
    - 允许灵活初始化对象状态。

- **示例**：

    ```cpp
    class Point {
    public:
        Point(int x, int y) : x_(x), y_(y) {}  // 使用初始化列表
    private:
        int x_, y_;
    };
    // 使用：Point p(10, 20);
    ```

---

### 3. 拷贝构造函数（Copy Constructor）

- **作用**：用同类型的另一个对象初始化新对象（深拷贝/浅拷贝）。

- **特点**：

    - 参数为 **`const T&`**（常量引用）。
    - 若用户未定义，编译器生成隐式拷贝构造函数（执行浅拷贝）。

- **调用场景**：

    - 对象直接初始化：`T obj2 = obj1;`
    - 函数传参（值传递时）。

- **示例**：

    ```cpp
    class Array {
    public:
        Array(const Array& other) {
            size_ = other.size_;
            data_ = new int[size_];  // 深拷贝
            for (int i = 0; i < size_; ++i) 
                data_[i] = other.data_[i];
        }
    private:
        int* data_;
        int size_;
    };
    ```

---

### 4. 移动构造函数（Move Constructor）（C++11引入）

- **作用**：将资源（如堆内存）从临时对象“移动”到新对象，避免深拷贝开销。

- **特点**：

    - 参数为 **`T&&`**（右值引用）。
    - 使用 `noexcept` 声明避免异常问题。
    - 被移动后的对象应处于有效但未定义状态。

- **示例**：

    ```cpp
    class Array {
    public:
        Array(Array&& other) noexcept 
            : data_(other.data_), size_(other.size_) {
            other.data_ = nullptr;  // 置空原指针，防止资源释放
            other.size_ = 0;
        }
    private:
        int* data_;
        int size_;
    };
    // 使用：Array a2 = std::move(a1); // 移动语义
    ```

---

### 5. 委托构造函数（Delegating Constructor）（C++11引入）

- **作用**：一个构造函数调用同类中的其他构造函数，避免代码重复。

- **示例**：

    ```cpp
    class Rectangle {
    public:
        // 委托给另一个构造函数
        Rectangle() : Rectangle(1, 1) {}  
        Rectangle(int w, int h) : width(w), height(h) {}
    private:
        int width, height;
    };
    ```

---

### 6. 转换构造函数（Converting Constructor）

- **作用**：将其他类型隐式转换为当前类类型。

- **特点**：

    - 单参数构造函数（或多参数但除第一个外均有默认值）。
    - 用 `explicit` 可禁止隐式转换。

- **示例**：

    ```cpp
    class String {
    public:
        String(const char* s) { ... }  // 隐式转换：char* → String
        explicit String(int size) { ... } // 禁用隐式转换：int → String
    };
    // 使用：String s1 = "Hello"; // 隐式转换
    // String s2 = 10;           // 错误（explicit阻止隐式转换）
    ```

---

### 7. 继承构造函数（Inheriting Constructor）（C++11引入）

- **作用**：派生类直接继承基类的构造函数。

- **语法**：`using Base::Base;`

- **示例**：

    ```cpp
    class Base {
    public:
        Base(int x) { ... }
    };
    class Derived : public Base {
    public:
        using Base::Base; // 继承Base的构造函数
    };
    // 使用：Derived d(10); // 调用Base(int)
    ```

---

### 关键特性总结：

| 构造函数类型       | 关键特点                                               |
| ------------------ | ------------------------------------------------------ |
| **默认构造函数**   | 无参数；对象默认初始化时调用。                         |
| **参数化构造函数** | 带参数；灵活初始化对象。                               |
| **拷贝构造函数**   | 参数为 `const T&`；用现有对象初始化新对象。            |
| **移动构造函数**   | 参数为 `T&&`；高效转移资源（C++11）。                  |
| **委托构造函数**   | 调用同类其他构造函数；减少冗余（C++11）。              |
| **转换构造函数**   | 单参数；支持类型隐式转换（可用 `explicit` 禁用）。     |
| **继承构造函数**   | `using Base::Base;`；派生类复用基类构造函数（C++11）。 |

---

### 注意事项：

1. **初始化列表**：优先使用成员初始化列表（效率更高，避免重复赋值）。
2. **`explicit` 关键字**：阻止不期望的隐式类型转换。
3. **编译器生成**：若未定义拷贝/移动构造函数，编译器会生成默认版本（可能不满足深拷贝需求）。

合理使用构造函数能提升代码的健壮性和效率，尤其在涉及资源管理（内存、文件句柄等）时！



## 生命周期

-   自动存储周期（栈上） - 函数的局部变量，自动析构
-   动态存储周期（堆上） - 通过 new 创建的，delete 时析构
-   静态存储周期（static 和 inline） - 全局变量，程序结束时析构



## 析构函数



### 析构函数的逆天大坑

定义了析构函数，就**必须删除移动构造函数、移动赋值函数、拷贝构造函数、拷贝赋值函数**！

原因很复杂，整个故事要从 boost 当年如何设计出右值引用到图灵的停机问题讲起，讲了你也记不住，只需要记住结论：

如果你要定义析构函数，就**必须删除移动构造函数、移动赋值函数、拷贝构造函数、拷贝赋值函数**！



### 虚类的析构函数必须是虚的



### 临时变量的生命周期是一行



## 参考资料

[深入理解析构函数与生命周期](https://parallel101.github.io/cppguidebook/cpp_lifetime/)





## DeepSeek 回答

>   “定义了析构函数，就必须删除移动构造函数、移动赋值函数、拷贝构造函数、拷贝赋值函数！ 原因很复杂，整个故事要从 boost 当年如何设计出右值引用到图灵的停机问题讲起，讲了你也记不住，只需要记住结论： 如果你要定义析构函数，就必须删除移动构造函数、移动赋值函数、拷贝构造函数、拷贝赋值函数！”
>   这个要如何解释和理解？

这段博客的表述**不够准确**，它过度简化并强化了 C++ 中关于资源管理类设计的规则（Rule of Three/Five）。让我们来澄清一下：

**核心规则：Rule of Three/Five (三/五法则)**

1.  **Rule of Three (C++98/03)：** 如果一个类需要显式地定义以下其中一项：
    *   **析构函数 (Destructor)**
    *   **拷贝构造函数 (Copy Constructor)**
    *   **拷贝赋值运算符 (Copy Assignment Operator)**
    那么它很可能也需要显式地定义**全部三项**。
    **为什么？** 这通常意味着你的类正在管理某种资源（动态内存、文件句柄、网络连接、锁等）。编译器生成的默认拷贝操作（浅拷贝）对于资源管理类通常是错误的，会导致双重释放、资源泄漏等问题。如果你定义了析构函数来释放资源，就必须确保拷贝操作也能正确处理资源（通常是深拷贝或禁止拷贝）。

2.  **Rule of Five (C++11 及以后)：** 在 Rule of Three 的基础上，增加了对移动语义的支持。如果一个类需要显式地定义以下其中一项：
    *   析构函数
    *   拷贝构造函数
    *   拷贝赋值运算符
    *   **移动构造函数 (Move Constructor)**
    *   **移动赋值运算符 (Move Assignment Operator)**
    那么它很可能也需要显式地定义**全部五项**（或者仔细考虑哪些需要定义，哪些需要删除 `=delete`，哪些可以用默认 `=default`）。
    **为什么？** 移动语义允许高效地“窃取”资源。如果你定义了析构函数（表明管理资源），并且你希望你的类支持高效的移动操作（而不是回退到拷贝），那么你需要定义移动构造和移动赋值来正确地转移资源所有权。同时，你也需要确保拷贝操作的行为是正确的（深拷贝或禁止）。

**对博客观点的修正与解释**

1.  **`定义了析构函数` 是信号，不是唯一条件：** 定义析构函数本身**并不强制要求**你必须删除拷贝和移动操作。它只是一个强烈的**信号**，表明这个类很可能在管理资源，因此你需要**仔细考虑**拷贝和移动操作的行为。
2.  **`就必须删除...` 是错误的绝对化：** 你至少有**三种选择**：
    *   **定义它们：** 实现正确的拷贝语义（深拷贝）和/或移动语义（资源转移）。
    *   **删除它们 (`=delete`):** 明确禁止拷贝和/或移动。这是当你确定你的类**不应该**被拷贝或移动时的做法（例如 `std::mutex`, `std::atomic`, `std::unique_ptr` 禁止拷贝但允许移动）。
    *   **使用默认 (`=default`):** 如果编译器生成的默认行为恰好就是正确的（例如，你的类所有成员本身都正确地实现了拷贝/移动/析构，比如只包含 `int`, `double`, `std::vector` 等），你可以显式使用 `=default`。但**一旦你定义了析构函数，编译器通常不会为你默认生成移动操作**（后面解释）。
3.  **“原因很复杂...停机问题” 是误导或过度引申：** 资源管理规则（Rule of Three/Five）的根本原因是为了解决**资源所有权和生命周期**的问题（双重释放、泄漏），与图灵停机问题没有直接关系。停机问题是计算理论中关于程序是否终止的不可判定性问题，虽然编程中处处有潜在的不终止，但 Rule of Five 的动机更直接、更具体。博客作者可能想表达“完整解释很复杂”，但用“停机问题”作比喻并不恰当。

**关键点：编译器行为与移动操作**

*   **C++11 的一个重要变化：** 如果你**显式声明**了以下任何一项：
    *   拷贝构造函数
    *   拷贝赋值运算符
    *   移动构造函数
    *   移动赋值运算符
    *   **析构函数**
    那么编译器**将不会自动生成移动构造函数和移动赋值运算符**。
*   **为什么有这个规则？** 这是保守但安全的设计。编译器看到你定义了析构函数（或拷贝操作），它认为你正在处理资源管理这种“特殊”任务。它不确定自动生成的默认移动操作（简单逐成员移动）是否安全（例如，移动后原对象析构时是否会错误地释放已被转移的资源？）。为了安全起见，它选择不生成，迫使你明确说明意图：是定义安全的移动操作、删除移动操作、还是让类回退到拷贝操作。

**如何正确理解和应用 Rule of Five**

1.  **当你为类定义析构函数时，提高警惕：** 问问自己：“我的类在管理资源吗？（内存、文件、锁、数据库连接等）”。
2.  **思考拷贝语义：** 这个类的对象应该能被拷贝吗？
    *   **应该：** 你需要**定义**拷贝构造函数和拷贝赋值运算符（实现深拷贝或其他正确的拷贝逻辑）。
    *   **不应该：** 你需要**删除**拷贝构造函数和拷贝赋值运算符 (`=delete`)。
3.  **思考移动语义：** 这个类的对象应该能被移动吗？（移动通常比拷贝高效）
    *   **应该且可以安全实现（转移资源）：** 你需要**定义**移动构造函数和移动赋值运算符。
    *   **不应该：** 你需要**删除**移动构造函数和移动赋值运算符 (`=delete`)。
    *   **可以不支持移动，但允许拷贝：** 如果你只定义了拷贝操作（或依赖编译器生成）并且没有定义移动操作，那么当尝试移动时，编译器会回退到使用拷贝操作。这可能有效率损失，但语义正确。
4.  **利用 `default` 和 `delete`：**
    *   如果编译器生成的默认行为（对于析构、拷贝、移动）**完全正确**，优先使用 `=default`。这使代码更清晰。
    *   如果某个操作**不应该存在**（如拷贝 `unique_ptr`），使用 `=delete` 明确禁止。
5.  **优先使用 RAII 对象管理资源：** 尽可能使用 `std::unique_ptr`, `std::shared_ptr`, `std::vector`, `std::string`, `std::fstream` 等标准库 RAII 类来管理资源。这些类已经正确实现了 Rule of Five。这样你自己的类就**不需要**定义析构函数和拷贝/移动操作（或者只需要 `=default`），因为它们的数据成员已经正确处理了资源。**这是现代 C++ 的最佳实践。**
6.  **`default` 析构函数的影响：** 如果你显式声明析构函数为 `=default`（通常在头文件中），它**仍然算作用户声明的析构函数**。因此，它会阻止编译器生成移动操作。如果你希望编译器生成移动操作，并且默认析构函数就足够，那么**不要声明析构函数**（即使是 `=default`），让编译器隐式生成。或者，显式 `=default` 移动操作。

**总结**

*   博客观点**不正确**：定义析构函数**不强制要求**删除拷贝和移动操作。
*   **正确规则是 Rule of Five：** 定义析构函数（或任何拷贝/移动操作）是一个**强烈信号**，表明你需要**仔细考虑并显式定义、删除或默认**其他拷贝/移动操作以及析构函数，以确保资源管理的正确性。
*   **核心原因：** 管理资源的类需要控制拷贝（避免浅拷贝问题）和移动（安全高效地转移资源）的行为。
*   **编译器行为：** 用户声明析构函数（或拷贝操作）会阻止编译器生成移动操作，迫使你明确意图。
*   **现代最佳实践：** 优先使用标准库 RAII 类型（`unique_ptr`, `vector` 等）管理资源，这样你自己的类通常不需要手动处理 Rule of Five。

**简单记忆（比博客的结论准确）：**
**“如果你定义了析构函数，请记得检查（并可能需要定义、删除或默认）拷贝构造函数、拷贝赋值运算符、移动构造函数和移动赋值运算符。”** 或者更简洁：**“管理资源？想想五巨头（析构、拷贝构造、拷贝赋值、移动构造、移动赋值）。”**