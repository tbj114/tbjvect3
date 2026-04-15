import ctypes
import os

# 加载动态链接库
lib_path = os.path.join(os.path.dirname(__file__), '../../build/libgeometry.so')
lib = ctypes.CDLL(lib_path)

# 定义C兼容的向量结构
class Vector3D(ctypes.Structure):
    _fields_ = [('x', ctypes.c_float),
                ('y', ctypes.c_float),
                ('z', ctypes.c_float)]

# 向量运算函数
lib.vector3d_add.argtypes = [Vector3D, Vector3D]
lib.vector3d_add.restype = Vector3D

lib.vector3d_sub.argtypes = [Vector3D, Vector3D]
lib.vector3d_sub.restype = Vector3D

lib.vector3d_mul.argtypes = [Vector3D, ctypes.c_float]
lib.vector3d_mul.restype = Vector3D

lib.vector3d_div.argtypes = [Vector3D, ctypes.c_float]
lib.vector3d_div.restype = Vector3D

lib.vector3d_dot.argtypes = [Vector3D, Vector3D]
lib.vector3d_dot.restype = ctypes.c_float

lib.vector3d_cross.argtypes = [Vector3D, Vector3D]
lib.vector3d_cross.restype = Vector3D

lib.vector3d_length.argtypes = [Vector3D]
lib.vector3d_length.restype = ctypes.c_float

lib.vector3d_normalize.argtypes = [Vector3D]
lib.vector3d_normalize.restype = Vector3D

lib.vector3d_project.argtypes = [Vector3D, Vector3D]
lib.vector3d_project.restype = Vector3D

lib.sat_collision.argtypes = [ctypes.POINTER(Vector3D), ctypes.c_int, ctypes.POINTER(Vector3D), ctypes.c_int]
lib.sat_collision.restype = ctypes.c_bool

lib.minkowski_difference.argtypes = [ctypes.POINTER(Vector3D), ctypes.c_int, ctypes.POINTER(Vector3D), ctypes.c_int, ctypes.POINTER(Vector3D)]
lib.minkowski_difference.restype = ctypes.c_int

# Python包装类
class Vector:
    def __init__(self, x=0.0, y=0.0, z=0.0):
        self.vec = Vector3D(x, y, z)
    
    def __add__(self, other):
        result = lib.vector3d_add(self.vec, other.vec)
        return Vector(result.x, result.y, result.z)
    
    def __sub__(self, other):
        result = lib.vector3d_sub(self.vec, other.vec)
        return Vector(result.x, result.y, result.z)
    
    def __mul__(self, scalar):
        result = lib.vector3d_mul(self.vec, scalar)
        return Vector(result.x, result.y, result.z)
    
    def __truediv__(self, scalar):
        result = lib.vector3d_div(self.vec, scalar)
        return Vector(result.x, result.y, result.z)
    
    def dot(self, other):
        return lib.vector3d_dot(self.vec, other.vec)
    
    def cross(self, other):
        result = lib.vector3d_cross(self.vec, other.vec)
        return Vector(result.x, result.y, result.z)
    
    def length(self):
        return lib.vector3d_length(self.vec)
    
    def normalize(self):
        result = lib.vector3d_normalize(self.vec)
        return Vector(result.x, result.y, result.z)
    
    def project(self, axis):
        result = lib.vector3d_project(self.vec, axis.vec)
        return Vector(result.x, result.y, result.z)
    
    def __repr__(self):
        return f"Vector({self.vec.x}, {self.vec.y}, {self.vec.z})"

# 碰撞检测函数
def sat_collision(shape1, shape2):
    shape1_array = (Vector3D * len(shape1))()
    for i, vec in enumerate(shape1):
        shape1_array[i] = vec.vec
    
    shape2_array = (Vector3D * len(shape2))()
    for i, vec in enumerate(shape2):
        shape2_array[i] = vec.vec
    
    return bool(lib.sat_collision(shape1_array, len(shape1), shape2_array, len(shape2)))

# 闵可夫斯基差函数
def minkowski_difference(shape1, shape2):
    shape1_array = (Vector3D * len(shape1))()
    for i, vec in enumerate(shape1):
        shape1_array[i] = vec.vec
    
    shape2_array = (Vector3D * len(shape2))()
    for i, vec in enumerate(shape2):
        shape2_array[i] = vec.vec
    
    max_result_size = len(shape1) * len(shape2)
    result_array = (Vector3D * max_result_size)()
    
    result_size = lib.minkowski_difference(shape1_array, len(shape1), shape2_array, len(shape2), result_array)
    
    result = []
    for i in range(result_size):
        result.append(Vector(result_array[i].x, result_array[i].y, result_array[i].z))
    
    return result
