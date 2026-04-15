#!/usr/bin/env python3
import sys
import os

# 添加Python包路径
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../src/python'))

from geometry import Vector, sat_collision, minkowski_difference

# 测试向量运算
v1 = Vector(1.0, 2.0, 3.0)
v2 = Vector(4.0, 5.0, 6.0)

print(f"Vector 1: {v1}")
print(f"Vector 2: {v2}")

sum_vec = v1 + v2
print(f"Sum: {sum_vec}")

diff_vec = v1 - v2
print(f"Difference: {diff_vec}")

scaled_vec = v1 * 2.0
print(f"Scaled: {scaled_vec}")

dot_product = v1.dot(v2)
print(f"Dot product: {dot_product}")

cross_product = v1.cross(v2)
print(f"Cross product: {cross_product}")

length = v1.length()
print(f"Length of v1: {length}")

normalized = v1.normalize()
print(f"Normalized v1: {normalized}")

# 测试投影
axis = Vector(1.0, 0.0, 0.0)
projection = v1.project(axis)
print(f"Projection of v1 onto x-axis: {projection}")

# 测试碰撞检测
shape1 = [
    Vector(0.0, 0.0, 0.0),
    Vector(1.0, 0.0, 0.0),
    Vector(1.0, 1.0, 0.0),
    Vector(0.0, 1.0, 0.0)
]

shape2 = [
    Vector(0.5, 0.5, 0.0),
    Vector(1.5, 0.5, 0.0),
    Vector(1.5, 1.5, 0.0),
    Vector(0.5, 1.5, 0.0)
]

collision = sat_collision(shape1, shape2)
print(f"Collision between shape1 and shape2: {'Yes' if collision else 'No'}")

# 测试闵可夫斯基差
minkowski = minkowski_difference(shape1, shape2)
print(f"Minkowski difference size: {len(minkowski)}")
print("First few points:")
for i, vec in enumerate(minkowski[:5]):
    print(f"{vec}")
