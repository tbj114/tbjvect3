#include <iostream>
#include "../../src/core/geometry.h"

int main() {
    // 创建一个凹多边形（由两个凸多边形组成）
    std::vector<std::vector<geometry::Vector3D>> concave_shape1;
    
    // 第一个凸部分（矩形）
    std::vector<geometry::Vector3D> convex1_1 = {
        geometry::Vector3D(0.0f, 0.0f, 0.0f),
        geometry::Vector3D(2.0f, 0.0f, 0.0f),
        geometry::Vector3D(2.0f, 1.0f, 0.0f),
        geometry::Vector3D(0.0f, 1.0f, 0.0f)
    };
    
    // 第二个凸部分（矩形）
    std::vector<geometry::Vector3D> convex1_2 = {
        geometry::Vector3D(0.5f, 1.0f, 0.0f),
        geometry::Vector3D(1.5f, 1.0f, 0.0f),
        geometry::Vector3D(1.5f, 2.0f, 0.0f),
        geometry::Vector3D(0.5f, 2.0f, 0.0f)
    };
    
    concave_shape1.push_back(convex1_1);
    concave_shape1.push_back(convex1_2);
    
    // 创建另一个凹多边形
    std::vector<std::vector<geometry::Vector3D>> concave_shape2;
    
    // 第一个凸部分（矩形）
    std::vector<geometry::Vector3D> convex2_1 = {
        geometry::Vector3D(1.0f, -1.0f, 0.0f),
        geometry::Vector3D(3.0f, -1.0f, 0.0f),
        geometry::Vector3D(3.0f, 0.5f, 0.0f),
        geometry::Vector3D(1.0f, 0.5f, 0.0f)
    };
    
    // 第二个凸部分（矩形）
    std::vector<geometry::Vector3D> convex2_2 = {
        geometry::Vector3D(2.0f, 0.5f, 0.0f),
        geometry::Vector3D(4.0f, 0.5f, 0.0f),
        geometry::Vector3D(4.0f, 1.5f, 0.0f),
        geometry::Vector3D(2.0f, 1.5f, 0.0f)
    };
    
    concave_shape2.push_back(convex2_1);
    concave_shape2.push_back(convex2_2);
    
    // 测试碰撞
    bool collision = geometry::concaveCollision(concave_shape1, concave_shape2);
    std::cout << "Concave collision: " << (collision ? "Yes" : "No") << std::endl;
    
    return 0;
}
