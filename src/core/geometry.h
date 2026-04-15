#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

// 跨平台导出宏
#ifdef WIN32
    #ifdef GEOMETRY_EXPORTS
        #define GEOMETRY_API __declspec(dllexport)
    #else
        #define GEOMETRY_API __declspec(dllimport)
    #endif
#else
    #define GEOMETRY_API
#endif

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
    
    // SIMD版本的运算（内部使用）
    static Vector3D simd_add(const Vector3D& a, const Vector3D& b);
    static Vector3D simd_sub(const Vector3D& a, const Vector3D& b);
    static Vector3D simd_mul(const Vector3D& a, float scalar);
    static float simd_dot(const Vector3D& a, const Vector3D& b);
    static float simd_length(const Vector3D& v);
    static Vector3D simd_normalize(const Vector3D& v);
};

// 三维投影
Vector3D project(const Vector3D& vector, const Vector3D& axis);

// 分离轴定律 - 检测两个凸多边形是否碰撞
bool satCollision(const std::vector<Vector3D>& shape1, const std::vector<Vector3D>& shape2);

// 检测两个凹多边形是否碰撞（通过凸分解）
bool concaveCollision(const std::vector<std::vector<Vector3D>>& shape1, const std::vector<std::vector<Vector3D>>& shape2);

// 连续碰撞检测 - 检测两个运动的凸多边形是否会在时间t内碰撞
bool continuousCollision(const std::vector<Vector3D>& shape1, const Vector3D& velocity1, const std::vector<Vector3D>& shape2, const Vector3D& velocity2, float& collisionTime, Vector3D& collisionPoint);

// 闵可夫斯基差
std::vector<Vector3D> minkowskiDifference(const std::vector<Vector3D>& shape1, const std::vector<Vector3D>& shape2);

} // namespace geometry

#endif // GEOMETRY_H
