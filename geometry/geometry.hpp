#pragma once

#include <iostream>
#include <valarray>
#include <vector>

struct Coord {
  Coord();
  int64_t x;
  int64_t y;
  Coord(const int64_t& ptx, const int64_t& pty);
};

class Vector {
 public:
  Vector();
  Vector(const Vector& other);
  Vector(int64_t ptx, int64_t pty);
  Vector(const Coord& pta, const Coord& ptb);
  Vector(const Coord& messi);
  friend int64_t operator*(const Vector& pta, const Vector& ptb);
  friend int64_t operator^(const Vector& pta, const Vector& ptb);
  Vector& operator+=(const Vector& other);
  Vector& operator-=(const Vector& other);
  Vector& operator*=(const int64_t& num);
  Vector& operator-();
  int64_t GetX() const;
  int64_t& GetX();
  int64_t GetY() const;
  int64_t& GetY();

 private:
  Coord vec_;
};

int64_t operator*(const Vector& pta, const Vector& ptb);
int64_t operator^(const Vector& pta, const Vector& ptb);
Vector operator+(const Vector& pta, const Vector& ptb);
Vector operator-(const Vector& pta, const Vector& ptb);
Vector operator*(const int64_t& num, const Vector& vec);
Vector operator*(const Vector& vec, const int64_t& num);

class Segment;
class Point;

class IShape {
 public:
  virtual void Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) = 0;
  virtual bool CrossSegment(const Segment&) = 0;
  virtual IShape* Clone() = 0;
  virtual ~IShape() = default;
};

class Point : public IShape {
 public:
  Point();
  Point(const int64_t& ptx, const int64_t& pty);
  int64_t GetX() const;
  int64_t& GetX();
  int64_t GetY() const;
  int64_t& GetY();
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& ptc) override;
  bool CrossSegment(const Segment& seg) override;
  IShape* Clone() override;
  Vector operator-(const Point& messi);

 private:
  Coord pt_;
};

class Segment : public IShape {
 public:
  Segment();
  Segment(const Point& beg, const Point& end);
  Point GetA() const;
  Point GetB() const;
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& ptc) override;
  bool CrossSegment(const Segment& seg) override;
  IShape* Clone() override;

 private:
  Point beg_;
  Point end_;
};

class Line : public IShape {
 public:
  Line();
  Line(const Point& beg, const Point& end);
  int64_t GetA() const;
  int64_t GetB() const;
  int64_t GetC() const;
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& ptc) override;
  bool CrossSegment(const Segment& seg) override;
  IShape* Clone() override;

 private:
  Point beg_;
  Point end_;
};

class Ray : public IShape {
 public:
  Ray();
  Ray(const Point& beg, const Point& end);
  Point& GetA();
  Vector GetVector();
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& ptc) override;
  bool CrossSegment(const Segment& seg) override;
  IShape* Clone() override;

 private:
  Point beg_;
  Point end_;
};

class Circle : public IShape {
 public:
  Circle();
  Circle(const Point& ptc, size_t& rad);
  Point& GetCentre();
  size_t& GetRadius();
  void Move(const Vector& vec) override;
  bool ContainsPoint(const Point& ptc) override;
  bool CrossSegment(const Segment& seg) override;
  IShape* Clone() override;

 private:
  Point pt_;
  size_t rad_;
};
