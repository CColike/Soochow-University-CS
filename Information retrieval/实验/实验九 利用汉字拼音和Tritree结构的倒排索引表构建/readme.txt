目标：尝试利用Tritree建立中文倒排索引
步骤：1）对文档分词；2）对词语进行字符解析；3）对字符进行拼音转换；4）利用拼音建立Tritree倒排索引；5）针对查询“阅读理解”，利用Tritree倒排索引，进行检索，检验是否能够查找到正确的相关文档（相关文档只有一个，ID号尉id1）。
数据：压缩包内的data文件夹中，有10个文本文件，要求对所有文件建立Tritree索引。