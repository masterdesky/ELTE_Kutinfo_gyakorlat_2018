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
#include <sstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <vector>

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
std::map<std::string, std::vector<double>> LocationDictFunc()
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

    return(LocationDict);
}

// Predefined Equatorial I Coordinates of Some Notable Stellar Objects
// Format:
// "StarName": [Right Ascension (RA), Declination (δ)]
std::map<std::string, std::vector<double>> StellarDictFunc()
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

    return(StellarDict);
}

std::vector<std::string> PlanetDictFunc(std::string Planet)
{
    std::vector<std::string> PlanetDict = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptunus", "Pluto"};

    return(PlanetDict);
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

    Time = TimeMultiply[0];
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
            Month += 1;
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
        Year += 1;
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
            Month += 1;
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
        Year += 1;
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
    if((DateMonth > 3 && DateMonth < 10) || ((DateMonth == 3 && DateDay >=25) || (DateMonth == 10 && (DateDay >= 8 && DateDay <=14))))
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

    if(LHAcos2_1 <= 1 && LHAcos2_1 >= -1)
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
        if(Azimuth1 + 3 > Azimuth3 && Azimuth1 - 3 < Azimuth3)
        {
            Azimuth = Azimuth1;
        }

        else if(Azimuth1 + 3 > Azimuth4 && Azimuth1 - 3 < Azimuth4)
        {
            Azimuth = Azimuth1;
        }

        else if(Azimuth2 + 3 > Azimuth3 && Azimuth2 - 3 < Azimuth3)
        {
            Azimuth = Azimuth2;
        }

        else if(Azimuth2 + 3 > Azimuth4 && Azimuth2 - 3 < Azimuth4)
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
        if(LHAcos <= 1 && LHAcos >= -1)
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
        if(Azimuth1_1 + 3 > Azimuth1_3 && Azimuth1_1 - 3 < Azimuth1_3)
        {
            Azimuth1 = Azimuth1_1;
        }

        else if(Azimuth1_1 + 3 > Azimuth1_4 && Azimuth1_1 - 3 < Azimuth1_4)
        {
            Azimuth1 = Azimuth1_1;
        }

        else if(Azimuth1_2 + 3 > Azimuth1_3 && Azimuth1_2 - 3 < Azimuth1_3)
        {
            Azimuth1 = Azimuth1_2;
        }

        else if(Azimuth1_2 + 3 > Azimuth1_4 && Azimuth1_2 - 3 < Azimuth1_4)
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
        if(Azimuth2_1 + 3 > Azimuth2_3 && Azimuth2_1 - 3 < Azimuth2_3)
        {
            Azimuth2 = Azimuth2_1;
        }

        else if(Azimuth2_1 + 3 > Azimuth2_4 && Azimuth2_1 - 3 < Azimuth2_4)
        {
            Azimuth2 = Azimuth2_1;
        }

        else if(Azimuth2_2 + 3 > Azimuth2_3 && Azimuth2_2 - 3 < Azimuth2_3)
        {
            Azimuth2 = Azimuth2_2;
        }

        else if(Azimuth2_2 + 3 > Azimuth2_4 && Azimuth2_2 - 3 < Azimuth2_4)
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
    if(RightAscension != NULL && LocalHourAngle == NULL)
    {
        LocalHourAngle = LocalSiderealTime - RightAscension;
        // Normalize LHA
        // LHA: [0,24h[
        LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24);
    }

    else if(RightAscension == NULL && LocalHourAngle != NULL)
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
    
    if(RightAscension == NULL && LocalHourAngle != NULL)
    {
        LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24);
    }

    else if(RightAscension != NULL && LocalHourAngle == NULL)
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
    // Declare Variables
    std::string PlanetJ;
    std::string PlanetM;
    std::string PlanetC;
    std::string PlanetA;
    std::string PlanetD;
    std::string PlanetOrbit;

    // 1. Mean Solar Noon
    // JAnomaly is an approximation of Mean Solar Time at WLongitude expressed as a Julian day with the day fraction
    // WLongitude is the longitude west (west is positive, east is negative) of the observer on the Earth
    double WLongitude = - Longitude;
    PlanetJ = Planet.append("J");
    double JAnomaly = (JulianDays - OrbitDictFunc(PlanetJ)[0]) / OrbitDictFunc(PlanetJ)[3] - WLongitude/360;

    // 2. Solar Mean Anomaly
    // MeanAnomaly (M) is the Solar Mean Anomaly used in a few of next equations
    // MeanAnomaly = (M_0 + M_1 * (JulianDays-J2000)) and Norm to 360
    PlanetM = Planet.append("M");
    double MeanAnomaly = (OrbitDictFunc(PlanetM)[0] + OrbitDictFunc(PlanetM)[1] * JulianDays);
    // Normalize Result
    MeanAnomaly = NormalizeZeroBounded(MeanAnomaly, 360);

    // 3. Equation of the Center
    // EquationOfCenter (C) is the Equation of the center value needed to calculate Lambda (see next equation)
    // EquationOfCenter = C_1 * sin(M) + C_2 * sin(2M) + C_3 * sin(3M) + C_4 * sin(4M) + C_5 * sin(5M) + C_6 * sin(6M)
    PlanetC = Planet.append("C");
    double EquationOfCenter = (OrbitDictFunc(PlanetC)[0] * sin((Pi / 180) * (MeanAnomaly)) + OrbitDictFunc(PlanetC)[1] * sin((Pi / 180) * (2 * MeanAnomaly)) + 
                       OrbitDictFunc(PlanetC)[2] * sin((Pi / 180) * (3 * MeanAnomaly)) + OrbitDictFunc(PlanetC)[3] * sin((Pi / 180) * (4 * MeanAnomaly)) + 
                       OrbitDictFunc(PlanetC)[4] * sin((Pi / 180) * (5 * MeanAnomaly)) + OrbitDictFunc(PlanetC)[5] * sin((Pi / 180) * (6 * MeanAnomaly)));

    // 4. Ecliptic Longitude
    // MeanEclLongitudeSun (L_sun) in the Mean Ecliptic Longitude
    // EclLongitudeSun (λ) is the Ecliptic Longitude
    // OrbitDictFunc(PlanetOrbit)[0] is a value for the argument of perihelion
    PlanetOrbit = Planet.append("Orbit");
    double MeanEclLongitudeSun = MeanAnomaly + OrbitDictFunc(PlanetOrbit)[0] + 180;
    double EclLongitudeSun = EquationOfCenter + MeanEclLongitudeSun;
    // Normalize Results
    MeanEclLongitudeSun = NormalizeZeroBounded(MeanEclLongitudeSun, 360);
    EclLongitudeSun = NormalizeZeroBounded(EclLongitudeSun, 360);

    // 5. Right Ascension of Sun (α)
    // PlanetA_2, PlanetA_4 and PlanetA_6 (measured in degrees) are coefficients in the series expansion of the Sun's Right Ascension
    // They varie for different planets in the Solar System
    // RightAscensionSun = EclLongitudeSun + S ≈ EclLongitudeSun + PlanetA_2 * sin(2 * EclLongitudeSun) + PlanetA_4 * sin(4 * EclLongitudeSun) + PlanetA_6 * sin(6 * EclLongitudeSun)
    PlanetA = Planet.append("A");
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
    PlanetD = Planet.append("D");
    double DeclinationSun = (OrbitDictFunc(PlanetD)[0] * sin((Pi / 180) * (EclLongitudeSun)) + OrbitDictFunc(PlanetD)[1] * 
                     pow((sin((Pi / 180) * (EclLongitudeSun))), 3) + OrbitDictFunc(PlanetD)[2] * pow((sin((Pi / 180) * (EclLongitudeSun))), 5));


    // 7. Solar Transit
    // Jtransit is the Julian date for the Local True Solar Transit (or Solar Noon)
    // JulianDate = JulianDays + 2451545
    // 2451545.5 is midnight or the beginning of the equivalent Julian year reference
    // Jtransit = J_x + 0.0053 * sin(MeanANomaly) - 0.0068 * sin(2 * L_sun)
    // "0.0053 * sin(MeanAnomaly) - 0.0069 * sin(2 * EclLongitudeSun)"  is a simplified version of the equation of time
    PlanetJ = Planet.append("J");
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
    if(LHAcos <= 1 && LHAcos >= -1)
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

    // Declare vaiables
    double RightAscensionSunCorr;
    double DeclinationSunCorr;
    double EclLongitudeSun;
    double JtransitCorr;

    double LocalHourAngleSun_PosCorr;
    double LocalHourAngleSun_OrigCorr;

    // Calculate Corrections for LHA of Sun
    std::vector<double> SunsCoordinatesCalcvec = SunsCoordinatesCalc(Planet, Longitude, JAlt_0);
    RightAscensionSunCorr = SunsCoordinatesCalcvec[0];
    DeclinationSunCorr = SunsCoordinatesCalcvec[1];
    EclLongitudeSun = SunsCoordinatesCalcvec[2];
    JtransitCorr = SunsCoordinatesCalcvec[3];

    std::vector<double> SunsLocalHourAnglevec = SunsLocalHourAngle(Planet, Latitude, Longitude, DeclinationSunCorr, EclLongitudeSun, AltitudeOfSun);
    LocalHourAngleSun_PosCorr = SunsLocalHourAnglevec[0];
    LocalHourAngleSun_OrigCorr = SunsLocalHourAnglevec[1];


    std::vector<double> CalculateCorrectionsForJvec = {LocalHourAngleSun_PosCorr, LocalHourAngleSun_OrigCorr, RightAscensionSunCorr, DeclinationSunCorr, JtransitCorr};
    return(CalculateCorrectionsForJvec);
}

std::vector<double> CalculateRiseAndSetTime(std::string Planet, double Latitude, double Longitude, double AltitudeOfSun, double LocalDateYear, double LocalDateMonth, double LocalDateDay)
{
    // Declare variables
    double RightAscensionSun;
    double DeclinationSun;
    double EclLongitudeSun;
    double Jtransit;

    double LocalHourAngleSun_Pos;
    double LocalHourAngleSun_Orig;

    double JRise;
    double JSet;

    // Calculate Actual Julian Date
    // Now UT = 0
    double UnitedHours = 0;
    double UnitedMinutes = 0;
    double UnitedSeconds = 0;
    double JulianDays = CalculateJulianDate(LocalDateYear, LocalDateMonth, LocalDateDay, UnitedHours, UnitedMinutes, UnitedSeconds);

    // Calulate Sun's coordinates on sky
    std::vector<double> SunsCoordinatesCalcvec = SunsCoordinatesCalc(Planet, Longitude, JulianDays);
    RightAscensionSun = SunsCoordinatesCalcvec[0];
    DeclinationSun = SunsCoordinatesCalcvec[1];
    EclLongitudeSun = SunsCoordinatesCalcvec[2];
    Jtransit = SunsCoordinatesCalcvec[3];

    std::vector<double> SunsLocalHourAnglevec = SunsLocalHourAngle(Planet, Latitude, Longitude, DeclinationSun, EclLongitudeSun, AltitudeOfSun);
    LocalHourAngleSun_Pos = SunsLocalHourAnglevec[0];
    LocalHourAngleSun_Orig = SunsLocalHourAnglevec[1];

    /*
    std::cout << "LocalHourAngleSun_Pos: ", LocalHourAngleSun_Pos;
    std::cout << "LocalHourAngleSun_Orig: ", LocalHourAngleSun_Orig;
    */

    // Calulate Rising and Setting Datetimes of the Sun
    // JRise is the actual Julian date of sunrise
    // JSet is the actual Julian date of sunset
    JRise = Jtransit - LocalHourAngleSun_Orig / 360;
    JSet = Jtransit + LocalHourAngleSun_Orig / 360;

    /*
    LocalHourAngleSun_PosCorrRise, LocalHourAngleSun_OrigCorrRise, RightAscensionSunCorrRise, DeclinationSunCorrRise, JtransitCorrRise =  CalculateCorrectionsForJ(Planet, Latitude, Longitude, AltitudeOfSun, JRise)
    LocalHourAngleSun_PosCorrSet, LocalHourAngleSun_OrigCorrSet, RightAscensionSunCorrSet, DeclinationSunCorrSet, JtransitCorrSet = CalculateCorrectionsForJ(Planet, Latitude, Longitude, AltitudeOfSun, JSet)
        
    std::cout << "LocalHourAngleSun_PosCorrRise: ", LocalHourAngleSun_PosCorrRise)
    std::cout << "LocalHourAngleSun_OrigCorrRise: ", LocalHourAngleSun_OrigCorrRise)
    std::cout << "LocalHourAngleSun_PosCorrSet: ", LocalHourAngleSun_PosCorrSet)
    std::cout << "LocalHourAngleSun_OrigCorrSet: ", LocalHourAngleSun_OrigCorrSet)
    */
    
    // Apply Corrections
    //JRise -= (LocalHourAngleSun_Orig + LocalHourAngleSun_OrigCorrRise) / 360
    //JSet -= (LocalHourAngleSun_Orig - LocalHourAngleSun_OrigCorrSet) / 360

    std::vector<double> CalculateRiseAndSetTimevec = {JRise, JSet};
    return(CalculateRiseAndSetTimevec);
}


// Calculate Sunrise and Sunset's Datetime
std::vector<double> SunSetAndRiseDateTime(std::string Planet, double Latitude, double Longitude, double AltitudeOfSun, double LocalDateYear, double LocalDateMonth, double LocalDateDay)
{
    // Declare variables
    double JRise;
    double JSet;

    double UTFracDayRise;
    double UTFracDaySet;

    std::vector<double> CalculateRiseAndSetTimevec = CalculateRiseAndSetTime(Planet, Latitude, Longitude, AltitudeOfSun, LocalDateYear, LocalDateMonth, LocalDateDay);
    JRise = CalculateRiseAndSetTimevec[0];
    JSet = CalculateRiseAndSetTimevec[1];

    // SUNRISE
    UTFracDayRise = JRise - int(JRise);

    UTFracDayRise *= 24;

    std::vector<double> NormalizeTimeParametersRise = NormalizeTimeParameters(UTFracDayRise, LocalDateYear, LocalDateMonth, LocalDateDay);
    double SunRiseUT = NormalizeTimeParametersRise[0];
    double SunRiseUTHours = NormalizeTimeParametersRise[1];
    double SunRiseUTMinutes = NormalizeTimeParametersRise[2];
    double SunRiseUTSeconds = NormalizeTimeParametersRise[3];
    double SunRiseUTDateYear = NormalizeTimeParametersRise[4];
    double SunRiseUTDateMonth = NormalizeTimeParametersRise[5];
    double SunRiseUTDateDay = NormalizeTimeParametersRise[6];


    // SUNSET
    UTFracDaySet = JSet - int(JSet);

    UTFracDaySet *= 24;

    std::vector<double> NormalizeTimeParametersSet = NormalizeTimeParameters(UTFracDaySet, LocalDateYear, LocalDateMonth, LocalDateDay);
    double SunSetUT = NormalizeTimeParametersSet[0];
    double SunSetUTHours = NormalizeTimeParametersSet[1];
    double SunSetUTMinutes = NormalizeTimeParametersSet[2];
    double SunSetUTSeconds = NormalizeTimeParametersSet[3];
    double SunSetUTDateYear = NormalizeTimeParametersSet[4];
    double SunSetUTDateMonth = NormalizeTimeParametersSet[5];
    double SunSetUTDateDay = NormalizeTimeParametersSet[6];



    // Convert results to Local Time
    std::vector<double> UTtoLTRise = UTtoLT(Latitude, SunRiseUTHours, SunRiseUTMinutes, SunRiseUTSeconds, SunRiseUTDateYear, SunRiseUTDateMonth, SunRiseUTDateDay);
    double LocalTimeRise = UTtoLTRise[0];
    double LocalHoursRise = UTtoLTRise[1];
    double LocalMinutesRise = UTtoLTRise[2];
    double LocalSecondsRise = UTtoLTRise[3];
    double LocalDateYearRise = UTtoLTRise[4];
    double LocalDateMonthRise = UTtoLTRise[5];
    double LocalDateDayRise = UTtoLTRise[6];

    std::vector<double> UTtoLTSet = UTtoLT(Latitude, SunSetUTHours, SunSetUTMinutes, SunSetUTSeconds, SunSetUTDateYear, SunSetUTDateMonth, SunSetUTDateDay);
    double LocalTimeSet = UTtoLTSet[0];
    double LocalHoursSet = UTtoLTSet[1];
    double LocalMinutesSet = UTtoLTSet[2];
    double LocalSecondsSet = UTtoLTSet[3];
    double LocalDateYearSet = UTtoLTSet[4];
    double LocalDateMonthSet = UTtoLTSet[5];
    double LocalDateDaySet = UTtoLTSet[6];

    std::vector<double> SunSetAndRiseDateTimevec = {LocalTimeRise, LocalHoursRise, LocalMinutesRise, LocalSecondsRise, LocalDateYearRise, LocalDateMonthRise, LocalDateDayRise,
                                                    LocalTimeSet, LocalHoursSet, LocalMinutesSet, LocalSecondsSet, LocalDateYearSet, LocalDateMonthSet, LocalDateDaySet};

    return(SunSetAndRiseDateTimevec);
}

std::vector<double> TwilightCalc(std::string Planet, double Latitude, double Longitude, double LocalDateYear, double LocalDateMonth, double LocalDateDay)
{
    // Definition of differenc Twilights
    // Begin/End of Civil Twilight:          m = -6°
    // Begin/End of Nautical Twilight:       m = -12°
    // Begin/End of Astronomical Twilight:   m = -18°
    double AltitudeDaylight = 0;
    double AltitudeCivil = -6;
    double AltitudeNaval = -12;
    double AltitudeAstro = -18;


    //Daylight
    std::vector<double> SunSetAndRiseDateTimeDaylight = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeDaylight, LocalDateYear, LocalDateMonth, LocalDateDay);
    double LocalTimeRiseDaylight = SunSetAndRiseDateTimeDaylight[0];
    double LocalHoursRiseDaylight = SunSetAndRiseDateTimeDaylight[1];
    double LocalMinutesRiseDaylight = SunSetAndRiseDateTimeDaylight[2];
    double LocalSecondsRiseDaylight = SunSetAndRiseDateTimeDaylight[3];
    double LocalDateYearRiseDaylight = SunSetAndRiseDateTimeDaylight[4];
    double LocalDateMonthRiseDaylight = SunSetAndRiseDateTimeDaylight[5];
    double LocalDateDayRiseDaylight = SunSetAndRiseDateTimeDaylight[6];
    
    double LocalTimeSetDaylight = SunSetAndRiseDateTimeDaylight[7];
    double LocalHoursSetDaylight = SunSetAndRiseDateTimeDaylight[8];
    double LocalMinutesSetDaylight = SunSetAndRiseDateTimeDaylight[9];
    double LocalSecondsSetDaylight = SunSetAndRiseDateTimeDaylight[10];
    double LocalDateYearSetDaylight = SunSetAndRiseDateTimeDaylight[11];
    double LocalDateMonthSetDaylight = SunSetAndRiseDateTimeDaylight[12];
    double LocalDateDaySetDaylight = SunSetAndRiseDateTimeDaylight[13];


    // Civil Twilight
    std::vector<double> SunSetAndRiseDateTimeCivil = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeCivil, LocalDateYear, LocalDateMonth, LocalDateDay);
    double LocalTimeRiseCivil = SunSetAndRiseDateTimeCivil[0];
    double LocalHoursRiseCivil = SunSetAndRiseDateTimeCivil[1];
    double LocalMinutesRiseCivil = SunSetAndRiseDateTimeCivil[2];
    double LocalSecondsRiseCivil = SunSetAndRiseDateTimeCivil[3];
    double LocalDateYearRiseCivil = SunSetAndRiseDateTimeCivil[4];
    double LocalDateMonthRiseCivil = SunSetAndRiseDateTimeCivil[5];
    double LocalDateDayRiseCivil = SunSetAndRiseDateTimeCivil[6];

    double LocalTimeSetCivil = SunSetAndRiseDateTimeCivil[7];
    double LocalHoursSetCivil = SunSetAndRiseDateTimeCivil[8];
    double LocalMinutesSetCivil = SunSetAndRiseDateTimeCivil[9];
    double LocalSecondsSetCivil = SunSetAndRiseDateTimeCivil[10];
    double LocalDateYearSetCivil = SunSetAndRiseDateTimeCivil[11];
    double LocalDateMonthSetCivil = SunSetAndRiseDateTimeCivil[12];
    double LocalDateDaySetCivil = SunSetAndRiseDateTimeCivil[13];


    // Nautical Twilight
    std::vector<double> SunSetAndRiseDateTimeNaval = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeNaval, LocalDateYear, LocalDateMonth, LocalDateDay);
    double LocalTimeRiseNaval = SunSetAndRiseDateTimeNaval[0];
    double LocalHoursRiseNaval = SunSetAndRiseDateTimeNaval[1];
    double LocalMinutesRiseNaval = SunSetAndRiseDateTimeNaval[2];
    double LocalSecondsRiseNaval = SunSetAndRiseDateTimeNaval[3];
    double LocalDateYearRiseNaval = SunSetAndRiseDateTimeNaval[4];
    double LocalDateMonthRiseNaval = SunSetAndRiseDateTimeNaval[5];
    double LocalDateDayRiseNaval = SunSetAndRiseDateTimeNaval[6];

    double LocalTimeSetNaval = SunSetAndRiseDateTimeNaval[7];
    double LocalHoursSetNaval = SunSetAndRiseDateTimeNaval[8];
    double LocalMinutesSetNaval = SunSetAndRiseDateTimeNaval[9];
    double LocalSecondsSetNaval = SunSetAndRiseDateTimeNaval[10];
    double LocalDateYearSetNaval = SunSetAndRiseDateTimeNaval[11];
    double LocalDateMonthSetNaval = SunSetAndRiseDateTimeNaval[12];
    double LocalDateDaySetNaval = SunSetAndRiseDateTimeNaval[13];


    // Astronomical Twilight
    std::vector<double> SunSetAndRiseDateTimeAstro = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeAstro, LocalDateYear, LocalDateMonth, LocalDateDay);
    double LocalTimeRiseAstro = SunSetAndRiseDateTimeAstro[0];
    double LocalHoursRiseAstro = SunSetAndRiseDateTimeAstro[1];
    double LocalMinutesRiseAstro = SunSetAndRiseDateTimeAstro[2];
    double LocalSecondsRiseAstro = SunSetAndRiseDateTimeAstro[3];
    double LocalDateYearRiseAstro = SunSetAndRiseDateTimeAstro[4];
    double LocalDateMonthRiseAstro = SunSetAndRiseDateTimeAstro[5];
    double LocalDateDayRiseAstro = SunSetAndRiseDateTimeAstro[6];

    double LocalTimeSetAstro = SunSetAndRiseDateTimeAstro[7];
    double LocalHoursSetAstro = SunSetAndRiseDateTimeAstro[8];
    double LocalMinutesSetAstro = SunSetAndRiseDateTimeAstro[9];
    double LocalSecondsSetAstro = SunSetAndRiseDateTimeAstro[10];
    double LocalDateYearSetAstro = SunSetAndRiseDateTimeAstro[11];
    double LocalDateMonthSetAstro = SunSetAndRiseDateTimeAstro[12];
    double LocalDateDaySetAstro = SunSetAndRiseDateTimeAstro[13];


    // Declare variables for stepping a day
    double LocalDateNextDay;
    double LocalDateNextMonth;
    double LocalDateNextYear;

    // Step +1 day
    LocalDateNextDay = LocalDateDay + 1;

    if(int(LocalDateYear)%4 == 0 && (int(LocalDateYear)%100 != 0 || int(LocalDateYear)%400 == 0))
    {
        if(LocalDateNextDay > MonthLengthListLeapYear[int(LocalDateMonth) - 1])
        {
            LocalDateNextDay = 1;
            LocalDateNextMonth = LocalDateMonth + 1;
        }

        else
        {
            LocalDateNextDay = LocalDateDay + 1;
            LocalDateNextMonth = LocalDateMonth;
        }
    }
    else
    {
        if(LocalDateNextDay > MonthLengthList[int(LocalDateMonth) - 1])
        {
            LocalDateNextDay = 1;
            LocalDateNextMonth = LocalDateMonth + 1;
        }

        else
        {
            LocalDateNextDay = LocalDateDay + 1;
            LocalDateNextMonth = LocalDateMonth;
        }
    }

    if(LocalDateNextMonth > 12)
    {
        LocalDateNextMonth = 1;
        LocalDateNextYear = LocalDateYear + 1;
    }
    
    else
    {
        LocalDateNextYear = LocalDateYear;
    }

    // Astronomical Twilight Next Day
    std::vector<double> SunSetAndRiseDateTimeAstro2 = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeAstro, LocalDateNextYear, LocalDateNextMonth, LocalDateNextDay);
    double LocalTimeRiseAstro2 = SunSetAndRiseDateTimeAstro2[0];
    double LocalHoursRiseAstro2 = SunSetAndRiseDateTimeAstro2[1];
    double LocalMinutesRiseAstro2 = SunSetAndRiseDateTimeAstro2[2];
    double LocalSecondsRiseAstro2 = SunSetAndRiseDateTimeAstro2[3];
    double LocalDateYearRiseAstro2 = SunSetAndRiseDateTimeAstro2[4];
    double LocalDateMonthRiseAstro2 = SunSetAndRiseDateTimeAstro2[5];
    double LocalDateDayRiseAstro2 = SunSetAndRiseDateTimeAstro2[6];

    double LocalTimeSetAstro2 = SunSetAndRiseDateTimeAstro2[7];
    double LocalHoursSetAstro2 = SunSetAndRiseDateTimeAstro2[8];
    double LocalMinutesSetAstro2 = SunSetAndRiseDateTimeAstro2[9];
    double LocalSecondsSetAstro2 = SunSetAndRiseDateTimeAstro2[10];
    double LocalDateYearSetAstro2 = SunSetAndRiseDateTimeAstro2[11];
    double LocalDateMonthSetAstro2 = SunSetAndRiseDateTimeAstro2[12];
    double LocalDateDaySetAstro2 = SunSetAndRiseDateTimeAstro2[13];

    //std::cout << LocalTimeRiseAstro, LocalTimeSetAstro)
    //std::cout << LocalTimeRiseAstro2, LocalTimeSetAstro2)

    // Noon and Midnight
    double LocalTimeNoon = LocalTimeRiseDaylight + (LocalTimeSetDaylight - LocalTimeRiseDaylight) / 2;
    double LocalTimeMidnight = LocalTimeSetAstro + (((24 - LocalTimeSetAstro) + LocalTimeRiseAstro2) / 2);

    //std::cout << LocalTimeMidnight;
    //LocalTimeMidnight = LocalTimeNoon + 12

    // Calc Noon Date
    double LocalDateDayNoon = LocalDateDayRiseAstro;
    double LocalDateMonthNoon = LocalDateMonthRiseAstro;
    double LocalDateYearNoon = LocalDateYearRiseAstro;

    // Calc initial Midnight Date
    double LocalDateDayMidnight = LocalDateDayRiseAstro;
    double LocalDateMonthMidnight = LocalDateMonthRiseAstro;
    double LocalDateYearMidnight = LocalDateYearRiseAstro;

    //std::cout << LocalDateDayMidnight;

    // LT of Noon and Midnight
    std::vector<double> NormalizeTimeParametersNoon = NormalizeTimeParameters(LocalTimeNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon);
    LocalTimeNoon = NormalizeTimeParametersNoon[0];
    double LocalHoursNoon = NormalizeTimeParametersNoon[1];
    double LocalMinutesNoon = NormalizeTimeParametersNoon[2];
    double LocalSecondsNoon = NormalizeTimeParametersNoon[3];
    LocalDateYearNoon = NormalizeTimeParametersNoon[4];
    LocalDateMonthNoon = NormalizeTimeParametersNoon[5];
    LocalDateDayNoon = NormalizeTimeParametersNoon[6];

    std::vector<double> NormalizeTimeParametersMidnight = NormalizeTimeParameters(LocalTimeMidnight, LocalDateYearMidnight, LocalDateMonthMidnight, LocalDateDayMidnight);
    LocalTimeMidnight = NormalizeTimeParametersMidnight[0];
    double LocalHoursMidnight = NormalizeTimeParametersMidnight[1];
    double LocalMinutesMidnight = NormalizeTimeParametersMidnight[2];
    double LocalSecondsMidnight = NormalizeTimeParametersMidnight[3];
    LocalDateYearMidnight = NormalizeTimeParametersMidnight[4];
    LocalDateMonthMidnight = NormalizeTimeParametersMidnight[5];
    LocalDateDayMidnight = NormalizeTimeParametersMidnight[6];

    
    std::vector<double> TwilightCalcvec = {LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon,
                                           LocalHoursMidnight, LocalMinutesMidnight, LocalSecondsMidnight, LocalDateYearMidnight, LocalDateMonthMidnight, LocalDateDayMidnight,
                                           LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight,
                                           LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight,
                                           LocalHoursRiseCivil, LocalMinutesRiseCivil, LocalSecondsRiseCivil, LocalDateYearRiseCivil, LocalDateMonthRiseCivil, LocalDateDayRiseCivil,
                                           LocalHoursSetCivil, LocalMinutesSetCivil, LocalSecondsSetCivil, LocalDateYearSetCivil, LocalDateMonthSetCivil, LocalDateDaySetCivil,
                                           LocalHoursRiseNaval, LocalMinutesRiseNaval, LocalSecondsRiseNaval, LocalDateYearRiseNaval, LocalDateMonthRiseNaval, LocalDateDayRiseNaval,
                                           LocalHoursSetNaval, LocalMinutesSetNaval, LocalSecondsSetNaval, LocalDateYearSetNaval, LocalDateMonthSetNaval, LocalDateDaySetNaval,
                                           LocalHoursRiseAstro, LocalMinutesRiseAstro, LocalSecondsRiseAstro, LocalDateYearSetAstro, LocalDateMonthSetAstro, LocalDateDaySetAstro,
                                           LocalHoursSetAstro, LocalMinutesSetAstro, LocalSecondsSetAstro, LocalDateYearRiseAstro, LocalDateMonthRiseAstro, LocalDateDayRiseAstro};
    return(TwilightCalcvec);
}


