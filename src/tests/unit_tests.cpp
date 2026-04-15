#include "geometry.h"
#include "matrix.h"
#include <iostream>
#include <cassert>
#include <cmath>

void testVectorOperations() {
    std::cout << "Testing vector operations..." << std::endl;
    
    geometry::Vector3D v1(1.0f, 2.0f, 3.0f);
    geometry::Vector3D v2(4.0f, 5.0f, 6.0f);
    
    // 测试加法
    geometry::Vector3D sum = v1 + v2;
    assert(sum.x == 5.0f && sum.y == 7.0f && sum.z == 9.0f);
    
    // 测试减法
    geometry::Vector3D diff = v2 - v1;
    assert(diff.x == 3.0f && diff.y == 3.0f && diff.z == 3.0f);
    
    // 测试标量乘法
    geometry::Vector3D scaled = v1 * 2.0f;
    assert(scaled.x == 2.0f && scaled.y == 4.0f && scaled.z == 6.0f);
    
    // 测试点积
    float dot = v1.dot(v2);
    assert(dot == 32.0f);
    
    // 测试叉积
    geometry::Vector3D cross = v1.cross(v2);
    assert(cross.x == -3.0f && cross.y == 6.0f && cross.z == -3.0f);
    
    // 测试长度
    float length = v1.length();
    assert(fabs(length - sqrtf(14.0f)) < 1e-6);
    
    // 测试归一化
    geometry::Vector3D normalized = v1.normalize();
    assert(fabs(normalized.length() - 1.0f) < 1e-6);
    
    std::cout << "Vector operations test passed!" << std::endl;
}

void testMatrixOperations() {
    std::cout << "Testing matrix operations..." << std::endl;
    
    // 测试单位矩阵
    geometry::Matrix4x4 identity;
    geometry::Vector3D v(1.0f, 2.0f, 3.0f);
    geometry::Vector3D transformed = identity * v;
    assert(transformed.x == 1.0f && transformed.y == 2.0f && transformed.z == 3.0f);
    
    // 测试平移
    geometry::Matrix4x4 translation = geometry::Matrix4x4::translation(geometry::Vector3D(1.0f, 2.0f, 3.0f));
    transformed = translation * v;
    assert(transformed.x == 2.0f && transformed.y == 4.0f && transformed.z == 6.0f);
    
    // 测试缩放
    geometry::Matrix4x4 scale = geometry::Matrix4x4::scale(geometry::Vector3D(2.0f, 3.0f, 4.0f));
    transformed = scale * v;
    assert(transformed.x == 2.0f && transformed.y == 6.0f && transformed.z == 12.0f);
    
    // 测试矩阵乘法
    geometry::Matrix4x4 combined = translation * scale;
    transformed = combined * v;
    assert(transformed.x == 3.0f && transformed.y == 8.0f && transformed.z == 15.0f);
    
    std::cout << "Matrix operations test passed!" << std::endl;
}

void testQuaternionOperations() {
    std::cout << "Testing quaternion operations..." << std::endl;
    
    // 测试四元数旋转
    geometry::Vector3D v(1.0f, 0.0f, 0.0f);
    geometry::Quaternion q(3.14159f / 2.0f, geometry::Vector3D(0.0f, 0.0f, 1.0f)); // 90度绕Z轴旋转
    geometry::Vector3D rotated = q.rotate(v);
    std::cout << "Rotated vector: (" << rotated.x << ", " << rotated.y << ", " << rotated.z << ")" << std::endl;
    assert(fabs(rotated.x - 0.0f) < 1e-5 && fabs(rotated.y - 1.0f) < 1e-5 && fabs(rotated.z - 0.0f) < 1e-5);
    
    // 测试四元数到矩阵的转换
    geometry::Matrix4x4 mat = q.toMatrix();
    geometry::Vector3D matRotated = mat * v;
    std::cout << "Matrix rotated vector: (" << matRotated.x << ", " << matRotated.y << ", " << matRotated.z << ")" << std::endl;
    assert(fabs(matRotated.x - 0.0f) < 1e-5 && fabs(matRotated.y - 1.0f) < 1e-5 && fabs(matRotated.z - 0.0f) < 1e-5);
    
    std::cout << "Quaternion operations test passed!" << std::endl;
}

void testCollisionDetection() {
    std::cout << "Testing collision detection..." << std::endl;
    
    // 测试凸形状碰撞
    std::vector<geometry::Vector3D> shape1 = {
        geometry::Vector3D(0.0f, 0.0f, 0.0f),
        geometry::Vector3D(1.0f, 0.0f, 0.0f),
        geometry::Vector3D(1.0f, 1.0f, 0.0f),
        geometry::Vector3D(0.0f, 1.0f, 0.0f)
    };
    
    std::vector<geometry::Vector3D> shape2 = {
        geometry::Vector3D(0.5f, 0.5f, 0.0f),
        geometry::Vector3D(1.5f, 0.5f, 0.0f),
        geometry::Vector3D(1.5f, 1.5f, 0.0f),
        geometry::Vector3D(0.5f, 1.5f, 0.0f)
    };
    
    assert(geometry::satCollision(shape1, shape2) == true);
    
    // 测试非碰撞
    std::vector<geometry::Vector3D> shape3 = {
        geometry::Vector3D(2.0f, 2.0f, 0.0f),
        geometry::Vector3D(3.0f, 2.0f, 0.0f),
        geometry::Vector3D(3.0f, 3.0f, 0.0f),
        geometry::Vector3D(2.0f, 3.0f, 0.0f)
    };
    
    assert(geometry::satCollision(shape1, shape3) == false);
    
    // 测试凹形状碰撞
    std::vector<std::vector<geometry::Vector3D>> concaveShape1 = {shape1};
    std::vector<std::vector<geometry::Vector3D>> concaveShape2 = {shape2};
    assert(geometry::concaveCollision(concaveShape1, concaveShape2) == true);
    
    // 测试连续碰撞
    geometry::Vector3D velocity1(0.0f, 0.0f, 0.0f);
    geometry::Vector3D velocity2(-1.0f, 0.0f, 0.0f);
    float collisionTime;
    geometry::Vector3D collisionPoint;
    bool collided = geometry::continuousCollision(shape2, velocity2, shape1, velocity1, collisionTime, collisionPoint);
    assert(collided == true);
    
    std::cout << "Collision detection test passed!" << std::endl;
}

int main() {
    testVectorOperations();
    testMatrixOperations();
    testQuaternionOperations();
    testCollisionDetection();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
