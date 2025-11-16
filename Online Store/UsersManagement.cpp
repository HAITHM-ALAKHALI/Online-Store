#include "UsersManagement.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>-
#include <cctype>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

const string RolePassword = "Admin_12345" , RolePassword2 = "Employee_12345";

string Temp , Line ;

vector<UsersInfo> UsersInVector;

inline bool FailValue() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }
    return false;
}

void OpenFile() 
{
    ofstream UsersFile("Archive.txt",ios::app);
    if (!UsersFile) {
        cout << "Error! Unable to open the file! Please restart the program.\n";
        exit(0);
    }
    UsersFile.close();
}

void CreateUsersID(UsersInfo& NewUser) {
    random_device DeviceTime;
    mt19937 Seed(DeviceTime());
    uniform_int_distribution<unsigned short int> RandomID{ 0, 9 };
    NewUser.UsersID = "55";
    for (int i = 0; i < 7; i++) {
        NewUser.UsersID += to_string(RandomID(Seed));
    }
}

inline bool CheckUsersID(string IDHelper)
{
    if (IDHelper.substr(0, 2) == "55")
    {
        for (auto& User : UsersInVector)
        {
            if (User.UsersID == IDHelper)
                return true;
        }
    }
    return false;
}

inline bool CheckIsNumber(string IsItNum)
{
    return (all_of(IsItNum.begin(), IsItNum.end(), ::isdigit));
}

inline bool CheckUsersName(string IsNameInFile) 
{
    for (auto& User : UsersInVector)
    {
        if (User.UsersName == IsNameInFile)
        {
            return true;
        }
    }
    return false;
}

Gender UsersGender(char *chHelper) {
    while (FailValue() || (*chHelper != 'm' && *chHelper != 'M' && *chHelper != 'f' && *chHelper != 'F')) {
        system("cls");
        cout << "Error! Please choose the correct letter: \nM (Male) \nF (Female) \n";
        cin >> *chHelper;
    }
    system("cls");
    return (*chHelper == 'M' || *chHelper == 'm') ? M : F;
}

void UsersNumber(string &PhoneEnter) {
    while (!CheckIsNumber(PhoneEnter))
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error ! Enter numbers . \n";
        getline(cin , PhoneEnter);
        system("cls");
    }
    while (PhoneEnter.size() != 9 ||
        (PhoneEnter.substr(0, 2) != "77" &&
            PhoneEnter.substr(0, 2) != "78" &&
            PhoneEnter.substr(0, 2) != "71" &&
            PhoneEnter.substr(0, 2) != "73")) {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error! Please enter a valid phone number (77, 78, 71, 73) with 9 digits: \n";
        getline(cin, PhoneEnter);
    }
    system("cls");
}

inline bool CheckUsersPassword(string PassHelper)
{
   for( auto &User : UsersInVector )
   {
       if (User.UsersPassword == PassHelper)
           return true;
   }
   return false;
}

inline bool CheckIsActive(string ActHelper)
{
    for (auto& User : UsersInVector)
    {
        if ((User.UsersName == ActHelper || User.UsersID == ActHelper) && User.IsActive)
            return true;
    }
    return false;
}

inline bool YesorNo(char &boHelper)
{
    while (FailValue() || boHelper != 'y' && boHelper != 'Y' && boHelper != 'n' && boHelper != 'N')
    {
        system("cls");
        cout << "Error ! Please enter Y or N : "; cin >> boHelper;
    }
    system("cls");
    return (boHelper == 'Y' || boHelper == 'y');
}

void SaveInFile() {
    ofstream UsersFile_Write("Archive.txt",ios::out|ios::trunc);
    if (!UsersFile_Write.is_open()) {
        system("cls");
        cout << "Error! Unable to open the file!\n";
        exit(0);
    }
    for (auto& User : UsersInVector)
    {
        UsersFile_Write << User.UsersName << "," << User.UsersPassword << "," << User.UsersID << ","
            << User.UsersNumber << "," << (User.UsersGender == M ? "M" : "F") << ","
            << (User.UsersRole == Admin ? "Admin" : (User.UsersRole==Employee ? "Employee" : "Client" )) << "," 
            << User.IsActive << "," << "\n";
    }
    UsersFile_Write.close();
}

void LoadToVector()
{
    string VectHelper;
    ifstream UsersFile_Read("Archive.txt");
    if (!UsersFile_Read.is_open()) {
        system("cls");
        cout << "Error! Unable to open the file! Please restart the program.\n";
        exit(0);
    }
    UsersInVector.clear();
    while (getline(UsersFile_Read, Line))
    {
        stringstream CheckFile(Line);
        UsersInfo ReadUsers;
        getline(CheckFile, ReadUsers.UsersName, ',');
        getline(CheckFile, ReadUsers.UsersPassword, ',');
        getline(CheckFile, ReadUsers.UsersID, ',');
        getline(CheckFile, ReadUsers.UsersNumber, ',');
        getline(CheckFile, VectHelper, ',');
        ReadUsers.UsersGender = (VectHelper == "M" ? M : F);
        getline(CheckFile, VectHelper, ',');
        ReadUsers.UsersRole = (VectHelper == "Admin" ? Admin : (VectHelper == "Employee" ? Employee : Client ));
        getline(CheckFile, VectHelper, ',');
        ReadUsers.IsActive = (VectHelper == "1" ? 1 : 0);
        UsersInVector.push_back(ReadUsers);
    }
    UsersFile_Read.close();
}

