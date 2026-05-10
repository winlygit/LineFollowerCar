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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    
     if(huart->Instance == USART1){
    if(value == '@'){
    uart_index = 0;
    ifrxstart = 1;
    }
    
    if(ifrxstart ==1){
    cmd[uart_index++] = value;

    }
    
    if(value == '#'){
        
        rxcplt_flag = 1;
            
    }
    
    HAL_UART_Receive_IT(&huart1,&value,1);
    
}
}
 


void readcmd(uint8_t* cmd){
    if(cmd[0]=='@'&&cmd[1]=='T'&&cmd[9]=='#'){
        if(cmd[2]=='C'&&cmd[3]=='M'&&cmd[4]=='D'){
            if(cmd[5]=='S'&&cmd[6]=='T'&&cmd[7]=='A'&&cmd[8]=='R'){
                start_flag = 1;
                stop_flag = 0;
            }
            if(cmd[5]=='S'&&cmd[6]=='T'&&cmd[7]=='O'&&cmd[8]=='P'){
                start_flag = 0;
                stop_flag = 1;
            }
        }

        if(cmd[2]=='P'&&cmd[3]=='K'&&cmd[4]=='P'){
            Kp = (cmd[5]-'0')*1 + (cmd[6]-'0')*0.1 + (cmd[7]-'0')*0.01+ (cmd[8]-'0')*0.001;
        }
        if(cmd[2]=='P'&&cmd[3]=='K'&&cmd[4]=='D'){
            Kd = (cmd[5]-'0')*1 + (cmd[6]-'0')*0.1 + (cmd[7]-'0')*0.01+ (cmd[8]-'0')*0.001;
        }
        if(cmd[2]=='E'&&cmd[3]=='R'&&cmd[4]=='1'){
            error1 = (cmd[5]-'0')*1000 + (cmd[6]-'0')*100 + (cmd[7]-'0')*10 + (cmd[8]-'0');
        }
        if(cmd[2]=='E'&&cmd[3]=='R'&&cmd[4]=='2'){
            error2 = (cmd[5]-'0')*1000 + (cmd[6]-'0')*100 + (cmd[7]-'0')*10 + (cmd[8]-'0');
        }
        if(cmd[2]=='L'&&cmd[3]=='O'&&cmd[4]=='C'){
            LOCK_CORRECTION = (cmd[5]-'0')*1000 + (cmd[6]-'0')*100 + (cmd[7]-'0')*10 + (cmd[8]-'0');
        }



    }






}





 






