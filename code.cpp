#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
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

const int TOTAL_ROUTES = 9;
const int MAX_ROUTE_LEN = 6;

string allRoutes[TOTAL_ROUTES][MAX_ROUTE_LEN] = {
    {"Sector N1", "Sector C", "Sector M", "Alt Route S", "Loading Bay", ""},
    {"Sector NW", "Sector C", "Sector M", "Alt Route S", "Loading Bay", ""},
    {"Sector NE", "Sector C", "Sector M", "Alt Route S", "Loading Bay", ""},
    {"Sector W1", "Sector M", "Alt Route S", "Loading Bay", "", ""},
    {"Sector E1", "Sector M", "Alt Route S", "Loading Bay", "", ""},
    {"Sector SW", "Alt Route S", "Loading Bay", "", "", ""},
    {"Sector SE", "Alt Route S", "Loading Bay", "", "", ""},
    {"Sector C", "Sector M", "Alt Route S", "Loading Bay", "", ""},
    {"Sector M", "Alt Route S", "Loading Bay", "", "", ""}
};


struct Sector
{
    string name; 
    int x;
    int y;
    int Id;
    float aqi;
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
int calculateRouteAQI(string route[])
{
    int maxAQI = 0;

    for(int i = 0; i < MAX_ROUTE_LEN; i++)
    {
        if(route[i] == "")
            break;

        int sectorAQI = getSectorAQI(route[i]);

        if(sectorAQI > maxAQI)
            maxAQI = sectorAQI;
    }

    return maxAQI;
}
int findGreenRouteFromAll(string currentSector)
{
    int bestRouteIndex = -1;
    int bestAQI = 100000;

    for(int i = 0; i < TOTAL_ROUTES; i++)
    {
        if(allRoutes[i][0] == currentSector)
        {
            cout << "\nChecking Route " << i+1 << "...\n";

            int routeAQI = calculateRouteAQI(allRoutes[i]);

            cout << "Route AQI: " << routeAQI << endl;

            if(routeAQI < bestAQI)
            {
                bestAQI = routeAQI;
                bestRouteIndex = i;
            }
        }
    }

    return bestRouteIndex;
}
void displayRoute(string route[])
{
    cout << "\n SELECTED GREEN ROUTE:\n";

    for(int i = 0; i < MAX_ROUTE_LEN; i++)
    {
        if(route[i] == "")
            break;

        cout << route[i];
        if(route[i+1] != "")
            cout << " -> ";
    }
    cout << endl;
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
    data.temperature = 60 + rand() % 50;    
    data.vibration   = rand() % 100;        
    data.rpm         = 800 + rand() % 2200; 
    return data;
}

bool checkEngineHealth(EngineData data) 
{
    if (data.temperature > 95 || data.vibration > 70 || data.rpm > 2800) 
    {
        return false;  
    }
    return true;      
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

int calculateDistance(Sector a, Sector b)
{
    
    return abs(a.x - b.x) + abs(a.y - b.y);
}

//Sector findGreenRoute(Sector current, Sector route1, Sector route2) //TO DO
//{
    
    //if(route1.aqi > 200.00)
        //return route2;

    //if(route2.aqi > 200.00)
        //return route1;

    
    //int d1 = calculateDistance(current, route1);
    //int d2 = calculateDistance(current, route2);

    //if(d1 <= d2)
        //return route1;
    //else
        //return route2;
//}

Sector switchToAlternativeRoute(Sector mainRoute, Sector alternativeRoute) //TO DO
{
    if(mainRoute.aqi > 200)
    {
        return alternativeRoute;
    }
    return mainRoute;
}

struct ESGScore
{
    int environmental;
    int social;
    int governance;
    int total;
};


int calculateEnvironmentalScore(int aqi)
{
    if(aqi <= 100) 
        return 90;
    else if(aqi <= 150) 
        return 70;
    else if(aqi <= 200) 
        return 40;
    else 
        return 20;
}

int calculateSocialScore(EngineData engine)
{
    if(checkEngineHealth(engine))
        return 85;
    else
        return 50;
}

int calculateGovernanceScore(string role)
{
    if(role == "Admin") 
        return 90;
    else if(role == "Moderator") 
        return 75;
    else 
        return 60;
}


ESGScore generateESGScore(int aqi, EngineData engine, string role)
{
    ESGScore score;

    score.environmental = calculateEnvironmentalScore(aqi);
    score.social = calculateSocialScore(engine);
    score.governance = calculateGovernanceScore(role);

    score.total = (score.environmental + score.social + score.governance) / 3;

    return score;
}

void displayESGScore(ESGScore score)
{
    cout << "\n--- ESG SCORE REPORT ---\n";
    cout << "Environmental Score: " << score.environmental << endl;
    cout << "Social Score: " << score.social << endl;
    cout << "Governance Score: " << score.governance << endl;
    cout << "Overall ESG Score: " << score.total << endl;

    if(score.total >= 80)
        cout << "Status: Excellent Sustainability\n";
    else if(score.total >= 60)
        cout << "Status: Moderate Sustainability\n";
    else
        cout << "Status: High Risk -> Needs Improvement\n";
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

    Sector s;
    Sector s1;
    Sector s2;

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
            int choice; 
            
            do
            {
                cout << "Choose your operation :-" << endl;
                cout << "1. Check Air Quality" << endl;
                cout << "2. Engine Monitoring System" << endl;
                cout << "3. Sector Information" << endl;   
                cout << "4. Show Mine Map" <<endl;
                cout << "5. Distance between two Sectors"<<endl;
                cout << "6.Display ESG Score"<<endl;
                cout<< "7. Find Green Route"<<endl;
                cout << "8. Exit"<<endl;

                cin >> choice;

                if (choice == 1)
                    {
                        srand(time(0));
                        string sectorInput;
                        cout << "\nEnter Sector Name (e.g., Sector W1): ";
                        cin.ignore(1000, '\n'); 
                        getline(cin, sectorInput);

                        int aqi = getSectorAQI(sectorInput); 
                        checkGasSafety(aqi);

                        Sector current;
                        current.name = sectorInput;
                        current.aqi = (float)aqi;
                        assignCoordinates(current);

                        if(current.x != 99) 
                        {
                            cout << "Location: (" << current.x << "," << current.y << ") | ";
                            if(current.Id >= 1 && current.Id <= 3) 
                                cout << "Resource: " << MineralInMine[current.Id-1].name << endl;
                        }
                    }
                else if (choice == 2 )
                {
                    srand(time(0)); 

                    cout << "===== SafeStrike Engine Monitoring System =====\n";

                    EngineData engine = generateEngineHealthData();
                    predictMaintenance(engine);
                }
                else if (choice == 3)
                {
                    cout << "Enter your sector: ";
                    cin.ignore(1000, '\n'); 
                    getline(cin, s.name);   
                    assignCoordinates(s);

                    if(s.x == 99 && s.y == 99) 
                    {
                        cout << "Invalid sector: Not in mine.\n";
                    }
                    else
                    {
                        cout << "Sector " << s.name << " coordinates (" 
                            << s.x << "," << s.y << ")";
                        if(s.Id == 1) 
                            cout << " contains Coal.\n";
                        else if(s.Id == 2) 
                            cout << " contains Iron Ore.\n";
                        else if(s.Id == 3) 
                            cout << " contains Diamond.\n";
                        else if(s.Id == 0) 
                            cout << " is Admin Office.\n";
                        else if(s.Id == 4) 
                            cout << " is Loading Bay.\n";
                    }
                }
                else if (choice == 4)
                        {
                            const char* mineMap = R"(
                        ====================== SAFE STRIKE : BASE MINE MAP ======================

                                                    [ Sector N1 ]                     
                                                        |                         
                                                        |                              
                        [ Sector NW ] -------- [ Sector C ] -------- [ Sector NE ]
                                                        |                              
                                                        |                              
                        [ Sector W1 ] -------- [ Sector M ] -------- [ Sector E1 ]
                                                        |                              
                                                        |                              
                        [ Sector SW ] -------- [ Alt Route S ] ------ [ Sector SE ]
                                                        |                              
                                                        |                              
                                                [ Loading Bay ]

                        =======================================================================
                        )";
                            cout << mineMap << endl;
                        }

                else if (choice == 5)
                {

                    cin.ignore(1000, '\n');

                    cout << "Enter your First Sector: ";
                    getline(cin, s1.name); 
                    assignCoordinates(s1); 
                    
                    cout << "Enter your Second Sector: ";
                    getline(cin, s2.name); 
                    assignCoordinates(s2); 

                    if (s1.x == 99 || s2.x == 99)
                    {
                        cout << "Error: One or both sectors not found in the database." << endl;
                    } 
                    else 
                    {
                        int d = calculateDistance(s1, s2);
                        cout << "\nDistance Calculation Result:" << endl;
                        cout << "The distance between " << s1.name << " and " << s2.name << " is " << d << " units." << endl;
                    }
                }

                else if (choice == 6)
                {
                    EngineData engine = generateEngineHealthData();
                    int aqi = getSectorAQI("Sector M");
                    ESGScore score = generateESGScore(aqi,engine,role); // TO DO
                    displayESGScore(score); 
                }
                else if (choice == 7)
                {
                    cin.ignore(1000, '\n');
                    string currentSector;
                    cout << "Enter your Current Sector: ";
                    getline(cin, currentSector);

                    int bestRouteIndex = findGreenRouteFromAll(currentSector);

                    if(bestRouteIndex != -1)
                    {
                        displayRoute(allRoutes[bestRouteIndex]);
                    }
                    else
                    {
                        cout << "No routes found from the specified sector.\n";
                    }
                }
                else
                {
                    cout<<"Exiting......";
                }
            } while (choice != 8);
        }
            

