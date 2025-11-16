#include <iostream>
#include<vector>
#include "UsersManagement.h"
#include"ProductsManagement.h"

using namespace std;

UsersInfo NewUser;
ProductsInfo NewProduct;

void Menu();

void SignUp(UsersInfo& NewUser);

void LogIn(UsersInfo& NewUser);

void BeAdmin(UsersInfo& NewUser);

void BeEmbloyee(UsersInfo& NewUser);

void InMenu(string strHelper);

void Settings(string UserSign);

void AdminSettings(const string UserSign);

void EmployeeSettings(const string UserSign);

void ClientSettings(const string UserSign);

char ReturnMenu(char &reHelper);

string FindUserSign(string FSUser);

void EditUsers(const string UserSign);

void ChangeUserProfile(const string chUser);

void BuyingProduct(string& BuyProduct);

void ChangeProductInfo(const string chProduct);

void AddProduct(ProductsInfo& NewProduct);

void SearchForProfile();

void SearchForProductProfile();

int main()
{
    OpenFile();
    OpenProductsFile();
    LoadToVector();
    LoadProductsToVector();
	Menu();
}

void Menu()
{
    int ClientChoose;
    cout << "\t\t\t\t\t\tWELCOME IN NOVA STORE\n\t\t\t\t\t------------------------------------\n\n\nPlease choose one of the following numbers: \n1- Sign up\n2- Log in\n";
    cin >> ClientChoose;
    while (ClientChoose < 1 || ClientChoose > 2 || FailValue()) {
        system("cls");
        cout << "Error! Please choose a number:\n1- Sign up\n2- Log in\n";
        cin >> ClientChoose;
    }
    system("cls");
    switch (ClientChoose) {
    case 1:
        SignUp(NewUser);
        break;
    default:
        LogIn(NewUser);
    }
}

void SignUp(UsersInfo& NewUser) 
{
    LoadToVector();
    cout << "Enter your username: ";
    cin.ignore();
    getline(cin, NewUser.UsersName);
    system("cls");

    while (CheckUsersName(NewUser.UsersName)) {
        system("cls");
        cin.ignore();
        cout << "Error! The username is already taken. Please enter another username: ";
        getline(cin, NewUser.UsersName);
    }

    system("cls");
    cout << "Enter your password: ";
    cin>>NewUser.UsersPassword;
    system("cls");

    CreateUsersID(NewUser);
    cout << "Enter your phone number (starting with 77, 73, 71, 78 and contains 9 digits): ";
    cin>>NewUser.UsersNumber;
    system("cls");

    UsersNumber(NewUser.UsersNumber);
    system("cls");

    BeAdmin(NewUser);
    BeEmbloyee(NewUser);
    system("cls");

    char chHelper;
    cout << "Choose your gender letter: M (Male) / F (Female): ";
    cin >> chHelper;

    NewUser.UsersGender = UsersGender(&chHelper);
    system("cls");
    UsersInVector.push_back(NewUser);
    SaveInFile();
    Menu();
}

void LogIn(UsersInfo& NewUser)
{
    LoadToVector();
    string UserInput, strHelper;
    while (true)
    {
        cin.ignore();
        cout << "Enter your username or ID : ";
        getline(cin ,UserInput);
        if (!FindUser(UserInput))
        {
            system("cls");
            cout << "Error ! Please input a valid info \n\n";
            continue;
        }
        strHelper = UserInput;
        system("cls");
        cout << "Enter your password : ";
        cin >> UserInput;
        int Error = 0;
        while (!CheckUsersPassword(UserInput))
        {
            system("cls");
            cout << "Error ! Please enter a valid password : ";
            cin >> UserInput;
            Error++;
            if (Error == 3)
            {
                char YorN;
                system("cls");
                cout << "Error ! do you want to try again ? ( Y or N ) ";
                cin >> YorN;
                system("cls");
                if (YesorNo(YorN))
                {
                    continue;
                }
                else
                {
                    system("cls");
                    cout << "Thanks to be with us . \n\n----------------------------------------------------------\n\n";
                    exit(0);
                }
            }
        }
        system("cls");
        if (!CheckIsActive(strHelper))
        {
            system("cls");
            cout << "You are not allowed to enter ( Not active ! )\n\n----------------------------------------------------------\n\n";
            exit(0);
        }
        break;
    }
    system("cls");
    InMenu(strHelper);
}

