#include "geosystemconverter.h"
#include "math.h"
const double ro = 206264.8062; /* Число угловых секунд в радиане */

/* Эллипсоид Красовского */
const double aP = 6378245; /* Большая полуось */
const double alP = 1 / 298.3; /* Сжатие */
const double e2P = 2 * alP - pow(alP, 2); /* Квадрат эксцентриситета */

/*
 * Эллипсоид WGS84
 */
const double aW = 6378137; // Большая полуось
const double alW = 1 / 298.257223563; // Сжатие
const double e2W = 2 * alW - pow(alW, 2); // Квадрат эксцентриситета

/* Вспомогательные значения для преобразования эллипсоидов */
const double a_dop = (aP + aW) / 2;
const double e2 = (e2P + e2W) / 2;
const double da = aW - aP;

const double de2 = e2W - e2P;

/* Линейные элементы трансформирования, в метрах */

const double dx = 24;
const double dy = -141;
const double dz = -81;

/* Угловые элементы трансформирования, в секундах */
const double wx = 0;
const double wy = -0.35;
const double wz = -0.82;

/* Дифференциальное различие масштабов */
const double ms = 0;

/*Константы для перевода с СК-42 в прямоугольные и обратно*/
const double a1 = 6367558;
const double a2 = 16036.5;
const double a3 = 16.8;
const double a = 6378245;
const double b = 0.006693422;
const double c = 0.006738525;

double GEOSystemConverter::dB(double Bd, double Ld, double H) {

    double B = Bd * M_PI / 180;
    double L = Ld * M_PI / 180;
    double M = a_dop * (1 - e2)
            / pow((1 - e2 * pow(sin(B), 2)), 1.5);
    double N = a_dop * pow((1 - e2 * pow(sin(B), 2)), -0.5);
    return ro
            / (M + H)
            * (N / a_dop * e2 * sin(B) * cos(B) * da
               + (pow(N, 2) / pow(a_dop, 2) + 1) * N
               * sin(B) * cos(B) * de2 / 2
               - (dx * cos(L) + dy * sin(L)) * sin(B) + dz
               * cos(B)) - wx * sin(L)
            * (1 + e2 * cos(2 * B)) + wy * cos(L)
            * (1 + e2 * cos(2 * B)) - ro * ms * e2 * sin(B)
            * cos(B);
}

double GEOSystemConverter::dL(double Bd, double Ld, double H) {
    double B = Bd *M_PI / 180;
    double L = Ld *M_PI / 180;
    double N = a_dop * pow((1 - e2 * pow(sin(B), 2)), -0.5);
    return ro / ((N + H) * cos(B))
            * (-dx * sin(L) + dy * cos(L)) + tan(B)
            * (1 - e2) * (wx * cos(L) + wy * sin(L)) - wz;
}

GEOPos GEOSystemConverter::WGS84_TO_SK42(GEOPos WGS84){
    GEOPos pos;
    //Широта
    pos.latitude = WGS84.latitude - dB(WGS84.latitude, WGS84.longitude, WGS84.height) / 3600;
    //Долгота
    pos.longitude = WGS84.longitude - dL(WGS84.latitude, WGS84.longitude, WGS84.height) / 3600;
    //Висота
    double B = WGS84.latitude *M_PI / 180;
    double L = WGS84.longitude *M_PI / 180;
    double N = a_dop * pow((1 - e2 * pow(sin(B), 2)), -0.5);
    double dH = -a_dop / N * da + N * pow(sin(B), 2) * de2 / 2
            + (dx * cos(L) + dy * sin(L)) * cos(B) + dz
            * sin(B) - N * e2 * sin(B) * cos(B)
            * (wx / ro * sin(L) - wy / ro * cos(L))
            + (pow(a_dop, 2) / N + WGS84.height) * ms;
    pos.height = WGS84.height - dH;
    pos.latitude_p=WGS84.latitude_p;
    pos.longitude_p=WGS84.longitude_p;
    return pos;
}

