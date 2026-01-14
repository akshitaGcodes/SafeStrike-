#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include<limits>

using namespace std;

const string b_red     = "\033[1;31m";
const string b_green   = "\033[1;32m";
const string b_white   = "\033[1;37m";
const string b_yellow  = "\033[1;33m";
const string b_blue    = "\033[1;34m";

const string reset      = "\033[0m";

 
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
struct Task
{
    string taskID;
    string description;
    int requiredHours;
    string assignedWorker;
};

struct WorkerStatus
{
    string workerName;
    int hoursWorked;
    int maxHours;
};

bool isWorkerAvailable(const WorkerStatus &worker, int taskHours)
{
    return (worker.hoursWorked + taskHours <= worker.maxHours);
}
void assignTask(Task &task, WorkerStatus &worker)
{
    if (isWorkerAvailable(worker, task.requiredHours))
    {
        task.assignedWorker = worker.workerName;
        worker.hoursWorked += task.requiredHours;

        cout << b_green<<"\n✅ Task Assigned Successfully\n"<<reset<<endl;
        cout << "Task: " << task.description << endl;
        cout << "Assigned To: " << worker.workerName << endl;
        cout << "Total Hours Worked: " 
             << worker.hoursWorked << "/" << worker.maxHours << endl;
    }
    else
    {
        cout <<b_red<< "\n⚠ Cannot Assign Task\n"<<reset<<endl;
        cout << "Worker: " << worker.workerName << endl;
        cout << "Reason: Exceeds allowed work hours\n";
    }
}

void displayTask(const Task &task)
{
    cout <<b_blue<< "\n--- TASK DETAILS ---\n"<<reset<<endl;
    cout <<b_white<<"Task ID: "<<reset << task.taskID << endl;
    cout <<b_white<<"Description: " <<reset<< task.description<< endl;
    cout <<b_white<< "Required Hours: " <<reset<< task.requiredHours << endl;
    cout <<b_white<<"Assigned Worker: " <<reset<< task.assignedWorker << endl<<endl;
}

void taskAssignmentPanel()
{
    WorkerStatus worker = {"Worker_1", 4, 8};

    Task task = {
        "T-101",
        "Inspect ventilation system in Sector C",
        3,
        "Not Assigned"
    };

    assignTask(task, worker);
    displayTask(task);
}

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

    cout << "\n" << sectorIdCopy <<b_white<< " Air Quality Data" <<reset<<endl;
    cout << "\nNO2: " << data.NO2;
    cout << "\nSO2: " << data.SO2;
    cout << "\nAQI: " << data.AQI << endl;

    return data.AQI;
}

void checkGasSafety(int aqi)
{
    if (aqi <= 100)
        cout <<b_white<< "Status:"<<reset<< b_green  <<"SAFE" << reset<< endl<<endl;
    else if (aqi <= 150)
        cout <<b_white<< "Status:"<<reset<< b_yellow  <<"MODERATE" << reset<< endl<<endl;
    else
        cout <<b_white<< "Status:"<<reset<< b_red  <<"HAZARDOUS" << reset<< endl<<endl;
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
    else if(s.name == "Sector SW") // diamond
    {
        s.x = -1;
        s.y = -1;
        s.Id = 3;
    }
    else if(s.name == "Sector SE") // iron ore
    {
        s.x = 1;
        s.y = -1;
        s.Id = 2;
    }
    else if(s.name == "Sector NW") //iron ore 
    {
        s.x = -1;
        s.y = 1;
        s.Id = 2;
    }
    else if(s.name == "Sector NE") //coal
    {
        s.x = 1;
        s.y = 1;
        s.Id = 1;
    }
    else if(s.name == "Sector N1") //admin office 
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
    cout <<b_green<< "\n SELECTED GREEN ROUTE:\n"<<reset<<endl;

    for(int i = 0; i < MAX_ROUTE_LEN; i++)
    {
        if(route[i] == "")
            break;

        cout <<b_green<< route[i] <<reset;
        if(route[i+1] != "")
            cout << " -> ";
    }
    cout << endl<<endl;
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
        cout <<b_red<< "⚠ WARNING: Engine health degrading"<<reset<<endl<<endl;
        cout << "🔧 Recommendation: Schedule maintenance immediately\n\n";
    } 
    else
     {
        cout <<b_green<< "✅ Engine status normal"<<reset<<endl<<endl;
        cout << "🟢 No maintenance required at the moment\n\n";
    }
}

