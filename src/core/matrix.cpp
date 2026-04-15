#include "matrix.h"
#include <cmath>

namespace geometry {

// 矩阵实现
Matrix4x4::Matrix4x4() {
    // 单位矩阵
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

Matrix4x4::Matrix4x4(float diagonal) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = (i == j) ? diagonal : 0.0f;
        }
    }
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Vector3D Matrix4x4::operator*(const Vector3D& vector) const {
    float x = data[0][0] * vector.x + data[0][1] * vector.y + data[0][2] * vector.z + data[0][3];
    float y = data[1][0] * vector.x + data[1][1] * vector.y + data[1][2] * vector.z + data[1][3];
    float z = data[2][0] * vector.x + data[2][1] * vector.y + data[2][2] * vector.z + data[2][3];
    return Vector3D(x, y, z);
}

Matrix4x4 Matrix4x4::translation(const Vector3D& translation) {
    Matrix4x4 result;
    result.data[0][3] = translation.x;
    result.data[1][3] = translation.y;
    result.data[2][3] = translation.z;
    return result;
}

Matrix4x4 Matrix4x4::rotation(const Vector3D& eulerAngles) {
    float cx = std::cos(eulerAngles.x);
    float sx = std::sin(eulerAngles.x);
    float cy = std::cos(eulerAngles.y);
    float sy = std::sin(eulerAngles.y);
    float cz = std::cos(eulerAngles.z);
    float sz = std::sin(eulerAngles.z);
    
    Matrix4x4 result;
    result.data[0][0] = cy * cz;
    result.data[0][1] = sx * sy * cz - cx * sz;
    result.data[0][2] = cx * sy * cz + sx * sz;
    result.data[1][0] = cy * sz;
    result.data[1][1] = sx * sy * sz + cx * cz;
    result.data[1][2] = cx * sy * sz - sx * cz;
    result.data[2][0] = -sy;
    result.data[2][1] = sx * cy;
    result.data[2][2] = cx * cy;
    return result;
}

Matrix4x4 Matrix4x4::rotation(float angle, const Vector3D& axis) {
    Vector3D normalizedAxis = axis.normalize();
    float c = std::cos(angle);
    float s = std::sin(angle);
    float t = 1.0f - c;
    
    Matrix4x4 result;
    result.data[0][0] = t * normalizedAxis.x * normalizedAxis.x + c;
    result.data[0][1] = t * normalizedAxis.x * normalizedAxis.y - s * normalizedAxis.z;
    result.data[0][2] = t * normalizedAxis.x * normalizedAxis.z + s * normalizedAxis.y;
    result.data[1][0] = t * normalizedAxis.x * normalizedAxis.y + s * normalizedAxis.z;
    result.data[1][1] = t * normalizedAxis.y * normalizedAxis.y + c;
    result.data[1][2] = t * normalizedAxis.y * normalizedAxis.z - s * normalizedAxis.x;
    result.data[2][0] = t * normalizedAxis.x * normalizedAxis.z - s * normalizedAxis.y;
    result.data[2][1] = t * normalizedAxis.y * normalizedAxis.z + s * normalizedAxis.x;
    result.data[2][2] = t * normalizedAxis.z * normalizedAxis.z + c;
    return result;
}

Matrix4x4 Matrix4x4::scale(const Vector3D& scale) {
    Matrix4x4 result;
    result.data[0][0] = scale.x;
    result.data[1][1] = scale.y;
    result.data[2][2] = scale.z;
    return result;
}

Matrix4x4 Matrix4x4::transpose() const {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}

float Matrix4x4::determinant() const {
    // 4x4矩阵行列式计算
    float det = 0.0f;
    det += data[0][0] * (data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - 
                         data[1][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) + 
                         data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]));
    det -= data[0][1] * (data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - 
                         data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) + 
                         data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]));
    det += data[0][2] * (data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - 
                         data[1][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) + 
                         data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
    det -= data[0][3] * (data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) - 
                         data[1][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) + 
                         data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
    return det;
}