        else if(role == "Moderator") 
        {
            int choice; 
            do 
            {
                cout << "Choose your operation :-" << endl;
                cout << "1. Check Air Quality" << endl;
                cout << "2. Engine Monitoring System" << endl;
                cout << "3. Exit"<<endl;

                cin >> choice;
                if(choice == 1)
                {
                    srand(time(0));
                    string sectorIdCopy;
                    cout << "\nEnter Sector ID to check air quality: ";
                    cin.ignore(1000, '\n'); 
                    getline(cin, sectorIdCopy);
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
                    cout<<"Exiting......";
                }
                }while(choice != 3);          
        }

         else if(role == "Worker") 
        {
             int choice; 
            do 
            {
                cout << "Choose your operation :-" << endl;
                cout << "1. Check Air Quality" << endl;
                cout << "2. Engine Monitoring System" << endl;
                cout << "3. Exit"<<endl;

        
                cin >> choice;
                if(choice == 1)
                {
                    srand(time(0));
                    string sectorIdCopy;
                    cout << "\nEnter Sector ID to check air quality: ";
                    cin.ignore(1000, '\n'); 
                    getline(cin, sectorIdCopy);
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
                    cout<<"Exiting......";
                }
                }while(choice != 3);    
        } 

    }
    return 0;
}
