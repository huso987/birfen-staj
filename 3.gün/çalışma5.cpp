#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;



struct EulerAcilari {
    double roll, pitch, yaw;
};

struct Quaternion {
    double w, x, y, z;
};

EulerAcilari ToEulerAngles(Quaternion q) {
    EulerAcilari ange;

    //roll
    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    ange.roll = atan2(sinr_cosp, cosr_cosp);

    // pitch 
    double sinp = 2 * (q.w * q.y - q.z * q.x);
    ange.pitch = asin(sinp);

    // yaw 
    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    ange.yaw = atan2(siny_cosp, cosy_cosp);

    return ange;
}


int main() {
    //örnek w,x,y,z
    Quaternion quater={1.0,0.0,0.0,0.0};
    EulerAcilari eulera=ToEulerAngles(quater);

    cout << "Roll:" << eulera.roll << "\n";
    cout << "Pitch:" << eulera.pitch << "\n";
    cout << "Yaw:" << eulera.yaw << "\n";
    return 0;
}


