# 欢迎使用 LXCSNotes

## 代码高亮示例
```python
def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)
```

## LaTeX 数学公式
行内公式: $E = mc^2$

块级公式:
$$
\nabla \times \vec{\mathbf{B}} - \frac{\partial \vec{\mathbf{E}}}{\partial t} = \mu_0 \vec{\mathbf{J}}
$$

## 提示框示例

!!! note "复杂度分析"

*   时间复杂度: $O(n \log n)$
*   空间复杂度: $O(n)$

```python
# Python 示例
print("Hello with Python tag")
```

```cpp
// C++ 示例
#include <iostream>
int main() {
  std::cout << "Hello with C++ tag";
}
```

```java
// Java 示例
public class Main {
  public static void main(String[] args) {
    System.out.println("Hello with Java tag");
  }
}
```

>   [!NOTE]
>
>   

>   [!TIP]
>
>   

