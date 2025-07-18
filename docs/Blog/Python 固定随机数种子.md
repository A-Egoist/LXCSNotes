# Python 固定随机数种子

在使用随机函数之前调用此函数固定随机数种子，使得训练结果可以复现。
```python
import os
import random
import numpy as np
import torch


def set_seed(seed=2000):
    """
    links: https://github.com/pytorch/pytorch/issues/7068
    :param seed: random seed
    :return: None
    """
    random.seed(seed)
    os.environ['PYTHONHASHSEED'] = str(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    torch.backends.cudnn.benchmark = False
    torch.backends.cudnn.deterministic = True


if __name__ == '__main__':
    set_seed(2000)  # set random seed

```

参考资料：
* [PyTorch固定随机数种子](https://blog.csdn.net/john_bh/article/details/107731443)
* [torch.backends.cudnn.benchmark和cudnn.deterministic](https://blog.csdn.net/weixin_42587961/article/details/109363698)
* [Pytorch中设置哪些随机数种子，才能保证实验可重复](https://blog.csdn.net/u014264373/article/details/114323297)