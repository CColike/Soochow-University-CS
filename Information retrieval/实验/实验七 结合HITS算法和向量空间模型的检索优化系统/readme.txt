要求：
1）使用向量空间模型，面向query.txt文件中的query，对DocSet文件夹中的所有文本文件进行“初排序”（排序原则是依照文本相似度大小，由高到低进行排序），“初排”的结果计入列表1中，按相似度由高到低的顺序，将DocSet文件夹中文本文件的编号，写入List1.txt文件；
2）使用HITS算法，利用Structuraldata.txt文件中的网络节点结构关系，对“初排”结果进行重排序，不仅输出依照Hub值的重排序结果，写入ListHub.txt文件，也要输出依照Authority值的重排序结果，写入ListAuthority.txt文件。