////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////        5. SOLVE ASTRONOMICAL TRIANGLES         ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////

std::vector<double> AstroTriangles(double aValue, double bValue, double cValue, double alphaValue, double betaValue, double gammaValue)
{
    if(aValue != 0 && bValue != 0 && cValue != 0)
    {
        if(((aValue + bValue) > cValue) && ((aValue + cValue) > bValue) && ((bValue + cValue) > aValue) && 
            (abs(aValue - bValue) < cValue) && (abs(aValue - cValue) < bValue) && (abs(bValue - cValue) < aValue) &&
            ((aValue + bValue + cValue) < 360))
        {
            
            // Calculate angle Alpha
            alphaValue = (180 / Pi) * (acos(
                (cos((Pi / 180) * (aValue)) - cos((Pi / 180) * (bValue)) * cos((Pi / 180) * (cValue))) /
                (sin((Pi / 180) * (bValue)) * sin((Pi / 180) * (cValue)))
            ));

            // Calculate angle Beta
            betaValue = (180 / Pi) * (acos(
                (cos((Pi / 180) * (bValue)) - cos((Pi / 180) * (cValue)) * cos((Pi / 180) * (aValue))) /
                (sin((Pi / 180) * (cValue)) * sin((Pi / 180) * (aValue)))
            ));

            // Calculate angle Gamma
            gammaValue = (180 / Pi) * (acos(
                (cos((Pi / 180) * (cValue)) - cos((Pi / 180) * (aValue)) * cos((Pi / 180) * (bValue))) /
                (sin((Pi / 180) * (aValue)) * sin((Pi / 180) * (bValue)))
            ));
        }

        else
        {
            std::cout << ">> Length of the sides are invalid!\n>> They violate the triangle inequality!" << std::endl;
        }

    }

    else if(aValue != 0 && bValue != 0 && gammaValue != 0)
    {
        // Calculate side C 
        cValue = (180 / Pi) * (atan(
            sqrt(pow((sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (bValue)) -
            cos((Pi / 180) * (aValue)) * sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (gammaValue))), 2) + 
            pow((sin((Pi / 180) * (bValue)) * sin((Pi / 180) * (gammaValue))), 2)) /
            (cos((Pi / 180) * (aValue)) * cos((Pi / 180) * (bValue)) + 
            sin((Pi / 180) * (aValue)) * sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (gammaValue)))
        ));

        // calculate angle Alpha
        alphaValue = (180 / Pi) * (atan(
            (sin((Pi / 180) * (aValue) * sin((Pi / 180) * (gammaValue)))) /
            (sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (aValue)) - 
            cos((Pi / 180) * (bValue)) * sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (gammaValue)))
        ));

        // Calculate angle Beta
        betaValue = (180 / Pi) * (atan(
            (sin((Pi / 180) * (bValue) * sin((Pi / 180) * (gammaValue)))) /
            (sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (bValue)) - 
            cos((Pi / 180) * (aValue)) * sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (gammaValue)))
        ));
    }

    else if(bValue != 0 && cValue != 0 && alphaValue != 0)
    {

        // Calculate side A 
        aValue = (180 / Pi) * (atan(
            sqrt(pow((sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (cValue)) -
            cos((Pi / 180) * (bValue)) * sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (alphaValue))), 2) + 
            pow((sin((Pi / 180) * (cValue)) * sin((Pi / 180) * (alphaValue))), 2)) /
            (cos((Pi / 180) * (bValue)) * cos((Pi / 180) * (cValue)) + 
            sin((Pi / 180) * (bValue)) * sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (alphaValue)))
        ));

        // calculate angle Gamma
        betaValue = (180 / Pi) * (atan(
            (sin((Pi / 180) * (bValue) * sin((Pi / 180) * (alphaValue)))) /
            (sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (bValue)) - 
            cos((Pi / 180) * (cValue)) * sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (alphaValue)))
        ));

        // Calculate angle Alpha
        gammaValue = (180 / Pi) * (atan(
            (sin((Pi / 180) * (cValue) * sin((Pi / 180) * (alphaValue)))) /
            (sin((Pi / 180) * (bValue)) * cos((Pi / 180) * (cValue)) - 
            cos((Pi / 180) * (bValue)) * sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (alphaValue)))
        ));
    }

    else if(aValue != 0 && cValue != 0 && betaValue != 0)
    {

        // Calculate side C 
        bValue = (180 / Pi) * (atan(
            sqrt(pow((sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (aValue)) -
            cos((Pi / 180) * (cValue)) * sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (betaValue))), 2) + 
            pow((sin((Pi / 180) * (aValue)) * sin((Pi / 180) * (betaValue))), 2)) /
            (cos((Pi / 180) * (cValue)) * cos((Pi / 180) * (aValue)) + 
            sin((Pi / 180) * (cValue)) * sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (betaValue)))
        ));

        // calculate angle Alpha
        gammaValue = (180 / Pi) * (atan(
            (sin((Pi / 180) * (cValue) * sin((Pi / 180) * (betaValue)))) /
            (sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (cValue)) - 
            cos((Pi / 180) * (aValue)) * sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (betaValue)))
        ));

        // Calculate angle Beta
        alphaValue = (180 / Pi) * (atan(
            (sin((Pi / 180) * (aValue) * sin((Pi / 180) * (betaValue)))) /
            (sin((Pi / 180) * (cValue)) * cos((Pi / 180) * (aValue)) - 
            cos((Pi / 180) * (cValue)) * sin((Pi / 180) * (aValue)) * cos((Pi / 180) * (betaValue)))
        ));

    }

    else if((aValue != 0 && bValue != 0 && alphaValue != 0) || (aValue != 0 && bValue != 0 && betaValue != 0) || 
        (bValue != 0 && cValue != 0 && betaValue != 0) || (bValue != 0 && cValue != 0 && gammaValue != 0) ||
        (aValue != 0 && cValue != 0 && betaValue != 0) || (aValue != 0 && cValue != 0 && gammaValue != 0))
    {}


    else if((aValue != 0 && betaValue != 0 && gammaValue != 0) || 
        (bValue != 0 && alphaValue != 0 && gammaValue != 0) ||
        (cValue != 0 && alphaValue != 0 && betaValue != 0))
    {}

    
    else if((aValue != 0 && alphaValue != 0 && betaValue != 0) || (aValue != 0 && alphaValue != 0 && gammaValue != 0) ||
        (bValue != 0 && betaValue != 0 && alphaValue != 0) || (bValue != 0 && betaValue != 0 && gammaValue != 0) ||
        (cValue != 0 && gammaValue != 0 && alphaValue != 0) || (aValue != 0 && gammaValue != 0 && betaValue != 0))
    {}


    else if(alphaValue != 0 && betaValue != 0 && gammaValue != 0)
    {}


    else
    {
        aValue = NULL;
        bValue = NULL;
        cValue = NULL;
        alphaValue = NULL;
        betaValue = NULL;
        gammaValue = NULL;
    }

    std::vector<double> AstroTriangles = {aValue, bValue, cValue, alphaValue, betaValue, gammaValue};
    return(AstroTriangles);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////   6. DRAW THE SUN'S ANNUAL PATH ON A SUNDIAL   ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<double> SundialPrecalculations(std::string Planet, double Latitude, double Longitude, double LocalDateYear, double LocalDateMonth, double LocalDateDay)
{
    // We would like to calculate rising and setting time
    double AltitudeOfSun = 0;

    // Daylight start and end LT
    std::vector<double> SunSetAndRiseDateTimeDaylight = SunSetAndRiseDateTime(Planet, Latitude, Longitude, AltitudeOfSun, LocalDateYear, LocalDateMonth, LocalDateDay);
    double LocalTimeRiseDaylight = SunSetAndRiseDateTimeDaylight[0];
    double LocalHoursRiseDaylight = SunSetAndRiseDateTimeDaylight[1];
    double LocalMinutesRiseDaylight = SunSetAndRiseDateTimeDaylight[2];
    double LocalSecondsRiseDaylight = SunSetAndRiseDateTimeDaylight[3];
    double LocalDateYearRiseDaylight = SunSetAndRiseDateTimeDaylight[4];
    double LocalDateMonthRiseDaylight = SunSetAndRiseDateTimeDaylight[5];
    double LocalDateDayRiseDaylight = SunSetAndRiseDateTimeDaylight[6];
    
    double LocalTimeSetDaylight = SunSetAndRiseDateTimeDaylight[7];
    double LocalHoursSetDaylight = SunSetAndRiseDateTimeDaylight[8];
    double LocalMinutesSetDaylight = SunSetAndRiseDateTimeDaylight[9];
    double LocalSecondsSetDaylight = SunSetAndRiseDateTimeDaylight[10];
    double LocalDateYearSetDaylight = SunSetAndRiseDateTimeDaylight[11];
    double LocalDateMonthSetDaylight = SunSetAndRiseDateTimeDaylight[12];
    double LocalDateDaySetDaylight = SunSetAndRiseDateTimeDaylight[13];

    // Calculate the Coordinates of the Sun's Apparent Position
    // Now UT = 0
    double UnitedHours = 0;
    double UnitedMinutes = 0;
    double UnitedSeconds = 0;
    double JulianDays = CalculateJulianDate(LocalDateYear, LocalDateMonth, LocalDateDay, UnitedHours, UnitedMinutes, UnitedSeconds);

    std::vector<double> SunsCoordinatesCalcvec = SunsCoordinatesCalc(Planet, Longitude, JulianDays);
    double RightAscensionSun = SunsCoordinatesCalcvec[0];
    double DeclinationSun = SunsCoordinatesCalcvec[1];
    double EclLongitudeSun = SunsCoordinatesCalcvec[2];
    double Jtransit = SunsCoordinatesCalcvec[3];

    std::vector<double> SunsLocalHourAnglevec = SunsLocalHourAngle(Planet, Latitude, Longitude, DeclinationSun, EclLongitudeSun, AltitudeOfSun);
    double LocalHourAngleSun_Pos = SunsLocalHourAnglevec[0];
    double LocalHourAngleSun_Orig = SunsLocalHourAnglevec[1];

    std::cout << "RA, Dec: " << RightAscensionSun, DeclinationSun;

    // Calculate Local Mean Sidereal Time for both Rising and Setting time
    std::vector<double> LocalSiderealTimeCalcRise = LocalSiderealTimeCalc(Longitude, LocalHoursRiseDaylight, LocalMinutesRiseDaylight, LocalSecondsRiseDaylight, LocalDateYearRiseDaylight, LocalDateMonthRiseDaylight, LocalDateDayRiseDaylight);
    double LocalSiderealHoursRise = LocalSiderealTimeCalcRise[0];
    double LocalSiderealMinutesRise = LocalSiderealTimeCalcRise[1];
    double LocalSiderealSecondsRise = LocalSiderealTimeCalcRise[2];
    double UnitedHoursRise = LocalSiderealTimeCalcRise[3];
    double UnitedMinutesRise = LocalSiderealTimeCalcRise[4];
    double UnitedSecondsRise = LocalSiderealTimeCalcRise[5];
    double GreenwichSiderealHoursRise = LocalSiderealTimeCalcRise[6];
    double GreenwichSiderealMinutesRise = LocalSiderealTimeCalcRise[7];
    double GreenwichSiderealSecondsRise = LocalSiderealTimeCalcRise[8];
    
    std::vector<double> LocalSiderealTimeCalcSet = LocalSiderealTimeCalc(Longitude, LocalHoursSetDaylight, LocalMinutesSetDaylight, LocalSecondsSetDaylight, LocalDateYearSetDaylight, LocalDateMonthSetDaylight, LocalDateDaySetDaylight);
    double LocalSiderealHoursSet = LocalSiderealTimeCalcSet[0];
    double LocalSiderealMinutesSet = LocalSiderealTimeCalcSet[1];
    double LocalSiderealSecondsSet = LocalSiderealTimeCalcSet[2];
    double UnitedHoursSet = LocalSiderealTimeCalcSet[3];
    double UnitedMinutesSet = LocalSiderealTimeCalcSet[4];
    double UnitedSecondsSet = LocalSiderealTimeCalcSet[5];
    double GreenwichSiderealHoursSet = LocalSiderealTimeCalcSet[6];
    double GreenwichSiderealMinutesSet = LocalSiderealTimeCalcSet[7];
    double GreenwichSiderealSecondsSet  = LocalSiderealTimeCalcSet[8];

    // Convert them to Decimal
    double LocalSiderealTimeRise = LocalSiderealHoursRise + LocalSiderealMinutesRise/60 + LocalSiderealSecondsRise/3600;
    double LocalSiderealTimeSet = LocalSiderealHoursSet + LocalSiderealMinutesSet/60 + LocalSiderealSecondsSet/3600;

    // Calculate Hour Angle of Rising and Setting Sun
    double LocalHourAngleRise = LocalSiderealTimeRise - RightAscensionSun;
    double LocalHourAngleSet = LocalSiderealTimeSet - RightAscensionSun;

    std::cout << "Rise/Set LT: " << LocalTimeRiseDaylight << ' ' << LocalTimeSetDaylight;
    std::cout << "Rise/Set ST: " << LocalSiderealTimeRise << ' ' << LocalSiderealTimeSet;
    std::cout << "Rise/Set LHA: " << LocalHourAngleRise << ' ' << LocalHourAngleSet;


    // Normalize Results
    LocalHourAngleRise = NormalizeZeroBounded(LocalHourAngleRise, 24);
    LocalHourAngleSet = NormalizeZeroBounded(LocalHourAngleSet, 24);

    std::cout << "Rise/Set LHA Nor: " << LocalHourAngleRise << ' ' << LocalHourAngleSet;
    std::cout << "\n";

    std::vector<double> SundialPrecalculationsvec = {LocalHourAngleRise, LocalHourAngleSet, DeclinationSun};
    return(SundialPrecalculationsvec);
}


std::vector<double> SundialParametersCalc(double Latitude, double LocalHourAngle, double DeclinationSun)
{
    // Declare variables
    double LocalHourAngleDegrees;
    double Altitude;
    double Altsin;

    double Azimuth;
    /*
    double Azsin;
    double Azimuth1;
    double Azimuth2;
    double Azimuth3;
    double Azimuth4;
    */

    double ShadowLength;

    // Convert to angles from hours (t -> H)
    LocalHourAngleDegrees = LocalHourAngle * 15;

    // Calculate Altitude (m)
    // sin(m) = sin(δ) * sin(φ) + cos(δ) * cos(φ) * cos(H)
    Altsin = sin((Pi / 180) * (DeclinationSun)) * sin((Pi / 180) * (Latitude)) + cos((Pi / 180) * (DeclinationSun)) * cos((Pi / 180) * (Latitude)) * cos((Pi / 180) * (LocalHourAngleDegrees));
    if(Altsin <= 1)
    {
        Altitude = (180 / Pi) * (asin(Altsin));
        //std::cout << Altitude;
    }

    else
    {
        Altitude = (180 / Pi) * (asin(2 - Altsin));
    }

    // Normalize Altitude
    // Altitude: [-π/2,+π/2]
    Altitude = NormalizeSymmetricallyBoundedPI_2(Altitude);

    // We should draw 1/tan(m) of the function of (AzimuthMax - AzimuthMin)
    ShadowLength = 1/tan((Pi / 180) * (Altitude));

    /*
    // Calculate Azimuth (A)
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
    Azimuth = NormalizeZeroBounded(Azimuth, 360)
    */

    Azimuth = 0;

    std::vector<double> SundialParametersCalcvec = {Altitude, Azimuth, ShadowLength};
    return(SundialParametersCalcvec);
}



////////////////////////////////////////////////////////////////////////////////
////////////////                                                ////////////////
////////////////             7. DRAW SUN ANALEMMA               ////////////////
////////////////                                                ////////////////
////////////////////////////////////////////////////////////////////////////////

std::vector<double> SunAnalemma(std::string Planet, double Latitude, double Longitude, double LocalDateYear, double LocalDateMonth, double LocalDateDay)
{
    std::vector<double> TwilightCalcvec = TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay);

    double LocalHoursNoon = TwilightCalcvec[0];
    double LocalMinutesNoon = TwilightCalcvec[1];
    double LocalSecondsNoon = TwilightCalcvec[2];
    double LocalDateYearNoon = TwilightCalcvec[3];
    double LocalDateMonthNoon = TwilightCalcvec[4];
    double LocalDateDayNoon = TwilightCalcvec[5];
    double LocalHoursMidnight = TwilightCalcvec[6];
    double LocalMinutesMidnight = TwilightCalcvec[7];
    double LocalSecondsMidnight = TwilightCalcvec[8];
    double LocalDateYearMidnight = TwilightCalcvec[9];
    double LocalDateMonthMidnight = TwilightCalcvec[10];
    double LocalDateDayMidnight = TwilightCalcvec[11];

    /*
    double LocalHoursRiseDaylight = TwilightCalcvec[12];
    double LocalMinutesRiseDaylight = TwilightCalcvec[13];
    double LocalSecondsRiseDaylight = TwilightCalcvec[14];
    double LocalDateYearRiseDaylight = TwilightCalcvec[15];
    double LocalDateMonthRiseDaylight = TwilightCalcvec[16];
    double LocalDateDayRiseDaylight = TwilightCalcvec[17];
    double LocalHoursSetDaylight = TwilightCalcvec[18];
    double LocalMinutesSetDaylight = TwilightCalcvec[19];
    double LocalSecondsSetDaylight = TwilightCalcvec[20];
    double LocalDateYearSetDaylight = TwilightCalcvec[21];
    double LocalDateMonthSetDaylight = TwilightCalcvec[22];
    double LocalDateDaySetDaylight = TwilightCalcvec[23];

    double LocalHoursRiseCivil = TwilightCalcvec[24];
    double LocalMinutesRiseCivil = TwilightCalcvec[25];
    double LocalSecondsRiseCivil = TwilightCalcvec[26];
    double LocalDateYearRiseCivil = TwilightCalcvec[27];
    double LocalDateMonthRiseCivil = TwilightCalcvec[28];
    double LocalDateDayRiseCivil = TwilightCalcvec[29];
    double LocalHoursSetCivil = TwilightCalcvec[30];
    double LocalMinutesSetCivil = TwilightCalcvec[31];
    double LocalSecondsSetCivil = TwilightCalcvec[32];
    double LocalDateYearSetCivil = TwilightCalcvec[33];
    double LocalDateMonthSetCivil = TwilightCalcvec[34];
    double LocalDateDaySetCivil = TwilightCalcvec[35];

    double LocalHoursRiseNaval = TwilightCalcvec[36];
    double LocalMinutesRiseNaval = TwilightCalcvec[37];
    double LocalSecondsRiseNaval = TwilightCalcvec[38];
    double LocalDateYearRiseNaval = TwilightCalcvec[39];
    double LocalDateMonthRiseNaval = TwilightCalcvec[40];
    double LocalDateDayRiseNaval = TwilightCalcvec[41];
    double LocalHoursSetNaval = TwilightCalcvec[42];
    double LocalMinutesSetNaval = TwilightCalcvec[43];
    double LocalSecondsSetNaval = TwilightCalcvec[44];
    double LocalDateYearSetNaval = TwilightCalcvec[45];
    double LocalDateMonthSetNaval = TwilightCalcvec[46];
    double LocalDateDaySetNaval = TwilightCalcvec[47];

    double LocalHoursRiseAstro = TwilightCalcvec[48];
    double LocalMinutesRiseAstro = TwilightCalcvec[49];
    double LocalSecondsRiseAstro = TwilightCalcvec[50];
    double LocalDateYearSetAstro = TwilightCalcvec[51];
    double LocalDateMonthSetAstro = TwilightCalcvec[52];
    double LocalDateDaySetAstro = TwilightCalcvec[53];
    double LocalHoursSetAstro = TwilightCalcvec[54];
    double LocalMinutesSetAstro = TwilightCalcvec[55];
    double LocalSecondsSetAstro = TwilightCalcvec[56];
    double LocalDateYearRiseAstro = TwilightCalcvec[57];
    double LocalDateMonthRiseAstro = TwilightCalcvec[58];
    double LocalDateDayRiseAstro = TwilightCalcvec[59];
    */

    // Calculate Local Mean Sidereal Time
    std::vector<double> LocalSiderealTimeCalcNoon = LocalSiderealTimeCalc(Longitude, LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon);
    double LocalSiderealHours = LocalSiderealTimeCalcNoon[0];
    double LocalSiderealMinutes = LocalSiderealTimeCalcNoon[1];
    double LocalSiderealSeconds = LocalSiderealTimeCalcNoon[2];
    double UnitedHoursNoon = LocalSiderealTimeCalcNoon[3];
    double UnitedMinutesNoon = LocalSiderealTimeCalcNoon[4];
    double UnitedSecondsNoon = LocalSiderealTimeCalcNoon[5];
    double GreenwichSiderealHours = LocalSiderealTimeCalcNoon[6];
    double GreenwichSiderealMinutes = LocalSiderealTimeCalcNoon[7];
    double GreenwichSiderealSeconds = LocalSiderealTimeCalcNoon[8];

    // Convert LT noon to UT noon time
    std::vector<double> LTtoUTvec = LTtoUT(Longitude, LocalHoursNoon, LocalMinutesNoon, LocalSecondsNoon, LocalDateYearNoon, LocalDateMonthNoon, LocalDateDayNoon);
    double UnitedTime = LTtoUTvec[0];
    double UnitedHours = LTtoUTvec[1];
    double UnitedMinutes = LTtoUTvec[2];
    double UnitedSeconds = LTtoUTvec[3];
    double UnitedDateYear = LTtoUTvec[4];
    double UnitedDateMonth = LTtoUTvec[5];
    double UnitedDateDay = LTtoUTvec[6];

    // Calculate corresponding Julian Date
    double JulianDays = CalculateJulianDate(UnitedDateYear, UnitedDateMonth, UnitedDateDay, UnitedHours, UnitedMinutes, UnitedSeconds);

    // Calculate Sun's position at this time
    std::vector<double> SunsCoordinatesCalcvec = SunsCoordinatesCalc(Planet, Longitude, JulianDays);
    double RightAscensionSun = SunsCoordinatesCalcvec[0];
    double DeclinationSun = SunsCoordinatesCalcvec[1];
    double EclLongitudeSun = SunsCoordinatesCalcvec[2];
    double Jtransit = SunsCoordinatesCalcvec[3];

    // Convert to horizontal
    double LocalSiderealTime = LocalSiderealHours + LocalSiderealMinutes/60 + LocalSiderealSeconds/3600;
    double LocalHourAngle = LocalSiderealTime - RightAscensionSun;
    // Normalize output
    LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24);
    
    // Initial input
    double Altitude = NULL;

    std::vector<double> EquIToHorvec = EquIToHor(Latitude, RightAscensionSun, DeclinationSun, Altitude, LocalSiderealTime, LocalHourAngle);
    Altitude = EquIToHorvec[0];
    double Azimuth = EquIToHorvec[1];

    std::vector<double> SunAnalemmavec = {Altitude, LocalHourAngle};
    return(SunAnalemmavec);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
////////                ...     ..      ..                                                 ////////
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
////////                                                                                   ////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///  ////                                                                                 ////  ///
  ////  ///                                                                            ///  ////
          //                                                                         //
  //   ///                                                                             ///   //
   ////                                                                                  ////

