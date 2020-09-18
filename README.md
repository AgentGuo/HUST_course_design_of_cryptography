# HUST_2018级密码学课程设计

## 1.SPN

就是如图所示的一个过程！

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/1.png)

#### 1.1 初次写SPN

[初代SPN](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/SPN)

为了方便的使用S盒P盒的那些运算（直接使用数组， 而不使用位运算），所以想起了C语言课上学的**字段结构体和联合**，but程序跑太慢了~（最后一个数据大概有 $4 \times 10^6$ 个）

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/2.png)

#### 1.2 输入加速

算法考试里常用的使用`getchar()`进行输入加速（也可以试试`fread()`哟），终于是快起来了（天翼3G太快啦~）。

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/3.png)

#### 1.3 再次加速

[二代SPN](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/SPN_v2)

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

[一代线性分析](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/linearAnalysis)

[二代线性分析](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/linearAnalysis_v2)

然并卵 T_T  超时！！！！遂即当场重写SPN T_T  （此时心态爆炸）

重写起飞，跑得飞快，芜湖~~~

## 3.差分分析

[差分分析](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/differentialAnalysis)

通过了线性分析，差分分析就是个dd（口头虽然这么说， 但是链也是找了我半天 T_T）

#### 3.1 找条链！

这个由于测试样例的原因，就算找到链质量一般也能过~~， 亲测下面这条链能过~

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/6.png)

#### 3.1 写代码

没啥，在线性分析的基础上随便改改hhh

## 4.SPN加强

[SPN加强](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/SPN_enhance)

#### 4.1 初次加强

直接使用之前的SPN，然后套用CBC模式（想偷懒），然而。。。。过不了（过不了随机性检测 T_T ， CTR模式也不行 T_T ）

#### 4.2 再次加强

把密钥加长到了128位，SPN加密长度加长到了64位（原始SPN的四倍），简单的换了一个P盒

果然效果爆炸，CBC模式瞎改初始向量即可~~，芜湖

## 5.RSA参数计算

[RSA参数计算](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/RSAParameterCalculation) 这个项目是再ubuntu使用vscode完成的（由于windows半天都没有装好gmp库）

#### 5.1 素性检测(Miller-Rabin算法)

密码学全忘光光了啊 T_T , 看会视频复习一下～

总算是搞懂了，冲冲冲！

#### 5.2 gcd实现

强行手动实现一波，其实也不难，辗转相除法，三下五除二，搞定～

#### 5.3 求逆

感觉是核心过程了，加油！

写是写好了，但是对于错误情况还有的没有考虑到，p-1,q-1过于平滑？这是啥？？（开始翻资料！！）

#### 5.4 光滑的判断

p-1和q-1过于光滑就是gcd(p-1, q-1)不是太大？

学到了学到了，也是终于把这个写好了～芜湖～～

## 6.模重复平方&中国剩余定理

[模重复平方&中国剩余定理](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/modularRepeatedSquare)

从室友那里搞来了一个vs工程文件，终于能在win下跑gmp库了，舒服了舒服了(^_^)

主要就是一个计算`a^e(mod N)`的过程，但是是用于RSA加密过程，给出参数`e, m, p, q`（分别为加密密钥，明文，参数p，q），所以还需要配合使用中国剩余定理进行计算~

芜湖，这算是写的最轻松的一个课设了，一遍过，起飞~~ (^_^)

## 7.综合5,6，完整实现RSA加密与解密过程

但是这里的解密过程不是真正的解密过程，这里是使用p，q并运用中国剩余定理解密的（实际情况不会这么解密~）

啊啊啊，还以为综合5,6能够轻松秒杀T_T，跑得不够快，唉~

突然想起老师提到的Montgomery算法，因该就是他了，然而都忘光光了，复习T_T~

啊啊啊，下一题就是Montgomery算法，那我这题咋过，好像Montgomery算法自己写的话也没有快多少，心态爆炸