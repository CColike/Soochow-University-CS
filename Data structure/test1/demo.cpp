#include"utility.h"//其中有user_says_yes()等常用的函数
#include"Life.h"

using namespace std;

int main()
{
    Life configuration;
    instructions();
    configuration.initialize();
    configuration.print();
    cout<<"Continue?(Y/N  yes/no  1/0)"<<endl;
    while(user_says_yes())
    {
        configuration.update();
        configuration.print();
        cout<<"Continue?(Y/N  yes/no  1/0)"<<endl;
    }
}