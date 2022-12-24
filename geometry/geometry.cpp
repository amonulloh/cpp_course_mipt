#include "geometry.hpp"

Coord::Coord() = default;
Coord::Coord(const int64_t& ptx, const int64_t& pty) : x(ptx), y(pty) {}

Vector::Vector() {
  vec_.x = 0;
  vec_.y = 0;
}

Vector::Vector(const Vector& other) {
  vec_.x = other.vec_.x;
  vec_.y = other.vec_.y;
}

Vector::Vector(int64_t ptx, int64_t pty) {
  vec_.x = ptx;
  vec_.y = pty;
}

Vector::Vector(const Coord& pta, const Coord& ptb) {
  vec_.x = ptb.x - pta.x;
  vec_.y = ptb.y - pta.y;
}

Vector::Vector(const Coord& messi) : vec_(messi) {}

Vector& Vector::operator+=(const Vector& other) {
  vec_.x += other.vec_.x;
  vec_.y += other.vec_.y;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  vec_.x -= other.vec_.x;
  vec_.y -= other.vec_.y;
  return *this;
}

Vector& Vector::operator*=(const int64_t& num) {
  vec_.x *= num;
  vec_.y *= num;
  return *this;
}

Vector& Vector::operator-() {
  vec_.x = -vec_.x;
  vec_.y = -vec_.y;
  return *this;
}

int64_t Vector::GetX() const { return vec_.x; }
int64_t& Vector::GetX() { return vec_.x; }
int64_t Vector::GetY() const { return vec_.y; }
int64_t& Vector::GetY() { return vec_.y; }

int64_t operator*(const Vector& pta, const Vector& ptb) {
  return pta.GetX() * ptb.GetX() + pta.GetY() * ptb.GetY();
}

int64_t operator^(const Vector& pta, const Vector& ptb) {
  return pta.GetX() * ptb.GetY() - pta.GetY() * ptb.GetX();
}

Vector operator+(const Vector& pta, const Vector& ptb) {
  Vector dop(pta);
  dop += ptb;
  return dop;
}

Vector operator-(const Vector& pta, const Vector& ptb) {
  Vector dop(pta);
  dop -= ptb;
  return dop;
}

Vector operator*(const int64_t& num, const Vector& vec) {
  Vector dop(vec);
  dop *= num;
  return dop;
}

Vector operator*(const Vector& vec, const int64_t& num) { return num * vec; }

Point::Point() = default;
Point::Point(const int64_t& ptx, const int64_t& pty) {
  pt_.x = ptx;
  pt_.y = pty;
}

int64_t Point::GetX() const { return pt_.x; }
int64_t& Point::GetX() { return pt_.x; }
int64_t Point::GetY() const { return pt_.y; }
int64_t& Point::GetY() { return pt_.y; }

Segment::Segment() = default;
Segment::Segment(const Point& beg, const Point& end) : beg_(beg), end_(end) {}
Point Segment::GetA() const { return beg_; }
Point Segment::GetB() const { return end_; }

Line::Line() = default;
Line::Line(const Point& beg, const Point& end) : beg_(beg), end_(end) {}
int64_t Line::GetA() const { return beg_.GetY() - end_.GetY(); }
int64_t Line::GetB() const { return end_.GetX() - beg_.GetX(); }
int64_t Line::GetC() const {
  return beg_.GetX() * end_.GetY() - end_.GetX() * beg_.GetY();
}

Ray::Ray() = default;
Ray::Ray(const Point& beg, const Point& end) : beg_(beg), end_(end) {}
Point& Ray::GetA() { return beg_; }
Vector Ray::GetVector() {
  Coord beg(beg_.GetX(), beg_.GetY());
  Coord end(end_.GetX(), end_.GetY());
  Vector vec(beg, end);
  return vec;
}

Circle::Circle() = default;
Circle::Circle(const Point& ptc, size_t& rad) : pt_(ptc), rad_(rad) {}
Point& Circle::GetCentre() { return pt_; }
size_t& Circle::GetRadius() { return rad_; }

void Point::Move(const Vector& vec) {
  pt_.x += vec.GetX();
  pt_.y += vec.GetY();
}

bool Point::ContainsPoint(const Point& ptc) {
  return ((pt_.x == ptc.GetX()) && (pt_.y == ptc.GetY()));
}

bool Point::CrossSegment(const Segment& seg) {
  Coord coorda(seg.GetA().GetX(), seg.GetA().GetY());
  Coord coordb(seg.GetB().GetX(), seg.GetB().GetY());
  Coord coordo(pt_.x, pt_.y);
  Vector vab(coorda, coordb);
  Vector voa(coordo, coorda);
  Vector vao(coorda, coordo);
  Vector vob(coordo, coordb);
  return ((vab ^ vao) == 0 && (voa * vob) <= 0);
}

IShape* Point::Clone() {
  Point* copy = new Point(pt_.x, pt_.y);
  return copy;
}

Vector Point::operator-(const Point& messi) {
  pt_.x -= messi.GetX();
  pt_.y -= messi.GetY();
  return Vector(pt_);
}

void Segment::Move(const Vector& vec) {
  beg_.GetX() += vec.GetX();
  end_.GetX() += vec.GetX();
  beg_.GetY() += vec.GetY();
  end_.GetY() += vec.GetY();
}

bool Segment::ContainsPoint(const Point& ptc) {
  Coord coorda(beg_.GetX(), beg_.GetY());
  Coord coordb(end_.GetX(), end_.GetY());
  Coord coordo(ptc.GetX(), ptc.GetY());
  Vector vab(coorda, coordb);
  Vector voa(coordo, coorda);
  Vector vao(coorda, coordo);
  Vector vob(coordo, coordb);
  return ((vab ^ vao) == 0 && (voa * vob) <= 0);
}

