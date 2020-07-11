/*******************************************************************************************
										    声 明
    本项目代码仅供个人学习使用，可以自由移植修改，但必须保留此声明信息。移植过程中出现其他
	
不可估量的BUG，天际智联不负任何责任。请勿商用！

* 程序版本：V1.01
* 程序日期：2018-8-18
* 程序作者：愤怒的小孩
* 版权所有：西安天际智联信息技术有限公司
*******************************************************************************************/
#ifndef _STRUCTCONFIG_H
#define _STRUCTCONFIG_H
#include "stdio.h"
#include "stdint.h"

/************************************************PID参数调试上位机波形显示*************************************************/
/* 如果想观察哪个轴的PID波形，就取消掉哪个注释，但是一次只能取消掉一个注释 */
//#define ROL_PID_DEBUG    
//#define PIT_PID_DEBUG
#define YAW_PID_DEBUG
//#define ALT_PID_DEBUGE
/**************************************************************************************************************************/

/********************************************飞机状态记录组SENSER_OFFSET_FLAG**********************************************/
extern uint8_t   SENSER_OFFSET_FLAG; //标志位组

//每一位对应功能
#define GYRO_OFFSET 0x01 //第一位陀螺仪校准标志位
#define ACC_OFFSET 0x02  //第二位加速度校准标志位


//对 SENSER_OFFSET_FLAG 的位的操作
#define SENSER_FLAG_SET(FLAG)   SENSER_OFFSET_FLAG|=FLAG                //标志位置1
#define SENSER_FLAG_RESET(FLAG) SENSER_OFFSET_FLAG&=~FLAG               //标志位值0
#define GET_FLAG(FLAG)         (SENSER_OFFSET_FLAG&FLAG)==FLAG ? 1 : 0  //获取标志位状态



//三轴整型（MPU6050原始数据）
typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
}INT16_XYZ;

//三轴浮点型
typedef struct
{
	float X;
	float Y;
	float Z;
}FLOAT_XYZ;

//姿态解算后的角度
typedef struct
{
	float rol;
	float pit;
	float yaw;
}FLOAT_ANGLE;

typedef struct
{
	float pit;
	float rol;
	float yaw;
	float X_Acc;
	float Y_Acc;
}MV_measure;

typedef struct
{
	float pit;
	float rol;
	float yaw;
	float X_Acc;
	float Y_Acc;
}SV_preset;

typedef struct
{
	float e_pit_0;
	float e_pit_1;
	float e_rol_0;
	float e_rol_1;
	float e_yaw_0;
	float e_yaw_1;
}e_attitude;

//姿态解算
extern FLOAT_XYZ 	 Gyr_degree,Gyr_rad;	              //把陀螺仪的各通道读出的数据，转换成弧度制 和 度
extern INT16_XYZ   	 MPU6050_ACC_RAW,MPU6050_GYRO_RAW;	  //MPU最新一次原始数据
extern INT16_XYZ	 GYRO_OFFSET_RAW,ACC_OFFSET_RAW;			//MPU零漂值
extern FLOAT_XYZ 	 Acc_filt,Gry_filt;	                  //滤波后的各通道数据
extern float       	 DCMgb[3][3];
extern float       	 Zacc,accb[3];
extern SV_preset	SV;
extern MV_measure	MV;

#endif

