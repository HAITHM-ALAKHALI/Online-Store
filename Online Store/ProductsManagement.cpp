#include "UsersManagement.h"
#include"ProductsManagement.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <cctype>
#include <random>
#include <algorithm>
#include <vector>
#include<string>

using namespace std;

vector<ProductsInfo> ProductsInVector;

vector<ProductsInfo> BoughtProducts;

void OpenProductsFile() 
{
    ofstream ProductsFile("Products.txt",ios::app);
    if (!ProductsFile)
    {
        cout << "Error! Unable to open the file! Please restart the program.\n";
        exit(0);
    }
    ProductsFile.close();
}

void CreateProductsID(ProductsInfo& NewProduct) 
{
    random_device DeviceTime;
    mt19937 Seed(DeviceTime());
    uniform_int_distribution<unsigned short int> RandomID{ 0, 9 };
    NewProduct.ProductsID = "19";
    for (int i = 0; i < 3; i++) {
        NewProduct.ProductsID += to_string(RandomID(Seed));
    }
}

inline auto SearchProductsInVector(string InVector)
{
    return find_if(ProductsInVector.begin(), ProductsInVector.end(), [&InVector](const ProductsInfo& user)
        {return user.ProductsID == InVector || user.ProductsName == InVector; });
}

void LoadProductsToVector()
{
    string Line;
    ifstream ProductsFile("Products.txt");
    if (!ProductsFile.is_open()) {
        system("cls");
        cout << "Error! Unable to open the file! Please restart the program.\n";
        exit(0);
    }
    ProductsInVector.clear();
    while (getline(ProductsFile, Line))
    {
        stringstream CheckFile(Line);
        ProductsInfo ReadProduct;
        string ChangeTostring;
        getline(CheckFile, ReadProduct.ProductsName, ',');
        getline(CheckFile, ReadProduct.ProductsID, ',');
        getline(CheckFile, ChangeTostring, ',');
        stringstream(ChangeTostring) >> ReadProduct.ProductsPrice;
        getline(CheckFile, ChangeTostring, ',');
        stringstream(ChangeTostring) >> ReadProduct.ProductsQuantity;
        ProductsInVector.push_back(ReadProduct);
    }
    ProductsFile.close();
}

void SaveProductsToFile()
{
    ofstream ProductsFile("Products.txt", ios::out |ios::trunc);
    if (!ProductsFile.is_open()) {
        system("cls");
        cout << "Error! Unable to open the file!\n";
        exit(0);
    }
    for (auto& Product : ProductsInVector) {
        ProductsFile << Product.ProductsName << "," <<Product.ProductsID<<"," << Product.ProductsPrice << ","
            << Product.ProductsQuantity << "\n";
    }
    ProductsFile.close();
}

void DeleteProduct(const string ProductName)
{
    auto it = SearchProductsInVector(ProductName);

    if (it != ProductsInVector.end())
    {
        ProductsInVector.erase(it);
        SaveProductsToFile();
    }
}

void ShowAllProducts() {
    system("cls");
    if (ProductsInVector.empty()) {
        cout << "No products available!\n\n";
    }
    else 
    {
        cout << "\t\t\t\tPRODUCTS DEPARTEMENT\n\t\t\t-----------------------------------------\n\n\n";
        for (auto& Product : ProductsInVector) {
            cout << "Product Name: " << Product.ProductsName << "\n" <<"ID: " <<Product.ProductsID<<"\n" << "Price: " << Product.ProductsPrice << "\n"
                << "Quantity: " << Product.ProductsQuantity << "\n" << "----------------------------\n";
        }
    }
}

inline bool CheckProductID(string IDHepler)
{
    for (auto& Product : ProductsInVector)
    {
        if (IDHepler == Product.ProductsID)
            return true;
    }
    return false;
}

inline bool CheckProductName(string NameHepler)
{
    for (auto& Product : ProductsInVector)
    {
        if (NameHepler == Product.ProductsName)
            return true;
    }
    return false;
}

inline bool FindProduct(string ProductSign)
{
    bool IsNum = CheckIsNumber(ProductSign);
    bool IDorName;
    return IDorName = IsNum ? CheckProductID(ProductSign) : CheckProductName(ProductSign);
}

inline void SaveBoughtProducts(const string BoughtSaved)
{
    for ( auto Product : ProductsInVector)
    {
        if (Product.ProductsID == BoughtSaved || Product.ProductsName == BoughtSaved)
            BoughtProducts.push_back(Product);
    }
}

inline double SumOfBoughtProducts()
{
    int Sum=0;
    for (auto &Product : BoughtProducts)
    {
        Sum += Product.ProductsPrice;
    }
    return Sum;
}

void LossQuantity(const string &LossProduct)
{
    for (auto &Product : ProductsInVector)
    {
        if (Product.ProductsID == LossProduct || Product.ProductsName == LossProduct)
            Product.ProductsQuantity--;
    }
    EndOfQuantity();
    SaveProductsToFile();
}

void EndOfQuantity()
{
    for (auto &Product : ProductsInVector)
    {
        if (Product.ProductsQuantity == 0)
        {
            DeleteProduct(Product.ProductsName);
        }
    }
    SaveProductsToFile();
}

void UpdateName(const string NewName , const string OldName)
{
    auto it = SearchProductsInVector(OldName);
    if (it != ProductsInVector.end())
    {
        it->ProductsName = NewName;
    }
    SaveProductsToFile();
}

void UpdatePrice(const double NewPrice, const string OldName)
{
    auto it = SearchProductsInVector(OldName);
    if (it != ProductsInVector.end())
    {
        it->ProductsPrice = NewPrice;
    }
    SaveProductsToFile();
}

void UpdateQuantity(const double NewQuantity, const string OldName)
{
    auto it = SearchProductsInVector(OldName);
    if (it != ProductsInVector.end())
    {
        it->ProductsQuantity = NewQuantity;
    }
    SaveProductsToFile();
}

void SearchForProduct(const string OldName)
{
    auto it = SearchProductsInVector(OldName);
    if (it != ProductsInVector.end())
    {
        cout <<"Product name : "<< it->ProductsName << "\nID : " << it->ProductsID << "\nPrice : " << it->ProductsPrice 
            <<"\nProductsQuantity : " << it->ProductsQuantity << "\n\n-----------------------------------------\n\n";
    }
    else
    {
        cout << "The product dose not found ! \n\n";
    }
}