#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm> 
using namespace std;


class CGoods
{
private:
	int m_num;	//��Ʒ���
	string m_name;	//��Ʒ����
	float m_price;	//��Ʒ�۸�

public:
	CGoods (int, const string&, float);
	friend ostream& operator<<(ostream&, const CGoods&);
//��Ʒ���ơ���Ʒ��ź���Ʒ�۸����ʾ��ʽ��Ҫ��Ϊռ10�С��Ҷ���
};

CGoods::CGoods (int num, const string&name, float price)
{
	m_num=num;
	m_name=name;
	m_price=price;
}

ostream& operator<<(ostream& out, const CGoods& temp)
{
	out.flags(ios::right);
	out.width(10);
	out<<temp.m_num;
	out.flags(ios::right);
	out.width(10);
	out<<temp.m_name;
	out.flags(ios::right);
	out.width(10);
	out<<temp.m_price;
	return out;
}

class CRouter:public CGoods
{
	float m_Frequency;
	int m_Channels;//�˿����� 
public:
	CRouter(int num=1,string name="M8",float price=100.0,float fre=2.4,int cha=8):
		CGoods(num,name,price)
	{
		m_Frequency=fre;
		m_Channels=cha;
	}
	float GetFrequency() const
	{
		return m_Frequency;
	}
	int GetChannels() const
	{
		return m_Channels;
	}
	CRouter operator++()
	{
		m_Channels++;
		return *this;
	}
	CRouter operator++(int)
	{
		CRouter temp(*this);
		m_Channels++;
		return temp;
	}
	friend ostream& operator<<(ostream &out,const CRouter &temp);
};

ostream& operator<<(ostream &out,const CRouter &temp)
{
	out<<CGoods(temp);//CGoods &neww(temp)      out<<temp;
	out.flags(ios::right);
	out.width(10);
	out<<temp.m_Frequency;
	out.flags(ios::right);
	out.width(10);
	out<<temp.m_Channels;
	return out;
}



void ReadData(vector<CRouter> &s,string ss)
{
	int num;	
	string name;
	float price;
	float Frequency;
	int Channels;
	ifstream infile(ss);
	if(!infile.is_open())return;
	
	while(infile>>num>>name>>price>>Frequency>>Channels)
	{
		CRouter temp(num,name,price,Frequency,Channels);
		s.push_back(temp);
	}
}

void DisplayData(const vector<CRouter> &s)
{
	int l=s.size();
	for(int i=0;i<l;i++)
	{
		cout<<s[i]<<endl;
	}
}
CRouter FindMax(vector<CRouter> &s)
{
	sort(s.begin(),s.end(),[](CRouter x,CRouter y)
	{
		return x.GetFrequency()*x.GetChannels()>y.GetFrequency()*y.GetChannels();
	});
	return s[0];
}

int main()
{
	vector<CRouter> s;

	ReadData(s,"D:\\data.txt");
	cout<<"��ȡ��ɺ������Ϊ"<<endl;
	DisplayData(s);

	CRouter t;
	cout<<endl<<"·��������ĳ�ʼֵΪ"<<endl<<t<<endl;

	t=FindMax(s);
	cout<<endl<<"�˻���������Ԫ��Ϊ"<<endl<<t<<endl;

	cout<<endl<<"�˻���������Ԫ�ؽ��������������ֱ�����:"<<endl;
	cout<<t++<<endl;
	cout<<t<<endl;

	cout<<++t<<endl;
	cout<<t<<endl;
}	
