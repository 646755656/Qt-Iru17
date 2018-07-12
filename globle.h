#ifndef GLOBLE_H
#define GLOBLE_H

class BE_Time
{
public:
    unsigned char BgHour;
    unsigned char BgMin;
    unsigned char EndHour;
    unsigned char EndMin;
};


class RunPlan
{
public:
    static char ParaFileVer;  //配置文件版本

    static BE_Time TimePeak[3];       //高峰时间段
    static BE_Time TimeValley;          //谷时间段
    static BE_Time TimeBp[3];          //变频时间段

    static double PressNonPlan;        //非计划压力
    static double PressLocalPeak;      //本地峰压力
    static double PressLocalVally;     //本地谷压力
    static double PressLocalFlat;      //本地平压力

    static double PressRemotePeak;      //远端峰压力
    static double PressRemoteVally;     //远端谷压力
    static double PressRemoteFlat;      //远端平压力

    static unsigned char BpControlValid;   //变频控制有效

};

class SysNetParam
{
//    static unsigned char UpdateFrame;					// 更新标记
public:
    static unsigned char IpTerminal[16];				// 终端IP
    static unsigned char NetMask[16];				//  终端NETMASK
    static unsigned char GateWay[16];				//  终端GETWAY
    static unsigned int  PortTerminal;						//  终端PORT
    static unsigned char IpCenter[16];					//  中心IP
    static unsigned int  PortCenter;					//  主站PORT
};

class SysParam
{
public:
    static unsigned char StationCode[10];				// 站编码
    static unsigned char PassWord[8];					// 密码

    static unsigned int UploadIntervalTime;			// 上报间隔时间
    static unsigned char AccountDay;					// 结算日期

    static unsigned char ParaFileVer;					// 系统配置文件版本
    static unsigned char SaveVer;						// 保存数据版本，用于上传数据更新

    static unsigned char DebugState;					// 调试状态

    static unsigned int InputTime[6];					// 投入时间  年月日时分秒
    static unsigned char InputFlag;					// 投入标记，超过投入标记才可结算效益
    static unsigned char ClearFlag;					// 清零标记，在到投入时刻时，数据清零
    static unsigned char AccountFirstFlag;				// 第一次结算标记

    static unsigned char CenterConnectMode;			// 中心连接方式  0-COM  1-TCP
};

//电表数据
class DbData
{
public:
    static double Ua;								// 电压
    static double Ub;
    static double Uc;
    static double Ia;								// 电流
    static double Ib;
    static double Ic;
    static double Power;								// 功率
    static double BiaoDi;								// 表底
    static double Factor;								//因数
    static unsigned char OnlineFlag;					// 在线状态
    static unsigned char ChangeFlag;                //换表标志
};

//流量计数据
class LljData
{
    static double PV;//瞬时流量
    static double F_BiaoDi;//正向表底
    static double R_BiaoDi;//负向表底
    static unsigned char OnlineFlag;//在线状态
    static unsigned char ChangeFlag;       //换表标志
};

class globle
{
private:
    static globle *m_instance;

public:
    globle();

    static globle *get_instance();



};

#endif // GLOBLE_H
