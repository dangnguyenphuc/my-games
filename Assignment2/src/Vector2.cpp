#include "../include/Vector2.hpp"

Vector2& Vector2::Add(const Vector2& v){
  this->x += v.x;
  this->y += v.y;
  return *this;
}
Vector2& Vector2::Subtract(const Vector2& v){
  this->x -= v.x;
  this->y -= v.y;
  return *this;
}

Vector2& Vector2::Multiply(const Vector2& v){
  this->x *= v.x;
  this->y *= v.y;
  return *this;
}

Vector2& Vector2::Multiply(const float& num){
  this->x *= num;
  this->y *= num;
  return *this;
}

Vector2& Vector2::Divide(const float& num){
  this->x /= num;
  this->y /= num;
  return *this;
}

Vector2& Vector2::Zero(){
  this->x = 0.0f;
  this->y = 0.0f;
  return *this;
}


Vector2 operator+(Vector2& left, const Vector2& right){
  Vector2 res;
  res.x = left.x + right.x;
  res.y = left.y + right.y;
  return res;
}

Vector2 operator-(Vector2& left, const Vector2& right){
  Vector2 res;
  res.x = left.x - right.x;
  res.y = left.y - right.y;
  return res;
}

float operator*(Vector2& left, const Vector2& right){
  float x = left.x * right.x;
  float y = left.y * right.y;
  return x+y;
}

Vector2 operator*(Vector2& left, const float& right){
  Vector2 res;
  res.x = left.x * right;
  res.y = left.y * right;
  return res;
}

Vector2 operator/(Vector2& left, const float& right){
  Vector2 res;
  res.x = left.x / right;
  res.y = left.y / right;
  return res;
}

Vector2& Vector2::operator+=(const Vector2& vec){
  return this->Add(vec);
}

Vector2& Vector2::operator-=(const Vector2& vec){
  return this->Subtract(vec);
}

Vector2& Vector2::operator*=(const float& num){
  return this->Multiply(num);
}

Vector2& Vector2::operator/=(const float& num){
  return this->Divide(num);
}
