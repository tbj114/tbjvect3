#include <stdio.h>
#include "../../src/c_interface/geometry_c.h"

int main() {
    // 测试向量运算
    Vector3D_C v1 = {1.0f, 2.0f, 3.0f};
    Vector3D_C v2 = {4.0f, 5.0f, 6.0f};
    
    printf("Vector 1: (%.2f, %.2f, %.2f)\n", v1.x, v1.y, v1.z);
    printf("Vector 2: (%.2f, %.2f, %.2f)\n", v2.x, v2.y, v2.z);
    
    Vector3D_C sum = vector3d_add(v1, v2);
    printf("Sum: (%.2f, %.2f, %.2f)\n", sum.x, sum.y, sum.z);
    
    Vector3D_C difference = vector3d_sub(v1, v2);
    printf("Difference: (%.2f, %.2f, %.2f)\n", difference.x, difference.y, difference.z);
    
    Vector3D_C scaled = vector3d_mul(v1, 2.0f);
    printf("Scaled: (%.2f, %.2f, %.2f)\n", scaled.x, scaled.y, scaled.z);
    
    float dot_product = vector3d_dot(v1, v2);
    printf("Dot product: %.2f\n", dot_product);
    
    Vector3D_C cross_product = vector3d_cross(v1, v2);
    printf("Cross product: (%.2f, %.2f, %.2f)\n", cross_product.x, cross_product.y, cross_product.z);
    
    float length = vector3d_length(v1);
    printf("Length of v1: %.2f\n", length);
    
    Vector3D_C normalized = vector3d_normalize(v1);
    printf("Normalized v1: (%.2f, %.2f, %.2f)\n", normalized.x, normalized.y, normalized.z);
    
    // 测试投影
    Vector3D_C axis = {1.0f, 0.0f, 0.0f};
    Vector3D_C projection = vector3d_project(v1, axis);
    printf("Projection of v1 onto x-axis: (%.2f, %.2f, %.2f)\n", projection.x, projection.y, projection.z);
    
    // 测试碰撞检测
    Vector3D_C shape1[] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    };
    int shape1_size = 4;
    
    Vector3D_C shape2[] = {
        {0.5f, 0.5f, 0.0f},
        {1.5f, 0.5f, 0.0f},
        {1.5f, 1.5f, 0.0f},
        {0.5f, 1.5f, 0.0f}
    };
    int shape2_size = 4;
    
    bool collision = sat_collision(shape1, shape1_size, shape2, shape2_size);
    printf("Collision between shape1 and shape2: %s\n", collision ? "Yes" : "No");
    
    // 测试闵可夫斯基差
    int max_result_size = shape1_size * shape2_size;
    Vector3D_C result[max_result_size];
    int result_size = minkowski_difference(shape1, shape1_size, shape2, shape2_size, result);
    
    printf("Minkowski difference size: %d\n", result_size);
    printf("First few points: \n");
    for (int i = 0; i < result_size && i < 5; i++) {
        printf("(%.2f, %.2f, %.2f)\n", result[i].x, result[i].y, result[i].z);
    }
    
    return 0;
}
