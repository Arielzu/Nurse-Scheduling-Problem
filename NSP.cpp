#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;

//Structures
struct Employees {
    char idEmployee;
    vector<int> MaxShift;
    int MaxTotalMinutes;
    int MinTotalMinutes;
    int MaxConsecutiveShifts;
    int MinConsecutiveShifts;
    int MinConsecutiveDaysOff;
    int MaxWeekends;
    vector<int> daysoff;
};

struct Shifts {
    char idShift;
    int length;
    vector<char> forbidden;
};

struct PenaltyQ {
    char EmployeeID;
    char Day;
    int ShiftID;
    int Weight;
};

struct PenaltyP {
    char EmployeeID;
    char Day;
    int ShiftID;
    int Weight;
};

struct CoverSUV {
    int Day;
    char ShiftID;
    int Requirement; // Sidt
    int WeightU; // Uidt
    int WeightO; // Vidt
};



//Parameters
int h;
vector<struct Employees> I;
vector<struct Shifts> T;
vector<struct PenaltyQ> Q; 
vector<struct PenaltyP> P;
vector<struct CoverSUV> S;


//Functions
bool file_reading(string name)
{
    string filename(name);
    vector<string> lines;
    string line;


    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "No se encontró el archivo - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }
    else{
        cerr << "Leyendo instancia...\n";
    }
    while (getline(input_file, line)){
        lines.push_back(line);
        int n = line.length();
        ///char line_aux[n+1];
        //strcpy(line_aux, line.c_str());
        //line = strtok(line_aux, "\r\n");
        if (line == "SECTION_HORIZON"){    
            cout << "holi";
            getline(input_file, line);
            getline(input_file, line);
            getline(input_file, line);
           // strcpy(line_aux, line.c_str());
            //line = strtok(line_aux, "\r\n");
            h = stoi(line);
        }
        if (line == "SECTION_SHIFTS"){ 
            struct Shifts shift;
            char *token; 
            getline(input_file, line);
            //strcpy(line_aux, line.c_str());
            //line = strtok(line_aux, "\r\n");
            while (line != ""){
                getline(input_file, line);
                //strcpy(line_aux, line.c_str());
                token = strtok(line, ",");
                while (token != NULL){
                    shift.idShift = *token;
                    token = strtok(NULL, ",");
                    shift.length = *token;
                    token = strtok(NULL, ",");
                    char *forbidden_shift = strtok(token, "|");
                    while (forbidden_shift != NULL){
                        shift.forbidden.push_back(*forbidden_shift);
                        forbidden_shift = strtok(NULL, "|");
                    }
                    T.push_back(shift);
                    //free(forbidden_shift);
                }   
            }
        }    
        if  (line == "SECTION_STAFF"){
            struct Employees employee;
            char *token;
            getline(input_file, line);
           //strcpy(line_aux, line.c_str());
            //line = strtok(line_aux, "\r\n");
            while (line != ""){
                getline(input_file, line);
               // strcpy(line_aux, line.c_str());
                token = strtok(line, "\r\n");
                char *token_copy = token;
                while (token != NULL){
                    token = strtok(NULL, ",");
                    employee.idEmployee = *token;
                    token = strtok(NULL, ",");
                    //employee.MaxShift = stoi(token);
                    //token = strtok(NULL, ",");
                    employee.MaxTotalMinutes = stoi(token);
                    token = strtok(NULL, ",");
                    employee.MinTotalMinutes = stoi(token);
                    token = strtok(NULL, ",");
                    employee.MaxConsecutiveShifts = stoi(token);
                    token = strtok(NULL, ",");
                    employee.MinConsecutiveShifts = stoi(token);
                    token = strtok(NULL, ",");
                    employee.MinConsecutiveDaysOff = stoi(token);
                    token = strtok(NULL, ",");
                    employee.MaxWeekends = stoi(token);
                    char *shiftmax = strtok(token_copy, "|");
                    while (shiftmax!=NULL){
                        employee.MaxShift.push_back(stoi(shiftmax+2));
                        shiftmax=strtok(NULL,",");
                    }
                    I.push_back(employee);
                }
            }
        }
        if (line == "SECTION_DAYS_OFF"){
            char *token;
            getline(input_file, line);
           // strcpy(line_aux, line.c_str());
            //line = strtok(line_aux, "\r\n");
            while (line != ""){
                getline(input_file, line);
                //strcpy(line_aux, line.c_str());
                token = strtok(line, "\r\n");
                int day_indexer = 0;
                while (token != NULL){
                    token = strtok(NULL, ",");
                    token = strtok(NULL, ",");
                    I[day_indexer].daysoff.push_back(stoi(token));
                    token = strtok(NULL, ",");
                }
                day_indexer++;
                
            }
        }
        if (line == "SECTION_SHIFT_ON_REQUESTS"){
            char *token;
            struct PenaltyQ penaltyq;
            getline(input_file, line);
            //strcpy(line_aux, line.c_str());
            //line = strtok(line_aux, "\r\n");
            while (line != ""){
                getline(input_file, line);
               // strcpy(line_aux, line.c_str());
                token = strtok(line, "\r\n");
                while (token != NULL){
                    token = strtok(NULL, ",");
                    penaltyq.EmployeeID = *token;       
                    token = strtok(NULL, ",");
                    penaltyq.Day = stoi(token);
                    token = strtok(NULL, ",");
                    penaltyq.ShiftID = *token;
                    token = strtok(NULL, ",");
                    penaltyq.Weight = stoi(token);
                    Q.push_back(penaltyq); 
                }
            }
        }
        if (line == "SECTION_SHIFT_OFF_REQUESTS"){
            char *token;
            struct PenaltyP penaltyp;
            getline(input_file, line);
           // strcpy(line_aux, line.c_str());
            //line = strtok(line_aux, "\r\n");
            while (line != ""){
                getline(input_file, line);
                //strcpy(line_aux, line.c_str());
                token = strtok(line, "\r\n");
                while (token != NULL){
                    token = strtok(line, ",");
                    penaltyp.EmployeeID = *token;       
                    token = strtok(NULL, ",");
                    penaltyp.Day = stoi(token);
                    token = strtok(NULL, ",");
                    penaltyp.ShiftID = *token;
                    token = strtok(NULL, ",");
                    penaltyp.Weight = stoi(token);
                    P.push_back(penaltyp); 
                }
            }
        }
        if (line == "SECTION_COVER"){
            char *token;
            struct CoverSUV SUV;
            getline(input_file, line);
           // strcpy(line_aux, line.c_str());
            //line = strtok(line_aux, "\r\n");
            while (line != ""){
                getline(input_file, line);
               // strcpy(line_aux, line.c_str());
                token = strtok(line, "\r\n");
                while (token != NULL){
                    token = strtok(NULL, ",");
                    SUV.Day = stoi(token);
                    token = strtok(NULL, ",");
                    SUV.ShiftID = *token;
                    token = strtok(NULL, ",");
                    SUV.Requirement = stoi(token);
                    token = strtok(NULL, ",");
                    SUV.WeightU = stoi(token);
                    token = strtok(NULL, ",");
                    SUV.WeightO = stoi(token);
                    S.push_back(SUV);
                }
            }
        }
    }  

    for (const auto &i : lines)
        cout << i << endl;

    input_file.close();
    return EXIT_SUCCESS;
}




int main()
{
    string name;
    cin >> name;
    file_reading(name);
}
