#include <iostream>
#include <cstring>
#include <string>
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

int getSectorAQI(string sectorIdCopy)
{
    GasData data = generateMockGasData();

    cout << "\nSector " << sectorIdCopy << " Air Quality Data";
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

void assignCoordinates(Sector &s)
{
    
    if(s.name == "Sector_M")
    {
        s.x = 0;
        s.y = 0;
    }
    else if(s.name == "Sector_W1")
    {
        s.x = -1;
        s.y = 0;
    }
    else if(s.name == "Sector_E1")
    {
        s.x = 1;
        s.y = 0;
    }
    else if(s.name == "Sector_C")
    {
        s.x = 0;
        s.y = 1;
    }
    else if(s.name == "Alt_Route_S")
    {
        s.x = -1;
        s.y = 0;
    }
    else if(s.name == "SW")
    {
        s.x = -1;
        s.y = -1;
    }
    else if(s.name == "SE")
    {
        s.x = 1;
        s.y = -1;
    }
    else if(s.name == "NW")
    {
        s.x = -1;
        s.y = 1;
    }
    else if(s.name == "NE")
    {
        s.x = 1;
        s.y = 1;
    }
    else if(s.name == "N1")
    {
        s.x = 0;
        s.y = 2;
    }
    else if(s.name == "Loading_Bay") 
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

struct EngineData 
{
    int temperature;     
    int vibration;       
    int rpm;             
};


EngineData generateEngineHealthData()
 {
    EngineData data;
    data.temperature = 60 + rand() % 50;    // 60–109 °C
    data.vibration   = rand() % 100;        // 0–99
    data.rpm         = 800 + rand() % 2200; // 800–2999 RPM
    return data;
}

bool checkEngineHealth(EngineData data) 
{
    if (data.temperature > 95 || data.vibration > 70 || data.rpm > 2800) 
    {
        return false;  // unhealthy
    }
    return true;       // healthy
}

void predictMaintenance(EngineData data) 
{
    cout << "\n--- Predictive Maintenance Report ---\n";
    cout << "Temperature: " << data.temperature << " °C\n";
    cout << "Vibration: " << data.vibration << "\n";
    cout << "RPM: " << data.rpm << "\n";

    if (!checkEngineHealth(data))
     {
        cout << "⚠ WARNING: Engine health degrading\n";
        cout << "🔧 Recommendation: Schedule maintenance immediately\n";
    } 
    else
     {
        cout << "✅ Engine status normal\n";
        cout << "🟢 No maintenance required at the moment\n";
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

    for(int i = 0; i < total_users; i++) 
    {
        if(userDatabase[i].checkCredentials(user_name, password)) 
        {
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
            int choice ; 
            cout<<"Choose your operation :-"<<endl<<"1.Check Air Quality"<<endl<<"2.Engine Monitoring System";
            cin>> choice;

            if(choice == 1)
            {
                srand(time(0));
                string sectorIdCopy;
                cout << "\nEnter Sector ID to check air quality: ";
                cin >> sectorIdCopy;
                int aqi = getSectorAQI(sectorIdCopy); 
                checkGasSafety(aqi);
            }
            else if (choice ==2 )
            {
                srand(time(0)); 

                cout << "===== SafeStrike Engine Monitoring System =====\n";

                EngineData engine = generateEngineHealthData();
                predictMaintenance(engine);
            }
            else
            {
                cout<<"Error......";
            }

        } 

        else if(role == "Moderator") 
        {
            int choice ; 
            cout<<"Choose your operation :-"<<endl<<"1.Check Air Quality"<<endl<<"2.Engine Monitoring System";
            cin>> choice;
            if(choice == 1)
            {
                srand(time(0));
                string sectorIdCopy;
                cout << "\nEnter Sector ID to check air quality: ";
                cin >> sectorIdCopy;
                int aqi = getSectorAQI(sectorIdCopy); 
                checkGasSafety(aqi);
            }
            else if (choice ==2 )
            {
                srand(time(0)); 

                cout << "===== SafeStrike Engine Monitoring System =====\n";

                EngineData engine = generateEngineHealthData();
                predictMaintenance(engine);
            }
            else
            {
                cout<<"Error......";
            }
           
        }

         else if(role == "Worker") 
        {
            int choice ; 
            cout<<"Choose your operation :-"<<endl<<"1.Engine Monitoring System";
            cin>> choice;
            if(choice == 1)
            {
                srand(time(0)); 

                cout << "===== SafeStrike Engine Monitoring System =====\n";

                EngineData engine = generateEngineHealthData();
                predictMaintenance(engine);
            }
            else
            {
                cout<<"Error......";
            }
        } 

    }
    return 0;
}
