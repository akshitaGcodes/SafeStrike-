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
    int Id;
    int aqi;
};

struct Minerals
{
    string name; 
    int Id; // coal 1 iron 2 diamond 3 

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
    
    if(s.name == "Sector M") // iron ore 
    {
        s.x = 0;
        s.y = 0;
        s.Id = 2;
    }
    else if(s.name == "Sector W1") //coal 
    {
        s.x = -1;
        s.y = 0;
        s.Id = 1;
    }
    else if(s.name == "Sector E1") // diamond
    {
        s.x = 1;
        s.y = 0;
        s.Id = 1;

    }
    else if(s.name == "Sector C") // diamond 
    {
        s.x = 0;
        s.y = 1;
        s.Id = 1;
    }
    else if(s.name == "Alt Route S") //coal
    {
        s.x = -1;
        s.y = 0;
        s.Id = 1;
    }
    else if(s.name == "SW") // diamond
    {
        s.x = -1;
        s.y = -1;
        s.Id = 3;
    }
    else if(s.name == "SE") // iron ore
    {
        s.x = 1;
        s.y = -1;
        s.Id = 2;
    }
    else if(s.name == "NW") //iron ore 
    {
        s.x = -1;
        s.y = 1;
        s.Id = 2;
    }
    else if(s.name == "NE") //coal
    {
        s.x = 1;
        s.y = 1;
        s.Id = 1;
    }
    else if(s.name == "N1") //admin office 
    {
        s.x = 0;
        s.y = 2;
        s.Id = 0;
    }
    else if(s.name == "Loading Bay") // delivery 
    {
        s.x = 0;
        s.y = -2;
        s.Id = 4;
    }
    else // not in mine 
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
void reportSector(Sector s) {
                    assignCoordinates(s);
                    if(s.x == 99 && s.y == 99) {
                         cout << "Invalid sector: Not in mine.\n";
                         return;
                    }
                 cout << "Sector " << s.name << " coordinates (" << s.x << "," << s.y << ")";
                 if(s.Id == 1) cout << " contains Coal.\n";
                 else if(s.Id == 2) cout << " contains Iron Ore.\n";
                  else if(s.Id == 3) cout << " contains Diamond.\n";
                  else if(s.Id == 0) cout << " is Admin Office.\n";
                   else if(s.Id == 4) cout << " is Loading Bay.\n";
}
int calculateDistance(Sector a, Sector b)
{
    
    return abs(a.x - b.x) + abs(a.y - b.y);
}
Sector findGreenRoute(Sector current, Sector route1, Sector route2)
{
    
    if(route1.aqi > 200)
        return route2;

    if(route2.aqi > 200)
        return route1;

    
    int d1 = calculateDistance(current, route1);
    int d2 = calculateDistance(current, route2);

    if(d1 <= d2)
        return route1;
    else
        return route2;
}
Sector switchToAlternativeRoute(Sector mainRoute, Sector alternativeRoute)
{
    if(mainRoute.aqi > 200)
    {
        return alternativeRoute;
    }
    return mainRoute;
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

    Minerals MineralInMine[] = {
                                {"Coal", 1},
                                {"Iron Ore", 2},
                                {"Diamond", 3}
};


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
            cout<<"Choose your operation :-"<<endl<<"1.Check Air Quality"<<endl<<"2.Engine Monitoring System"<<endl;
            cin>> choice;

            if(choice == 1)
            {
                srand(time(0));
                string sectornameCopy;
                cout << "\nEnter Sector Name to check air quality: ";
                cin.ignore(1000, '\n'); 
                getline(cin, sectornameCopy);
                int aqi = getSectorAQI(sectornameCopy); 
                checkGasSafety(aqi);
            }
            else if (choice ==2 )
            {
                srand(time(0)); 

                cout << "===== SafeStrike Engine Monitoring System =====\n";

                EngineData engine = generateEngineHealthData();
                predictMaintenance(engine);
            }
            else if(choice==3)
            {
              void reportSector(Sector s);           
          }
            else
            {
                cout<<"Error......";
            }

        } 

        else if(role == "Moderator") 
        {
            int choice ; 
            cout<<"Choose your operation :-"<<endl<<"1.Check Air Quality"<<endl<<"2.Engine Monitoring System"<<endl;
            cin>> choice;
            if(choice == 1)
            {
                srand(time(0));
                string sectornameCopy;
                cout << "\nEnter Sector Name to check air quality: ";
                cin.ignore(1000, '\n'); 
                getline(cin, sectornameCopy);
                int aqi = getSectorAQI(sectornameCopy); 
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
            cout<<"Choose your operation :-"<<endl<<"1.Engine Monitoring System"<<endl;
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
