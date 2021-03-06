# HUST_2018级密码学课程设计

## 1.SPN

就是如图所示的一个过程！

![image](https://github.com/AgentGuo/HUST_course_design_of_cryptography/blob/master/image/1.png)

#### 1.1 初次写SPN

[初代SPN](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/SPN)

为了方便的使用S盒P盒的那些运算（直接使用数组， 而不使用位运算），所以想起了C语言课上学的**字段结构体和联合**，but程序跑太慢了~（最后一个数据大概有 $4 \times 10^6$ 个）

#### 1.2 输入加速

算法考试里常用的使用`getchar()`进行输入加速（也可以试试`fread()`哟），终于是快起来了（天翼3G太快啦~）。

#### 1.3 再次加速

[二代SPN](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/SPN_v2)

速度跑的还是太慢了，影响后面线性分析的效率，所以又回来重写一波~

听到大佬说打表跑得飞快，那我就不客气咯，遂即打了一个65536大小的表，果然起飞~~~（但与此同时，代码也飙升至4000+行，都是小问题~）

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

[中国剩余定理](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/RSAEncryptionAndDecryption)

但是这里的解密过程不是真正的解密过程，这里是使用p，q并运用中国剩余定理解密的（实际情况不会这么解密~）

啊啊啊，还以为综合5,6能够轻松秒杀T_T，跑得不够快，唉~

时隔快一周了，我终于能过了，在多位同学的点播下，终于能过了T_T，太不容易了，总结下来主要有三点吧：

1. 避免**重复计算**，有些值在输入完`p`,`q`后是不会改变的（比如p和q的逆），应该用变量将其保存好，避免不必要的计算（感谢黄同学点播^_^）
2. **中国剩余定理加速**，在求解模幂时，要将解密指数`d`模除以`p-1`和`q-1`，这样也能加速计算（感谢黄同学点播^_^）
3. **模除2加速**，模幂运算的过程中需要不对的对指数模除2，直接用除法效率并不高，可以使用`gmp_get_str`先将其转化为二进制字符串，然后再进行平方乘算法（感谢张同学点播^_^）

啊啊啊，太不容易了，枯了，不过总算是能跑快快了，芜湖~

## 8. 蒙哥马利算法

[蒙哥马利算法](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/RSAMontgomery)

要人命！！gmp库居然没有移位运算，直接白给，跑的巨慢无比T_T

都想放弃了，要不世界上库函数吧T_T！

问问带佬咋做的，带佬还是猛，直接没用移位运算，用一个数组存好，直接移动指针，NB！

枯了，昨晚调试到2点，心态崩了，太狗血了，本地`unsigned long`是32位，OJ是64位的，这也太坑爹了。。。

还是睡醒了清醒，大早上半小时BUG就调好了，舒服了舒服了，终于过了，芜湖~~^_^

## 9. PKCS7

这个太简单辣，跳过^_^

## 10. 彩虹表

[彩虹表](https://github.com/AgentGuo/HUST_course_design_of_cryptography/tree/master/rainbowTable)

感觉还是比较简单的，OJ时间卡得也不死，信心满满的开始。。。

PA..PA..总是PA....，时间不早了~ 意料之中的结束T_T，不过还好不是RA~

通过一顿分析老师给的仅有的一个样例，终于找到bug了，又是一波脑淤血操作，100000写成了10000，这bug找了我两小时？？？T_T

不过总蒜过了！芜湖~