GEOPos GEOSystemConverter::SK42_TO_WGS84(GEOPos SK42){
    GEOPos pos;
    pos.latitude = SK42.latitude + dB(SK42.latitude, SK42.longitude, SK42.height) / 3600;
    pos.longitude = SK42.longitude + dL(SK42.latitude, SK42.longitude, SK42.height) / 3600;
    double B = SK42.latitude *M_PI / 180;
    double L = SK42.longitude *M_PI / 180;
    double N = a_dop * pow((1 - e2 * pow(sin(B), 2)), -0.5);
    double dH = -a_dop / N * da + N * pow(sin(B), 2) * de2 / 2
            + (dx * cos(L) + dy * sin(L)) * cos(B) + dz
            * sin(B) - N * e2 * sin(B) * cos(B)
            * (wx / ro * sin(L) - wy / ro * cos(L))
            + (pow(a_dop, 2) / N + SK42.height) * ms;
    pos.height = SK42.height + dH;
    pos.latitude_p=SK42.latitude_p;
    pos.longitude_p=SK42.longitude_p;
    return pos;
}

DMCSystem GEOSystemConverter::Decimal_TO_DMC(double decimal_system){
    double dfFrac; // fraction after decimal
    double dfSec; // fraction converted to seconds
    DMCSystem result;
    result.degrees = (int)(decimal_system);
    dfFrac = decimal_system - result.degrees;
    dfSec = dfFrac * 3600;
    result.minutes = (int)(dfSec / 60);
    result.seconds = dfSec - result.minutes * 60;
    return result;
}

double GEOSystemConverter::DMC_TO_Decimal(DMCSystem DMC){
    double result;
    double dfFrac;
    dfFrac = DMC.minutes / 60 + DMC.seconds / 3600;

    if (DMC.degrees < 0)
        result = DMC.degrees - dfFrac;
    else
        result = DMC.degrees + dfFrac;
    return result;
}

SquareSystem GEOSystemConverter::SK42_TO_SQUARE(GEOPos SK_42) {
    SquareSystem result;
    double B, L, N, X1, L0;
    int Nz, L1;
    B = SK_42.latitude;
    L = SK_42.longitude;
    B = B * M_PI / 180;
    //L = L * M_PI / 180;
    N = a / (sqrt(1 - c * sin(B) * sin(B)));
    X1 = a1 * B - a2 * sin(2 * B) + a3 * sin(4 * B);
    Nz = (int) (L / 6 + 1);
    L1 = 6 * Nz - 3;
    L0 = (L - L1) * (M_PI / 180);
    result.X = (int) (X1 + L0
                      * L0
                      / 2
                      * N
                      * sin(B)
                      * cos(B)
                      * (1 + L0
                         * L0
                         / 12
                         * cos(B)
                         * cos(B)
                         * ((5 - tan(B) * tan(B) + 9 * c * cos(B)
                             * cos(B)) + L0
                            * L0
                            / 30
                            * cos(B)
                            * cos(B)
                            * (61 + tan(B) * tan(B) * tan(B)
                               * tan(B) - 58 * tan(B)
                               * tan(B)))));
    result.Y = (int) (L0
                      * N
                      * cos(B)
                      * (1 + L0
                         * L0
                         / 6
                         * cos(B)
                         * cos(B)
                         * ((1 + c * cos(B) * cos(B) - tan(B)
                             * tan(B)) + L0
                            * L0
                            / 20
                            * cos(B)
                            * cos(B)
                            * (5 + tan(B) * tan(B) * tan(B)
                               * tan(B) - 18 * tan(B)
                               * tan(B)))) + 500000);
    result.Y = result.Y + Nz* 1000000;
    return result;
}

