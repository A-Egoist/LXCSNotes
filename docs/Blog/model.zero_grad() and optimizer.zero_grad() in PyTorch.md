在 PyTorch 中, 对模型参数的梯度置 0 通常有两种方式: `model.zero_grad()` 和 `optimizer.zero_grad()`.

model.zero_grad() 的作用是将所有模型参数的梯度置为 0.

optimizer.zero_grad() 的作用是将优化的 torch.Tensor 梯度清除.

当使用 `optimizer = optim.optimizer(model.parameters())` 设置优化器时, 上述两种方法是等效的.

当多个模型使用同一个优化器, 或者当一个模型使用多个优化器时, 两者是不同的, 需要根据实际情况选择梯度的清除方式.

参考资料:
[PyTorch中的model.zero_grad() vs optimizer.zero_grad()](https://cloud.tencent.com/developer/article/1710864)
[optimizer.zero_grad()](https://blog.csdn.net/weixin_36670529/article/details/108630740)