void BeAdmin(UsersInfo& NewUser)
{
    char adHelper;
    string passHelper;
    cout << "Do you want to be an admin ? ( Y or N )";
    cin >> adHelper;
    system("cls");
    if (YesorNo(adHelper))
    {
        cout << "Enter the admin's password to be an admin : ( If you want to be an employee, contact with the general admin by 774071411 )";
        cin >> passHelper;
        int wepass = 0;
        while (!ToBeAdmin(passHelper))
        {
            system("cls");
            cout << "Error ! Please enter a valid password : ";
            cin >> passHelper;
            wepass++;
            if (wepass == 3)
            {
                system("cls");
                cout << "Error ! you passed the trying limits\nyou will enter as a client.\n\n";
                break;
            }
        }
        if (ToBeAdmin(passHelper))
            NewUser.UsersRole = Admin;
        else
            NewUser.UsersRole = Client;
    }
    else
        NewUser.UsersRole = Client;
}

void BeEmbloyee(UsersInfo& NewUser)
{
    char adHelper;
    string passHelper;
    cout << "Do you want to be an employee ? ( Y or N )";cin >> adHelper;
    system("cls");
    if (YesorNo(adHelper))
    {
        cout << "Enter the employee's password to be an employee : ";cin >> passHelper;
        int wepass = 0;
        while (!ToBeEmployee(passHelper))
        {
            system("cls");
            cout << "Error ! Please enter a valid password : ";
            cin >> passHelper;
            wepass++;
            if (wepass == 3)
            {
                system("cls");
                cout << "Error ! you passed the trying limits\nyou will enter as a client.\n\n";
                break;
            }
        }
        if (ToBeEmployee(passHelper))
            NewUser.UsersRole = Employee;
        else
            NewUser.UsersRole = Client;
    }
    else
        NewUser.UsersRole = Client;
}

char Return;

void InMenu(string strHelper)
{
    int ChooseMenu;
    cout << "Please choose one of the following numbers : \n1- Store\n2- Settings\n3- Exit\n";
    cin >> ChooseMenu;
    while (FailValue() || ChooseMenu < 1 || ChooseMenu > 3)
    {
        system("cls");
        cout << "Error ! Please enter a valid number : \n1- Store\n2- Settings\n3- Exit\n";
        cin >> ChooseMenu;
    }
    system("cls");
    string BuyProduct;
    char Return;
    switch (ChooseMenu)
    {
    case 1:
        ShowAllProducts();
        while (true)
        {
            cin.ignore();
            cout << "Enter a product's name or ID : ";
            getline(cin ,BuyProduct);
            BuyingProduct(BuyProduct);
            cout << "Do you want to buy again ? ( Y or N ) ";
            cin >> Return;
            system("cls");
            if (YesorNo(Return))
            {
                ShowAllProducts();
                continue;
            }
            else
                break;
        }
        cout << "The price of bought products is : " << SumOfBoughtProducts() << "\n------------------------------------------------\n\n";
        InMenu(strHelper);
        break;
    case 2:
        Settings(strHelper);
        break;
    default:
        system("cls");
        cout << "Thank you for supporting NOVA store \n\n----------------------------------------------------------\n\n";
        exit(0);
    }
}

void Settings(const string UserSign)
{
    cout << "Choose one of the following numbers : \n";
    switch (CheckUserRole(UserSign))
    {
    case Admin:
    {
        AdminSettings(UserSign);
        break;
    }
    case Employee:
    {
        EmployeeSettings(UserSign);
        break;
    }
    default:
    {
        ClientSettings(UserSign);
    }
    }
}

int UserChoose;
string EditProduct;


