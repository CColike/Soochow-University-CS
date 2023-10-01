#include<fstream>
#include<cmath>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<vector>
#include<algorithm>   //sort
using namespace std;

class CPU
{
private:
		double m_MainFreq;	//主频，单位GHz
		int m_CoreNum;		//核心数
		double m_Power;		//功率，单位：W

public:
		CPU(double MainFreq, int CoreNum, double Power);
		double GetMainFreq(void)const;	//获取主频
		CPU& operator++();	//前自增，主频加0.1，核心数加2，功率加1.0
		CPU operator++(int);	//后自增，规则同上
		friend ostream& operator<<(ostream& Out, const CPU& Obj);	//输出CPU的参数，4
														//主频占6列，小数部分保留2位，左对齐
														//核心数占3列，左对齐
														//功率占6列，小数部分保留1位，左对齐
};

CPU::CPU(double MainFreq, int CoreNum, double Power)
{
	m_MainFreq=MainFreq;
	m_CoreNum=CoreNum;
	m_Power=Power;
}


double CPU::GetMainFreq(void)const	
{
	return m_MainFreq;
}

CPU& CPU::operator++()
{
	m_MainFreq+=0.1;
	m_CoreNum+=2;
	m_Power+=1.0;
	return *this;
}

CPU CPU::operator++(int)	//后自增，规则同上
{
	CPU neww(m_MainFreq,m_CoreNum,m_Power);
	m_MainFreq+=0.1;
	m_CoreNum+=2;
	m_Power+=1.0;
	return neww;
}

ostream& operator<<(ostream& Out, const CPU& Obj)
{
	Out.flags(ios::left);
	Out.width(6);
	Out.precision(2);
	Out.setf(ios::fixed);
	Out<<Obj.m_MainFreq;
			
	Out.flags(ios::left);
	Out.width(3);
	Out<<Obj.m_CoreNum;
			
	Out.flags(ios::left);
	Out.width(6);
	Out.precision(1);
	Out.setf(ios::fixed);
	Out<<Obj.m_Power;
	return Out;
}

class Computer
{
private:
	CPU m_CPU;
	int m_Memory;	//内存容量，单位：G
	int m_HD;		//硬盘容量，单位：G

public:
	Computer(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD);
	CPU GetCPU(void)const;		//获取CPU数据
	double GetMemory(void)const;	//获取内存容量
	Computer& operator++();	//前自增，CPU部分自增规则同CPU类，内存扩大4G，硬盘扩大128G
	Computer operator++(int);	//后自增，规则同上
	friend ostream& operator<<(ostream& Out, const Computer& Obj);	//有缘的区别在于调取参数的不同，多一个自身，可以把自身放在后面 
//CPU部分数据的输出规则与CPU类中定义相同
											//内存容量占6列，左对齐
											//硬盘容量占8列，左对齐
};

Computer::Computer(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD):
	m_CPU(CPU_MainFreq,CPU_CoreNum,CPU_Power)
{
	m_Memory=Memory;
	m_HD=HD;
}

CPU Computer::GetCPU(void)const
{
	return m_CPU;
}

double Computer::GetMemory(void)const
{
	return m_Memory;
}

Computer& Computer::operator++()
{
	m_CPU++;
	m_Memory+=4;
	m_HD+=128;
	return *this;
}

Computer Computer::operator++(int)
{
	Computer temp(*this);
	m_CPU++;
	m_Memory+=4;
	m_HD+=128;
	return temp;
}

ostream& operator<<(ostream& Out, const Computer& Obj)
{
	Out<<Obj.m_CPU;
	Out.flags(ios::left);
	Out.width(6);
	Out<<Obj.m_Memory;
	Out.flags(ios::left);
	Out.width(8);
	Out<<Obj.m_HD;
	return Out;
}




