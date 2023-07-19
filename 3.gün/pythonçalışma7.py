import numpy as np

def translationmatris(dx, dy, dz):
    return np.array([
        [1, 0, 0, dx],
        [0, 1, 0, dy],
        [0, 0, 1, dz],
        [0, 0, 0, 1]
    ])


def rotationmatris_z(a):
    c = np.cos(a)
    s = np.sin(a)
    return np.array([
        [c, -s, 0, 0],
        [s, c, 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1]
    ])

def rotationmatris_y(a):
    c = np.cos(a)
    s = np.sin(a)
    return np.array([
        [c, 0, s, 0],
        [0, 1, 0, 0],
        [-s, 0, c, 0],
        [0, 0, 0, 1]
    ])

def rotationmatris_x(a):
    c = np.cos(a)
    s = np.sin(a)
    return np.array([
        [1, 0, 0, 0],
        [0, c, -s, 0],
        [0, s, c, 0],
        [0, 0, 0, 1]
    ])

def transformationmatris(dx, dy, dz, rx, ry, rz):
    translation = translationmatris(dx, dy, dz)
    rotation_x = rotationmatris_x(rx)
    rotation_y = rotationmatris_y(ry)
    rotation_z = rotationmatris_z(rz)
    return np.dot(np.dot(np.dot(translation, rotation_x), rotation_y), rotation_z)

# Example usage:
dx, dy, dz = 1, 2, 3
rx, ry, rz = np.radians(45), np.radians(30), np.radians(60)

T = transformationmatris(dx, dy, dz, rx, ry, rz)
print("Transformation Matrix:".center(80,'*'))
print(T)
