import ctypes
import os

# 加载动态链接库
import platform

# 根据平台选择正确的库扩展名
if platform.system() == 'Windows':
    lib_extension = '.dll'
elif platform.system() == 'Darwin':
    lib_extension = '.dylib'
else:
    lib_extension = '.so'

lib_path = os.path.join(os.path.dirname(__file__), f'../../build/libgeometry{lib_extension}')
lib = ctypes.CDLL(lib_path)

# 定义C兼容的向量结构
class Vector3D(ctypes.Structure):
    _fields_ = [('x', ctypes.c_float),
                ('y', ctypes.c_float),
                ('z', ctypes.c_float)]

# 定义C兼容的矩阵结构
class Matrix4x4(ctypes.Structure):
    _fields_ = [('data', ctypes.c_float * 4 * 4)]

# 定义C兼容的四元数结构
class Quaternion(ctypes.Structure):
    _fields_ = [('w', ctypes.c_float),
                ('x', ctypes.c_float),
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

# 矩阵运算函数
lib.matrix4x4_multiply.argtypes = [Matrix4x4, Matrix4x4]
lib.matrix4x4_multiply.restype = Matrix4x4

lib.matrix4x4_multiply_vector.argtypes = [Matrix4x4, Vector3D]
lib.matrix4x4_multiply_vector.restype = Vector3D

lib.matrix4x4_translation.argtypes = [Vector3D]
lib.matrix4x4_translation.restype = Matrix4x4

lib.matrix4x4_rotation.argtypes = [Vector3D]
lib.matrix4x4_rotation.restype = Matrix4x4

lib.matrix4x4_rotation_axis.argtypes = [ctypes.c_float, Vector3D]
lib.matrix4x4_rotation_axis.restype = Matrix4x4

lib.matrix4x4_scale.argtypes = [Vector3D]
lib.matrix4x4_scale.restype = Matrix4x4

lib.matrix4x4_transpose.argtypes = [Matrix4x4]
lib.matrix4x4_transpose.restype = Matrix4x4

lib.matrix4x4_inverse.argtypes = [Matrix4x4]
lib.matrix4x4_inverse.restype = Matrix4x4

lib.matrix4x4_determinant.argtypes = [Matrix4x4]
lib.matrix4x4_determinant.restype = ctypes.c_float

# 四元数运算函数
lib.quaternion_multiply.argtypes = [Quaternion, Quaternion]
lib.quaternion_multiply.restype = Quaternion

lib.quaternion_add.argtypes = [Quaternion, Quaternion]
lib.quaternion_add.restype = Quaternion

lib.quaternion_multiply_scalar.argtypes = [Quaternion, ctypes.c_float]
lib.quaternion_multiply_scalar.restype = Quaternion

lib.quaternion_conjugate.argtypes = [Quaternion]
lib.quaternion_conjugate.restype = Quaternion

lib.quaternion_inverse.argtypes = [Quaternion]
lib.quaternion_inverse.restype = Quaternion

lib.quaternion_length.argtypes = [Quaternion]
lib.quaternion_length.restype = ctypes.c_float

lib.quaternion_normalize.argtypes = [Quaternion]
lib.quaternion_normalize.restype = Quaternion

lib.quaternion_to_matrix.argtypes = [Quaternion]
lib.quaternion_to_matrix.restype = Matrix4x4

lib.quaternion_rotate.argtypes = [Quaternion, Vector3D]
lib.quaternion_rotate.restype = Vector3D

# 凹形碰撞检测函数
lib.concave_collision.argtypes = [ctypes.POINTER(ctypes.POINTER(Vector3D)), ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.POINTER(Vector3D)), ctypes.POINTER(ctypes.c_int), ctypes.c_int]
lib.concave_collision.restype = ctypes.c_bool

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

# 矩阵包装类
class Matrix:
    def __init__(self):
        self.mat = Matrix4x4()
        # 初始化单位矩阵
        for i in range(4):
            for j in range(4):
                self.mat.data[i][j] = 1.0 if i == j else 0.0
    
    def __mul__(self, other):
        if isinstance(other, Matrix):
            result = lib.matrix4x4_multiply(self.mat, other.mat)
            mat = Matrix()
            mat.mat = result
            return mat
        elif isinstance(other, Vector):
            result = lib.matrix4x4_multiply_vector(self.mat, other.vec)
            return Vector(result.x, result.y, result.z)
        return NotImplemented
    
    @staticmethod
    def translation(translation):
        result = lib.matrix4x4_translation(translation.vec)
        mat = Matrix()
        mat.mat = result
        return mat
    
    @staticmethod
    def rotation(euler_angles):
        result = lib.matrix4x4_rotation(euler_angles.vec)
        mat = Matrix()
        mat.mat = result
        return mat
    
    @staticmethod
    def rotation_axis(angle, axis):
        result = lib.matrix4x4_rotation_axis(angle, axis.vec)
        mat = Matrix()
        mat.mat = result
        return mat
    
    @staticmethod
    def scale(scale):
        result = lib.matrix4x4_scale(scale.vec)
        mat = Matrix()
        mat.mat = result
        return mat
    
    def transpose(self):
        result = lib.matrix4x4_transpose(self.mat)
        mat = Matrix()
        mat.mat = result
        return mat
    
    def inverse(self):
        result = lib.matrix4x4_inverse(self.mat)
        mat = Matrix()
        mat.mat = result
        return mat
    
    def determinant(self):
        return lib.matrix4x4_determinant(self.mat)
    
    def __repr__(self):
        return "Matrix([[{}, {}, {}, {}], [{}, {}, {}, {}], [{}, {}, {}, {}], [{}, {}, {}, {}]])".format(
            self.mat.data[0][0], self.mat.data[0][1], self.mat.data[0][2], self.mat.data[0][3],
            self.mat.data[1][0], self.mat.data[1][1], self.mat.data[1][2], self.mat.data[1][3],
            self.mat.data[2][0], self.mat.data[2][1], self.mat.data[2][2], self.mat.data[2][3],
            self.mat.data[3][0], self.mat.data[3][1], self.mat.data[3][2], self.mat.data[3][3]
        )

