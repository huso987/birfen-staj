#include <iostream>
#include <cmath>
using namespace std;

struct Matris4x4 {
    double veri[4][4];
};

Matris4x4 translationMatris(double dx, double dy, double dz) {
    Matris4x4 mat;
    mat.veri[0][0] = 1; mat.veri[0][1] = 0; mat.veri[0][2] = 0; mat.veri[0][3] = dx;
    mat.veri[1][0] = 0; mat.veri[1][1] = 1; mat.veri[1][2] = 0; mat.veri[1][3] = dy;
    mat.veri[2][0] = 0; mat.veri[2][1] = 0; mat.veri[2][2] = 1; mat.veri[2][3] = dz;
    mat.veri[3][0] = 0; mat.veri[3][1] = 0; mat.veri[3][2] = 0; mat.veri[3][3] = 1;
    return mat;
}

Matris4x4 rotationMatrisX(double angle) {
    double c = cos(angle);
    double s = sin(angle);
    Matris4x4 mat;
    mat.veri[0][0] = 1; mat.veri[0][1] = 0; mat.veri[0][2] = 0; mat.veri[0][3] = 0;
    mat.veri[1][0] = 0; mat.veri[1][1] = c; mat.veri[1][2] = -s; mat.veri[1][3] = 0;
    mat.veri[2][0] = 0; mat.veri[2][1] = s; mat.veri[2][2] = c; mat.veri[2][3] = 0;
    mat.veri[3][0] = 0; mat.veri[3][1] = 0; mat.veri[3][2] = 0; mat.veri[3][3] = 1;
    return mat;
}

Matris4x4 rotationMatrisY(double angle) {
    double c = cos(angle);
    double s = sin(angle);
    Matris4x4 mat;
    mat.veri[0][0] = c; mat.veri[0][1] = 0; mat.veri[0][2] = s; mat.veri[0][3] = 0;
    mat.veri[1][0] = 0; mat.veri[1][1] = 1; mat.veri[1][2] = 0; mat.veri[1][3] = 0;
    mat.veri[2][0] = -s; mat.veri[2][1] = 0; mat.veri[2][2] = c; mat.veri[2][3] = 0;
    mat.veri[3][0] = 0; mat.veri[3][1] = 0; mat.veri[3][2] = 0; mat.veri[3][3] = 1;
    return mat;
}
Matris4x4 rotationMatrisZ(double angle) {
    double c = cos(angle);
    double s = sin(angle);
    Matris4x4 mat;
    mat.veri[0][0] = c; mat.veri[0][1] = -s; mat.veri[0][2] = 0; mat.veri[0][3] = 0;
    mat.veri[1][0] = s; mat.veri[1][1] = c; mat.veri[1][2] = 0; mat.veri[1][3] = 0;
    mat.veri[2][0] = 0; mat.veri[2][1] = 0; mat.veri[2][2] = 1; mat.veri[2][3] = 0;
    mat.veri[3][0] = 0; mat.veri[3][1] = 0; mat.veri[3][2] = 0; mat.veri[3][3] = 1;
    return mat;
}
Matris4x4 multiplyMatris(const Matris4x4& mat1, const Matris4x4& mat2) {
    Matris4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.veri[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result.veri[i][j] += mat1.veri[i][k] * mat2.veri[k][j];
            }
        }
    }
    return result;
}
Matris4x4 transformationMatris(double dx, double dy, double dz, double rx, double ry, double rz) {
    Matris4x4 translation = translationMatris(dx, dy, dz);
    Matris4x4 rotation_x = rotationMatrisX(rx);
    Matris4x4 rotation_y = rotationMatrisY(ry);
    Matris4x4 rotation_z = rotationMatrisZ(rz);
    return multiplyMatris(multiplyMatris(multiplyMatris(translation, rotation_x), rotation_y), rotation_z);
}

int main() {
    double dx, dy, dz, rx, ry, rz;
    cout << "ilk sayiyi gir(dx): "; cin >> dx;
    cout << "ikinci sayiyi gir(dy): "; cin >> dy;
    cout << "ucuncu sayiyi gir(dz): "; cin >> dz;
    cout << "dorduncu sayiyi gir(rx in degrees): "; cin >> rx;
    cout << "besinci sayiyi gir(ry in degrees): "; cin >> ry;
    cout << "altinci sayiyi gir(rz in degrees): "; cin >> rz;

    // dereceleri radyana çevirme
    rx = rx * M_PI / 180.0;
    ry = ry * M_PI / 180.0;
    rz = rz * M_PI / 180.0;

    Matris4x4 T = transformationMatris(dx, dy, dz, rx, ry, rz);

    cout << "Transformation Matrix:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << T.veri[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
