#include "globle.h"

//静态成员变量初始化
//***************系统设置************
//unsigned char SysParam::UpdateFrame = 0;					// 更新标记

unsigned char SysNetParam::IpTerminal[16] = {};				// 终端IP
unsigned char SysNetParam::NetMask[16] = {};				//  终端NETMASK
unsigned char SysNetParam::GateWay[16] = {};				//  终端GETWAY
unsigned int  SysNetParam::PortTerminal = 0;						//  终端PORT
unsigned char SysNetParam::IpCenter[16] = {};					//  中心IP
unsigned int  SysNetParam::PortCenter = 0;					//  主站PORT

unsigned char SysParam::StationCode[10] = {};				// 站编码
unsigned char SysParam::PassWord[8] = {};					// 密码

unsigned int SysParam::UploadIntervalTime = 0;			// 上报间隔时间
unsigned char SysParam::AccountDay = 0;					// 结算日期

unsigned char SysParam::ParaFileVer = 0;					// 系统配置文件版本
unsigned char SysParam::SaveVer = 0;						// 保存数据版本，用于上传数据更新

unsigned char SysParam::DebugState = 0;					// 调试状态

unsigned int SysParam::InputTime[6] = {};					// 投入时间  年月日时分秒
unsigned char SysParam::InputFlag = 0;					// 投入标记，超过投入标记才可结算效益
unsigned char SysParam::ClearFlag = 0;					// 清零标记，在到投入时刻时，数据清零
unsigned char SysParam::AccountFirstFlag = 0;				// 第一次结算标记

unsigned char SysParam::CenterConnectMode = 0;			// 中心连接方式  0-COM  1-TCP

//***************运行计划************
char RunPlan::ParaFileVer = 0;  //配置文件版本
//BE_Time runplan::TimePeak[3] = {{0,0,0,0},{0,0,0,0},{0,0,0,0}};
//BE_Time runplan::TimeValley = {0,0,0,0};
//BE_Time runplan::TimeBp[3] = {{0,0,0,0},{0,0,0,0},{0,0,0,0}};
BE_Time RunPlan::TimePeak[3] = {{1,1,1,1},{1,1,1,1},{1,1,1,1}};
BE_Time RunPlan::TimeValley = {1,1,1,1};
BE_Time RunPlan::TimeBp[3] = {{1,1,1,1},{1,1,1,1},{1,1,1,1}};

double RunPlan::PressNonPlan = 0;        //非计划压力
double RunPlan::PressLocalPeak = 0;      //本地峰压力
double RunPlan::PressLocalVally = 0;     //本地谷压力
double RunPlan::PressLocalFlat = 0;      //本地平压力

double RunPlan::PressRemotePeak = 0;      //远端峰压力
double RunPlan::PressRemoteVally = 0;     //远端谷压力
double RunPlan::PressRemoteFlat = 0;      //远端平压力
unsigned char RunPlan::BpControlValid = 1;   //变频控制有效


//***************电表数据****************
double DbData::Ua = 0;								// 电压
double DbData::Ub = 0;
double DbData::Uc = 0;
double DbData::Ia = 0;								// 电流
double DbData::Ib = 0;
double DbData::Ic = 0;
double DbData::Power = 0;								// 功率
double DbData::BiaoDi = 0;								// 表底
double DbData::Factor = 0;								//因数
unsigned char DbData::OnlineFlag = 0;					// 在线状态
unsigned char DbData::ChangeFlag;                //换表标志

//***************流量计数据**********
double LljData::PV = 0;//瞬时流量
double LljData::F_BiaoDi = 0;//正向表底
double LljData::R_BiaoDi = 0;//负向表底
unsigned char LljData::OnlineFlag = 1;//在线状态
unsigned char LljData::ChangeFlag = 0;       //换表标志







globle *globle::m_instance = 0;

//单例模式
globle *globle::get_instance()
{
    if(m_instance == 0)
        m_instance = new globle();
    return m_instance;
}



globle::globle()
{
}
