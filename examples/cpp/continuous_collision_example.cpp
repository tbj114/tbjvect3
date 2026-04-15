#include <iostream>
#include "../../src/core/geometry.h"

int main() {
    // 创建两个矩形
    std::vector<geometry::Vector3D> shape1 = {
        geometry::Vector3D(0.0f, 0.0f, 0.0f),
        geometry::Vector3D(2.0f, 0.0f, 0.0f),
        geometry::Vector3D(2.0f, 1.0f, 0.0f),
        geometry::Vector3D(0.0f, 1.0f, 0.0f)
    };
    
    std::vector<geometry::Vector3D> shape2 = {
        geometry::Vector3D(3.0f, 0.0f, 0.0f),
        geometry::Vector3D(5.0f, 0.0f, 0.0f),
        geometry::Vector3D(5.0f, 1.0f, 0.0f),
        geometry::Vector3D(3.0f, 1.0f, 0.0f)
    };
    
    // 设置速度
    geometry::Vector3D velocity1(0.0f, 0.0f, 0.0f);  // 静止
    geometry::Vector3D velocity2(-2.0f, 0.0f, 0.0f); // 向左移动
    
    // 测试连续碰撞检测
    float collisionTime;
    geometry::Vector3D collisionPoint;
    bool collision = geometry::continuousCollision(shape1, velocity1, shape2, velocity2, collisionTime, collisionPoint);
    
    if (collision) {
        std::cout << "Collision will occur at time: " << collisionTime << std::endl;
        std::cout << "Collision point: (" << collisionPoint.x << ", " << collisionPoint.y << ", " << collisionPoint.z << ")" << std::endl;
    } else {
        std::cout << "No collision will occur" << std::endl;
    }
    
    return 0;
}
