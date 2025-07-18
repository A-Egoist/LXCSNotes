# Python词云实战

```python
# -*- coding: utf-8 -*-
# author：Egoist
# 导入相关库
import numpy as mp
import pandas as pd
import matplotlib.pyplot as plt
import jieba
import wordcloud


def main():
    file_path = r'comments.csv'
    df = pd.read_csv(file_path)
    temp = df.loc[:, 'comments']
    text = ''
    for i in temp:
        try:
            text += i
        except:
            continue
    word_frequencies = dict()

    add_word_list = ['米津玄师', '《恋如雨止》', 'aimer', 'Ref:rain', 'Aimer', 'Brave Shine', '士郎', '吾王', 'Fate',
                     'fate', 'hf', 'ubw', '————', '伊莉雅', '卫宫士郎', '樱', '狐妖小红娘', '亚瑟王', '凛', 'brave shine',
                     '红a', '红A', '时臣', '阿尔托莉娅·亚瑟·潘德拉贡', '远坂凛', 'FATE', 'EA', '狐妖粉', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '' ]
    for i in add_word_list:
        jieba.add_word(i)

    cut_text = jieba.lcut(text)
    continue_words = ['我', '你', '的', '了', '呢', ',', '?', ' ', '“', '”', '。', '《', '》', '；', '？', '，', '、',
                      '（', '）', '…', '！', '...', '是', '我们', '自己', '但', '还是', '她', '会', '有', '又', '因为',
                      '后来', '谁', '没有', '所有', '都', '\\', '更', '对', '而且', '只是', '这个', '啊', '就', '那个',
                      '上', '向', '像', '这', '才', '走', '和', '却', '只', '还', '抄', '个', '从', '一个', '做', '——',
                      '：', '(', ')', 'a', 'A', '之', '所以', '小', '你们', '为什么', '能', '不是', '下', '被', '大家',
                      '抄袭', '不', '也', '说', '来', '里', '吧', '而', '很', '人', '点', '前', '后', '高', '低', '会',
                      '不会', '过', '什么', '为', '去', '再', '是因为', '这件', '', '', '', '', '', '', '', '', '', '', '', '', ''
                      , '么', '一些', '事', '要', '不要', '到', '啦', '√', '-', '～', '......', '。。。', '......',
                      '吗', '哪里', '最', '一下', '·', '的话', '给', '看', '.', '怎么', '但是', '算了', '吵', '', '', '', '', '', '', '', '',
                      '在', '为了', '写', '把', '催', '懂', '弄', '打', '区', '某些', '虽然', '这么', '可以', '认为', '', '', '', '', '', ''
                      , '各位', '这首', '者', '应该', '吃', '由', '得', '然而', '2', '来自', '人家', '那些', '那', '以为',
                      '', '', '', '', '', '', '', '', '', '']
    # 统计频数
    for i in cut_text:
        if i in continue_words:
            continue
        if i in word_frequencies:
            word_frequencies[i] += 1
        else:
            word_frequencies[i] = 1

    wc = wordcloud.WordCloud(
        font_path=r'C:\Windows\Fonts\simkai.ttf',
        background_color='white',
        width=1000, height=800,
        max_words=200,
        max_font_size=400,
        min_font_size=10,
        mode='RGBA')

    # print(word_frequencies)
    word_frequencies['Aimer'] = 50000
    word_frequencies['aimer'] = 0
    wc.generate_from_frequencies(word_frequencies)  # 根据词出现的频数进行
    wc.to_file(r'wordcloud.png')  # 保存词云图


if __name__ == '__main__':
    main()
```

