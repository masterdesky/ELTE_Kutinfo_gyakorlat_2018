#include <iostream>


// Time is normalized into [0h,24h[ intervals
double NormalizeZeroBoundedTime(double Time)
{
    int Multiply;

    if(Time >= 24)
    {
        Multiply = int(Time / 24);
        Time = Time - Multiply * 24;
    }

    else if(Time < 0)
    {
        Multiply = int(Time / 24) - 1;
        Time = Time + std::abs(Multiply) * 24;
    }

    else
    {
        Multiply = 0;
    }

    return(Time, Multiply);
}

int main()
{
    double Time = 25.654;

    double Time, int Multiply = NormalizeZeroBoundedTime(Time);

    std::cout << "Anyad faszat: " << Time << ", " << Multiply;
    
}