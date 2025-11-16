#ifndef PRODUCTS_MANAGEMENT_H
#define PRODUCTS_MANAGEMENT_H

#include <string>
#include <fstream>
#include <vector>

extern struct ProductsInfo		
{
	std::string ProductsName , ProductsID ;
	double ProductsPrice;
	unsigned int ProductsQuantity;
};

extern std::vector<ProductsInfo> ProductsInVector;

extern void OpenProductsFile();
extern void CreateProductsID(ProductsInfo& NewProduct);
extern inline auto SearchProductsInVector(std::string InVector);
extern void LoadProductsToVector();
extern void SaveProductsToFile();
extern void DeleteProduct(const std::string ProductName);
extern void ShowAllProducts();
extern inline bool CheckProductID(std::string IDHepler);
extern inline bool CheckProductName(std::string NameHepler);
extern inline bool FindProduct(std::string ProductSign);
extern inline void SaveBoughtProducts(const std::string BoughtSaved);
extern inline inline double SumOfBoughtProducts();
extern void LossQuantity(const std::string& LossProduct);
extern void EndOfQuantity();
extern void UpdateName(const std::string NewName, const std::string OldName);
void UpdatePrice(const double NewPrice, const std::string OldName);
void UpdateQuantity(const double NewQuantity, const std::string OldName);
void SearchForProduct(const std::string OldName);
#endif // !PRODUCTS_MANAGEMENT_H