#include <iostream>
#include <cstring>
using namespace std;

int passwordChecker(char name[50] , char password[50])
{
    if(strcmp(name, "ak") == 0)
    {
        if (strcmp(password, "ak") == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    
}
int main()
{
    char user_name[100];
    char password[100];
    cout<<"Welcome to SafeStrike"<<endl;

    cout<<"Please enter your login credentials."<<endl;
    cout<<"UserName : ";
    cin>>user_name;
    cout<<"Password : ";
    cin>>password;
    if(!(passwordChecker(user_name,password)))
    {
        cout<<"Invalid Credentials !!. Please try again"<<endl;
    }
    else
    {
        cout << "\nAccess Granted!" << endl;
        cout << "Welcome " << user_name << " to the SafeStrike Dashboard!!" << endl;

    }


    return 0;
}



