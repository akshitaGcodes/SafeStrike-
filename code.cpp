#include <iostream>
#include <cstring>
using namespace std;

class User 
{
    private:
    string password;

    public:
        string username;
        string role;

        User(string u, string p, string r)
        {
            username = u;
            password = p;
            role = r;
        }

        bool checkCredentials(string u, string p) 
        {
            return (u == username && p == password);
        }
};

int main() 
{

    User userDatabase[] = {
        User("Akshita_G", "AG.007", "Admin"),
        User("Deepanshi_G", "DG.99", "Moderator"),
        User("Adhya_J", "AJ.27", "Moderator"),
        User("Akshita_D", "AD.2024", "Moderator"),
        User("Priyan_S", "PS.n404", "Admin"),
        User("123", "123", "Worker")
    };
    int total_users = 6;

    string user_name, password;
    cout << "Welcome to SafeStrike" << endl;
    cout << "Please enter your login credentials." << endl;
    cout << "UserName : ";
    cin >> user_name;
    cout << "Password : ";
    cin >> password;

    bool accessGranted = false;
    string role;

    for(int i = 0; i < total_users; i++) {
        if(userDatabase[i].checkCredentials(user_name, password)) {
            accessGranted = true;
            role = userDatabase[i].role;
            break;
        }
    }

    if(!accessGranted) 
    {
        cout << "Invalid Credentials !!. Please try again" << endl;
    } 
    else 
    {
        cout << "\nAccess Granted!" << endl;
        cout << "Welcome " << user_name << " (" << role << ") to the SafeStrike Dashboard!!" << endl;

        if(role == "Admin") 
        {
            //full access 
        } 
        else if(role == "Moderator") 
        {
            //partial access 
        }
         else if(role == "Worker") 
         {
            ////limited access 
        } 

    }

    return 0;
}
