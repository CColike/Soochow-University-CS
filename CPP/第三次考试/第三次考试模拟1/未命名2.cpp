#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<fstream>
#include<algorithm>
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
		if (Sex < 0 || Sex>1)
		{
			cout << "性别初始值" << Sex << "不符合要求！" << endl;
			exit(0);
		}
		if (Age <= 0)
		{
			cout << "年龄初始值" << Age << "不符合要求！" << endl;
			exit(0);
		}
		m_ID = ID;
		m_Name = Name;
		m_Sex = Sex;
		m_Age = Age;
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
		Out << right << setw(5) << Obj.m_ID;
		Out << right << setw(10) << Obj.m_Name;
		Out << right << setw(5) << Obj.m_Sex;
		Out << right << setw(6) << Obj.m_Age;
		return Out;
	}
};
class CBenchWorker :public CWorker
{
private:
	int m_Grade;
public:
	CBenchWorker(int id = 0, string name = "No Name", int sex = 1, int age = 18, int grade = 1):CWorker(id, name, sex, age) 
	{
		m_Grade = grade;
	}
	int GetGrade() 
	{
		return m_Grade;
	}
	friend CBenchWorker& operator++(CBenchWorker& c);
	friend ostream& operator<<(ostream& cout, const CBenchWorker& c);
};
CBenchWorker& operator++(CBenchWorker& c) {
	c.m_Grade++;
	return c;
}
ostream& operator<<(ostream& cout, const CBenchWorker& c) {
	cout << CWorker(c);
	cout << right << setw(5) << c.m_Grade;
	return cout;
}
int ReadData(string filename,vector<CBenchWorker>&a) {
	ifstream ifs;
	ifs.open(filename, ios::in);
	int id, sex, age, grade;
	string name;
	if (!ifs.is_open()) {
		cout << "文件打开失败";
		return 0;
	}
	else {
		while (ifs >> id >> name >> sex >> age>>grade) {
			CBenchWorker b(id, name, sex, age,grade);
			a.push_back(b);
		}
	}
	ifs.close();
	return 1;
}
void DisplayData(const vector<CBenchWorker> &a) {
	for (int i = 0;i < a.size();i++) {
		cout << a[i] << endl;
	}
}
void InecData(vector<CBenchWorker>& a) {
	for (int i = 0;i < a.size();i++) {
		++a[i];
	}
}
int DelData(vector<CBenchWorker> &a,int x,int y) {
	int count = 0;
	for (int i = 0;i < a.size();) {
		if (a[i].GetAge() >= x && a[i].GetGrade() <= y) {
			a.erase(a.begin()+i);
			count++;
		}
		else {
			i++;
		}
	}
	return count;
}
int judge(string a, string b) {
	int flag = 0;
	if (a.length() < b.length()) {
		return 0;
	}
	else {
		int j = 0;
		while (j < a.length() - b.length()) {
			for (int i = 0;i < b.length();i++) {
				if (tolower(b[i]) == tolower(a[j])) {
					j++;
				}
				else {
					break;
				}
				flag = 1;
			}
			j++;
		}
	}
	return flag;
}
int DelData(vector<CBenchWorker>& a, string word) {
	int count = 0;
	for (int i = 0;i < a.size();) {
		if (judge(a[i].GetName(), word) == 1) {
			a.erase(a.begin() + i);
			count++;
		}
		else{
			i++;
		}
	}
	return count;
}
bool cmp(CBenchWorker w1, CBenchWorker w2) {
	if (w1.GetSex() < w2.GetSex()) {
		return w1.GetSex() < w2.GetSex();
	}
	else {
		if (w1.GetSex() == 0 && w2.GetSex() == 0) {
			return w1.GetGrade() > w2.GetGrade();
		}
		else {
			return w1.GetGrade() < w2.GetGrade();
		}
	}
}
void SortData(vector<CBenchWorker>& a) {
	sort(a.begin(), a.end(), cmp);
}
int WriteData(string filename,const vector<CBenchWorker>& a) {
	ofstream ofs;
	ofs.open(filename, ios::out);
	if (!ofs.is_open()) {
		return 0;
	}
	for (int i = 0;i < a.size();i++) {
		ofs << a[i] << endl;
	}
	ofs.close();
	return 1;
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
