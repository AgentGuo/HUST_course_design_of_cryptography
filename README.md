# HUST_2018级密码学课程设计

## 1. SPN

就是如图所示的一个过程！

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/1.png)

#### 1.1 初次写SPN

为了方便的使用S盒P盒的那些运算（直接使用数组， 而不使用位运算），所以想起了C语言课上学的**字段结构体和联合**，but程序跑太慢了~（最后一个数据大概有 $4 \times 10^6$ 个）

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/2.png)

#### 1.2 输入加速

算法考试里常用的使用`getchar()`进行输入加速（也可以试试`fread()`哟），终于是快起来了（天翼3G太快啦~）。

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/3.png)

#### 1.3 再次加速

速度跑的还是太慢了，影响后面线性分析的效率，所以又回来重写一波~

听到大佬说打表跑得飞快，那我就不客气咯，遂即打了一个65536大小的表，果然起飞~~~（但与此同时，代码也飙升至4000+行，都是小问题~）

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/4.png)

## 2.线性分析

#### 2.1 找链！！！

这个我真要吐血了~~

怎么找都不行~~~~

暴力穷举了大半天（8输入8输出），失败~~~~

辉佬NB，这条链真的猛！辉佬yyds（这链12位输出，怪不得我穷举半天都穷举不到 T_T ）

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/5.png)

这条链是12位输出的话那就要先算出其他8位再来算这条链~

#### 2.2 写代码

然并卵 T_T  超时！！！！遂即当场重写SPN T_T  （此时心态爆炸）

重写起飞，跑得飞快，芜湖~~~

## 3.差分分析

通过了线性分析，差分分析就是个dd（口头虽然这么说， 但是链也是找了我半天 T_T）

#### 3.1 找条链！

这个由于测试样例的原因，就算找到链质量一般也能过~~， 亲测下面这条链能过~

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/6.png)

#### 3.1 写代码

没啥，在线性分析的基础上随便改改hhh

## 4.SPN加强

#### 4.1 初次加强

直接使用之前的SPN，然后套用CBC模式（想偷懒），然而。。。。过不了（过不了随机性检测 T_T ， CTR模式也不行 T_T ）

#### 4.2 再次加强

把密钥加长到了128位，SPN加密长度加长到了64位（原始SPN的四倍），简单的换了一个P盒

果然效果爆炸，CBC模式瞎改初始向量即可~~，芜湖