GEOPos GEOSystemConverter::SQUARE_TO_SK42(SquareSystem pos) {
    GEOPos result;
    int i = 1, Yo, n = 0, Y_bez_zoni;
    double B, C, Br, Lo, Lr;
    double Bo[3];
    Bo[i] = pos.X / a1;
    i++;
    Bo[i] = Bo[i - 1] + (a2 * sin(2 * Bo[i - 1])/a1) - (a3 * sin(4 * Bo[i - 1])/a1);
    while (!(abs(Bo[i] - Bo[i - 1]) <= 0.00000001)) {
        i++;
        Bo[i] = Bo[i - 1] + (a2 * sin(2 * Bo[i - 1])/a1) - (a3 * sin(4 * Bo[i - 1])/a1);
    }
    B = Bo[i];
    Y_bez_zoni = pos.Y - ((int) pos.Y / 1000000) * 1000000;
    Yo = Y_bez_zoni - 500000;
    C = Yo /a *( sqrt(1 - b * sin(B) * sin(B)));
    Br = B
            - (C * C)
            / 2 * tan(B) * (1 + c * cos(B) * cos(B)) * (1 - C
                                                        * C
                                                        / 12
                                                        * ((5 + 3 * tan(B) * tan(B) + c
                                                            * cos(B) * cos(B) - 9 * c
                                                            * sin(B) * sin(B)) - C
                                                           * C
                                                           / 30
                                                           * (61 + 90 * tan(B) * tan(B) + 45
                                                              * tan(B) * tan(B)
                                                              * tan(B) * tan(B))));
    Lo = C
            / cos(B)
            * (1 - C
               * C
               / 6
               * ((1 + c * cos(B) * cos(B) + 2 * tan(B)
                   * tan(B)) - C
                  * C
                  / 20
                  * (6 + 25 * tan(B) * tan(B) + 24
                     * tan(B) * tan(B)
                     * tan(B) * tan(B))));
    n = pos.Y / 1000000;
    Lr = n * M_PI / 30 - M_PI / 60 + Lo;
    result.latitude = Br / M_PI * 180;
    result.longitude = Lr / M_PI * 180;
    return result;
}

int GEOSystemConverter::calculateDistance(SquareSystem posA, SquareSystem posB)
{
    double k = pow((double)(posA.X-posB.X),2)+pow((double)(posA.Y-posB.Y),2);
    k = pow(k ,0.5);
    int b = k;
    return b;
}


double GEOSystemConverter::calculateAngle(SquareSystem posA, SquareSystem posB)
{
//    if (checkZZ(yA, yB) == true)
//    {
//        converZZ(xA, yA, xB, yB);
//        xA = getNew_xA();
//        yA = getNew_yA();
//    }

    //Если Y будут в разных зонах то надо переписать эту функцию
    double Ya = dropZoneY(posA.Y);
    double Yb = dropZoneY(posB.Y);
    double alpha;
    double ro1;
    double dX = posA.X-posB.X;
    double dY = Ya-Yb;
    if (dX == 0)
    {
        if (abs(Yb) > abs(Ya))
        {
            alpha = (double)15.00;
        }
        else {
            alpha = (double)45.00;
        }
    }
    else ro1 = atan(dY/dX) * 9.5493;
    if (dX < 0)
    {
        alpha = 30 + ro1;
    }
    else if (dX > 0)
    {
        if (ro1 < 0)
        {
            alpha = 60 + ro1;
        }
        else
        {
            alpha = ro1;
        }
    }
    return alpha;
}

int GEOSystemConverter::dropZoneY(int y)
{
    double temp = (double)y / 1000000;
    y = temp - y / 1000000;
    temp *= 1000000;
    y = temp;
    return y;
}

QString GEOSystemConverter::Angle_To_String(double Angle) {
    QString result = QString::number((int)Angle);
    double temp = Angle - (int)Angle;
    QString tempS = QString::number((int)(temp * 100));
    if (tempS.length()==1)tempS="0"+tempS;
    result= result+"-"+tempS;
    return result;
}
