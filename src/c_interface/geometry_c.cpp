#include "geometry_c.h"
#include "../core/geometry.h"
#include "../core/matrix.h"

// 转换C向量到C++向量
geometry::Vector3D to_cpp_vector(Vector3D_C v) {
    return geometry::Vector3D(v.x, v.y, v.z);
}

// 转换C++向量到C向量
Vector3D_C to_c_vector(geometry::Vector3D v) {
    Vector3D_C result = {v.x, v.y, v.z};
    return result;
}

// 转换C矩阵到C++矩阵
geometry::Matrix4x4 to_cpp_matrix(Matrix4x4_C m) {
    geometry::Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = m.data[i][j];
        }
    }
    return result;
}

// 转换C++矩阵到C矩阵
Matrix4x4_C to_c_matrix(geometry::Matrix4x4 m) {
    Matrix4x4_C result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = m.data[i][j];
        }
    }
    return result;
}

// 转换C四元数到C++四元数
geometry::Quaternion to_cpp_quaternion(Quaternion_C q) {
    return geometry::Quaternion(q.w, q.x, q.y, q.z);
}

// 转换C++四元数到C四元数
Quaternion_C to_c_quaternion(geometry::Quaternion q) {
    Quaternion_C result = {q.w, q.x, q.y, q.z};
    return result;
}

// 向量运算实现
Vector3D_C vector3d_add(Vector3D_C v1, Vector3D_C v2) {
    return to_c_vector(to_cpp_vector(v1) + to_cpp_vector(v2));
}

Vector3D_C vector3d_sub(Vector3D_C v1, Vector3D_C v2) {
    return to_c_vector(to_cpp_vector(v1) - to_cpp_vector(v2));
}

Vector3D_C vector3d_mul(Vector3D_C v, float scalar) {
    return to_c_vector(to_cpp_vector(v) * scalar);
}

Vector3D_C vector3d_div(Vector3D_C v, float scalar) {
    return to_c_vector(to_cpp_vector(v) / scalar);
}

// 点积
float vector3d_dot(Vector3D_C v1, Vector3D_C v2) {
    return to_cpp_vector(v1).dot(to_cpp_vector(v2));
}

// 叉积
Vector3D_C vector3d_cross(Vector3D_C v1, Vector3D_C v2) {
    return to_c_vector(to_cpp_vector(v1).cross(to_cpp_vector(v2)));
}

// 长度
float vector3d_length(Vector3D_C v) {
    return to_cpp_vector(v).length();
}

// 归一化
Vector3D_C vector3d_normalize(Vector3D_C v) {
    return to_c_vector(to_cpp_vector(v).normalize());
}

// 三维投影
Vector3D_C vector3d_project(Vector3D_C vector, Vector3D_C axis) {
    return to_c_vector(geometry::project(to_cpp_vector(vector), to_cpp_vector(axis)));
}

// 分离轴定律 - 检测两个凸多边形是否碰撞
bool sat_collision(Vector3D_C* shape1, int shape1_size, Vector3D_C* shape2, int shape2_size) {
    std::vector<geometry::Vector3D> cpp_shape1;
    std::vector<geometry::Vector3D> cpp_shape2;
    
    for (int i = 0; i < shape1_size; i++) {
        cpp_shape1.push_back(to_cpp_vector(shape1[i]));
    }
    
    for (int i = 0; i < shape2_size; i++) {
        cpp_shape2.push_back(to_cpp_vector(shape2[i]));
    }
    
    return geometry::satCollision(cpp_shape1, cpp_shape2);
}

// 闵可夫斯基差 - 返回结果的大小
int minkowski_difference(Vector3D_C* shape1, int shape1_size, Vector3D_C* shape2, int shape2_size, Vector3D_C* result) {
    std::vector<geometry::Vector3D> cpp_shape1;
    std::vector<geometry::Vector3D> cpp_shape2;
    
    for (int i = 0; i < shape1_size; i++) {
        cpp_shape1.push_back(to_cpp_vector(shape1[i]));
    }
    
    for (int i = 0; i < shape2_size; i++) {
        cpp_shape2.push_back(to_cpp_vector(shape2[i]));
    }
    
    std::vector<geometry::Vector3D> cpp_result = geometry::minkowskiDifference(cpp_shape1, cpp_shape2);
    
    for (std::size_t i = 0; i < cpp_result.size(); i++) {
        result[i] = to_c_vector(cpp_result[i]);
    }
    
    return cpp_result.size();
}