int main()
{
    // Print version info
    std::stringstream STARTMSG;
    STARTMSG << "\n//////// Csillész II Problem Solver Program " << ActualVersion << "////////\n////////         Developed by Balázs Pál.         ////////\n\n";
    std::string STARTMSGstring = STARTMSG.str();
    std::cout << STARTMSGstring;

    while(1)
    {
        std::cout << ">> MAIN MENU <<\n";
        std::cout << "(1) Coordinate System Conversion\n";
        std::cout << "(2) Geographical Distances\n";
        std::cout << "(3) Local Mean Sidereal Time\n";
        std::cout << "(4) Datetimes of Twilights\n";
        std::cout << "(5) Solve Astronomical Triangles\n";
        std::cout << "(6) Plot Sun's Path on Sundial\n";
        std::cout << "(7) Plot Sun's Analemma\n";
        std::cout << "(H) Solve End-Semester Homework\n";
        std::cout << "(Q) Quit Program\n";


        // Choose mode by user input
        std::string mode;
        std::cout << "\n> Choose a mode and press enter...: ";
        std::cin >> mode;
        std::cout << "\n\n\n";

        //    _____                    _    _____              _____                 
        //   / ____|                  | |  / ____|            / ____|                
        //  | |     ___   ___  _ __ __| | | (___  _   _ ___  | |     ___  _ ____   __
        //  | |    / _ \ / _ \| '__/ _` |  \___ \| | | / __| | |    / _ \| '_ \ \ / /
        //  | |___| (_) | (_) | | | (_| |  ____) | |_| \__ \ | |___| (_) | | | \ V / 
        //   \_____\___/ \___/|_|  \__,_| |_____/ \__, |___/  \_____\___/|_| |_|\_/  
        //                                         __/ |                             
        //                                        |___/                              
        // COORDINATE SYSTEM CONVERSION
        if(mode.compare("1") == 0)
        {
            while(1)
            {
                std::cout << ">> Coordinate System Conversion\n";
                std::cout << ">> Please choose which coordinate system conversion you'd like to make!\n";
                std::cout << "(1) Horizontal to Equatorial I\n";
                std::cout << "(2) Horizontal to Equatorial II\n";
                std::cout << "(3) Equatorial I to Horizontal\n";
                std::cout << "(4) Equatorial I to Equatorial II\n";
                std::cout << "(5) Equatorial II to Equatorial I\n";
                std::cout << "(6) Equatorial II to Horizontal\n";
                std::cout << "(Q) Quit to Main Menu\n";

                std::string CoordMode;
                std::cout << "\n> Choose a number and press enter...: ";
                std::cin >> CoordMode;
                std::cout << "\n\n";

                //  __  
                // /  | 
                // `| | 
                //  | | 
                // _| |__
                // \___(_)
                // 1. Horizontal to Equatorial I Coordinate System
                if(CoordMode.compare("1") == 0)
                {
                    std::cout << ">> Conversion from Horizontal to Equatorial I Coordinate System\n";
                    std::cout << ">> Give Parameters!\n";

                    std::cout << ">> Would you like to give Geographical Coordinates by yourself,\n>> or would like to choose a predefined Location's Coordinates?\n";
                    std::cout << ">> Write \'1\' for User defined Coordinates, and write \'2\' for Predefined Locations' Coordinates!\n";

                    std::string HorToEquILocationChoose;
                    std::cout << "\n>> (1) User Defined, (2) Predefined: ";
                    std::cin >> HorToEquILocationChoose;
                    std::cout << "\n\n";

                    double Latitude;
                    double LocalSiderealTime;

                    while(1)
                    {
                        if(HorToEquILocationChoose.compare("1") == 0)
                        {
                            std::cout << ">> User Defined Parameters\n";
                            std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                            
                            double LatitudeHours;
                            double LatitudeMinutes;
                            double LatitudeSeconds;
                            
                            std::cout << "> Latitude (φ) Hours: ";
                            std::cin >> LatitudeHours;
                            std::cout << '\n';
                            std::cout << "> Latitude (φ) Minutes: ";
                            std::cin >> LatitudeMinutes;
                            std::cout << '\n';
                            std::cout << "> Latitude (φ) Seconds: ";
                            std::cin >> LatitudeSeconds;
                            std::cout << '\n';
                            Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600;
                            break;
                        }
                        
                        else if(HorToEquILocationChoose.compare("2") == 0)
                        {
                            std::cout << ">> Predefined Parameters\n";
                            while(1)
                            {
                                std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                                std::string Location;
                                std::cout << "\n> Location's name (type \'H\' for Help): ";
                                std::cin >> Location;
                                std::cout << '\n';

                                if(Location.compare("Help") == 0 || Location.compare("help") == 0 || Location.compare("H") == 0 || Location.compare("h") == 0)
                                {
                                    std::cout << "\n>> Predefined Locations you can choose from:\n";

                                    for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                                    {
                                        std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << "\n";
                                    }

                                    std::cout << '\n';
                                }

                                else
                                {
                                    try
                                    {
                                        Latitude = LocationDict[Location][0];
                                    
                                        auto LocationSearch = LocationDict.find(Location);
                                        if(LocationSearch == LocationDict.end())
                                        {
                                            throw Location;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                    catch(std::string Location)
                                    {
                                        std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!\n";
                                        std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                                    }
                                }
                            }
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                        }
                    }

                    double AltitudeHours;
                    double AltitudeMinutes;
                    double AltitudeSeconds;
                    double AzimuthHours;
                    double AzimuthMinutes;
                    double AzimuthSeconds;

                    std::cout << "> Altitude (m) Hours: ";
                    std::cin >> AltitudeHours;
                    std::cout << '\n';
                    std::cout << "> Altitude (m) Minutes: ";
                    std::cin >> AltitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Altitude (m) Seconds: ";
                    std::cin >> AltitudeSeconds;
                    std::cout << '\n';
                    double Altitude = AltitudeHours + AltitudeMinutes/60 + AltitudeSeconds/3600;

                    std::cout <<  "> Azimuth (A) Hours: ";
                    std::cin >> AzimuthHours;
                    std::cout << '\n';
                    std::cout <<  "> Azimuth (A) Minutes: ";
                    std::cin >> AzimuthMinutes;
                    std::cout << '\n';
                    std::cout <<  "> Azimuth (A) Seconds: ";
                    std::cin >> AzimuthSeconds;
                    std::cout << '\n';
                    double Azimuth = AzimuthHours + AzimuthMinutes/60 + AzimuthSeconds/3600;

                    std::cout << "\n>> Is Local Mean Sidereal Time given?\n";
                    while(1)
                    {
                        std::string HorToEquIChoose;
                        std::cout << ">> Write \'Y\' or \'N\' (Yes or No): ";
                        std::cin >> HorToEquIChoose;
                        std::cout << '\n';

                        if(HorToEquIChoose.compare("Y") == 0 || HorToEquIChoose.compare("y") == 0 || HorToEquIChoose.compare("Yes") == 0 || HorToEquIChoose.compare("yes") == 0 || HorToEquIChoose.compare("YEs") == 0 || HorToEquIChoose.compare("yEs") == 0 || HorToEquIChoose.compare("yeS") == 0 || HorToEquIChoose.compare("YeS") == 0 || HorToEquIChoose.compare("yES") == 0)
                        {
                            std::cout << "\n>> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                            double LocalSiderealTimeHours;
                            double LocalSiderealTimeMinutes;
                            double LocalSiderealTimeSeconds;

                            std::cout << "> Local Mean Sidereal Time (S) Hours: ";
                            std::cin >> LocalSiderealTimeHours;
                            std::cout << '\n';
                            std::cout << "> Local Mean Sidereal Time (S) Minutes: ";
                            std::cin >> LocalSiderealTimeMinutes;
                            std::cout << '\n';
                            std::cout << "> Local Mean Sidereal Time (S) Seconds: ";
                            std::cin >> LocalSiderealTimeSeconds;
                            std::cout << "\n\n";
                            LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600;

                            break;
                        }

                        else if(HorToEquIChoose.compare("N") == 0 || HorToEquIChoose.compare("n") == 0 || HorToEquIChoose.compare("No") == 0 || HorToEquIChoose.compare("no") == 0 || HorToEquIChoose.compare("nO") == 0)
                        {
                            LocalSiderealTime = NULL;
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                        }
                    }

                    // Used Formulas:
                    // sin(δ) = sin(m) * sin(φ) + cos(m) * cos(φ) * cos(A)
                    // sin(H) = - sin(A) * cos(m) / cos(δ)
                    // α = S – t
                    std::vector<double> HorToEquIoutputVec = HorToEquI(Latitude, Altitude, Azimuth, LocalSiderealTime);
                    double RightAscension = HorToEquIoutputVec[0];
                    double Declination = HorToEquIoutputVec[1];
                    double LocalHourAngle = HorToEquIoutputVec[2];

                    // Print Results
                    std::cout << "\n> Calculated parameters in Equatorial I Coord. Sys.:\n";
                    
                    // Declination
                    int DeclinationHours = int(Declination);
                    int DeclinationMinutes = int((Declination - DeclinationHours) * 60);
                    int DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60);

                    std::stringstream declinmsg;
                    declinmsg << "- Declination (δ): "<< DeclinationHours << "°" << DeclinationMinutes << "\'" << DeclinationSeconds << "\"";
                    std::string declinmsgstr = declinmsg.str();
                    std::cout << declinmsgstr << '\n';

                    // Local Hour Angle
                    int LocalHourAngleHours = int(LocalHourAngle);
                    int LocalHourAngleMinutes = int((LocalHourAngle - LocalHourAngleHours) * 60);
                    int LocalHourAngleSeconds = int((((LocalHourAngle - LocalHourAngleHours) * 60) - LocalHourAngleMinutes) * 60);

                    std::stringstream hourangmsg;
                    hourangmsg << "- Local Hour Angle (t): " << LocalHourAngleHours<< "h" << LocalHourAngleMinutes << "m" << LocalHourAngleSeconds << "s";
                    std::string hourangmsgstr = hourangmsg.str();                    
                    std::cout << hourangmsgstr << '\n';
                    
                    if(LocalSiderealTime != NULL)
                    {
                        // Right Ascension
                        int RightAscensionHours = int(RightAscension);
                        int RightAscensionMinutes = int((RightAscension - RightAscensionHours) * 60);
                        int RightAscensionSeconds = int((((RightAscension - RightAscensionHours) * 60) - RightAscensionMinutes) * 60);

                        std::stringstream RAmsg;
                        RAmsg << "- Right Ascension (α): " << RightAscensionHours << "h" << RightAscensionMinutes << "m" << RightAscensionSeconds << "s";
                        std::string RAmsgstr = RAmsg.str();
                        std::cout << RAmsgstr << '\n';
                    }

                    std::cout << '\n';
                }


                //  _____   
                // / __  \  
                // `' / /'  
                //   / /    
                // ./ /____ 
                // \_____(_)
                // 2. Horizontal to Equatorial II Coordinate System
                else if(CoordMode.compare("2") == 0)
                {
                    std::cout << ">> Conversion from Horizontal to Equatorial II Coordinate System\n";
                    std::cout << ">> Give Parameters!\n";
                    
                    std::cout << ">> Would you like to give Geographical Coordinates by yourself,\n>> or would like to choose a predefined Location's Coordinates?\n";
                    std::cout << ">> Write \'1\' for User defined Coordinates, and write \'2\' for Predefined Locations' Coordinates!\n";

                    std::string HorToEquIILocationChoose;
                    std::cout << "\n>> (1) User Defined, (2) Predefined: ";
                    std::cin >> HorToEquIILocationChoose;
                    std::cout << "\n\n";

                    double Latitude;
                    double LocalSiderealTime;
                    
                    while(1)
                    {
                        if(HorToEquIILocationChoose.compare("1") == 0)
                        {
                            std::cout << ">> User Defined Parameters\n";
                            std::cout << "\n>> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                            
                            double LatitudeHours;
                            double LatitudeMinutes;
                            double LatitudeSeconds;
                            
                            std::cout << "> Latitude (φ) Hours: ";
                            std::cin >> LatitudeHours;
                            std::cout << '\n';
                            std::cout << "> Latitude (φ) Minutes: ";
                            std::cin >> LatitudeMinutes;
                            std::cout << '\n';
                            std::cout << "> Latitude (φ) Seconds: ";
                            std::cin >> LatitudeSeconds;
                            std::cout << "\n\n";
                            Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600;
                            break;
                        }
                        
                        else if(HorToEquIILocationChoose.compare("2") == 0)
                        {
                            std::cout << ">> Predefined Parameters\n";
                            while(1)
                            {
                                std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                                std::string Location;
                                std::cout << "\n> Location's name (type \'H\' for Help): ";
                                std::cin >> Location;
                                std::cout << '\n';

                                if(Location.compare("Help") == 0 || Location.compare("help") == 0 || Location.compare("H") == 0 || Location.compare("h") == 0)
                                {
                                    std::cout << "\n>> Predefined Locations you can choose from:\n";

                                    for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                                    {
                                        std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << "\n";
                                    }

                                    std::cout << '\n';
                                }

                                else
                                {
                                    try
                                    {
                                        Latitude = LocationDict[Location][0];
                                    
                                        auto LocationSearch = LocationDict.find(Location);
                                        if(LocationSearch == LocationDict.end())
                                        {
                                            throw Location;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                    catch(std::string Location)
                                    {
                                        std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!\n";
                                        std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n\n";
                                    }
                                }
                            }
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                        }
                    }

                    double AltitudeHours;
                    double AltitudeMinutes;
                    double AltitudeSeconds;
                    double AzimuthHours;
                    double AzimuthMinutes;
                    double AzimuthSeconds;

                    std::cout << "\n\n>> HINT: You can write Altitude and Azimuth as a Decimal Fraction. For this you\n>> Need to write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";

                    std::cout << "\n> Altitude (m) Hours: ";
                    std::cin >> AltitudeHours;
                    std::cout << '\n';
                    std::cout << "> Altitude (m) Minutes: ";
                    std::cin >> AltitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Altitude (m) Seconds: ";
                    std::cin >> AltitudeSeconds;
                    std::cout << '\n';
                    double Altitude = AltitudeHours + AltitudeMinutes/60 + AltitudeSeconds/3600;

                    std::cout <<  "\n> Azimuth (A) Hours: ";
                    std::cin >> AzimuthHours;
                    std::cout << '\n';
                    std::cout <<  "> Azimuth (A) Minutes: ";
                    std::cin >> AzimuthMinutes;
                    std::cout << '\n';
                    std::cout <<  "> Azimuth (A) Seconds: ";
                    std::cin >> AzimuthSeconds;
                    std::cout << '\n';
                    double Azimuth = AzimuthHours + AzimuthMinutes/60 + AzimuthSeconds/3600;
                    
                    std::cout << "\n\n>> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LocalSiderealTimeHours;
                    double LocalSiderealTimeMinutes;
                    double LocalSiderealTimeSeconds;

                    std::cout << "\n> Local Mean Sidereal Time (S) Hours: ";
                    std::cin >> LocalSiderealTimeHours;
                    std::cout << '\n';
                    std::cout << "> Local Mean Sidereal Time (S) Minutes: ";
                    std::cin >> LocalSiderealTimeMinutes;
                    std::cout << '\n';
                    std::cout << "> Local Mean Sidereal Time (S) Seconds: ";
                    std::cin >> LocalSiderealTimeSeconds;
                    std::cout << '\n';
                    LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600;

                    std::vector<double> HorToEquIIoutputVec = HorToEquII(Latitude, Altitude, Azimuth, LocalSiderealTime);
                    double RightAscension = HorToEquIIoutputVec[0];
                    double Declination = HorToEquIIoutputVec[1];
                    LocalSiderealTime = HorToEquIIoutputVec[2];


                    // Print Results
                    std::cout << "\n> Calculated Parameters in Equatorial II Coord. Sys.:";

                    // Declination
                    int DeclinationHours = int(Declination);
                    int DeclinationMinutes = int((Declination - DeclinationHours) * 60);
                    int DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60);

                    std::stringstream declinmsg;
                    declinmsg << "- Declination (δ): " << DeclinationHours << "°" << DeclinationMinutes << "\'" << DeclinationSeconds << "\"";
                    std::string declinmsgstr = declinmsg.str();
                    std::cout << declinmsgstr << '\n';

                    // Right Ascension
                    int RightAscensionHours = int(RightAscension);
                    int RightAscensionMinutes = int((RightAscension - RightAscensionHours) * 60);
                    int RightAscensionSeconds = int((((RightAscension - RightAscensionHours) * 60) - RightAscensionMinutes) * 60);

                    std::stringstream RAmsg;
                    RAmsg << "- Right Ascension (α): " << RightAscensionHours << "h" << RightAscensionMinutes << "m" << RightAscensionSeconds << "s";
                    std::string RAmsgstr = RAmsg.str();
                    std::cout << RAmsgstr << '\n';

                    // Local Mean Sidereal Time
                    std::stringstream sidermsg;
                    sidermsg << "- Local Mean Sidereal Time (S): " << LocalSiderealTimeHours << "h" << LocalSiderealTimeMinutes << "m" << LocalSiderealTimeSeconds << "s";
                    std::string sidermsgstr = sidermsg.str();
                    std::cout << sidermsgstr << '\n';

                    std::cout << '\n';
                }

                //  _____  
                // |____ | 
                //     / / 
                //     \ \ 
                // .___/ / 
                // \____(_)
                // 3. Equatorial I to Horizontal Coordinate System
                else if(CoordMode.compare("3") == 0)
                {
                    std::cout << ">> Conversion from Equatorial I to Horizontal Coordinate System\n";
                    std::cout << ">> Give Parameters!\n";

                    double Latitude;
                    double Declination;
                    double RightAscension;
                    double Azimuth;
                    double Altitude;
                    double LocalHourAngle;
                    double LocalSiderealTime;
                    
                    while(1)
                    {
                        std::cout << "\n>>> LOCATION\n";
                        std::cout << ">> Would you like to give Geographical Coordinates by yourself,\n>> Or would like to choose a predefined Location's Coordinates?\n";
                        std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for Predefined Locations' Coordinates!\n";

                        std::string EquIToHorLocationChoose;
                        std::cout << ">> (1) User Defined, (2) Predefined: ";
                        std::cin >> EquIToHorLocationChoose;
                        std::cout << "\n\n";

                        if(EquIToHorLocationChoose.compare("1") == 0)
                        {
                            std::cout << ">> User Defined Parameters\n";
                            std::cout << "\n\n>> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                            
                            double LatitudeHours;
                            double LatitudeMinutes;
                            double LatitudeSeconds;
                            
                            std::cout << "\n> Latitude (φ) Hours: ";
                            std::cin >> LatitudeHours;
                            std::cout << '\n';
                            std::cout << "> Latitude (φ) Minutes: ";
                            std::cin >> LatitudeMinutes;
                            std::cout << '\n';
                            std::cout << "> Latitude (φ) Seconds: ";
                            std::cin >> LatitudeSeconds;
                            std::cout << '\n';
                            Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600;
                            break;
                        }

                        else if(EquIToHorLocationChoose.compare("2") == 0)
                        {
                            std::cout << ">> Predefined Parameters\n";
                            while(1)
                            {
                                std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                                std::string Location;
                                std::cout << "\n> Location's name (type \'H\' for Help): ";
                                std::cin >> Location;
                                std::cout << '\n';

                                if(Location.compare("Help") == 0 || Location.compare("help") == 0 || Location.compare("H") == 0 || Location.compare("h") == 0)
                                {
                                    std::cout << ">> Predefined Locations you can choose from:\n";

                                    for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                                    {
                                        std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << '\n';
                                    }

                                    std::cout << '\n';
                                }

                                else
                                {
                                    try
                                    {
                                        Latitude = LocationDict[Location][0];
                                    
                                        auto LocationSearch = LocationDict.find(Location);
                                        if(LocationSearch == LocationDict.end())
                                        {
                                            throw Location;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                    catch(std::string Location)
                                    {
                                        std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!\n";
                                        std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                                    }
                                }
                            }
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "\n>>> STELLAR OBJECT\n";
                        std::cout << ">> Would you like to give the stellar object's Coordinates by yourself,\n>> Or would like to choose a Predefined Object's Coordinates?\n";
                        std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for a Predefined Stellar Object's Coordinates!\n";

                        std::string EquIToHorStellarChoose;
                        std::cout << ">> (1) User Defined, (2) Predefined: ";
                        std::cin >> EquIToHorStellarChoose;
                        std::cout << "\n\n";
                        
                        if(EquIToHorStellarChoose.compare("1") == 0)
                        {
                            std::cout << ">> User Defined Parameters\n";
                            std::cout << ">> Which Parameter Is given?\n";
                            std::cout << ">> Declination is essential for calculation Horizontal Coordinates!\n>> Right Ascension only, isn't enough for calculating these parameters!\n";
                            
                            std::string RAorDecEquIToHorChoose;
                            std::cout << ">> Only Declination (write \'D\'), Or both of\n>> Right Ascension and Declination (write \'B\')?: ";
                            std::cin >> RAorDecEquIToHorChoose;
                            std::cout << '\n';

                            if(RAorDecEquIToHorChoose.compare("D") == 0 || RAorDecEquIToHorChoose.compare("d") == 0)
                            {
                                RightAscension = NULL;

                                std::cout << "\n\n>> HINT: You can write RA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";

                                double DeclinationHours;
                                double DeclinationMinutes;
                                double DeclinationSeconds;
                                
                                std::cout << "\n> Declination (δ) Hours: ";
                                std::cin >> DeclinationHours;
                                std::cout << '\n';
                                std::cout << "> Declination (δ) Minutes: ";
                                std::cin >> DeclinationMinutes;
                                std::cout << '\n';
                                std::cout << "> Declination (δ) Seconds: ";
                                std::cin >> DeclinationSeconds;
                                std::cout << '\n';
                                Declination = DeclinationHours + DeclinationMinutes/60 + DeclinationSeconds/3600;
                                break;
                            }

                            else if(RAorDecEquIToHorChoose.compare("B") == 0 || RAorDecEquIToHorChoose.compare("b") == 0)
                            {
                                std::cout << "\n>> HINT: You can write RA and Declination as a Decimal Fraction.\n>> For this you need to write Hours as a float-type value, then\n>> You can Press Enter for both Minutes and Seconds.\n";

                                double DeclinationHours;
                                double DeclinationMinutes;
                                double DeclinationSeconds;
                                double RightAscensionHours;
                                double RightAscensionMinutes;
                                double RightAscensionSeconds;

                                std::cout << "\n> Right Ascension (α) Hours: ";
                                std::cin >> RightAscensionHours;
                                std::cout << '\n';
                                std::cout << "> Right Ascension (α) Minutes: ";
                                std::cin >> RightAscensionMinutes;
                                std::cout << '\n';
                                std::cout << "> Right Ascension (α) Seconds: ";
                                std::cin >> RightAscensionSeconds;
                                std::cout << '\n';
                                RightAscension = RightAscensionHours + RightAscensionMinutes/60 + RightAscensionSeconds/3600;

                                std::cout << "\n> Declination (δ) Hours: ";
                                std::cin >> DeclinationHours;
                                std::cout << '\n';
                                std::cout << "> Declination (δ) Minutes: ";
                                std::cin >> DeclinationMinutes;
                                std::cout << '\n';
                                std::cout << "> Declination (δ) Seconds: ";
                                std::cin >> DeclinationSeconds;
                                std::cout << '\n';
                                Declination = DeclinationHours + DeclinationMinutes/60 + DeclinationSeconds/3600;
                                break;
                            }

                            else
                            {
                                std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'D\' or \'B\'!\n";
                            }
                        }

                        else if(EquIToHorStellarChoose.compare("2") == 0)
                        {
                            while(1)
                            {
                                std::map<std::string, std::vector<double>> StellarDict = StellarDictFunc();

                                std::string StellarObject;
                                std::cout << "> Stellar object's name (type \'H\' for Help): ";
                                std::cin >> StellarObject;
                                std::cout << '\n';

                                if(StellarObject.compare("Help") == 0 || StellarObject.compare("help") == 0 || StellarObject.compare("H") == 0 || StellarObject.compare("h") == 0)
                                {
                                    std::cout << ">> Predefined Objects you can choose from: \n";

                                    for(auto Objects = StellarDict.cbegin(); Objects != StellarDict.cend(); ++Objects)
                                    {
                                        std::cout << Objects->first << ": " << Objects->second[0] << "h ; " << Objects->second[1] << "°" << "\n";
                                    }

                                    std::cout << '\n';
                                }

                                else
                                {
                                    try
                                    {
                                        double TestVariable = StellarDict[StellarObject][0];
                                    
                                        if(StellarDict.find(StellarObject) != StellarDict.end())
                                        {
                                            throw StellarObject;
                                        }
                                        else
                                        {
                                            std::cout << ">> Which Parameter Is given?\n";
                                            std::cout << ">> Declination is essential for calculation Horizontal Coordinates!\n>> Right Ascension only, isn't enough for calculating these parameters!\n";
                                            
                                            std::string RAorDecEquIToHorChoose;
                                            std::cout << ">> Only Declination (write \'D\'), Or both of\n>> Right Ascension and Declination (write \'B\')?: ";
                                            std::cin >> RAorDecEquIToHorChoose;
                                            std::cout << '\n';

                                            if(RAorDecEquIToHorChoose.compare("D") == 0 || RAorDecEquIToHorChoose.compare("d") == 0)
                                            {
                                            
                                                RightAscension = NULL;
                                                Declination = StellarDict[StellarObject][1];
                                                break;
                                            }

                                            else if(RAorDecEquIToHorChoose.compare("B") == 0 || RAorDecEquIToHorChoose.compare("b") == 0)
                                            {
                                                RightAscension = StellarDict[StellarObject][0];
                                                Declination = StellarDict[StellarObject][1];
                                                break;
                                            }

                                            else
                                            {
                                                std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'D\' or \'B\'!\n";
                                            }
                                        }
                                    }
                                    catch(std::string StellarObject)
                                    {
                                        std::cout << ">>>> ERROR: The Stellar Object, named \"" + StellarObject + "\" is not in the Database!\n";
                                        std::cout << ">>>> Type \"Help\" to list Available Stellar Objects in Database!\n";
                                    }
                                }
                            }

                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                        }
                    }

                    if(RightAscension != NULL && Declination != NULL)
                    {
                        while(1)
                        {
                            std::cout << "\n>> Is Local Mean Sidereal Time (S) given?\n";

                            std::string EquIToHorChoose1;
                            std::cout << ">> Write \'Y\' or \'N\' (Yes or No): ";
                            std::cin >> EquIToHorChoose1;
                            std::cout << '\n';

                            if(EquIToHorChoose1.compare("Y") == 0 || EquIToHorChoose1.compare("y") == 0 || EquIToHorChoose1.compare("Yes") == 0 || EquIToHorChoose1.compare("yes") == 0 || EquIToHorChoose1.compare("YEs") == 0 || EquIToHorChoose1.compare("yEs") == 0 || EquIToHorChoose1.compare("yeS") == 0 || EquIToHorChoose1.compare("YeS") == 0 || EquIToHorChoose1.compare("yES") == 0)
                            {
                                std::cout << "\n\n>> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.";

                                double LocalSiderealTimeHours;
                                double LocalSiderealTimeMinutes;
                                double LocalSiderealTimeSeconds;

                                std::cout << "\n> Local Mean Sidereal Time (S) Hours: ";
                                std::cin >> LocalSiderealTimeHours;
                                std::cout << '\n';
                                std::cout << "> Local Mean Sidereal Time (S) Minutes: ";
                                std::cin >> LocalSiderealTimeMinutes;
                                std::cout << '\n';
                                std::cout << "> Local Mean Sidereal Time (S) Seconds: ";
                                std::cin >> LocalSiderealTimeSeconds;
                                std::cout << '\n';
                                LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600;

                                Altitude = NULL;
                                break;
                            }

                            else if(EquIToHorChoose1.compare("N") == 0 || EquIToHorChoose1.compare("n") == 0 || EquIToHorChoose1.compare("No") == 0 || EquIToHorChoose1.compare("no") == 0 || EquIToHorChoose1.compare("nO") == 0)
                            {
                                LocalSiderealTime = NULL;

                                std::cout << "\n>> Is Local Hour Angle given?";

                                std::string EquIToHorChoose2;
                                std::cout << ">> Write \'Y\' or \'N\' (Yes or No): ";
                                std::cin >> EquIToHorChoose2;
                                std::cout << '\n';

                                if(EquIToHorChoose2.compare("Y") == 0 || EquIToHorChoose2.compare("y") == 0 || EquIToHorChoose2.compare("Yes") == 0 || EquIToHorChoose2.compare("yes") == 0 || EquIToHorChoose2.compare("YEs") == 0 || EquIToHorChoose2.compare("yEs") == 0 || EquIToHorChoose2.compare("yeS") == 0 || EquIToHorChoose2.compare("YeS") == 0 || EquIToHorChoose2.compare("yES") == 0)
                                {
                                    std::cout << "\n>> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.";
                                    
                                    double LocalHourAngleHours;
                                    double LocalHourAngleMinutes;
                                    double LocalHourAngleSeconds;

                                    std::cout << "\n> Local Hour Angle (t) Hours: ";
                                    std::cin >> LocalHourAngleHours;
                                    std::cout << '\n';
                                    std::cout << "> Local Hour Angle (t) Minutes: ";
                                    std::cin >> LocalHourAngleMinutes;
                                    std::cout << '\n';
                                    std::cout << "> Local Hour Angle (t) Seconds: ";
                                    std::cin >> LocalHourAngleSeconds;
                                    std::cout << '\n';
                                    LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600;

                                    Altitude = NULL;
                                    break;
                                }

                                else if(EquIToHorChoose2.compare("N") == 0 || EquIToHorChoose2.compare("n") == 0 || EquIToHorChoose2.compare("No") == 0 || EquIToHorChoose2.compare("no") == 0 || EquIToHorChoose2.compare("nO") == 0)
                                {
                                    LocalHourAngle = NULL;
                                    std::cout << "\n>> From the given data, you can calculate Azimuth (A),\n>> If Altitude (m) is given.";

                                    double AltitudeHours;
                                    double AltitudeMinutes;
                                    double AltitudeSeconds;

                                    std::cout << "\n> Altitude (m) Hours: ";
                                    std::cin >> AltitudeHours;
                                    std::cout << '\n';
                                    std::cout << "> Altitude (m) Minutes: ";
                                    std::cin >> AltitudeMinutes;
                                    std::cout << '\n';
                                    std::cout << "> Altitude (m) Seconds: ";
                                    std::cin >> AltitudeSeconds;
                                    std::cout << '\n';
                                    Altitude = AltitudeHours + AltitudeMinutes/60 + AltitudeSeconds/3600;

                                    Azimuth = NULL;

                                    break;
                                }
                            }
                        }
                    }

                    else if(Declination != NULL && RightAscension == NULL)
                    {
                        while(1)
                        {
                            std::cout << "\n>> Is Local Hour Angle (t) given?";

                            std::string EquIToHorChooseD;
                            std::cout << ">> Write \'Y\' or \'N\' (Yes or No): ";
                            std::cin >> EquIToHorChooseD;
                            std::cout << '\n';

                            if(EquIToHorChooseD.compare("Y") == 0 || EquIToHorChooseD.compare("y") == 0 || EquIToHorChooseD.compare("Yes") == 0 || EquIToHorChooseD.compare("yes") == 0 || EquIToHorChooseD.compare("YEs") == 0 || EquIToHorChooseD.compare("yEs") == 0 || EquIToHorChooseD.compare("yeS") == 0 || EquIToHorChooseD.compare("YeS") == 0 || EquIToHorChooseD.compare("yES") == 0)
                            {
                                std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.";

                                double LocalHourAngleHours;
                                double LocalHourAngleMinutes;
                                double LocalHourAngleSeconds;

                                std::cout << "\n> Local Hour Angle (t) Hours: ";
                                std::cin >> LocalHourAngleHours;
                                std::cout << '\n';
                                std::cout << "> Local Hour Angle (t) Minutes: ";
                                std::cin >> LocalHourAngleMinutes;
                                std::cout << '\n';
                                std::cout << "> Local Hour Angle (t) Seconds: ";
                                std::cin >> LocalHourAngleSeconds;
                                std::cout << '\n';
                                LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600;
                                break;
                            }

                            else if(EquIToHorChooseD.compare("N") == 0 || EquIToHorChooseD.compare("n") == 0 || EquIToHorChooseD.compare("No") == 0 || EquIToHorChooseD.compare("no") == 0 || EquIToHorChooseD.compare("nO") == 0)
                            {
                                LocalHourAngle = NULL;
                                std::cout << "\n>> From the given data, you can calculate Azimuth (A),\n>> If Altitude (m) is given.";
                                std::cout << ">> HINT: You can write Altitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.";

                                double AltitudeHours;
                                double AltitudeMinutes;
                                double AltitudeSeconds;

                                std::cout << "\n> Altitude (m) Hours: ";
                                std::cin >> AltitudeHours;
                                std::cout << '\n';
                                std::cout << "> Altitude (m) Minutes: ";
                                std::cin >> AltitudeMinutes;
                                std::cout << '\n';
                                std::cout << "> Altitude (m) Seconds: ";
                                std::cin >> AltitudeSeconds;
                                std::cout << '\n';
                                Altitude = AltitudeHours + AltitudeMinutes/60 + AltitudeSeconds/3600;

                                Azimuth = NULL;

                                break;
                            }

                            else
                            {
                                std::cout << ">>>> ERROR: Invalid option! Try Again!";
                            }
                        }
                    }

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
                    if(LocalSiderealTime != NULL || LocalHourAngle != NULL)
                    {                        
                        std::vector<double> EquIToHoroutputVec = EquIToHor(Latitude, RightAscension, Declination, Altitude, LocalSiderealTime, LocalHourAngle);
                        Altitude = EquIToHoroutputVec[0];
                        Azimuth = EquIToHoroutputVec[1];

                        // Print Results
                        std::cout << "\n> Calculated Parameters in Horizontal Coord. Sys.:\n";

                        std::stringstream altitmsg;
                        altitmsg << "- Altitude (m): "<< Altitude << "°";
                        std::string altitmsgstr = altitmsg.str();
                        std::cout << altitmsgstr << '\n';

                        std::stringstream azimmsg;
                        azimmsg << "- Azimuth (A): "<< Azimuth << "°";
                        std::string azimmsgstr = azimmsg.str();
                        std::cout << azimmsgstr << '\n';
                    }

                    // Used formulas:
                    // cos(H) = (sin(m) - sin(δ) * sin(φ)) / cos(δ) * cos(φ)
                    // sin(A) = - sin(H) * cos(δ) / cos(m)
                    else if(Altitude != NULL)
                    {
                        double Azimuth1;
                        double Azimuth2;
                        double H_dil;
                        
                        std::vector<double> EquIToHoroutputVec = EquIToHor(Latitude, RightAscension, Declination, Altitude, LocalSiderealTime, LocalHourAngle);

                        Altitude = EquIToHoroutputVec[0];
                        Azimuth1 = EquIToHoroutputVec[1];
                        Azimuth2 = EquIToHoroutputVec[2];
                        H_dil = EquIToHoroutputVec[3];

                        // Print Results
                        std::cout << ">> Available Data are only suited for Calculating Rising/Setting Altitudes!\n";
                        std::cout << "\n> Calculated Parameter of Rising/Setting Object in Horizontal Coord. Sys.:\n";

                        std::stringstream azimmsg;
                        azimmsg << "- Rising and Setting Azimuths (A) are: " << Azimuth1 << "° and " << Azimuth2 << "°";
                        std::string azimmsgstr = azimmsg.str();
                        std::cout << azimmsgstr << '\n';
                    }
                }

                //    ___   
                //   /   |  
                //  / /| |  
                // / /_| |  
                // \___  |_ 
                //     |_(_)
                // 4. Equatorial I to Equatorial II Coordinate System
                else if(CoordMode.compare("4") == 0)
                {
                    std::cout << ">> Conversion from Equatorial I to Equatorial II Coordinate System\n";
                    std::cout << ">> Give Parameters!\n";

                    std::cout << ">> Would you like to give the stellar object's Coordinates by yourself,\n>> Or would like to choose a Predefined Object's Coordinates?\n";
                    std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for a Predefined Stellar Object's Coordinates!\n";

                    std::string EquIToEquIIStellarChoose;
                    std::cout << "\n>> (1) User Defined, (2) Predefined: ";
                    std::cin >> EquIToEquIIStellarChoose;
                    std::cout << '\n';

                    double RightAscension;
                    double Declination;
                    double LocalHourAngle;
                    double LocalSiderealTime;

                    while(1)
                    {
                        if(EquIToEquIIStellarChoose.compare("1") == 0)
                        {
                            std::cout << ">> HINT: You can write RA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, and type 0\n>> For both Minutes and Seconds.";
                            double RightAscensionHours;
                            double RightAscensionMinutes;
                            double RightAscensionSeconds;

                            std::cout << "\n> Right Ascension (α) Hours: ";
                            std::cin >> RightAscensionHours;
                            std::cout << '\n';
                            std::cout << "> Right Ascension (α) Minutes: ";
                            std::cin >> RightAscensionMinutes;
                            std::cout << '\n';
                            std::cout << "> Right Ascension (α) Seconds: ";
                            std::cin >> RightAscensionSeconds;
                            std::cout << '\n';
                            RightAscension = RightAscensionHours + RightAscensionMinutes/60 + RightAscensionSeconds/3600;

                            while(1)
                            {
                                std::cout << ">> Is Declination given?\n";

                                std::string EquIToEquIIChoose;
                                std::cout << ">> Write \'Y\' or \'N\' (Yes or No): ";
                                std::cin >> EquIToEquIIChoose;
                                std::cout << '\n';
                                
                                if(EquIToEquIIChoose.compare("Y") == 0 || EquIToEquIIChoose.compare("y") == 0 || EquIToEquIIChoose.compare("Yes") == 0 || EquIToEquIIChoose.compare("yes") == 0 || EquIToEquIIChoose.compare("YEs") == 0 || EquIToEquIIChoose.compare("yEs") == 0 || EquIToEquIIChoose.compare("yeS") == 0 || EquIToEquIIChoose.compare("YeS") == 0 || EquIToEquIIChoose.compare("yES") == 0)
                                {
                                    std::cout << "\n>> HINT: You can write Declination as a Decimal Fraction.\n>> For this you need to write Hours as a float-type value, then\n>> You can Press Enter for both Minutes and Seconds.\n";

                                    double DeclinationHours;
                                    double DeclinationMinutes;
                                    double DeclinationSeconds;

                                    std::cout << "\n> Declination (δ) Hours: ";
                                    std::cin >> DeclinationHours;
                                    std::cout << '\n';
                                    std::cout << "> Declination (δ) Minutes: ";
                                    std::cin >> DeclinationMinutes;
                                    std::cout << '\n';
                                    std::cout << "> Declination (δ) Seconds: ";
                                    std::cin >> DeclinationSeconds;
                                    std::cout << '\n';
                                    Declination = DeclinationHours + DeclinationMinutes/60 + DeclinationSeconds/3600;
                                    break;
                                }
                                
                                else if(EquIToEquIIChoose.compare("N") == 0 || EquIToEquIIChoose.compare("n") == 0 || EquIToEquIIChoose.compare("No") == 0 || EquIToEquIIChoose.compare("no") == 0 || EquIToEquIIChoose.compare("nO") == 0)
                                {
                                    Declination = NULL;
                                }

                                else
                                {
                                    std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                                }
                            }
                        }

                        else if(EquIToEquIIStellarChoose.compare("2") == 0)
                        {
                            while(1)
                            {
                                std::map<std::string, std::vector<double>> StellarDict = StellarDictFunc();

                                std::string StellarObject;
                                std::cout << "> Stellar object's name (type \'H\' for Help): ";
                                std::cin >> StellarObject;
                                std::cout << '\n';

                                if(StellarObject.compare("Help") == 0 || StellarObject.compare("help") == 0 || StellarObject.compare("H") == 0 || StellarObject.compare("h") == 0)
                                {
                                    std::cout << ">> Predefined Objects you can choose from: \n";

                                    for(auto Objects = StellarDict.cbegin(); Objects != StellarDict.cend(); ++Objects)
                                    {
                                        std::cout << Objects->first << ": " << Objects->second[0] << "h ; " << Objects->second[1] << "°" << "\n";
                                    }

                                    std::cout << '\n';
                                }

                                else
                                {
                                    try
                                    {
                                        double TestVariable = StellarDict[StellarObject][0];
                                    
                                        if(StellarDict.find(StellarObject) != StellarDict.end())
                                        {
                                            throw StellarObject;
                                        }
                                        else
                                        {
                                            RightAscension = StellarDict[StellarObject][0];

                                            while(1)
                                            {
                                                std::cout << ">> Is Declination given?\n";

                                                std::string EquIToEquIIChoose;
                                                std::cout << ">> Write \'Y\' or \'N\' (Yes or No): ";
                                                std::cin >> EquIToEquIIChoose;
                                                std::cout << '\n';

                                                if(EquIToEquIIChoose.compare("Y") == 0 || EquIToEquIIChoose.compare("y") == 0 || EquIToEquIIChoose.compare("Yes") == 0 || EquIToEquIIChoose.compare("yes") == 0 || EquIToEquIIChoose.compare("YEs") == 0 || EquIToEquIIChoose.compare("yEs") == 0 || EquIToEquIIChoose.compare("yeS") == 0 || EquIToEquIIChoose.compare("YeS") == 0 || EquIToEquIIChoose.compare("yES") == 0)
                                                {
                                                    Declination = StellarDict[StellarObject][1];
                                                    break;
                                                }

                                                else if(EquIToEquIIChoose.compare("N") == 0 || EquIToEquIIChoose.compare("n") == 0 || EquIToEquIIChoose.compare("No") == 0 || EquIToEquIIChoose.compare("no") == 0 || EquIToEquIIChoose.compare("nO") == 0)
                                                {
                                                    Declination = NULL;
                                                }

                                                else
                                                {
                                                    std::cout << ">>>> ERROR: Invalid option! Try Again!";
                                                }
                                            }
                                        }
                                    }
                                    catch(std::string StellarObject)
                                    {
                                        std::cout << ">>>> ERROR: The Stellar Object, named \"" + StellarObject + "\" is not in the Database!\n";
                                        std::cout << ">>>> Type \"Help\" to list Available Stellar Objects in Database!\n";
                                    }
                                }
                            }
                            break;
                        }


                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                        }
                    }


                    std::cout << ">> You should input LHA (t) manually!\n";
                    std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";

                    double LocalHourAngleHours;
                    double LocalHourAngleMinutes;
                    double LocalHourAngleSeconds;

                    std::cout << "\n> Local Hour Angle (t) Hours: ";
                    std::cin >> LocalHourAngleHours;
                    std::cout << '\n';
                    std::cout << "> Local Hour Angle (t) Minutes: ";
                    std::cin >> LocalHourAngleMinutes;
                    std::cout << '\n';
                    std::cout << "> Local Hour Angle (t) Seconds: ";
                    std::cin >> LocalHourAngleSeconds;
                    std::cout << '\n';
                    LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600;

                    LocalSiderealTime = EquIToEquII(RightAscension, LocalHourAngle);

                    // Print Results
                    std::cout << "\n> Calculated Parameters in Equatorial II Coord. Sys.:\n";

                    // Local Mean Sidereal Time
                    int LocalSiderealTimeHours = int(LocalSiderealTime);
                    int LocalSiderealTimeMinutes = int((LocalSiderealTime - LocalSiderealTimeHours) * 60);
                    int LocalSiderealTimeSeconds = int((((LocalSiderealTime - LocalSiderealTimeHours) * 60) - LocalSiderealTimeMinutes) * 60);

                    std::stringstream sidermsg;
                    sidermsg << "- Local Mean Sidereal Time (S): "  << LocalSiderealTimeHours << "°" << LocalSiderealTimeMinutes << "\'" << LocalSiderealTimeSeconds << "\"";
                    std::string sidermsgstr = sidermsg.str();
                    std::cout << sidermsgstr << '\n';
                    
                    // Declination
                    if(Declination != NULL)
                    {
                        int DeclinationHours = int(Declination);
                        int DeclinationMinutes = int((Declination - DeclinationHours) * 60);
                        int DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60);

                        std::stringstream declinmsg;
                        declinmsg << "- Declination (δ): "  << DeclinationHours << "°" << DeclinationMinutes << "\'" << DeclinationSeconds << "\"";
                        std::string declinmsgstr = declinmsg.str();
                        std::cout << declinmsgstr << '\n';
                    }

                    else
                    {
                        std::cout << "- Declination is Unknown!\n";
                    }
                    std::cout << '\n';

                }


                //  _____  
                // |  ___| 
                // |___ \  
                //     \ \ 
                // /\__/ / 
                // \____(_)
                // 5. Equatorial II to Equatorial I Coordinate System
                else if(CoordMode.compare("5") == 0)
                {
                    std::cout << ">> Conversion from Equatorial II to Equatorial I Coordinate System\n";
                    std::cout << ">> Give Parameters!\n\n";

                    double RightAscension;
                    double Declination;
                    double LocalHourAngle;

                    std::cout << ">> You should input LMST (S) manually!\n";
                    std::cout << ">> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    
                    double LocalSiderealTime;
                    double LocalSiderealTimeHours;
                    double LocalSiderealTimeMinutes;
                    double LocalSiderealTimeSeconds;

                    std::cout << "\n> Local Mean Sidereal Time (S) Hours: ";
                    std::cin >> LocalSiderealTimeHours;
                    std::cout << '\n';
                    std::cout << "> Local Mean Sidereal Time (S) Minutes: ";
                    std::cin >> LocalSiderealTimeMinutes;
                    std::cout << '\n';
                    std::cout << "> Local Mean Sidereal Time (S) Seconds: ";
                    std::cin >> LocalSiderealTimeSeconds;
                    std::cout << '\n';
                    LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600;

                    while(1)
                    {
                        std::cout << ">> Is Declination given?\n";

                        std::string EquIIToEquIChoose;
                        std::cout << ">> Write \'Y\' or \'N\' (Yes or No): ";
                        std::cin >> EquIIToEquIChoose;
                        std::cout << '\n';
                        
                        if(EquIIToEquIChoose.compare("Y") == 0 || EquIIToEquIChoose.compare("y") == 0 || EquIIToEquIChoose.compare("Yes") == 0 || EquIIToEquIChoose.compare("yes") == 0 || EquIIToEquIChoose.compare("YEs") == 0 || EquIIToEquIChoose.compare("yEs") == 0 || EquIIToEquIChoose.compare("yeS") == 0 || EquIIToEquIChoose.compare("YeS") == 0 || EquIIToEquIChoose.compare("yES") == 0)
                        {
                            std::cout << "\n>> HINT: You can write Declination as a Decimal Fraction.\n>> For this you need to write Hours as a float-type value, then\n>> You can Press Enter for both Minutes and Seconds.\n";

                            double DeclinationHours;
                            double DeclinationMinutes;
                            double DeclinationSeconds;

                            std::cout << "\n> Declination (δ) Hours: ";
                            std::cin >> DeclinationHours;
                            std::cout << '\n';
                            std::cout << "> Declination (δ) Minutes: ";
                            std::cin >> DeclinationMinutes;
                            std::cout << '\n';
                            std::cout << "> Declination (δ) Seconds: ";
                            std::cin >> DeclinationSeconds;
                            std::cout << '\n';
                            Declination = DeclinationHours + DeclinationMinutes/60 + DeclinationSeconds/3600;
                            break;
                        }

                        else if(EquIIToEquIChoose.compare("N") == 0 || EquIIToEquIChoose.compare("n") == 0 || EquIIToEquIChoose.compare("No") == 0 || EquIIToEquIChoose.compare("no") == 0 || EquIIToEquIChoose.compare("nO") == 0)
                        {
                            Declination = NULL;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << ">> Which essential Parameter Is given?\n";

                        std::string EquIIToEquIDecChoose;
                        std::cout << ">> Right Ascension (write \'A\'), or Local Hour Angle in Hours (write \'T\')?: ";
                        std::cin >> EquIIToEquIDecChoose;
                        std::cout << '\n';

                        if(EquIIToEquIDecChoose.compare("A") == 0 || EquIIToEquIDecChoose.compare("a") == 0)
                        {
                            std::cout << ">> HINT: You can write RA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, and type 0\n>> For both Minutes and Seconds.\n";
                            double RightAscensionHours;
                            double RightAscensionMinutes;
                            double RightAscensionSeconds;

                            std::cout << "\n> Right Ascension (α) Hours: ";
                            std::cin >> RightAscensionHours;
                            std::cout << '\n';
                            std::cout << "> Right Ascension (α) Minutes: ";
                            std::cin >> RightAscensionMinutes;
                            std::cout << '\n';
                            std::cout << "> Right Ascension (α) Seconds: ";
                            std::cin >> RightAscensionSeconds;
                            std::cout << '\n';
                            RightAscension = RightAscensionHours + RightAscensionMinutes/60 + RightAscensionSeconds/3600;

                            LocalHourAngle = NULL;
                            break;
                        }

                        else if(EquIIToEquIDecChoose.compare("T") == 0 || EquIIToEquIDecChoose.compare("t") == 0)
                        {
                            RightAscension = NULL;

                            std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                            double LocalHourAngleHours;
                            double LocalHourAngleMinutes;
                            double LocalHourAngleSeconds;

                            std::cout << "\n> Local Hour Angle (t) Hours: ";
                            std::cin >> LocalHourAngleHours;
                            std::cout << '\n';
                            std::cout << "> Local Hour Angle (t) Minutes: ";
                            std::cin >> LocalHourAngleMinutes;
                            std::cout << '\n';
                            std::cout << "> Local Hour Angle (t) Seconds: ";
                            std::cin >> LocalHourAngleSeconds;
                            std::cout << '\n';
                            LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600;
                            
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'A\' or \'T\'!\n";
                        }
                    }

                    std::vector<double> EquIIToEquIoutputVec = EquIIToEquI(LocalSiderealTime, RightAscension, LocalHourAngle);
                    RightAscension = EquIIToEquIoutputVec[0];
                    LocalHourAngle  = EquIIToEquIoutputVec[1];

                    // Print Results
                    std::cout << "\n> Calculated parameters in Equatorial I Coord. Sys.:\n";

                    // Right Ascension
                    int RightAscensionHours = int(RightAscension);
                    int RightAscensionMinutes = int((RightAscension - RightAscensionHours) * 60);
                    int RightAscensionSeconds = int((((RightAscension - RightAscensionHours) * 60) - RightAscensionMinutes) * 60);

                    std::stringstream RAmsg;
                    RAmsg << "- Right Ascension (α): " << RightAscensionHours << "h" << RightAscensionMinutes << "m" << RightAscensionSeconds << "s";
                    std::string RAmsgstr = RAmsg.str();
                    std::cout << RAmsgstr << '\n';

                    // Declination
                    if(Declination != NULL)
                    {
                        int DeclinationHours = int(Declination);
                        int DeclinationMinutes = int((Declination - DeclinationHours) * 60);
                        int DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60);

                        std::stringstream declinmsg;
                        declinmsg << "- Declination (δ): "  << DeclinationHours << "°" << DeclinationMinutes << "\'" << DeclinationSeconds << "\"";
                        std::string declinmsgstr = declinmsg.str();
                        std::cout << declinmsgstr << '\n';
                    }

                    else
                    {
                        std::cout << "Declination is Unknown!\n";
                    }
                    std::cout << '\n';

                    // Local Hour Angle
                    int LocalHourAngleHours = int(LocalHourAngle);
                    int LocalHourAngleMinutes = int((LocalHourAngle - LocalHourAngleHours) * 60);
                    int LocalHourAngleSeconds = int((((LocalHourAngle - LocalHourAngleHours) * 60) - LocalHourAngleMinutes) * 60);

                    std::stringstream hourangmsg;
                    hourangmsg << "- Local Hour Angle (t): " << LocalHourAngleHours<< "h" << LocalHourAngleMinutes << "m" << LocalHourAngleSeconds << "s";
                    std::string hourangmsgstr = hourangmsg.str();                    
                    std::cout << hourangmsgstr << "\n\n";
                }

                //   ____   
                //  / ___|  
                // / /___   
                // | ___ \  
                // | \_/ |_ 
                // \_____(_)
                // 6. Equatorial II to Horizontal Coordinate System
                else if(CoordMode.compare("6") == 0)
                {
                    std::cout << ">> Conversion from Equatorial II to Horizontal Coordinate System\n";
                    std::cout << ">> Give Parameters!";

                    double Latitude;
                    double Altitude;
                    double Azimuth;
                    double RightAscension;
                    double Declination;
                    double LocalHourAngle;
                    double LocalSiderealTime;

                    while(1)
                    {
                        std::cout << "\n>>> LOCATION\n";
                        std::cout << ">> Would you like to give Geographical Coordinates by yourself,\n>> Or would like to choose a predefined Location's Coordinates?\n";
                        std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for Predefined Locations' Coordinates!\n";

                        std::string EquIIToHorLocationChoose;
                        std::cout << ">> (1) User Defined, (2) Predefined: ";
                        std::cin >> EquIIToHorLocationChoose;
                        std::cout << '\n';

                        if(EquIIToHorLocationChoose.compare("1") == 0)
                        {
                            std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                            double LatitudeHours;
                            double LatitudeMinutes;
                            double LatitudeSeconds;
                            
                            std::cout << "\n> Latitude (φ) Hours: ";
                            std::cin >> LatitudeHours;
                            std::cout << '\n';
                            std::cout << "> Latitude (φ) Minutes: ";
                            std::cin >> LatitudeMinutes;
                            std::cout << '\n';
                            std::cout << "> Latitude (φ) Seconds: ";
                            std::cin >> LatitudeSeconds;
                            std::cout << '\n';
                            Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600;
                            break;
                        }

                        else if(EquIIToHorLocationChoose.compare("2") == 0)
                        {
                            std::cout << ">> Predefined Parameters\n";
                            while(1)
                            {
                                std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                                std::string Location;
                                std::cout << "\n> Location's name (type \'H\' for Help): ";
                                std::cin >> Location;
                                std::cout << '\n';

                                if(Location.compare("Help") == 0 || Location.compare("help") == 0 || Location.compare("H") == 0 || Location.compare("h") == 0)
                                {
                                    std::cout << ">> Predefined Locations you can choose from:\n";

                                    for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                                    {
                                        std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << '\n';
                                    }

                                    std::cout << '\n';
                                }

                                else
                                {
                                    try
                                    {
                                        Latitude = LocationDict[Location][0];
                                    
                                        auto LocationSearch = LocationDict.find(Location);
                                        if(LocationSearch == LocationDict.end())
                                        {
                                            throw Location;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                    catch(std::string Location)
                                    {
                                        std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!\n";
                                        std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                                    }
                                }
                            }
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "\n>>> STELLAR OBJECT\n";
                        std::cout << ">> Would you like to give the stellar object's Coordinates by yourself,\n>> Or would like to choose a Predefined Object's Coordinates?\n";
                        std::cout << ">> Write \'1\' for User defined Coordinates, and\n>> Write \'2\' for a Predefined Stellar Object's Coordinates!\n";

                        std::string EquIIToHorStellarChoose;
                        std::cout << ">> (1) User Defined, (2) Predefined: ";
                        std::cin >> EquIIToHorStellarChoose;
                        std::cout << '\n';

                        if(EquIIToHorStellarChoose.compare("1") == 0)
                        {
                            std::cout << ">> User Defined Parameters";
                            std::cout << ">> Which essential Parameter Is given?";

                            std::string EquIIToEquIDecChoose;
                            std::cout << ">> Right Ascension (write \'A\'), or Local Hour Angle in Hours (write \'T\')?: ";
                            std::cin >> EquIIToEquIDecChoose;
                            std::cout << '\n';

                            if(EquIIToEquIDecChoose.compare("A") == 0 || EquIIToEquIDecChoose.compare("a") == 0)
                            {
                                std::cout << ">> HINT: You can write RA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                                double RightAscensionHours;
                                double RightAscensionMinutes;
                                double RightAscensionSeconds;

                                std::cout << "\n> Right Ascension (α) Hours: ";
                                std::cin >> RightAscensionHours;
                                std::cout << '\n';
                                std::cout << "> Right Ascension (α) Minutes: ";
                                std::cin >> RightAscensionMinutes;
                                std::cout << '\n';
                                std::cout << "> Right Ascension (α) Seconds: ";
                                std::cin >> RightAscensionSeconds;
                                std::cout << '\n';
                                RightAscension = RightAscensionHours + RightAscensionMinutes/60 + RightAscensionSeconds/3600;

                                LocalHourAngle = NULL;
                                break;
                            }

                            else if(EquIIToEquIDecChoose.compare("T") == 0 || EquIIToEquIDecChoose.compare("t") == 0)
                            {
                                RightAscension = NULL;

                                std::cout << ">> HINT: You can write LHA as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                                double LocalHourAngleHours;
                                double LocalHourAngleMinutes;
                                double LocalHourAngleSeconds;

                                std::cout << "\n> Local Hour Angle (t) Hours: ";
                                std::cin >> LocalHourAngleHours;
                                std::cout << '\n';
                                std::cout << "> Local Hour Angle (t) Minutes: ";
                                std::cin >> LocalHourAngleMinutes;
                                std::cout << '\n';
                                std::cout << "> Local Hour Angle (t) Seconds: ";
                                std::cin >> LocalHourAngleSeconds;
                                std::cout << '\n';
                                LocalHourAngle = LocalHourAngleHours + LocalHourAngleMinutes/60 + LocalHourAngleSeconds/3600;
                                break;
                            }

                            else
                            {
                                std::cout << ">>>> ERROR: Invalid option! Try Again! Write \'A\' or \'T\'!";
                            }
                        }

                        else if(EquIIToHorStellarChoose.compare("2") == 0)
                        {
                            while(1)
                            {
                                std::cout << ">> Predefined Parameters";
                                std::map<std::string, std::vector<double>> StellarDict = StellarDictFunc();

                                std::string StellarObject;
                                std::cout << "> Stellar object's name (type \'H\' for Help): ";
                                std::cin >> StellarObject;
                                std::cout << '\n';

                                if(StellarObject.compare("Help") == 0 || StellarObject.compare("help") == 0 || StellarObject.compare("H") == 0 || StellarObject.compare("h") == 0)
                                {
                                    std::cout << ">> Predefined Objects you can choose from: \n";

                                    for(auto Objects = StellarDict.cbegin(); Objects != StellarDict.cend(); ++Objects)
                                    {
                                        std::cout << Objects->first << ": " << Objects->second[0] << "h ; " << Objects->second[1] << "°" << "\n";
                                    }

                                    std::cout << '\n';
                                }

                                else
                                {
                                    try
                                    {
                                        double TestVariable = StellarDict[StellarObject][0];
                                    
                                        if(StellarDict.find(StellarObject) != StellarDict.end())
                                        {
                                            throw StellarObject;
                                        }
                                        else
                                        {
                                            RightAscension = StellarDict[StellarObject][0];

                                            while(1)
                                            {
                                                std::cout << ">> Is Declination given?\n";

                                                std::string EquIToEquIIChoose;
                                                std::cout << ">> Write \'Y\' or \'N\' (Yes or No): ";
                                                std::cin >> EquIToEquIIChoose;
                                                std::cout << '\n';

                                                if(EquIToEquIIChoose.compare("Y") == 0 || EquIToEquIIChoose.compare("y") == 0 || EquIToEquIIChoose.compare("Yes") == 0 || EquIToEquIIChoose.compare("yes") == 0 || EquIToEquIIChoose.compare("YEs") == 0 || EquIToEquIIChoose.compare("yEs") == 0 || EquIToEquIIChoose.compare("yeS") == 0 || EquIToEquIIChoose.compare("YeS") == 0 || EquIToEquIIChoose.compare("yES") == 0)
                                                {
                                                    Declination = StellarDict[StellarObject][1];
                                                    break;
                                                }

                                                else if(EquIToEquIIChoose.compare("N") == 0 || EquIToEquIIChoose.compare("n") == 0 || EquIToEquIIChoose.compare("No") == 0 || EquIToEquIIChoose.compare("no") == 0 || EquIToEquIIChoose.compare("nO") == 0)
                                                {
                                                    Declination = NULL;
                                                }

                                                else
                                                {
                                                    std::cout << ">>>> ERROR: Invalid option! Try Again!";
                                                }
                                            }
                                        }
                                    }
                                    catch(std::string StellarObject)
                                    {
                                        std::cout << ">>>> ERROR: The Stellar Object, named \"" + StellarObject + "\" is not in the Database!\n";
                                        std::cout << ">>>> Type \"Help\" to list Available Stellar Objects in Database!\n";
                                    }
                                }
                            }
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!";
                        }
                    }

                    std::cout << ">> You should input LMST (S) manually!";
                    std::cout << ">> HINT: You can write LMST as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LocalSiderealTimeHours;
                    double LocalSiderealTimeMinutes;
                    double LocalSiderealTimeSeconds;

                    std::cout << "\n> Local Mean Sidereal Time (S) Hours: ";
                    std::cin >> LocalSiderealTimeHours;
                    std::cout << '\n';
                    std::cout << "> Local Mean Sidereal Time (S) Minutes: ";
                    std::cin >> LocalSiderealTimeMinutes;
                    std::cout << '\n';
                    std::cout << "> Local Mean Sidereal Time (S) Seconds: ";
                    std::cin >> LocalSiderealTimeSeconds;
                    std::cout << '\n';
                    LocalSiderealTime = LocalSiderealTimeHours + LocalSiderealTimeMinutes/60 + LocalSiderealTimeSeconds/3600;

                    std::vector<double> EquIIToHoroutputVec = EquIIToHor(Latitude, RightAscension, Declination, Altitude, Azimuth, LocalSiderealTime, LocalHourAngle);
                    Altitude = EquIIToHoroutputVec[0];
                    Azimuth = EquIIToHoroutputVec[1];

                    // Print Results
                    std::cout << "\n> Calculated Parameters in Horizontal Coord. Sys.:\n";

                    // Altitude
                    int AltitudeHours = int(Altitude);
                    int AltitudeMinutes = int((Altitude - AltitudeHours) * 60);
                    int AltitudeSeconds = int((((Altitude - AltitudeHours) * 60) - AltitudeMinutes) * 60);

                    std::stringstream altitmsg;
                    altitmsg << "- Altitude (m): "<< AltitudeHours << "° " << AltitudeMinutes << "\' " << AltitudeSeconds << "\"";
                    std::string altitmsgstr = altitmsg.str();
                    std::cout << altitmsgstr << '\n';

                    // Azimuth
                    int AzimuthHours = int(Azimuth);
                    int AzimuthMinutes = int((Azimuth - AzimuthHours) * 60);
                    int AzimuthSeconds = int((((Azimuth - AzimuthHours) * 60) - AzimuthMinutes) * 60);

                    std::stringstream azimmsg;
                    azimmsg << "- Azimuth (A): "<< AzimuthHours << "° " << AzimuthMinutes << "\' " << AzimuthSeconds << "\"";
                    std::string azimmsgstr = azimmsg.str();
                    std::cout << azimmsgstr << '\n';

                }

                else if(CoordMode.compare("Q") == 0 || CoordMode.compare("q") == 0)
                {
                    break;
                }

                else
                {
                    std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                }
            }
        }
        //    _____                    _____  _     _      _____      _      
        //   / ____|                  |  __ \(_)   | |    / ____|    | |     
        //  | |  __  ___  ___   __ _  | |  | |_ ___| |_  | |     __ _| | ___ 
        //  | | |_ |/ _ \/ _ \ / _` | | |  | | / __| __| | |    / _` | |/ __|
        //  | |__| |  __/ (_) | (_| | | |__| | \__ \ |_  | |___| (_| | | (__ 
        //   \_____|\___|\___/ \__, | |_____/|_|___/\__|  \_____\__,_|_|\___|
        //                      __/ |                                        
        //                     |___/                                         
        // GEOGRAPHICAL DISTANCE CALCULATION
        else if(mode.compare("2") == 0)
        {
            while(1)
            {
                std::cout << ">> Geographical Distance Calculator\n";
                std::cout << ">> Please choose a mode you'd like to use!\n";
                std::cout << "(1) Positional Coordinates from User Input\n";
                std::cout << "(2) Positional Coordinates of Predefined Locations\n";
                std::cout << "(Q) Quit to Main Menu\n\n";

                double Latitude1;
                double Latitude2;
                double Longitude1;
                double Longitude2;
                double Distance;

                std::string Location1;
                std::string Location2;

                std::string DistMode;
                std::cout << "> Choose a mode and press enter...: ";
                std::cin >> DistMode;
                std::cout << '\n';

                if(DistMode.compare("1") == 0)
                {
                    std::cout << ">> Calculate Distance from given Coordinates\n";
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";

                    double LatitudeHours1;
                    double LatitudeMinutes1;
                    double LatitudeSeconds1;
                    double LatitudeHours2;
                    double LatitudeMinutes2;
                    double LatitudeSeconds2;

                    double LongitudeHours1;
                    double LongitudeMinutes1;
                    double LongitudeSeconds1;
                    double LongitudeHours2;
                    double LongitudeMinutes2;
                    double LongitudeSeconds2;
                    
                    std::cout << ">> Give the FIRST City's Parameters!\n";
                    std::cout << "\n> Latitude #1 (φ1) Hours: ";
                    std::cin >> LatitudeHours1;
                    std::cout << '\n';
                    std::cout << "> Latitude #1 (φ1) Minutes: ";
                    std::cin >> LatitudeMinutes1;
                    std::cout << '\n';
                    std::cout << "> Latitude #1 (φ1) Seconds: ";
                    std::cin >> LatitudeSeconds1;
                    std::cout << '\n';
                    Latitude1 = LatitudeHours1 + LatitudeMinutes1/60 + LatitudeSeconds1/3600;

                    std::cout << "\n> Longitude #1 (φ1) Hours: ";
                    std::cin >> LongitudeHours1;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Minutes: ";
                    std::cin >> LongitudeMinutes1;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Seconds: ";
                    std::cin >> LongitudeSeconds1;
                    std::cout << '\n';
                    Longitude1 = LongitudeHours1 + LongitudeMinutes1/60 + LongitudeSeconds1/3600;

                    std::cout << ">> Give the SECOND City's Parameters!\n";
                    std::cout << "\n> Latitude #2 (φ2) Hours: ";
                    std::cin >> LatitudeHours2;
                    std::cout << '\n';
                    std::cout << "> Latitude #2 (φ2) Minutes: ";
                    std::cin >> LatitudeMinutes2;
                    std::cout << '\n';
                    std::cout << "> Latitude #2 (φ2) Seconds: ";
                    std::cin >> LatitudeSeconds2;
                    std::cout << '\n';
                    Latitude2 = LatitudeHours2 + LatitudeMinutes2/60 + LatitudeSeconds2/3600;

                    std::cout << "\n> Longitude #2 (φ2) Hours: ";
                    std::cin >> LongitudeHours2;
                    std::cout << '\n';
                    std::cout << "> Longitude #2 (φ2) Minutes: ";
                    std::cin >> LongitudeMinutes2;
                    std::cout << '\n';
                    std::cout << "> Longitude #2 (φ2) Seconds: ";
                    std::cin >> LongitudeSeconds1;
                    std::cout << '\n';
                    Longitude2 = LongitudeHours2 + LongitudeMinutes2/60 + LongitudeSeconds2/3600;
                }

                else if(DistMode.compare("2") == 0)
                {
                    std::cout << ">> Calculate Distance of Choosen Predefined Locations\n";
                    std::cout << ">> Write the Names of Two Choosen Cities to the Input!\n";
                    while(1)
                    {
                        std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                        std::cout << "\n> Location's name #1 (type \'H\' for Help): ";
                        std::cin >> Location1;
                        std::cout << '\n';

                        if(Location1.compare("Help") == 0 || Location1.compare("help") == 0 || Location1.compare("H") == 0 || Location1.compare("h") == 0)
                        {
                            std::cout << ">> Predefined Locations you can choose from:\n";

                            for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                            {
                                std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << '\n';
                            }

                            std::cout << '\n';
                        }

                        else
                        {
                            try
                            {
                                Latitude1 = LocationDict[Location1][0];
                                Longitude1 = LocationDict[Location1][1];
                            
                                auto LocationSearch1 = LocationDict.find(Location1);
                                if(LocationSearch1 == LocationDict.end())
                                {
                                    throw Location1;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            catch(std::string Location1)
                            {
                                std::cout << ">>>> ERROR: The Location, named \"" + Location1 + "\" is not in the Database!\n";
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                            }
                        }
                    }
                    while(1)
                    {
                        std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                        std::cout << "\n> Location's name #2 (type \'H\' for Help): ";
                        std::cin >> Location2;
                        std::cout << '\n';

                        if(Location2.compare("Help") == 0 || Location2.compare("help") == 0 || Location2.compare("H") == 0 || Location2.compare("h") == 0)
                        {
                            std::cout << ">> Predefined Locations you can choose from:\n";

                            for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                            {
                                std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << '\n';
                            }

                            std::cout << '\n';
                        }

                        else
                        {
                            try
                            {
                                Latitude2 = LocationDict[Location2][0];
                                Longitude2 = LocationDict[Location2][1];
                            
                                auto LocationSearch2 = LocationDict.find(Location2);
                                if(LocationSearch2 == LocationDict.end())
                                {
                                    throw Location2;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            catch(std::string Location2)
                            {
                                std::cout << ">>>> ERROR: The Location, named \"" + Location2 + "\" is not in the Database!\n";
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                            }
                        }
                    }
                }

                else if(DistMode.compare("Q") == 0 || DistMode.compare("q") == 0)
                {
                    break;
                }

                else
                {
                    std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                }

                if(DistMode.compare("1") == 0 || DistMode.compare("2") == 0)
                {
                    Distance = GeogDistCalc(Latitude1, Latitude2, Longitude1, Longitude2);
                    // Convert Distance to Km
                    Distance = double(Distance / 1000);
                    
                    if(DistMode.compare("1") == 0)
                    {
                        std::stringstream distmsg;
                        distmsg << "\n>>> The Geographical Distance Between\n>>> " << Latitude1 << "N ; " << Longitude1 << "E\n>>> and\n>>> " << Latitude2 << "N ; " << Longitude2 << "E\n>>> is\n>>>" << Distance << "km";
                        std::string distmsgstr = distmsg.str();
                        std::cout << distmsgstr << '\n';
                    }

                    else if(DistMode.compare("2") == 0)
                    {
                        std::stringstream distmsg;
                        distmsg << "\n>>> The Geographical Distance Between\n>>> " << Location1 << " and " << Location2 << " is\n>>> " << Distance << "km";
                        std::string distmsgstr = distmsg.str();
                        std::cout << distmsgstr << "\n\n";

                    }
                }
            }
        }


        //   _      __  __  _____ _______    _____      _      
        //  | |    |  \/  |/ ____|__   __|  / ____|    | |     
        //  | |    | \  / | (___    | |    | |     __ _| | ___ 
        //  | |    | |\/| |\___ \   | |    | |    / _` | |/ __|
        //  | |____| |  | |____) |  | |    | |___| (_| | | (__ 
        //  |______|_|  |_|_____/   |_|     \_____\__,_|_|\___|
        // LOCAL MEAN SIDEREAL TIME CALCULATION
        else if(mode.compare("3") == 0)
        {
            while(1)
            {
                std::cout << ">> Local Mean Sidereal Time Calculator\n";
                std::cout << ">> Please choose a mode you'd like to use!\n";
                std::cout << "(1) Parameters from User Input\n";
                std::cout << "(2) Parameters of Predefined Locations\n";
                std::cout << "(Q) Quit to Main Menu\n\n";

                // Declare Variables
                double Latitude;
                double Longitude;
                double DateYear;
                double DateMonth;
                double DateDay;
                double LocalHours;
                double LocalMinutes;
                double LocalSeconds;
                std::string Location;

                std::string LMSTMode;
                std::cout << "> Choose a mode and press enter...: ";
                std::cin >> LMSTMode;
                std::cout << '\n';

                if(LMSTMode.compare("1") == 0)
                {
                    std::cout << ">> Calculate LMST from given Parameters\n";
                    std::cout << ">> Give Parameters!\n";
                    
                    // Input Positional Parameters
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LatitudeHours;
                    double LatitudeMinutes;
                    double LatitudeSeconds;
                    
                    std::cout << "\n> Latitude (φ) Hours: ";
                    std::cin >> LatitudeHours;
                    std::cout << '\n';
                    std::cout << "> Latitude (φ) Minutes: ";
                    std::cin >> LatitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Latitude (φ) Seconds: ";
                    std::cin >> LatitudeSeconds;
                    std::cout << '\n';
                    Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600;

                    std::cout << ">> HINT: You can write Longitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LongitudeHours;
                    double LongitudeMinutes;
                    double LongitudeSeconds;
                    
                    std::cout << "\n> Longitude #1 (φ1) Hours: ";
                    std::cin >> LongitudeHours;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Minutes: ";
                    std::cin >> LongitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Seconds: ";
                    std::cin >> LongitudeSeconds;
                    std::cout << '\n';
                    Longitude = LongitudeHours + LongitudeMinutes/60 + LongitudeSeconds/3600;

                    // Input Time Parameters
                    while(1)
                    {
                        std::cout << "> Year: ";
                        std::cin >> DateYear;

                        if(DateYear != 0)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Month: ";
                        std::cin >> DateMonth;

                        if(DateMonth > 0 && DateMonth < 13)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Months should be inside [1,12] interval, and should be Integer!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Day: ";
                        std::cin >> DateDay;

                        if(int(DateYear)%4 == 0 && (int(DateYear)%100 != 0 || int(DateYear)%400 == 0))
                        {
                            if(MonthLengthListLeapYear[int(DateMonth) - 1] >= DateDay && DateDay > 0)
                            {
                                std::cout << '\n';
                                break;
                            }
                            else
                            {
                                std::stringstream daysmsg;
                                daysmsg << ">>>> ERROR: Days should be inside [1," << MonthLengthListLeapYear[int(DateMonth) - 1] << "] interval, and should be Integer!";
                                std::string daysmsgstr = daysmsg.str();
                                std::cout << daysmsgstr << '\n';
                            }
                        }

                        else
                        {
                            if(MonthLengthList[int(DateMonth) - 1] >= DateDay && DateDay > 0)
                            {
                                std::cout << '\n';
                                break;
                            }

                            else
                            {
                                std::stringstream daysmsg;
                                daysmsg << ">>>> ERROR: Days should be inside [1," << MonthLengthList[int(DateMonth) - 1] << "] interval, and should be Integer!";
                                std::string daysmsgstr = daysmsg.str();
                                std::cout << daysmsgstr << '\n';
                            }
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Local Hours: ";
                        std::cin >> LocalHours;
                        if(LocalHours >= 0 && LocalHours < 24)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Hours should be inside [0,24[ interval!\n";
                        }
                    }

                    while(1)
                    {

                        std::cout << "> Local Minutes: ";
                        std::cin >> LocalMinutes;
                        if(LocalMinutes >= 0 && LocalMinutes <= 59)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Minutes should be inside [0,59] interval, and should be Integer!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Local Seconds: ";
                        std::cin >> LocalSeconds;
                        if(LocalSeconds >= 0 && LocalSeconds < 60)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Seconds should be inside [0,60[ interval!\n";
                        }
                    }

                    std::vector<double> LocalSiderealTimeCalcoutputVec = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, DateYear, DateMonth, DateDay);
                    double LocalSiderealHours = LocalSiderealTimeCalcoutputVec[0];
                    double LocalSiderealMinutes = LocalSiderealTimeCalcoutputVec[1];
                    double LocalSiderealSeconds = LocalSiderealTimeCalcoutputVec[2];
                    double UnitedHours = LocalSiderealTimeCalcoutputVec[3];
                    double UnitedMinutes = LocalSiderealTimeCalcoutputVec[4];
                    double UnitedSeconds = LocalSiderealTimeCalcoutputVec[5];
                    double GreenwichSiderealHours = LocalSiderealTimeCalcoutputVec[6];
                    double GreenwichSiderealMinutes = LocalSiderealTimeCalcoutputVec[7];
                    double GreenwichSiderealSeconds = LocalSiderealTimeCalcoutputVec[8];

                    std::stringstream sidmsg;
                    sidmsg << ">>> The Local Mean Sidereal Time at " << UnitedHours << ":" << UnitedMinutes << ":" << UnitedSeconds << " UT\n>>> At " << Latitude << "N ; " << Longitude << "E\n>>> With" << GreenwichSiderealHours << ":" << GreenwichSiderealMinutes << ":" << GreenwichSiderealSeconds << " GMST at 00:00:00 UT\n>>> is " << LocalSiderealHours << ":" << LocalSiderealMinutes << ":" << LocalSiderealSeconds;
                    std::string sidmsgstr = sidmsg.str();
                    std::cout << sidmsgstr << '\n';

                }

                else if(LMSTMode.compare("2") == 0)
                {
                    std::cout << ">> Calculate LMST from the Coordinates of a Predefined Location\n";
                    std::cout << ">> Write the Name of a Choosen Location to the Input!\n";

                    // Input Choosen Location's Name
                    while(1)
                    {
                        std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                        std::cout << "\n> Location's name (type \'H\' for Help): ";
                        std::cin >> Location;
                        std::cout << '\n';

                        if(Location.compare("Help") == 0 || Location.compare("help") == 0 || Location.compare("H") == 0 || Location.compare("h") == 0)
                        {
                            std::cout << ">> Predefined Locations you can choose from:\n";

                            for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                            {
                                std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << '\n';
                            }

                            std::cout << '\n';
                        }

                        else
                        {
                            try
                            {
                                Latitude = LocationDict[Location][0];
                            
                                auto LocationSearch = LocationDict.find(Location);
                                if(LocationSearch == LocationDict.end())
                                {
                                    throw Location;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            catch(std::string Location)
                            {
                                std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!\n";
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                            }
                        }
                    }

                    // Input Time Parameters
                    while(1)
                    {
                        std::cout << "> Year: ";
                        std::cin >> DateYear;
                        if(DateYear != 0)
                        {
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Month: ";
                        std::cin >> DateMonth;
                        if(DateMonth > 0 && DateMonth < 13)
                        {
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Months should be inside [1,12] interval, and should be Integer!\n";
                        }
                    }

                    // Leap Year Handling
                    while(1)
                    {
                        std::cout << "> Day: ";
                        std::cin >> DateDay;
                        if(int(DateYear)%4 == 0 && (int(DateYear)%100 != 0 || int(DateYear)%400 == 0))
                        {
                            if(MonthLengthListLeapYear[int(DateMonth) - 1] >= DateDay && DateDay > 0)
                            {
                                break;
                            }

                            else
                            {
                                std::stringstream daysmsg;
                                daysmsg << ">>>> ERROR: Days should be inside [1," << MonthLengthListLeapYear[int(DateMonth) - 1] << "] interval, and should be Integer!\n";
                                std::string daysmsgstr = daysmsg.str();
                                std::cout << daysmsgstr << '\n';
                            }
                        }

                        else
                        {
                            if(MonthLengthList[int(DateMonth) - 1] >= DateDay && DateDay > 0)
                            {
                                break;
                            }

                            else
                            {
                                std::stringstream daysmsg;
                                daysmsg << ">>>> ERROR: Days should be inside [1," << MonthLengthList[int(DateMonth) - 1] << "] interval, and should be Integer!\n";
                                std::string daysmsgstr = daysmsg.str();
                                std::cout << daysmsgstr << '\n';
                            }
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Local Hours: ";
                        std::cin >> LocalHours;
                        if(LocalHours >= 0 && LocalHours < 24)
                        {
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Hours should be inside [0,24[ interval!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Local Minutes: ";
                        std::cin >> LocalMinutes;
                        if(LocalMinutes >= 0 && LocalMinutes <= 59)
                        {
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Minutes should be inside [0,59] interval, and should be Integer!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Local Seconds: ";
                        std::cin >> LocalSeconds;
                        if(LocalSeconds >= 0 && LocalSeconds < 60)
                        {
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Seconds should be inside [0,60[ interval!\n";
                        }
                    }

                    std::vector<double> LocalSiderealTimeCalcoutputVec = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, DateYear, DateMonth, DateDay);
                    double LocalSiderealHours = LocalSiderealTimeCalcoutputVec[0];
                    double LocalSiderealMinutes = LocalSiderealTimeCalcoutputVec[1];
                    double LocalSiderealSeconds = LocalSiderealTimeCalcoutputVec[2];
                    double UnitedHours = LocalSiderealTimeCalcoutputVec[3];
                    double UnitedMinutes = LocalSiderealTimeCalcoutputVec[4];
                    double UnitedSeconds = LocalSiderealTimeCalcoutputVec[5];
                    double GreenwichSiderealHours = LocalSiderealTimeCalcoutputVec[6];
                    double GreenwichSiderealMinutes = LocalSiderealTimeCalcoutputVec[7];
                    double GreenwichSiderealSeconds = LocalSiderealTimeCalcoutputVec[8];

                    std::stringstream sidmsg;
                    sidmsg << ">>> The Local Mean Sidereal Time at " << UnitedHours << ":" << UnitedMinutes << ":" << UnitedSeconds << " UT\n>>> in " << Location << " with\n>>> " << GreenwichSiderealHours << ":" << GreenwichSiderealMinutes << ":" << GreenwichSiderealSeconds << " GMST at 00:00:00 UT\n>>> is " << LocalSiderealHours << ":" << LocalSiderealMinutes << ":" << LocalSiderealSeconds;
                    std::string sidmsgstr = sidmsg.str();
                    std::cout << sidmsgstr << '\n';
                }

                else if(LMSTMode.compare("Q") == 0 || LMSTMode.compare("q") == 0)
                {
                    break;
                }

                else
                {
                    std::cout << ">>>> ERROR: Invalid option! Try Again!";
                }
            }
        }


        //   _______       _ _ _       _     _      _____      _      
        //  |__   __|     (_) (_)     | |   | |    / ____|    | |     
        //     | |_      ___| |_  __ _| |__ | |_  | |     __ _| | ___ 
        //     | \ \ /\ / / | | |/ _` | '_ \| __| | |    / _` | |/ __|
        //     | |\ V  V /| | | | (_| | | | | |_  | |___| (_| | | (__ 
        //     |_| \_/\_/ |_|_|_|\__, |_| |_|\__|  \_____\__,_|_|\___|
        //                        __/ |                               
        //                       |___/                                
        // DATETIME CALCULATION FOR TWILIGHTS
        else if(mode.compare("4") == 0)
        {
            while(1)
            {
                std::cout << ">> Calculate Datetimes of Twilights at Specific Location\n";
                std::cout << ">> Please choose a mode you'd like to use!\n";
                std::cout << "(1) Parameters from User Input\n";
                std::cout << "(2) Parameters of Predefined Locations\n";
                std::cout << "(Q) Quit to Main Menu\n\n";

                std::string TwiMode;
                std::cout << "> Choose a mode and press enter...: ";
                std::cin >> TwiMode;
                std::cout << '\n';

                // Constant for Calculations
                std::string Planet = "Earth";
                std::string Location;

                // Declare Variables
                double Latitude;
                double Longitude;

                double LocalDateYear;
                double LocalDateMonth;
                double LocalDateDay;

                if(TwiMode.compare("1") == 0)
                {
                    std::cout << ">> Calculate Twilights from given Parameters\n";
                    std::cout << ">> Give Parameters!\n";

                    // Input Positional Parameters
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LatitudeHours;
                    double LatitudeMinutes;
                    double LatitudeSeconds;
                    
                    std::cout << "\n> Latitude (φ) Hours: ";
                    std::cin >> LatitudeHours;
                    std::cout << '\n';
                    std::cout << "> Latitude (φ) Minutes: ";
                    std::cin >> LatitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Latitude (φ) Seconds: ";
                    std::cin >> LatitudeSeconds;
                    std::cout << '\n';
                    Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600;

                    std::cout << ">> HINT: You can write Longitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LongitudeHours;
                    double LongitudeMinutes;
                    double LongitudeSeconds;
                    
                    std::cout << "\n> Longitude #1 (φ1) Hours: ";
                    std::cin >> LongitudeHours;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Minutes: ";
                    std::cin >> LongitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Seconds: ";
                    std::cin >> LongitudeSeconds;
                    std::cout << '\n';
                    Longitude = LongitudeHours + LongitudeMinutes/60 + LongitudeSeconds/3600;
                }

                else if(TwiMode.compare("2") == 0)
                {                        
                    while(1)
                    {
                        std::cout << ">> Calculate Datetimes of Twilights from the Coordinates of a Predefined Location\n";
                        std::cout << ">> Write the Name of a Choosen Location to the Input!\n";

                        std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                        std::cout << "\n> Location's name (type \'H\' for Help): ";
                        std::cin >> Location;
                        std::cout << '\n';

                        if(Location.compare("Help") == 0 || Location.compare("help") == 0 || Location.compare("H") == 0 || Location.compare("h") == 0)
                        {
                            std::cout << ">> Predefined Locations you can choose from:\n";

                            for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                            {
                                std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << '\n';
                            }

                            std::cout << '\n';
                        }

                        else
                        {
                            try
                            {
                                Latitude = LocationDict[Location][0];
                                Longitude = LocationDict[Location][1];
                            
                                auto LocationSearch = LocationDict.find(Location);
                                if(LocationSearch == LocationDict.end())
                                {
                                    throw Location;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            catch(std::string Location2)
                            {
                                std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!\n";
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                            }
                        }
                    }
                }

                else if(TwiMode.compare("Q") == 0 || TwiMode.compare("q") == 0)
                {
                    break;
                }

                else
                {
                    std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                }

                if(TwiMode.compare("1") == 0 || TwiMode.compare("2") == 0)
                {
                    // Input Time Parameters
                    while(1)
                    {
                        std::cout << "> Year: ";
                        std::cin >> LocalDateYear;
                        if(LocalDateYear != 0)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << "> Month: ";
                        std::cin >> LocalDateMonth;
                        if(LocalDateMonth > 0 && LocalDateMonth < 13)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Months should be inside [1,12] interval, and should be Integer!\n";
                        }
                    }

                    // Leap Year Handling
                    while(1)
                    {
                        std::cout << "> Day: ";
                        std::cin >> LocalDateDay;
                        if(int(LocalDateYear)%4 == 0 && (int(LocalDateYear)%100 != 0 || int(LocalDateYear)%400 == 0))
                        {
                            if(MonthLengthListLeapYear[int(LocalDateMonth) - 1] >= LocalDateDay && LocalDateDay > 0)
                            {
                                break;
                            }

                            else
                            {
                                std::stringstream daysmsg;
                                daysmsg << ">>>> ERROR: Days should be inside [1," << MonthLengthListLeapYear[int(LocalDateMonth) - 1] << "] interval, and should be Integer!\n";
                                std::string daysmsgstr = daysmsg.str();
                                std::cout << daysmsgstr << '\n';
                            }
                        }

                        else
                        {
                            if(MonthLengthList[int(LocalDateMonth) - 1] >= LocalDateDay && LocalDateDay > 0)
                            {
                                std::cout << '\n';
                                break;
                            }

                            else
                            {
                                std::stringstream daysmsg;
                                daysmsg << ">>>> ERROR: Days should be inside [1," << MonthLengthList[int(LocalDateMonth) - 1] << "] interval, and should be Integer!\n";
                                std::string daysmsgstr = daysmsg.str();
                                std::cout << daysmsgstr << '\n';
                            }
                        }
                    }


                    std::vector<double> TwilightCalcvec = TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay);

                    double LocalHoursNoon = TwilightCalcvec[0];
                    double LocalMinutesNoon = TwilightCalcvec[1];
                    double LocalSecondsNoon = TwilightCalcvec[2];
                    double LocalDateYearNoon = TwilightCalcvec[3];
                    double LocalDateMonthNoon = TwilightCalcvec[4];
                    double LocalDateDayNoon = TwilightCalcvec[5];
                    double LocalHoursMidnight = TwilightCalcvec[6];
                    double LocalMinutesMidnight = TwilightCalcvec[7];
                    double LocalSecondsMidnight = TwilightCalcvec[8];
                    double LocalDateYearMidnight = TwilightCalcvec[9];
                    double LocalDateMonthMidnight = TwilightCalcvec[10];
                    double LocalDateDayMidnight = TwilightCalcvec[11];

                    double LocalHoursRiseDaylight = TwilightCalcvec[12];
                    double LocalMinutesRiseDaylight = TwilightCalcvec[13];
                    double LocalSecondsRiseDaylight = TwilightCalcvec[14];
                    double LocalDateYearRiseDaylight = TwilightCalcvec[15];
                    double LocalDateMonthRiseDaylight = TwilightCalcvec[16];
                    double LocalDateDayRiseDaylight = TwilightCalcvec[17];
                    double LocalHoursSetDaylight = TwilightCalcvec[18];
                    double LocalMinutesSetDaylight = TwilightCalcvec[19];
                    double LocalSecondsSetDaylight = TwilightCalcvec[20];
                    double LocalDateYearSetDaylight = TwilightCalcvec[21];
                    double LocalDateMonthSetDaylight = TwilightCalcvec[22];
                    double LocalDateDaySetDaylight = TwilightCalcvec[23];

                    double LocalHoursRiseCivil = TwilightCalcvec[24];
                    double LocalMinutesRiseCivil = TwilightCalcvec[25];
                    double LocalSecondsRiseCivil = TwilightCalcvec[26];
                    double LocalDateYearRiseCivil = TwilightCalcvec[27];
                    double LocalDateMonthRiseCivil = TwilightCalcvec[28];
                    double LocalDateDayRiseCivil = TwilightCalcvec[29];
                    double LocalHoursSetCivil = TwilightCalcvec[30];
                    double LocalMinutesSetCivil = TwilightCalcvec[31];
                    double LocalSecondsSetCivil = TwilightCalcvec[32];
                    double LocalDateYearSetCivil = TwilightCalcvec[33];
                    double LocalDateMonthSetCivil = TwilightCalcvec[34];
                    double LocalDateDaySetCivil = TwilightCalcvec[35];

                    double LocalHoursRiseNaval = TwilightCalcvec[36];
                    double LocalMinutesRiseNaval = TwilightCalcvec[37];
                    double LocalSecondsRiseNaval = TwilightCalcvec[38];
                    double LocalDateYearRiseNaval = TwilightCalcvec[39];
                    double LocalDateMonthRiseNaval = TwilightCalcvec[40];
                    double LocalDateDayRiseNaval = TwilightCalcvec[41];
                    double LocalHoursSetNaval = TwilightCalcvec[42];
                    double LocalMinutesSetNaval = TwilightCalcvec[43];
                    double LocalSecondsSetNaval = TwilightCalcvec[44];
                    double LocalDateYearSetNaval = TwilightCalcvec[45];
                    double LocalDateMonthSetNaval = TwilightCalcvec[46];
                    double LocalDateDaySetNaval = TwilightCalcvec[47];

                    double LocalHoursRiseAstro = TwilightCalcvec[48];
                    double LocalMinutesRiseAstro = TwilightCalcvec[49];
                    double LocalSecondsRiseAstro = TwilightCalcvec[50];
                    double LocalDateYearSetAstro = TwilightCalcvec[51];
                    double LocalDateMonthSetAstro = TwilightCalcvec[52];
                    double LocalDateDaySetAstro = TwilightCalcvec[53];
                    double LocalHoursSetAstro = TwilightCalcvec[54];
                    double LocalMinutesSetAstro = TwilightCalcvec[55];
                    double LocalSecondsSetAstro = TwilightCalcvec[56];
                    double LocalDateYearRiseAstro = TwilightCalcvec[57];
                    double LocalDateMonthRiseAstro = TwilightCalcvec[58];
                    double LocalDateDayRiseAstro = TwilightCalcvec[59];

                    if(TwiMode.compare("1") == 0)
                    {
                        std::stringstream suncoordmsg;
                        suncoordmsg << ">>> Calculated Datetimes of Twilights at Coordinates \n>>> " << Latitude << "N ; " << Longitude << "E :";
                        std::string suncoordmsgstr = suncoordmsg.str();
                        std::cout << suncoordmsgstr << '\n';
                    }

                    else if(TwiMode.compare("2") == 0)
                    {
                        std::cout << "\n>>> Calculated Datetimes of Twilights at " << Location << ":";
                    }

                    // +4 and -6 are Corrections for more accurate times
                    std::stringstream msgdaylightrise;
                    std::stringstream msgdaylightset;
                    msgdaylightrise << "\n>> Rising Daylight's time: " << LocalHoursRiseDaylight << ":" << LocalMinutesRiseDaylight << ":" << LocalSecondsRiseDaylight << " on " << LocalDateYearRiseDaylight << "." << LocalDateMonthRiseDaylight << "." << LocalDateDayRiseDaylight;
                    msgdaylightset << ">> Setting Daylight's time: " << LocalHoursSetDaylight << ":" << LocalMinutesSetDaylight << ":" << LocalSecondsSetDaylight << " on " << LocalDateYearSetDaylight << "." << LocalDateMonthSetDaylight << "." << LocalDateDaySetDaylight;
                    std::string msgdaylightrisestr = msgdaylightrise.str();
                    std::string msgdaylightsetstr = msgdaylightset.str();
                    std::cout << msgdaylightrisestr << '\n';
                    std::cout << msgdaylightsetstr << '\n';

                    std::stringstream msgcivilrise;
                    std::stringstream msgcivilset;
                    msgcivilrise << "\n>> Rising Civil Twilight's time is between\n>> " << LocalHoursRiseCivil << ":" << LocalMinutesRiseCivil + 4 << ":" << LocalSecondsRiseCivil << " and " << LocalHoursRiseDaylight << ":" << LocalMinutesRiseDaylight << ":" << LocalSecondsRiseDaylight << " on " << LocalDateYearRiseCivil << "." << LocalDateMonthRiseCivil << "." << LocalDateDayRiseCivil;
                    msgcivilset << ">> Setting Civil Twilight's time is between\n>> " << LocalHoursSetDaylight << ":" << LocalMinutesSetDaylight << ":" << LocalSecondsSetDaylight << " and " << LocalHoursSetCivil << ":" << LocalMinutesSetCivil - 6 << ":" << LocalSecondsSetCivil << " on " << LocalDateYearSetCivil << "." << LocalDateMonthSetCivil << "." << LocalDateDaySetCivil;
                    std::string msgcivilrisestr = msgcivilrise.str();
                    std::string msgcivilsetstr = msgcivilset.str();
                    std::cout << msgcivilrisestr << '\n';
                    std::cout << msgcivilsetstr << '\n';

                    std::stringstream msgnavalrise;
                    std::stringstream msgnavalset;
                    msgnavalrise << "\n>> Rising Nautical Twilight's time is between\n>> " << LocalHoursRiseNaval << ":" << LocalMinutesRiseNaval + 4 << ":" << LocalSecondsRiseNaval << " and " << LocalHoursRiseCivil << ":" << LocalMinutesRiseCivil + 4 << ":" << LocalSecondsRiseCivil << " on " << LocalDateYearRiseNaval << "." << LocalDateMonthRiseNaval << "." << LocalDateDayRiseNaval;
                    msgnavalset << ">> Setting Nautical Twilight's time is between\n>> " << LocalHoursSetCivil << ":" << LocalMinutesSetCivil - 6 << ":" << LocalSecondsSetCivil << " and " << LocalHoursSetNaval << ":" << LocalMinutesSetNaval - 6 << ":" << LocalSecondsSetNaval << " on " << LocalDateYearSetNaval << "." << LocalDateMonthSetNaval << "." << LocalDateDaySetNaval;
                    std::string msgnavalrisestr = msgnavalrise.str();
                    std::string msgnavalsetstr = msgnavalset.str();
                    std::cout << msgnavalrisestr << '\n';
                    std::cout << msgnavalsetstr << '\n';

                    std::stringstream msgastrorise;
                    std::stringstream msgastroset;
                    msgastrorise << "\n>> Rising Astronomical Twilight's time is between\n>> " << LocalHoursRiseAstro << ":" << LocalMinutesRiseAstro + 4 << ":" << LocalSecondsRiseAstro << " and " << LocalHoursRiseNaval << ":" << LocalMinutesRiseNaval + 4 << ":" << LocalSecondsRiseNaval << " on " << LocalDateYearSetAstro << "." << LocalDateMonthSetAstro << "." << LocalDateDaySetAstro;
                    msgastroset << ">> Setting Astronomical Twilight's time is between\n>> " << LocalHoursSetNaval << ":" << LocalMinutesSetNaval - 6 << ":" << LocalSecondsSetNaval << " and " << LocalHoursSetAstro << ":" << LocalMinutesSetAstro - 6 << ":" << LocalSecondsSetAstro << " on " << LocalDateYearRiseAstro << "." << LocalDateMonthRiseAstro << "." << LocalDateDayRiseAstro;
                    std::string msgastrorisestr = msgastrorise.str();
                    std::string msgastrosetstr = msgastroset.str();
                    std::cout << msgastrorisestr << '\n';
                    std::cout << msgastrosetstr << '\n';

                    std::stringstream msgnoon;
                    std::stringstream msgmidnight;
                    msgnoon << "\n>> Noon occurs at " << LocalHoursNoon << ":" << LocalMinutesNoon << ":" << LocalSecondsNoon << " on " << LocalDateYearNoon << "." << LocalDateMonthNoon << "." << LocalDateDayNoon;
                    msgmidnight << ">> Midnight occurs at " << LocalHoursMidnight << ":" << LocalMinutesMidnight << ":" << LocalSecondsMidnight << " on " << LocalDateYearMidnight << "." << LocalDateMonthMidnight << "." << LocalDateDayMidnight;
                    std::string msgnoonstr = msgnoon.str();
                    std::string msgmidnightstr = msgmidnight.str();
                    std::cout << msgnoonstr << '\n';
                    std::cout << msgmidnightstr << '\n';
                }
            }
        }


        //    ___      _               _____    _                   _           
        //   / _ \    | |             |_   _|  (_)                 | |          
        //  / /_\ \___| |_ _ __ ___     | |_ __ _  __ _ _ __   __ _| | ___  ___ 
        //  |  _  / __| __| '__/ _ \    | | '__| |/ _` | '_ \ / _` | |/ _ \/ __|
        //  | | | \__ \ |_| | | (_) |   | | |  | | (_| | | | | (_| | |  __/\__ \
        //  \_| |_/___/\__|_|  \___/    \_/_|  |_|\__,_|_| |_|\__, |_|\___||___/
        //                                                     __/ |            
        //                                                    |___/             
        // Calculate Astronomical Triangles Parameters
        else if(mode.compare("5") == 0)
        {
            while(1)
            {
                std::cout << ">> Calculate Astronomical Triangles Parameters from given Ones\n";
                std::cout << ">> Please choose a mode you'd like to use!\n";
                std::cout << "(1) Parameters from User Input\n";
                std::cout << "(Q) Quit to Main Menu\n\n";

                std::string TrigMode;
                std::cout << "> Choose a mode and press enter...: ";
                std::cin >> TrigMode;
                std::cout << '\n';

                // Declare variables
                double aValue;
                double bValue;
                double cValue;
                double alphaValue;
                double betaValue;
                double gammaValue;

                if(TrigMode.compare("1") == 0)
                {
                    std::cout << "\n>> Please Give Parameters' Values!\n";
                    std::cout << ">>> HINT: You should give Parameters in angular units. You can press enter for\n>> A blank input too. Doing like this will mark the actual parameter\n>> As a missing one.\n";
                    
                    std::cout << "> Value for side \'A\': ";
                    std::cin >> aValue;
                    std::cout << '\n';

                    std::cout << "> Value for side \'B\': ";
                    std::cin >> bValue;
                    std::cout << '\n';

                    std::cout << "> Value for side \'C\': ";
                    std::cin >> cValue;
                    std::cout << '\n';

                    std::cout << "> Value for angle \'α\': ";
                    std::cin >> alphaValue;
                    std::cout << '\n';

                    std::cout << "> Value for angle \'β\': ";
                    std::cin >> betaValue;
                    std::cout << '\n';

                    std::cout << "> Value for angle \'γ\': ";
                    std::cin >> gammaValue;
                    std::cout << '\n';
                }

                else if(TrigMode.compare("2") == 0)
                {}
                
                else if(TrigMode.compare("Q") == 0 || TrigMode.compare("q") == 0)
                {
                    break;
                }

                else
                {
                    std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                }

                
                if(TrigMode.compare("1") == 0)
                {
                    
                    std::vector<double> AstroTrianglesoutputVec = AstroTriangles(aValue, bValue, cValue, alphaValue, betaValue, gammaValue);
                    aValue = AstroTrianglesoutputVec[0];
                    bValue = AstroTrianglesoutputVec[1];
                    cValue = AstroTrianglesoutputVec[2];
                    alphaValue = AstroTrianglesoutputVec[3];
                    betaValue = AstroTrianglesoutputVec[4];
                    gammaValue = AstroTrianglesoutputVec[5];

                    if(aValue == 0 || bValue == 0 || cValue == 0 || alphaValue == 0 || betaValue == 0 || gammaValue == 0)
                    {
                        std::cout << "Given Data are\'nt enough to calculate the Triangle's Parameters!";
                    }

                    std::cout << ">> Calculated Parameters of the Triangle:\n";
                    std::cout << "Side \'A\': " << aValue << '\n';
                    std::cout << "Side \'B\': " << bValue << '\n';
                    std::cout << "Side \'C\': " << cValue << '\n';
                    std::cout << "Angle \'α\': " << alphaValue << '\n';
                    std::cout << "Angle \'β\': " << betaValue << '\n';
                    std::cout << "Angle \'γ\': " << gammaValue << '\n';
                    std::cout << "\n";
                }
            }
        }


        //   _____                 _ _       _ 
        //  /  ___|               | (_)     | |
        //  \ `--. _   _ _ __   __| |_  __ _| |
        //   `--. \ | | | '_ \ / _` | |/ _` | |
        //  /\__/ / |_| | | | | (_| | | (_| | |
        //  \____/ \__,_|_| |_|\__,_|_|\__,_|_|
        // Plot Sundial for Choosen Locations
        else if(mode.compare("6") == 0)
        {
            while(1)
            {
                std::cout << ">> Plot Sun's Path on a Sundial at Choosen Location on Earth\n";
                std::cout << ">> Please choose a mode you'd like to use!\n";
                std::cout << "(1) Parameters from User Input\n";
                std::cout << "(2) Parameters of Predefined Locations\n";
                std::cout << "(Q) Quit to Main Menu\n\n";
                
                std::string SundialMode;
                std::cout << "> Choose a mode and press enter...: ";
                std::cin >> SundialMode;
                std::cout << '\n';

                // Constants for calculation
                std::string Planet = "Earth";

                // Declare Variables
                double Latitude;
                double Longitude;

                std::string SunDialChoose;
                double SunDialYear;

                double LocalDateYear;
                double LocalDateMonth;
                double LocalDateDay;

                if(SundialMode.compare("1") == 0)
                {
                    std::cout << ">> Plot a Sundial on a User-defined Location\n";
                    std::cout << ">> Give Parameters!\n";

                    // Input Positional Parameters
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LatitudeHours;
                    double LatitudeMinutes;
                    double LatitudeSeconds;
                    
                    std::cout << "\n> Latitude (φ) Hours: ";
                    std::cin >> LatitudeHours;
                    std::cout << '\n';
                    std::cout << "> Latitude (φ) Minutes: ";
                    std::cin >> LatitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Latitude (φ) Seconds: ";
                    std::cin >> LatitudeSeconds;
                    std::cout << '\n';
                    Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600;

                    std::cout << ">> HINT: You can write Longitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LongitudeHours;
                    double LongitudeMinutes;
                    double LongitudeSeconds;
                    
                    std::cout << "\n> Longitude #1 (φ1) Hours: ";
                    std::cin >> LongitudeHours;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Minutes: ";
                    std::cin >> LongitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Seconds: ";
                    std::cin >> LongitudeSeconds;
                    std::cout << '\n';
                    Longitude = LongitudeHours + LongitudeMinutes/60 + LongitudeSeconds/3600;
                }

                else if(SundialMode.compare("2") == 0)
                {
                    std::cout << ">> Plot a Sundial on a Predefined Location's Coordinates";
                    std::cout << ">> Write the Name of a Choosen Location to the Input!";

                    // Input Choosen Location's Name
                    while(1)
                    {
                        std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                        std::string Location;
                        std::cout << "\n> Location's name (type \'H\' for Help): ";
                        std::cin >> Location;
                        std::cout << '\n';

                        if(Location.compare("Help") == 0 || Location.compare("help") == 0 || Location.compare("H") == 0 || Location.compare("h") == 0)
                        {
                            std::cout << ">> Predefined Locations you can choose from:\n";

                            for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                            {
                                std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << '\n';
                            }

                            std::cout << '\n';
                        }

                        else
                        {
                            try
                            {
                                Latitude = LocationDict[Location][0];
                                Longitude = LocationDict[Location][1];
                            
                                auto LocationSearch = LocationDict.find(Location);
                                if(LocationSearch == LocationDict.end())
                                {
                                    throw Location;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            catch(std::string Location)
                            {
                                std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!\n";
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                            }
                        }
                    }
                }

                else if(SundialMode.compare("Q") == 0 || SundialMode.compare("q") == 0)
                {
                    break;
                }

                else
                {
                    std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                }


                if(SundialMode.compare("1") == 0 || SundialMode.compare("2") == 0)
                {
                    std::cout << ">> For which Year would You like to Draw the Sundial?\n";
                    while(1)
                    {
                        std::cout << "> Choosen Year: ";
                        std::cin >> SunDialYear;
                        std::cout << '\n';

                        if(SunDialYear != 0)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n";
                        }
                    }

                    while(1)
                    {
                        std::cout << ">> Would you like to plot the Sun's path for a Choosen Date in This Year too?\n";

                        std::cout << ">> Write Y for Yes or N for No: ";
                        std::cin >> SunDialChoose;
                        std::cout << '\n';

                        if(SunDialChoose.compare("Y") == 0 || SunDialChoose.compare("y") == 0 || SunDialChoose.compare("Yes") == 0 || SunDialChoose.compare("yes") == 0 || SunDialChoose.compare("YEs") == 0 || SunDialChoose.compare("yEs") == 0 || SunDialChoose.compare("yeS") == 0 || SunDialChoose.compare("YeS") == 0 || SunDialChoose.compare("yES") == 0)
                        {
                            // Input Time Parameters
                            while(1)
                            {
                                std::cout << "> Month: ";
                                std::cin >> LocalDateMonth;
                                std::cout << '\n';

                                if(LocalDateMonth > 0 && LocalDateMonth < 13)
                                {
                                    std::cout << '\n';
                                    break;
                                }

                                else
                                {
                                    std::cout << ">>>> ERROR: Months should be inside [1,12] interval, and should be Integer!\n";
                                }
                            }

                            // Leap Year Handling
                            while(1)
                            {
                                std::cout << "> Day: ";
                                std::cin >> LocalDateDay;
                                std::cout << '\n';

                                if(int(LocalDateYear)%4 == 0 && (int(LocalDateYear)%100 != 0 || int(LocalDateYear)%400 == 0))
                                {
                                    if(MonthLengthListLeapYear[int(LocalDateMonth) - 1] >= LocalDateDay || LocalDateDay > 0)
                                    {
                                        std::cout << '\n';
                                        break;
                                    }

                                    else
                                    {
                                        std::stringstream daysmsg;
                                        daysmsg << ">>>> ERROR: Days should be inside [1," << MonthLengthListLeapYear[int(LocalDateMonth) - 1] << "] interval, and should be Integer!";
                                        std::string daysmsgstr = daysmsg.str();
                                        std::cout << daysmsgstr << '\n';
                                    }
                                }

                                else
                                {
                                    if(MonthLengthList[int(LocalDateMonth) - 1] >= LocalDateDay && LocalDateDay > 0)
                                    {
                                        std::cout << '\n';
                                        break;
                                    }

                                    else
                                    {
                                        std::stringstream daysmsg;
                                        daysmsg << ">>>> ERROR: Days should be inside [1," << MonthLengthList[int(LocalDateMonth) - 1] << "] interval, and should be Integer!";
                                        std::string daysmsgstr = daysmsg.str();
                                        std::cout << daysmsgstr << '\n';
                                    }
                                }
                            }

                            break;
                        }

                        else if(SunDialChoose.compare("N") == 0 || SunDialChoose.compare("n") == 0 || SunDialChoose.compare("No") == 0 || SunDialChoose.compare("no") == 0 || SunDialChoose.compare("nO") == 0)
                        {
                            std::cout << '\n';
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Invalid option! Try Again!";
                        }
                    }

                    int MeasureNumber = 1000;
                    int FineTuned = 1000;

                    if(SunDialChoose.compare("Y") == 0 || SunDialChoose.compare("y") == 0 || SunDialChoose.compare("Yes") == 0 || SunDialChoose.compare("yes") == 0 || SunDialChoose.compare("YEs") == 0 || SunDialChoose.compare("yEs") == 0 || SunDialChoose.compare("yeS") == 0 || SunDialChoose.compare("YeS") == 0 || SunDialChoose.compare("yES") == 0)
                    {
                        std::cout << "Choosen Date:\n";
                        ////// CHOOSEN DATE //////
                        std::vector<double> SundialPrecalculationsoutputVecChoosen = SundialPrecalculations(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay);
                        double LocalHourAngleRiseChoosen = SundialPrecalculationsoutputVecChoosen[0];
                        double LocalHourAngleSetChoosen = SundialPrecalculationsoutputVecChoosen[1];
                        double DeclinationSunChoosen = SundialPrecalculationsoutputVecChoosen[2];

                        // Create lists for plot parameters
                        std::vector<double> LocalHourAngleChoosen = {};
                        std::vector<double> AltitudesChoosen = {};
                        std::vector<double> AzimuthsChoosen = {};
                        std::vector<double> ShadowsChoosen = {};

                        if(LocalHourAngleRiseChoosen > LocalHourAngleSetChoosen)
                        {
                            int ChoosenStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseChoosen * FineTuned)) / (MeasureNumber / 2));
                            int ChoosenStep2 = int(int(LocalHourAngleSetChoosen * FineTuned) / (MeasureNumber / 2));

                            // Calculate plot parameters
                            for(int LocalHourAngleActual = int(LocalHourAngleRiseChoosen * FineTuned); int(23.999999999 * FineTuned); ChoosenStep1)
                            {
                                // Norm back to normal
                                double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                                // Calculate parameters by ~10 seconds interval
                                std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunChoosen);
                                double AltitudeActual = SundialParametersCalcoutputVec[0];
                                double AzimuthActual = SundialParametersCalcoutputVec[1];
                                double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                                //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunChoosen)
                                //std::cout << LocalHourAngleActual, AltitudeActual)

                                // Append parameters to lists
                                LocalHourAngleActual += 12;
                                LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                                LocalHourAngleChoosen.push_back(LocalHourAngleActual);
                                AltitudesChoosen.push_back(AltitudeActual);
                                AzimuthsChoosen.push_back(AzimuthActual);
                                ShadowsChoosen.push_back(ShadowsLengthActual);
                            }

                            // Calculate plot parameters
                            for(int LocalHourAngleActual = 0; int(LocalHourAngleSetChoosen * FineTuned); ChoosenStep2)
                            {
                                // Norm back to normal
                                double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                                // Calculate parameters by ~10 seconds interval
                                std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunChoosen);
                                double AltitudeActual = SundialParametersCalcoutputVec[0];
                                double AzimuthActual = SundialParametersCalcoutputVec[1];
                                double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                                //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunChoosen)
                                //std::cout << LocalHourAngleActual, AltitudeActual)

                                // Append parameters to lists
                                LocalHourAngleActual += 12;
                                LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                                LocalHourAngleChoosen.push_back(LocalHourAngleActual);
                                AltitudesChoosen.push_back(AltitudeActual);
                                AzimuthsChoosen.push_back(AzimuthActual);
                                ShadowsChoosen.push_back(ShadowsLengthActual);
                            }
                        }

                        else
                        {
                            int ChoosenStep = int((int(LocalHourAngleSetChoosen * FineTuned) - int(LocalHourAngleRiseChoosen * FineTuned)) / MeasureNumber);

                            // Calculate plot parameters
                            for(int LocalHourAngleActual = int(LocalHourAngleRiseChoosen * FineTuned); int(LocalHourAngleSetChoosen * FineTuned); ChoosenStep)
                            {
                                // Norm back to normal
                                double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                                // Calculate parameters by ~10 seconds interval
                                std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunChoosen);
                                double AltitudeActual = SundialParametersCalcoutputVec[0];
                                double AzimuthActual = SundialParametersCalcoutputVec[1];
                                double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                                //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunChoosen)
                                //std::cout << LocalHourAngleActual, AltitudeActual)

                                // Append parameters to lists
                                LocalHourAngleActual += 12;
                                LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                                LocalHourAngleChoosen.push_back(LocalHourAngleActual);
                                AltitudesChoosen.push_back(AltitudeActual);
                                AzimuthsChoosen.push_back(AzimuthActual);
                                ShadowsChoosen.push_back(ShadowsLengthActual);
                            }
                        }
                    }


                    std::cout << "Summer Solstice:";
                    ////// SUMMER SOLSTICE //////
                    int LocalDateMonthSummer = 6;
                    int LocalDateDaySummer;
                    if(int(SunDialYear)%4 == 0)
                    {
                        LocalDateDaySummer = 20;
                    }

                    else
                    {
                        LocalDateDaySummer = 21;
                    }

                    std::vector<double> SundialPrecalculationsoutputVecSummer = SundialPrecalculations(Planet, Latitude, Longitude, SunDialYear, LocalDateMonthSummer, LocalDateDaySummer);
                    double LocalHourAngleRiseSummer = SundialPrecalculationsoutputVecSummer[0];
                    double LocalHourAngleSetSummer = SundialPrecalculationsoutputVecSummer[1];
                    double DeclinationSunSummer = SundialPrecalculationsoutputVecSummer[2];

                    // Create lists for plot parameters
                    std::vector<double> LocalHourAngleSummer = {};
                    std::vector<double> AltitudesSummer = {};
                    std::vector<double> AzimuthsSummer = {};
                    std::vector<double> ShadowsSummer = {};

                    if(LocalHourAngleRiseSummer > LocalHourAngleSetSummer)
                    {
                        int SummerStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseSummer * FineTuned)) / (MeasureNumber / 2));
                        int SummerStep2 = int(int(LocalHourAngleSetSummer * FineTuned) / (MeasureNumber / 2));

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = int(LocalHourAngleRiseSummer * FineTuned); int(23.999999999 * FineTuned); SummerStep1)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSummer);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSummer)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleSummer.push_back(LocalHourAngleActual);
                            AltitudesSummer.push_back(AltitudeActual);
                            AzimuthsSummer.push_back(AzimuthActual);
                            ShadowsSummer.push_back(ShadowsLengthActual);
                        }

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = 0; int(LocalHourAngleSetSummer * FineTuned); SummerStep2)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSummer);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSummer)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleSummer.push_back(LocalHourAngleActual);
                            AltitudesSummer.push_back(AltitudeActual);
                            AzimuthsSummer.push_back(AzimuthActual);
                            ShadowsSummer.push_back(ShadowsLengthActual);
                        }
                    }

                    else
                    {
                        int SummerStep = int((int(LocalHourAngleSetSummer * FineTuned) - int(LocalHourAngleRiseSummer * FineTuned)) / MeasureNumber);

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = int(LocalHourAngleRiseSummer * FineTuned); int(LocalHourAngleSetSummer * FineTuned); SummerStep)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSummer);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSummer)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleSummer.push_back(LocalHourAngleActual);
                            AltitudesSummer.push_back(AltitudeActual);
                            AzimuthsSummer.push_back(AzimuthActual);
                            ShadowsSummer.push_back(ShadowsLengthActual);
                        }
                    }


                    std::cout << "Winter Solstice:";
                    ////// WINTER SOLSTICE //////
                    int LocalDateMonthWinter = 12;
                    int LocalDateDayWinter;
                    if(int(SunDialYear + 1)%4 == 0)
                    {
                        LocalDateDayWinter = 22;
                    }

                    else
                    {
                        LocalDateDayWinter = 21;
                    }

                    std::vector<double> SundialPrecalculationsoutputVecWinter = SundialPrecalculations(Planet, Latitude, Longitude, SunDialYear, LocalDateMonthWinter, LocalDateDayWinter);
                    double LocalHourAngleRiseWinter = SundialPrecalculationsoutputVecWinter[0];
                    double LocalHourAngleSetWinter = SundialPrecalculationsoutputVecWinter[1];
                    double DeclinationSunWinter = SundialPrecalculationsoutputVecWinter[2];

                    // Create lists for plot parameters
                    std::vector<double> LocalHourAngleWinter = {};
                    std::vector<double> AltitudesWinter = {};
                    std::vector<double> AzimuthsWinter = {};
                    std::vector<double> ShadowsWinter = {};

                    if(LocalHourAngleRiseWinter > LocalHourAngleSetWinter)
                    {
                        int WinterStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseWinter * FineTuned)) / (MeasureNumber / 2));
                        int WinterStep2 = int(int(LocalHourAngleSetWinter * FineTuned) / (MeasureNumber / 2));

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = int(LocalHourAngleRiseWinter * FineTuned); int(23.999999999 * FineTuned); WinterStep1)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunWinter);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunWinter)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleWinter.push_back(LocalHourAngleActual);
                            AltitudesWinter.push_back(AltitudeActual);
                            AzimuthsWinter.push_back(AzimuthActual);
                            ShadowsWinter.push_back(ShadowsLengthActual);
                        }

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = 0; int(LocalHourAngleSetWinter * FineTuned); WinterStep2)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunWinter);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunWinter)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleWinter.push_back(LocalHourAngleActual);
                            AltitudesWinter.push_back(AltitudeActual);
                            AzimuthsWinter.push_back(AzimuthActual);
                            ShadowsWinter.push_back(ShadowsLengthActual);
                        }
                    }

                    else
                    {
                        int WinterStep = int((int(LocalHourAngleSetWinter * FineTuned) - int(LocalHourAngleRiseWinter * FineTuned)) / MeasureNumber);

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = int(LocalHourAngleRiseWinter * FineTuned); int(LocalHourAngleSetWinter * FineTuned); WinterStep)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunWinter);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, AzimuthAShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunWinter)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleWinter.push_back(LocalHourAngleActual);
                            AltitudesWinter.push_back(AltitudeActual);
                            AzimuthsWinter.push_back(AzimuthActual);
                            ShadowsWinter.push_back(ShadowsLengthActual);
                        }
                    }


                    std::cout << "March Equinox:";
                    ////// MARCH EQUINOX //////
                    int LocalDateMonthMarch = 3;
                    int LocalDateDayMarch = 20;

                    std::vector<double> SundialPrecalculationsoutputVecMarch = SundialPrecalculations(Planet, Latitude, Longitude, SunDialYear, LocalDateMonthMarch, LocalDateDayMarch);
                    double LocalHourAngleRiseMarch = SundialPrecalculationsoutputVecMarch[0];
                    double LocalHourAngleSetMarch = SundialPrecalculationsoutputVecMarch[1];
                    double DeclinationSunMarch = SundialPrecalculationsoutputVecMarch[2];

                    // Create lists for plot parameters
                    std::vector<double> LocalHourAngleMarch = {};
                    std::vector<double> AltitudesMarch = {};
                    std::vector<double> AzimuthsMarch = {};
                    std::vector<double> ShadowsMarch = {};

                    if(LocalHourAngleRiseMarch > LocalHourAngleSetMarch)
                    {
                        int MarchStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseMarch * FineTuned)) / (MeasureNumber / 2));
                        int MarchStep2 = int(int(LocalHourAngleSetMarch * FineTuned) / (MeasureNumber / 2));

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = int(LocalHourAngleRiseMarch * FineTuned); int(23.999999999 * FineTuned); MarchStep1)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunMarch);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunMarch)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleMarch.push_back(LocalHourAngleActual);
                            AltitudesMarch.push_back(AltitudeActual);
                            AzimuthsMarch.push_back(AzimuthActual);
                            ShadowsMarch.push_back(ShadowsLengthActual);
                        }

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = 0; int(LocalHourAngleSetMarch * FineTuned); MarchStep2)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunMarch);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunMarch)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleMarch.push_back(LocalHourAngleActual);
                            AltitudesMarch.push_back(AltitudeActual);
                            AzimuthsMarch.push_back(AzimuthActual);
                            ShadowsMarch.push_back(ShadowsLengthActual);
                        }
                    }


                    else
                    {
                        int MarchStep = int((int(LocalHourAngleSetMarch * FineTuned) - int(LocalHourAngleRiseMarch * FineTuned)) / MeasureNumber);

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = int(LocalHourAngleRiseMarch * FineTuned); int(LocalHourAngleSetMarch * FineTuned); MarchStep)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunMarch);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunMarch)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleMarch.push_back(LocalHourAngleActual);
                            AltitudesMarch.push_back(AltitudeActual);
                            AzimuthsMarch.push_back(AzimuthActual);
                            ShadowsMarch.push_back(ShadowsLengthActual);
                        }
                    }


                    std::cout << "September Equinox:";
                    ////// SEPTEMBER EQIUNOX //////
                    int LocalDateMonthSeptember = 9;
                    int LocalDateDaySeptember;
                    if(int(SunDialYear)%4 == 0 || int(SunDialYear - 1)%4 == 0)
                    {
                        LocalDateDaySeptember = 22;
                    }

                    else
                    {
                        LocalDateDaySeptember = 23;
                    }

                    std::vector<double> SundialPrecalculationsoutputVec = SundialPrecalculations(Planet, Latitude, Longitude, SunDialYear, LocalDateMonthSeptember, LocalDateDaySeptember);
                    double LocalHourAngleRiseSeptember = SundialPrecalculationsoutputVec[0];
                    double LocalHourAngleSetSeptember = SundialPrecalculationsoutputVec[1];
                    double DeclinationSunSeptember = SundialPrecalculationsoutputVec[2];

                    // Create lists for plot parameters
                    std::vector<double> LocalHourAngleSeptember = {};
                    std::vector<double> AltitudesSeptember = {};
                    std::vector<double> AzimuthsSeptember = {};
                    std::vector<double> ShadowsSeptember = {};

                    if(LocalHourAngleRiseSeptember > LocalHourAngleSetSeptember)
                    {
                        int SeptemberStep1 = int((int(23.999999999 * FineTuned) - int(LocalHourAngleRiseSeptember * FineTuned)) / (MeasureNumber / 2));
                        int SeptemberStep2 = int(int(LocalHourAngleSetSeptember * FineTuned) / (MeasureNumber / 2));

                        // Calculate plot parameters
                        for(double LocalHourAngleActual = int(LocalHourAngleRiseSeptember * FineTuned); LocalHourAngleActual < int(23.999999999 * FineTuned); SeptemberStep1)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSeptember);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSeptember)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleSeptember.push_back(LocalHourAngleActual);
                            AltitudesSeptember.push_back(AltitudeActual);
                            AzimuthsSeptember.push_back(AzimuthActual);
                            ShadowsSeptember.push_back(ShadowsLengthActual);
                        }

                        // Calculate plot parameters
                        for(double LocalHourAngleActual = 0; LocalHourAngleActual < int(LocalHourAngleSetSeptember * FineTuned); SeptemberStep2)
                        {
                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSeptember);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSeptember)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleSeptember.push_back(LocalHourAngleActual);
                            AltitudesSeptember.push_back(AltitudeActual);
                            AzimuthsSeptember.push_back(AzimuthActual);
                            ShadowsSeptember.push_back(ShadowsLengthActual);
                        }
                    }

                    else
                    {
                        int SeptemberStep = int((int(LocalHourAngleSetSeptember * FineTuned) - int(LocalHourAngleRiseSeptember * FineTuned)) / MeasureNumber);

                        // Calculate plot parameters
                        for(int LocalHourAngleActual = int(LocalHourAngleRiseSeptember * FineTuned); LocalHourAngleActual < int(LocalHourAngleSetSeptember * FineTuned); SeptemberStep)
                        {

                            // Norm back to normal
                            double LocalHourAngleActualDouble = LocalHourAngleActual / FineTuned;

                            // Calculate parameters by ~10 seconds interval
                            std::vector<double> SundialParametersCalcoutputVec = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSeptember);
                            double AltitudeActual = SundialParametersCalcoutputVec[0];
                            double AzimuthActual = SundialParametersCalcoutputVec[1];
                            double ShadowsLengthActual = SundialParametersCalcoutputVec[2];
                            //AltitudeActual, ShadowsLengthActual = SundialParametersCalc(Latitude, LocalHourAngleActualDouble, DeclinationSunSeptember)
                            //std::cout << LocalHourAngleActual, AltitudeActual)

                            // Append parameters to lists
                            LocalHourAngleActual += 12;
                            LocalHourAngleActual = NormalizeZeroBounded(LocalHourAngleActual, 24);
                            LocalHourAngleSeptember.push_back(LocalHourAngleActual);
                            AltitudesSeptember.push_back(AltitudeActual);
                            AzimuthsSeptember.push_back(AzimuthActual);
                            ShadowsSeptember.push_back(ShadowsLengthActual);
                        }
                    }

                    // Sun's path on the Sky
                    /*plt.title("Sun's path on the Sky")
                    plt.plot(LocalHourAngleSummer, AltitudesSummer, '.', label="Summer Solstice")
                    plt.plot(LocalHourAngleWinter, AltitudesWinter, '.', label="Winter Solstice")
                    plt.plot(LocalHourAngleMarch, AltitudesMarch, '.', label="March Equinox")
                    plt.plot(LocalHourAngleSeptember, AltitudesSeptember, '.', label="Sept. Equinox")

                    plt.xlabel("Hours (h)")
                    plt.ylabel("Altitude of the Sun (°)")
                    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)
                    plt.grid()
                    plt.show()

                    plt.plot(AzimuthsSummer, AltitudesSummer, '.', label="Summer Solstice")
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
                    plt.show()
                    

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
                    plt.show()*/
                }
            }
        }


        //    ___              _                                
        //   / _ \            | |                               
        //  / /_\ \_ __   __ _| | ___ _ __ ___  _ __ ___   __ _ 
        //  |  _  | '_ \ / _` | |/ _ \ '_ ` _ \| '_ ` _ \ / _` |
        //  | | | | | | | (_| | |  __/ | | | | | | | | | | (_| |
        //  \_| |_/_| |_|\__,_|_|\___|_| |_| |_|_| |_| |_|\__,_|
        // Draw Sun Analemma at Choosen Location on Earth
        else if(mode.compare("7") == 0)
        {
            while(1)
            {
                std::cout << ">> Plot the Sun Analemma at Choosen Location on Earth\n";
                std::cout << ">> Please choose a mode you'd like to use!\n";
                std::cout << "(1) Parameters from User Input\n";
                std::cout << "(2) Parameters of Predefined Locations\n";
                std::cout << "(Q) Quit to Main Menu\n\n";
                
                std::string AnalemmaMode;
                std::cout << "> Choose a mode and press enter...: ";
                std::cin >> AnalemmaMode;
                std::cout << '\n';

                // Constants for calculation
                std::string Planet = "Earth";

                // Declare Variables
                std::string Location;
                double Latitude;
                double Longitude;

                double AnalemmaYear;

                double AltitudeActual;
                double LocalHourAngleActual;

                if(AnalemmaMode.compare("1") == 0)
                {
                    std::cout << ">> Plot Analemma on a User-defined Location\n";
                    std::cout << ">> Give Parameters!\n";

                    // Input Positional Parameters
                    std::cout << ">> HINT: You can write Latitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LatitudeHours;
                    double LatitudeMinutes;
                    double LatitudeSeconds;
                    
                    std::cout << "\n> Latitude (φ) Hours: ";
                    std::cin >> LatitudeHours;
                    std::cout << '\n';
                    std::cout << "> Latitude (φ) Minutes: ";
                    std::cin >> LatitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Latitude (φ) Seconds: ";
                    std::cin >> LatitudeSeconds;
                    std::cout << '\n';
                    Latitude = LatitudeHours + LatitudeMinutes/60 + LatitudeSeconds/3600;

                    std::cout << ">> HINT: You can write Longitude as a Decimal Fraction. For this you need to\n>> Write Hours as a float-type value, then you can\n>> Press Enter for both Minutes and Seconds.\n";
                    double LongitudeHours;
                    double LongitudeMinutes;
                    double LongitudeSeconds;
                    
                    std::cout << "\n> Longitude #1 (φ1) Hours: ";
                    std::cin >> LongitudeHours;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Minutes: ";
                    std::cin >> LongitudeMinutes;
                    std::cout << '\n';
                    std::cout << "> Longitude #1 (φ1) Seconds: ";
                    std::cin >> LongitudeSeconds;
                    std::cout << '\n';
                    Longitude = LongitudeHours + LongitudeMinutes/60 + LongitudeSeconds/3600;
                }

                else if(AnalemmaMode.compare("2") == 0)
                {
                    std::cout << ">> Plot Analemma on a Predefined Location's Coordinates";
                    std::cout << ">> Write the Name of a Choosen Location to the Input!";

                    // Input Choosen Location's Name
                    while(1)
                    {
                        std::cout << ">> Calculate Datetimes of Twilights from the Coordinates of a Predefined Location\n";
                        std::cout << ">> Write the Name of a Choosen Location to the Input!\n";

                        std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();

                        std::cout << "\n> Location's name (type \'H\' for Help): ";
                        std::cin >> Location;
                        std::cout << '\n';

                        if(Location.compare("Help") == 0 || Location.compare("help") == 0 || Location.compare("H") == 0 || Location.compare("h") == 0)
                        {
                            std::cout << ">> Predefined Locations you can choose from:\n";

                            for(auto Locations = LocationDict.cbegin(); Locations != LocationDict.cend(); ++Locations)
                            {
                                std::cout << Locations->first << ": " << Locations->second[0] << "N ; " << Locations->second[1] << "E" << '\n';
                            }

                            std::cout << '\n';
                        }

                        else
                        {
                            try
                            {
                                Latitude = LocationDict[Location][0];
                                Longitude = LocationDict[Location][1];
                            
                                auto LocationSearch = LocationDict.find(Location);
                                if(LocationSearch == LocationDict.end())
                                {
                                    throw Location;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            catch(std::string Location2)
                            {
                                std::cout << ">>>> ERROR: The Location, named \"" + Location + "\" is not in the Database!\n";
                                std::cout << ">>>> Type \"Help\" to list Available Cities in Database!\n";
                            }
                        }
                    }
                }

                else if(AnalemmaMode.compare("Q") == 0 || AnalemmaMode.compare("q") == 0)
                {
                    break;
                }

                else
                {
                    std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
                }


                if(AnalemmaMode.compare("1") == 0 || AnalemmaMode.compare("2") == 0)
                {
                    while(1)
                    {
                        std::cout << ">> For which Year would You like to Draw the Analemma?\n";
                        
                        std::cout << "> Choosen Year: ";
                        std::cin >> AnalemmaYear;
                        std::cout << '\n';

                        if(AnalemmaYear != 0)
                        {
                            break;
                        }

                        else
                        {
                            std::cout << ">>>> ERROR: Year 0 is not defined! Please write another date!\n";
                        }
                    }

                    std::vector<double> LocalHourAngleAnalemma = {};
                    std::vector<double> AltitudesAnalemma = {};

                    for(int LocalDateMonth = 1; LocalDateMonth < 13; LocalDateMonth++)
                    {
                        for(int LocalDateDay = 1; LocalDateDay < MonthLengthList[LocalDateMonth - 1] + 1; LocalDateDay++)
                        {
                            std::vector<double> SundialParametersCalcoutputVec = SunAnalemma(Planet, Latitude, Longitude, AnalemmaYear, LocalDateMonth, LocalDateDay);

                            AltitudeActual = SundialParametersCalcoutputVec[0];
                            LocalHourAngleActual = SundialParametersCalcoutputVec[1];

                            LocalHourAngleAnalemma.push_back(LocalHourAngleActual + 12);
                            AltitudesAnalemma.push_back(AltitudeActual);
                        }
                    }

                    // PLOT
                    // Shadow's length on the ground
                    /*if(AnalemmaMode.compare("1") == 0):
                        plt.title("Sun Analemma at Cordinates " + str(Latitude) + "; " + str(Longitude))

                    else if(AnalemmaMode.compare("2") == 0):
                        plt.title("Sun Analemma at " + Location)

                    plt.plot(LocalHourAngleAnalemma, AltitudesAnalemma, '.')

                    plt.xlabel("Hours (h)")
                    plt.ylabel("Altitude of Sun (°)")
                    plt.xlim((12.0,12.1))
                    plt.grid()
                    plt.show()*/
                }
            }
        }


        //   _   _                                         _    
        //  | | | |                                       | |   
        //  | |_| | ___  _ __ ___   _____      _____  _ __| | __
        //  |  _  |/ _ \| '_ ` _ \ / _ \ \ /\ / / _ \| '__| |/ /
        //  | | | | (_) | | | | | |  __/\ V  V / (_) | |  |   < 
        //  \_| |_/\___/|_| |_| |_|\___| \_/\_/ \___/|_|  |_|\_\
        // HOMEWORK MODE
        else if(mode.compare("Home") == 0 || mode.compare("home") == 0 || mode.compare("H") == 0 || mode.compare("h") == 0)
        {
            // Constant map for Locations and Stellar Objects
            std::map<std::string, std::vector<double>> LocationDict = LocationDictFunc();
            std::map<std::string, std::vector<double>> StellarDict = StellarDictFunc();
            std::vector<double> LocalSiderealTimeCalcoutputVec;

            // Constant variables for homework
            std::string Planet;
            std::string Star;
            std::string Location;
            double Latitude;
            double Longitude;
            double LocalDateYear;
            double LocalDateMonth;
            double LocalDateDay;
            double LocalHours;
            double LocalMinutes;
            double LocalSeconds;

            double LocalSiderealTime;
            double LocalSiderealHours;
            double LocalSiderealMinutes;
            double LocalSiderealSeconds;
            double UnitedHours;
            double UnitedMinutes;
            double UnitedSeconds;
            double GreenwichSiderealHours;
            double GreenwichSiderealMinutes;
            double GreenwichSiderealSeconds;

            double RightAscension;
            double Declination;
            double Altitude;
            double Azimuth;
            double LocalHourAngle;

            std::stringstream timemsg;
            std::stringstream grwmsg;

            std::stringstream sidermsg;
            std::stringstream hourangmsg;
            std::stringstream altitmsg;
            std::stringstream azimmsg;
            std::stringstream declinmsg;
            std::stringstream RAmsg;

            std::stringstream astrosetmsg;
            std::stringstream astrorisemsg;
            std::stringstream astrotimemsg;

            std::string timemsgstr;
            std::string grwmsgstr;
            std::string sidermsgstr;
            std::string azimmsgstr;


            std::cout << "//////  Csillesz II end-semester homework results, solved by the program  //////\n";
            std::cout << "_________________________________________________________________________\n\n";

            std::cout << "1.1/1.\n\n";

            Location = "Szombathely";
            Longitude = LocationDict[Location][1];
            LocalDateYear = 2017;
            LocalDateMonth = 12;
            LocalDateDay = 27;
            LocalHours = 14;
            LocalMinutes = 0;
            LocalSeconds = 0;

            LocalSiderealTimeCalcoutputVec = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, LocalDateYear, LocalDateMonth, LocalDateDay);
            LocalSiderealHours = LocalSiderealTimeCalcoutputVec[0];
            LocalSiderealMinutes = LocalSiderealTimeCalcoutputVec[1];
            LocalSiderealSeconds = LocalSiderealTimeCalcoutputVec[2];
            UnitedHours = LocalSiderealTimeCalcoutputVec[3];
            UnitedMinutes = LocalSiderealTimeCalcoutputVec[4];
            UnitedSeconds = LocalSiderealTimeCalcoutputVec[5];
            GreenwichSiderealHours = LocalSiderealTimeCalcoutputVec[6];
            GreenwichSiderealMinutes = LocalSiderealTimeCalcoutputVec[7];
            GreenwichSiderealSeconds = LocalSiderealTimeCalcoutputVec[8];

            std::cout << ">>> Calculate LMST at " << Location << ", at " << LocalHours << ":" << LocalMinutes << ":" << LocalSeconds << " LT, " << LocalDateYear << "." << LocalDateMonth << "." << LocalDateDay << '\n';
            std::cout << ">>> Used formulas:\n";
            std::cout << ">>> 1. S_0 (Greenwich Mean Sidereal Time) at 00:00 UT was calculated\n";
            std::cout << ">>> 2. S (Local Mean Sidereal Time) = S_0 + Longitude/15 + dS * UnitedTime\n\n";

            std::stringstream sidmsg;
            sidmsg << ">>> The Local Mean Sidereal Time at " << UnitedHours << ":" << UnitedMinutes << ":" << UnitedSeconds << " UT\n>>> in " << Location << " with\n>>> " << GreenwichSiderealHours << ":" << GreenwichSiderealMinutes << ":" << GreenwichSiderealSeconds << " GMST at 00:00:00 UT\n>>> is " << LocalSiderealHours << ":" << LocalSiderealMinutes << ":" << LocalSiderealSeconds;
            std::string sidmsgstr = sidmsg.str();
            std::cout << sidmsgstr << '\n';
            std::cout << "_________________________________________________________________________\n\n";

            std::cout << "1.1/2.\n\n";

            Location = "Szeged";
            Latitude = LocationDict[Location][0];
            double RightAscensionVenus = 18 + 41/60 + 54/3600;
            double DeclinationVenus = -(24 + 4/60 + 9/3600);
            std::vector<double> EquIToHoroutputVec = EquIToHor(Latitude, RightAscensionVenus, DeclinationVenus, 0, NULL, NULL);
            Altitude = EquIToHoroutputVec[0];
            double Azimuth1 = EquIToHoroutputVec[1];
            double Azimuth2 = EquIToHoroutputVec[2];
            double H_dil = EquIToHoroutputVec[3];

            std::cout << ">>> Calculate Rising and Setting Local Time of Venus,\n>>> As seen from " << Location << ".\n";
            std::cout << ">>> Used formulas:\n";
            std::cout << ">>> 1. First let's calculate LHA:\n>>> cos(H) = (sin(m) - sin(δ) * sin(φ)) / cos(δ) * cos(φ)\n";
            std::cout << ">>> 2. arccos(x) has two correct output on this interval.\n>>> One if them will be the Rising, the other is\n>>> The Setting Local Hour Angle: LHA2 = -LHA1\n";
            std::cout << ">>> 3. We calculate Azimuth for both Local Hour Angle.\n>>> For each one, we use 2 equations to determine the correct output:\n";
            std::cout << ">>> a) sin(A) = - sin(H) * cos(δ) / cos(m)\n>>> b) cos(A) = (sin(δ) - sin(φ) * sin(m)) / (cos(φ) * cos(m))\n";
            std::cout << ">>> These 2 equation outputs 2-2 values for an Azimuth. 1-1 from both these\n>>> Outputs will be equal, and that's the correct value for one of the Azimuths.\n";

            // Print Results
            std::cout << ">>> INFO: Available Data are only suited for Calculating Rising or\n>>> Setting Altitudes!\n";
            std::cout << "\n>>> Calculated Parameter of Rising/Setting Object in Horizontal Coord. Sys.:\n";

            azimmsg << "Rising and Setting Azimuths (A) are:\n>>> " << Azimuth1 << "° and " << Azimuth2 << "°";
            azimmsgstr = azimmsg.str();
            std::cout << azimmsgstr << '\n';
            
            timemsg << "Elapsed time between them: is " << H_dil/15 << "h";
            timemsgstr = timemsg.str();
            std::cout << timemsgstr << '\n';
            std::cout << "_________________________________________________________________________\n\n";

            std::cout << "1.1/3.\n";

            Planet = "Earth";
            Location = "Piszkesteto";
            Latitude = LocationDict[Location][0];
            Longitude = LocationDict[Location][1];
            LocalDateYear = 2018;
            LocalDateMonth = 12;
            double LocalDateDay1 = 21;
            double LocalDateDay2 = 22;

            std::vector<double> TwilightCalcvec1 = TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay);

            double LocalHoursRiseAstro1 = TwilightCalcvec1[48];
            double LocalMinutesRiseAstro1 = TwilightCalcvec1[49];
            double LocalSecondsRiseAstro1 = TwilightCalcvec1[50];
            double LocalDateYearSetAstro1 = TwilightCalcvec1[51];
            double LocalDateMonthSetAstro1 = TwilightCalcvec1[52];
            double LocalDateDaySetAstro1 = TwilightCalcvec1[53];
            double LocalHoursSetAstro1 = TwilightCalcvec1[54];
            double LocalMinutesSetAstro1 = TwilightCalcvec1[55];
            double LocalSecondsSetAstro1 = TwilightCalcvec1[56];
            double LocalDateYearRiseAstro1 = TwilightCalcvec1[57];
            double LocalDateMonthRiseAstro1 = TwilightCalcvec1[58];
            double LocalDateDayRiseAstro1 = TwilightCalcvec1[59];

            std::vector<double> TwilightCalcvec2 = TwilightCalc(Planet, Latitude, Longitude, LocalDateYear, LocalDateMonth, LocalDateDay2);

            double LocalHoursRiseAstro2 = TwilightCalcvec2[48];
            double LocalMinutesRiseAstro2 = TwilightCalcvec2[49];
            double LocalSecondsRiseAstro2 = TwilightCalcvec2[50];
            double LocalDateYearSetAstro2 = TwilightCalcvec2[51];
            double LocalDateMonthSetAstro2 = TwilightCalcvec2[52];
            double LocalDateDaySetAstro2 = TwilightCalcvec2[53];
            double LocalHoursSetAstro2 = TwilightCalcvec2[54];
            double LocalMinutesSetAstro2 = TwilightCalcvec2[55];
            double LocalSecondsSetAstro2 = TwilightCalcvec2[56];
            double LocalDateYearRiseAstro2 = TwilightCalcvec2[57];
            double LocalDateMonthRiseAstro2 = TwilightCalcvec2[58];
            double LocalDateDayRiseAstro2 = TwilightCalcvec2[59];


            double LocalDateDaySetAstroTime1 = LocalHoursSetAstro1 + LocalMinutesSetAstro1/60 + LocalSecondsSetAstro1/3600;
            double LocalDateDayRiseAstroTime2 = LocalHoursRiseAstro2 + LocalMinutesRiseAstro2/60 + LocalSecondsRiseAstro2/3600;

            std::cout << ">>> Calculate lenght of Astronomical Twilight at " << Location << " on\n>>> " << LocalDateYear << "." << LocalDateMonth << "." << LocalDateDay2 << " evening.\n";
            std::cout << ">>> Used formulas:\n";
            std::cout << ">>> 1. Sun's position for given day was calculated (RA and δ)\n";
            std::cout << ">>> 2. Julian Date of the Begind/End of Astrological Twilights\n>>> Was been calculated.\n";
            std::cout << ">>> 3. Julian Date was converted to United Time (UT), then Local Time (LT)\n>>> Was calculated for " << Location << "\n\n";

            astrosetmsg << ">>> End of Astronomical Twilight on " << LocalDateYear << "." << LocalDateMonth << "." << LocalDateDay1 << " is at " << LocalHoursSetAstro1 << ":" << LocalMinutesSetAstro1 << ":" << LocalSecondsSetAstro1;
            std::string astrosetmsgstr = astrosetmsg.str();
            std::cout << astrosetmsgstr << '\n';

            astrorisemsg << ">>> Begin of Astronomical Twilight on " << LocalDateYear << "." << LocalDateMonth << "." << LocalDateDay2 << " is at " << LocalHoursRiseAstro2 << ":" << LocalMinutesRiseAstro2 << ":" << LocalSecondsRiseAstro2;
            std::string astrorisemsgstr = astrorisemsg.str();
            std::cout << astrorisemsgstr << '\n';

            // Length of the astronomical night
            double AstroNightLength = 24 - (LocalDateDaySetAstroTime1 - LocalDateDayRiseAstroTime2);
            int AstroNightHours = int(AstroNightLength);
            int AstroNightMinutes = int((AstroNightLength - AstroNightHours) * 60);
            int AstroNightSeconds = int((((AstroNightLength - AstroNightHours) * 60) - AstroNightMinutes) * 60);

            astrotimemsg << ">>> The astronomical night's lenght at " << Location << " is " << AstroNightHours << ":" << AstroNightMinutes << ":" << AstroNightSeconds << " long\n>>> In the night, between " << LocalDateYear << "." << LocalDateMonth << "." << LocalDateDay1 << ", and " << LocalDateDay2 << ".";
            std::string astrotimemsgstr = astrotimemsg.str();
            std::cout << astrotimemsgstr << '\n';

            std::cout << "_________________________________________________________________________\n\n";

            std::cout << "1.2/1.\n";

            double aValue = 54.3666666;
            double bValue = 72.2;
            double cValue = 0;
            double alphaValue = 0;
            double betaValue = 0;
            double gammaValue = 94.01666666;

            std::vector<double> AstroTrianglesoutputVec = AstroTriangles(aValue, bValue, cValue, alphaValue, betaValue, gammaValue);
            aValue = AstroTrianglesoutputVec[0];
            bValue = AstroTrianglesoutputVec[1];
            cValue = AstroTrianglesoutputVec[2];
            alphaValue = AstroTrianglesoutputVec[3];
            betaValue = AstroTrianglesoutputVec[4];
            gammaValue = AstroTrianglesoutputVec[5];

            std::cout << ">>> Used formulas:\n";
            std::cout << ">>> The program uses formulas, which may be derived using vector algebra\n";
            std::cout << ">>> Given parameters: side \'A\', side \'B\' and angle \'γ\'\n";
            std::cout << ">>> C = arctan( sqrt(\n    (sin(A) * cos(B) - cos(A) * sin(B) * cos(γ))^2 + (sin(B) * sin(γ))^2 ) /\n    (cos(A) * cos(B) + sin(A) * sin(B) * cos(γ)) )\n";
            std::cout << ">>> α = arctan(\n    (sin(A) * sin(γ)) / (sin(B) * cos(A) - cos(B) * sin(A) * cos(γ))\n    )\n";
            std::cout << ">>> β = arctan(\n    (sin(B) * sin(γ)) / (sin(A) * cos(B) - cos(A) * sin(B) * cos(γ))\n    )\n\n";

            std::cout << ">>> Calculated Parameters of the Triangle:\n";
            std::cout << ">>> Side \'A\': " << aValue << '\n';
            std::cout << ">>> Side \'B\': " << bValue << '\n';
            std::cout << ">>> Side \'C\': " << cValue << '\n';
            std::cout << ">>> Angle \'α\': " << alphaValue << '\n';
            std::cout << ">>> Angle \'β\': " << betaValue << '\n';
            std::cout << ">>> Angle \'γ\': " << gammaValue << '\n';
            std::cout << "\n";

            std::cout << "_________________________________________________________________________\n\n";

            std::cout << "1.2/2.\n";

            Location = "Baja";
            Star = "Altair";
            Latitude = LocationDict[Location][0];
            Longitude = LocationDict[Location][1];
            RightAscension = StellarDict[Star][0];
            Declination = StellarDict[Star][1];
            Altitude = NULL;
            Azimuth = NULL;
            LocalHourAngle = NULL;
            LocalDateYear = 2013;
            LocalDateMonth = 6;
            LocalDateDay = 21;
            LocalHours = 20;
            LocalMinutes = 45;
            LocalSeconds = 0;

            // Calculate Local Mean Sidereal Time
            LocalSiderealTimeCalcoutputVec = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, LocalDateYear, LocalDateMonth, LocalDateDay);
            LocalSiderealHours = LocalSiderealTimeCalcoutputVec[0];
            LocalSiderealMinutes = LocalSiderealTimeCalcoutputVec[1];
            LocalSiderealSeconds = LocalSiderealTimeCalcoutputVec[2];
            UnitedHours = LocalSiderealTimeCalcoutputVec[3];
            UnitedMinutes = LocalSiderealTimeCalcoutputVec[4];
            UnitedSeconds = LocalSiderealTimeCalcoutputVec[5];
            GreenwichSiderealHours = LocalSiderealTimeCalcoutputVec[6];
            GreenwichSiderealMinutes = LocalSiderealTimeCalcoutputVec[7];
            GreenwichSiderealSeconds = LocalSiderealTimeCalcoutputVec[8];

            // Convert to decimal
            LocalSiderealTime = LocalSiderealHours + LocalSiderealMinutes/60 + LocalSiderealSeconds/3600;
            
            // Normalize result
            LocalSiderealTime = NormalizeZeroBounded(LocalSiderealTime, 24);

            std::vector<double> EquIIToHoroutputVec = EquIIToHor(Latitude, RightAscension, Declination, Altitude, Azimuth, LocalSiderealTime, LocalHourAngle);
            Altitude = EquIIToHoroutputVec[0];
            Azimuth = EquIIToHoroutputVec[1];

            // For printing this step too
            LocalHourAngle = LocalSiderealTime - RightAscension;
            // Normalize Result
            LocalHourAngle = NormalizeZeroBounded(LocalHourAngle, 24);

            std::cout << ">>> Used formulas:\n";
            std::cout << ">>> 1. S_0 (Greenwich Mean Sidereal Time) at 00:00 UT was calculated\n";
            std::cout << ">>> 2. S (Local Mean Sidereal Time) = S_0 + Longitude/15 + dS * UnitedTime\n";
            std::cout << ">>> 3. S - α = t; H = 15*t\n";
            std::cout << ">>> 4. sin(m) = sin(δ) * sin(φ) + cos(δ) * cos(φ) * cos(H);\n>>> Altitude (m) should been between [-π/2,+π/2]\n";
            std::cout << ">>> 5. sin(A) = - sin(H) * cos(δ) / cos(m), Azimuth at given H hour angle\n>>> Also cos(A) = (sin(δ) - sin(φ) sin(m)) / cos(φ) cos(m)\n";
            std::cout << ">>> These 2 equation outputs 2-2 values for Azimuth. 1-1 from both these\n>>> Outputs will be equal, and that's the correct value for Azimuth.\n\n";

            // Print Results
            timemsg << ">>> Altitude and Azimuth of " << Star << " from " << Location << " on " << LocalDateYear << "." << LocalDateMonth << "." << LocalDateDay;
            timemsgstr = timemsg.str();
            std::cout << timemsgstr << '\n';
            
            // Greenwich Mean Sidereal Time
            grwmsg << "- GMST (S_0): "  << GreenwichSiderealHours << "°" << GreenwichSiderealMinutes << "\'" << GreenwichSiderealSeconds << "\"";
            grwmsgstr = grwmsg.str();
            std::cout << grwmsgstr << '\n';

            std::cout << ">>> Calculated Parameters:\n";

            // Local Mean Sidereal Time
            sidermsg << "- Local Mean Sidereal Time (S): "  << LocalSiderealHours << "°" << LocalSiderealMinutes << "\'" << LocalSiderealSeconds << "\"";
            sidermsgstr = sidermsg.str();
            std::cout << sidermsgstr << '\n';

            // Local Hour Angle
            int LocalHourAngleHours = int(LocalHourAngle);
            int LocalHourAngleMinutes = int((LocalHourAngle - LocalHourAngleHours) * 60);
            int LocalHourAngleSeconds = int((((LocalHourAngle - LocalHourAngleHours) * 60) - LocalHourAngleMinutes) * 60);

            hourangmsg << "- Local Hour Angle (t): " << LocalHourAngleHours<< "h" << LocalHourAngleMinutes << "m" << LocalHourAngleSeconds << "s";
            std::string hourangmsgstr = hourangmsg.str();                    
            std::cout << hourangmsgstr << "\n\n";

            // Altitude
            int AltitudeHours = int(Altitude);
            int AltitudeMinutes = int((Altitude - AltitudeHours) * 60);
            int AltitudeSeconds = int((((Altitude - AltitudeHours) * 60) - AltitudeMinutes) * 60);

            altitmsg << "- Altitude (m): "<< AltitudeHours << "° " << AltitudeMinutes << "\' " << AltitudeSeconds << "\"";
            std::string altitmsgstr = altitmsg.str();
            std::cout << altitmsgstr << '\n';

            // Azimuth
            int AzimuthHours = int(Azimuth);
            int AzimuthMinutes = int((Azimuth - AzimuthHours) * 60);
            int AzimuthSeconds = int((((Azimuth - AzimuthHours) * 60) - AzimuthMinutes) * 60);

            azimmsg << "- Azimuth (A): "<< AzimuthHours << "° " << AzimuthMinutes << "\' " << AzimuthSeconds << "\"";
            azimmsgstr = azimmsg.str();
            std::cout << azimmsgstr << '\n';

            std::cout << "_________________________________________________________________________\n\n";

            std::cout << "1.2/3.\n";

            Location = "Rio";
            Latitude = LocationDict[Location][0];
            Longitude = LocationDict[Location][1];

            Altitude = 55.656388;
            Azimuth = 208.113611;

            LocalDateYear = 2018;
            LocalDateMonth = 4;
            LocalDateDay = 17;
            LocalHours = 20;
            LocalMinutes = 34;
            LocalSeconds = 53;

            LocalSiderealTimeCalcoutputVec = LocalSiderealTimeCalc(Longitude, LocalHours, LocalMinutes, LocalSeconds, LocalDateYear, LocalDateMonth, LocalDateDay);
            LocalSiderealHours = LocalSiderealTimeCalcoutputVec[0];
            LocalSiderealMinutes = LocalSiderealTimeCalcoutputVec[1];
            LocalSiderealSeconds = LocalSiderealTimeCalcoutputVec[2];
            UnitedHours = LocalSiderealTimeCalcoutputVec[3];
            UnitedMinutes = LocalSiderealTimeCalcoutputVec[4];
            UnitedSeconds = LocalSiderealTimeCalcoutputVec[5];
            GreenwichSiderealHours = LocalSiderealTimeCalcoutputVec[6];
            GreenwichSiderealMinutes = LocalSiderealTimeCalcoutputVec[7];
            GreenwichSiderealSeconds = LocalSiderealTimeCalcoutputVec[8];
            
            // Convert to decimal
            LocalSiderealTime = LocalSiderealHours + LocalSiderealMinutes/60 + LocalSiderealSeconds/3600;
            
            // Normalize result
            LocalSiderealTime = NormalizeZeroBounded(LocalSiderealTime, 24);

            std::vector<double> HorToEquIIoutputVec = HorToEquII(Latitude, Altitude, Azimuth, LocalSiderealTime);
            RightAscension = HorToEquIIoutputVec[0];
            Declination = HorToEquIIoutputVec[1];
            LocalSiderealTime = HorToEquIIoutputVec[2];

            std::cout << "Calculate a star's equatorial II coordinates (S and δ) from Horizontal coords.\n";
            std::cout << "Used Formulas:\n";
            std::cout << ">>> 1. S_0 (Greenwich Mean Sidereal Time) at 00:00 UT was calculated\n";
            std::cout << ">>> 2. S (Local Mean Sidereal Time) = S_0 + Longitude/15 + dS * UnitedTime\n";
            std::cout << ">>> 3. Declination was calculated:\n>>> sin(δ) = sin(m) * sin(φ) + cos(m) * cos(φ) * cos(A)\n";
            std::cout << ">>> 4. Local Hour Angle was calculated with two equations:\n>>> a) sin(H) = - sin(A) * cos(m) / cos(δ)\n>>> b) cos(H) = (sin(m) - sin(δ) * sin(φ)) / cos(δ) * cos(φ)\n";
            std::cout << ">>> These 2 equations outputs 2-2 values for Local Hour Angle. 1-1 from both\n>>> These outputs will be equal, and that's the correct value for LHA.\n";
            std::cout << ">>> 5. Right Ascension was also calculated: RA = S - t; t = 15 * H\n\n";

            std::cout << ">>> Initial Coordinates:\n";
            std::cout << ">>> Azimuth: " << Azimuth;
            std::cout << ">>> Altitude: " << Altitude;

            std::stringstream equIImsg;
            equIImsg << "\n>>> Calculated Parameters of the Star in Equatorial II Coord. Sys. from " << Location << ":";
            std::string equIImsgstr = equIImsg.str();
            std::cout << equIImsgstr << '\n';

            // Greenwich Mean Sidereal Time
            grwmsg << "- GMST (S_0): "  << GreenwichSiderealHours << "°" << GreenwichSiderealMinutes << "\'" << GreenwichSiderealSeconds << "\"";
            grwmsgstr = grwmsg.str();
            std::cout << grwmsgstr << '\n';
            
            // Declination
            int DeclinationHours = int(Declination);
            int DeclinationMinutes = int((Declination - DeclinationHours) * 60);
            int DeclinationSeconds = int((((Declination - DeclinationHours) * 60) - DeclinationMinutes) * 60);

            declinmsg << "- Declination (δ): " << DeclinationHours << "°" << DeclinationMinutes << "\'" << DeclinationSeconds << "\"";
            std::string declinmsgstr = declinmsg.str();
            std::cout << declinmsgstr << '\n';
            
            // Right Ascension
            int RightAscensionHours = int(RightAscension);
            int RightAscensionMinutes = int((RightAscension - RightAscensionHours) * 60);
            int RightAscensionSeconds = int((((RightAscension - RightAscensionHours) * 60) - RightAscensionMinutes) * 60);

            RAmsg << "- Right Ascension (α): " << RightAscensionHours << "h" << RightAscensionMinutes << "m" << RightAscensionSeconds << "s";
            std::string RAmsgstr = RAmsg.str();
            std::cout << RAmsgstr << '\n';
            
            // Local Mean Sidereal Time
            sidermsg << "- Local Mean Sidereal Time (S): "  << LocalSiderealHours << "°" << LocalSiderealMinutes << "\'" << LocalSiderealSeconds << "\"";
            sidermsgstr = sidermsg.str();
            std::cout << sidermsgstr << '\n';

            std::cout << "_________________________________________________________________________\n\n";

            std::cout << "1.3\n\n";

            std::cout << ">>> For the Sundial, do the following:\n";
            std::cout << ">>> 1. Choose mode \'6\'\n";
            std::cout << ">>> 2. Choose eg. Predefined Locations with option \'2\'";
            std::cout << ">>> 3. Write eg. \'Budapest\'\n";
            std::cout << ">>> 4. Year = 2018\n";
            std::cout << ">>> 5. Select \'N\' for \'Choosen Date\'\n";
            std::cout << ">>> The graph shows the Sun's path on the sky at daylight, which will be\n>>> Projected on the ground, eg. on a Sundial.\n";
            std::cout << ">>> It also shows, that shadows are longer in Winter, and\n>>> Shorter in Summer. In March and September, the shadows'\n>>> Length are in-between these two.\n\n";
        }

        // MAIN MENU MODE
        // QUIT PROGRAM
        else if(mode.compare("Q") == 0 || mode.compare("q") == 0)
        {
            std::cout << "////////    Developed by Balazs Pal, ELTE    ////////";
            exit(0);
        }

        else
        {
            std::cout << ">>>> ERROR: Invalid option! Try Again!\n";
        }
    }
}