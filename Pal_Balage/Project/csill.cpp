/////////////////////////////////////////////////////////////////////////////////////////////////////
////////  ______             __  __  __    __                               ______  ______     //////
//////   /      \           |  \|  \|  \   \_\                              |      \|      \     ////
//////  |  $$$$$$\  _______  \$$| $$| $$  ______    _______  ________        \$$$$$$ \$$$$$$     ////
//////  | $$   \$$ /       \|  \| $$| $$ /      \  /       \|        \        | $$    | $$       ////
//////  | $$      |  $$$$$$$| $$| $$| $$|  $$$$$$\|  $$$$$$$ \$$$$$$$$        | $$    | $$       ////
//////  | $$   __  \$$    \ | $$| $$| $$| $$    $$ \$$    \   /    $$         | $$    | $$       ////
//////  | $$__/  \ _\$$$$$$\| $$| $$| $$| $$$$$$$$ _\$$$$$$\ /  $$$$_        _| $$_  _| $$_      ////
//////   \$$    $$|       $$| $$| $$| $$ \$$     \|       $$|  $$    \      |   $$ \|   $$ \     ////
//////    \$$$$$$  \$$$$$$$  \$$ \$$ \$$  \$$$$$$$ \$$$$$$$  \$$$$$$$$       \$$$$$$ \$$$$$$     ////
//////                                            __                                             ////
//////                                           / _|                                            ////
//////                                          | |_ _ __ ___  _ __ ___                          ////
//////                                          |  _| '__/ _ \| '_ ` _ \                         ////
//////              _______            __       | | | | | (_) | | | | | |                        ////
//////             /       \          /  |      |_| |_|  \___/|_| |_| |_|                        ////
//////             $$$$$$$  | ______  $$ |  ______    ______    ______                           ////
//////             $$ |__$$ |/      \ $$ | /      \  /      \  /      \                          ////
//////             $$    $$/ $$$$$$  |$$ |/$$$$$$  |/$$$$$$  |/$$$$$$  |                         ////
//////             $$$$$$$/  /    $$ |$$ |$$    $$ |$$    $$ |$$    $$ |                         ////
//////             $$ |     /$$$$$$$ |$$ |$$$$$$$$/ $$$$$$$$/ $$$$$$$$/                          ////
//////             $$ |     $$    $$ |$$ |$$       |$$       |$$       |                         ////
//////             $$/       $$$$$$$/ $$/  $$$$$$$/  $$$$$$$/  $$$$$$$/                          ////
//////                                                                                           ////
//////                                                                                           ////
//////        > Conversion Between Coordinate Systems                                            ////
//////        > Calculate Geographical Distances                                                 ////
//////        > Convert Sidereal Time/Local Mean Sidereal Time (S, LMST)                         ////
//////        > Calculate Datetimes of Sunrises and Sunsets                                      ////
//////        > Calculate Twilights' Correct Datetimes at Specific Locations                     ////
//////        > Draw Sun's Path on Earth during a Choosen Year                                   ////
//////        > Solve Csillész II End-Semester Homework with One Click                           ////
//////        > Draw Sun Analemma for a Choosen Year                                             ////
//////       Future:                                                                             ////
//////        > Better Optimalization and Greater Precision                                      ////
////////                                                                                       //////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////////                                                                                       //////
//////        USED LEGENDS AND LABELS:                                                           ////
//////                                                                                           ////
//////        φ: Latitude                                                                        ////
//////        λ: Longitude                                                                       ////
//////        H: Local Hour Angle in Degrees                                                     ////
//////        t/LHA: Local Hour Angle in Hours                                                   ////
//////        S/LMST: Local Mean Sidereal Time                                                   ////
//////        S_0/GMST: Greenwich Mean Sidereal Time                                             ////
//////        A: Azimuth at Horizontal Coords                                                    ////
//////        m: Altitude at Horizontal Coords                                                   ////
//////        δ: Declination at Equatorial Coords                                                ////
//////        α/RA: Right Ascension at Equatorial Coords                                         ////
//////        ε: Obliquity of the equator of the planet compared to the orbit of the planet      ////
//////        Π: Perihelion of the planet, relative to the ecliptic and vernal equinox           ////
////////                                                                                       //////
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <vector>
//#include "csill.h"


// Current Version of the Csillész II Problem Solver
std::string ActualVersion = "v1.32";


//////////////////////////////////////////////////////////////////////////////////
//////////////////                                                ////////////////
//////////////////       CONSTANTS FOR CALCULATIONS HEADER        ////////////////
//////////////////                                                ////////////////
//////////////////////////////////////////////////////////////////////////////////

// Pi
double Pi = 3.14159265358979323846264338327950288419716939937510L;

// Earth's Radius
double R = 6378e03;

// Lenght of 1 Solar Day = 1.002737909350795 Sidereal Days
// It's Usually Labeled as dS/dm
// We Simply Label It as dS
double dS = 1.002737909350795;

// Months' length int days, without leap day
int MonthLengthList[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

// Months' length int days, with leap day
int MonthLengthListLeapYear[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

// Predefined Coordinates of Some Notable Cities
// Format:
// "LocationName": [N Latitude (φ), E Longitude(λ)]
// Latitude: + if N, - if S
// Longitude: + if E, - if W
std::vector<double> LocationDictFunc(std::string Location)
{
    std::map<std::string, std::vector<double>> LocationDict;

    LocationDict["Amsterdam"] = {52.3702, 4.8952};
    LocationDict["Athen"] = {37.9838, 23.7275};
    LocationDict["Baja"] = {46.1803, 19.0111};
    LocationDict["Beijing"] = {39.9042, 116.4074};
    LocationDict["Berlin"] = {52.5200, 13.4050};
    LocationDict["Budapest"] = {47.4979, 19.0402};
    LocationDict["Budakeszi"] = {47.5136, 18.9278};
    LocationDict["Budaors"] = {47.4621, 18.9530};
    LocationDict["Brussels"] = {50.8503, 4.3517};
    LocationDict["Debrecen"] = {47.5316, 21.6273};
    LocationDict["Dunaujvaros"] = {46.9619, 18.9355};
    LocationDict["Gyor"] = {47.6875, 17.6504};
    LocationDict["Jerusalem"] = {31.7683, 35.2137};
    LocationDict["Kecskemet"] = {46.8964, 19.6897};
    LocationDict["London"] = {51.5074, -0.1278};
    LocationDict["Mako"] = {46.2219, 20.4809};
    LocationDict["Miskolc"] = {48.1035, 20.7784};
    LocationDict["Nagykanizsa"] = {46.4590, 16.9897};
    LocationDict["NewYork"] = {40.7128, -74.0060};
    LocationDict["Paris"] = {48.8566, 2.3522};
    LocationDict["Piszkesteto"] = {47.91806, 19.8942};
    LocationDict["Pecs"] = {46.0727, 18.2323};
    LocationDict["Rio"] = {-22.9068, -43.1729};
    LocationDict["Rome"] = {41.9028, 12.4964};
    LocationDict["Szeged"] = {46.2530, 20.1414};
    LocationDict["Szeghalom"] = {47.0239, 21.1667};
    LocationDict["Szekesfehervar"] = {47.1860, 18.4221};
    LocationDict["Szombathely"] = {47.2307, 16.6218};
    LocationDict["Tokyo"] = {35.6895, 139.6917};
    LocationDict["Washington"] = {47.7511, -120.7401};
    LocationDict["Zalaegerszeg"] = {46.8417, 16.8416};

    return(LocationDict[Location]);
}

// Predefined Equatorial I Coordinates of Some Notable Stellar Objects
// Format:
// "StarName": [Right Ascension (RA), Declination (δ)]
std::vector<double> StellarDictFunc(std::string Object)
{
    std::map<std::string, std::vector<double>> StellarDict;

    StellarDict["Achernar"] = {1.62857, -57.23675};
    StellarDict["Aldebaran"] = {4.59868, 16.50930};
    StellarDict["Algol"] = {3.13614, 40.95565};
    StellarDict["AlphaAndromedae"] = {0.13979, 29.09043};
    StellarDict["AlphaCentauri"] = {14.66014, -60.83399};
    StellarDict["AlphaPersei"] = {3.40538, 49.86118};
    StellarDict["Alphard"] = {9.45979, -8.65860};
    StellarDict["Altair"] = {19.8625, 8.92278};
    StellarDict["Antares"] = {16.49013, -26.43200};
    StellarDict["Arcturus"] = {14.26103, 19.18222};
    StellarDict["BetaCeti"] = {0.72649, -17.986605};
    StellarDict["BetaUrsaeMajoris"] = {11.03069, 56.38243};
    StellarDict["BetaUrsaeMinoris"] = {14.84509, 74.15550};
    StellarDict["Betelgeuse"] = {5.91953, 7.407064};
    StellarDict["Canopus"] = {6.39920, -52.69566};
    StellarDict["Capella"] = {5.278155, 45.99799};
    StellarDict["Deneb"] = {20.69053, 45.28028};
    StellarDict["Fomalhaut"] = {22.960845, -29.62223};
    StellarDict["GammaDraconis"] = {17.94344, 51.4889};
    StellarDict["GammaVelorum"] = {8.15888, -47.33658};
    StellarDict["M31"] = {0.712305, 41.26917};
    StellarDict["Polaris"] = {2.53030, 89.26411};
    StellarDict["Pollux"] = {7.75526, 28.02620};
    StellarDict["ProximaCentauri"] = {14.49526, -62.67949};
    StellarDict["Rigel"] = {5.24230, -8.20164};
    StellarDict["Sirius"] = {6.75248, -16.716116};
    StellarDict["Vega"] = {18.61565, 38.78369};
    StellarDict["VYCanisMajoris"] = {7.38287, -25.767565};

    return(StellarDict[Object]);
}


// Constants for Planetary Orbits
// Format:
// "PlanetNameX": [X_0, X_1, X_2 .., X_E.] or [X_1, X_3, ..., X_E] etc.
// "PlanetNameOrbit": [Π, ε, Correction for Refraction and Sun's visible shape]
std::vector<double> OrbitDictFunc(std::string Planet)
{

    std::map<std::string, std::vector<double>> OrbitDict;

    OrbitDict["MercuryM"] = {174.7948, 4.09233445};
    OrbitDict["MercuryC"] = {23.4400, 2.9818, 0.5255, 0.1058, 0.0241, 0.0055, 0.0026};
    OrbitDict["MercuryA"] = {-0.0000, 0.0000, 0.0000, 0.0000};
    OrbitDict["MercuryD"] = {0.0351, 0.0000, 0.0000, 0.0000};
    OrbitDict["MercuryJ"] = {45.3497, 11.4556, 0.00000, 175.9386};
    OrbitDict["MercuryH"] = {0.035, 0.00000, 0.00000};
    OrbitDict["MercuryOrbit"] = {230.3265, 0.0351, -0.69};

    OrbitDict["VenusM"] = {50.4161, 1.60213034};
    OrbitDict["VenusC"] = {0.7758, 0.0033, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000};
    OrbitDict["VenusA"] = {-0.0304, 0.00000, 0.00000, 0.0001};
    OrbitDict["VenusD"] = {.6367, 0.0009, 0.00000, 0.0036};
    OrbitDict["VenusJ"] = {52.1268, -0.2516, 0.0099, -116.7505};
    OrbitDict["VenusH"] = {2.636, 0.001, 0.00000};
    OrbitDict["VenusOrbit"] = {73.7576,	2.6376, -0.37};

    OrbitDict["EarthM"] = {357.5291, 0.98560028};
    OrbitDict["EarthJ"] = {0.0009, 0.0053, -0.0068, 1.0000000};
    OrbitDict["EarthC"] = {1.9148, 0.0200, 0.0003, 0.00000, 0.00000, 0.00000, 0.00000};
    OrbitDict["EarthA"] = {-2.4657, 0.0529, -0.0014, 0.0003};
    OrbitDict["EarthD"] = {22.7908, 0.5991, 0.0492, 0.0003};
    OrbitDict["EarthH"] = {22.137, 0.599, 0.016};
    OrbitDict["EarthOrbit"] = {102.9373, 23.4393, -0.83};

    OrbitDict["MarsM"] = {19.3730, 0.52402068};
    OrbitDict["MarsC"] = {10.6912, 0.6228, 0.0503, 0.0046, 0.0005, 0.00000, 0.0001};
    OrbitDict["MarsA"] = {-2.8608, 0.0713, -0.0022, 0.0004};
    OrbitDict["MarsD"] = {24.3880, 0.7332, 0.0706, 0.0011};
    OrbitDict["MarsJ"] = {0.9047, 0.0305, -0.0082, 1.027491};
    OrbitDict["MarsH"] = {23.576, 0.733, 0.024};
    OrbitDict["MarsOrbit"] = {71.0041, 25.1918, -0.17};

    OrbitDict["JupiterM"] = {20.0202, 0.08308529};
    OrbitDict["JupiterC"] = {5.5549, 0.1683, 0.0071, 0.0003, 0.00000, 0.00000, 0.0001};
    OrbitDict["JupiterA"] = {-0.0425, 0.00000, 0.00000, 0.0001};
    OrbitDict["JupiterD"] = {3.1173, 0.0015, 0.00000, 0.0034};
    OrbitDict["JupiterJ"] = {0.3345, 0.0064, 0.00000, 0.4135778};
    OrbitDict["JupiterH"] = {3.116, 0.002, 0.00000};
    OrbitDict["JupiterOrbit"] = {237.1015, 3.1189, -0.05};

    OrbitDict["SaturnM"] = {317.0207, 0.03344414};
    OrbitDict["SaturnC"] = {6.3585, 0.2204, 0.0106, 0.0006, 0.00000, 0.00000, 0.0001};
    OrbitDict["SaturnA"] = {-3.2338, 0.0909, -0.0031, 0.0009};
    OrbitDict["SaturnD"] = {25.7696, 0.8640, 0.0949, 0.0010};
    OrbitDict["SaturnJ"] = {0.0766, 0.0078, -0.0040, 0.4440276};
    OrbitDict["SaturnH"] = {24.800, 0.864, 0.032};
    OrbitDict["SaturnOrbit"] = {99.4587, 26.7285, -0.03};

    OrbitDict["UranusM"] = {141.0498, 0.01172834};
    OrbitDict["UranusC"] = {5.3042, 0.1534, 0.0062, 0.0003, 0.00000, 0.00000, 0.0001};
    OrbitDict["UranusA"] = {-42.5874, 12.8117, -2.6077, 17.6902};
    OrbitDict["UranusD"] = {56.9083, -0.8433, 26.1648, 3.34};
    OrbitDict["UranusJ"] = {0.1260, -0.0106, 0.0850, -0.7183165};
    OrbitDict["UranusH"] = {28.680, -0.843, 8.722};
    OrbitDict["UranusOrbit"] = {5.4634, 82.2298, -0.01};

    OrbitDict["NeptunusM"] = {256.2250, 0.00598103};
    OrbitDict["NeptunusC"] = {1.0302, 0.0058, 0.00000, 0.00000, 0.00000, 0.00000, 0.0001};
    OrbitDict["NeptunusA"] = {-3.5214, 0.1078, -0.0039, 0.0163};
    OrbitDict["NeptunusD"] = {26.7643, 0.9669, 0.1166, 0.060};
    OrbitDict["NeptunusJ"] = {0.3841, 0.0019, -0.0066, 0.6712575};
    OrbitDict["NeptunusH"] = {26.668, 0.967, 0.039};
    OrbitDict["NeptunusOrbit"] = {182.2100, 27.8477, -0.01};

    OrbitDict["PlutoM"] = {14.882, 0.00396};
    OrbitDict["PlutoC"] = {28.3150, 4.3408, 0.9214, 0.2235, 0.0627, 0.0174, 0.0096};
    OrbitDict["PlutoA"] = {-19.3248, 3.0286, -0.4092, 0.5052};
    OrbitDict["PlutoD"] = {49.8309, 4.9707, 5.5910, 0.19};
    OrbitDict["PlutoJ"] = {4.5635, -0.5024, 0.3429, 6.387672};
    OrbitDict["PlutoH"] = {38.648, 4.971, 1.864};
    OrbitDict["PlutoOrbit"] = {184.5484, 119.6075, -0.01};

    return(OrbitDict[Planet]);
}

////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////               UTILITY FUNCTIONS                ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////

// Normalization with Bound [0,NonZeroBound]
double NormalizeZeroBounded(double Parameter, double NonZeroBound)
{

    if(Parameter >= NonZeroBound)
    {
        Parameter = Parameter - (int(Parameter / NonZeroBound)) * NonZeroBound;
    }

    else if(Parameter < 0)
    {
        Parameter = Parameter + (abs(int(Parameter / NonZeroBound)) + 1) * NonZeroBound;
    }
    return(Parameter);
}

// Time is normalized into [0h,24h[ intervals
std::vector<double> NormalizeZeroBoundedTime(double Time)
{
    double Multiply;

    if(Time >= 24)
    {
        Multiply = int(Time / 24);
        Time = Time - Multiply * 24;
    }

    else if(Time < 0)
    {
        Multiply = int(Time / 24) - 1;
        Time = Time + abs(Multiply) * 24;
    }

    else
    {
        Multiply = 0;
    }

    std::vector<double> NormZeroTime = {Time, Multiply};

    return(NormZeroTime);
}

// Normalization Between to [-π,+π[
double NormalizeSymmetricallyBoundedPI(double Parameter)
{
    if(Parameter < 0 || Parameter >= 360)
    {
        Parameter = NormalizeZeroBounded(Parameter, 360);
    }

    if(Parameter > 180)
    {
        Parameter = Parameter - 360;
    }

    return(Parameter);
}

// Normalization Between to [-π/2,+π/2]
double NormalizeSymmetricallyBoundedPI_2(double Parameter)
{
    
    if(Parameter < 0 || Parameter >= 360)
    {
        Parameter = NormalizeZeroBounded(Parameter, 360);
    }

    if(Parameter > 90 && Parameter <= 270)
    {
        Parameter = - (Parameter - 180);
    }

    else if(Parameter > 270 && Parameter <= 360)
    {
        Parameter = Parameter - 360;
    }

    return(Parameter);

}

std::vector<double> NormalizeTimeParameters(double Time, double Year, double Month, double Day)
{
    // Function call: Time, Hours, Minutes, Seconds, Year, Month, Day = NormalizeTimeParameters(Time, Year, Month, Day)

    // First normalize Time if abs(Time) >= 24
    std::vector<double> TimeMultiply = NormalizeZeroBoundedTime(Time);

    // Declare variables
    double Hours;
    double Minutes;
    double Seconds;
    double CountingIndex;
    double Time = TimeMultiply[0];
    double Multiply = TimeMultiply[1];

    // CORRECTIONS IF MINUTES >= 60 or SECONDS >= 60
    Hours = int(Time);
    Minutes = int((Time - Hours) * 60);

    if(Minutes >= 60)
    {
        Minutes = NormalizeZeroBounded(Minutes, 60);
        Hours += 1;
    }

    if(Hours >= 24)
    {
        Hours = NormalizeZeroBounded(Hours, 24);
        Day += 1;
    }

    if(int(Year)%4 == 0 && (int(Year)%100 != 0 || int(Year)%400 == 0))
    {
        if(Day > MonthLengthListLeapYear[int(Month) - 1])
        {
            Month =+ 1;
        }
    }

    else
    {
        if(Day > MonthLengthList[int(Month) - 1])
        {
            Month += 1;
        }
    }

    if(Month > 12)
    {
        Month = 1;
        Year =+ 1;
    }

    Seconds = int((((Time - Hours) * 60) - Minutes) * 60);
    if(Seconds >= 60)
    {
        Seconds = NormalizeZeroBounded(Seconds, 60);
        Minutes += 1;
    }

    if(Minutes >= 60)
    {
        Minutes = NormalizeZeroBounded(Minutes, 60);
        Hours += 1;
    }

    if(Hours >= 24)
    {
        Hours = NormalizeZeroBounded(Hours, 24);
        Day += 1;
    }

    if(int(Year)%4 == 0 && (int(Year)%100 != 0 || int(Year)%400 == 0))
    {
        if(Day > MonthLengthListLeapYear[int(Month) - 1])
        {
            Month =+ 1;
        }
    }

    else
    {
        if(Day > MonthLengthList[int(Month) - 1])
            Month += 1;
    }

    if(Month > 12)
    {
        Month = 1;
        Year =+ 1;
    }

    // CORRECTIONS IF abs(Time) >= 24
    if(Multiply != 0)
    {
        Day = Day + Multiply;
        CountingIndex = Multiply;
    }

    else
    {
        CountingIndex = 0;
    }

    while(1)
    {
        if(int(Year)%4 == 0 && (int(Year)%100 != 0 || int(Year)%400 == 0))
        {
            if(Day > MonthLengthListLeapYear[int(Month) - 1])
            {
                Day = Day - MonthLengthListLeapYear[int(Month) - 1];
                Month = Month + 1;
                if(Month == 13)
                {
                    Month = 1;
                    Year = Year + 1;
                }

                if(Day > MonthLengthListLeapYear[int(Month) - 1])
                {
                    CountingIndex = CountingIndex - MonthLengthListLeapYear[int(Month) - 1];
                }

                else
                {
                    CountingIndex = 0;
                    break;
                }
            }

            else
            {
                break;
            }
        }

        if(int(Year)%4 != 0)
        {
            if(Day > MonthLengthList[int(Month) - 1])
            {
                Day = Day - MonthLengthList[int(Month) - 1];
                Month = Month + 1;
                if(Month == 13)
                {
                    Month = 1;
                    Year = Year + 1;
                }

                if(Day > MonthLengthList[int(Month) - 1])
                {
                    CountingIndex = CountingIndex - MonthLengthList[int(Month) - 1];
                }
                
                else
                {
                    CountingIndex = 0;
                    break;
                }
            }

            else
            {
                break;
            }
        }
    }


    std::vector<double> NormTimeParam = {Time, Hours, Minutes, Seconds, Year, Month, Day};
    return(NormTimeParam);
}

// Normalization and Conversion of Local Time to United Time
std::vector <double> LTtoUT(float Longitude, double LocalHours, double LocalMinutes, double LocalSeconds, double DateYear, double DateMonth, double DateDay)
{

    // Declare variables
    double LocalTime;
    double UnitedTime;

    // Calculate United Time
    LocalTime = LocalHours + LocalMinutes/60 + LocalSeconds/3600;
    // Normalize LT
    LocalTime = NormalizeZeroBounded(LocalTime, 24);

    // Summer/Winter Saving time
    // Summer: March 26/31 - October 8/14 LT+1
    // Winter: October 8/14 - March 26/31 LT+0
    // ISN'T NEEDED
    if((DateMonth > 3 and DateMonth < 10) || ((DateMonth == 3 and DateDay >=25) || (DateMonth == 10 && (DateDay >= 8 && DateDay <=14))))
    {
        UnitedTime = LocalTime - (std::round(Longitude/15) + 1);
    }

    else
    {
        UnitedTime = LocalTime - std::round(Longitude/15);
    }

    //UnitedTime = LocalTime - round(Longitude/15, 0)

    // Apply corrections if United Time is not in the correct format
    // returns: UnitedTime, UnitedHours, UnitedMinutes, UnitedSeconds, UnitedDateYear, UnitedDateMonth, UnitedDateDay
    std::vector<double> LTtoUTvec = NormalizeTimeParameters(UnitedTime, DateYear, DateMonth, DateDay);
    return(LTtoUTvec);

}

std::vector<double> UTtoLT(double Longitude, double UnitedHours, double UnitedMinutes, double UnitedSeconds, double UnitedDateYear, double UnitedDateMonth, double UnitedDateDay)
{
    // Declare variables
    double UnitedTime;
    double LocalTime;

    // Calculate United Time
    UnitedTime = UnitedHours + UnitedMinutes/60 + UnitedSeconds/3600;
    // Normalize LT
    UnitedTime = NormalizeZeroBounded(UnitedTime, 24);

    // Summer/Winter Saving time
    // Summer: March 26/31 - October 8/14 LT+1
    // Winter: October 8/14 - March 26/31 LT+0
    // ISN'T NEEDED
    if((UnitedDateMonth > 3 && UnitedDateMonth < 10) || ((UnitedDateMonth == 3 && UnitedDateDay >=25) || (UnitedDateMonth == 10 && (UnitedDateDay >= 8 && UnitedDateDay <=14))))
    {
        LocalTime = UnitedTime + (std::round(Longitude/15) + 1);
    }

    else
    {
        LocalTime = UnitedTime + std::round(Longitude/15);
    }

    // Apply corrections if Local Time is not in the correct format
    // returns: LocalTime, LocalHours, LocalMinutes, LocalSeconds, LocalDateYear, LocalDateMonth, LocalDateDay
    std::vector<double> UTtoLTvec = NormalizeTimeParameters(LocalTime, UnitedDateYear, UnitedDateMonth, UnitedDateDay);

    // Correction for Julian Date
    //LocalHours += 12
    //LocalHours = NormalizeZeroBounded(LocalHours, 24)

    // Apply Correction for Local Time
    //LocalTime = LocalHours + LocalMinutes/60 + LocalSeconds/3600

    return(UTtoLTvec);
}

// Calculate Greenwich Mean Sidereal Time (GMST = S_0) at UT 00:00 on Given Date
double CalculateGMST(float Longitude, double UnitedHoursForGMST, double UnitedMinutesForGMST, double UnitedSecondsForGMST, int UnitedDateYear, int UnitedDateMonth, int UnitedDateDay)
{
    // JulianDays = UT days since J2000.0, including parts of a day
    // Could be + or - or 0
    //Dwhole = int(int(1461 * int(UnitedDateYear + 4800 + (UnitedDateMonth - 14) / 12)) / 4) + int((367 * (UnitedDateMonth - 2 - 12 * int((UnitedDateMonth - 14) / 12))) / 12) - int((3 * int((UnitedDateYear + 4900 + (UnitedDateMonth - 14)/12) / 100)) / 4) + UnitedDateDay - 32075
    //Dwhole = 367 * UnitedDateYear - int(int(7 * (UnitedDateYear + 5001 + (UnitedDateMonth - 9) / 7)) / 4) + int((275 * UnitedDateMonth) / 9) + UnitedDateDay + 1729777
    double Dwhole = 367 * UnitedDateYear - int(7 * (UnitedDateYear + int((UnitedDateMonth + 9) / 12)) / 4) + int(275 * UnitedDateMonth / 9) + UnitedDateDay - 730531.5;
    // Dfrac: Fraction of the day
    // If UT = 00:00:00, then Dfrac = 0
    double Dfrac = (UnitedHoursForGMST + UnitedMinutesForGMST/60 + UnitedSecondsForGMST/3600)/24;
    double JulianDays = Dwhole + Dfrac;

    // Number of Julian centuries since J2000.0
    double JulianCenturies = JulianDays / 36525;

    // Calculate GMST in Degrees
    double GMSTDegrees = 280.46061837 + 360.98564736629 * JulianDays + 0.000388 * pow(JulianCenturies, 2);

    // Normalize between to [0,+2π[
    GMSTDegrees = NormalizeZeroBounded(GMSTDegrees, 360);

    // Convert GMST to Hours
    double GMST = GMSTDegrees / 15;

    return(GMST);
}



////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////      1. CONVERSION OF COORDINATE SYSTEMS       ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////

// 1. Horizontal to Equatorial I
std::vector<double> HorToEquI(float Latitude, double Altitude, double Azimuth, double LocalSiderealTime)
{

    // Declare variables
    double RightAscension;
    double Declination;
    double LocalHourAngle;
    double LocalHourAngleDegrees;
    double LocalHourAngleDegrees1_1;
    double LocalHourAngleDegrees1_2;
    double LHAcos2_1;
    double LocalHourAngleDegrees2_1;
    double LocalHourAngleDegrees2_2;

    // Initial Data Normalization
    // Latitude: [-π,+π]
    // Altitude: [-π/2,+π/2]
    // Azimuth: [0,+2π[
    // Local Mean Sidereal Time: [0,24h[
    Latitude = NormalizeSymmetricallyBoundedPI(Latitude);
    Altitude = NormalizeSymmetricallyBoundedPI_2(Altitude);
    Azimuth = NormalizeZeroBounded(Azimuth, 360);

    if (LocalSiderealTime != NULL)
    {
        LocalSiderealTime = NormalizeZeroBounded(LocalSiderealTime, 24);
    }

    // Calculate Declination (δ)
    // sin(δ) = sin(m) * sin(φ) + cos(m) * cos(φ) * cos(A)
    Declination =  (180 / Pi) * (asin(
                   sin((Pi / 180) * (Altitude)) * sin((Pi / 180) * (Latitude)) +
                   cos((Pi / 180) * (Altitude)) * cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (Azimuth))
                   ));
    // Normalize result for Declination [-π/2,+π/2]
    Declination = NormalizeSymmetricallyBoundedPI_2(Declination);

    // Calculate Local Hour Angle in Degrees (H)
    // sin(H) = - sin(A) * cos(m) / cos(δ)
    LocalHourAngleDegrees1_1 = (180 / Pi) * (asin(
                            - sin((Pi / 180) * (Azimuth)) * cos((Pi / 180) * (Altitude)) / cos((Pi / 180) * (Declination))
                            ));

    if(LocalHourAngleDegrees1_1 <= 180)
    {
        LocalHourAngleDegrees1_2 = 180 - LocalHourAngleDegrees1_1;
    }

    else if(LocalHourAngleDegrees1_1 > 180)
    {
        LocalHourAngleDegrees1_2 = 540 - LocalHourAngleDegrees1_1;
    }

    // Check correct value
    // cos(H) = (sin(m) - sin(δ) * sin(φ)) / cos(δ) * cos(φ)
    LHAcos2_1 = (sin((Pi / 180) * (Altitude)) - sin((Pi / 180) * (Declination)) * sin((Pi / 180) * (Latitude))) / (cos((Pi / 180) * (Declination)) * cos((Pi / 180) * (Latitude)));

    if(LHAcos2_1 <= 1 and LHAcos2_1 >= -1)
    {
        LocalHourAngleDegrees2_1 = (180 / Pi) * (acos(LHAcos2_1));
    }

    else if(LHAcos2_1 > 1)
    {
        LocalHourAngleDegrees2_1 = (180 / Pi) * (acos(1));
    }

    else if(LHAcos2_1 < -1)
    {
        LocalHourAngleDegrees2_1 = (180 / Pi) * (acos(-1));
    }

    LocalHourAngleDegrees2_2 = - LocalHourAngleDegrees2_1;

    // Compare Azimuth values
    if(int(LocalHourAngleDegrees1_1) == int(LocalHourAngleDegrees2_1))
    {
        LocalHourAngleDegrees = LocalHourAngleDegrees1_1;
    }

    else if(int(LocalHourAngleDegrees1_1) == int(LocalHourAngleDegrees2_2))
    {
        LocalHourAngleDegrees = LocalHourAngleDegrees1_1;
    }

    else
    {
        LocalHourAngleDegrees = LocalHourAngleDegrees1_2;
    }

    // Normalize result [0,+2π[
    LocalHourAngleDegrees = NormalizeZeroBounded(LocalHourAngleDegrees, 360);
    // Convert to hours from angles (H -> t)
    LocalHourAngle = LocalHourAngleDegrees / 15;

    if(LocalSiderealTime != NULL)
    {
        // Calculate Right Ascension (α)
        // α = S – t
        RightAscension = LocalSiderealTime - LocalHourAngle;
    }

    else
    {
        RightAscension = NULL;
    }

    std::vector<double> HorToEquIvec = {RightAscension, Declination, LocalHourAngle};
    return(HorToEquIvec);
}

// 2. Horizontal to Equatorial II
std::vector<double> HorToEquII(float Latitude, double Altitude, double Azimuth, double LocalSiderealTime)
{
    // First Convert Horizontal to Equatorial I Coordinates
    // returns: Declination, LocalHourAngle, RightAscension
    std::vector<double> DecLHARAHorToEquII = HorToEquI(Latitude, Altitude, Azimuth, LocalSiderealTime);

    //Declare variables
    double RightAscension = DecLHARAHorToEquII[0];
    double Declination = DecLHARAHorToEquII[1];
    double LocalHourAngle = DecLHARAHorToEquII[2];

    // Convert Equatorial I to Equatorial II
    LocalSiderealTime = LocalHourAngle + RightAscension;
    // Normalize LMST
    // LMST: [0,24h[
    LocalSiderealTime = NormalizeZeroBounded(LocalSiderealTime, 24);

    std::vector<double> HorToEquIIvec = {RightAscension, Declination, LocalSiderealTime};
    return(HorToEquIIvec);
}

// 3. Equatorial I to Horizontal
std::vector<double> EquIToHor(float Latitude, double RightAscension, double Declination, double Altitude, double LocalSiderealTime, double LocalHourAngle)
{
    // Initial Data Normalization
    // Latitude: [-π,+π]
    // Right Ascension: [0h,24h[
    // Declination: [-π/2,+π/2]
    Latitude = NormalizeSymmetricallyBoundedPI(Latitude);

    if(RightAscension != NULL)
    {
        RightAscension = NormalizeZeroBounded(RightAscension, 24);
    }

    if(Declination != NULL)
    {
        Declination = NormalizeSymmetricallyBoundedPI_2(Declination);
    }


    if(LocalSiderealTime != NULL)
    {
        // Calculate Local Hour Angle in Hours (t)
        // t = S - α
        LocalHourAngle = LocalSiderealTime - RightAscension;
        // Normalize LHA
        // LHA: [0h,24h[
        LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24);
    }

    if(LocalHourAngle != NULL)
    {
        // Declare variables
        double Azimuth;
        double Azimuth1;
        double Azimuth2;
        double Azimuth3;
        double Azimuth4;
        double LocalHourAngleDegrees;

        // Convert to angles from hours (t -> H)
        LocalHourAngleDegrees = LocalHourAngle * 15;

        // Calculate Altitude (m)
        // sin(m) = sin(δ) * sin(φ) + cos(δ) * cos(φ) * cos(H)
        Altitude = (180 / Pi) * (asin(
                sin((Pi / 180) * (Declination)) * sin((Pi / 180) * (Latitude)) +
                cos((Pi / 180) * (Declination)) * cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (LocalHourAngleDegrees))
                ));
        // Normalize Altitude
        // Altitude: [-π/2,+π/2]
        Altitude = NormalizeSymmetricallyBoundedPI_2(Altitude);

        // Calculate Azimuth (A)
        // sin(A) = - sin(H) * cos(δ) / cos(m)
        // Azimuth at given H Local Hour Angle
        Azimuth1 = (180 / Pi) * (asin(
                - sin((Pi / 180) * (LocalHourAngleDegrees)) * cos((Pi / 180) * (Declination)) / cos((Pi / 180) * (Altitude))
                ));

        Azimuth1 = NormalizeZeroBounded(Azimuth1, 360);

        if(Azimuth1 <= 180)
        {
            Azimuth2 = 180 - Azimuth1;
        }

        else if(Azimuth1 > 180)
        {
            Azimuth2 = 540 - Azimuth1;
        }

        // Calculate Azimuth (A) with a second method, to determine which one is the correct (A_1 or A_2?)
        // cos(A) = (sin(δ) - sin(φ) * sin(m)) / (cos(φ) * cos(m))
        Azimuth3 = (180 / Pi) * (acos(
                (sin((Pi / 180) * (Declination)) - sin((Pi / 180) * (Latitude)) * sin((Pi / 180) * (Altitude))) / 
                (cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (Altitude)))
                ));

        Azimuth4 = - Azimuth3;

        // Normalize negative result
        // Azimuth: [0,+2π[
        Azimuth4 = NormalizeZeroBounded(Azimuth4, 360);

        // Compare Azimuth values
        if(Azimuth1 + 3 > Azimuth3 and Azimuth1 - 3 < Azimuth3)
        {
            Azimuth = Azimuth1;
        }

        else if(Azimuth1 + 3 > Azimuth4 and Azimuth1 - 3 < Azimuth4)
        {
            Azimuth = Azimuth1;
        }

        else if(Azimuth2 + 3 > Azimuth3 and Azimuth2 - 3 < Azimuth3)
        {
            Azimuth = Azimuth2;
        }

        else if(Azimuth2 + 3 > Azimuth4 and Azimuth2 - 3 < Azimuth4)
        {
            Azimuth = Azimuth2;
        }

        else
        {
            std::cout << Azimuth1 << Azimuth2 << Azimuth3 << Azimuth4;
        }

        // Normalize Azimuth
        // Azimuth: [0,+2π[
        Azimuth = NormalizeZeroBounded(Azimuth, 360);

        std::vector<double> EquIToHorvec1 = {Altitude, Azimuth};
        return(EquIToHorvec1);
    }

    else if(Altitude != NULL)
    {

        // Declare variables
        double LHAcos;
        double LocalHourAngleDegrees1;
        double LocalHourAngleDegrees2;
        double Azimuth1;
        double Azimuth1_1;
        double Azimuth1_2;
        double Azimuth1_3;
        double Azimuth1_4;

        double Azimuth2;
        double Azimuth2_1;
        double Azimuth2_2;
        double Azimuth2_3;
        double Azimuth2_4;

        double H_dil;

        // Starting Equations: 
        // sin(m) = sin(δ) * sin(φ) + cos(δ) * cos(φ) * cos(H)
        // We can calculate eg. setting/rising with the available data (m = 0°), or other things...
        // First let's calculate LHA:
        // cos(H) = (sin(m) - sin(δ) * sin(φ)) / cos(δ) * cos(φ)
        LHAcos = (sin((Pi / 180) * (Altitude)) - sin((Pi / 180) * (Declination)) * sin((Pi / 180) * (Latitude))) / (cos((Pi / 180) * (Declination)) * cos((Pi / 180) * (Latitude)));
        if(LHAcos <= 1 and LHAcos >= -1)
        {
            LocalHourAngleDegrees1 = (180 / Pi) * (acos(LHAcos));
        }

        else if(LHAcos > 1)
        {
            LocalHourAngleDegrees1 = (180 / Pi) * (acos(1));
        }

        else if(LHAcos < -1)
        {
            LocalHourAngleDegrees1 = (180 / Pi) * (acos(-1));
        }
        
        // acos(x) has two correct output on this interval
        LocalHourAngleDegrees2 = - LocalHourAngleDegrees1;

        // Normalize LHAs:
        LocalHourAngleDegrees1 = NormalizeZeroBounded(LocalHourAngleDegrees1, 360);
        LocalHourAngleDegrees2 = NormalizeZeroBounded(LocalHourAngleDegrees2, 360);

        // Calculate Azimuth (A) for both Local Hour Angles!
        // Calculate Azimuth (A) for FIRST LOCAK HOUR ANGLE
        // sin(A) = - sin(H) * cos(δ) / cos(m)
        // Azimuth at given H Local Hour Angle
        Azimuth1_1 = (180 / Pi) * (asin(
                - sin((Pi / 180) * (LocalHourAngleDegrees2)) * cos((Pi / 180) * (Declination)) / cos((Pi / 180) * (Altitude))
                ));

        Azimuth1_1 = NormalizeZeroBounded(Azimuth1_1, 360);

        if(Azimuth1_1 <= 180)
        {
            Azimuth1_2 = 180 - Azimuth1_1;
        }

        else if(Azimuth1_1 > 180)
        {
            Azimuth1_2 = 540 - Azimuth1_1;
        }

        // Calculate Azimuth (A) with a second method, to determine which one is the correct (A1_1 or A1_2?)
        // cos(A) = (sin(δ) - sin(φ) * sin(m)) / (cos(φ) * cos(m))
        Azimuth1_3 = (180 / Pi) * (acos(
                (sin((Pi / 180) * (Declination)) - sin((Pi / 180) * (Latitude)) * sin((Pi / 180) * (Altitude))) / 
                (cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (Altitude)))
                ));

        Azimuth1_4 = - Azimuth1_3;

        // Normalize negative result
        // Azimuth: [0,+2π[
        Azimuth1_4 = NormalizeZeroBounded(Azimuth1_4, 360);

        // Compare Azimuth values
        if(Azimuth1_1 + 3 > Azimuth1_3 and Azimuth1_1 - 3 < Azimuth1_3)
        {
            Azimuth1 = Azimuth1_1;
        }

        else if(Azimuth1_1 + 3 > Azimuth1_4 and Azimuth1_1 - 3 < Azimuth1_4)
        {
            Azimuth1 = Azimuth1_1;
        }

        else if(Azimuth1_2 + 3 > Azimuth1_3 and Azimuth1_2 - 3 < Azimuth1_3)
        {
            Azimuth1 = Azimuth1_2;
        }

        else if(Azimuth1_2 + 3 > Azimuth1_4 and Azimuth1_2 - 3 < Azimuth1_4)
        {
            Azimuth1 = Azimuth1_2;
        }

        else
        {
            std::cout << Azimuth1_1 << ' ' << Azimuth1_2 << ' ' << Azimuth1_3 << ' ' << Azimuth1_4 << '\n';
        }

        // Calculate Azimuth (A) for SECOND LOCAL HOUR ANGLE
        // sin(A) = - sin(H) * cos(δ) / cos(m)
        // Azimuth at given H Local Hour Angle
        Azimuth2_1 = (180 / Pi) * (asin(
                - sin((Pi / 180) * (LocalHourAngleDegrees1)) * cos((Pi / 180) * (Declination)) / cos((Pi / 180) * (Altitude))
                ));

        Azimuth2_1 = NormalizeZeroBounded(Azimuth2_1, 360);

        if(Azimuth2_1 <= 180)
        {
            Azimuth2_2 = 180 - Azimuth2_1;
        }

        else if(Azimuth2_1 > 180)
        {
            Azimuth2_2 = 540 - Azimuth2_1;
        }

        // Calculate Azimuth (A) with a second method, to determine which one is the correct (A2_1 or A2_2?)
        // cos(A) = (sin(δ) - sin(φ) * sin(m)) / (cos(φ) * cos(m))
        Azimuth2_3 = (180 / Pi) * (acos(
                (sin((Pi / 180) * (Declination)) - sin((Pi / 180) * (Latitude)) * sin((Pi / 180) * (Altitude))) / 
                (cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (Altitude)))
                ));

        Azimuth2_4 = - Azimuth2_3;

        // Normalize negative result
        // Azimuth: [0,+2π[
        Azimuth2_4 = NormalizeZeroBounded(Azimuth2_4, 360);

        // Compare Azimuth values
        if(Azimuth2_1 + 3 > Azimuth2_3 and Azimuth2_1 - 3 < Azimuth2_3)
        {
            Azimuth2 = Azimuth2_1;
        }

        else if(Azimuth2_1 + 3 > Azimuth2_4 and Azimuth2_1 - 3 < Azimuth2_4)
        {
            Azimuth2 = Azimuth2_1;
        }

        else if(Azimuth2_2 + 3 > Azimuth2_3 and Azimuth2_2 - 3 < Azimuth2_3)
        {
            Azimuth2 = Azimuth2_2;
        }

        else if(Azimuth2_2 + 3 > Azimuth2_4 and Azimuth2_2 - 3 < Azimuth2_4)
        {
            Azimuth2 = Azimuth2_2;
        }

        else
        {
            std::cout << Azimuth2_1 << ' ' << Azimuth2_2 << ' ' << Azimuth2_3 << ' ' << Azimuth2_4 << '\n';
        }

        // Calculate time between them
        // Use precalculated LHAs
        // H_dil is the time, as long as the Object stays above the Horizon
        H_dil = abs(LocalHourAngleDegrees1 - LocalHourAngleDegrees2);

        std::vector<double> EquIToHorvec2 = {Altitude, Azimuth1, Azimuth2, H_dil};
        return(EquIToHorvec2);
    }
}