void UsersProfile(string UserSign)
{
    cout << "\t\t\t\t\t\tYOUR PROFILE\n\t\t\t\t\t---------------------------\n\n\n";
    for (auto& User : UsersInVector)
    {
        if (UserSign == User.UsersName || UserSign == User.UsersID)
        {
            cout << "Name : " << User.UsersName << "\nPassword : " << User.UsersPassword << "\nID : " << User.UsersID
                << "\nPhone number : " << User.UsersNumber << "\nGender : " << (User.UsersGender == M ? "Male" : "Female")
                << "\nRole : " << (User.UsersRole == Admin ? "Admin" : (User.UsersRole == Employee ? "Employee" : "Client"))
                << "\nActivation : " << (User.IsActive == 1 ? "Active" : "Nonactive")
                << "\n\n----------------------------------------------------------------------------\n\n";
            return;
        }
    }
}

inline bool ToBeAdmin(string PassAdmin)
{
    if (PassAdmin == RolePassword)
        return true;
    return false;
}

inline bool ToBeEmployee(string PassAdmin)
{
    if (PassAdmin == RolePassword2)
        return true;
    return false;
}

inline Role CheckUserRole(string RoHelper)
{
    for (auto& User : UsersInVector)
    {
        if (User.UsersID == RoHelper || User.UsersName == RoHelper)
            return User.UsersRole;
    }
    return Client;
}

void PrintAllUsers()
{
    for (auto& User : UsersInVector)
    {
        cout << "Name : " << User.UsersName << "\nPassword : " << User.UsersPassword << "\nID : " << User.UsersID
            << "\nPhone number : " << User.UsersNumber << "\nGender : " << (User.UsersGender == M ? "Male" : "Female")
            << "\nRole : " << (User.UsersRole == Admin ? "Admin" : (User.UsersRole == Employee ? "Employee" : "Client"))
            << "\n Activation : " << (User.IsActive == 1 ? "Active" : "Nonactive")
            << "\n----------------------------------------------------------------------------\n";
    }
}

inline bool FindUser(string UserSign)
{
    bool IsNum = CheckIsNumber(UserSign);
    bool IDorName;
    return IDorName = IsNum ? CheckUsersID(UserSign) : CheckUsersName(UserSign);
}

inline auto SearchInVector(string InVector)
{
    return find_if(UsersInVector.begin(), UsersInVector.end(), [&InVector](const UsersInfo& user)
        {return user.UsersID == InVector || user.UsersName == InVector; });
}

void DeleteUser(string DeleteInfo)
{
    auto it = SearchInVector(DeleteInfo);
        if (it != UsersInVector.end())
        {
            UsersInVector.erase(it);
        }
        SaveInFile();
}

void ChangeActivation(string ChangeInfo)
{
    auto it = SearchInVector(ChangeInfo);
    if (it != UsersInVector.end())
    {
        it->IsActive = !it->IsActive;
        cout << it->UsersName << " is now " << it->IsActive<<"\n\n";
    }
    SaveInFile();
}

//void ChangeRole(const string ChangeInfo, const string RoleChoose)
//{
//    auto it = SearchInVector(ChangeInfo);
//    if (it != UsersInVector.end())
//    {
//        if (RoleChoose == "Admin" || RoleChoose == "admin")
//            it->UsersRole = Admin;
//        else if (RoleChoose == "Employee" || RoleChoose == "employee")
//            it->UsersRole = Employee;
//        else
//            it->UsersRole = Client;
//    }
//    else
//        cout << "no";
//    SaveInFile();
//}

void UpdateUserName(const string NewUserName,const string UserSign)
{
    auto it = SearchInVector(UserSign);
    if (it != UsersInVector.end())
    {
        it->UsersName = NewUserName;
    }
    SaveInFile();
}

void UpdatePassword(const string NewPassword , const string UserSign)
{
    auto it = SearchInVector(UserSign);
    if (it != UsersInVector.end())
    {
        it->UsersPassword = NewPassword;
    }
    SaveInFile();
}

void UpdatePhoneNumber(const string NewPhoneNumber , const string UserSign)
{
    auto it = SearchInVector(UserSign);
    if (it != UsersInVector.end())
    {
        it->UsersNumber = NewPhoneNumber;
    }
    SaveInFile();
}

void SearchFoUser(const string UserSign)
{
    auto it = SearchInVector(UserSign);
    if (it != UsersInVector.end())
    {
        cout << "Name : "<<it->UsersName<<"\nUser Id : "<<it->UsersID<<"\nPassword : "<<it->UsersPassword
            <<"\nPhone number : "<<it->UsersNumber<<"\nGender : "<<it->UsersGender<<"\nRole : "
            << (it->UsersRole == Admin ? "Admin" : (it->UsersRole == Employee ? "Employee" : "Client"))
            << "\nActivation : " << (it->IsActive=1?"Active":"Nonactive") << "\n\n-----------------------------------------\n\n";
    }
    else
    {
        cout << "The user does not found ! \n\n";
    }
}