bool Segment::CrossSegment(const Segment& seg) {
  Segment dseg(seg.GetA(), seg.GetB());
  Coord coorda(beg_.GetX(), beg_.GetY());
  Coord coordb(end_.GetX(), end_.GetY());
  Coord coordc(seg.GetA().GetX(), seg.GetA().GetY());
  Coord coordd(seg.GetB().GetX(), seg.GetB().GetY());
  Vector vab(coorda, coordb);
  Vector vac(coorda, coordc);
  Vector vad(coorda, coordd);
  Vector vcd(coordc, coordd);
  Vector vca(coordc, coorda);
  Vector vcb(coordc, coordb);
  return (((vab ^ vac) * (vab ^ vad) < 0 && (vcd ^ vca) * (vcd ^ vcb) < 0) ||
          (ContainsPoint(seg.GetA()) || ContainsPoint(seg.GetB()) ||
           dseg.ContainsPoint(beg_) || dseg.ContainsPoint(end_)));
}

IShape* Segment::Clone() {
  Segment* copy = new Segment(beg_, end_);
  return copy;
}

void Line::Move(const Vector& vec) {
  beg_.GetX() += vec.GetX();
  end_.GetX() += vec.GetX();
  beg_.GetY() += vec.GetY();
  end_.GetY() += vec.GetY();
}

bool Line::ContainsPoint(const Point& ptc) {
  return (GetA() * ptc.GetX() + GetB() * ptc.GetY() + GetC() == 0);
}

bool Line::CrossSegment(const Segment& seg) {
  Coord coorda(beg_.GetX(), beg_.GetY());
  Coord coordb(end_.GetX(), end_.GetY());
  Coord coordc(seg.GetA().GetX(), seg.GetA().GetY());
  Coord coordd(seg.GetB().GetX(), seg.GetB().GetY());
  Vector vab(coorda, coordb);
  Vector vac(coorda, coordc);
  Vector vad(coorda, coordd);
  return ((vab ^ vac) * (vab ^ vad) <= 0);
}

IShape* Line::Clone() {
  Line* copy = new Line(beg_, end_);
  return copy;
}

void Ray::Move(const Vector& vec) {
  beg_.GetX() += vec.GetX();
  end_.GetX() += vec.GetX();
  beg_.GetY() += vec.GetY();
  end_.GetY() += vec.GetY();
}

bool Ray::ContainsPoint(const Point& ptc) {
  Coord coorda(beg_.GetX(), beg_.GetY());
  Coord coordc(ptc.GetX(), ptc.GetY());
  Vector vab(GetVector());
  Vector vac(coorda, coordc);
  return ((vab ^ vac) == 0 && (vab * vac) >= 0);
}

bool Ray::CrossSegment(const Segment& seg) {
  Coord coorda(beg_.GetX(), beg_.GetY());
  Coord coordb(end_.GetX(), end_.GetY());
  Coord coordc(seg.GetA().GetX(), seg.GetA().GetY());
  Coord coordd(seg.GetB().GetX(), seg.GetB().GetY());
  Vector vab(coorda, coordb);
  Vector vac(coorda, coordc);
  Vector vad(coorda, coordd);
  return (((vac ^ vab) * (vad ^ vab) < 0) ||
          ((vac ^ vab) == 0 && (vac * vab) >= 0) ||
          ((vad ^ vab) == 0 && (vad * vab) >= 0));
}

IShape* Ray::Clone() {
  Ray* copy = new Ray(beg_, end_);
  return copy;
}

void Circle::Move(const Vector& vec) {
  pt_.GetX() += vec.GetX();
  pt_.GetY() += vec.GetY();
}

bool Circle::ContainsPoint(const Point& ptc) {
  int64_t mula = pow(ptc.GetX() - pt_.GetX(), 2);
  int64_t mulb = pow(ptc.GetY() - pt_.GetY(), 2);
  return (mula + mulb <= pow(GetRadius(), 2));
}

bool Circle::CrossSegment(const Segment& seg) {
  Coord coord(pt_.GetX(), pt_.GetY());
  Coord coorda(seg.GetA().GetX(), seg.GetA().GetY());
  Coord coordb(seg.GetB().GetX(), seg.GetB().GetY());
  Vector vao(coorda, coord);
  Vector vab(coorda, coordb);
  Vector vbo(coordb, coord);
  Vector vba(coordb, coorda);
  double lom;
  double lao = sqrt((pow((double)vao.GetX(), 2) + pow((double)vao.GetY(), 2)));
  double lbo = sqrt((pow((double)vbo.GetX(), 2) + pow((double)vbo.GetY(), 2)));
  double lab = sqrt((pow((double)vab.GetX(), 2) + pow((double)vab.GetY(), 2)));
  if ((vao * vab) < 0 || (vbo * vba) < 0) {
    return ((lao <= (double)GetRadius() && lbo >= (double)GetRadius()) ||
            (lao >= (double)GetRadius() && lbo <= (double)GetRadius()));
  }
  Line line(seg.GetA(), seg.GetB());
  lom = (double)(line.GetA() * pt_.GetX() + line.GetB() * pt_.GetY() +
                 line.GetC()) /
        (sqrt(pow((double)line.GetA(), 2) + pow((double)line.GetB(), 2)));
  return ((lom <= (double)GetRadius()) &&
          (lao >= (double)GetRadius() || lbo >= (double)GetRadius()));
}

IShape* Circle::Clone() {
  Circle* copy = new Circle(GetCentre(), GetRadius());
  return copy;
}