// 4. Equatorial I to Equatorial II
double EquIToEquII(double RightAscension, double LocalHourAngle)
{
    // Declare variable
    double LocalSiderealTime;

    LocalSiderealTime = LocalHourAngle + RightAscension;
    // Normalize LMST
    // LMST: [0,24h[
    LocalSiderealTime = NormalizeZeroBounded(LocalSiderealTime, 24);

    return(LocalSiderealTime);
}


// 5. Equatorial II to Equatorial I
std::vector<double> EquIIToEquI(double RightAscension, double LocalHourAngle, double LocalSiderealTime)
{
    // Calculate Right Ascension or Local Mean Sidereal Time
    if(RightAscension != NULL and LocalHourAngle == NULL)
    {
        LocalHourAngle = LocalSiderealTime - RightAscension;
        // Normalize LHA
        // LHA: [0,24h[
        LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24);
    }

    else if(RightAscension == NULL and LocalHourAngle != NULL)
    {
        RightAscension = LocalSiderealTime - LocalHourAngle;
        // Normalize Right Ascension
        // Right Ascension: [0,24h[
        RightAscension = NormalizeZeroBounded(RightAscension, 24);
    }

    else
    {}

    std::vector<double> EquIIToEquIvec = {RightAscension, LocalHourAngle};
    return(EquIIToEquIvec);
}


// 6. Equatorial II to Horizontal
std::vector<double> EquIIToHor(double Latitude, double RightAscension, double Declination, double Altitude, double Azimuth, double LocalHourAngle, double LocalSiderealTime)
{

    // Initial Data Normalization
    // Latitude: [-π,+π]
    // Local Mean Sidereal Time: [0h,24h[
    // Local Hour Angle: [0h,24h[
    // Right Ascension: [0h,24h[
    // Declination: [-π/2,+π/2]
    Latitude = NormalizeSymmetricallyBoundedPI(Latitude);
    LocalSiderealTime = NormalizeZeroBounded(LocalSiderealTime, 24);
    
    if(RightAscension == NULL and LocalHourAngle != NULL)
    {
        LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24);
    }

    else if(RightAscension != NULL and LocalHourAngle == NULL)
    {
        RightAscension = NormalizeZeroBounded(RightAscension, 24);
    }

    Declination = NormalizeSymmetricallyBoundedPI_2(Declination);

    // Convert Equatorial II to Equatorial I
    std::vector<double> EquIIToEquIvec = EquIIToEquI(LocalSiderealTime, RightAscension, LocalHourAngle);

    RightAscension = EquIIToEquIvec[0];
    LocalHourAngle = EquIIToEquIvec[1];

    // Normalization of Output Data
    LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24);
    RightAscension = NormalizeZeroBounded(RightAscension, 24);

    // Convert Equatorial I to Horizontal
    std::vector<double> EquIToHorvec  = EquIToHor(Latitude, RightAscension, Declination, Altitude, LocalSiderealTime, LocalHourAngle);

    Altitude = EquIToHorvec[0];
    Azimuth = EquIToHorvec[1];

    // Normalization of Output Data
    // Altitude: [-π/2,+π/2]
    // Azimuth: [0,+2π[
    Altitude = NormalizeSymmetricallyBoundedPI_2(Altitude);
    Azimuth = NormalizeZeroBounded(Azimuth, 360);

    std::vector<double> EquIIToHorvec = {Altitude, Azimuth};
    return(EquIIToHorvec);
}


////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////            2. GEOGRAPHICAL DISTANCE            ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////

// Calculate distances between coordinates
double GeogDistCalc(double Latitude1, double Latitude2, double Longitude1, double Longitude2)
{

    // Declare variables
    double hav_1;
    double hav_2;
    double Distance;

    // Initial Data Normalization
    // Latitude: [-π,+π]
    // Longitude: [0,+2π[
    Latitude1 = NormalizeSymmetricallyBoundedPI(Latitude1);
    Latitude2 = NormalizeSymmetricallyBoundedPI(Latitude2);
    Longitude1 = NormalizeZeroBounded(Longitude1, 360);
    Longitude2 = NormalizeZeroBounded(Longitude2, 360);

    // Haversine formula:
    // Step 1.: hav_1 = (sin((φ2 - φ1) / 2))^2 + cos(φ1) ⋅ cos(φ2) ⋅ (sin((λ2 - λ1) / 2))^2
    // Step 2.: hav_2 = 2 * atan2(sqrt(hav_1),sqrt(1 - hav_1))
    // Step 3.: d = R * hav_2

    // Step 1
    hav_1 = ( pow((sin((Pi / 180) * (Latitude2 - Latitude1) / 2)), 2) +
            ( cos((Pi / 180) * (Latitude1)) * cos((Pi / 180) * (Latitude2)) * pow((sin((Pi / 180) * (Longitude2 - Longitude1) / 2)), 2) ));

    // Step 2
    hav_2 = 2 * atan2(sqrt(hav_1), sqrt(1-hav_1));

    // Step 3
    Distance = R * hav_2;

    return(Distance);
}


////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
//////////////// 3. CALCULATE LOCAL MEAN SIDEREAL TIME (LMST)   ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////

// Calculate LMST from Predefined Coordinates
std::vector<double> LocalSiderealTimeCalc(double Longitude, double LocalHours, double LocalMinutes, double LocalSeconds, double DateYear, double DateMonth, double DateDay)
{
    // Initial Data Normalization
    // Longitude: [0,+2π[
    Longitude = NormalizeZeroBounded(Longitude, 360);

    std::vector<double> LTtoUTvec = LTtoUT(Longitude, LocalHours, LocalMinutes, LocalSeconds, DateYear, DateMonth, DateDay);

    double UnitedTime = LTtoUTvec[0];
    double UnitedHours = LTtoUTvec[1];
    double UnitedMinutes = LTtoUTvec[2];
    double UnitedSeconds = LTtoUTvec[3];
    double UnitedDateYear = LTtoUTvec[4];
    double UnitedDateMonth = LTtoUTvec[5];
    double UnitedDateDay = LTtoUTvec[6];

    // Calculate Greenwich Mean Sidereal Time (GMST)
    // Now UT = 00:00:00
    double UnitedHoursForGMST = 0;
    double UnitedMinutesForGMST = 0;
    double UnitedSecondsForGMST = 0;
    double S_0 = CalculateGMST(Longitude, UnitedHoursForGMST, UnitedMinutesForGMST, UnitedSecondsForGMST, UnitedDateYear, UnitedDateMonth, UnitedDateDay);

    // Greenwich Zero Time for Supervision
    std::vector<double> NormTimeParamvec1 = NormalizeTimeParameters(S_0, DateYear, DateMonth, DateDay);

    double GreenwichSiderealTime = NormTimeParamvec1[0];
    double GreenwichSiderealHours = NormTimeParamvec1[1];
    double GreenwichSiderealMinutes = NormTimeParamvec1[2];
    double GreenwichSiderealSeconds = NormTimeParamvec1[3];
    double SiderealDateYear =  NormTimeParamvec1[4];
    double SiderealDateMonth = NormTimeParamvec1[5];
    double SiderealDateDay = NormTimeParamvec1[6];

    // Calculate LMST
    double LMST = S_0 + Longitude/15 + dS * UnitedTime;

    // Norm LMST
    double LMSTNorm = NormalizeZeroBounded(LMST, 24);

    std::vector<double> NormTimeParamvec2 = NormalizeTimeParameters(LMSTNorm, DateYear, DateMonth, DateDay);

     double LocalSiderealTime = NormTimeParamvec2[0];
     double LocalSiderealHours = NormTimeParamvec2[1];
     double LocalSiderealMinutes = NormTimeParamvec2[2];
     double LocalSiderealSeconds = NormTimeParamvec2[3];
     double LocalDateYear = NormTimeParamvec2[4];
     double LocalDateMonth = NormTimeParamvec2[5];
     double LocalDateDay = NormTimeParamvec2[6];

    std::vector<double> LocalSiderealTimeCalc = {LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds,
                                                UnitedHours, UnitedMinutes, UnitedSeconds, 
                                                GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds};

    return(LocalSiderealTimeCalc);
}


