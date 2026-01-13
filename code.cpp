#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// username locking 
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

// sector declaration  - > coordinate + name 
struct Sector
{
    string name; 
    int x;
    int y;
};

//levels 
struct GasData
{
    int NO2;
    int SO2;
    int AQI;
};

//random generator 
GasData generateMockGasData()
{
    GasData data;
    data.NO2 = rand() % 200 + 20;
    data.SO2 = rand() % 200 + 20;
    data.AQI = (data.NO2 + data.SO2) / 2;
    return data;
}

// aqi display 
int getSectorAQI(int sectorId , string sectorIdCopy)
{
    GasData data = generateMockGasData();

    cout << "\nSector " << sectorIdCopy << " Air Quality Data";// error 
    cout << "\nNO2: " << data.NO2;
    cout << "\nSO2: " << data.SO2;
    cout << "\nAQI: " << data.AQI << endl;

    return data.AQI;
}

// normal correct
void checkGasSafety(int aqi)
{
    if (aqi <= 100)
        cout << "Status: SAFE" << endl;
    else if (aqi <= 150)
        cout << "Status: MODERATE" << endl;
    else
        cout << "Status: HAZARDOUS" << endl;
}

// using struct as paramaeter 
void assignCoordinates(Sector &s)
{
    
    if(s.name == "Sector M")
    {
        s.x = 0;
        s.y = 0;
    }
    else if(s.name == "Sector W1")
    {
        s.x = -1;
        s.y = 0;
    }
    else if(s.name == "Sector E1")
    {
        s.x = 1;
        s.y = 0;
    }
    else if(s.name == "Sector C")
    {
        s.x = 0;
        s.y = 1;
    }
    else if(s.name == "Alt Route S")
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
// Structure to store engine parameters
struct EngineData {
    int temperature;     // in °C
    int vibration;       // vibration level (0–100)
    int rpm;             // engine speed
};

// 1️⃣ Simulates engine parameters
EngineData generateEngineHealthData() {
    EngineData data;
    data.temperature = 60 + rand() % 50;   // 60–109 °C
    data.vibration   = rand() % 100;       // 0–99
    data.rpm         = 800 + rand() % 2200; // 800–2999 RPM
    return data;
}

// 2️⃣ Detects early signs of engine failure
bool checkEngineHealth(EngineData data) {
    if (data.temperature > 95 || data.vibration > 70 || data.rpm > 2800) {
        return false;  // unhealthy
    }
    return true;       // healthy
}

// 3️⃣ Suggests maintenance before breakdown
void predictMaintenance(EngineData data) {
    cout << "\n--- Predictive Maintenance Report ---\n";
    cout << "Temperature: " << data.temperature << " °C\n";
    cout << "Vibration: " << data.vibration << "\n";
    cout << "RPM: " << data.rpm << "\n";

    if (!checkEngineHealth(data)) {
        cout << "⚠ WARNING: Engine health degrading\n";
        cout << "🔧 Recommendation: Schedule maintenance immediately\n";
    } else {
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
            //full access 

            srand(time(0));

            int sectorId; 
            string sectorIdCopy;
            cout << "\nEnter Sector ID to check air quality: ";
            cin >> sectorIdCopy;

            //sectorId =

            int aqi = getSectorAQI(sectorId ,sectorIdCopy); // error 
            checkGasSafety(aqi);
           
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
    srand(time(0)); // seed random values

    cout << "===== SafeStrike Engine Monitoring System =====\n";

    EngineData engine = generateEngineHealthData();
    predictMaintenance(engine);
    return 0;
}