int calculateDistance(Sector a, Sector b)
{
    
    return abs(a.x - b.x) + abs(a.y - b.y);
}

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
    cout << "\n------ ESG SCORE REPORT ------\n";
    cout << "Environmental Score: " << score.environmental << endl;
    cout << "Social Score: " << score.social << endl;
    cout << "Governance Score: " << score.governance << endl;
    cout << "Overall ESG Score: " << score.total << endl;

    if(score.total >= 80)
        cout << "Status:"<<b_green <<"Excellent Sustainability\n"<<reset<< endl;
    else if(score.total >= 60)
        cout << "Status: "<<b_yellow <<"Moderate Sustainability\n"<<reset<< endl;
    else
        cout << "Status:"<< b_red<<"High Risk -> Needs Improvement\n"<<reset<< endl;
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

    cout <<b_white << "====================================\n"<<reset;
    cout << b_green  <<" SAFE STRIKE "<<reset<<b_blue<<"| Mine Safety System\n"<<reset;
    cout << b_blue <<" Hackathon Prototype : "<<reset<<b_green<<"Error 404 \n" << reset;
    cout << b_white << "====================================\n"<<reset<<endl<<endl;

    cout << b_white << "----------------Welcome to SafeStrike----------------" << reset << endl;
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
        cout << b_red << "Invalid Credentials !!. Please try again" << reset << endl;
    } 
    else 
    {
        cout << b_green  << "\nAccess Granted!" << reset << endl;
        cout << "Welcome " <<b_white << user_name  << "(" <<  role  << ")"<<reset<< "to the SafeStrike Dashboard!!" << endl;

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
                cout << "6. Display ESG Score"<<endl;
                cout << "7. Assign Work to Worker"<<endl;
                cout << "8. Find Green Route"<<endl;
                cout << b_red << "9. Logout & Exit" << reset << endl;
                cout << "Selection: ";

                cin >> choice;

                cin.ignore(1000, '\n');

                if (choice == 1)
                    {
                        srand(time(0));
                        string sectorInput;
                        cout << "\nEnter Sector Name (e.g., Sector W1): ";
                        //cin.ignore(1000, '\n'); 
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
                    if (cin.peek() == '\n') cin.ignore(); 

                    cout << "Enter your sector (e.g., Sector NW, Sector M, Loading Bay): ";
                    getline(cin, s.name);  

                    assignCoordinates(s);

                    if (s.x == 99 && s.y == 99)
                    {
                        cout << b_red << "Invalid sector: '" << s.name << "' not found in database." << reset << endl;
                        cout << "Hint: Check spelling or use 'Show Mine Map' for valid names." << endl;
                    }
                    else
                    {
                        cout << "\n" << b_blue << "========= SECTOR PROFILE =========" << reset << endl;
                        cout << "Name        : " << s.name << endl;
                        cout << "Coordinates : (" << s.x << ", " << s.y << ")" << endl;

                        cout << "Type        : ";
                        switch(s.Id) {
                            case 0: cout << "Admin Office"; break;
                            case 1: cout << "Resource Node (Coal)"; break;
                            case 2: cout << "Resource Node (Iron Ore)"; break;
                            case 3: cout << "Resource Node (Diamond)"; break;
                            case 4: cout << "Loading Bay"; break;
                            default: cout << "General Access Area";
                        }
                        cout << "\n==================================\n" << endl;
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
                    //cin.ignore(1000, '\n');

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
                        cout <<b_white<< "\nDistance Calculation Result:"<<reset << endl;
                        cout << "The distance between " << s1.name << " and " << s2.name << " is " <<b_blue<< d <<reset<<" units." << endl<<endl;
                    }
                }

                else if (choice == 6)
                {
                    string sectorQ;

                    cout << "Enter your Sector: ";
                    getline(cin, sectorQ); 

                    EngineData engine = generateEngineHealthData();
                    int aqi = getSectorAQI(sectorQ);
                    ESGScore score = generateESGScore(aqi,engine,role); 
                    displayESGScore(score); 
                }
                 else if (choice == 7)                               
                {
                    taskAssignmentPanel();                            
                }


                else if (choice == 8)
                {
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
                        cout <<b_red<< "No routes found from the specified sector."<<endl<<reset<<endl;
                    }
                }
                else
                {
                    cout<<"Exiting......";
                }
            } while (choice != 9);
        }
            

        else if(role == "Moderator") 
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
                cout << "6. Find Green Route"<<endl;
                cout << b_red << "7. Logout & Exit" << reset << endl;
                cout << "Selection: ";

                cin >> choice;

                cin.ignore(1000, '\n');

                if (choice == 1)
                    {
                        srand(time(0));
                        string sectorInput;
                        cout << "\nEnter Sector Name (e.g., Sector W1): ";
                        //cin.ignore(1000, '\n'); 
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
                    if (cin.peek() == '\n') cin.ignore(); 

                    cout << "Enter your sector (e.g., Sector NW, Sector M, Loading Bay): ";
                    getline(cin, s.name);  

                    assignCoordinates(s);

                    if (s.x == 99 && s.y == 99)
                    {
                        cout << b_red << "Invalid sector: '" << s.name << "' not found in database." << reset << endl;
                        cout << "Hint: Check spelling or use 'Show Mine Map' for valid names." << endl;
                    }
                    else
                    {
                        cout << "\n" << b_blue << "========= SECTOR PROFILE =========" << reset << endl;
                        cout << "Name        : " << s.name << endl;
                        cout << "Coordinates : (" << s.x << ", " << s.y << ")" << endl;

                        cout << "Type        : ";
                        switch(s.Id) {
                            case 0: cout << "Admin Office"; break;
                            case 1: cout << "Resource Node (Coal)"; break;
                            case 2: cout << "Resource Node (Iron Ore)"; break;
                            case 3: cout << "Resource Node (Diamond)"; break;
                            case 4: cout << "Loading Bay"; break;
                            default: cout << "General Access Area";
                        }
                        cout << "\n==================================\n" << endl;
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
                    //cin.ignore(1000, '\n');

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
                        cout <<b_white<< "\nDistance Calculation Result:"<<reset << endl;
                        cout << "The distance between " << s1.name << " and " << s2.name << " is " <<b_blue<< d <<reset<<" units." << endl<<endl;
                    }
                }

                else if (choice == 6)
                {
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
                        cout <<b_red<< "No routes found from the specified sector."<<endl<<reset<<endl;
                    }
                }
                else
                {
                    cout<<"Exiting......";
                }
            } while (choice != 7);
        }       
        else if(role == "Worker") 
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
                cout << b_red << "6. Logout & Exit" << reset << endl;
                cout << "Selection: ";

                cin >> choice;

                cin.ignore(1000, '\n');

                if (choice == 1)
                    {
                        srand(time(0));
                        string sectorInput;
                        cout << "\nEnter Sector Name (e.g., Sector W1): ";
                        //cin.ignore(1000, '\n'); 
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
                    if (cin.peek() == '\n') cin.ignore(); 

                    cout << "Enter your sector (e.g., Sector NW, Sector M, Loading Bay): ";
                    getline(cin, s.name);  

                    assignCoordinates(s);

                    if (s.x == 99 && s.y == 99)
                    {
                        cout << b_red << "Invalid sector: '" << s.name << "' not found in database." << reset << endl;
                        cout << "Hint: Check spelling or use 'Show Mine Map' for valid names." << endl;
                    }
                    else
                    {
                        cout << "\n" << b_blue << "========= SECTOR PROFILE =========" << reset << endl;
                        cout << "Name        : " << s.name << endl;
                        cout << "Coordinates : (" << s.x << ", " << s.y << ")" << endl;

                        cout << "Type        : ";
                        switch(s.Id) 
                        {
                            case 0: cout << "Admin Office"; break;
                            case 1: cout << "Resource Node (Coal)"; break;
                            case 2: cout << "Resource Node (Iron Ore)"; break;
                            case 3: cout << "Resource Node (Diamond)"; break;
                            case 4: cout << "Loading Bay"; break;
                            default: cout << "General Access Area";
                        }
                        cout << "\n==================================\n" << endl;
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
                    //cin.ignore(1000, '\n');

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
                        cout <<b_white<< "\nDistance Calculation Result:"<<reset << endl;
                        cout << "The distance between " << s1.name << " and " << s2.name << " is " <<b_blue<< d <<reset<<" units." << endl<<endl;
                    }
                }
                else
                {
                    cout<<"Exiting......";
                }
            } while (choice != 6);
        }
    return 0;
}
}
