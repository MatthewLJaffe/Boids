#include "Vector2.hpp"

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    Vector2 returnVector(v1.x + v2.x, v1.y + v2.y);
    return returnVector;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    Vector2 returnVector(v1.x - v2.x, v1.y - v2.y);
    return returnVector;
}

Vector2 operator*(const Vector2& v1, const Vector2& v2)
{
    Vector2 returnVector(v1.x * v2.x, v1.y * v2.y);
    return returnVector;
}

Vector2 operator*(const Vector2& v1, const float scalar)
{
    Vector2 returnVector(v1.x * scalar, v1.y * scalar);
    return returnVector;
}

Vector2 operator/(const Vector2& v1, const Vector2& v2)
{
    Vector2 returnVector(v1.x / v2.x, v1.y / v2.y);
    return returnVector;
}

Vector2 operator/(const Vector2& v1, const float scalar)
{
    Vector2 returnVector(v1.x / scalar, v1.y / scalar);
    return returnVector;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& v)
{
    this->x *= v.x;
    this->y *= v.y;
    return *this;
}

Vector2& Vector2::operator*=(const float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}


Vector2& Vector2::operator/=(const Vector2& v)
{
    this->x /= v.x;
    this->y /= v.y;
    return *this;
}

Vector2& Vector2::operator/=(const float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
    return stream << "(" << vec.x << "," << vec.y << ")";
}

float Vector2::distance(Vector2 otherV)
{
    return (sqrtf(powf(this->x - otherV.x, 2) + powf(this->y - otherV.y, 2)));
}

float Vector2::mag()
{
    return sqrtf(this->x * this->x + this->y * this->y);
}

void Vector2::normalize()
{
    float mag = this->mag();
    if (mag < 0.00001) return;
    this->x /= mag;
    this->y /= mag;
}

Vector2 Vector2::normalized()
{
    Vector2 norm = Vector2(x, y);
    float mag = this->mag();
    if (mag < 0.00001) return norm;
    norm.x /= mag;
    norm.y /= mag;
    return norm;
}

Vector2 Vector2::rotate(double theta)
{
    Vector2 rotated;
    theta *= 3.141592653 / 180;
    rotated.x = cos(theta) * this->x - sin(theta) * this->y;
    rotated.y = sin(theta) * this->x + cos(theta) * this->y;
    return rotated;
}

float Vector2::angleBetween(Vector2 otherV)
{
    float angle =  180 / 3.141592653 * (atan2f(otherV.y, otherV.x) - atan2f(this->y, this->x));
    if (angle < 0)
        angle += 360;
    return angle;
}
