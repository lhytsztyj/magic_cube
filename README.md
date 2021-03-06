复原魔方
=======

编译
-------
`make`： 编译程序到main

`make debug`： 编译程序到main。附加-g -Wall选项。

`make test`： 编译测试程序到test。执行test可自动测试多组随机数据，
并将正在测试的魔方的初始状态dump到dump.txt。

添加-VERBOSE=true可输出冗余信息到stderr

运行
-------
运行main以复原魔方。程序从stdin读入魔方的初始状态，将复原过程输出到
stdout，VERBOSE=true时在stderr打印冗余信息。

读入格式为六个3x3字符矩阵，例如：

```
ROW
WRW
WGY
YYB
WOG
WBO
YYB
OBB
BOG
OGG
GGR
OOR
ORR
BYY
YBG
RRG
WWY
WRB
```

或

```
row
wrw
wgy

yyb
wog
wbo

yyb
obb
bog

ogg
ggr
oor

orr
byy
ybg

rrg
wwy
wrb
```

六个矩阵分别代表*前、后、左、右、上、下*六个面的状态
，其中左、后、右面由前面横向旋转若干次得到，上面由前面向下旋转一次得到，下
面由前面向上旋转一次得到（与结对编程定义相同）。矩阵中的字符r,g,b,w,y,o分
别代表红、绿、蓝、白、黄、橙。

输出将12种操作（F,Fi,L,Li,B,Bi,R,Ri,U,Ui,D,Di，其中无i的为顺时针旋转，有i
的为逆时针旋转，与参考资料相同）输出，每行一个操作。

stderr输出的冗余信息包括输入提示以及读入后、每次操作后的魔方状态。
