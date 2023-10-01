#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>    // exit(0)
using namespace std; 

class CWorker
{
private:
	int m_ID; //工号
	string m_Name; //姓名
	int m_Sex; //性别 0代表女性 1代表男性
	int m_Age; //年龄
public:
	CWorker(int ID, string Name, int Sex, int Age)
	{
		if (Sex<0 || Sex>1)
		{
			cout<<"性别初始值"<<Sex<<"不符合要求！"<<endl;
			exit(0);
		}
		if (Age<=0)
		{
			cout<<"年龄初始值"<<Age<<"不符合要求！"<<endl;
			exit(0);
		}
		m_ID=ID;
		m_Name=Name;
		m_Sex=Sex;
		m_Age=Age;
	}
	
	string GetName()const
	{
		return m_Name;
	}
	
	int GetSex()const
	{
		return m_Sex;
	}
	
	int GetAge()const
	{
		return m_Age;
	}
	
	friend ostream& operator<<(ostream& Out, const CWorker& Obj)
	{
		Out<<right<<setw(5)<<Obj.m_ID;
		Out<<right<<setw(10)<<Obj.m_Name;
		Out<<right<<setw(5)<<Obj.m_Sex;
		Out<<right<<setw(6)<<Obj.m_Age;
		return Out;
	}
};


class CBenchWorker:public CWorker
{
	int m_grade;
public:
	CBenchWorker(int id,string name,int sex,int age,int grade):CWorker(id,name,sex,age)
	{
		m_grade=grade;
	}
	
	int GetGrade()const
	{
		return m_grade;
	}
	
	CBenchWorker operator++()
	{
		m_grade++;
		return *this;
	}
	
	friend ostream &operator<<(ostream &out,const CBenchWorker &t);
};

ostream &operator<<(ostream &out,const CBenchWorker &t)
{
	out<<CWorker(t);
	out<<right<<setw(5)<<t.m_grade;
	return out;
}

int ReadData(string s, vector<CBenchWorker> &a)
{
	ifstream infile(s);
	if(!infile.is_open())
		return 0;
	int id,sex,age,grade; string name; 
	while(!infile.eof())
	{
		infile>>id>>name>>sex>>age>>grade;
		CBenchWorker neww(id,name,sex,age,grade);
		a.push_back(neww);
	}
	infile.close();
}

void DisplayData(const vector<CBenchWorker> &a)
{
	int l=a.size();
	for(int i=0;i<l;i++)
	{
		cout<<a[i]<<endl;
	}
}

void InecData(vector<CBenchWorker> &a)
{
	int l=a.size();
	for(int i=0;i<l;i++)
	{
		++a[i];
	}
}

int DelData(vector<CBenchWorker> &a,int age_std,int grade_std)
{
	int l=a.size(),cnt=0;
	for(int i=l-1;i>=0;i--)
	{
		if(a[i].GetAge()>=age_std&&a[i].GetGrade()<=grade_std)
		{
			a.erase(a.begin()+i);
			cnt++;
		}
	}
	return cnt;
}

int DelData(vector<CBenchWorker> &a,string s)
{
	int l=a.size(),cnt=0;
	for(int i=l-1;i>=0;i--)
	{
		string ss=a[i].GetName();
		int flag=0;
		for(int j=0;j<=ss.size()-s.size();j++)
		{
			for(int k=0;k<s.size();k++)
			{
				char x=s[k],y=ss[j+k];
				if(x>='a'&&x<='z')x=x-'a'+'A';
				if(y>='a'&&y<='z')y=y-'a'+'A';
				if(x!=y)
				{
					break;
				}
				if(k==s.size()-1)flag=1;
			}
			if(flag)break;
		}
		if(flag)
		{
			a.erase(a.begin()+i);
			cnt++;
		}
	}
	return cnt;
}

void SortData(vector<CBenchWorker> &a)
{
	sort(a.begin(),a.end(),[](CBenchWorker x,CBenchWorker y)
	{
		int xs=x.GetSex();
		int ys=y.GetSex();
		if(xs!=ys)
		{
			return xs<ys;
		}
		else
		{
			if(xs==0)
			{
				return x.GetGrade()>y.GetGrade();
			}
			else
			{
				return x.GetGrade()<y.GetGrade();
			}
		}
	});
}

int WriteData(string s,const vector<CBenchWorker> &a)
{
	ofstream outfile(s);
	if(!outfile.is_open())return 0;
	int l=a.size();
	for(int i=0;i<l;i++)
	{
		outfile<<a[i]<<endl;
	}
	outfile.close();
}

int main()
{
	vector<CBenchWorker> a;
	int c;

	if (ReadData("d:\\workers.txt", a) == 0)
		return -1;

	cout << "文件读取后一共有 " << a.size() << " 条钳工数据：" << endl;
	DisplayData(a);

	InecData(a);

	c = DelData(a, 55, 2);	//第2个参数为年龄，第3个参数为等级
	cout << endl << "第1次删除了" << c << "个钳工数据" << endl;

	c = DelData(a, "Tom");
	cout << endl << "第2次删除了" << c << "个钳工数据" << endl;

	SortData(a);

	cout << endl << "上述流程结束后一共有 " << a.size() << " 条钳工数据：" << endl;
	DisplayData(a);

	if (WriteData("d:\\res.txt", a) == 0)
		return -1;
	cout << endl << "文件保存成功" << endl << endl;
}
