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
		double m_MainFreq;	//��Ƶ����λGHz
		int m_CoreNum;		//������
		double m_Power;		//���ʣ���λ��W

public:
		CPU(double MainFreq, int CoreNum, double Power);
		double GetMainFreq(void)const;	//��ȡ��Ƶ
		CPU& operator++();	//ǰ��������Ƶ��0.1����������2�����ʼ�1.0
		CPU operator++(int);	//������������ͬ��
		friend ostream& operator<<(ostream& Out, const CPU& Obj);	//���CPU�Ĳ�����4
														//��Ƶռ6�У�С�����ֱ���2λ�������
														//������ռ3�У������
														//����ռ6�У�С�����ֱ���1λ�������
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

CPU CPU::operator++(int)	//������������ͬ��
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
	int m_Memory;	//�ڴ���������λ��G
	int m_HD;		//Ӳ����������λ��G

public:
	Computer(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD);
	CPU GetCPU(void)const;		//��ȡCPU����
	double GetMemory(void)const;	//��ȡ�ڴ�����
	Computer& operator++();	//ǰ������CPU������������ͬCPU�࣬�ڴ�����4G��Ӳ������128G
	Computer operator++(int);	//������������ͬ��
	friend ostream& operator<<(ostream& Out, const Computer& Obj);	//��Ե���������ڵ�ȡ�����Ĳ�ͬ����һ���������԰�������ں��� 
//CPU�������ݵ����������CPU���ж�����ͬ
											//�ڴ�����ռ6�У������
											//Ӳ������ռ8�У������
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
		int m_ProtectGrade;		//�����ȼ�
		static int m_Counts;	//���ػ�����

public:
		IPC(double CPU_MainFreq=3.7, int CPU_CoreNum=6, double CPU_Power=95.0, int Memory=16, int HD=512, int ProtectGrade=65);
		IPC(const IPC& Obj);
		double GetProtectGrade(void)const;	//��ȡ�����ȼ�
		static int GetCounts(void);	//��ȡ��ǰ���ػ�����
		IPC& operator++();		//ǰ������Computer������������ͬ�ϣ������ȼ���1
		IPC operator++(int);	//������������ͬ��
		friend ostream& operator<<(ostream& Out, const IPC& Obj);	
//Computer�������ݵ����������Computer���ж�����ͬ
							//�����ȼ�ռ5�У������
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
	Computer& temp(*this);//////////////����ֱ��ǿ������ת�������������Ĳ���ԭ�����Ƿݣ����ǿ���
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
	cout<<"��ǰ���ػ�̨��: "<<IPC::GetCounts()<<endl;
	SortIPC(A);
	IncreaseIPC(A);
	cout<<"��ǰ���ػ�̨��: "<<IPC::GetCounts()<<endl;
	OutputIPCFile(A,"d:\\res.txt");

	IPC t1;

	cout<<t1<<endl;
	cout<<t1++<<endl;
	cout<<t1<<endl;
	cout<<"��ǰ���ػ�̨��"<<IPC::GetCounts()<<endl;

	IPC t2(t1);

	cout<<t2<<endl;
	cout<<"��ǰ���ػ�̨��"<<IPC::GetCounts()<<endl;
}