class IPC:public Computer
{
private:
		int m_ProtectGrade;		//防护等级
		static int m_Counts;	//工控机数量

public:
		IPC(double CPU_MainFreq=3.7, int CPU_CoreNum=6, double CPU_Power=95.0, int Memory=16, int HD=512, int ProtectGrade=65);
		IPC(const IPC& Obj);
		double GetProtectGrade(void)const;	//获取防护等级
		static int GetCounts(void);	//获取当前工控机数量
		IPC& operator++();		//前自增，Computer数据自增规则同上，防护等级加1
		IPC operator++(int);	//后自增，规则同上
		friend ostream& operator<<(ostream& Out, const IPC& Obj);	
//Computer部分数据的输出规则与Computer类中定义相同
							//防护等级占5列，左对齐
		~IPC();
};

IPC::IPC(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD, int ProtectGrade):
	Computer(CPU_MainFreq,CPU_CoreNum,CPU_Power,Memory,HD),
	m_ProtectGrade(ProtectGrade)
{	
	m_Counts++;
}

IPC::IPC(const IPC& Obj):
	Computer(Obj)
{
	m_ProtectGrade=Obj.m_ProtectGrade;
	m_Counts++;
}

double IPC::GetProtectGrade(void)const
{
	return m_ProtectGrade;
}

int IPC::GetCounts(void)
{
	return m_Counts;
}

int IPC::m_Counts=0;
 
IPC& IPC::operator++() /////////////////
{
	Computer& temp(*this);
	temp++;
	this->m_ProtectGrade++;
	return *this;
}

IPC IPC::operator++(int)
{
	IPC cpy(*this);
	Computer& temp(*this);//////////////不能直接强制类型转换，否则自增的不是原本的那份，而是拷贝
	temp++; 
	m_ProtectGrade++;
	return cpy;
}

ostream& operator<<(ostream& Out, const IPC& Obj)
{
	Out<<Computer(Obj);
	Out.flags(ios::left);
	Out.width(5);
	Out<<Obj.m_ProtectGrade;
	return Out;
}

IPC::~IPC()
{
	m_Counts--;
}



void ReadIPCFile(string s,vector<IPC> &A)
{
	int CPU_CoreNum,Memory,HD,ProtectGrade;
	double CPU_Power,CPU_MainFreq;
	ifstream infile(s);
	if(!infile.is_open())
		return;
	while(infile>>CPU_MainFreq>>CPU_CoreNum>>CPU_Power>>Memory>>HD>>ProtectGrade)
	{
		
		IPC neww(CPU_MainFreq,CPU_CoreNum,CPU_Power,Memory,HD,ProtectGrade);
		A.push_back(neww);
	}
	
}

void SortIPC(vector<IPC> &A)
{
	sort(A.begin(),A.end(),[](IPC x,IPC y)
	{
		if(x.GetCPU().GetMainFreq()==y.GetCPU().GetMainFreq())
		{
			return x.GetProtectGrade()<y.GetProtectGrade();
		}
		else
		{
			return x.GetCPU().GetMainFreq()<y.GetCPU().GetMainFreq();
		}
	});
}

void IncreaseIPC(vector<IPC> &A)
{
	int l=A.size();
	for(int i=0;i<l;i++)
	{
		if(Computer(A[i]).GetMemory()<=4)
			++A[i];
	}
}
 
 
void OutputIPCFile(const vector<IPC> &A,string s)
{
	ofstream outfile(s);
	if(!outfile.is_open())return;
	int l=A.size();
	for(int i=0;i<l;i++)
	{
		outfile<<A[i]<<endl;
	}
} 
 
int main()
{
	vector<IPC> A;

	ReadIPCFile("d:\\source.txt", A);
	cout<<"当前工控机台数: "<<IPC::GetCounts()<<endl;
	SortIPC(A);
	IncreaseIPC(A);
	cout<<"当前工控机台数: "<<IPC::GetCounts()<<endl;
	OutputIPCFile(A,"d:\\res.txt");

	IPC t1;

	cout<<t1<<endl;
	cout<<t1++<<endl;
	cout<<t1<<endl;
	cout<<"当前工控机台数"<<IPC::GetCounts()<<endl;

	IPC t2(t1);

	cout<<t2<<endl;
	cout<<"当前工控机台数"<<IPC::GetCounts()<<endl;
}
