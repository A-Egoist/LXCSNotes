

在 PyTorch 的 `Module` 和 `Tensor` 使用 `to()` 有所区别, `Module` 对象只需要调用 `to(device)` 不用接受返回值, `Tensor` 对象需要接收返回值.

### Module

1.   定义

     ```python
     device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
     ```

2.   使用

     ```python
     model.to(device)
     ```


3.   查看

     ```python
     print(next(model.parameters()).device)
     ```

### Tensor

1.   定义

     ```python
     device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
     ```

2.   使用

     ```python
     data = data.to(device)
     ```

3.   查看

     ```python
     print(data.device)
     ```