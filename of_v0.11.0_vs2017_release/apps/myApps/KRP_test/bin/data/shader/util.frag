#define HALF_PI 1.57079632679
#define PI 3.14159265358979323846
#define TWO_PI 6.28318530717958647693
#define DEG_TO_RAD (PI/180.0)
#define RAD_TO_DEG (180.0/PI)

float map(float value, float min1, float max1, float min2, float max2)
{
    float perc = (value - min1) / (max1 - min1);
    return perc * (max2 - min2) + min2;
}

vec2 latlon2xy(float lon, float lat, float lon_center, float lat_center, float R)
{
    float k = (2.0 * R) / (1.0 + sin(lat_center) * sin(lat) + cos(lat_center) * cos(lat) * cos(lon - lon_center));
    float x = -k * cos(lat) * sin(lon - lon_center);
    float y = -k * (cos(lat_center) * sin(lat) - sin(lat_center) * cos(lat) * cos(lon - lon_center));
    return vec2(x, y);
}

vec2 xy2lonlat(float x, float y, float lon_center, float lat_center, float R)
{
    float x2 = x;
    float y2 = y;
    x2 *= -1;
    y2 *= -1;
    float rho = sqrt(x2 * x2 + y2 * y2);
    float c = 2 * atan(rho / (2 * R));
    float tanX = rho * cos(lat_center) * cos(c) - y2 * sin(lat_center) * sin(c);
    float tanY = x2 * sin(c);

    float lon = RAD_TO_DEG * lon_center + RAD_TO_DEG * atan(tanY / tanX);
    float lat = RAD_TO_DEG * (asin(cos(c) * sin(lat_center) + y2 * sin(c) * cos(lat_center) / rho));
        
    if(tanX < 0)
    {
        lon += 180;
    }
    else if(tanX >= 0 && tanY < 0)
    {
        lon += 360;
    }

    if(lon >= 360)
    {
        lon -= 360;
    }
    
    return vec2(lon, lat);
}
