#include <iostream>


int Test(double Number)
{
    if(Number != 5)
    {
        std::cout << "Not == 5" ;
    }

    else
    {
        std::cout << "It is == 5";
    }
}


int main()
{
    double Number;

    std::cout << "Insert number: ";
    std::cin >> Number;
    Test(Number);
}