#ifndef GEOSYSTEMCONVERTER_H
#define GEOSYSTEMCONVERTER_H
#include <QString>
struct GEOPos{
    double latitude;
    QString latitude_p;
    double longitude;
    QString longitude_p;
    double height;
};

struct DMCSystem{
    double degrees;
    double minutes;
    double seconds;
};

struct SquareSystem{
    int X;
    int Y;
};

class GEOSystemConverter
{
private:
    static double dB(double Bd, double Ld, double H);
    static double dL(double Bd, double Ld, double H);
    static int dropZoneY(int y);
public:
    static GEOPos WGS84_TO_SK42(GEOPos WGS84);
    static GEOPos SK42_TO_WGS84(GEOPos SK42);
    static DMCSystem Decimal_TO_DMC(double decimal_system);
    static double DMC_TO_Decimal(DMCSystem DMC);
    static SquareSystem SK42_TO_SQUARE(GEOPos SK42);
    static GEOPos SQUARE_TO_SK42(SquareSystem);
    static int calculateDistance(SquareSystem posA, SquareSystem posB);
    static double calculateAngle(SquareSystem posA, SquareSystem posB);
    static QString Angle_To_String(double Angle);
};

#endif // GEOSYSTEMCONVERTER_H
