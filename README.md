# HUST_2018级密码学课程设计

## 1. SPN

就是如图所示的一个过程！

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/0XBZDB8J{`BZI$WBZDP6)CA.png)

#### 1.1 初次写SPN

为了方便的使用S盒P盒的那些运算（直接使用数组， 而不使用位运算），所以想起了C语言课上学的**字段结构体和联合**，but程序跑太慢了~（最后一个数据大概有 $4 \times 10^6$ 个）

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/wsLDFP.png)

#### 1.2 输入加速

算法考试里常用的使用`getchar()`进行输入加速（也可以试试`fread()`哟），终于是快起来了（天翼3G太快啦~）。

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/image-20200915104907959.png)

#### 1.3 再次加速

速度跑的还是太慢了，影响后面线性分析的效率，所以又回来重写一波~

听到大佬说打表跑得飞快，那我就不客气咯，遂即打了一个65536大小的表，果然起飞~~~（但与此同时，代码也飙升至4000+行，都是小问题~）

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/Y~~0@}R[64LEW_372SRUY35.png)

## 2.线性分析

## 3.差分分析

## 4.SPN加强

