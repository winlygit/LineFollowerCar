# 设计一套AT指令

功能：开始循迹，停止循迹，设置pid参数，设置基准速度，设置误差量


格式：@T+指令+参数+#


变量：KP，KI，KD，error1,error2,base,全白脱线速度lock

指令：STAR,STOP,

具体格式：赋值操作的指令为变量名分别为：PKP,PKI,PKD,ER1,ER2,LOC

                  命令操作的指令为CMD,参数为STAR，STOP


赋值时的pid参数格式为一位整数加三位小数，不加小数点，不足位补零。其他参数为四位，不足在前面补零。


例：

控制KP为1.5         指令：@TPKP1500#

控制error1为2      指令：@TER10002#

控制开始循迹       指令：@TCMDSTAR#
