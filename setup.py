from setuptools import setup
import os

# 读取 README.md 作为长描述
with open('README.md', 'r', encoding='utf-8') as f:
    long_description = f.read()

# 设置安装配置
setup(
    name='geometry',
    version='1.0.0',
    description='3D geometry library with collision detection',
    long_description=long_description,
    long_description_content_type='text/markdown',
    author='Your Name',
    author_email='your.email@example.com',
    url='https://github.com/tbj114/tbjvect3',
    packages=['geometry'],
    package_dir={'geometry': 'src/python'},
    package_data={
        'geometry': ['*.so', '*.dll', '*.dylib']
    },
    classifiers=[
        'Programming Language :: Python :: 3',
        'Programming Language :: C++',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.6',
    install_requires=[],
)
