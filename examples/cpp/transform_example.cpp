#include <iostream>
#include "../../src/core/geometry.h"
#include "../../src/core/matrix.h"

int main() {
    // 测试向量
    geometry::Vector3D v(1.0f, 2.0f, 3.0f);
    std::cout << "Original vector: (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
    
    // 测试平移
    geometry::Matrix4x4 translate = geometry::Matrix4x4::translation(geometry::Vector3D(10.0f, 20.0f, 30.0f));
    geometry::Vector3D translated = translate * v;
    std::cout << "Translated vector: (" << translated.x << ", " << translated.y << ", " << translated.z << ")" << std::endl;
    
    // 测试旋转（欧拉角）
    geometry::Matrix4x4 rotate = geometry::Matrix4x4::rotation(geometry::Vector3D(0.0f, 0.0f, 3.14159f / 2.0f)); // 90度绕Z轴
    geometry::Vector3D rotated = rotate * v;
    std::cout << "Rotated vector: (" << rotated.x << ", " << rotated.y << ", " << rotated.z << ")" << std::endl;
    
    // 测试缩放
    geometry::Matrix4x4 scale = geometry::Matrix4x4::scale(geometry::Vector3D(2.0f, 3.0f, 4.0f));
    geometry::Vector3D scaled = scale * v;
    std::cout << "Scaled vector: (" << scaled.x << ", " << scaled.y << ", " << scaled.z << ")" << std::endl;
    
    // 测试组合变换
    geometry::Matrix4x4 combined = translate * rotate * scale;
    geometry::Vector3D transformed = combined * v;
    std::cout << "Combined transform: (" << transformed.x << ", " << transformed.y << ", " << transformed.z << ")" << std::endl;
    
    // 测试四元数
    geometry::Quaternion q(3.14159f / 2.0f, geometry::Vector3D(0.0f, 0.0f, 1.0f)); // 90度绕Z轴
    geometry::Vector3D quat_rotated = q.rotate(v);
    std::cout << "Quaternion rotated: (" << quat_rotated.x << ", " << quat_rotated.y << ", " << quat_rotated.z << ")" << std::endl;
    
    return 0;
}
