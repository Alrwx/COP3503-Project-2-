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

void overlay(int blue1, int green1, int red1, int blue2, int green2, int red2) {
    float fblue1 = (blue1 / (float)255);
    float fgreen1 = (green1 / (float)255);
    float fred1 = (red1 / (float)255);

    //second bracket
    float fblue2 = (blue2 / (float)255);
    float fgreen2 = (green2 / (float)255);
    float fred2 = (red2 / (float)255);

    int bigblue;
    int biggreen;
    int bigred;

        if (fblue2 <= 0.5) {
            float nblue = 2 * fblue2 * fblue1;
            bigblue = (int)((nblue * 255) + 0.5);
        } else {
            float nblue = 1 - (2 * (1 - fblue1) * (1- fblue2));
            bigblue = (int)((nblue * 255) + 0.5);
        }

        if (fgreen2 <= 0.5) {
            float ngreen = 2 * fgreen2 * fgreen1;
            biggreen = (int)((ngreen * 255) + 0.5);
        } else {
            float ngreen = 1 - (2 * (1 - fgreen1) * (1- fgreen2));
            biggreen = (int)((ngreen * 255) + 0.5);
        } 
        
        if (fred2 <= 0.5) {
            float nred = 2 * fred2 * fred1;
            bigred = (int)((nred * 255) + 0.5);
        } else {
            float nred = 1 - (2 * (1 - fred1) * (1- fred2));
            bigred = (int)((nred * 255) + 0.5);
        }

    cout << bigblue << ", " << biggreen << ", " << bigred << endl;
}

void onlyColor(int blue, int green, int red, string color) {
    int bigblue;
    int biggreen;
    int bigred;
        if (color == "red") {
            bigblue = red;
            biggreen = red;
            bigred = red;
        } else if (color == "green") {
            bigblue = green;
            biggreen = green;
            bigred = green;
        } else {
            bigblue = blue;
            biggreen = blue;
            bigred = blue;
        }
        cout << bigblue << ", " << biggreen << ", " << bigred << endl;
};
    

void reverse(vector<int> nums) {

    vector<int> rev;
    for (int i = 0; i < nums.size(); i++) {
        rev.push_back(nums[nums.size() - i]);
    }

    for (int i = 0; i < rev.size(); i++) {
        cout << rev[i] << ", ";
    }
}



int main () {
    // screen(0, 0, 0, 87, 126, 150);

    // overlay(255, 1, 60, 127, 127, 0);

    onlyColor(100, 250, 67, "blue");

    vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    reverse(vec);


};