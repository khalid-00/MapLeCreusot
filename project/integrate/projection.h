/*
Use code from libosmium projection.hpp fast projection
*/

#ifndef PROJECTION_H
#define PROJECTION_H
#include <Qt>
#include <QPoint>
#include <math.h>


inline constexpr double deg_to_rad(double degree) noexcept;

constexpr inline double lon_to_x(double lon) noexcept;

inline double lat_to_y_with_tan(double lat);

inline double lat_to_y(double lat);

QPointF projection(double lon, double lat);

#endif // PROJECTION_H
