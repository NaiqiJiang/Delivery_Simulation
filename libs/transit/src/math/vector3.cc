#include "math/vector3.h"

#define _USE_MATH_DEFINES
#define EPS 0.0000001

/**
 * @brief Default constructor, initializes to zero vector.
 */
Vector3::Vector3() : Vector3(0) {}

/**
 * @brief Constructs a Vector3 with all components set to the same value.
 * @param a The value for all components.
 */
Vector3::Vector3(double a) : Vector3(a, a, a) {}

/**
 * @brief Constructs a Vector3 with specified x, y, and z values.
 * @param a X component.
 * @param b Y component.
 * @param c Z component.
 */
Vector3::Vector3(double a, double b, double c) : x(a), y(b), z(c) {}

/**
 * @brief Compares two Vector3 objects for equality with an epsilon tolerance.
 * @param v Vector3 to compare with.
 * @return True if vectors are equal within the tolerance, false otherwise.
 */
bool Vector3::operator==(const Vector3& v) const { return dist(v) < EPS; }

/**
 * @brief Accesses the ith component of the Vector3.
 * @param i Index of the component.
 * @return Reference to the component.
 */
double& Vector3::operator[](int i) {
  if (i < 0 || i >= 3) throw std::out_of_range("i not in range for vector");
  switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
  }
  return x;
}

/**
 * @brief Const access to the ith component of the Vector3.
 * @param i Index of the component.
 * @return Value of the component.
 */
double Vector3::operator[](int i) const {
  if (i < 0 || i >= 3) throw std::out_of_range("i not in range for vector");
  switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
  }
  return x;
}

/**
 * @brief Adds two Vector3 objects.
 * @param v Vector3 to add.
 * @return Sum of the vectors.
 */
Vector3 Vector3::operator+(const Vector3& v) const {
  return Vector3(x + v.x, y + v.y, z + v.z);
}

/**
 * @brief Subtracts one Vector3 from another.
 * @param v Vector3 to subtract.
 * @return Difference of the vectors.
 */
Vector3 Vector3::operator-(const Vector3& v) const {
  return (*this) + (v * -1);
}

/**
 * @brief Multiplies the Vector3 by a scalar.
 * @param s Scalar to multiply with.
 * @return Scaled vector.
 */
Vector3 Vector3::operator*(double s) const {
  return Vector3(x * s, y * s, z * s);
}

/**
 * @brief Divides the Vector3 by a scalar.
 * @param s Scalar to divide by.
 * @return Scaled vector.
 */
Vector3 Vector3::operator/(double s) const { return (*this) * (1 / s); }

/**
 * @brief Dot product of two Vector3 objects.
 * @param v Vector3 to dot with.
 * @return Dot product value.
 */
double Vector3::operator*(const Vector3& v) const {
  return x * v.x + y * v.y + z * v.z;
}

/**
 * @brief Cross product of two Vector3 objects.
 * @param v Vector3 to cross with.
 * @return Cross product vector.
 */
Vector3 Vector3::cross(const Vector3& v) const {
  return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

/**
 * @brief Calculates the magnitude of the Vector3.
 * @return Magnitude of the vector.
 */
double Vector3::magnitude() const { return sqrt(x * x + y * y + z * z); }

/**
 * @brief Normalizes the Vector3 to unit length.
 * @return Reference to this vector after normalization.
 */
Vector3& Vector3::normalize() {
  (*this) = unit();
  return *this;
}

/**
 * @brief Gets the unit vector along the direction of this vector.
 * @return Unit vector of this vector.
 */
Vector3 Vector3::unit() const {
  if (magnitude() < EPS) return (*this);
  return (*this) / magnitude();
}

/**
 * @brief Calculates the distance between this vector and another.
 * @param v Vector3 to calculate the distance with.
 * @return Distance between the two vectors.
 */
double Vector3::dist(const Vector3& v) const {
  return ((*this) - v).magnitude();
}

/**
 * @brief Overloads the output stream operator for Vector3.
 * @param strm Output stream.
 * @param v Vector3 to output.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& strm, const Vector3& v) {
  strm << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return strm;
}
