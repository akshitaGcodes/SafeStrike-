#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
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

struct Sector
{
    string name;
    int x;
    int y;
};

void assignCoordinates(Sector &s)
{
    if(s.name == "Sector C")
    {
        s.x = 0;
        s.y = 0;
    }
    else if(s.name == "Sector N1")
    {
        s.x = 0;
        s.y = 1;
    }
    else if(s.name == "Sector S1")
    {
        s.x = 0;
        s.y = -1;
    }
    else if(s.name == "Sector E1")
    {
        s.x = 1;
        s.y = 0;
    }
    else if(s.name == "Sector W1")
    {
        s.x = -1;
        s.y = 0;
    }
    else if(s.name == "Loading Bay")
    {
        s.x = 0;
        s.y = -2;
    }
    else
    {
        
        s.x = 99;
        s.y = 99;
    }
}

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
            srand(time(0));

            int sectorId;
            cout << "\nEnter Sector ID to check air quality: ";
            cin >> sectorId;

            int aqi = getSectorAQI(sectorId);
            checkGasSafety(aqi);
            //full access 
        } 
        else if(role == "Moderator") 
        {
            //partial access 
        }
         else if(role == "Worker") 
         {
            //limited access 
        } 

    }

    return 0;
}

struct GasData
{
    int NO2;
    int SO2;
    int AQI;
};

GasData generateMockGasData()
{
    GasData data;
    data.NO2 = rand() % 200 + 20;
    data.SO2 = rand() % 200 + 20;
    data.AQI = (data.NO2 + data.SO2) / 2;
    return data;
}

int getSectorAQI(int sectorId)
{
    GasData data = generateMockGasData();

    cout << "\nSector " << sectorId << " Air Quality Data";
    cout << "\nNO2: " << data.NO2;
    cout << "\nSO2: " << data.SO2;
    cout << "\nAQI: " << data.AQI << endl;

    return data.AQI;
}

void checkGasSafety(int aqi)
{
    if (aqi <= 100)
        cout << "Status: SAFE" << endl;
    else if (aqi <= 150)
        cout << "Status: MODERATE" << endl;
    else
        cout << "Status: HAZARDOUS" << endl;
}

