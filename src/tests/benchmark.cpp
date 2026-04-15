#include "geometry.h"
#include "matrix.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>

using namespace std::chrono;

void benchmarkVectorOperations() {
    std::cout << "Benchmarking vector operations..." << std::endl;
    
    const int iterations = 1000000;
    
    // 创建测试数据
    std::vector<geometry::Vector3D> vecs1(iterations);
    std::vector<geometry::Vector3D> vecs2(iterations);
    for (int i = 0; i < iterations; i++) {
        vecs1[i] = geometry::Vector3D(i * 0.1f, i * 0.2f, i * 0.3f);
        vecs2[i] = geometry::Vector3D(i * 0.4f, i * 0.5f, i * 0.6f);
    }
    
    // 测试加法
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        geometry::Vector3D result = vecs1[i] + vecs2[i];
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Vector addition: " << duration << " ms" << std::endl;
    
    // 测试点积
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        float result = vecs1[i].dot(vecs2[i]);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Vector dot product: " << duration << " ms" << std::endl;
    
    // 测试长度
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        float result = vecs1[i].length();
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Vector length: " << duration << " ms" << std::endl;
    
    // 测试归一化
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        geometry::Vector3D result = vecs1[i].normalize();
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Vector normalization: " << duration << " ms" << std::endl;
}

void benchmarkMatrixOperations() {
    std::cout << "Benchmarking matrix operations..." << std::endl;
    
    const int iterations = 100000;
    
    // 创建测试数据
    std::vector<geometry::Matrix4x4> mats1(iterations);
    std::vector<geometry::Matrix4x4> mats2(iterations);
    std::vector<geometry::Vector3D> vecs(iterations);
    
    for (int i = 0; i < iterations; i++) {
        mats1[i] = geometry::Matrix4x4::rotation(geometry::Vector3D(i * 0.1f, i * 0.2f, i * 0.3f));
        mats2[i] = geometry::Matrix4x4::translation(geometry::Vector3D(i * 0.1f, i * 0.2f, i * 0.3f));
        vecs[i] = geometry::Vector3D(i * 0.1f, i * 0.2f, i * 0.3f);
    }
    
    // 测试矩阵乘法
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        geometry::Matrix4x4 result = mats1[i] * mats2[i];
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Matrix multiplication: " << duration << " ms" << std::endl;
    
    // 测试矩阵变换
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        geometry::Vector3D result = mats1[i] * vecs[i];
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Matrix transformation: " << duration << " ms" << std::endl;
}

void benchmarkQuaternionOperations() {
    std::cout << "Benchmarking quaternion operations..." << std::endl;
    
    const int iterations = 100000;
    
    // 创建测试数据
    std::vector<geometry::Quaternion> quats(iterations);
    std::vector<geometry::Vector3D> vecs(iterations);
    
    for (int i = 0; i < iterations; i++) {
        quats[i] = geometry::Quaternion(i * 0.1f, geometry::Vector3D(1.0f, 0.0f, 0.0f));
        vecs[i] = geometry::Vector3D(i * 0.1f, i * 0.2f, i * 0.3f);
    }
    
    // 测试四元数旋转
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        geometry::Vector3D result = quats[i].rotate(vecs[i]);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Quaternion rotation: " << duration << " ms" << std::endl;
    
    // 测试四元数到矩阵的转换
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        geometry::Matrix4x4 result = quats[i].toMatrix();
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Quaternion to matrix: " << duration << " ms" << std::endl;
}

void benchmarkCollisionDetection() {
    std::cout << "Benchmarking collision detection..." << std::endl;
    
    const int iterations = 100000;
    
    // 创建测试数据
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
    
    // 测试SAT碰撞检测
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        bool result = geometry::satCollision(shape1, shape2);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "SAT collision detection: " << duration << " ms" << std::endl;
}

int main() {
    benchmarkVectorOperations();
    benchmarkMatrixOperations();
    benchmarkQuaternionOperations();
    benchmarkCollisionDetection();
    
    return 0;
}
