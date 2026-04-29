#include "main.h"
#include "uart.h"


/*
******************************************************************************
        本文件用于存放串口驱动函数
        以及串口中断处理
        
        
******************************************************************************
*/


#include "main.h"
#include "uart.h"
#include "global.h"





void U1_printf (const uint8_t* pData ) //向串口1发送数据
{   
   if (pData == NULL){
       return;
   }
   
   uint16_t len = 0;
   while (pData[len] != '\0')
   {
       len++;
   }
   HAL_UART_Transmit_IT(&huart1,pData,len);


}


void readcmd(uint8_t* cmd){
    if(cmd[0]=='A'&&cmd[1]=='T'&&cmd[9]=='#'){
        if(cmd[2]=='C'&&cmd[3]=='M'&&cmd[4]=='D'){

        }

        if()
    }






}





 






