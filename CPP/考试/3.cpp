#include<bits/stdc++.h>
using namespace std;

void ReadFile(string s,vector<string> &A)
{
	ifstream infile(s);//
	string a;
	while(infile>>a)A.push_back(a);
	infile.close();//
}

void ShowData(const vector<string> &A,int x=5,int y=10)
{
	for(int i=0;i<A.size();i++)
	{
		cout.flags(ios::left);//
		cout.width(8);//
		cout<<A[i];//
		//cout<<setiosflags(ios::left)<<setw(y)<<A[i];//
		if((i+1)%x==0)cout<<endl;
	}
}

void StringToInteger(const vector<string> &A,vector<int> &B)
{
	for(int i=0;i<A.size();i++)
	{
		int len=A[i].size(),sum=0;
		for(int j=0;j<len;j++)
		{
			sum+=int(A[i][j]);
		}
		B.push_back(sum);
	}
}

void ShowData(const vector<int> &B,int x=8,int y=6)
{
	for(int i=0;i<B.size();i++)
	{
		cout<<setiosflags(ios::left)<<setw(y)<<B[i];
		if((i+1)%x==0)cout<<endl;
	}
}

void DelMultiInt(vector<int> &B)
{
	for(int i=B.size()-1;i>=0;i--)
	{
		int flag=0;
		for(int j=0;j<i;j++)
		{
			if(B[i]==B[j])
			{
				flag=1;
				break;
			}
		}
		if(flag)B.erase(B.begin()+i);
	}
}




void SortData(vector<int> &B)
{
	sort(B.begin(),B.end(),[](int a,int b)
	{
	int x=0,y=0;
	while(a!=0)
	{
		x+=a%10;
		a/=10;
	}
	while(b!=0)
	{
		y+=b%10;
		b/=10;
	}
	return x<y;
});
}

void ReadFile(string s,vector<int> &C)
{
	ifstream infile(s);
	int a;
	while(infile>>a)C.push_back(a);
}

void InsertNum(vector<int> &B,const vector<int> &C)
{
	for(int i=0;i<C.size();i++)
	{
		int l=0;
		while(B[l]<C[i]&&l<B.size())l++;
		if(l==B.size()+1) 
		{
			B.push_back(C[i]);
			continue;
		}
		if(C[i]==B[l])continue;
		B.insert(B.begin()+l,1,C[i]);//
	}
}

void WriteFile(string s,const vector<int> &B,int x=8,int y=6)
{
	ofstream outfile(s);
	for(int i=0;i<B.size();i++)
	{
		outfile<<setiosflags(ios::right)<<setw(y)<<B[i];
		if((i+1)%x==0)outfile<<endl;
	}
	outfile.close();
}

int main()
{
	string fname;
	vector<string> A;
	vector<int> B, C;
	
	fname = "d:\\words.txt";
	ReadFile(fname, A);
	cout << "====单词向量A为:====\n";
	ShowData(A);
	cout << endl;

	StringToInteger(A, B);
	cout << "====整数向量B为:====\n";
	ShowData(B, 6);
	cout << endl;

	DelMultiInt(B);
	SortData (B);
	cout << "====删除重复元素并升序排序后的向量B为:====\n";
	ShowData(B, 6, 8);
	cout << endl;

	fname = "d:\\integer.txt";
	ReadFile(fname, C);

	InsertNum(B, C);
	fname = "d:\\result.txt";
	WriteFile(fname, B);

	system("pause");
	return 0;
}