void AdminSettings(const string UserSign)
{
    int UserChoose;
    char Return;
    string EditProduct;
    cout << "1- My profile\n2- All users\n3- All product\n4- Add product\n5- Search for user\n6- Search for product\n"; cin >> UserChoose;
    while (FailValue() || UserChoose < 1 || UserChoose > 6)
    {
        system("cls");
        cout << "Error ! Please Choose one of the following numbers : 1- My profile\n2- All users\n3- All product\n4- Add product\n5- Search for user\n6- Search for product\n";
        cin >> UserChoose;
    }
    system("cls");
    switch (UserChoose)
    {
    case 1:
        UsersProfile(UserSign);
        cout << "Do you want to edit your profile ? ( Y or N ) ";
        cin >> Return;
        system("cls");
        if (YesorNo(Return))
        {
            UsersProfile(UserSign);
            cout << "Please choose one of the following numbers to edit : \n1- Username\n2-Password\n3-Phone number\n";
            cin >> UserChoose;
            system("cls");
            ChangeUserProfile(UserSign);
        }
        system("cls");
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
        break;
    case 2:
        PrintAllUsers();
        cout << "Do you want to edit users info ? ( Y or N )";
        cin >> Return;
        system("cls");
        if (YesorNo(Return))
        {
            EditUsers(UserSign);
        }
        else
        {
            system("cls");
            cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
            cin >> Return;
            if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
                Settings(UserSign);
            else
                InMenu(UserSign);
        }
        break;
    case 3:
        ShowAllProducts();
        cout << "Do you want to edit products info ? ( Y or N ) ";
        cin >> Return;
        system("cls");
        if (YesorNo(Return))
        {
            ShowAllProducts();
            cin.ignore();
            cout << "Enter a products name or ID : ";
            getline(cin, EditProduct);  
            while (!FindProduct(EditProduct))
            {
                system("cls");
                cin.ignore();
                cout << "Error ! Please input a valid info : ";
                getline(cin, EditProduct); 
            }
            system("cls");
            cout << "Please choose one of the following numbers to edit : \n1- Delete\n2- Change Name\n3- Change price\n4- Change quantity\n";
            cin >> UserChoose;
            ChangeProductInfo(EditProduct);
            cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
            cin >> Return;
            if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
                Settings(UserSign);
            else
                InMenu(UserSign);
        }
        system("cls");
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
        break;
    case 4:
        AddProduct(NewProduct);
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
    case 5:
        SearchForProfile();
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
        break;
    default:
        SearchForProductProfile();
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
    }
}

void EmployeeSettings(const string UserSign)
{
    int UserChoose;
    char Return;
    string EditProduct;

    cout << "1- My profile\n2- All users\n3- All product\n4- Add product\n5- Search for user\n6- Search for product\n";
    cin >> UserChoose;
    while (FailValue() || UserChoose < 1 || UserChoose > 6)
    {
        system("cls");
        cout << "Error ! Please Choose one of the following numbers : 1- My profile\n2- All users\n3- All product\n4- Add product\n5- Search for user\n6- Search for product\n";
        cin >> UserChoose;
    }
    system("cls");
    switch (UserChoose)
    {
    case 1:
        UsersProfile(UserSign);
        cout << "Do you want to edit your profile ? ( Y or N ) ";
        cin >> Return;
        system("cls");
        if (YesorNo(Return))
        {
            UsersProfile(UserSign);
            cout << "Please choose one of the following numbers to edit : \n1- Username\n2-Password\n3-Phone number\n";
            cin >> UserChoose;
            system("cls");
            ChangeUserProfile(UserSign);
        }
        system("cls");
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
        break;
    case 2:
    {
        PrintAllUsers();
            cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
            cin >> Return;
            if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
                Settings(UserSign);
            else
                InMenu(UserSign);
        }
        break;
    case 3:
        ShowAllProducts();
        cout << "Do you want to edit products info ? ( Y or N ) ";
        cin >> Return;
        system("cls");
        if (YesorNo(Return))
        {
            ShowAllProducts();
            cin.ignore();
            cout << "Enter a products name or ID : ";
            getline(cin, EditProduct);
            while (!FindProduct(EditProduct))
            {
                system("cls");
                cin.ignore();
                cout << "Error ! Please input a valid info : ";
                getline(cin, EditProduct);
            }
            system("cls");
            cout << "Please choose one of the following numbers to edit : \n1- Delete\n2- Change Name\n3- Change price\n4- Change quantity\n";
            cin >> UserChoose;
            ChangeProductInfo(EditProduct);
            cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
            cin >> Return;
            if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
                Settings(UserSign);
            else
                InMenu(UserSign);
        }
        system("cls");
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
        break;
    case 4:
        AddProduct(NewProduct);
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
    case 5:
        SearchForProfile();
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
        break;
    default:
        SearchForProductProfile();
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
    }
}

