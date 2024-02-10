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


Vector2& operator+(Vector2& left, const Vector2& right){
  return left.Add(right);
}

Vector2& operator-(Vector2& left, const Vector2& right){
  return left.Subtract(right);
}

Vector2& operator*(Vector2& left, const Vector2& right){
  return left.Multiply(right);
}

Vector2& operator*(Vector2& left, const float& right){
  return left.Multiply(right);
}

Vector2& operator/(Vector2& left, const float& right){
  return left.Divide(right);
}

Vector2& Vector2::operator+=(const Vector2& vec){
  return this->Add(vec);
}

Vector2& Vector2::operator-=(const Vector2& vec){
  return this->Subtract(vec);
}

Vector2& Vector2::operator*=(const Vector2& vec){
  return this->Multiply(vec);
}

Vector2& Vector2::operator*=(const float& num){
  return this->Multiply(num);
}

Vector2& Vector2::operator/=(const float& num){
  return this->Divide(num);
}
