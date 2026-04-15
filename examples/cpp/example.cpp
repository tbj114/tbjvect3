#include <iostream>
#include <vector>
#include "../../src/core/geometry.h"

int main() {
    // 测试向量运算
    geometry::Vector3D v1(1.0f, 2.0f, 3.0f);
    geometry::Vector3D v2(4.0f, 5.0f, 6.0f);
    
    std::cout << "Vector 1: (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << std::endl;
    std::cout << "Vector 2: (" << v2.x << ", " << v2.y << ", " << v2.z << ")" << std::endl;
    
    geometry::Vector3D sum = v1 + v2;
    std::cout << "Sum: (" << sum.x << ", " << sum.y << ", " << sum.z << ")" << std::endl;
    
    geometry::Vector3D difference = v1 - v2;
    std::cout << "Difference: (" << difference.x << ", " << difference.y << ", " << difference.z << ")" << std::endl;
    
    geometry::Vector3D scaled = v1 * 2.0f;
    std::cout << "Scaled: (" << scaled.x << ", " << scaled.y << ", " << scaled.z << ")" << std::endl;
    
    float dot_product = v1.dot(v2);
    std::cout << "Dot product: " << dot_product << std::endl;
    
    geometry::Vector3D cross_product = v1.cross(v2);
    std::cout << "Cross product: (" << cross_product.x << ", " << cross_product.y << ", " << cross_product.z << ")" << std::endl;
    
    float length = v1.length();
    std::cout << "Length of v1: " << length << std::endl;
    
    geometry::Vector3D normalized = v1.normalize();
    std::cout << "Normalized v1: (" << normalized.x << ", " << normalized.y << ", " << normalized.z << ")" << std::endl;
    
    // 测试投影
    geometry::Vector3D axis(1.0f, 0.0f, 0.0f);
    geometry::Vector3D projection = geometry::project(v1, axis);
    std::cout << "Projection of v1 onto x-axis: (" << projection.x << ", " << projection.y << ", " << projection.z << ")" << std::endl;
    
    // 测试碰撞检测
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
    
    bool collision = geometry::satCollision(shape1, shape2);
    std::cout << "Collision between shape1 and shape2: " << (collision ? "Yes" : "No") << std::endl;
    
    // 测试闵可夫斯基差
    std::vector<geometry::Vector3D> minkowski = geometry::minkowskiDifference(shape1, shape2);
    std::cout << "Minkowski difference size: " << minkowski.size() << std::endl;
    std::cout << "First few points: " << std::endl;
    for (int i = 0; i < std::min(5, (int)minkowski.size()); i++) {
        std::cout << "(" << minkowski[i].x << ", " << minkowski[i].y << ", " << minkowski[i].z << ")" << std::endl;
    }
    
    return 0;
}
