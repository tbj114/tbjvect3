#include "geometry.h"
#include <cmath>

namespace geometry {

// 向量运算实现
Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(float scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator/(float scalar) const {
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

// 点积
float Vector3D::dot(const Vector3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// 叉积
Vector3D Vector3D::cross(const Vector3D& other) const {
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

// 长度
float Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// 归一化
Vector3D Vector3D::normalize() const {
    float len = length();
    if (len > 0) {
        return *this / len;
    }
    return *this;
}

// 三维投影
Vector3D project(const Vector3D& vector, const Vector3D& axis) {
    Vector3D normalizedAxis = axis.normalize();
    float dotProduct = vector.dot(normalizedAxis);
    return normalizedAxis * dotProduct;
}

// 计算形状在轴上的投影范围
void projectShape(const std::vector<Vector3D>& shape, const Vector3D& axis, float& min, float& max) {
    min = shape[0].dot(axis);
    max = min;
    for (size_t i = 1; i < shape.size(); i++) {
        float proj = shape[i].dot(axis);
        if (proj < min) min = proj;
        if (proj > max) max = proj;
    }
}

// 检查两个投影范围是否重叠
bool projectionsOverlap(float min1, float max1, float min2, float max2) {
    return max1 >= min2 && max2 >= min1;
}

// 分离轴定律 - 检测两个凸多边形是否碰撞
bool satCollision(const std::vector<Vector3D>& shape1, const std::vector<Vector3D>& shape2) {
    // 收集所有可能的分离轴
    std::vector<Vector3D> axes;
    
    // 形状1的边
    for (size_t i = 0; i < shape1.size(); i++) {
        Vector3D edge = shape1[(i + 1) % shape1.size()] - shape1[i];
        Vector3D normal = edge.cross(Vector3D(0, 0, 1)).normalize();
        axes.push_back(normal);
    }
    
    // 形状2的边
    for (size_t i = 0; i < shape2.size(); i++) {
        Vector3D edge = shape2[(i + 1) % shape2.size()] - shape2[i];
        Vector3D normal = edge.cross(Vector3D(0, 0, 1)).normalize();
        axes.push_back(normal);
    }
    
    // 检查每个分离轴
    for (const Vector3D& axis : axes) {
        float min1, max1, min2, max2;
        projectShape(shape1, axis, min1, max1);
        projectShape(shape2, axis, min2, max2);
        
        if (!projectionsOverlap(min1, max1, min2, max2)) {
            return false; // 找到分离轴，无碰撞
        }
    }
    
    return true; // 所有轴都重叠，有碰撞
}

// 闵可夫斯基差
std::vector<Vector3D> minkowskiDifference(const std::vector<Vector3D>& shape1, const std::vector<Vector3D>& shape2) {
    std::vector<Vector3D> result;
    for (const Vector3D& p1 : shape1) {
        for (const Vector3D& p2 : shape2) {
            result.push_back(p1 - p2);
        }
    }
    return result;
}

} // namespace geometry