////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////      4. CALCULATE DATETIMES OF TWILIGHTS       ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////

// Calculate actual Julian Date
double CalculateJulianDate(double LocalDateYear, double LocalDateMonth, double LocalDateDay, double UnitedHours, double UnitedMinutes, double UnitedSeconds)
{
    // Declare variables
    double Dwhole;
    double Dfrac;
    double JulianDays;

    // JulianDays = UT days since J2000.0, including parts of a day
    // Could be + or - or 0
    //Dwhole = int(int(1461 * int(LocalDateYear + 4800 + (LocalDateMonth - 14) / 12)) / 4) + int((367 * (LocalDateMonth - 2 - 12 * int((LocalDateMonth - 14) / 12))) / 12) - int((3 * int((LocalDateYear + 4900 + (LocalDateMonth - 14)/12) / 100)) / 4) + LocalDateDay - 32075;
    //Dwhole = 367 * LocalDateYear - int(int(7 * (LocalDateYear + 5001 + (LocalDateMonth - 9) / 7)) / 4) + int((275 * LocalDateMonth) / 9) + LocalDateDay + 1729777.
    Dwhole = 367 * LocalDateYear - int(7 * (LocalDateYear + int((LocalDateMonth + 9) / 12)) / 4) + int(275 * LocalDateMonth / 9) + LocalDateDay - 730531.5;
    //Dwhole = round(Dwhole, 0)
    // Dfrac: Fraction of the day
    Dfrac = (UnitedHours + UnitedMinutes/60 + UnitedSeconds/3600)/24;
    // Julian days
    JulianDays = Dwhole + Dfrac;

    return(JulianDays);
}

// Calculate Sun's Position
std::vector<double> SunsCoordinatesCalc(std::string Planet, double Longitude, double JulianDays)
{
    // 1. Mean Solar Noon
    // JAnomaly is an approximation of Mean Solar Time at WLongitude expressed as a Julian day with the day fraction
    // WLongitude is the longitude west (west is positive, east is negative) of the observer on the Earth
    double WLongitude = - Longitude;
    std::string PlanetJ = Planet.append("J");
    double JAnomaly = (JulianDays - OrbitDictFunc(PlanetJ)[0]) / OrbitDictFunc(PlanetJ)[3] - WLongitude/360;

    // 2. Solar Mean Anomaly
    // MeanAnomaly (M) is the Solar Mean Anomaly used in a few of next equations
    // MeanAnomaly = (M_0 + M_1 * (JulianDays-J2000)) and Norm to 360
    std::string PlanetM = Planet.append("M");
    double MeanAnomaly = (OrbitDictFunc(PlanetM)[0] + OrbitDictFunc(PlanetM)[1] * JulianDays);
    // Normalize Result
    MeanAnomaly = NormalizeZeroBounded(MeanAnomaly, 360);

    // 3. Equation of the Center
    // EquationOfCenter (C) is the Equation of the center value needed to calculate Lambda (see next equation)
    // EquationOfCenter = C_1 * sin(M) + C_2 * sin(2M) + C_3 * sin(3M) + C_4 * sin(4M) + C_5 * sin(5M) + C_6 * sin(6M)
    std::string PlanetC = Planet.append("C");
    double EquationOfCenter = (OrbitDictFunc(PlanetC)[0] * sin((Pi / 180) * (MeanAnomaly)) + OrbitDictFunc(PlanetC)[1] * sin((Pi / 180) * (2 * MeanAnomaly)) + 
                       OrbitDictFunc(PlanetC)[2] * sin((Pi / 180) * (3 * MeanAnomaly)) + OrbitDictFunc(PlanetC)[3] * sin((Pi / 180) * (4 * MeanAnomaly)) + 
                       OrbitDictFunc(PlanetC)[4] * sin((Pi / 180) * (5 * MeanAnomaly)) + OrbitDictFunc(PlanetC)[5] * sin((Pi / 180) * (6 * MeanAnomaly)));

    // 4. Ecliptic Longitude
    // MeanEclLongitudeSun (L_sun) in the Mean Ecliptic Longitude
    // EclLongitudeSun (λ) is the Ecliptic Longitude
    // OrbitDictFunc(PlanetOrbit)[0] is a value for the argument of perihelion
    std::string PlanetOrbit = Planet.append("Orbit");
    double MeanEclLongitudeSun = MeanAnomaly + OrbitDictFunc(PlanetOrbit)[0] + 180;
    double EclLongitudeSun = EquationOfCenter + MeanEclLongitudeSun;
    // Normalize Results
    MeanEclLongitudeSun = NormalizeZeroBounded(MeanEclLongitudeSun, 360);
    EclLongitudeSun = NormalizeZeroBounded(EclLongitudeSun, 360);

    // 5. Right Ascension of Sun (α)
    // PlanetA_2, PlanetA_4 and PlanetA_6 (measured in degrees) are coefficients in the series expansion of the Sun's Right Ascension
    // They varie for different planets in the Solar System
    // RightAscensionSun = EclLongitudeSun + S ≈ EclLongitudeSun + PlanetA_2 * sin(2 * EclLongitudeSun) + PlanetA_4 * sin(4 * EclLongitudeSun) + PlanetA_6 * sin(6 * EclLongitudeSun)
    std::string PlanetA = Planet.append("A");
    double RightAscensionSun = (EclLongitudeSun + OrbitDictFunc(PlanetA)[0] * sin((Pi / 180) * (2 * EclLongitudeSun)) + OrbitDictFunc(PlanetA)[1] * 
                        sin((Pi / 180) * (4 * EclLongitudeSun)) + OrbitDictFunc(PlanetA)[2] * sin((Pi / 180) * (6 * EclLongitudeSun)));

    RightAscensionSun /= 15;

    // 6./a Declination of the Sun (δ) (Wikipedia)
    // DeclinationSun (δSun) is the Declination of the Sun
    // 23.44° is Earth's maximum Axial Tilt toward's the Sun
    //DeclinationSun = (180 / Pi) * (asin(
    //       sin((Pi / 180) * (EclLongitudeSun)) * sin((Pi / 180) * (23.44)) ))
    // Normalize Declination
    //DeclinationSun = NormalizeSymmetricallyBoundedPI_2(DeclinationSun)

    // 6./b Declination of the Sun (δ) (Astronomy Answers)
    // PlanetD_1, PlanetD_3 and PlanetD_5 (measured in degrees) are coefficients in the series expansion of the Sun's Declination.
    // They varie for different planets in the Solar System.
    // DeclinationSun = PlanetD_1 * sin(EclLongitudeSun) + PlanetD_3 * (sin(EclLongitudeSun))^3 + PlanetD_5 * (sin(EclLongitudeSun))^5
    std::string PlanetD = Planet.append("D");
    double DeclinationSun = (OrbitDictFunc(PlanetD)[0] * sin((Pi / 180) * (EclLongitudeSun)) + OrbitDictFunc(PlanetD)[1] * 
                     pow((sin((Pi / 180) * (EclLongitudeSun))), 3) + OrbitDictFunc(PlanetD)[2] * pow((sin((Pi / 180) * (EclLongitudeSun))), 5));


    // 7. Solar Transit
    // Jtransit is the Julian date for the Local True Solar Transit (or Solar Noon)
    // JulianDate = JulianDays + 2451545
    // 2451545.5 is midnight or the beginning of the equivalent Julian year reference
    // Jtransit = J_x + 0.0053 * sin(MeanANomaly) - 0.0068 * sin(2 * L_sun)
    // "0.0053 * sin(MeanAnomaly) - 0.0069 * sin(2 * EclLongitudeSun)"  is a simplified version of the equation of time
    std::string PlanetJ = Planet.append("J");
    double J_x = (JulianDays + 2451545) + OrbitDictFunc(PlanetJ)[3] * (JulianDays - JAnomaly);
    double Jtransit = J_x + OrbitDictFunc(PlanetJ)[1] * sin((Pi / 180) * (MeanAnomaly)) + OrbitDictFunc(PlanetJ)[2] * sin((Pi / 180) * (2 * MeanEclLongitudeSun));

    std::vector<double> SunsCoordinatesCalc = {RightAscensionSun, DeclinationSun, EclLongitudeSun, Jtransit};
    return(SunsCoordinatesCalc);
}


std::vector<double> SunsLocalHourAngle(std::string Planet, double Latitude, double Longitude, double DeclinationSun, double EclLongitudeSun, double AltitudeOfSun)
{
    // Declare variables
    double LocalHourAngleSun_Orig;

    // 8./a Local Hour Angle of Sun (H)
    // H+ ≈ 90° + H_1 * sin(EclLongitudeSun) * tan(φ) + H_3 * sin(EclLongitudeSun)^3 * tan(φ) * (3 + tan(φ)^2) + H_5 * sin(EclLongitudeSun)^5 * tan(φ) * (15 + 10*tan(φ)^2 + 3 * tan(φ)^4))
    std::string PlanetH = Planet.append("H");
    double LocalHourAngleSun_Pos = (90 + OrbitDictFunc(PlanetH)[0] * sin((Pi / 180) * (EclLongitudeSun)) * tan((Pi / 180) * (Latitude)) + OrbitDictFunc(PlanetH)[1] * 
                            sin((Pi / 180) * pow(((EclLongitudeSun)), 3) * tan((Pi / 180) * (Latitude)) * (3 + pow(tan((Pi / 180) * (Latitude)), 2)) + OrbitDictFunc(PlanetH)[2] * 
                            pow(sin((Pi / 180) * (EclLongitudeSun)), 5) * tan((Pi / 180) * (Latitude)) * (15 + 10 * pow(tan((Pi / 180) * (Latitude)), 2) + 3 * pow(tan((Pi / 180) * (Latitude)), 4))));

    // 8./b1 Local Hour Angle of Sun (H)
    // cos(H) = (sin(m_0) - sin(φ) * sin(δ)) / (cos(φ) * cos(δ))
    // LocalHourAngleSun (t_0) is the Local Hour Angle from the Observer's Zenith
    // Latitude (φ) is the North Latitude of the Observer (north is positive, south is negative)
    // m_0 = Planet_RefCorr is a compensation of Altitude (m) in degrees, for the Sun's distorted shape, and the atmospherical refraction
    // The equation return two value, LHA1 and LHA2. We need that one, which is approximately equals to LHA_Pos
    std::string PlanetOrbit = Planet.append("Orbit");
    double LHAcos = ((sin((Pi / 180) * (AltitudeOfSun + OrbitDictFunc(PlanetOrbit)[2])) - sin((Pi / 180) * (Latitude)) * sin((Pi / 180) * (DeclinationSun))) /
            (cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (DeclinationSun))));
    if(LHAcos <= 1 and LHAcos >= -1)
    {
        LocalHourAngleSun_Orig = (180 / Pi) * (acos(LHAcos));
    }

    else if(LHAcos > 1)
    {
        LocalHourAngleSun_Orig = (180 / Pi) * (acos(1));
    }

    else if(LHAcos < -1)
    {
        LocalHourAngleSun_Orig = (180 / Pi) * (acos(-1));
    }

    //LocalHourAngleSun_Orig2 = - LocalHourAngleSun_Orig1
    
    // Normalize result for Hour Angles
    LocalHourAngleSun_Pos = NormalizeZeroBounded(LocalHourAngleSun_Pos, 360);
    LocalHourAngleSun_Orig = NormalizeZeroBounded(LocalHourAngleSun_Orig, 360);

    std::vector<double> SunsLocalHourAnglevec = {LocalHourAngleSun_Pos, LocalHourAngleSun_Orig};
    return(SunsLocalHourAnglevec);
}


std::vector<double> CalculateCorrectionsForJ(std::string Planet, double Latitude, double Longitude, double AltitudeOfSun, double JAlt_0)
{
    // Calculate Corrections for LHA of Sun
    RightAscensionSunCorr, DeclinationSunCorr, EclLongitudeSun, JtransitCorr = SunsCoordinatesCalc(Planet, Longitude, JAlt_0)
    LocalHourAngleSun_PosCorr, LocalHourAngleSun_OrigCorr = SunsLocalHourAngle(Planet, Latitude, Longitude, DeclinationSunCorr, EclLongitudeSun, AltitudeOfSun)


    return(LocalHourAngleSun_PosCorr, LocalHourAngleSun_OrigCorr, RightAscensionSunCorr, DeclinationSunCorr, JtransitCorr)
}

def CalculateRiseAndSetTime(Planet, Latitude, Longitude, AltitudeOfSun, LocalDateYear, LocalDateMonth, LocalDateDay):

    // Calculate Actual Julian Date
    // Now UT = 0
    UnitedHours = 0
    UnitedMinutes = 0
    UnitedSeconds = 0
    JulianDays = CalculateJulianDate(LocalDateYear, LocalDateMonth, LocalDateDay, UnitedHours, UnitedMinutes, UnitedSeconds)

    // Calulate Sun's coordinates on sky
    RightAscensionSun, DeclinationSun, EclLongitudeSun, Jtransit = SunsCoordinatesCalc(Planet, Longitude, JulianDays)
    LocalHourAngleSun_Pos, LocalHourAngleSun_Orig = SunsLocalHourAngle(Planet, Latitude, Longitude, DeclinationSun, EclLongitudeSun, AltitudeOfSun)


    '''std::cout << "LocalHourAngleSun_Pos: ", LocalHourAngleSun_Pos)
    std::cout << "LocalHourAngleSun_Orig: ", LocalHourAngleSun_Orig)'''

    // Calulate Rising and Setting Datetimes of the Sun
    // JRise is the actual Julian date of sunrise
    // JSet is the actual Julian date of sunset
    JRise = Jtransit - LocalHourAngleSun_Orig / 360
    JSet = Jtransit + LocalHourAngleSun_Orig / 360

    '''LocalHourAngleSun_PosCorrRise, LocalHourAngleSun_OrigCorrRise, RightAscensionSunCorrRise, DeclinationSunCorrRise, JtransitCorrRise =  CalculateCorrectionsForJ(Planet, Latitude, Longitude, AltitudeOfSun, JRise)
    LocalHourAngleSun_PosCorrSet, LocalHourAngleSun_OrigCorrSet, RightAscensionSunCorrSet, DeclinationSunCorrSet, JtransitCorrSet = CalculateCorrectionsForJ(Planet, Latitude, Longitude, AltitudeOfSun, JSet)
        
    std::cout << "LocalHourAngleSun_PosCorrRise: ", LocalHourAngleSun_PosCorrRise)
    std::cout << "LocalHourAngleSun_OrigCorrRise: ", LocalHourAngleSun_OrigCorrRise)
    std::cout << "LocalHourAngleSun_PosCorrSet: ", LocalHourAngleSun_PosCorrSet)
    std::cout << "LocalHourAngleSun_OrigCorrSet: ", LocalHourAngleSun_OrigCorrSet)'''
    
    // Apply Corrections
    //JRise -= (LocalHourAngleSun_Orig + LocalHourAngleSun_OrigCorrRise) / 360
    //JSet -= (LocalHourAngleSun_Orig - LocalHourAngleSun_OrigCorrSet) / 360

    return(JRise, JSet)


// Calculate Sunrise and Sunset's Datetime
def SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeOfSun, LocalDateYear, LocalDateMonth, LocalDateDay):

    JRise, JSet = CalculateRiseAndSetTime(Planet, Latitude, Longitude, AltitudeOfSun, LocalDateYear, LocalDateMonth, LocalDateDay)

    // SUNRISE
    double UTFracDayRise = JRise - int(JRise)

    UTFracDayRise *= 24

    SunRiseUT, SunRiseUTHours, SunRiseUTMinutes, SunRiseUTSeconds, SunRiseUTDateYear, SunRiseUTDateMonth, SunRiseUTDateDay = NormalizeTimeParameters(UTFracDayRise, LocalDateYear, LocalDateMonth, LocalDateDay)


    // SUNSET
    double UTFracDaySet = JSet - int(JSet)

    UTFracDaySet *= 24

    SunSetUT, SunSetUTHours, SunSetUTMinutes, SunSetUTSeconds, SunSetUTDateYear, SunSetUTDateMonth, SunSetUTDateDay = NormalizeTimeParameters(UTFracDaySet, LocalDateYear, LocalDateMonth, LocalDateDay)

    // Convert results to Local Time
    LocalTimeRise, LocalHoursRise, LocalMinutesRise, LocalSecondsRise, LocalDateYearRise, LocalDateMonthRise, LocalDateDayRise = UTtoLT(Latitude, SunRiseUTHours, SunRiseUTMinutes, SunRiseUTSeconds, SunRiseUTDateYear, SunRiseUTDateMonth, SunRiseUTDateDay)
    LocalTimeSet, LocalHoursSet, LocalMinutesSet, LocalSecondsSet, LocalDateYearSet, LocalDateMonthSet, LocalDateDaySet = UTtoLT(Latitude, SunSetUTHours, SunSetUTMinutes, SunSetUTSeconds, SunSetUTDateYear, SunSetUTDateMonth, SunSetUTDateDay)

    return(LocalTimeSet, LocalHoursSet, LocalMinutesSet, LocalSecondsSet, LocalDateYearSet, LocalDateMonthSet, LocalDateDaySet, LocalTimeRise, LocalHoursRise, LocalMinutesRise, LocalSecondsRise, LocalDateYearRise, LocalDateMonthRise, LocalDateDayRise)


def TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay):

    // Definition of differenc Twilights
    // Begin/End of Civil Twilight:          m = -6°
    // Begin/End of Nautical Twilight:       m = -12°
    // Begin/End of Astronomical Twilight:   m = -18°
    int AltitudeDaylight = 0
    int AltitudeCivil = -6
    int AltitudeNaval = -12
    int AltitudeAstro = -18

    //Daylight
    (LocalTimeSetDaylight, LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight, 
    LocalTimeRiseDaylight, LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight) = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeDaylight, LocalDateYear, LocalDateMonth, LocalDateDay)

    // Civil Twilight
    (LocalTimeSetCivil, LocalHoursSetCivil, LocalMinutesSetCivil, LocalSecondsSetCivil, LocalDateYearSetCivil, LocalDateMonthSetCivil, LocalDateDaySetCivil, 
    LocalTimeRiseCivil, LocalHoursRiseCivil, LocalMinutesRiseCivil, LocalSecondsRiseCivil, LocalDateYearRiseCivil, LocalDateMonthRiseCivil, LocalDateDayRiseCivil) = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeCivil, LocalDateYear, LocalDateMonth, LocalDateDay)

    // Nautical Twilight
    (LocalTimeSetNaval, LocalHoursSetNaval, LocalMinutesSetNaval, LocalSecondsSetNaval, LocalDateYearSetNaval, LocalDateMonthSetNaval, LocalDateDaySetNaval, 
    LocalTimeRiseNaval, LocalHoursRiseNaval, LocalMinutesRiseNaval, LocalSecondsRiseNaval, LocalDateYearRiseNaval, LocalDateMonthRiseNaval, LocalDateDayRiseNaval) = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeNaval, LocalDateYear, LocalDateMonth, LocalDateDay)

    // Astronomical Twilight
    (LocalTimeSetAstro, LocalHoursSetAstro, LocalMinutesSetAstro, LocalSecondsSetAstro, LocalDateYearSetAstro, LocalDateMonthSetAstro, LocalDateDaySetAstro, 
    LocalTimeRiseAstro, LocalHoursRiseAstro, LocalMinutesRiseAstro, LocalSecondsRiseAstro, LocalDateYearRiseAstro, LocalDateMonthRiseAstro, LocalDateDayRiseAstro) = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeAstro, LocalDateYear, LocalDateMonth, LocalDateDay)

    // Step +1 day
    LocalDateNextDay = LocalDateDay + 1

    if(LocalDateYear%4 == 0 and (LocalDateYear%100 != 0 or LocalDateYear%400 == 0)):
        if(LocalDateNextDay > MonthLengthListLeapYear[LocalDateMonth - 1]):
            LocalDateNextDay = 1
            LocalDateNextMonth = LocalDateMonth + 1
        else:
            LocalDateNextDay = LocalDateDay + 1
            LocalDateNextMonth = LocalDateMonth
    
    else:
        if(LocalDateNextDay > MonthLengthList[LocalDateMonth - 1]):
            LocalDateNextDay = 1
            LocalDateNextMonth = LocalDateMonth + 1
        else:
            LocalDateNextDay = LocalDateDay + 1
            LocalDateNextMonth = LocalDateMonth

    if(LocalDateNextMonth > 12):
        LocalDateNextMonth = 1
        LocalDateNextYear = LocalDateYear + 1

    else:
        LocalDateNextYear = LocalDateYear

    // Astronomical Twilight Next Day
    (LocalTimeSetAstro2, LocalHoursSetAstro2, LocalMinutesSetAstro2, LocalSecondsSetAstro2, LocalDateYearSetAstro2, LocalDateMonthSetAstro2, LocalDateDaySetAstro2, 
    LocalTimeRiseAstro2, LocalHoursRiseAstro2, LocalMinutesRiseAstro2, LocalSecondsRiseAstro2, LocalDateYearRiseAstro2, LocalDateMonthRiseAstro2, LocalDateDayRiseAstro2) = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeAstro, LocalDateNextYear, LocalDateNextMonth, LocalDateNextDay)

    //std::cout << LocalTimeRiseAstro, LocalTimeSetAstro)
    //std::cout << LocalTimeRiseAstro2, LocalTimeSetAstro2)

    // Noon and Midnight
    LocalTimeNoon = LocalTimeRiseDaylight + (LocalTimeSetDaylight - LocalTimeRiseDaylight) / 2
    LocalTimeMidnight = LocalTimeSetAstro + (((24 - LocalTimeSetAstro) + LocalTimeRiseAstro2) / 2)

    //std::cout << LocalTimeMidnight)
    //LocalTimeMidnight = LocalTimeNoon + 12

    // Calc Noon Date
    LocalDateDayNoon = LocalDateDayRiseAstro
    LocalDateMonthNoon = LocalDateMonthRiseAstro
    LocalDateYearNoon = LocalDateYearRiseAstro

    // Calc initial Midnight Date
    LocalDateDayMidnight = LocalDateDayRiseAstro
    LocalDateMonthMidnight = LocalDateMonthRiseAstro
    LocalDateYearMidnight = LocalDateYearRiseAstro

    //std::cout << LocalDateDayMidnight)

    // LT of Noon and Midnight
    LocalTimeNoon, LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon = NormalizeTimeParameters(LocalTimeNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon)
    LocalTimeMidnight, LocalHoursMidnight, LocalMinutesMidnight, LocalSecondsMidnight, LocalDateYearMidnight, LocalDateMonthMidnight, LocalDateDayMidnight = NormalizeTimeParameters(LocalTimeMidnight, LocalDateYearMidnight, LocalDateMonthMidnight, LocalDateDayMidnight)

    return(LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon,
            LocalHoursMidnight, LocalMinutesMidnight, LocalSecondsMidnight, LocalDateYearMidnight, LocalDateMonthMidnight, LocalDateDayMidnight,
            LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight,
            LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight,
            LocalHoursRiseCivil, LocalMinutesRiseCivil, LocalSecondsRiseCivil, LocalDateYearRiseCivil, LocalDateMonthRiseCivil, LocalDateDayRiseCivil,
            LocalHoursSetCivil, LocalMinutesSetCivil, LocalSecondsSetCivil, LocalDateYearSetCivil, LocalDateMonthSetCivil, LocalDateDaySetCivil,
            LocalHoursRiseNaval, LocalMinutesRiseNaval, LocalSecondsRiseNaval, LocalDateYearRiseNaval, LocalDateMonthRiseNaval, LocalDateDayRiseNaval,
            LocalHoursSetNaval, LocalMinutesSetNaval, LocalSecondsSetNaval, LocalDateYearSetNaval, LocalDateMonthSetNaval, LocalDateDaySetNaval,
            LocalHoursRiseAstro, LocalMinutesRiseAstro, LocalSecondsRiseAstro, LocalDateYearSetAstro, LocalDateMonthSetAstro, LocalDateDaySetAstro,
            LocalHoursSetAstro, LocalMinutesSetAstro, LocalSecondsSetAstro, LocalDateYearRiseAstro, LocalDateMonthRiseAstro, LocalDateDayRiseAstro)



////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////        5. SOLVE ASTRONOMICAL TRIANGLES         ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////