void ClientSettings(const string UserSign)
{
    system("cls");
    UsersProfile(UserSign);
    cout << "Do you want to edit your profile ? ( Y or N ) ";
    cin >> Return;
    system("cls");
    if (YesorNo(Return))
    {
        UsersProfile(UserSign);
        cout << "Please choose one of the following numbers to edit : \n1- Username\n2-Password\n3-Phone number\n";
        cin >> UserChoose;
        ChangeUserProfile(UserSign);
    }
    system("cls");
    cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
    cin >> Return;
    if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
        Settings(UserSign);
    else
        InMenu(UserSign);
}

char ReturnMenu(char& reHelper)
{
    while (FailValue() || (reHelper != 'M' && reHelper != 'm' && reHelper != 'l' && reHelper != 'L'))
    {
        system("cls");
        cout << "Error! Please enter M or L: ";
        cin >> reHelper;
    }
    system("cls");
    return reHelper;
}

string FindUserSign(string FSUser)
{
    cin.ignore();
    cout << "Enter a user's username or ID: ";
    getline(cin, FSUser);  
    while (!FindUser(FSUser))  
    {
        system("cls");
        cout << "Error! Please input a valid info: ";
        getline(cin, FSUser); 
    }
    system("cls");
    return FSUser;
}

void EditUsers(const string UserSign)
{
    cout << "Please Choose one of the following numbers : \n1- Delete user\n2- Change activation\n";
    cin >> UserChoose;
    while (FailValue() || UserChoose < 1 || UserChoose > 2)
    {
        system("cls");
        cout << "Error ! Please Choose one of the following numbers : \n1- Delete user\n2- Change activation\n";
        cin >> UserChoose;
    }
    system("cls");
    string edUser;
    PrintAllUsers();
    switch (UserChoose)
    {
    case 1:
    {
        DeleteUser(FindUserSign(edUser));
        system("cls");
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
        break;
    }
    case 2:
    {
        ChangeActivation(FindUserSign(edUser));
        system("cls");
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
        break;
    }
   /* default:
    {
        string RoleChoose;
        system("cls");
        cout << FindUserSign(edUser) << "\nTo which role do you want to change it: ( Admin , Employee , Client ) ";
        cin>>RoleChoose;  
        while (RoleChoose != "Admin" && RoleChoose != "admin" && RoleChoose != "Employee" && RoleChoose != "employee" && RoleChoose != "Client" && RoleChoose != "client")
        {
            system("cls");
            cout << "Error! Please enter a valid value: ( Admin , Employee , Client ) ";
            cin>>RoleChoose;  
        }
        system("cls");
        ChangeRole(edUser, RoleChoose);
        system("cls");
        cout << "Press M to return to the settings menu or press L to return to the log in menu : ";
        cin >> Return;
        if (ReturnMenu(Return) == 'm' || ReturnMenu(Return) == 'm')
            Settings(UserSign);
        else
            InMenu(UserSign);
    }*/
    }
}

