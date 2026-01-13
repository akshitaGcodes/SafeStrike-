#include <iostream>
#include <cstring>
using namespace std;

int passwordChecker(char name[50] , char password[50])
{
    const char* userDatabase[6][2] = {
                                        {"Akshita_G", "AG.007"},
                                        {"Deepanshi_G", "DG.99"},
                                        {"Adhya_J", "AJ.27"},
                                        {"Akshita_D", "AD2024"},
                                        {"Priyan_S", "PS.n404"},
                                        {"123", "123"} // TESTER 
                                    };
    
    int total_users = 6;

    for(int i = 0; i < total_users; i++) 
    {
        if(strcmp(name, userDatabase[i][0]) == 0) 
        {
            if (strcmp(password, userDatabase[i][1]) == 0) 
            {
                return 1; 
            } 
            else 
            {
                return 0; 
            }
        }
    }
    return 0;
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



