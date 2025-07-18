# PyTorch 中 tensor.view() 和 tensor.reshape() 的区别

## tensor.view()

只是对原始 tensor 做一个视图的改变, 新的 tensor 与原始 tensor 共享存储空间. 当新的 tensor 改变的时候, 原始 tensor 也会改变.

## tensor.reshape()
当满足 tensor 连续条件的时候 tensor.reshape() 和 tensor.view() 效果相同; 当不满足时, tensor.reshape() 效果与 tensor.clone().view() 相同.
简单来说就是直接使用 tensor.reshape() 之后, 再修改 tensor 的值不确定是否会修改原始 tensor 的值.

## 结论
官方推荐使用 tensor.clone().view() 来代替 tensor.reshape().
此外使用 tensor.clone() 还有一个好处是会被记录在计算图中，即梯度回传到副本时也会传到源 tensor.

## 例证
```python
import torch


if __name__ == '__main__':
    x = torch.rand(2, 3)
    print(f'x = {x}')
    y = x.view(3, 2)
    z = x.clone().view(3, 2)
    print(f'y = {y}')
    print(f'z = {z}')
    y[0][0] += 1
    print(f'x = {x}')
    print(f'y = {y}')
    print(f'z = {z}')
```
```bash
x = tensor([[0.4721, 0.3825, 0.7544],
        [0.4049, 0.8971, 0.4204]])
y = tensor([[0.4721, 0.3825],
        [0.7544, 0.4049],
        [0.8971, 0.4204]])
z = tensor([[0.4721, 0.3825],
        [0.7544, 0.4049],
        [0.8971, 0.4204]])
x = tensor([[1.4721, 0.3825, 0.7544],
        [0.4049, 0.8971, 0.4204]])
y = tensor([[1.4721, 0.3825],
        [0.7544, 0.4049],
        [0.8971, 0.4204]])
z = tensor([[0.4721, 0.3825],
        [0.7544, 0.4049],
        [0.8971, 0.4204]])
```