import sys
print(f"Python version: {sys.version}")

# 尝试导入PyQt6
print("\nTrying to import PyQt6...")
try:
    import PyQt6
    print("Successfully imported PyQt6")
    
    # 尝试导入QtWidgets
    print("\nTrying to import QtWidgets...")
    from PyQt6 import QtWidgets
    print("Successfully imported QtWidgets")
    
    # 尝试创建一个简单的应用
    print("\nTrying to create QApplication...")
    app = QtWidgets.QApplication([])
    print("Successfully created QApplication")
    
    print("\nAll tests passed! PyQt6 is working correctly.")
except Exception as e:
    print(f"Error: {e}")
    import traceback
    traceback.print_exc()