void ChangeUserProfile(const string chUser)
{
    while (FailValue() || UserChoose < 1 || UserChoose > 3)
    {
        system("cls");
        cout << "Error! Please Choose one of the following numbers: \n1- Username\n2-Password\n3-Phone number\n";
        cin >> UserChoose;
    }
    system("cls");

    string NewInfo;

    switch (UserChoose)
    {
    case 1:
        cout << "Enter your new username: ";
        cin >> NewInfo;
        system("cls");
        UpdateUserName(NewInfo, chUser);
        break;
    case 2:
        cout << "Enter your new password: ";
        cin >> NewInfo;
        system("cls");
        UpdatePassword(NewInfo, chUser);
        break;
    default:
        cout << "Enter your new phone number: ";
        cin >> NewInfo;
        UsersNumber(NewInfo);
        UpdatePhoneNumber(NewInfo, chUser);
        system("cls");
    }
}

void BuyingProduct(string& BuyProduct)
{
    while (!FindProduct(BuyProduct))
    {
        system("cls");
        cin.ignore();
        cout << "Error! Please input a valid product name or ID: ";
        getline(cin , BuyProduct) ;
    }
    system("cls");

    SaveBoughtProducts(BuyProduct);
    LossQuantity(BuyProduct);
}

void ChangeProductInfo(const string chProduct)
{
    while (FailValue() || UserChoose < 1 || UserChoose > 4)
    {
        system("cls");
        cout << "Error! Please choose one of the following numbers:\n1- Delete\n2- Change Name\n3- Change price\n4- Change quantity\n";
        cin >> UserChoose;
    }
    system("cls");
    string NewProduct;
    switch (UserChoose)
    {
    case 1:
        DeleteProduct(chProduct);
        break;
    case 2:
        cin.ignore();
        cout << "Enter the new name: ";
        getline(cin, NewProduct);  
        UpdateName(NewProduct, chProduct);
        break;
    case 3:
        double NewPrice;
        cout << "Enter the new price: ";
        cin >> NewPrice;
        while (FailValue() || NewPrice <= 0)
        {
            system("cls");
            cout << "Error! The price must be greater than 0: ";
            cin >> NewPrice;
        }
        system("cls");
        UpdatePrice(NewPrice, chProduct);
        break;
    default:
        int NewQuantity;
        cout << "Enter the new quantity: ";
        cin >> NewQuantity;
        while (FailValue() || NewQuantity <= 0)
        {
            system("cls");
            cout << "Error! The quantity must be greater than 0: ";
            cin >> NewQuantity;
        }
        system("cls");
        UpdateQuantity(NewQuantity, chProduct);
    }
}

void AddProduct(ProductsInfo& NewProduct)
{
    cin.ignore();
    cout << "Enter product name: ";
    getline(cin, NewProduct.ProductsName);  
    while (CheckProductName(NewProduct.ProductsName) || NewProduct.ProductsName.empty())
    {
        system("cls");
        cin.ignore();
        cout << "Error! Please enter a new name: ";
        getline(cin, NewProduct.ProductsName);
    }
    system("cls");

    CreateProductsID(NewProduct);  

    cout << "Enter product price: ";
    cin >> NewProduct.ProductsPrice;
    while (FailValue() || NewProduct.ProductsPrice <= 0)
    {
        system("cls");
        cout << "Error! Please enter a valid price: ";
        cin >> NewProduct.ProductsPrice;
    }
    system("cls");

    cout << "Enter product quantity: ";
    cin >> NewProduct.ProductsQuantity;
    while (FailValue() || NewProduct.ProductsQuantity <= 0)
    {
        system("cls");
        cout << "Error! Please enter a valid number: ";
        cin >> NewProduct.ProductsQuantity;
    }
    system("cls");

    ProductsInVector.push_back(NewProduct);
    SaveProductsToFile();
}

void SearchForProfile()
{
    string ForSearch;
    cout << "Enter the info of the user you want to find : "; 
    cin.ignore();
    getline (cin , ForSearch);
    system("cls");
    SearchFoUser(ForSearch);
}

void SearchForProductProfile()
{
    string ForSearch;
    cout << "Enter the info of the product you want to find : ";
    cin.ignore();
    getline(cin, ForSearch);
    system("cls");
    SearchForProduct(ForSearch);
}