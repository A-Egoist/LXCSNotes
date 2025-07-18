







Python跨文件共享全局变量

比如在`global.py`中:

```python
Email = "1012738513@qq.com"
Name = "Amonologue"
```

在`information.py`中直接使用

```python
import global
def main():
    print(f"My name is: {Name}")
    print(f"My email address is: {Email}")


if __name__ == "__main__":
    main()

```

