#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <string>
#include <fstream>
#include <vector>

enum Role { Admin = 1, Employee, Client };
enum Gender { M = 1, F };

extern const std::string RolePassword;

extern struct UsersInfo
{
    std::string UsersName, UsersPassword, UsersNumber, UsersID;
    bool IsActive = true;
    Role UsersRole ;
    Gender UsersGender;
};

extern std::vector<UsersInfo> UsersInVector;

extern inline bool FailValue();
extern void OpenFile();
extern void CreateUsersID(UsersInfo& NewUser);
extern inline bool CheckUsersID(std::string IDHelper);
extern inline bool CheckIsNumber(std::string IsItNum);
extern inline bool CheckUsersName(std::string IsNameInFile);
extern Gender UsersGender(char* chHelper);
extern void UsersNumber(std::string& PhoneEnter);
extern inline bool CheckUsersPassword(std::string PassHelper);
extern inline bool CheckIsActive(std::string ActHelper);
extern inline bool YesorNo(char &boHelper);
extern void SaveInFile();
extern void LoadToVector();
extern void UsersProfile(std::string UserSign);
extern inline bool ToBeAdmin(std::string PassAdmin);
extern inline bool ToBeEmployee(std::string PassAdmin);
extern inline Role CheckUserRole(std::string RoHelper);
extern void PrintAllUsers();
extern inline bool FindUser(std::string UserSign);
extern inline auto SearchInVector(std::string InVector);
extern void DeleteUser(std::string DeleteInfo);
extern void ChangeActivation(std::string ChangeInfo);
//extern void ChangeRole(const std::string ChangeInfo , const std::string RoleChoose);
void UpdateUserName(const std::string NewUserName, const std::string UserSign);
void UpdatePassword(const std::string NewPassword, const std::string UserSign);
extern void UpdatePhoneNumber(const std::string NewPhoneNumber,const std::string UserSign);
void SearchFoUser(const std::string UserSign);
#endif //USER_MANAGEMENT_H