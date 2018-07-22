#include <math.h>

/*****************************************************************************/
int getMultiplied(int a, int b, int c)
{
  return (a * b * c);
}

/*****************************************************************************/
double get_julian_date(int year, int month, int day, double UT)
{
	double locJD, a, b, c, d, e, f, g;
	a = modf((month + 9)/12, &b);
	a = modf((7 * (year + b))/4, &c);
	a = modf((275 * month)/9, &d);
	e = 367 * year - c + d + day + 1721013.5 + UT/24;
	f = (100 * year + month - 190002.5);
	g = f/fabs(f);
	locJD = e - 0.5 * g + 0.5;
  return (locJD);
}
