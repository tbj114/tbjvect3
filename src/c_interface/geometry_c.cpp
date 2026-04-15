#include "geometry_c.h"
#include "../core/geometry.h"

// 转换C向量到C++向量
geometry::Vector3D to_cpp_vector(Vector3D_C v) {
    return geometry::Vector3D(v.x, v.y, v.z);
}

// 转换C++向量到C向量
Vector3D_C to_c_vector(geometry::Vector3D v) {
    Vector3D_C result = {v.x, v.y, v.z};
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