// 矩阵运算实现
Matrix4x4_C matrix4x4_multiply(Matrix4x4_C m1, Matrix4x4_C m2) {
    return to_c_matrix(to_cpp_matrix(m1) * to_cpp_matrix(m2));
}

Vector3D_C matrix4x4_multiply_vector(Matrix4x4_C m, Vector3D_C v) {
    return to_c_vector(to_cpp_matrix(m) * to_cpp_vector(v));
}

// 矩阵变换实现
Matrix4x4_C matrix4x4_translation(Vector3D_C translation) {
    return to_c_matrix(geometry::Matrix4x4::translation(to_cpp_vector(translation)));
}

Matrix4x4_C matrix4x4_rotation(Vector3D_C eulerAngles) {
    return to_c_matrix(geometry::Matrix4x4::rotation(to_cpp_vector(eulerAngles)));
}

Matrix4x4_C matrix4x4_rotation_axis(float angle, Vector3D_C axis) {
    return to_c_matrix(geometry::Matrix4x4::rotation(angle, to_cpp_vector(axis)));
}

Matrix4x4_C matrix4x4_scale(Vector3D_C scale) {
    return to_c_matrix(geometry::Matrix4x4::scale(to_cpp_vector(scale)));
}

// 矩阵操作实现
Matrix4x4_C matrix4x4_transpose(Matrix4x4_C m) {
    return to_c_matrix(to_cpp_matrix(m).transpose());
}

Matrix4x4_C matrix4x4_inverse(Matrix4x4_C m) {
    return to_c_matrix(to_cpp_matrix(m).inverse());
}

float matrix4x4_determinant(Matrix4x4_C m) {
    return to_cpp_matrix(m).determinant();
}

// 四元数运算实现
Quaternion_C quaternion_multiply(Quaternion_C q1, Quaternion_C q2) {
    return to_c_quaternion(to_cpp_quaternion(q1) * to_cpp_quaternion(q2));
}

Quaternion_C quaternion_add(Quaternion_C q1, Quaternion_C q2) {
    return to_c_quaternion(to_cpp_quaternion(q1) + to_cpp_quaternion(q2));
}

Quaternion_C quaternion_multiply_scalar(Quaternion_C q, float scalar) {
    return to_c_quaternion(to_cpp_quaternion(q) * scalar);
}

// 四元数操作实现
Quaternion_C quaternion_conjugate(Quaternion_C q) {
    return to_c_quaternion(to_cpp_quaternion(q).conjugate());
}

Quaternion_C quaternion_inverse(Quaternion_C q) {
    return to_c_quaternion(to_cpp_quaternion(q).inverse());
}

float quaternion_length(Quaternion_C q) {
    return to_cpp_quaternion(q).length();
}

Quaternion_C quaternion_normalize(Quaternion_C q) {
    return to_c_quaternion(to_cpp_quaternion(q).normalize());
}

// 四元数转换实现
Matrix4x4_C quaternion_to_matrix(Quaternion_C q) {
    return to_c_matrix(to_cpp_quaternion(q).toMatrix());
}

Vector3D_C quaternion_rotate(Quaternion_C q, Vector3D_C v) {
    return to_c_vector(to_cpp_quaternion(q).rotate(to_cpp_vector(v)));
}

// 凹形碰撞检测实现
bool concave_collision(Vector3D_C** shape1, int* shape1_sizes, int shape1_parts, Vector3D_C** shape2, int* shape2_sizes, int shape2_parts) {
    std::vector<std::vector<geometry::Vector3D>> cpp_shape1;
    std::vector<std::vector<geometry::Vector3D>> cpp_shape2;
    
    // 转换shape1
    for (int i = 0; i < shape1_parts; i++) {
        std::vector<geometry::Vector3D> convex;
        for (int j = 0; j < shape1_sizes[i]; j++) {
            convex.push_back(to_cpp_vector(shape1[i][j]));
        }
        cpp_shape1.push_back(convex);
    }
    
    // 转换shape2
    for (int i = 0; i < shape2_parts; i++) {
        std::vector<geometry::Vector3D> convex;
        for (int j = 0; j < shape2_sizes[i]; j++) {
            convex.push_back(to_cpp_vector(shape2[i][j]));
        }
        cpp_shape2.push_back(convex);
    }
    
    return geometry::concaveCollision(cpp_shape1, cpp_shape2);
}
