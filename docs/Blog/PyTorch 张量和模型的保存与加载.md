# PyTorch 张量和模型的保存与加载

PyTorch 中 Tensor 和模型可以保存为 `.pt`, `.pth`, `.pkl` 格式的文件，三者在格式上没有区别

## 张量的保存和加载

### 单个张量

```python
x = torch.randint(100, (4, 4))
torch.save(x, './save_model/x.pt')  # 保存

y = torch.load('./save_model/x.pt')  # 加载
print(y)
```

### 多个张量

```python
x = torch.randint(10, (2, 2))
y = torch.randint(100, (3, 3))

a = [x, y]
torch.save(a, './save_model/a.pt')
a_ = torch.load('./save_model/a.pt')

b = (x, y)
torch.save(b, './save_model/b.pt')
b_ = torch.load('./save_model/b.pt')

c = {'x':x, 'y':y}
torch.save(c, './save_model/c.pt')
c_ = torch.load('./save_model/c.pt')
```



`torch.save()` 会保留张量之间的关系。若只想保留张量的数据，不保留张量之间的关系，可以使用`clone()`来保存张量的数据克隆。

```python
x = torch.arange(10)
y = x[:5]
torch.save([x, y.clone()], './save_model/x_and_y.pt')
x_, y_ = torch.load('./save_model/x_and_y.pt')
```



## 模型的保存和加载

### 保存模型

这种方式不仅保存、加载模型的数据，也**包括模型的结构**一并存储，存储的文件会较大，好处是加载时不需要提前知道模型的结构，解来即用。实际上这与上文提到的保存Tensor是一致的。

```python
torch.save(model, save_path)  # 保存
model = torch.load(save_path)  # 加载
model.eval()  # 如果加载的模型要用于 inference，则需要使用 model.eval()
```



### 保存模型参数

这是一种**较为推荐**的保存方法，即**只保存模型的参数**，保存的模型文件会较小，而且比较灵活。但是当加载时，需要先实例化一个模型，然后通过加载将参数赋给这个模型的实例，也就是说**加载之前使用者需要知道模型的结构**。

```python
torch.save(model.state_dict(), save_path)  # 保存
model = Model()  # 实例化
model.load_state_dict(torch.load(save_path))  # 加载
model.eval()
```

比较重要的点是：

- 保存模型时调用 `state_dict()` 获取模型的参数，而不保存结构
- 加载模型时需要预先实例化一个对应的网络，比如`model = Model()`，这也就意味着，使用者需要预先有`Model`这个类，如果不知道这个网络的类定义或者结构，这种只保存参数的方法将无法使用
- 加载模型使用 `load_state_dict` 方法，其参数不是文件路径，而是 `torch.load(PATH)`
- 如果加载出来的模型**用于验证**，不要忘了使用 `model.eval()` 方法，它会丢弃 dropout、normalization 等层，因为这些层不能在inference 的时候使用，否则得到的推断结果不一致

### 保存与加载模型其他参数

有时我们不仅要保存模型，还要**连带保存一些其他的信息**。比如在训练过程中保存一些 checkpoint，往往除了模型，还要保存它的epoch、loss、optimizer等信息，以便于加载后对这些 checkpoint 继续训练等操作；或者再比如，有时候需要将多个模型一起打包保存等。这些其实也很简单，正如我们上文提到的，`torch.save` 可以保存dict、list、tuple等多种数据结构，所以一个字典可以很完美的解决这个问题，比如一个简单的例子：

```python
# saving
torch.save({
            'epoch': epoch,
            'model_state_dict': model.state_dict(),
            'optimizer_state_dict': optimizer.state_dict(),
            'loss': loss,
            ...
            }, PATH)

# loading
model = TheModelClass(*args, **kwargs)
optimizer = TheOptimizerClass(*args, **kwargs)

checkpoint = torch.load(PATH)
model.load_state_dict(checkpoint['model_state_dict'])
optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
epoch = checkpoint['epoch']
loss = checkpoint['loss']

model.eval()
# - or -
model.train()
```

### 跨设备存储与加载

* 从 CPU 保存，加载到 CPU

实际上，这就是默认的情况，我们上文提到的所有内容都没有关心设备的问题，因此也就适应于这种情况。

* 从 CPU 保存，加载到 GPU

```python
torch.save(net.state_dict(), save_path)  # 保存

device = torch.device('cuda: 0')
net = Net()
net.load_state_dict(torch.load(save_path, map_location=device))  # 通过 map_loacation 映射到 GPU
# or
net.load_state_dict(torch.load(save_path))  # 加载
net.to(device)  # 使用 .to() 发送到 GPU
```



* 从 GPU 保存，加载到 CPU

```python
torch.save(net.state_dict(), save_path)  # 保存
device = torch.device('cpu')
net = Net()  # 实例化
net.load_state_dict(torch.load(save_path, map_location=device))
```



* 从 GPU 保存，加载到 GPU

```python
torch.save(net.state_dict(), save_path)  # 保存
device = torch.device('cuda: 0')  # 指定设备
net = Net()  # 实例化
net.to(device)  # 使用 .to() 发送到 GPU
```



## 断电续训

* 保存

```python
torch.save({'model_state_dict': model.state_dict(),
            'optimizer_state_dict': optimizer.state_dict(),
            'epoch': epoch,
            'loss': loss,
            'acc': acc}, save_path)
```

* 重新加载

```python
model = Model()  # 实例化
optimizer = torch.optim.SGD(*args, **kwargs)
checkpoint = torch.load(save_path)
model.load_state_dict(checkpoint['model_state_dict'])
optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
epoch = checkpoint['epoch']
loss = checkpoint['loss']
acc = checkpoint['acc']

model.train()  # 训练
# or
model.eval()  # 验证
```

> 在保存用于推理或者继续训练的常规检查点的时候，除了模型的 `state_dict` 之外，还必须保存其他参数。保存优化器的 `state_dict` 也非常重要，因为它包含了模型在训练时候优化器的缓存和参数。除此之外，还可以保存停止训练时 `epoch` 数，最新的模型损失，额外的 `torch.nn.Embedding` 层等。
>
> 要保存多个组件，则将它们放到一个字典中，然后使用 `torch.save()` 序列化这个字典。一般来说，使用 `.tar` 文件格式来保存这些检查点。
>
> 加载各个组件，首先初始化模型和优化器，然后使用 `torch.load()` 加载保存的字典，然后可以直接查询字典中的值来获取保存的组件。
>
> 同样，评估模型的时候一定不要忘了调用 `model.eval()`



## 参考资料

* [PyTorch教程-7：PyTorch中保存与加载tensor和模型详解](https://www.jianshu.com/p/18d6078ae205)
* [PyTorch使用cpu与gpu之间模型相互加载调用](https://blog.csdn.net/weixin_39032619/article/details/118492794)
* [Pytorch：模型的保存与加载 torch.save()、torch.load()、torch.nn.Module.load_state_dict()](https://blog.csdn.net/weixin_40522801/article/details/106563354)

