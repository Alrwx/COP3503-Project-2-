#include <iostream>
#include <vector>
#include <string>

using namespace std;


void screen (int blue1, int green1, int red1, int blue2, int green2, int red2) {
    float fblue1 = 1 - (blue1 / (float)255);
    float fgreen1 = 1 - (green1 / (float)255);
    float fred1 = 1 - (red1 / (float)255);

    //second bracket
    float fblue2 = 1 - (blue2 / (float)255);
    float fgreen2 = 1 - (green2 / (float)255);
    float fred2 = 1 - (red2 / (float)255);

    //totaling
    float nblue = (1 - (fblue1 * fblue2));
    int bigblue = (int)((nblue * 255) + 0.5);
    float ngreen = (1 - (fgreen1 * fgreen2));
    int biggreen = (int)((ngreen * 255) + 0.5);
    float nred = (1 - (fred1 * fred2));
    int bigred = (int)((nred * 255) + 0.5);

    cout << bigblue << ", " << biggreen << ", " << bigred << endl;
};

int main () {
    screen(0, 0, 0, 87, 126, 150);
};