def AstroTriangles(aValue, bValue, cValue, alphaValue, betaValue, gammaValue):

    if(aValue != 0 and bValue != 0 and cValue != 0):
        
        if(((aValue + bValue) > cValue) and ((aValue + cValue) > bValue) and ((bValue + cValue) > aValue) and 
            (abs(aValue - bValue) < cValue) and (abs(aValue - cValue) < bValue) and (abs(bValue - cValue) < aValue) and
            ((aValue + bValue + cValue) < 360)):
            
            // Calculate angle Alpha
            alphaValue = (180 / Pi) * (acos(
                (cos((Pi / 180) * (aValue)) - cos((Pi / 180) * (bValue)) * cos((Pi / 180) * (cValue))) /
                (sin((Pi / 180) * (bValue)) * sin((Pi / 180) * (cValue)))
            ))

            // Calculate angle Beta
            betaValue = (180 / Pi) * (acos(
                (cos((Pi / 180) * (bValue)) - cos((Pi / 180) * (cValue)) * cos((Pi / 180) * (aValue))) /
                (sin((Pi / 180) * (cValue)) * sin((Pi / 180) * (aValue)))
            ))

            // Calculate angle Gamma
            gammaValue = (180 / Pi) * (acos(
                (cos((Pi / 180) * (cValue)) - cos((Pi / 180) * (aValue)) * cos((Pi / 180) * (bValue))) /
                (sin((Pi / 180) * (aValue)) * sin((Pi / 180) * (bValue)))
            ))

        else:
            std::cout << ">> Length of the sides are invalid!\n>> They violate the triangle inequality!")


    else if(aValue != 0 and bValue != 0 and gammaValue != 0):

        // Calculate side C 
        cValue = (180 / Pi) * (math.atan(
            sqrt((sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (bValue)) -
            cos((Pi / 180) * (aValue)) * sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (gammaValue)))**2 + 
            (sin((Pi / 180) * (bValue)) * sin((Pi / 180) * (gammaValue)))**2) /
            (cos((Pi / 180) * (aValue)) * cos((Pi / 180) * (bValue)) + 
            sin((Pi / 180) * (aValue)) * sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (gammaValue)))
        ))

        // calculate angle Alpha
        alphaValue = (180 / Pi) * (math.atan(
            (sin((Pi / 180) * (aValue) * sin((Pi / 180) * (gammaValue)))) /
            (sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (aValue)) - 
            cos((Pi / 180) * (bValue)) * sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (gammaValue)))
        ))

        // Calculate angle Beta
        betaValue = (180 / Pi) * (math.atan(
            (sin((Pi / 180) * (bValue) * sin((Pi / 180) * (gammaValue)))) /
            (sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (bValue)) - 
            cos((Pi / 180) * (aValue)) * sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (gammaValue)))
        ))

    else if(bValue != 0 and cValue != 0 and alphaValue != 0): 

        // Calculate side A 
        aValue = (180 / Pi) * (math.atan(
            sqrt((sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (cValue)) -
            cos((Pi / 180) * (bValue)) * sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (alphaValue)))**2 + 
            (sin((Pi / 180) * (cValue)) * sin((Pi / 180) * (alphaValue)))**2) /
            (cos((Pi / 180) * (bValue)) * cos((Pi / 180) * (cValue)) + 
            sin((Pi / 180) * (bValue)) * sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (alphaValue)))
        ))

        // calculate angle Gamma
        betaValue = (180 / Pi) * (math.atan(
            (sin((Pi / 180) * (bValue) * sin((Pi / 180) * (alphaValue)))) /
            (sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (bValue)) - 
            cos((Pi / 180) * (cValue)) * sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (alphaValue)))
        ))

        // Calculate angle Alpha
        gammaValue = (180 / Pi) * (math.atan(
            (sin((Pi / 180) * (cValue) * sin((Pi / 180) * (alphaValue)))) /
            (sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (cValue)) - 
            cos((Pi / 180) * (bValue)) * sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (alphaValue)))
        ))
    
    else if(aValue != 0 and cValue != 0 and betaValue != 0):

        // Calculate side C 
        bValue = (180 / Pi) * (math.atan(
            sqrt((sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (aValue)) -
            cos((Pi / 180) * (cValue)) * sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (betaValue)))**2 + 
            (sin((Pi / 180) * (aValue)) * sin((Pi / 180) * (betaValue)))**2) /
            (cos((Pi / 180) * (cValue)) * cos((Pi / 180) * (aValue)) + 
            sin((Pi / 180) * (cValue)) * sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (betaValue)))
        ))

        // calculate angle Alpha
        gammaValue = (180 / Pi) * (math.atan(
            (sin((Pi / 180) * (cValue) * sin((Pi / 180) * (betaValue)))) /
            (sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (cValue)) - 
            cos((Pi / 180) * (aValue)) * sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (betaValue)))
        ))

        // Calculate angle Beta
        alphaValue = (180 / Pi) * (math.atan(
            (sin((Pi / 180) * (aValue) * sin((Pi / 180) * (betaValue)))) /
            (sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (aValue)) - 
            cos((Pi / 180) * (cValue)) * sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (betaValue)))
        ))


    else if((aValue != 0 and bValue != 0 and alphaValue != 0) or (aValue != 0 and bValue != 0 and betaValue != 0) or 
        (bValue != 0 and cValue != 0 and betaValue != 0) or (bValue != 0 and cValue != 0 and gammaValue != 0) or
        (aValue != 0 and cValue != 0 and betaValue != 0) or (aValue != 0 and cValue != 0 and gammaValue != 0)):
        pass


    else if((aValue != 0 and betaValue != 0 and gammaValue != 0) or 
        (bValue != 0 and alphaValue != 0 and gammaValue != 0) or
        (cValue != 0 and alphaValue != 0 and betaValue != 0)):
        pass

    
    else if((aValue != 0 and alphaValue != 0 and betaValue != 0) or (aValue != 0 and alphaValue != 0 and gammaValue != 0) or
        (bValue != 0 and betaValue != 0 and alphaValue != 0) or (bValue != 0 and betaValue != 0 and gammaValue != 0) or
        (cValue != 0 and gammaValue != 0 and alphaValue != 0) or (aValue != 0 and gammaValue != 0 and betaValue != 0)):
        pass


    else if(alphaValue != 0 and betaValue != 0 and gammaValue != 0):
        pass


    else:
        aValue = NULL
        bValue = NULL
        cValue = NULL
        alphaValue = NULL
        betaValue = NULL
        gammaValue = NULL


    return(aValue, bValue, cValue, alphaValue, betaValue, gammaValue)



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////   6. DRAW THE SUN'S ANNUAL PATH ON A SUNDIAL   ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def SundialPrecalculations(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay):

    // We would like to calculate rising and setting time
    AltitudeOfSun = 0

    // Daylight start and end LT
    (LocalTimeSetDaylight, LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight, 
    LocalTimeRiseDaylight, LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight) = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeOfSun, LocalDateYear, LocalDateMonth, LocalDateDay)

    // Calculate the Coordinates of the Sun's Apparent Position
    // Now UT = 0
    UnitedHours = 0
    UnitedMinutes = 0
    UnitedSeconds = 0
    JulianDays = CalculateJulianDate(LocalDateYear, LocalDateMonth, LocalDateDay, UnitedHours, UnitedMinutes, UnitedSeconds)
    RightAscensionSun, DeclinationSun, EclLongitudeSun, Jtransit = SunsCoordinatesCalc(Planet, Longitude, JulianDays)
    LocalHourAngleSun_Pos, LocalHourAngleSun_Orig = SunsLocalHourAngle(Planet, Latitude, Longitude, DeclinationSun, EclLongitudeSun, AltitudeOfSun)

    std::cout << "RA, Dec: ", RightAscensionSun, DeclinationSun)

    // Calculate Local Mean Sidereal Time for both Rising and Setting time
    LocalSiderealHoursRise, LocalSiderealMinutesRise, LocalSiderealSecondsRise, UnitedHoursRise, UnitedMinutesRise, UnitedSecondsRise, GreenwichSiderealHoursRise, GreenwichSiderealMinutesRise, GreenwichSiderealSecondsRise = LocalSiderealTimeCalc(Longitude, LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight)
    LocalSiderealHoursSet, LocalSiderealMinutesSet, LocalSiderealSecondsSet, UnitedHoursSet, UnitedMinutesSet, UnitedSecondsSet, GreenwichSiderealHoursSet, GreenwichSiderealMinutesSet, GreenwichSiderealSecondsSet = LocalSiderealTimeCalc(Longitude, LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight)

    // Convert them to Decimal
    LocalSiderealTimeRise = LocalSiderealHoursRise + LocalSiderealMinutesRise/60 + LocalSiderealSecondsRise/3600
    LocalSiderealTimeSet = LocalSiderealHoursSet + LocalSiderealMinutesSet/60 + LocalSiderealSecondsSet/3600

    // Calculate Hour Angle of Rising and Setting Sun
    LocalHourAngleRise = LocalSiderealTimeRise - RightAscensionSun
    LocalHourAngleSet = LocalSiderealTimeSet - RightAscensionSun

    std::cout << "Rise/Set LT: ", LocalTimeRiseDaylight, LocalTimeSetDaylight)
    std::cout << "Rise/Set ST: ", LocalSiderealTimeRise, LocalSiderealTimeSet)
    std::cout << "Rise/Set LHA: ", LocalHourAngleRise, LocalHourAngleSet)


    // Normalize Results
    LocalHourAngleRise = NormalizeZeroBounded(LocalHourAngleRise, 24)
    LocalHourAngleSet = NormalizeZeroBounded(LocalHourAngleSet, 24)

    std::cout << "Rise/Set LHA Nor: ", LocalHourAngleRise, LocalHourAngleSet)
    std::cout << "\n")    

    return(LocalHourAngleRise, LocalHourAngleSet, DeclinationSun)

def SundialParametersCalc(Latitude, LocalHourAngle, DeclinationSun):

    // Convert to angles from hours (t -> H)
    LocalHourAngleDegrees = LocalHourAngle * 15

    // Calculate Altitude (m)
    // sin(m) = sin(δ) * sin(φ) + cos(δ) * cos(φ) * cos(H)
    Altsin = sin((Pi / 180) * (DeclinationSun)) * sin((Pi / 180) * (Latitude)) + cos((Pi / 180) * (DeclinationSun)) * cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (LocalHourAngleDegrees))
    if(Altsin <= 1):
        Altitude = (180 / Pi) * (asin(Altsin))
        //std::cout << Altitude)
    else:
        Altitude = (180 / Pi) * (asin(2 - Altsin))
    // Normalize Altitude
    // Altitude: [-π/2,+π/2]
    Altitude = NormalizeSymmetricallyBoundedPI_2(Altitude)

    // We should draw 1/tan(m) of the function of (AzimuthMax - AzimuthMin)
    ShadowLength = 1/tan((Pi / 180) * (Altitude))

    '''// Calculate Azimuth (A)
    // sin(A) = - sin(H) * cos(δ) / cos(m)
    // Azimuth at given H Local Hour Angle
    Azsin = - sin((Pi / 180) * (LocalHourAngleDegrees)) * cos((Pi / 180) * (DeclinationSun)) / cos((Pi / 180) * (Altitude))
    if(Azsin <= 1 and Azsin >= -1):
        Azimuth1 = (180 / Pi) * (asin(Azsin))
    else if(Azsin > 1):
        std::cout << Azsin)
        Azimuth1 = 180 - (180 / Pi) * (asin(2 - Azsin))
    else:
        std::cout << Azsin)
        Azimuth1 = - 180 + (180 / Pi) * (asin(2 + Azsin))

    Azimuth1 = NormalizeZeroBounded(Azimuth1, 360)

    if(Azimuth1 <= 180):
        Azimuth2 = 180 - Azimuth1

    else if(Azimuth1 > 180):
        Azimuth2 = 540 - Azimuth1

    // Calculate Azimuth (A) with a second method, to determine which one is the correct (A_1 or A_2?)
    // cos(A) = (sin(δ) - sin(φ) * sin(m)) / (cos(φ) * cos(m))
    Azcos = (sin((Pi / 180) * (DeclinationSun)) - sin((Pi / 180) * (Latitude)) * sin((Pi / 180) * (Altitude))) / (cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (Altitude)))
    if(Azcos <= 1 and Azcos >= -1):
        Azimuth3 = (180 / Pi) * (acos(Azcos))

    else if(Azcos < -1):
        Azimuth3 = 180 + (180 / Pi) * (asin(2 + Azcos))

    else:
        Azimuth3 = (180 / Pi) * (asin(2 - Azcos))

    Azimuth3 = NormalizeZeroBounded(Azimuth3, 360)

    Azimuth4 = - Azimuth3

    // Normalize negative result
    // Azimuth: [0,+2π[
    Azimuth4 = NormalizeZeroBounded(Azimuth4, 360)

    // Compare Azimuth values
    if(Azimuth1 + 3 > Azimuth3 and Azimuth1 - 3 < Azimuth3):
        Azimuth = Azimuth1

    else if(Azimuth1 + 3 > Azimuth4 and Azimuth1 - 3 < Azimuth4):
        Azimuth = Azimuth1

    else if(Azimuth2 + 3 > Azimuth3 and Azimuth2 - 3 < Azimuth3):
        Azimuth = Azimuth2

    else if(Azimuth2 + 3 > Azimuth4 and Azimuth2 - 3 < Azimuth4):
        Azimuth = Azimuth2
    
    else:
        std::cout << Azimuth1, Azimuth2, Azimuth3, Azimuth4)

    // Normalize Azimuth
    // Azimuth: [0,+2π[
    Azimuth = NormalizeZeroBounded(Azimuth, 360)'''

    Azimuth = 0

    return(Altitude, Azimuth, ShadowLength)



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////             7. DRAW SUN ANALEMMA               ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def SunAnalemma(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay):

    (LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon,
    LocalHoursMidnight, LocalMinutesMidnight, LocalSecondsMidnight, LocalDateYearMidnight, LocalDateMonthMidnight, LocalDateDayMidnight,
    LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight,
    LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight,
    LocalHoursRiseCivil, LocalMinutesRiseCivil, LocalSecondsRiseCivil, LocalDateYearRiseCivil, LocalDateMonthRiseCivil, LocalDateDayRiseCivil,
    LocalHoursSetCivil, LocalMinutesSetCivil, LocalSecondsSetCivil, LocalDateYearSetCivil, LocalDateMonthSetCivil, LocalDateDaySetCivil,
    LocalHoursRiseNaval, LocalMinutesRiseNaval, LocalSecondsRiseNaval, LocalDateYearRiseNaval, LocalDateMonthRiseNaval, LocalDateDayRiseNaval,
    LocalHoursSetNaval, LocalMinutesSetNaval, LocalSecondsSetNaval, LocalDateYearSetNaval, LocalDateMonthSetNaval, LocalDateDaySetNaval,
    LocalHoursRiseAstro, LocalMinutesRiseAstro, LocalSecondsRiseAstro, LocalDateYearSetAstro, LocalDateMonthSetAstro, LocalDateDaySetAstro,
    LocalHoursSetAstro, LocalMinutesSetAstro, LocalSecondsSetAstro, LocalDateYearRiseAstro, LocalDateMonthRiseAstro, LocalDateDayRiseAstro) = TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay)

    // Calculate Local Mean Sidereal Time
    (LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds,
    UnitedHours, UnitedMinutes, UnitedSeconds, 
    GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds) = LocalSiderealTimeCalc(Longitude, LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon)

    // Convert LT noon to UT noon time
    UnitedTime, UnitedHours, UnitedMinutes, UnitedSeconds, UnitedDateYear, UnitedDateMonth, UnitedDateDay = LTtoUT(Longitude, LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon)

    // Calculate corresponding Julian Date
    JulianDays = CalculateJulianDate(UnitedDateYear, UnitedDateMonth, UnitedDateDay, UnitedHours, UnitedMinutes, UnitedSeconds)

    // Calculate Sun's position at this time
    RightAscensionSun, DeclinationSun, EclLongitudeSun, Jtransit = SunsCoordinatesCalc(Planet, Longitude, JulianDays)

    // Convert to horizontal
    LocalSiderealTime = LocalSiderealHours + LocalSiderealMinutes/60 + LocalSiderealSeconds/3600
    LocalHourAngle = LocalSiderealTime - RightAscensionSun
    // Normalize output
    LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24)
    Altitude = NULL
    Altitude, Azimuth = EquIToHor(Latitude, RightAscensionSun, DeclinationSun, Altitude, LocalSiderealTime, LocalHourAngle)

    return(LocalHourAngle, Altitude)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////                ...     ..      ..                                                     ////////
////                x*8888x.:*8888: -"888:                 @88>                                ////
////               X   48888X `8888H  8888                 %8P                                 ////
////              X8x.  8888X  8888X  !888>                       x@88k u@88c.                 ////
////              X8888 X8888  88888   "*8%-    us888u.   .@88u  ^"8888""8888"                 ////
////              '*888!X8888> X8888  xH8>   .@88 "8888" ''888E`   8888  888R                  ////
////                `?8 `8888  X888X X888>   9888  9888    888E    8888  888R                  ////
////                -^  '888"  X888  8888>   9888  9888    888E    8888  888R                  ////
////                 dx '88~x. !88~  8888>   9888  9888    888E    8888  888R                  ////
////               .8888Xf.888x:!    X888X.: 9888  9888    888&   "*88*" 8888"                 ////
////              :""888":~"888"     `888*"  "888*""888"   R888"    ""   'Y"                   ////
////                  "~'    "~        ""                   ""                                 ////
////////                                                                                       ////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////  ////////                                                                             ////////  //////
  ////////  //////                                                                         //////  ////////
        ////                                                                           ////
  //   //////                                                                             //////   //
   ////////                                                                                 ////////
