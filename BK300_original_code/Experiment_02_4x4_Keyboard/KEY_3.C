/********************************************************************************************
* 实验二:   独立按键实验
* CPU型号： PIC16F877A 
* 晶振：    4MHz 
* 说明:     独立按键K17 K18 K19 K20按下时数码管分别显示S-17，S-18，S-19，S-20
* 作    者：MCU2000
* 日    期：2012年10月19日
本例程在<<BK300 PIC实验板>>上调试通过
*********************************************************************************************/
#include <pic.h>	      //包含PIC头文件 软件自带的头文件可以用< >
#include "BoardConfig.h"  //包含开发板硬件初始化头文件 自已写的头文件用" " 否测PICC编译会出错
__CONFIG(0x3F32);         //芯片配置字

void LED_DISPLAY(void);   //数码管显示子函数
void delay(uchar a,uchar i);
uchar LED_DIS[5]={0X92,0Xbf,0Xc0,0Xc0};      //数码管段码S-00

/********************************************************************************************
函数名称: main
功    能: 函数
参    数: 
返回值  : 无
/*******************************************************************************************/
void main (void)
{
   uchar key;
   
   Board_init();     //调用开发板硬件初始化函数
   
   TRISB=0X0F;       //RB0-RB3设为输入检测按键
   PORTB=0X0F;       //使能内部上拉
   OPTION&=0x7f;     //使能内部上拉 （使用按键时需加这两个语句使能内部上拉)

   ADCON1=0X00;
  
   while(1)
   {
          key=PORTB & 0X0F;              //读取RB0-RB3的电平
          if(key !=0x0F)                 //判断有无按键
          {
                switch(key)
                {
                case  0x0E:              //按键K17
                   LED_DIS[2]=0Xf9;      //数码管字符1的段码
                   LED_DIS[3]=0XF8;      //数码管字符7的段码
                   break;
                case  0x0D:              //按键K18
                   LED_DIS[2]=0Xf9; 
                   LED_DIS[3]=0X80;
                   break;
                case  0x0B:              //按键K19
                   LED_DIS[2]=0Xf9; 
                   LED_DIS[3]=0X90;
                   break;
                case  0x07:              //按键K20
                   LED_DIS[2]=0XA4; 
                   LED_DIS[3]=0XC0;
                   break;
                }
           }
           LED_DISPLAY();                //调用数码管显示子程序
     }
}

/********************************************************************************************
函数名称: LED_DISPLAY
功    能: 数码管显示子函数
参    数: 
返回值  : 无
/*******************************************************************************************/

void LED_DISPLAY(void)
{
     uchar i,TEMP;
     RA3=0;                      //U3输出使能
     TEMP=0X80;
     for(i=0;i<4;i++)
     {
     
//****************数码管位码****************************************************
     RC4=1;                      //U3锁存端设为高电平输出端电平随输入端而变化
     PORTD=TEMP;                 //送数码管位码
     RC4=0;                      //U3锁存端设为低电平输出端不变
//******************************************************************************     

//****************数码管段码****************************************************
     RC3=1;
     PORTD=LED_DIS[i];
     RC3=0;
//******************************************************************************

     TEMP>>=1;                 //右移一位准备下一位数码管显示
     delay(10,10);             //延时一会提高数码管显示亮度
   
//****************关闭数码管显示************************************************
     RC4=1; 
     PORTD=0X00;              //位选输出高电位关闭显示 （数码管是4位共阳的)
     RC4=0;                   //
     delay(1,10);
//******************************************************************************     
     }
   
}

/********************************************************************************************
函数名称: delay
功    能: 延时子函数
参    数: uchar a,uchar i
返回值  : 无
/*******************************************************************************************/
////////////延时子函数/////////////////
void delay(uchar a,uchar i)
{	
     while(--a)
     while(--i);
}

