#include "geometry.h"
#include "simd_utils.h"
#include <cmath>
#include <limits>

namespace geometry {

// 向量运算实现
Vector3D Vector3D::operator+(const Vector3D& other) const {
    return simd_add(*this, other);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return simd_sub(*this, other);
}

Vector3D Vector3D::operator*(float scalar) const {
    return simd_mul(*this, scalar);
}

Vector3D Vector3D::operator/(float scalar) const {
    return simd_mul(*this, 1.0f / scalar);
}

// 点积
float Vector3D::dot(const Vector3D& other) const {
    return simd_dot(*this, other);
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
    return simd_length(*this);
}

// 归一化
Vector3D Vector3D::normalize() const {
    return simd_normalize(*this);
}

// SIMD版本的实现
Vector3D Vector3D::simd_add(const Vector3D& a, const Vector3D& b) {
    float data1[4] = {a.x, a.y, a.z, 0.0f};
    float data2[4] = {b.x, b.y, b.z, 0.0f};
    float4 v1 = load4(data1);
    float4 v2 = load4(data2);
    float4 result = add4(v1, v2);
    float out[4];
    store4(out, result);
    return Vector3D(out[0], out[1], out[2]);
}

Vector3D Vector3D::simd_sub(const Vector3D& a, const Vector3D& b) {
    float data1[4] = {a.x, a.y, a.z, 0.0f};
    float data2[4] = {b.x, b.y, b.z, 0.0f};
    float4 v1 = load4(data1);
    float4 v2 = load4(data2);
    float4 result = sub4(v1, v2);
    float out[4];
    store4(out, result);
    return Vector3D(out[0], out[1], out[2]);
}

Vector3D Vector3D::simd_mul(const Vector3D& a, float scalar) {
    float data[4] = {a.x, a.y, a.z, 0.0f};
    float4 v = load4(data);
    float4 result = mul4_scalar(v, scalar);
    float out[4];
    store4(out, result);
    return Vector3D(out[0], out[1], out[2]);
}

float Vector3D::simd_dot(const Vector3D& a, const Vector3D& b) {
    float data1[4] = {a.x, a.y, a.z, 0.0f};
    float data2[4] = {b.x, b.y, b.z, 0.0f};
    float4 v1 = load4(data1);
    float4 v2 = load4(data2);
    return dot4(v1, v2);
}

float Vector3D::simd_length(const Vector3D& v) {
    float data[4] = {v.x, v.y, v.z, 0.0f};
    float4 vec = load4(data);
    return length4(vec);
}

Vector3D Vector3D::simd_normalize(const Vector3D& v) {
    float data[4] = {v.x, v.y, v.z, 0.0f};
    float4 vec = load4(data);
    float4 normalized = normalize4(vec);
    float out[4];
    store4(out, normalized);
    return Vector3D(out[0], out[1], out[2]);
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

// 检查点是否在多边形内
bool pointInPolygon(const std::vector<Vector3D>& polygon, const Vector3D& point) {
    bool inside = false;
    size_t n = polygon.size();
    
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        if (((polygon[i].y > point.y) != (polygon[j].y > point.y)) &&
            (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }
    
    return inside;
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

// 检测两个凹多边形是否碰撞（通过凸分解）
bool concaveCollision(const std::vector<std::vector<Vector3D>>& shape1, const std::vector<std::vector<Vector3D>>& shape2) {
    // 检查shape1的每个凸部分与shape2的每个凸部分是否碰撞
    for (const std::vector<Vector3D>& convex1 : shape1) {
        for (const std::vector<Vector3D>& convex2 : shape2) {
            if (satCollision(convex1, convex2)) {
                return true; // 只要有一个凸部分碰撞，整个凹多边形就碰撞
            }
        }
    }
    return false;
}

// 连续碰撞检测 - 检测两个运动的凸多边形是否会在时间t内碰撞
bool continuousCollision(const std::vector<Vector3D>& shape1, const Vector3D& velocity1, const std::vector<Vector3D>& shape2, const Vector3D& velocity2, float& collisionTime, Vector3D& collisionPoint) {
    // 计算相对速度
    Vector3D relativeVelocity = velocity2 - velocity1;
    
    // 计算闵可夫斯基差
    std::vector<Vector3D> minkowski = minkowskiDifference(shape2, shape1);
    
    // 检查原点是否在闵可夫斯基差内（已经碰撞）
    if (pointInPolygon(minkowski, Vector3D(0, 0, 0))) {
        collisionTime = 0.0f;
        collisionPoint = Vector3D(0, 0, 0);
        return true;
    }
    
    // 检查相对速度是否为零
    if (relativeVelocity.length() < 1e-6) {
        return false;
    }
    
    // 检查相对速度是否与闵可夫斯基差相交
    // 这里使用简化的实现，实际应用中可能需要更复杂的算法
    float minTime = std::numeric_limits<float>::max();
    Vector3D closestPoint;
    
    // 遍历闵可夫斯基差的边，检查与相对速度的交点
    for (size_t i = 0; i < minkowski.size(); i++) {
        Vector3D p1 = minkowski[i];
        Vector3D p2 = minkowski[(i + 1) % minkowski.size()];
        
        // 计算线段p1-p2与射线(0,0,0) -> relativeVelocity的交点
        Vector3D edge = p2 - p1;
        Vector3D start = Vector3D(0, 0, 0);
        
        // 计算叉积
        Vector3D cross = edge.cross(relativeVelocity);
        if (std::abs(cross.length()) < 1e-6) {
            continue; // 平行线
        }
        
        // 计算参数
        Vector3D startToP1 = p1 - start;
        float t = startToP1.cross(edge).dot(cross) / cross.dot(cross);
        float u = startToP1.cross(relativeVelocity).dot(cross) / cross.dot(cross);
        
        if (t >= 0 && t <= 1 && u >= 0) {
            if (u < minTime) {
                minTime = u;
                closestPoint = start + relativeVelocity * u;
            }
        }
    }
    
    if (minTime < std::numeric_limits<float>::max()) {
        collisionTime = minTime;
        collisionPoint = closestPoint;
        return true;
    }
    
    return false;
}

} // namespace geometry
