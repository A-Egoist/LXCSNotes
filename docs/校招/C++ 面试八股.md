# C++ 面试八股



## C++ 多态



### C++ 多态解决了什么问题

多态分为静态多态和动态多态

静态多态通过模板和函数重载实现

动态多态通过虚函数和继承实现

![image-20250806110659917](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202508061107767.png)

**静态多态**

```cpp
#include <iostream>
#include <string>

class Circle {
public:
    void Draw() const {
        std::cout << "Draw a circle.\n";
    }
};

class Square {
public:
    void Draw() const {
        std::cout << "Draw a square.\n";
    }
};

template <typename T>
void Draw(const T& shape) {
    shape.Draw();  // 编译时绑定
}

int main() {
    Circle c;
    Square s;

    Draw(c);  // 模板参数推导
    Draw(s);  // 模板参数推导

    return 0;
}
```

1.   复用：Draw 模板适用于任何有 Draw 方法的类型

2.   扩展：新增只需实现 Draw，无需修改模板

3.   解耦：Draw 不依赖基类，仅依赖隐式接口



**动态多态**

```cpp
#include <iostream>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void Draw() const = 0;
};

class Circle : public Shape {
public:
    virtual void Draw() const override {
        std::cout << "Draw a circle.\n";
    }
};

class Square : public Shape {
public:
    virtual void Draw() const override {
        std::cout << "Draw a square.\n";
    }
};

void RenderAll(const std::vector<Shape*>& shapes) {
    for (const auto* shape : shapes) {
        shape->Draw();  // 动态绑定，调用具体实现
    }
}

int main() {
    std::vector<Shape*> shapes = {new Circle(), new Square()};
    RenderAll(shapes);

    for (auto* shape : shapes) {
        delete shape;
    }

    return 0;
}
```

1.   复用：RenderAll
2.   扩展：新增只需继承 Shape 并实现 Draw()，无需修改 RenderAll
3.   解耦：RenderAll 只依赖抽象 Shape，不依赖具体图形类



[字节后端C++一面：C++多态解决了什么问题？【码农Mark】](https://www.bilibili.com/video/BV1vNTtzuEVj/?spm_id_from=333.1391.0.0&vd_source=f4cc25a44af6631d6f4db023b3bb88e4)



## 堆栈









## 参考资料

[1] [史上最全C/C++面试、C++面经八股文，一文带你彻底搞懂C/C++面试、C++面经！](https://blog.csdn.net/songbijian/article/details/132507421)

[2] 