# 四元数包装类
class Quat:
    def __init__(self, w=1.0, x=0.0, y=0.0, z=0.0):
        self.quat = Quaternion(w, x, y, z)
    
    def __mul__(self, other):
        if isinstance(other, Quat):
            result = lib.quaternion_multiply(self.quat, other.quat)
            quat = Quat()
            quat.quat = result
            return quat
        elif isinstance(other, float):
            result = lib.quaternion_multiply_scalar(self.quat, other)
            quat = Quat()
            quat.quat = result
            return quat
        return NotImplemented
    
    def __add__(self, other):
        if isinstance(other, Quat):
            result = lib.quaternion_add(self.quat, other.quat)
            quat = Quat()
            quat.quat = result
            return quat
        return NotImplemented
    
    def conjugate(self):
        result = lib.quaternion_conjugate(self.quat)
        quat = Quat()
        quat.quat = result
        return quat
    
    def inverse(self):
        result = lib.quaternion_inverse(self.quat)
        quat = Quat()
        quat.quat = result
        return quat
    
    def length(self):
        return lib.quaternion_length(self.quat)
    
    def normalize(self):
        result = lib.quaternion_normalize(self.quat)
        quat = Quat()
        quat.quat = result
        return quat
    
    def to_matrix(self):
        result = lib.quaternion_to_matrix(self.quat)
        mat = Matrix()
        mat.mat = result
        return mat
    
    def rotate(self, vector):
        result = lib.quaternion_rotate(self.quat, vector.vec)
        return Vector(result.x, result.y, result.z)
    
    @staticmethod
    def from_axis_angle(angle, axis):
        # 这里需要实现从轴角创建四元数的逻辑
        # 由于C接口没有直接的函数，我们可以在Python中实现
        import math
        half_angle = angle * 0.5
        sin_half = math.sin(half_angle)
        axis_len = axis.length()
        if axis_len > 0:
            axis = axis / axis_len
        return Quat(
            math.cos(half_angle),
            axis.vec.x * sin_half,
            axis.vec.y * sin_half,
            axis.vec.z * sin_half
        )
    
    def __repr__(self):
        return f"Quat({self.quat.w}, {self.quat.x}, {self.quat.y}, {self.quat.z})"

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

# 凹形碰撞检测函数
def concave_collision(shape1, shape2):
    """检测两个凹多边形是否碰撞（通过凸分解）
    
    Args:
        shape1: 第一个凹多边形，由多个凸多边形组成的列表
        shape2: 第二个凹多边形，由多个凸多边形组成的列表
    
    Returns:
        bool: 是否碰撞
    """
    # 准备shape1的数据
    shape1_parts = len(shape1)
    shape1_array = (ctypes.POINTER(Vector3D) * shape1_parts)()
    shape1_sizes = (ctypes.c_int * shape1_parts)()
    
    for i, convex in enumerate(shape1):
        convex_size = len(convex)
        shape1_sizes[i] = convex_size
        convex_array = (Vector3D * convex_size)()
        for j, vec in enumerate(convex):
            convex_array[j] = vec.vec
        shape1_array[i] = convex_array
    
    # 准备shape2的数据
    shape2_parts = len(shape2)
    shape2_array = (ctypes.POINTER(Vector3D) * shape2_parts)()
    shape2_sizes = (ctypes.c_int * shape2_parts)()
    
    for i, convex in enumerate(shape2):
        convex_size = len(convex)
        shape2_sizes[i] = convex_size
        convex_array = (Vector3D * convex_size)()
        for j, vec in enumerate(convex):
            convex_array[j] = vec.vec
        shape2_array[i] = convex_array
    
    return bool(lib.concave_collision(
        shape1_array, shape1_sizes, shape1_parts,
        shape2_array, shape2_sizes, shape2_parts
    ))

# 导出符号
__all__ = ['Vector', 'Matrix', 'Quat', 'sat_collision', 'concave_collision', 'minkowski_difference']