Matrix4x4 Matrix4x4::inverse() const {
    // 简化版逆矩阵计算，实际应用中可能需要更高效的实现
    float det = determinant();
    if (std::abs(det) < 1e-6) {
        return Matrix4x4();
    }
    
    Matrix4x4 result;
    // 计算伴随矩阵
    result.data[0][0] = data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - 
                       data[1][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) + 
                       data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]);
    result.data[0][1] = -data[0][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) + 
                        data[0][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - 
                        data[0][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]);
    result.data[0][2] = data[0][1] * (data[1][2] * data[3][3] - data[1][3] * data[3][2]) - 
                       data[0][2] * (data[1][1] * data[3][3] - data[1][3] * data[3][1]) + 
                       data[0][3] * (data[1][1] * data[3][2] - data[1][2] * data[3][1]);
    result.data[0][3] = -data[0][1] * (data[1][2] * data[2][3] - data[1][3] * data[2][2]) + 
                        data[0][2] * (data[1][1] * data[2][3] - data[1][3] * data[2][1]) - 
                        data[0][3] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]);
    
    result.data[1][0] = -data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) + 
                        data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) - 
                        data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]);
    result.data[1][1] = data[0][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - 
                       data[0][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) + 
                       data[0][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]);
    result.data[1][2] = -data[0][0] * (data[1][2] * data[3][3] - data[1][3] * data[3][2]) + 
                        data[0][2] * (data[1][0] * data[3][3] - data[1][3] * data[3][0]) - 
                        data[0][3] * (data[1][0] * data[3][2] - data[1][2] * data[3][0]);
    result.data[1][3] = data[0][0] * (data[1][2] * data[2][3] - data[1][3] * data[2][2]) - 
                       data[0][2] * (data[1][0] * data[2][3] - data[1][3] * data[2][0]) + 
                       data[0][3] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]);
    
    result.data[2][0] = data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - 
                       data[1][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) + 
                       data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);
    result.data[2][1] = -data[0][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) + 
                        data[0][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) - 
                        data[0][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);
    result.data[2][2] = data[0][0] * (data[1][1] * data[3][3] - data[1][3] * data[3][1]) - 
                       data[0][1] * (data[1][0] * data[3][3] - data[1][3] * data[3][0]) + 
                       data[0][3] * (data[1][0] * data[3][1] - data[1][1] * data[3][0]);
    result.data[2][3] = -data[0][0] * (data[1][1] * data[2][3] - data[1][3] * data[2][1]) + 
                        data[0][1] * (data[1][0] * data[2][3] - data[1][3] * data[2][0]) - 
                        data[0][3] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    
    result.data[3][0] = -data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) + 
                        data[1][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) - 
                        data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);
    result.data[3][1] = data[0][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) - 
                       data[0][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) + 
                       data[0][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);
    result.data[3][2] = -data[0][0] * (data[1][1] * data[3][2] - data[1][2] * data[3][1]) + 
                        data[0][1] * (data[1][0] * data[3][2] - data[1][2] * data[3][0]) - 
                        data[0][2] * (data[1][0] * data[3][1] - data[1][1] * data[3][0]);
    result.data[3][3] = data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) - 
                       data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) + 
                       data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    
    // 除以行列式
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] /= det;
        }
    }
    
    return result;
}

// 四元数实现
Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

Quaternion::Quaternion(float angle, const Vector3D& axis) {
    Vector3D normalizedAxis = axis.normalize();
    float halfAngle = angle * 0.5f;
    w = std::cos(halfAngle);
    float sinHalfAngle = std::sin(halfAngle);
    x = normalizedAxis.x * sinHalfAngle;
    y = normalizedAxis.y * sinHalfAngle;
    z = normalizedAxis.z * sinHalfAngle;
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.w - x * other.x - y * other.y - z * other.z,
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w
    );
}

Quaternion Quaternion::operator+(const Quaternion& other) const {
    return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
}

Quaternion Quaternion::operator*(float scalar) const {
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::inverse() const {
    float lenSq = w * w + x * x + y * y + z * z;
    if (lenSq < 1e-6) {
        return Quaternion();
    }
    float invLenSq = 1.0f / lenSq;
    return Quaternion(w * invLenSq, -x * invLenSq, -y * invLenSq, -z * invLenSq);
}

float Quaternion::length() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::normalize() const {
    float len = length();
    if (len < 1e-6) {
        return Quaternion();
    }
    float invLen = 1.0f / len;
    return Quaternion(w * invLen, x * invLen, y * invLen, z * invLen);
}

Matrix4x4 Quaternion::toMatrix() const {
    Matrix4x4 result;
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;
    float yy = y * y;
    float yz = y * z;
    float yw = y * w;
    float zz = z * z;
    float zw = z * w;
    
    result.data[0][0] = 1.0f - 2.0f * (yy + zz);
    result.data[0][1] = 2.0f * (xy - zw);
    result.data[0][2] = 2.0f * (xz + yw);
    result.data[1][0] = 2.0f * (xy + zw);
    result.data[1][1] = 1.0f - 2.0f * (xx + zz);
    result.data[1][2] = 2.0f * (yz - xw);
    result.data[2][0] = 2.0f * (xz - yw);
    result.data[2][1] = 2.0f * (yz + xw);
    result.data[2][2] = 1.0f - 2.0f * (xx + yy);
    
    return result;
}

Vector3D Quaternion::rotate(const Vector3D& vector) const {
    Quaternion vecQuat(0.0f, vector.x, vector.y, vector.z);
    Quaternion resultQuat = *this * vecQuat * this->conjugate();
    return Vector3D(resultQuat.x, resultQuat.y, resultQuat.z);
}

} // namespace geometry
