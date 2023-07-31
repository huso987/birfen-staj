import math

def quaterniontoeuler(w, x, y, z):
    # Roll 
    t0 = +2.0 * (w * x + y * z)
    t1 = +1.0 - 2.0 * (x * x + y * y)
    roll = math.degrees(math.atan2(t0, t1))

    # Pitch 
    t2 = +2.0 * (w * y - z * x)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    pitch = math.degrees(math.asin(t2))

    # Yaw 
    t3 = +2.0 * (w * z + x * y)
    t4 = +1.0 - 2.0 * (y * y + z * z)
    yaw = math.degrees(math.atan2(t3, t4))

    return roll, pitch, yaw

# ornek w,x,y,z
w = 1.0
x = 0.0
y = 0.0
z = 0.0

roll, pitch, yaw = quaterniontoeuler(w, x, y, z)

print("Derece cinsinden Roll,Pitch,Yaw degerleri".center(80,'*'))
print("Roll:", roll)
print("Pitch:", pitch)
print("Yaw:", yaw)