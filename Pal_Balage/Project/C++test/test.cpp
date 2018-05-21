#include <iostream>
#include <vector>
#include <map>
#include <string>

std::vector<double> TestFunc1(std::string TestString)
{
    std::map<std::string, std::vector<double>> TestMap;

    TestMap["Vector1"] = {357.12, 0.003};
    TestMap["Vector2"] = {0.0009, 1.54};

    return(TestMap[TestString]);
}

std::vector<double> TestFunc2(double Number)
{
	std::string Vector1 = "Vector1";
	std::string Vector2 = "Vector2";

    std::vector<double> ReturnVector1 = TestFunc1(Vector1);
    std::vector<double> ReturnVector2 = TestFunc1(Vector2);

    double Result1test = Number * ReturnVector1[0] + ReturnVector1[1];
    double Result2test = Number * ReturnVector2[0] + ReturnVector2[1];

    std::vector<double> ReturnParams = {Result1test, Result2test};

    return(ReturnParams);
}

int main()
{
    double Number = 1.5;

    std::vector<double> Result = TestFunc2(Number);

	std::cout << "Result1 * Result2: " << Result[0] * Result[1];
}