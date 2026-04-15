#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

namespace geometry {

// 三维向量类
class Vector3D {
public:
    float x, y, z;
    
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
    
    // 向量运算
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(float scalar) const;
    Vector3D operator/(float scalar) const;
    
    // 点积
    float dot(const Vector3D& other) const;
    
    // 叉积
    Vector3D cross(const Vector3D& other) const;
    
    // 长度
    float length() const;
    
    // 归一化
    Vector3D normalize() const;
};

// 三维投影
Vector3D project(const Vector3D& vector, const Vector3D& axis);

// 分离轴定律 - 检测两个凸多边形是否碰撞
bool satCollision(const std::vector<Vector3D>& shape1, const std::vector<Vector3D>& shape2);

// 闵可夫斯基差
std::vector<Vector3D> minkowskiDifference(const std::vector<Vector3D>& shape1, const std::vector<Vector3D>& shape2);

} // namespace geometry

#endif // GEOMETRY_H
