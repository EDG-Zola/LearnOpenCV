## 这是结合OpenCV和SVM进行的交通标志识别的demo
### 开发环境
Win7 + OpenCV2.4.9 + VS 2010
### 训练图片数据集
数据集来源于GTSRB的43类数据中的最高限速（20,30,50,60,70,80,100,120）的图片，经过颜色空间+圆检测+灰度化后，改变成45x45的尺寸大小的图片
[训练图片](https://github.com/EDG-Zola/LearnOpenCV/tree/master/TSR/TrainModel1/TrainModel1/result/1 (1).jpg)
[预测结果](https://github.com/EDG-Zola/LearnOpenCV/tree/master/TSR/TrainModel1/TrainModel1/test/testresult.png)