int main()
{
    // Print version info
    STARTMSG = "\n//////// Csillész II Problem Solver Program {0} ////////\n////////         Developed by Balázs Pál.         ////////\n\n"
    std::cout << STARTMSG.format(ActualVersion))

    while(1):

        std::cout << ">> MAIN MENU <<")
        std::cout << "(1) Coordinate System Conversion")
        std::cout << "(2) Geographical Distances")
        std::cout << "(3) Local Mean Sidereal Time")
        std::cout << "(4) Datetimes of Twilights")
        std::cout << "(5) Solve Astronomical Triangles")
        std::cout << "(6) Plot Sun's Path on Sundial")
        std::cout << "(7) Plot Sun's Analemma")
        std::cout << "(H) Solve End-Semester Homework")
        std::cout << "(Q) Quit Program\n")

        // Choose mode by user input
        mode = input("> Choose a mode and press enter...: ")
        std::cout << '\n\n')

        //    _____                    _    _____              _____                 
        //   / ____|                  | |  / ____|            / ____|                
        //  | |     ___   ___  _ __ __| | | (___  _   _ ___  | |     ___  _ ____   __
        //  | |    / _ \ / _ \| '__/ _` |  \___ \| | | / __| | |    / _ \| '_ \ \ / /
        //  | |___| (_) | (_) | | | (_| |  ____) | |_| \__ \ | |___| (_) | | | \ V / 
        //   \_____\___/ \___/|_|  \__,_| |_____/ \__, |___/  \_____\___/|_| |_|\_/  
        //                                         __/ |                             
        //                                        |___/                              
        // COORDINATE SYSTEM CONVERSION
        if(mode == '1'):
            while(1):
                std::cout << ">> Coordinate System Conversion")
                std::cout << ">> Please choose which coordinate system conversion you'd like to make!")
                std::cout << "(1) Horizontal to Equatorial I")
                std::cout << "(2) Horizontal to Equatorial II")
                std::cout << "(3) Equatorial I to Horizontal")
                std::cout << "(4) Equatorial I to Equatorial II")
                std::cout << "(5) Equatorial II to Equatorial I")
                std::cout << "(6) Equatorial II to Horizontal")
                std::cout << "(Q) Quit to Main Menu\n")
                CoordMode = input("> Choose a number and press enter...:")

                std::cout << '\n')

                //  __  
                // /  | 
                // `| | 
                //  | | 
                // _| |__
                // \___(_)
                // 1. Horizontal to Equatorial I Coordinate System
                if(CoordMode == '1'):
                    std::cout << ">> Conversion from Horizontal to Equatorial I Coordinate System")
                    std::cout << ">> Give Parameters!")

                    std::cout << ">> Would you like to give Geographical Coordinates by yourself,\n>> or would like to choose a predefined Location's Coordinates?")
                    std::cout << ">> Write \'1\' for User defined Coordinates, and write \'2\' for Predefined Locations' Coordinates!")

                    HorToEquILocationChoose = input(">> (1) User Defined, (2) Predefined: ")

                    while(1):
                        if(HorToEquILocationChoose == '1'):
                            std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                            LatitudeHours = float(input("> Latitude (φ) Hours: ") or "0")
                            LatitudeMinutes = float(input("> Latitude (φ) Minutes: ") or "0")
                            LatitudeSeconds = float(input("> Latitude (φ) Seconds: ") or "0")
                            Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600
                            break
                        
                        else if(HorToEquILocationChoose == '2'):
                            while(1):
                                Location = input("> Location's name (type \'H\' for Help): ")

                                if(Location == "Help" or Location == "help" or Location == "H" or Location == "h"):
                                    std::cout << "\n>> Predefined Locations you can choose from:")
                                    for keys in LocationDict.items():
                                        std::cout << keys)
                                    std::cout << '\n')
                                
                                else:
                                    try:
                                        Latitude = LocationDictFunc(Location)[0]

                                    except KeyError:
                                        std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!")
                                        std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")
                                        
                                    else:
                                        break

                            break
                                
                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    Altitude = float(input("> Altitude (m): "))
                    Azimuth = float(input("> Azimuth (A): "))

                    std::cout << "Is Local Mean Sidereal Time given?")
                    while(1):
                        HorToEquIChoose = input("Write \'Y\' or \'N\' (Yes or No)")
                        if(HorToEquIChoose == 'Y' or HorToEquIChoose == 'y' or HorToEquIChoose == 'Yes' or HorToEquIChoose == 'yes' or HorToEquIChoose == 'YEs' or HorToEquIChoose == 'yEs' or HorToEquIChoose == 'yeS' or HorToEquIChoose == 'YeS' or HorToEquIChoose == 'yES'):
                            std::cout << ">> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                            LocalSiderealTimeHours = float(input("> Local Mean Sidereal Time (S) Hours: ") or "0")
                            LocalSiderealTimeMinutes = float(input("> Local Mean Sidereal Time (S) Minutes: ") or "0")
                            LocalSiderealTimeSeconds = float(input("> Local Mean Sidereal Time (S) Seconds: ") or "0")
                            LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600
                            break

                        else if(HorToEquIChoose == 'N' or HorToEquIChoose == 'n' or HorToEquIChoose == 'No' or HorToEquIChoose == 'no' or HorToEquIChoose == 'nO'):
                            LocalSiderealTime = NULL
                            break

                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    // Used Formulas:
                    // sin(δ) = sin(m) * sin(φ) + cos(m) * cos(φ) * cos(A)
                    // sin(H) = - sin(A) * cos(m) / cos(δ)
                    // α = S – t
                    Declination, LocalHourAngle, RightAscension = HorToEquI(Latitude, Altitude, Azimuth, LocalSiderealTime)

                    DeclinationHours = int(Declination)
                    DeclinationMinutes = int((Declination - DeclinationHours) * 60)
                    DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60)

                    LocalHourAngleHours = int(LocalHourAngle)
                    LocalHourAngleMinutes = int((LocalHourAngle - LocalHourAngleHours) * 60)
                    LocalHourAngleSeconds = int((((LocalHourAngle - LocalHourAngleHours) * 60) - LocalHourAngleMinutes) * 60)

                    // Print Results
                    std::cout << "\n> Calculated parameters in Equatorial I Coord. Sys.:")
                    
                    declinmsg = "- Declination (δ): {0}° {1}\' {2}\""
                    hourangmsg = "- Local Hour Angle (t): {0}h {1}m {2}s"
                    std::cout << declinmsg.format(DeclinationHours, DeclinationMinutes, DeclinationSeconds))
                    std::cout << hourangmsg.format(LocalHourAngleHours, LocalHourAngleMinutes, LocalHourAngleSeconds))
                    
                    if(LocalSiderealTime != NULL):
                        
                        RightAscensionHours = int(RightAscension)
                        RightAscensionMinutes = int((RightAscension - RightAscensionHours) * 60)
                        RightAscensionSeconds = int((((RightAscension - RightAscensionHours) * 60) - RightAscensionMinutes) * 60)

                        RAmsg = "- Right Ascension (α): {0}h {1}m {2}s"
                        std::cout << RAmsg.format(RightAscensionHours, RightAscensionMinutes, RightAscensionSeconds))

                    std::cout << '\n')

                //  _____   
                // / __  \  
                // `' / /'  
                //   / /    
                // ./ /____ 
                // \_____(_)
                // 2. Horizontal to Equatorial II Coordinate System
                else if(CoordMode == '2'):
                    std::cout << ">> Conversion from Horizontal to Equatorial II Coordinate System")
                    std::cout << ">> Give Parameters!")
                    
                    std::cout << ">> Would you like to give Geographical Coordinates by yourself,\n>> or would like to choose a predefined Location's Coordinates?")
                    std::cout << ">> Write \'1\' for User defined Coordinates, and write \'2\' for Predefined Locations' Coordinates!")

                    HorToEquIILocationChoose = input(">> (1) User Defined, (2) Predefined: ")
                    
                    while(1):
                        if(HorToEquIILocationChoose == '1'):
                            std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                            LatitudeHours = float(input("> Latitude (φ) Hours: ") or "0")
                            LatitudeMinutes = float(input("> Latitude (φ) Minutes: ") or "0")
                            LatitudeSeconds = float(input("> Latitude (φ) Seconds: ") or "0")
                            Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600
                            break
                        
                        else if(HorToEquIILocationChoose == '2'):
                            while(1):
                                Location = input("> Location's name (type \'H\' for Help): ")

                                if(Location == "Help" or Location == "help" or Location == "H" or Location == "h"):
                                    std::cout << "\n>> Predefined Locations you can choose from:")
                                    for keys in LocationDict.items():
                                        std::cout << keys)
                                    std::cout << '\n')
                                
                                else:
                                    try:
                                        Latitude = LocationDictFunc(Location)[0]

                                    except KeyError:
                                        std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!")
                                        std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")
                                        
                                    else:
                                        break

                            break
                                
                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    Altitude = float(input("> Altitude (m): "))
                    Azimuth = float(input("> Azimuth (A): "))
                    
                    std::cout << ">> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LocalSiderealTimeHours = float(input("> Local Mean Sidereal Time (S) Hours: ") or "0")
                    LocalSiderealTimeMinutes = float(input("> Local Mean Sidereal Time (S) Minutes: ") or "0")
                    LocalSiderealTimeSeconds = float(input("> Local Mean Sidereal Time (S) Seconds: ") or "0")
                    LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600

                    Declination, RightAscension, LocalSiderealTime = HorToEquII(Latitude, Altitude, Azimuth, LocalSiderealTime)

                    DeclinationHours = int(Declination)
                    DeclinationMinutes = int((Declination - DeclinationHours) * 60)
                    DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60)

                    RightAscensionHours = int(RightAscension)
                    RightAscensionMinutes = int((RightAscension - RightAscensionHours) * 60)
                    RightAscensionSeconds = int((((RightAscension - RightAscensionHours) * 60) - RightAscensionMinutes) * 60)

                    LocalSiderealTimeHours = int(LocalSiderealTime)
                    LocalSiderealTimeMinutes = int((LocalSiderealTime - LocalSiderealTimeHours) * 60)
                    LocalSiderealTimeSeconds = int((((LocalSiderealTime - LocalSiderealTimeHours) * 60) - LocalSiderealTimeMinutes) * 60)


                    // Print Results
                    std::cout << "\n> Calculated Parameters in Equatorial II Coord. Sys.:")

                    declinmsg = "- Declination (δ): {0}° {1}\' {2}\""
                    RAmsg = "- Right Ascension (α): {0}h {1}m {2}s"
                    sidermsg = "- Local Mean Sidereal Time (S): {0}:{1}:{2}\n"
                    std::cout << declinmsg.format(DeclinationHours, DeclinationMinutes, DeclinationSeconds))
                    std::cout << RAmsg.format(RightAscensionHours, RightAscensionMinutes, RightAscensionSeconds))
                    std::cout << sidermsg.format(LocalSiderealTimeHours, LocalSiderealTimeMinutes, LocalSiderealTimeSeconds))
                    std::cout << '\n')

                //  _____  
                // |____ | 
                //     / / 
                //     \ \ 
                // .___/ / 
                // \____(_)
                // 3. Equatorial I to Horizontal Coordinate System
                else if(CoordMode == '3'):
                    std::cout << ">> Conversion from Equatorial I to Horizontal Coordinate System")
                    std::cout << ">> Give Parameters!\n")
                    
                    while(1):
                        std::cout << ">>> LOCATION")
                        std::cout << ">> Would you like to give Geographical Coordinates by yourself,\n>> Or would like to choose a predefined Location's Coordinates?")
                        std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for Predefined Locations' Coordinates!")

                        EquIToHorLocationChoose = input(">> (1) User Defined, (2) Predefined: ")

                        if(EquIToHorLocationChoose == '1'):
                            std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                            LatitudeHours = float(input("> Latitude (φ) Hours: ") or "0")
                            LatitudeMinutes = float(input("> Latitude (φ) Minutes: ") or "0")
                            LatitudeSeconds = float(input("> Latitude (φ) Seconds: ") or "0")
                            Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600
                            break
                        
                        else if(EquIToHorLocationChoose == '2'):
                            while(1):
                                Location = input("> Location's name (type \'H\' for Help): ")

                                if(Location == "Help" or Location == "help" or Location == "H" or Location == "h"):
                                    std::cout << "\n>> Predefined Locations you can choose from:")
                                    for keys in LocationDict.items():
                                        std::cout << keys)
                                    std::cout << '\n')
                                
                                else:
                                    try:
                                        Latitude = LocationDictFunc(Location)[0]

                                    except KeyError:
                                        std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!")
                                        std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")
                                        
                                    else:
                                        break

                            break
                                
                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")
                    
                    while(1):
                        std::cout << "\n>>> STELLAR OBJECT")
                        std::cout << ">> Would you like to give the stellar object's Coordinates by yourself,\n>> Or would like to choose a Predefined Object's Coordinates?")
                        std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for a Predefined Stellar Object's Coordinates!")

                        EquIToHorStellarChoose = input(">> (1) User Defined, (2) Predefined: ")
                        
                        if(EquIToHorStellarChoose == '1'):
                            std::cout << "\n>> Which Parameter Is given?")
                            std::cout << ">> Declination is essential for calculation Horizontal Coordinates!\n>> Right Ascension only, isn't enough for calculating these parameters!")
                            RAorDecEquIToHorChoose = input(">> Only Declination (write \'D\'), Or both of\n>> Right Ascension and Declination (write \'B\')?: ")

                            if(RAorDecEquIToHorChoose == 'D' or RAorDecEquIToHorChoose == 'd'):
                                RightAscension = NULL

                                std::cout << "\n>> HINT: You can write RA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                                DeclinationHours = float(input("\n> Declination (δ) Hours: ") or "0")
                                DeclinationMinutes = float(input("> Declination (δ) Minutes: ") or "0")
                                DeclinationSeconds = float(input("> Declination (δ) Seconds: ") or "0")
                                Declination = DeclinationHours + DeclinationMinutes/60 + DeclinationSeconds/3600
                                break

                            else if(RAorDecEquIToHorChoose == 'B' or RAorDecEquIToHorChoose == 'b'):
                                std::cout << "\n>> HINT: You can write RA and Declination as a Decimal Fraction.\n>> For this you need to write Hours as a float-type value, then\n>> You can Press Enter for both Minutes and Seconds.")
                                RightAscensionHours = float(input("\n> Right Ascension (α) Hours: ") or "0")
                                RightAscensionMinutes = float(input("> Right Ascension (α) Minutes: ") or "0")
                                RightAscensionSeconds = float(input("> Right Ascension (α) Seconds: ") or "0")
                                RightAscension = RightAscensionHours + RightAscensionMinutes/60 + RightAscensionSeconds/3600

                                DeclinationHours = float(input("\n> Declination (δ) Hours: ") or "0")
                                DeclinationMinutes = float(input("> Declination (δ) Minutes: ") or "0")
                                DeclinationSeconds = float(input("> Declination (δ) Seconds: ") or "0")
                                Declination = DeclinationHours + DeclinationMinutes/60 + DeclinationSeconds/3600
                                break

                            else:
                                std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'D\' or \'B\'!")

                        else if(EquIToHorStellarChoose == '2'):
                            while(1):
                                StellarObject = input("> Stellar object's name (type \'H\' for Help): ")

                                if(StellarObject == "Help" or StellarObject == "help" or StellarObject == "H" or StellarObject == "h"):
                                    std::cout << "\n>> Predefined Objects you can choose from:")
                                    for keys in StellarDict.items():
                                        std::cout << keys)
                                    std::cout << '\n')
                                
                                else:
                                    try:
                                        TestVariable = StellarDict[StellarObject][0]
                                        del TestVariable

                                    except KeyError:
                                        std::cout << ">>>> ERROR: The Stellar Object, named \"" + StellarObject + "\" is not in the Database!")
                                        std::cout << ">>>> Type \"Help\" to list Available Stellar Objects in Database!")

                                    else:
                                        std::cout << ">> Which Parameter Is given?")
                                        std::cout << ">> Declination is essential for calculation Horizontal Coordinates!\n>> Right Ascension only, isn't enough for calculating these parameters!")
                                        RAorDecEquIToHorChoose = input(">> Only Declination (write \'D\'), Or both of\n>> Right Ascension and Declination (write \'B\')?: ")

                                        if(RAorDecEquIToHorChoose == 'D' or RAorDecEquIToHorChoose == 'd'):
                                            RightAscension = NULL
                                            Declination = StellarDict[StellarObject][1]
                                            break

                                        else if(RAorDecEquIToHorChoose == 'B' or RAorDecEquIToHorChoose == 'b'):
                                            RightAscension = StellarDict[StellarObject][0]
                                            Declination = StellarDict[StellarObject][1]
                                            break

                                        else:
                                            std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'D\' or \'B\'!")
                            break

                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    if(RightAscension != NULL and Declination != NULL):
                        while(1):
                            std::cout << "\n>> Is Local Mean Sidereal Time (S) given?")
                            EquIToHorChoose1 = input(">> Write \'Y\' or \'N\' (Yes or No): ")

                            if(EquIToHorChoose1 == 'Y' or EquIToHorChoose1 == 'y' or EquIToHorChoose1 == 'Yes' or EquIToHorChoose1 == 'yes' or EquIToHorChoose1 == 'YEs' or EquIToHorChoose1 == 'yEs' or EquIToHorChoose1 == 'yeS' or EquIToHorChoose1 == 'YeS' or EquIToHorChoose1 == 'yES'):
                                std::cout << "\n>> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                                LocalSiderealTimeHours = float(input("\n> Local Mean Sidereal Time (S) Hours: ") or "0")
                                LocalSiderealTimeMinutes = float(input("> Local Mean Sidereal Time (S) Minutes: ") or "0")
                                LocalSiderealTimeSeconds = float(input("> Local Mean Sidereal Time (S) Seconds: ") or "0")
                                LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600

                                Altitude = NULL
                                break

                            else if(EquIToHorChoose1 == 'N' or EquIToHorChoose1 == 'n' or EquIToHorChoose1 == 'No' or EquIToHorChoose1 == 'no' or EquIToHorChoose1 == 'nO'):
                                LocalSiderealTime = NULL

                                std::cout << "\n>> Is Local Hour Angle given?")
                                EquIToHorChoose2 = input(">> Write \'Y\' or \'N\' (Yes or No): ")

                                if(EquIToHorChoose2 == 'Y' or EquIToHorChoose2 == 'y' or EquIToHorChoose2 == 'Yes' or EquIToHorChoose2 == 'yes' or EquIToHorChoose2 == 'YEs' or EquIToHorChoose2 == 'yEs' or EquIToHorChoose2 == 'yeS' or EquIToHorChoose2 == 'YeS' or EquIToHorChoose2 == 'yES'):
                                    std::cout << "\n>> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                                    LocalHourAngleHours = float(input("\n> Local Hour Angle (t) Hours: ") or "0")
                                    LocalHourAngleMinutes = float(input("> Local Hour Angle (t) Minutes: ") or "0")
                                    LocalHourAngleSeconds = float(input("> Local Hour Angle (t) Seconds: ") or "0")
                                    LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600

                                    Altitude = NULL
                                    break

                                else if(EquIToHorChoose2 == 'N' or EquIToHorChoose2 == 'n' or EquIToHorChoose2 == 'No' or EquIToHorChoose2 == 'no' or EquIToHorChoose2 == 'nO'):
                                    LocalHourAngle = NULL
                                    std::cout << "\n>> From the given data, you can calculate Azimuth (A),\n>> If Altitude (m) is given.")

                                    Azimuth == NULL
                                    AltitudeHours = float(input("> Altitude (m) Hours: ") or "0")
                                    AltitudeMinutes = float(input("> Altitude (m) Minutes: ") or "0")
                                    AltitudeSeconds = float(input("> Altitude (m) Seconds: ") or "0")
                                    ALtitude = AltitudeHours + AltitudeMinutes/60 + AltitudeSeconds/3600
                                    break

                    else if(Declination != NULL and RightAscension == NULL):
                        while(1):
                            std::cout << "\n>> Is Local Hour Angle (t) given?")
                            EquIToHorChooseD = input(">> Write \'Y\' or \'N\' (Yes or No): ")

                            if(EquIToHorChooseD == 'Y' or EquIToHorChooseD == 'y' or EquIToHorChooseD == 'Yes' or EquIToHorChooseD == 'yes' or EquIToHorChooseD == 'YEs' or EquIToHorChooseD == 'yEs' or EquIToHorChooseD == 'yeS' or EquIToHorChooseD == 'YeS' or EquIToHorChooseD == 'yES'):
                                std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                                LocalHourAngleHours = float(input("> Local Hour Angle (t) Hours: ") or "0")
                                LocalHourAngleMinutes = float(input("> Local Hour Angle (t) Minutes: ") or "0")
                                LocalHourAngleSeconds = float(input("> Local Hour Angle (t) Seconds: ") or "0")
                                LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600
                                break

                            else if(EquIToHorChooseD == 'N' or EquIToHorChooseD == 'n' or EquIToHorChooseD == 'No' or EquIToHorChooseD == 'no' or EquIToHorChooseD == 'nO'):
                                LocalHourAngle = NULL
                                std::cout << "\n>> From the given data, you can calculate Azimuth (A),\n>> If Altitude (m) is given.")
                                std::cout << ">> HINT: You can write Altitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                                Azimuth == NULL

                                AltitudeHours = float(input("> Altitude (m) Hours: ") or "0")
                                AltitudeMinutes = float(input("> Altitude (m) Minutes: ") or "0")
                                AltitudeSeconds = float(input("> Altitude (m) Seconds: ") or "0")
                                ALtitude = AltitudeHours + AltitudeMinutes/60 + AltitudeSeconds/3600
                                break

                            else:
                                std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    // Starting parameters could be:
                    // 1. Latitude, RightAscension, Declination, LocalSiderealTime   // φ,α,δ,S:  S,α -> t; t -> H; H,δ,φ -> m; H,δ,m -> A    // Output: A,m
                    // 2. Latitude, RightAscension, Declination, LocalHourAngle      // φ,α,δ,t:  t -> H; H,δ,φ -> m; H,δ,m -> A              // Output: A,m
                    // 3. Latitude, RightAscension, Declination, Azimuth             // φ,α,δ,A:  Not Enough Parameters!                      // Output: NULL
                    // 4. Latitude, RightAscension, Declination, Altitude            // φ,α,δ,m:  m,δ,φ -> H; H,δ,m -> A                      // Output: A from m
                    // 5. Latitude, RightAscension, LocalSiderealTime                // φ,α,S:    Not Enough Parameters!                      // Output: NULL
                    // 6. Latitude, RightAscension, LocalHourAngle                   // φ,α,t:    Not Enough Parameters!                      // Output: NULL
                    // 7. Latitude, RightAscension, Azimuth                          // φ,α,A:    Not Enough Parameters!                      // Output: NULL
                    // 8. Latitude, RightAscension, Altitude                         // φ,α,m:    Not Enough Parameters!                      // Output: NULL
                    // 9. Latitude, Declination, LocalSiderealTime                   // φ,δ,S:    Not Enough Parameters!                      // Output: NULL
                    // 10. Latitude, Declination, LocalHourAngle                     // φ,δ,t:    t -> H; H,δ,φ -> m; H,δ,m -> A              // Output: A,m
                    // 11. Latitude, Declination, Azimuth                            // φ,δ,A:    Not Enough Parameters!                      // Output: NULL
                    // 12. Latitude, Declination, Altitude                           // φ,δ,m:    m,δ,φ -> H; H,δ,m -> A                      // Output: A from m
                    // !!!! Now only those could be selected, which has any kind of output !!!!


                    // Used formulas:
                    // t = S - α
                    // sin(m) = sin(δ) * sin(φ) + cos(δ) * cos(φ) * cos(H)
                    if(LocalSiderealTime != NULL or LocalHourAngle != NULL):

                        Altitude, Azimuth = EquIToHor(Latitude, RightAscension, Declination, Altitude, LocalSiderealTime, LocalHourAngle)

                        // Print Results
                        std::cout << "\n> Calculated Parameters in Horizontal Coord. Sys.:")

                        azimmsg = "- Azimuth (A):  {0}°"
                        altitmsg = "- Altitude (m): {0}°"
                        std::cout << azimmsg.format(Azimuth))
                        std::cout << altitmsg.format(Altitude))
                        std::cout << '\n')

                    // Used formulas:
                    // cos(H) = (sin(m) - sin(δ) * sin(φ)) / cos(δ) * cos(φ)
                    // sin(A) = - sin(H) * cos(δ) / cos(m)
                    else if(Altitude != NULL):
                        Altitude, Azimuth1, Azimuth2, H_dil = EquIToHor(Latitude, RightAscension, Declination, Altitude, LocalSiderealTime, LocalHourAngle)

                        // Print Results
                        std::cout << ">> Available Data are only suited for Calculating Rising/Setting Altitudes!")
                        std::cout << "\n> Calculated Parameter of Rising/Setting Object in Horizontal Coord. Sys.:")

                        azimmsg = "- Rising and Setting Azimuths (A) are:\n- {0}° and {1}°"
                        std::cout << azimmsg.format(Azimuth1, Azimuth2))
                        std::cout << '\n')
                        
                //    ___   
                //   /   |  
                //  / /| |  
                // / /_| |  
                // \___  |_ 
                //     |_(_)
                // 4. Equatorial I to Equatorial II Coordinate System
                else if(CoordMode == '4'):
                    std::cout << ">> Conversion from Equatorial I to Equatorial II Coordinate System")
                    std::cout << ">> Give Parameters!")

                    std::cout << ">> Would you like to give the stellar object's Coordinates by yourself,\n>> Or would like to choose a Predefined Object's Coordinates?")
                    std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for a Predefined Stellar Object's Coordinates!")

                    EquIToEquIIStellarChoose = input(">> (1) User Defined, (2) Predefined: ")

                    while(1):
                        if(EquIToEquIIStellarChoose == '1'):
                            std::cout << ">> HINT: You can write RA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, and type 0\n>> For both Minutes and Seconds.")
                            RightAscensionHours = float(input("> Right Ascension (α) Hours: ") or "0")
                            RightAscensionMinutes = float(input("> Right Ascension (α) Minutes: ") or "0")
                            RightAscensionSeconds = float(input("> Right Ascension (α) Seconds: ") or "0")
                            RightAscension = RightAscensionHours + RightAscensionMinutes/60 + RightAscensionSeconds/3600

                            std::cout << ">> Is Declination given?")
                            while(1):
                                EquIToEquIIChoose = input(">> Write \'Y\' or \'N\' (Yes or No): ")
                                
                                if(EquIToEquIIChoose == 'Y' or EquIToEquIIChoose == 'y' or EquIToEquIIChoose == 'Yes' or EquIToEquIIChoose == 'yes' or EquIToEquIIChoose == 'YEs' or EquIToEquIIChoose == 'yEs' or EquIToEquIIChoose == 'yeS' or EquIToEquIIChoose == 'YeS' or EquIToEquIIChoose == 'yES'):
                                    Declination = float(input("> Declination (δ): "))
                                    break
                                
                                else if(EquIToEquIIChoose == 'N' or EquIToEquIIChoose == 'n' or EquIToEquIIChoose == 'No' or EquIToEquIIChoose == 'no' or EquIToEquIIChoose == 'nO'):
                                    Declination = NULL

                                else:
                                    std::cout << ">>>> ERROR: Invalid option! Try Again!")
                        
                        else if(EquIToEquIIStellarChoose == '2'):
                            while(1):
                                StellarObject = input("> Stellar object's name (type \'H\' for Help): ")

                                if(StellarObject == "Help" or StellarObject == "help" or StellarObject == "H" or StellarObject == "h"):
                                    std::cout << "\n>> Predefined Objects you can choose from:")
                                    for keys in StellarDict.items():
                                        std::cout << keys)
                                    std::cout << '\n')
                                
                                else:
                                    try:
                                        TestVariable = StellarDict[StellarObject][0]
                                        del TestVariable

                                    except KeyError:
                                        std::cout << ">>>> ERROR: The Stellar Object, named \"" + StellarObject + "\" is not in the Database!")
                                        std::cout << ">>>> Type \"Help\" to list Available Stellar Objects in Database!")

                                    else:
                                        RightAscension = StellarDict[StellarObject][0]

                                        std::cout << ">> Is Declination given?")
                                        while(1):
                                            EquIToEquIIChoose = input(">> Write \'Y\' or \'N\' (Yes or No): ")

                                            if(EquIToEquIIChoose == 'Y' or EquIToEquIIChoose == 'y' or EquIToEquIIChoose == 'Yes' or EquIToEquIIChoose == 'yes' or EquIToEquIIChoose == 'YEs' or EquIToEquIIChoose == 'yEs' or EquIToEquIIChoose == 'yeS' or EquIToEquIIChoose == 'YeS' or EquIToEquIIChoose == 'yES'):
                                                Declination = StellarDict[StellarObject][1]
                                                break

                                            else if(EquIToEquIIChoose == 'N' or EquIToEquIIChoose == 'n' or EquIToEquIIChoose == 'No' or EquIToEquIIChoose == 'no' or EquIToEquIIChoose == 'nO'):
                                                Declination = NULL

                                            else:
                                                std::cout << ">>>> ERROR: Invalid option! Try Again!")

                            break

                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    std::cout << ">> You should input LHA (t) manually!")
                    std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LocalHourAngleHours = float(input("> Local Hour Angle (t) Hours: ") or "0")
                    LocalHourAngleMinutes = float(input("> Local Hour Angle (t) Minutes: ") or "0")
                    LocalHourAngleSeconds = float(input("> Local Hour Angle (t) Seconds: ") or "0")
                    LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600

                    LocalSiderealTime = EquIToEquII(RightAscension, LocalHourAngle)

                    LocalSiderealTimeHours = int(LocalSiderealTime)
                    LocalSiderealTimeMinutes = int((LocalSiderealTime - LocalSiderealTimeHours) * 60)
                    LocalSiderealTimeSeconds = int((((LocalSiderealTime - LocalSiderealTimeHours) * 60) - LocalSiderealTimeMinutes) * 60)

                    // Print Results
                    std::cout << "\n> Calculated Parameters in Equatorial II Coord. Sys.:")

                    sidermsg = "- Local Mean Sidereal Time (S): {0}:{1}:{2}"
                    std::cout << sidermsg.format(LocalSiderealTime))
                    
                    if(Declination != NULL):

                        DeclinationHours = int(Declination)
                        DeclinationMinutes = int((Declination - DeclinationHours) * 60)
                        DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60)

                        declinmsg = "- Declination (δ): {0}° {1}\' {2}\""
                        std::cout << declinmsg.format(Declination))

                    else:
                        std::cout << "- Declination is Unknown!")

                    std::cout << '\n')

                //  _____  
                // |  ___| 
                // |___ \  
                //     \ \ 
                // /\__/ / 
                // \____(_)
                // 5. Equatorial II to Equatorial I Coordinate System
                else if(CoordMode == '5'):
                    std::cout << ">> Conversion from Equatorial II to Equatorial I Coordinate System")
                    std::cout << ">> Give Parameters!")

                    std::cout << ">> You should input LMST (S) manually!")
                    std::cout << ">> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LocalSiderealTimeHours = float(input("> Local Mean Sidereal Time (S) Hours: ") or "0")
                    LocalSiderealTimeMinutes = float(input("> Local Mean Sidereal Time (S) Minutes: ") or "0")
                    LocalSiderealTimeSeconds = float(input("> Local Mean Sidereal Time (S) Seconds: ") or "0")
                    LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600

                    std::cout << ">> Is Declination given?")
                    while(1):
                        EquIIToEquIChoose = input(">> Write \'Y\' or \'N\' (Yes or No): ")
                        
                        if(EquIIToEquIChoose == 'Y' or EquIIToEquIChoose == 'y' or EquIIToEquIChoose == 'Yes' or EquIIToEquIChoose == 'yes' or EquIIToEquIChoose == 'YEs' or EquIIToEquIChoose == 'yEs' or EquIIToEquIChoose == 'yeS' or EquIIToEquIChoose == 'YeS' or EquIIToEquIChoose == 'yES'):
                            Declination = float(input("> Declination (δ): "))
                            break
                        
                        else if(EquIIToEquIChoose == 'N' or EquIIToEquIChoose == 'n' or EquIIToEquIChoose == 'No' or EquIIToEquIChoose == 'no' or EquIIToEquIChoose == 'nO'):
                            Declination = NULL

                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    while(1):
                        std::cout << ">> Which essential Parameter Is given?")
                        EquIIToEquIDecChoose = input(">> Right Ascension (write \'A\'), or Local Hour Angle in Hours (write \'T\')?: ")
                        if(EquIIToEquIDecChoose == 'A' or EquIIToEquIDecChoose == 'a'):
                            LocalHourAngle = NULL
                            RightAscension = float(input("> Right Ascension (α): "))
                            break

                        else if(EquIIToEquIDecChoose == 'T' or EquIIToEquIDecChoose == 't'):
                            std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                            LocalHourAngleHours = float(input("> Local Hour Angle (t) Hours: ") or "0")
                            LocalHourAngleMinutes = float(input("> Local Hour Angle (t) Minutes: ") or "0")
                            LocalHourAngleSeconds = float(input("> Local Hour Angle (t) Seconds: ") or "0")
                            LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600
                            RightAscension = NULL
                            break

                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'A\' or \'T\'!")

                    LocalHourAngle, RightAscension = EquIIToEquI(LocalSiderealTime, RightAscension, LocalHourAngle)

                    RightAscensionHours = int(RightAscension)
                    RightAscensionMinutes = int((RightAscension - RightAscensionHours) * 60)
                    RightAscensionSeconds = int((((RightAscension - RightAscensionHours) * 60) - RightAscensionMinutes) * 60)

                    // Print Results
                    std::cout << "\n> Calculated parameters in Equatorial I Coord. Sys.:")

                    RAmsg = "- Right Ascension (α): {0}h {1}m {2}s"
                    std::cout << RAmsg.format(RightAscension))

                    if(Declination != NULL):

                        DeclinationHours = int(Declination)
                        DeclinationMinutes = int((Declination - DeclinationHours) * 60)
                        DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60)

                        declinmsg = "- Declination (δ): {0}° {1}\' {2}\""
                        std::cout << declinmsg.format(Declination))

                    else:
                        std::cout << "Declination is Unknown!")

                    std::cout << '\n')

                    hourangmsg = "- Local Hour Angle (t): {0}h {1}m {2}s"
                    std::cout << hourangmsg.format(LocalHourAngle))
                    
                    std::cout << '\n')

                //   ____   
                //  / ___|  
                // / /___   
                // | ___ \  
                // | \_/ |_ 
                // \_____(_)
                // 6. Equatorial II to Horizontal Coordinate System
                else if(CoordMode == '6'):
                    std::cout << ">> Conversion from Equatorial II to Horizontal Coordinate System")
                    std::cout << ">> Give Parameters!")

                    while(1):
                        std::cout << ">>> LOCATION")
                        std::cout << ">> Would you like to give Geographical Coordinates by yourself,\n>> Or would like to choose a predefined Location's Coordinates?")
                        std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for Predefined Locations' Coordinates!")

                        EquIIToHorLocationChoose = input(">> (1) User Defined, (2) Predefined: ")

                        if(EquIIToHorLocationChoose == '1'):
                            std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                            LatitudeHours = float(input("> Latitude (φ) Hours: ") or "0")
                            LatitudeMinutes = float(input("> Latitude (φ) Minutes: ") or "0")
                            LatitudeSeconds = float(input("> Latitude (φ) Seconds: ") or "0")
                            Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600
                            break

                        else if(EquIIToHorLocationChoose == '2'):
                            while(1):
                                Location = input("> Location's name (type \'H\' for Help): ")

                                if(Location == "Help" or Location == "help" or Location == "H" or Location == "h"):
                                    std::cout << "\n>> Predefined Locations you can choose from:")
                                    for keys in LocationDict.items():
                                        std::cout << keys)
                                    std::cout << '\n')

                                else:
                                    try:
                                        Latitude = LocationDictFunc(Location)[0]

                                    except KeyError:
                                        std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!")
                                        std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")

                                    else:
                                        break

                            break

                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")


                    while(1):
                        std::cout << "\n>>> STELLAR OBJECT")
                        std::cout << ">> Would you like to give the stellar object's Coordinates by yourself,\n>> Or would like to choose a Predefined Object's Coordinates?")
                        std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for a Predefined Stellar Object's Coordinates!")

                        EquIIToHorStellarChoose = input(">> (1) User Defined, (2) Predefined: ")

                        if(EquIIToHorStellarChoose == '1'):
                            
                            std::cout << ">> Which essential Parameter Is given?")
                            EquIIToEquIDecChoose = input(">> Right Ascension (write \'A\'), or Local Hour Angle in Hours (write \'T\')?: ")
                            if(EquIIToEquIDecChoose == 'A' or EquIIToEquIDecChoose == 'a'):
                                LocalHourAngle = NULL
                                std::cout << ">> HINT: You can write RA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                                RightAscensionHours = float(input("> Right Ascension (α) Hours: ") or "0")
                                RightAscensionMinutes = float(input("> Right Ascension (α) Minutes: ") or "0")
                                RightAscensionSeconds = float(input("> Right Ascension (α) Seconds: ") or "0")
                                RightAscension = RightAscensionHours + RightAscensionMinutes/60 + RightAscensionSeconds/3600
                                break

                            else if(EquIIToEquIDecChoose == 'T' or EquIIToEquIDecChoose == 't'):
                                std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                                LocalHourAngleHours = float(input("> Local Hour Angle (t) Hours: ") or "0")
                                LocalHourAngleMinutes = float(input("> Local Hour Angle (t) Minutes: ") or "0")
                                LocalHourAngleSeconds = float(input("> Local Hour Angle (t) Seconds: ") or "0")
                                LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600
                                RightAscension = NULL
                                break

                            else:
                                std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'A\' or \'T\'!")
                        
                        else if(EquIIToHorStellarChoose == '2'):
                            while(1):
                                StellarObject = input("> Stellar object's name (type \'H\' for Help): ")

                                if(StellarObject == "Help" or StellarObject == "help" or StellarObject == "H" or StellarObject == "h"):
                                    std::cout << "\n>> Predefined Objects you can choose from:")
                                    for keys in StellarDict.items():
                                        std::cout << keys)
                                    std::cout << '\n')

                                else:
                                    try:
                                        TestVariable = StellarDict[StellarObject][0]
                                        del TestVariable

                                    except KeyError:
                                        std::cout << ">>>> ERROR: The Stellar Object, named \"" + StellarObject + "\" is not in the Database!")
                                        std::cout << ">>>> Type \"Help\" to list Available Stellar Objects in Database!")

                                    else:
                                        std::cout << ">> Which essential Parameter Is given?")
                                        EquIIToEquIDecChoose = input(">> Right Ascension (write \'A\'), or Local Hour Angle in Hours (write \'T\')?: ")
                                        if(EquIIToEquIDecChoose == 'A' or EquIIToEquIDecChoose == 'a'):
                                            LocalHourAngle = NULL
                                            RightAscension = StellarDict[StellarObject][0]
                                            break

                                        else if(EquIIToEquIDecChoose == 'T' or EquIIToEquIDecChoose == 't'):
                                            std::cout << ">> You should input LHA (t) manually!")
                                            std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                                            LocalHourAngleHours = float(input("> Local Hour Angle (t) Hours: ") or "0")
                                            LocalHourAngleMinutes = float(input("> Local Hour Angle (t) Minutes: ") or "0")
                                            LocalHourAngleSeconds = float(input("> Local Hour Angle (t) Seconds: ") or "0")
                                            LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600
                                            RightAscension = NULL
                                            break

                                        else:
                                            std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'A\' or \'T\'!")

                            break

                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    std::cout << ">> You should input LMST (S) manually!")
                    std::cout << ">> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LocalSiderealTimeHours = float(input("> Local Mean Sidereal Time (S) Hours: ") or "0")
                    LocalSiderealTimeMinutes = float(input("> Local Mean Sidereal Time (S) Minutes: ") or "0")
                    LocalSiderealTimeSeconds = float(input("> Local Mean Sidereal Time (S) Seconds: ") or "0")
                    LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600

                    Altitude, Azimuth = EquIIToHor(Latitude, RightAscension, Declination, Altitude, Azimuth, LocalSiderealTime, LocalHourAngle)

                    // Print Results
                    std::cout << "> Calculated Parameters in Horizontal Coord. Sys.:")

                    azimmsg = "- Azimuth (A):  {0}°"
                    altitmsg = "- Altitude (m): {0}°"
                    std::cout << azimmsg.format(Azimuth))
                    std::cout << altitmsg.format(Altitude))
                    std::cout << '\n')

                else if(CoordMode == 'Q' or CoordMode == 'q'):
                    break

                else:
                    std::cout << ">>>> ERROR: Invalid option! Try Again!\n")

        //    _____                    _____  _     _      _____      _      
        //   / ____|                  |  __ \(_)   | |    / ____|    | |     
        //  | |  __  ___  ___   __ _  | |  | |_ ___| |_  | |     __ _| | ___ 
        //  | | |_ |/ _ \/ _ \ / _` | | |  | | / __| __| | |    / _` | |/ __|
        //  | |__| |  __/ (_) | (_| | | |__| | \__ \ |_  | |___| (_| | | (__ 
        //   \_____|\___|\___/ \__, | |_____/|_|___/\__|  \_____\__,_|_|\___|
        //                      __/ |                                        
        //                     |___/                                         
        // GEOGRAPHICAL DISTANCE CALCULATION
        else if(mode == '2'):
            while(1):
                std::cout << ">> Geographical Distance Calculator\n")
                std::cout << ">> Please choose a mode you'd like to use!")
                std::cout << "(1) Positional Coordinates from User Input")
                std::cout << "(2) Positional Coordinates of Predefined Locations")
                std::cout << "(Q) Quit to Main Menu\n")

                DistMode = input("> Choose a mode and press enter...: ")
                std::cout << '\n')

                if(DistMode == '1'):
                    std::cout << ">> Calculate Distance from given Coordinates\n")
                    std::cout << ">> Give Parameters!")
                    Latitude1 = float(input("> Latitude //1 (φ1): "))
                    Longitude1 = float(input("> Longitude //1 (λ1): "))
                    Latitude2 = float(input("> Latitude //2 (φ2): "))
                    Longitude2 = float(input("> Longitude //2 (λ2): "))


                else if(DistMode == '2'):
                    std::cout << ">> Calculate Distance of Choosen Predefined Locations\n")
                    std::cout << ">> Write the Names of Two Choosen Cities to the Input!")
                    while(1):
                        Location1 = input("> Location //1 (type \'H\' for Help): ")

                        if(Location1 == "Help" or Location1 == "help" or Location1 == "H" or Location1 == "h"):
                            std::cout << "\n>> Predefined Locations you can choose from:")
                            for keys in LocationDict.items():
                                std::cout << keys)
                            std::cout << '\n')

                        else:
                            try:
                                Latitude1 = LocationDictFunc(Location)[0]
                                Longitude1 = LocationDictFunc(Location)[1]

                            except KeyError:
                                std::cout << ">>>> ERROR: The Location, named \"" + Location1 + "\" is not in the Database!")
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")

                            else:
                                break

                    while(1):
                        Location2 = input("> Location //2 (type \'H\' for Help): ")

                        if(Location2 == "Help" or Location2 == "help" or Location2 == "H" or Location2 == "h"):
                            std::cout << "\n>> Predefined Locations you can choose from:")
                            for keys in LocationDict.items():
                                std::cout << keys)
                            std::cout << '\n')

                        else:
                            try:
                                Latitude2 = LocationDictFunc(Location)[0]
                                Longitude2 = LocationDictFunc(Location)[1]

                            except KeyError:
                                std::cout << ">>>> ERROR: The Location, named \"" + Location2 + "\" is not in the Database!")
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")
                                
                            else:
                                break

                    Distance = GeogDistCalc(Latitude1, Latitude2, Longitude1, Longitude2)
                    // Convert Distance to Km
                    Distance = float(Distance / 1000)

                else if(DistMode == 'Q' or DistMode == 'q'):
                    break

                else:
                    std::cout << ">>>> ERROR: Invalid option! Try Again!")

                if(DistMode == 1 || DistMode == 2)
                {
                    Distance = GeogDistCalc(Latitude1, Latitude2, Longitude1, Longitude2)
                    // Convert Distance to Km
                    Distance = float(Distance / 1000)
                    
                    if(DistMode == 1)
                    {
                        distmsg = "\n>>> The Geographical Distance Between\n>>> {0}°,{1}°\n>>> and\n>>> {2}°,{3}°\n>>> is\n>>> {4:.3f} km\n"
                        std::cout << distmsg.format(Latitude1,Longitude1,Latitude2,Longitude2, Distance))
                    }

                    else if(DistMode == 2)
                    {
                        distmsg = "\n>>> The Geographical Distance Between\n>>> {0} and {1} is\n>>> {2:.3f} km\n"
                        std::cout << distmsg.format(Location1, Location2, Distance))
                    }
                }

        //   _      __  __  _____ _______    _____      _      
        //  | |    |  \/  |/ ____|__   __|  / ____|    | |     
        //  | |    | \  / | (___    | |    | |     __ _| | ___ 
        //  | |    | |\/| |\___ \   | |    | |    / _` | |/ __|
        //  | |____| |  | |____) |  | |    | |___| (_| | | (__ 
        //  |______|_|  |_|_____/   |_|     \_____\__,_|_|\___|
        // LOCAL MEAN SIDEREAL TIME CALCULATION
        else if(mode == '3'):
            while(1):
                std::cout << ">> Local Mean Sidereal Time Calculator\n")
                std::cout << ">> Please choose a mode you'd like to use!")
                std::cout << "(1) Parameters from User Input")
                std::cout << "(2) Parameters of Predefined Locations")
                std::cout << "(Q) Quit to Main Menu\n")

                DistMode = input("> Choose a mode and press enter...: ")
                std::cout << '\n')

                if(DistMode == '1'):
                    std::cout << ">> Calculate LMST from given Parameters\n")
                    std::cout << ">> Give Parameters!")
                    
                    // Input Positional Parameters
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LatitudeHours = float(input("> Latitude (φ) Hours: ") or "0")
                    LatitudeMinutes = float(input("> Latitude (φ) Minutes: ") or "0")
                    LatitudeSeconds = float(input("> Latitude (φ) Seconds: ") or "0")
                    Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600

                    std::cout << ">> HINT: You can write Longitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LongitudeHours = float(input("> Longitude (λ) Hours: ") or "0")
                    LongitudeMinutes = float(input("> Longitude (λ) Minutes: ") or "0")
                    LongitudeSeconds = float(input("> Longitude (λ) Seconds: ") or "0")
                    Longitude = LongitudeHours + LongitudeMinutes/60 + LongitudeSeconds/3600

                    // Input Time Parameters
                    while(1):
                        DateYear = int(input("> Year: "))
                        if(DateYear != 0):
                            break
                        else:
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n")

                    while(1):
                        DateMonth = int(input("> Month: "))
                        if(DateMonth > 0 and DateMonth < 13):
                            break
                        else:
                            std::cout << ">>>> ERROR: Months should be inside [1,12] interval, and should be Integer!\n")

                    while(1):
                        DateDay = int(input("> Day: "))
                        if(DateYear%4 == 0 and (DateYear%100 != 0 or DateYear%400 == 0)):
                            if(MonthLengthListLeapYear[DateMonth - 1] >= DateDay and DateDay > 0):
                                break
                            else:
                                daysmsg = ">>>> ERROR: Days should be inside [1,{0}] interval, and should be Integer!\n"
                                std::cout << daysmsg.format(MonthLengthListLeapYear[DateMonth - 1]))
                        else:
                            if(MonthLengthList[DateMonth - 1] >= DateDay and DateDay > 0):
                                break
                            else:
                                daysmsg = ">>>> ERROR: Days should be inside [1,{0}] interval, and should be Integer!\n"
                                std::cout << daysmsg.format(MonthLengthList[DateMonth - 1]))

                    while(1):
                        LocalHours = float(input("> Local Hours: ") or "0")
                        if(LocalHours >= 0 and LocalHours < 24):
                            break
                        else:
                            std::cout << ">>>> ERROR: Hours should be inside [0,24[ interval!\n")

                    while(1):
                        LocalMinutes = int(input("> Local Minutes: ") or "0")
                        if(LocalMinutes >= 0 and LocalMinutes <= 59):
                            break
                        else:
                            std::cout << ">>>> ERROR: Minutes should be inside [0,59] interval, and should be Integer!\n")

                    while(1):
                        LocalSeconds = float(input("> Local Seconds: ") or "0")
                        if(LocalSeconds >= 0 and LocalSeconds < 60):
                            break
                        else:
                            std::cout << ">>>> ERROR: Seconds should be inside [0,60[ interval!\n")

                    LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds, UnitedHours, UnitedMinutes, UnitedSeconds, GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, DateYear, DateMonth, DateDay)

                    sidmsg = "\n>>> The Local Mean Sidereal Time\n>>> at {0}:{1}:{2} UT, at location\n>>> {3}°,{4}° with\n>>> {5}:{6}:{7} GMST at 00:00:00 UT\n>>> is {8}:{9}:{10}\n\n"
                    std::cout << sidmsg.format(UnitedHours, UnitedMinutes, UnitedSeconds, Latitude, Longitude, GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds, LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds))

                else if(DistMode == '2'):
                    std::cout << ">> Calculate LMST from the Coordinates of a Predefined Location\n")
                    std::cout << ">> Write the Name of a Choosen Location to the Input!")

                    // Input Choosen Location's Name
                    while(1):
                        Location = input("> Location's name (type \'H\' for Help): ")

                        if(Location == "Help" or Location == "help" or Location == "H" or Location == "h"):
                            std::cout << "\n>> Predefined Locations you can choose from:")
                            for keys in LocationDict.items():
                                std::cout << keys)
                            std::cout << '\n')

                        else:
                            try:
                                Longitude = LocationDictFunc(Location)[1]

                            except KeyError:
                                std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!")
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")

                            else:
                                break

                    // Input Time Parameters
                    while(1):
                        DateYear = int(input("> Year: "))
                        if(DateYear != 0):
                            break
                        else:
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n")

                    while(1):
                        DateMonth = int(input("> Month: "))
                        if(DateMonth > 0 and DateMonth < 13):
                            break
                        else:
                            std::cout << ">>>> ERROR: Months should be inside [1,12] interval, and should be Integer!\n")

                    // Leap Year	Handling
                    while(1):
                        DateDay = int(input("> Day: "))
                        if(DateYear%4 == 0 and (DateYear%100 != 0 or DateYear%400 == 0)):
                            if(MonthLengthListLeapYear[DateMonth - 1] >= DateDay and DateDay > 0):
                                break
                            else:
                                daysmsg = ">>>> ERROR: Days should be inside [1,{0}] interval, and should be Integer!\n"
                                std::cout << daysmsg.format(MonthLengthListLeapYear[DateMonth - 1]))
                        else:
                            if(MonthLengthList[DateMonth - 1] >= DateDay and DateDay > 0):
                                break
                            else:
                                daysmsg = ">>>> ERROR: Days should be inside [1,{0}] interval, and should be Integer!\n"
                                std::cout << daysmsg.format(MonthLengthList[DateMonth - 1]))

                    while(1):
                        LocalHours = float(input("> Local Hours: ") or "0")
                        if(LocalHours >= 0 and LocalHours < 24):
                            break
                        else:
                            std::cout << ">>>> ERROR: Hours should be inside [0,24[ interval!\n")

                    while(1):
                        LocalMinutes = int(input("> Local Minutes: ") or "0")
                        if(LocalMinutes >= 0 and LocalMinutes <= 59):
                            break
                        else:
                            std::cout << ">>>> ERROR: Minutes should be inside [0,59] interval, and should be Integer!\n")

                    while(1):
                        LocalSeconds = float(input("> Local Seconds: ") or "0")
                        if(LocalSeconds >= 0 and LocalSeconds < 60):
                            break
                        else:
                            std::cout << ">>>> ERROR: Seconds should be inside [0,60[ interval!\n")

                    LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds, UnitedHours, UnitedMinutes, UnitedSeconds, GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, DateYear, DateMonth, DateDay)

                    sidmsg = "\n>>> The Local Mean Sidereal Time at {0}:{1}:{2} UT\n>>> in {3} with\n>>> {4}:{5}:{6} GMST at 00:00:00 UT\n>>> is {7}:{8}:{9}\n\n"
                    std::cout << sidmsg.format(UnitedHours, UnitedMinutes, UnitedSeconds, Location, GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds, LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds))

                else if(DistMode == 'Q' or DistMode == 'q'):
                    break

                else:
                    std::cout << ">>>> ERROR: Invalid option! Try Again!")


        //   _______       _ _ _       _     _      _____      _      
        //  |__   __|     (_) (_)     | |   | |    / ____|    | |     
        //     | |_      ___| |_  __ _| |__ | |_  | |     __ _| | ___ 
        //     | \ \ /\ / / | | |/ _` | '_ \| __| | |    / _` | |/ __|
        //     | |\ V  V /| | | | (_| | | | | |_  | |___| (_| | | (__ 
        //     |_| \_/\_/ |_|_|_|\__, |_| |_|\__|  \_____\__,_|_|\___|
        //                        __/ |                               
        //                       |___/                                
        // DATETIME CALCULATION FOR TWILIGHTS
        else if(mode == '4'):
            while(1):
                std::cout << ">> Calculate Datetimes of Twilights at Specific Location")
                std::cout << ">> Please choose a mode you'd like to use!")
                std::cout << "(1) Parameters from User Input")
                std::cout << "(2) Parameters of Predefined Locations")
                std::cout << "(Q) Quit to Main Menu\n")

                TwiMode = input("> Choose a mode and press enter...: ")
                std::cout << '\n')

                // Constant for Calculations
                Planet = OrbitDict["Earth"
]
                if(TwiMode == '1'):
                    std::cout << ">> Calculate Twilights from given Parameters\n")
                    std::cout << ">> Give Parameters!")

                    // Input Positional Parameters
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LatitudeHours = float(input("> Latitude (φ) Hours: ") or "0")
                    LatitudeMinutes = float(input("> Latitude (φ) Minutes: ") or "0")
                    LatitudeSeconds = float(input("> Latitude (φ) Seconds: ") or "0")
                    Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600

                    std::cout << ">> HINT: You can write Longitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LongitudeHours = float(input("> Longitude (λ) Hours: ") or "0")
                    LongitudeMinutes = float(input("> Longitude (λ) Minutes: ") or "0")
                    LongitudeSeconds = float(input("> Longitude (λ) Seconds: ") or "0")
                    Longitude = LongitudeHours + LongitudeMinutes/60 + LongitudeSeconds/3600

                else if(TwiMode == '2'):
                    while(1):
                        std::cout << ">> Calculate Datetimes of Twilights from the Coordinates of a Predefined Location")
                        std::cout << ">> Write the Name of a Choosen Location to the Input!")

                        // Input Choosen Location's Name
                        Location = input("> Location's name (type \'H\' for Help): ")
                        
                        if(Location == "Help" or Location == "help" or Location == "H" or Location == "h"):
                            std::cout << "\n>> Predefined Locations you can choose from:")
                            for keys in LocationDict.items():
                                std::cout << keys)
                            std::cout << '\n')
                        
                        else:
                            try:
                                Latitude = LocationDictFunc(Location)[0]
                                Longitude = LocationDictFunc(Location)[1]

                            except KeyError:
                                std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!")
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")
                                
                            else:
                                break

                else if(TwiMode == 'Q' or TwiMode == 'q'):
                    break

                else:
                    std::cout << ">>>> ERROR: Invalid option! Try Again!")

                if(TwiMode == '1' or TwiMode == '2'):
                    // Input Time Parameters
                    while(1):
                        LocalDateYear = int(input("> Year: "))
                        if(LocalDateYear != 0):
                            break
                        else:
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n")

                    while(1):
                        LocalDateMonth = int(input("> Month: "))
                        if(LocalDateMonth > 0 and LocalDateMonth < 13):
                            break
                        else:
                            std::cout << ">>>> ERROR: Months should be inside [1,12] interval, and should be Integer!\n")

                    // Leap Year	Handling
                    while(1):
                        LocalDateDay = int(input("> Day: "))
                        if(LocalDateYear%4 == 0 and (LocalDateYear%100 != 0 or LocalDateYear%400 == 0)):
                            if(MonthLengthListLeapYear[LocalDateMonth - 1] >= LocalDateDay and LocalDateDay > 0):
                                break
                            else:
                                daysmsg = ">>>> ERROR: Days should be inside [1,{0}] interval, and should be Integer!\n"
                                std::cout << daysmsg.format(MonthLengthListLeapYear[LocalDateMonth - 1]))
                        else:
                            if(MonthLengthList[LocalDateMonth - 1] >= LocalDateDay and LocalDateDay > 0):
                                break
                            else:
                                daysmsg = ">>>> ERROR: Days should be inside [1,{0}] interval, and should be Integer!\n"
                                std::cout << daysmsg.format(MonthLengthList[LocalDateMonth - 1]))


                    (LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon,
                    LocalHoursMidnight, LocalMinutesMidnight, LocalSecondsMidnight, LocalDateYearMidnight, LocalDateMonthMidnight, LocalDateDayMidnight,
                    LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight,
                    LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight,
                    LocalHoursRiseCivil, LocalMinutesRiseCivil, LocalSecondsRiseCivil, LocalDateYearRiseCivil, LocalDateMonthRiseCivil, LocalDateDayRiseCivil,
                    LocalHoursSetCivil, LocalMinutesSetCivil, LocalSecondsSetCivil, LocalDateYearSetCivil, LocalDateMonthSetCivil, LocalDateDaySetCivil,
                    LocalHoursRiseNaval, LocalMinutesRiseNaval, LocalSecondsRiseNaval, LocalDateYearRiseNaval, LocalDateMonthRiseNaval, LocalDateDayRiseNaval,
                    LocalHoursSetNaval, LocalMinutesSetNaval, LocalSecondsSetNaval, LocalDateYearSetNaval, LocalDateMonthSetNaval, LocalDateDaySetNaval,
                    LocalHoursRiseAstro, LocalMinutesRiseAstro, LocalSecondsRiseAstro, LocalDateYearSetAstro, LocalDateMonthSetAstro, LocalDateDaySetAstro,
                    LocalHoursSetAstro, LocalMinutesSetAstro, LocalSecondsSetAstro, LocalDateYearRiseAstro, LocalDateMonthRiseAstro, LocalDateDayRiseAstro) = TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay)

                    if(TwiMode == '1'):
                        suncoordmsg = ">>> Calculated Datetimes of Twilights at Coordinates \n>>> {0}, {1}:"
                        std::cout << suncoordmsg.format(Latitude, Longitude))

                    else if(TwiMode == '2'):
                        std::cout << "\n>>> Calculated Datetimes of Twilights at " + Location + ":")

                    msgdaylightrise = "\n>> Rising Daylight's time: {0}:{1}:{2} on {3}.{4}.{5}"
                    msgdaylightset = ">> Setting Daylight's time: {0}:{1}:{2} on {3}.{4}.{5}\n"

                    msgcivilrise = "\n>> Rising Civil Twilight's time is between\n>> {0}:{1}:{2} and {3}:{4}:{5} on {6}.{7}.{8}"
                    msgcivilset = ">> Setting Civil Twilight's time is between\n>> {0}:{1}:{2} and {3}:{4}:{5} on {6}.{7}.{8}\n"

                    msgnavalrise = "\n>> Rising Nautical Twilight's time is between\n>> {0}:{1}:{2} and {3}:{4}:{5} on {6}.{7}.{8}"
                    msgnavalset = ">> Setting Nautical Twilight's time is between\n>> {0}:{1}:{2} and {3}:{4}:{5} on {6}.{7}.{8}\n"

                    msgastrorise = "\n>> Rising Astronomical Twilight's time is between\n>> {0}:{1}:{2} and {3}:{4}:{5} on {6}.{7}.{8}"
                    msgastroset = ">> Setting Astronomical Twilight's time is between\n>> {0}:{1}:{2} and {3}:{4}:{5} on {6}.{7}.{8}\n"

                    msgnoon = "\n>> Noon occurs at {0}:{1}:{2} on {3}.{4}.{5}"
                    msgmidnight = ">> Midnight occurs at {0}:{1}:{2} on {3}.{4}.{5}\n"

                    // +4 and -6 are Corrections for more accurate times

                    std::cout << msgdaylightrise.format(LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight))
                    std::cout << msgdaylightset.format(LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight))
                
                    std::cout << msgcivilrise.format(LocalHoursRiseCivil, LocalMinutesRiseCivil + 4, LocalSecondsRiseCivil, LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseCivil, LocalDateMonthRiseCivil, LocalDateDayRiseCivil))
                    std::cout << msgcivilset.format(LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalHoursSetCivil, LocalMinutesSetCivil - 6, LocalSecondsSetCivil, LocalDateYearSetCivil, LocalDateMonthSetCivil, LocalDateDaySetCivil))

                    std::cout << msgnavalrise.format(LocalHoursRiseNaval, LocalMinutesRiseNaval + 4, LocalSecondsRiseNaval, LocalHoursRiseCivil, LocalMinutesRiseCivil + 4, LocalSecondsRiseCivil, LocalDateYearRiseNaval, LocalDateMonthRiseNaval, LocalDateDayRiseNaval))
                    std::cout << msgnavalset.format(LocalHoursSetCivil, LocalMinutesSetCivil - 6, LocalSecondsSetCivil, LocalHoursSetNaval, LocalMinutesSetNaval - 6, LocalSecondsSetNaval, LocalDateYearSetNaval, LocalDateMonthSetNaval, LocalDateDaySetNaval))

                    std::cout << msgastrorise.format(LocalHoursRiseAstro, LocalMinutesRiseAstro + 4, LocalSecondsRiseAstro, LocalHoursRiseNaval, LocalMinutesRiseNaval + 4, LocalSecondsRiseNaval, LocalDateYearSetAstro, LocalDateMonthSetAstro, LocalDateDaySetAstro))
                    std::cout << msgastroset.format(LocalHoursSetNaval, LocalMinutesSetNaval - 6, LocalSecondsSetNaval, LocalHoursSetAstro, LocalMinutesSetAstro - 6, LocalSecondsSetAstro, LocalDateYearRiseAstro, LocalDateMonthRiseAstro, LocalDateDayRiseAstro))

                    std::cout << msgnoon.format(LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon))
                    std::cout << msgmidnight.format(LocalHoursMidnight, LocalMinutesMidnight, LocalSecondsMidnight, LocalDateYearMidnight, LocalDateMonthMidnight, LocalDateDayMidnight))



        //    ___      _               _____    _                   _           
        //   / _ \    | |             |_   _|  (_)                 | |          
        //  / /_\ \___| |_ _ __ ___     | |_ __ _  __ _ _ __   __ _| | ___  ___ 
        //  |  _  / __| __| '__/ _ \    | | '__| |/ _` | '_ \ / _` | |/ _ \/ __|
        //  | | | \__ \ |_| | | (_) |   | | |  | | (_| | | | | (_| | |  __/\__ \
        //  \_| |_/___/\__|_|  \___/    \_/_|  |_|\__,_|_| |_|\__, |_|\___||___/
        //                                                     __/ |            
        //                                                    |___/             
        // Calculate Astronomical Triangles Parameters
        else if(mode == '5'):
            while(1):
                std::cout << ">> Calculate Astronomical Triangles Parameters from given Ones")
                std::cout << ">> Please choose a mode you'd like to use!")
                std::cout << "(1) Parameters from User Input")
                std::cout << "(Q) Quit to Main Menu")

                TrigMode = input("> Choose a mode and press enter...: ")

                std::cout << '\n')

                if(TrigMode == '1'):
                    std::cout << "\n>> Please Give Parameters' Values!")
                    std::cout << ">>> HINT: You should give Parameters in angular units. You can press enter for\n>> A blank input too. Doing like this will mark the actual parameter\n>> As a missing one.")
                    aValue = float(input("> Value for side \'A\': ") or "0")
                    bValue = float(input("> Value for side \'B\': ") or "0")
                    cValue = float(input("> Value for side \'C\': ") or "0")
                    alphaValue = float(input("> Value for angle \'α\': ") or "0")
                    betaValue = float(input("> Value for angle \'β\': ") or "0")
                    gammaValue = float(input("> Value for angle \'γ\': ") or "0")

                else if(TrigMode == '2'):
                    pass
                
                else if(TrigMode == 'Q' or TrigMode == 'q'):
                    break

                else:
                    std::cout << ">>>> ERROR: Invalid option! Try Again!")

                
                if(TrigMode == '1'):
                    
                    aValue, bValue, cValue, alphaValue, betaValue, gammaValue = AstroTriangles(aValue, bValue, cValue, alphaValue, betaValue, gammaValue)

                    if(aValue == 0 or bValue == 0 or cValue == 0 or alphaValue == 0 or betaValue == 0 or gammaValue == 0):
                        std::cout << "Given Data are\'nt enough to calculate the Triangle's Parameters!")


                    std::cout << ">> Calculated Parameters of the Triangle:")
                    std::cout << "Side \'A\': ", aValue)
                    std::cout << "Side \'B\': ", bValue)
                    std::cout << "Side \'C\': ", cValue)
                    std::cout << "Angle \'α\': ", alphaValue)
                    std::cout << "Angle \'β\': ", betaValue)
                    std::cout << "Angle \'γ\': ", gammaValue)
                    std::cout << "\n")


        //   _____                 _ _       _ 
        //  /  ___|               | (_)     | |
        //  \ `--. _   _ _ __   __| |_  __ _| |
        //   `--. \ | | | '_ \ / _` | |/ _` | |
        //  /\__/ / |_| | | | | (_| | | (_| | |
        //  \____/ \__,_|_| |_|\__,_|_|\__,_|_|
        // Plot Sundial for Choosen Locations
        else if(mode == '6'):
            while(1):
                std::cout << ">> Plot Sun's Path on a Sundial at Choosen Location on Earth")
                std::cout << ">> Please choose a mode you'd like to use!")
                std::cout << "(1) Parameters from User Input")
                std::cout << "(2) Parameters of Predefined Locations")
                std::cout << "(Q) Quit to Main Menu")
                
                SundialMode = input("> Choose a mode and press enter...: ")

                std::cout << '\n')

                // Constants for calculation
                Planet = OrbitDict["Earth"
]
                if(SundialMode == '1'):
                    std::cout << ">> Plot a Sundial on a User-defined Location\n")
                    std::cout << ">> Give Parameters!")

                    // Input Positional Parameters
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LatitudeHours = float(input("> Latitude (φ) Hours: ") or "0")
                    LatitudeMinutes = float(input("> Latitude (φ) Minutes: ") or "0")
                    LatitudeSeconds = float(input("> Latitude (φ) Seconds: ") or "0")
                    Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600

                    std::cout << ">> HINT: You can write Longitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LongitudeHours = float(input("> Longitude (λ) Hours: ") or "0")
                    LongitudeMinutes = float(input("> Longitude (λ) Minutes: ") or "0")
                    LongitudeSeconds = float(input("> Longitude (λ) Seconds: ") or "0")
                    Longitude = LongitudeHours + LongitudeMinutes/60 + LongitudeSeconds/3600


                else if(SundialMode == '2'):
                    std::cout << ">> Plot a Sundial on a Predefined Location's Coordinates")
                    std::cout << ">> Write the Name of a Choosen Location to the Input!")

                    // Input Choosen Location's Name
                    while(1):
                        Location = input("> Location's name (type \'H\' for Help): ")
                        
                        if(Location == "Help" or Location == "help" or Location == "H" or Location == "h"):
                            std::cout << "\n>> Predefined Locations you can choose from:")
                            for keys in LocationDict.items():
                                std::cout << keys)
                            std::cout << '\n')
                        
                        else:
                            try:
                                Latitude = LocationDictFunc(Location)[0]
                                Longitude = LocationDictFunc(Location)[1]

                            except KeyError:
                                std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!")
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")
                                
                            else:
                                break

                else if(SundialMode == 'Q' or SundialMode == 'q'):
                    break

                else:
                    std::cout << ">>>> ERROR: Invalid option! Try Again!")


                if(SundialMode == '1' or SundialMode == '2'):
                    std::cout << ">> For which Year would You like to Draw the Sundial?")
                    while(1):
                        SunDialYear = float(input("> Choosen Year: "))
                        if(SunDialYear != 0):
                            break
                        else:
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n")

                    
                    while(1):
                        std::cout << ">> Would you like to plot the Sun's path for a Choosen Date in This Year too?")
                        SunDialChoose = input(">> Write Y for Yes or N for No: ")
                        if(SunDialChoose == 'Y' or SunDialChoose == 'y' or SunDialChoose == 'Yes' or SunDialChoose == 'yes' or SunDialChoose == 'YEs' or SunDialChoose == 'yEs' or SunDialChoose == 'yeS' or SunDialChoose == 'YeS' or SunDialChoose == 'yES'):
                            // Input Time Parameters
                            while(1):
                                LocalDateMonth = int(input("> Month: "))
                                if(LocalDateMonth > 0 and LocalDateMonth < 13):
                                    break
                                else:
                                    std::cout << ">>>> ERROR: Months should be inside [1,12] interval, and should be Integer!\n")

                            // Leap Year	Handling
                            while(1):
                                LocalDateDay = int(input("> Day: "))
                                if(LocalDateYear%4 == 0 and (LocalDateYear%100 != 0 or LocalDateYear%400 == 0)):
                                    if(MonthLengthListLeapYear[LocalDateMonth - 1] >= LocalDateDay and LocalDateDay > 0):
                                        break
                                    else:
                                        daysmsg = ">>>> ERROR: Days should be inside [1,{0}] interval, and should be Integer!\n"
                                        std::cout << daysmsg.format(MonthLengthListLeapYear[LocalDateMonth - 1]))
                                else:
                                    if(MonthLengthList[LocalDateMonth - 1] >= LocalDateDay and LocalDateDay > 0):
                                        break
                                    else:
                                        daysmsg = ">>>> ERROR: Days should be inside [1,{0}] interval, and should be Integer!\n"
                                        std::cout << daysmsg.format(MonthLengthList[LocalDateMonth - 1]))

                            break

                        else if(SunDialChoose == 'N' or SunDialChoose == 'n' or SunDialChoose == 'No' or SunDialChoose == 'no' or SunDialChoose == 'nO'):
                            break

                        else:
                            std::cout << ">>>> ERROR: Invalid option! Try Again!")

                    MeasureNumber = 1000
                    FineTuned = 1000

                    if(SunDialChoose == 'Y' or SunDialChoose == 'y' or SunDialChoose == 'Yes' or SunDialChoose == 'yes' or SunDialChoose == 'YEs' or SunDialChoose == 'yEs' or SunDialChoose == 'yeS' or SunDialChoose == 'YeS' or SunDialChoose == 'yES'):

                        std::cout << "Choosen Date:")
                        ////// CHOOSEN DATE //////
                        LocalHourAngleRiseChoosen, LocalHourAngleSetChoosen, DeclinationSunChoosen = SundialPrecalculations(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay)

                        // Create lists for plot parameters
                        LocalHourAngleChoosen = []
                        AltitudesChoosen = []
                        AzimuthsChoosen = []
                        ShadowsChoosen = []

                        if(LocalHourAngleRiseChoosen > LocalHourAngleSetChoosen):

                            ChoosenStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseChoosen * FineTuned)) / (MeasureNumber / 2))
                            ChoosenStep2 = int(int(LocalHourAngleSetChoosen * FineTuned) / (MeasureNumber / 2))

                            // Calculate plot parameters
                            for LocalHourAngleActual in range(int(LocalHourAngleRiseChoosen * FineTuned), int(23.999999999 * FineTuned), ChoosenStep1):

                                // Norm back to normal
                                LocalHourAngleActual /= FineTuned

                                // Calculate parameters by ~10 seconds interval
                                AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunChoosen)
                                //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunChoosen)
                                //std::cout << LocalHourAngleActual, AltitudeActual)

                                // Append parameters to lists
                                LocalHourAngleActual += 12
                                LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                                LocalHourAngleChoosen.append(LocalHourAngleActual)
                                AltitudesChoosen.append(AltitudeActual)
                                AzimuthsChoosen.append(AzimuthActual)
                                ShadowsChoosen.append(ShadowsLengthActual)

                            // Calculate plot parameters
                            for LocalHourAngleActual in range(0, int(LocalHourAngleSetChoosen * FineTuned), ChoosenStep2):

                                // Norm back to normal
                                LocalHourAngleActual /= FineTuned

                                // Calculate parameters by ~10 seconds interval
                                AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunChoosen)
                                //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunChoosen)
                                //std::cout << LocalHourAngleActual, AltitudeActual)

                                // Append parameters to lists
                                LocalHourAngleActual += 12
                                LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                                LocalHourAngleChoosen.append(LocalHourAngleActual)
                                AltitudesChoosen.append(AltitudeActual)
                                AzimuthsChoosen.append(AzimuthActual)
                                ShadowsChoosen.append(ShadowsLengthActual)


                        else:

                            ChoosenStep = int((int(LocalHourAngleSetChoosen * FineTuned) - int(LocalHourAngleRiseChoosen * FineTuned)) / MeasureNumber)

                            // Calculate plot parameters
                            for LocalHourAngleActual in range(int(LocalHourAngleRiseChoosen * FineTuned), int(LocalHourAngleSetChoosen * FineTuned), ChoosenStep):

                                // Norm back to normal
                                LocalHourAngleActual /= FineTuned

                                // Calculate parameters by ~10 seconds interval
                                AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunChoosen)
                                //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunChoosen)
                                //std::cout << LocalHourAngleActual, AltitudeActual)

                                // Append parameters to lists
                                LocalHourAngleActual += 12
                                LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                                LocalHourAngleChoosen.append(LocalHourAngleActual)
                                AltitudesChoosen.append(AltitudeActual)
                                AzimuthsChoosen.append(AzimuthActual)
                                ShadowsChoosen.append(ShadowsLengthActual)



                    std::cout << "Summer Solstice:")
                    ////// SUMMER SOLSTICE //////
                    LocalDateMonthSummer = 6
                    if(SunDialYear%4 == 0):
                        LocalDateDaySummer = 20

                    else:
                        LocalDateDaySummer = 21

                    LocalHourAngleRiseSummer, LocalHourAngleSetSummer, DeclinationSunSummer = SundialPrecalculations(Planet, Latitude, Longitude, SunDialYear, LocalDateMonthSummer, LocalDateDaySummer)

                    // Create lists for plot parameters
                    LocalHourAngleSummer = []
                    AltitudesSummer = []
                    AzimuthsSummer = []
                    ShadowsSummer = []

                    DeclinationSunSummer = 23.5

                    if(LocalHourAngleRiseSummer > LocalHourAngleSetSummer):

                        SummerStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseSummer * FineTuned)) / (MeasureNumber / 2))
                        SummerStep2 = int(int(LocalHourAngleSetSummer * FineTuned) / (MeasureNumber / 2))

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(int(LocalHourAngleRiseSummer * FineTuned), int(23.999999999 * FineTuned), SummerStep1):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSummer)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSummer)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleSummer.append(LocalHourAngleActual)
                            AltitudesSummer.append(AltitudeActual)
                            AzimuthsSummer.append(AzimuthActual)
                            ShadowsSummer.append(ShadowsLengthActual)

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(0, int(LocalHourAngleSetSummer * FineTuned), SummerStep2):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSummer)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSummer)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleSummer.append(LocalHourAngleActual)
                            AltitudesSummer.append(AltitudeActual)
                            AzimuthsSummer.append(AzimuthActual)
                            ShadowsSummer.append(ShadowsLengthActual)


                    else:

                        SummerStep = int((int(LocalHourAngleSetSummer * FineTuned) - int(LocalHourAngleRiseSummer * FineTuned)) / MeasureNumber)

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(int(LocalHourAngleRiseSummer * FineTuned), int(LocalHourAngleSetSummer * FineTuned), SummerStep):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSummer)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSummer)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleSummer.append(LocalHourAngleActual)
                            AltitudesSummer.append(AltitudeActual)
                            AzimuthsSummer.append(AzimuthActual)
                            ShadowsSummer.append(ShadowsLengthActual)


                    std::cout << "Winter Solstice:")
                    ////// WINTER SOLSTICE //////
                    LocalDateMonthWinter = 12
                    if((SunDialYear + 1)%4 == 0):
                        LocalDateDayWinter = 22

                    else:
                        LocalDateDayWinter = 21

                    LocalHourAngleRiseWinter, LocalHourAngleSetWinter, DeclinationSunWinter = SundialPrecalculations(Planet, Latitude, Longitude, SunDialYear, LocalDateMonthWinter, LocalDateDayWinter)

                    // Create lists for plot parameters
                    LocalHourAngleWinter = []
                    AltitudesWinter = []
                    AzimuthsWinter = []
                    ShadowsWinter = []

                    if(LocalHourAngleRiseWinter > LocalHourAngleSetWinter):

                        WinterStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseWinter * FineTuned)) / (MeasureNumber / 2))
                        WinterStep2 = int(int(LocalHourAngleSetWinter * FineTuned) / (MeasureNumber / 2))

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(int(LocalHourAngleRiseWinter * FineTuned), int(23.999999999 * FineTuned), WinterStep1):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunWinter)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunWinter)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleWinter.append(LocalHourAngleActual)
                            AltitudesWinter.append(AltitudeActual)
                            //AzimuthsWinter.append(AzimuthActual)
                            ShadowsWinter.append(ShadowsLengthActual)

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(0, int(LocalHourAngleSetWinter * FineTuned), WinterStep2):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunWinter)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunWinter)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleWinter.append(LocalHourAngleActual)
                            AltitudesWinter.append(AltitudeActual)
                            AzimuthsWinter.append(AzimuthActual)
                            ShadowsWinter.append(ShadowsLengthActual)


                    else:

                        WinterStep = int((int(LocalHourAngleSetWinter * FineTuned) - int(LocalHourAngleRiseWinter * FineTuned)) / MeasureNumber)

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(int(LocalHourAngleRiseWinter * FineTuned), int(LocalHourAngleSetWinter * FineTuned), SummerStep):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunWinter)
                            //AltitudeActual, AzimuthAShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunWinter)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleWinter.append(LocalHourAngleActual)
                            AltitudesWinter.append(AltitudeActual)
                            AzimuthsWinter.append(AzimuthActual)
                            ShadowsWinter.append(ShadowsLengthActual)


                    std::cout << "March Equinox:")
                    ////// MARCH EQUINOX //////
                    LocalDateMonthMarch = 3
                    LocalDateDayMarch = 20

                    LocalHourAngleRiseMarch, LocalHourAngleSetMarch, DeclinationSunMarch = SundialPrecalculations(Planet, Latitude, Longitude, SunDialYear, LocalDateMonthMarch, LocalDateDayMarch)

                    // Create lists for plot parameters
                    LocalHourAngleMarch = []
                    AltitudesMarch = []
                    AzimuthsMarch = []
                    ShadowsMarch = []

                    if(LocalHourAngleRiseMarch > LocalHourAngleSetMarch):

                        MarchStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseMarch * FineTuned)) / (MeasureNumber / 2))
                        MarchStep2 = int(int(LocalHourAngleSetMarch * FineTuned) / (MeasureNumber / 2))

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(int(LocalHourAngleRiseMarch * FineTuned), int(23.999999999 * FineTuned), MarchStep1):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunMarch)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunMarch)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleMarch.append(LocalHourAngleActual)
                            AltitudesMarch.append(AltitudeActual)
                            AzimuthsMarch.append(AzimuthActual)
                            ShadowsMarch.append(ShadowsLengthActual)

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(0, int(LocalHourAngleSetMarch * FineTuned), MarchStep2):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunMarch)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunMarch)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleMarch.append(LocalHourAngleActual)
                            AltitudesMarch.append(AltitudeActual)
                            AzimuthsMarch.append(AzimuthActual)
                            ShadowsMarch.append(ShadowsLengthActual)


                    else:

                        MarchStep = int((int(LocalHourAngleSetMarch * FineTuned) - int(LocalHourAngleRiseMarch * FineTuned)) / MeasureNumber)

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(int(LocalHourAngleRiseMarch * FineTuned), int(LocalHourAngleSetMarch * FineTuned), SummerStep):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunMarch)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunMarch)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleMarch.append(LocalHourAngleActual)
                            AltitudesMarch.append(AltitudeActual)
                            AzimuthsMarch.append(AzimuthActual)
                            ShadowsMarch.append(ShadowsLengthActual)


                    std::cout << "September Equinox:")
                    ////// SEPTEMBER EQIUNOX //////
                    LocalDateMonthSeptember = 9
                    if(SunDialYear%4 == 0 or (SunDialYear - 1)%4 == 0):
                        LocalDateDaySeptember = 22

                    else:
                        LocalDateDaySeptember = 23

                    LocalHourAngleRiseSeptember, LocalHourAngleSetSeptember, DeclinationSunSeptember = SundialPrecalculations(Planet, Latitude, Longitude, SunDialYear, LocalDateMonthSeptember, LocalDateDaySeptember)

                    // Create lists for plot parameters
                    LocalHourAngleSeptember = []
                    AltitudesSeptember = []
                    AzimuthsSeptember = []
                    ShadowsSeptember = []

                    if(LocalHourAngleRiseSeptember > LocalHourAngleSetSeptember):

                        SeptemberStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseSeptember * FineTuned)) / (MeasureNumber / 2))
                        SeptemberStep2 = int(int(LocalHourAngleSetSeptember * FineTuned) / (MeasureNumber / 2))

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(int(LocalHourAngleRiseSeptember * FineTuned), int(23.999999999 * FineTuned), SeptemberStep1):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSeptember)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSeptember)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleSeptember.append(LocalHourAngleActual)
                            AltitudesSeptember.append(AltitudeActual)
                            AzimuthsSeptember.append(AzimuthActual)
                            ShadowsSeptember.append(ShadowsLengthActual)

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(0, int(LocalHourAngleSetSeptember * FineTuned), SeptemberStep2):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSeptember)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSeptember)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleSeptember.append(LocalHourAngleActual)
                            AltitudesSeptember.append(AltitudeActual)
                            AzimuthsSeptember.append(AzimuthActual)
                            ShadowsSeptember.append(ShadowsLengthActual)


                    else:

                        SeptemberStep = int((int(LocalHourAngleSetSeptember * FineTuned) - int(LocalHourAngleRiseSeptember * FineTuned)) / MeasureNumber)

                        // Calculate plot parameters
                        for LocalHourAngleActual in range(int(LocalHourAngleRiseSeptember * FineTuned), int(LocalHourAngleSetSeptember * FineTuned), SeptemberStep):

                            // Norm back to normal
                            LocalHourAngleActual /= FineTuned

                            // Calculate parameters by ~10 seconds interval
                            AltitudeActual, AzimuthActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSeptember)
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActual, DeclinationSunSeptember)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24)
                            LocalHourAngleSeptember.append(LocalHourAngleActual)
                            AltitudesSeptember.append(AltitudeActual)
                            AzimuthsSeptember.append(AzimuthActual)
                            ShadowsSeptember.append(ShadowsLengthActual)

                    // Sun's path on the Sky
                    plt.title("Sun's path on the Sky")
                    plt.plot(LocalHourAngleSummer, AltitudesSummer, '.', label="Summer Solstice")
                    plt.plot(LocalHourAngleWinter, AltitudesWinter, '.', label="Winter Solstice")
                    plt.plot(LocalHourAngleMarch, AltitudesMarch, '.', label="March Equinox")
                    plt.plot(LocalHourAngleSeptember, AltitudesSeptember, '.', label="Sept. Equinox")

                    plt.xlabel("Hours (h)")
                    plt.ylabel("Altitude of the Sun (°)")
                    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)
                    plt.grid()
                    plt.show()

                    '''plt.plot(AzimuthsSummer, AltitudesSummer, '.', label="Summer Solstice")
                    plt.plot(AzimuthsWinter, AltitudesWinter, '.', label="Winter Solstice")
                    plt.plot(AzimuthsMarch, AltitudesMarch, '.', label="March Equinox")
                    plt.plot(AzimuthsSeptember, AltitudesSeptember, '.', label="Sept. Equinox")
                    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)
                    plt.show()

                    plt.plot(AzimuthsSummer, ShadowsSummer, '.', label="Summer Solstice")
                    plt.plot(AzimuthsWinter, ShadowsWinter, '.', label="Winter Solstice")
                    plt.plot(AzimuthsMarch, ShadowsMarch, '.', label="March Equinox")
                    plt.plot(AzimuthsSeptember, ShadowsSeptember, '.', label="Sept. Equinox")
                    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)
                    plt.show()'''

                    // Shadow's length on the ground
                    plt.title("Sun's path on Sundial")
                    plt.plot(LocalHourAngleSummer, ShadowsSummer, '.', label="Summer Solstice")
                    plt.plot(LocalHourAngleWinter, ShadowsWinter, '.', label="Winter Solstice")
                    plt.plot(LocalHourAngleMarch, ShadowsMarch, '.', label="March Equinox")
                    plt.plot(LocalHourAngleSeptember, ShadowsSeptember, '.', label="Sept. Equinox")

                    plt.xlabel("Hours (h)")
                    plt.ylabel("Length of the shadow (m)")
                    plt.xlim((0,24))
                    plt.ylim((0,10))
                    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)
                    plt.grid()
                    plt.show()



        //    ___              _                                
        //   / _ \            | |                               
        //  / /_\ \_ __   __ _| | ___ _ __ ___  _ __ ___   __ _ 
        //  |  _  | '_ \ / _` | |/ _ \ '_ ` _ \| '_ ` _ \ / _` |
        //  | | | | | | | (_| | |  __/ | | | | | | | | | | (_| |
        //  \_| |_/_| |_|\__,_|_|\___|_| |_| |_|_| |_| |_|\__,_|
        // Draw Sun Analemma at Choosen Location on Earth
        else if(mode == '7'):
            while(1):
                std::cout << ">> Plot the Sun Analemma at Choosen Location on Earth")
                std::cout << ">> Please choose a mode you'd like to use!")
                std::cout << "(1) Parameters from User Input")
                std::cout << "(2) Parameters of Predefined Locations")
                std::cout << "(Q) Quit to Main Menu")
                
                AnalemmaMode = input("> Choose a mode and press enter...: ")

                std::cout << '\n')

                // Constants for calculation
                Planet = OrbitDict["Earth"
]
                if(AnalemmaMode == '1'):
                    std::cout << ">> Plot Analemma on a User-defined Location\n")
                    std::cout << ">> Give Parameters!")

                    // Input Positional Parameters
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LatitudeHours = float(input("> Latitude (φ) Hours: ") or "0")
                    LatitudeMinutes = float(input("> Latitude (φ) Minutes: ") or "0")
                    LatitudeSeconds = float(input("> Latitude (φ) Seconds: ") or "0")
                    Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600

                    std::cout << ">> HINT: You can write Longitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.")
                    LongitudeHours = float(input("> Longitude (λ) Hours: ") or "0")
                    LongitudeMinutes = float(input("> Longitude (λ) Minutes: ") or "0")
                    LongitudeSeconds = float(input("> Longitude (λ) Seconds: ") or "0")
                    Longitude = LongitudeHours + LongitudeMinutes/60 + LongitudeSeconds/3600


                else if(AnalemmaMode == '2'):
                    std::cout << ">> Plot Analemma on a Predefined Location's Coordinates")
                    std::cout << ">> Write the Name of a Choosen Location to the Input!")

                    // Input Choosen Location's Name
                    while(1):
                        Location = input("> Location's name (type \'H\' for Help): ")
                        
                        if(Location == "Help" or Location == "help" or Location == "H" or Location == "h"):
                            std::cout << "\n>> Predefined Locations you can choose from:")
                            for keys in LocationDict.items():
                                std::cout << keys)
                            std::cout << '\n')
                        
                        else:
                            try:
                                Latitude = LocationDictFunc(Location)[0]
                                Longitude = LocationDictFunc(Location)[1]

                            except KeyError:
                                std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!")
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!")
                                
                            else:
                                break

                else if(AnalemmaMode == 'Q' or AnalemmaMode == 'q'):
                    break

                else:
                    std::cout << ">>>> ERROR: Invalid option! Try Again!")


                if(AnalemmaMode == '1' or AnalemmaMode == '2'):
                    while(1):
                        std::cout << ">> For which Year would You like to Draw the Analemma?")
                        AnalemmaYear = float(input("> Choosen Year: "))
                        if(AnalemmaYear != 0):
                            break
                        else:
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n")

                    LocalHourAngleAnalemma = []
                    AltitudesAnalemma = []

                    for LocalDateMonth in range(1, 13):
                        for LocalDateDay in range(1, MonthLengthList[LocalDateMonth - 1] + 1, 1):

                            LocalHourAngleActual, AltitudeActual = SunAnalemma(Planet, Latitude, Longitude, AnalemmaYear, LocalDateMonth, LocalDateDay)

                            LocalHourAngleAnalemma.append(LocalHourAngleActual + 12)
                            AltitudesAnalemma.append(AltitudeActual)

                    // Shadow's length on the ground
                    if(AnalemmaMode == '1'):
                        plt.title("Sun Analemma at Cordinates " + str(Latitude) + "; " + str(Longitude))

                    else if(AnalemmaMode == '2'):
                        plt.title("Sun Analemma at " + Location)

                    plt.plot(LocalHourAngleAnalemma, AltitudesAnalemma, '.')

                    plt.xlabel("Hours (h)")
                    plt.ylabel("Altitude of Sun (°)")
                    plt.xlim((12.0,12.1))
                    plt.grid()
                    plt.show()



        //   _   _                                         _    
        //  | | | |                                       | |   
        //  | |_| | ___  _ __ ___   _____      _____  _ __| | __
        //  |  _  |/ _ \| '_ ` _ \ / _ \ \ /\ / / _ \| '__| |/ /
        //  | | | | (_) | | | | | |  __/\ V  V / (_) | |  |   < 
        //  \_| |_/\___/|_| |_| |_|\___| \_/\_/ \___/|_|  |_|\_\
        // HOMEWORK MODE
        else if(mode == 'Home' or mode == 'home' or mode == 'H' or mode == 'h' or sys.argv[0] == "H" or sys.argv[0] == "h"):

            std::cout << "//////  Csillesz II end-semester homework results, solved by the program  //////")
            std::cout << "_________________________________________________________________________")

            std::cout << "1.1/1.\n")

            Location = "Szombathely"
            Longitude = LocationDictFunc(Location)[1]
            LocalDateYear = 2017
            LocalDateMonth = 12
            LocalDateDay = 27
            LocalHours = 14
            LocalMinutes = 0
            LocalSeconds = 0
            LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds, UnitedHours, UnitedMinutes, UnitedSeconds, GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, LocalDateYear, LocalDateMonth, LocalDateDay)

            std::cout << ">>> Calculate LMST at " + Location + ", at " + str(LocalHours) + ":" + str(LocalMinutes) + ":" + str(LocalSeconds) + " LT, " + str(LocalDateYear) + "." + str(LocalDateMonth) + "." + str(LocalDateDay))
            std::cout << ">>> Used formulas:")
            std::cout << ">>> 1. S_0 (Greenwich Mean Sidereal Time) at 00:00 UT was calculated")
            std::cout << ">>> 2. S (Local Mean Sidereal Time) = S_0 + Longitude/15 + dS * UnitedTime\n")

            sidmsg = ">>> The Local Mean Sidereal Time at {0}:{1}:{2} UT\n>>> in {3} with\n>>> {4}:{5}:{6} GMST at 00:00:00 UT\n>>> is {7}:{8}:{9}\n"
            std::cout << sidmsg.format(UnitedHours, UnitedMinutes, UnitedSeconds, Location, GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds, LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds))
            std::cout << "_________________________________________________________________________")

            std::cout << "1.1/2.\n")

            Location = "Szeged"
            Latitude = LocationDictFunc(Location)[0]
            RightAscensionVenus = 18 + 41/60 + 54/3600
            DeclinationVenus = -(24 + 4/60 + 9/3600)
            Altitude, Azimuth1, Azimuth2, H_dil = EquIToHor(Latitude, RightAscensionVenus, DeclinationVenus, 0, NULL, NULL)

            std::cout << ">>> Calculate Rising and Setting Local Time of Venus,\n>>> As seen from " + Location + ".")
            std::cout << ">>> Used formulas:")
            std::cout << ">>> 1. First let's calculate LHA:\n>>> cos(H) = (sin(m) - sin(δ) * sin(φ)) / cos(δ) * cos(φ)")
            std::cout << ">>> 2. arccos(x) has two correct output on this interval.\n>>> One if them will be the Rising, the other is\n>>> The Setting Local Hour Angle: LHA2 = -LHA1")
            std::cout << ">>> 3. We calculate Azimuth for both Local Hour Angle.\n>>> For each one, we use 2 equations to determine the correct output:")
            std::cout << ">>> a) sin(A) = - sin(H) * cos(δ) / cos(m)\n>>> b) cos(A) = (sin(δ) - sin(φ) * sin(m)) / (cos(φ) * cos(m))")
            std::cout << ">>> These 2 equation outputs 2-2 values for an Azimuth. 1-1 from both these\n>>> Outputs will be equal, and that's the correct value for one of the Azimuths.\n")        

            // Print Results
            std::cout << ">>> INFO: Available Data are only suited for Calculating Rising or\n>>> Setting Altitudes!")
            std::cout << "\n>>> Calculated Parameter of Rising/Setting Object in Horizontal Coord. Sys.:")

            azimmsg = "Rising and Setting Azimuths (A) are:\n>>> {0:.4f}° and {1:.4f}°"
            timemsg = "Elapsed time between them: is {0:.2f}h\n"
            std::cout << azimmsg.format(Azimuth1, Azimuth2))
            std::cout << timemsg.format(H_dil/15))
            std::cout << "_________________________________________________________________________")

            std::cout << "1.1/3.\n")

            Planet = OrbitDict["Earth"
]            Location = "Piszkesteto"
            Latitude = LocationDictFunc(Location)[0]
            Longitude = LocationDictFunc(Location)[1]
            LocalDateYear = 2018
            LocalDateMonth = 12
            LocalDateDay1 = 21
            LocalDateDay2 = 22

            (LocalHoursNoon1, LocalMinutesNoon1, LocalSecondsNoon1, LocalDateYearNoon1, LocalDateMonthNoon1, LocalDateDayNoon1,
                LocalHoursMidnight1, LocalMinutesMidnight1, LocalSecondsMidnight1, LocalDateYearMidnight1, LocalDateMonthMidnight1, LocalDateDayMidnight1,
                LocalHoursRiseDaylight1, LocalMinutesRiseDaylight1, LocalSecondsRiseDaylight1, LocalDateYearRiseDaylight1, LocalDateMonthRiseDaylight1, LocalDateDayRiseDaylight1,
                LocalHoursSetDaylight1, LocalMinutesSetDaylight1, LocalSecondsSetDaylight1, LocalDateYearSetDaylight1, LocalDateMonthSetDaylight1, LocalDateDaySetDaylight1,
                LocalHoursRiseCivil1, LocalMinutesRiseCivil1, LocalSecondsRiseCivil1, LocalDateYearRiseCivil1, LocalDateMonthRiseCivil1, LocalDateDayRiseCivil1,
                LocalHoursSetCivil1, LocalMinutesSetCivil1, LocalSecondsSetCivil1, LocalDateYearSetCivil1, LocalDateMonthSetCivil1, LocalDateDaySetCivil1,
                LocalHoursRiseNaval1, LocalMinutesRiseNaval1, LocalSecondsRiseNaval1, LocalDateYearRiseNaval1, LocalDateMonthRiseNaval1, LocalDateDayRiseNaval1,
                LocalHoursSetNaval1, LocalMinutesSetNaval1, LocalSecondsSetNaval1, LocalDateYearSetNaval1, LocalDateMonthSetNaval1, LocalDateDaySetNaval1,
                LocalHoursRiseAstro1, LocalMinutesRiseAstro1, LocalSecondsRiseAstro1, LocalDateYearSetAstro1, LocalDateMonthSetAstro1, LocalDateDaySetAstro1,
                LocalHoursSetAstro1, LocalMinutesSetAstro1, LocalSecondsSetAstro1, LocalDateYearRiseAstro1, LocalDateMonthRiseAstro1, LocalDateDayRiseAstro1) = TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay1)

            (LocalHoursNoon2, LocalMinutesNoon2, LocalSecondsNoon2, LocalDateYearNoon2, LocalDateMonthNoon2, LocalDateDayNoon2,
                LocalHoursMidnight2, LocalMinutesMidnight2, LocalSecondsMidnight2, LocalDateYearMidnight2, LocalDateMonthMidnight2, LocalDateDayMidnight2,
                LocalHoursRiseDaylight2, LocalMinutesRiseDaylight2, LocalSecondsRiseDaylight2, LocalDateYearRiseDaylight2, LocalDateMonthRiseDaylight2, LocalDateDayRiseDaylight2,
                LocalHoursSetDaylight2, LocalMinutesSetDaylight2, LocalSecondsSetDaylight2, LocalDateYearSetDaylight2, LocalDateMonthSetDaylight2, LocalDateDaySetDaylight2,
                LocalHoursRiseCivil2, LocalMinutesRiseCivil2, LocalSecondsRiseCivil2, LocalDateYearRiseCivil2, LocalDateMonthRiseCivil2, LocalDateDayRiseCivil2,
                LocalHoursSetCivil2, LocalMinutesSetCivil2, LocalSecondsSetCivil2, LocalDateYearSetCivil2, LocalDateMonthSetCivil2, LocalDateDaySetCivil2,
                LocalHoursRiseNaval2, LocalMinutesRiseNaval2, LocalSecondsRiseNaval2, LocalDateYearRiseNaval2, LocalDateMonthRiseNaval2, LocalDateDayRiseNaval2,
                LocalHoursSetNaval2, LocalMinutesSetNaval2, LocalSecondsSetNaval2, LocalDateYearSetNaval2, LocalDateMonthSetNaval2, LocalDateDaySetNaval2,
                LocalHoursRiseAstro2, LocalMinutesRiseAstro2, LocalSecondsRiseAstro2, LocalDateYearSetAstro2, LocalDateMonthSetAstro2, LocalDateDaySetAstro2,
                LocalHoursSetAstro2, LocalMinutesSetAstro2, LocalSecondsSetAstro2, LocalDateYearRiseAstro2, LocalDateMonthRiseAstro2, LocalDateDayRiseAstro2) = TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay2)

            LocalDateDaySetAstroTime1 = LocalHoursSetAstro1 + LocalMinutesSetAstro1/60 + LocalSecondsSetAstro1/3600
            LocalDateDayRiseAstroTime2 = LocalHoursRiseAstro2 + LocalMinutesRiseAstro2/60 + LocalSecondsRiseAstro2/3600

            std::cout << ">>> Calculate lenght of Astronomical Twilight at " + Location + " on\n>>> " + str(LocalDateYear) + "." + str(LocalDateMonth) + "." + str(LocalDateDay2) + " evening.")
            std::cout << ">>> Used formulas:")
            std::cout << ">>> 1. Sun's position for given day was calculated (RA and δ)")
            std::cout << ">>> 2. Julian Date of the Begind/End of Astrological Twilights\n>>> Was been calculated.")
            std::cout << ">>> 3. Julian Date was converted to United Time (UT), then Local Time (LT)\n>>> Was calculated for " + Location + "\n")

            // Length of the astronomical night
            AstroNightLength = 24 - (LocalDateDaySetAstroTime1 - LocalDateDayRiseAstroTime2)
            AstroNightHours = int(AstroNightLength)
            AstroNightMinutes = int((AstroNightLength - AstroNightHours) * 60)
            AstroNightSeconds = int((((AstroNightLength - AstroNightHours) * 60) - AstroNightMinutes) * 60)

            astrosetmsg = ">>> End of Astronomical Twilight on {0}.{1}.{2} is at {3}:{4}:{5}"
            astrorisemsg = ">>> Begin of Astronomical Twilight on {0}.{1}.{2} is at {3}:{4}:{5}"
            astrotimemsg = ">>> The astronomical night's lenght at " + Location + " is {0}:{1}:{2} long\n>>> In the night, between {3}.{4}.{5}, and {6}.\n"
            std::cout << astrosetmsg.format(LocalDateYear, LocalDateMonth, LocalDateDay1, LocalHoursSetAstro1, LocalMinutesSetAstro1, LocalSecondsSetAstro1))
            std::cout << astrorisemsg.format(LocalDateYear, LocalDateMonth, LocalDateDay2, LocalHoursRiseAstro2, LocalMinutesRiseAstro2, LocalSecondsRiseAstro2))
            std::cout << astrotimemsg.format(AstroNightHours, AstroNightMinutes, AstroNightSeconds, LocalDateYear, LocalDateMonth, LocalDateDay1, LocalDateDay2))
            std::cout << "_________________________________________________________________________")

            std::cout << "1.2/1.\n")

            aValue = 54.3666666
            bValue = 72.2
            cValue = 0
            alphaValue = 0
            betaValue = 0
            gammaValue = 94.01666666

            aValue, bValue, cValue, alphaValue, betaValue, gammaValue = AstroTriangles(aValue, bValue, cValue, alphaValue, betaValue, gammaValue)

            std::cout << ">>> Used formulas:")
            std::cout << ">>> The program uses formulas, which may be derived using vector algebra")
            std::cout << ">>> Given parameters: side \'A\', side \'B\' and angle \'γ\'")
            std::cout << ">>> C = arctan( sqrt(\n    (sin(A) * cos(B) - cos(A) * sin(B) * cos(γ))^2 + (sin(B) * sin(γ))^2 ) /\n    (cos(A) * cos(B) + sin(A) * sin(B) * cos(γ)) )")
            std::cout << ">>> α = arctan(\n    (sin(A) * sin(γ)) / (sin(B) * cos(A) - cos(B) * sin(A) * cos(γ))\n    )")
            std::cout << ">>> β = arctan(\n    (sin(B) * sin(γ)) / (sin(A) * cos(B) - cos(A) * sin(B) * cos(γ))\n    )")

            std::cout << ">>> Calculated Parameters of the Triangle:")
            std::cout << ">>> Side \'A\': ", aValue)
            std::cout << ">>> Side \'B\': ", bValue)
            std::cout << ">>> Side \'C\': ", cValue)
            std::cout << ">>> Angle \'α\': ", alphaValue)
            std::cout << ">>> Angle \'β\': ", betaValue)
            std::cout << ">>> Angle \'γ\': ", gammaValue)
            std::cout << "\n")

            std::cout << "_________________________________________________________________________")

            std::cout << "1.2/2.\n")

            Location = "Baja"
            Star = "Altair"
            Latitude = LocationDictFunc(Location)[0]
            Longitude = LocationDictFunc(Location)[1]
            RightAscension = StellarDict[Star][0]
            Declination = StellarDict[Star][1]
            Altitude = NULL
            Azimuth = NULL
            LocalHourAngle = NULL
            LocalHours = 20
            LocalMinutes = 45
            LocalSeconds = 0
            LocalDateYear = 2013
            LocalDateMonth = 6
            LocalDateDay = 21

            // Calculate Local Mean Sidereal Time
            LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds, UnitedHours, UnitedMinutes, UnitedSeconds, GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, LocalDateYear, LocalDateMonth, LocalDateDay)

            // Convert to decimal
            LocalSiderealTime = LocalSiderealHours + LocalSiderealMinutes/60 + LocalSiderealSeconds/3600
            
            // Normalize result
            LocalSiderealTime = NormalizeZeroBounded(LocalSiderealTime, 24)

            Altitude, Azimuth = EquIIToHor(Latitude, RightAscension, Declination, Altitude, Azimuth, LocalSiderealTime, LocalHourAngle)

            // For printing this step too
            LocalHourAngle = LocalSiderealTime - RightAscension
            // Normalize Result
            LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24)

            LocalHourAngleHours = int(LocalHourAngle)
            LocalHourAngleMinutes = int((LocalHourAngle - LocalHourAngleHours) * 60)
            LocalHourAngleSeconds = int((((LocalHourAngle - LocalHourAngleHours) * 60) - LocalHourAngleMinutes) * 60)

            AzimuthHours = int(Azimuth)
            AzimuthMinutes = int((Azimuth - AzimuthHours) * 60)
            AzimuthSeconds = int((((Azimuth - AzimuthHours) * 60) - AzimuthMinutes) * 60)

            AltitudeHours = int(Altitude)
            AltitudeMinutes = int((Altitude - AltitudeHours) * 60)
            AltitudeSeconds = int((((Altitude - AltitudeHours) * 60) - AltitudeMinutes) * 60)

            std::cout << ">>> Used formulas:")
            std::cout << ">>> 1. S_0 (Greenwich Mean Sidereal Time) at 00:00 UT was calculated")
            std::cout << ">>> 2. S (Local Mean Sidereal Time) = S_0 + Longitude/15 + dS * UnitedTime")
            std::cout << ">>> 3. S - α = t; H = 15*t")
            std::cout << ">>> 4. sin(m) = sin(δ) * sin(φ) + cos(δ) * cos(φ) * cos(H);\n>>> Altitude (m) should been between [-π/2,+π/2]")
            std::cout << ">>> 5. sin(A) = - sin(H) * cos(δ) / cos(m), Azimuth at given H hour angle\n>>> Also cos(A) = (sin(δ) - sin(φ) sin(m)) / cos(φ) cos(m)")
            std::cout << ">>> These 2 equation outputs 2-2 values for Azimuth. 1-1 from both these\n>>> Outputs will be equal, and that's the correct value for Azimuth.\n")

            // Print Results
            timemsg = ">>> Altitude and Azimuth of " + Star + " from " + Location + " on {0}.{1}.{2}"
            grwmsg = ">>> GMST: {0}:{1}:{2}"
            std::cout << timemsg.format(LocalDateYear, LocalDateMonth, LocalDateDay))
            std::cout << grwmsg.format(GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds))

            std::cout << ">>> Calculated Parameters:")
            locsidmsg = ">>> Local Mean Siderel Time (S): {0}:{1}:{2}"
            lhamsg = ">>> Local Hour Angle (t): {0}h {1}m {2}s"
            azimmsg = ">>> Azimuth (A):  {0}° {1}' {2}\""
            altitmsg = ">>> Altitude (m): {0}° {1}' {2}\"\n"
            std::cout << locsidmsg.format(LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds))
            std::cout << lhamsg.format(LocalHourAngleHours, LocalHourAngleMinutes, LocalHourAngleSeconds))
            std::cout << azimmsg.format(AzimuthHours, AzimuthMinutes, AzimuthSeconds))
            std::cout << altitmsg.format(AltitudeHours, AltitudeMinutes, AltitudeSeconds))

            std::cout << "_________________________________________________________________________")

            std::cout << "1.2/3.\n")

            Location = "Rio"
            Latitude = LocationDictFunc(Location)[0]
            Longitude = LocationDictFunc(Location)[1]

            Altitude = 55.656388
            Azimuth = 208.113611

            LocalHours = 20
            LocalMinutes = 34
            LocalSeconds = 53
            LocalDateYear = 2018
            LocalDateMonth = 4
            LocalDateDay = 17

            LocalSiderealHours, LocalSiderealMinutes, LocalSiderealSeconds, UnitedHours, UnitedMinutes, UnitedSeconds, GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, LocalDateYear, LocalDateMonth, LocalDateDay)
            
            // Convert to decimal
            LocalSiderealTime = LocalSiderealHours + LocalSiderealMinutes/60 + LocalSiderealSeconds/3600
            
            // Normalize result
            LocalSiderealTime = NormalizeZeroBounded(LocalSiderealTime, 24)

            Declination, RightAscension, LocalSiderealTime = HorToEquII(Latitude, Altitude, Azimuth, LocalSiderealTime)

            // Normalize Parameters
            DeclinationHours = int(Declination)
            DeclinationMinutes = int((Declination - DeclinationHours) * 60)
            DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60)

            RightAscensionHours = int(RightAscension)
            RightAscensionMinutes = int((RightAscension - RightAscensionHours) * 60)
            RightAscensionSeconds = int((((RightAscension - RightAscensionHours) * 60) - RightAscensionMinutes) * 60)

            LocalSiderealTimeHours = int(LocalSiderealTime)
            LocalSiderealTimeMinutes = int((LocalSiderealTime - LocalSiderealTimeHours) * 60)
            LocalSiderealTimeSeconds = int((((LocalSiderealTime - LocalSiderealTimeHours) * 60) - LocalSiderealTimeMinutes) * 60)

            std::cout << "Calculate a star's equatorial II coordinates (S and δ) from Horizontal coords.")
            std::cout << "Used Formulas:")
            std::cout << ">>> 1. S_0 (Greenwich Mean Sidereal Time) at 00:00 UT was calculated")
            std::cout << ">>> 2. S (Local Mean Sidereal Time) = S_0 + Longitude/15 + dS * UnitedTime")
            std::cout << ">>> 3. Declination was calculated:\n>>> sin(δ) = sin(m) * sin(φ) + cos(m) * cos(φ) * cos(A)")
            std::cout << ">>> 4. Local Hour Angle was calculated with two equations:\n>>> a) sin(H) = - sin(A) * cos(m) / cos(δ)\n>>> b) cos(H) = (sin(m) - sin(δ) * sin(φ)) / cos(δ) * cos(φ)")
            std::cout << ">>> These 2 equations outputs 2-2 values for Local Hour Angle. 1-1 from both\n>>> These outputs will be equal, and that's the correct value for LHA.")
            std::cout << ">>> 5. Right Ascension was also calculated: RA = S - t; t = 15 * H\n")

            std::cout << ">>> Initial Coordinates:")
            std::cout << ">>> Azimuth: ", Azimuth)
            std::cout << ">>> Altitude: ", Altitude)

            equIImsg = "\n>>> Calculated Parameters of the Star in Equatorial II Coord. Sys. from {0}:"
            std::cout << equIImsg.format(Location))

            grwmsg = "GMST: {0}:{1}:{2}" 
            declinmsg = "Declination (δ): {0}° {1}\' {2}\""
            RAmsg = "Right Ascension (α): {0}h {1}m {2}s"
            sidermsg = "Local Mean Sidereal Time (S): {0}:{1}:{2}\n"
            std::cout << grwmsg.format(GreenwichSiderealHours, GreenwichSiderealMinutes, GreenwichSiderealSeconds))
            std::cout << declinmsg.format(DeclinationHours, DeclinationMinutes, DeclinationSeconds))
            std::cout << RAmsg.format(RightAscensionHours, RightAscensionMinutes, RightAscensionSeconds))
            std::cout << sidermsg.format(LocalSiderealTimeHours, LocalSiderealTimeMinutes, LocalSiderealTimeSeconds))

            std::cout << "_________________________________________________________________________")

            std::cout << "1.3\n")

            std::cout << ">>> For the Sundial, do the following:")
            std::cout << ">>> 1. Choose mode \'6\'")
            std::cout << ">>> 2. Choose eg. Predefined Locations with option \'2\'")
            std::cout << ">>> 3. Write eg. \'Budapest\'")
            std::cout << ">>> 4. Year = 2018")
            std::cout << ">>> 5. Select \'N\' for \'Choosen Date\'")
            std::cout << ">>> The graph shows the Sun's path on the sky at daylight, which will be\n>>> Projected on the ground, eg. on a Sundial.")
            std::cout << ">>> It also shows, that shadows are longer in Winter, and\n>>> Shorter in Summer. In March and September, the shadows'\n>>> Length are in-between these two.\n\n")


        // MAIN MENU MODE
        // QUIT PROGRAM
        else if(mode == 'Q' or mode == 'q'):
            std::cout << "////////    Developed by Balazs Pal, ELTE    ////////")
            exit()

        else:
            std::cout << ">>>> ERROR: Invalid option! Try Again!")
}