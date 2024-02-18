#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#pragma once

class Vector2{
  public:
    float x;
    float y;

    Vector2(){

    };
    Vector2(float x, float y) : x(x), y(y){

    };
    ~Vector2(){

    };

    Vector2& Add(const Vector2& v);
    Vector2& Subtract(const Vector2& v);
    Vector2& Multiply(const Vector2& v);
    Vector2& Multiply(const float& num);
    Vector2& Divide(const float& num);
    Vector2& Zero();

    friend Vector2& operator+(Vector2& left, const Vector2& right);
    friend Vector2& operator-(Vector2& left, const Vector2& right);
    friend Vector2& operator*(Vector2& left, const Vector2& right);
    friend Vector2& operator*(Vector2& left, const float& right);
    friend Vector2& operator/(Vector2& left, const float& right);

    Vector2& operator+=(const Vector2& vec);
    Vector2& operator-=(const Vector2& vec);
    Vector2& operator*=(const Vector2& vec);
    Vector2& operator*=(const float& num);
    Vector2& operator/=(const float& num);

    float squareOfDistance(const Vector2& v1, const Vector2& v2){
      return (v2.x-v1.x)*(v2.x-v1.x) + (v2.y-v1.y)*(v2.y-v1.y);
    }
};


#endif