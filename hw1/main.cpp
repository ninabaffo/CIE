// Name: Nina Baffo
// Course: ENGR 2730
// Date: Sep 1, 2022
// FileName: homework1 (Sorry, I messed up the file that I named 'hw1' and I didn't want make it worse, so I just made a new file.)
// Assignment: hw1
// Description: Implement a C++ program that reports a variety of statistics related to a corn field.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

double averageFunction(double sum);
double stdDeviation(double sum, double avg, double xVal);

int main() {
    ifstream fin("baumerRadarSensorData.csv"); // Attempt to open file

    if (fin.fail()){
        cout << "Error: could not open baumerRadarSensorData.csv";
        return -1;
    }

    string colNames;
    getline(fin, colNames); //read first line of file
    cout << colNames << endl;

    string tmp, tmp1, tmp2, tmp3, date, time, lat, longitude, speed, angle, altitude, sat, RH, T, CC, C_Ht, C_HtIn, GC, G_Ht, G_HtIn, flags;
    double speedTemp, altTemp, satTemp, TTemp, RHTemp, C_HtInTemp, GCTemp, C_HtTemp, G_HtTemp, G_HtInTemp;

    while (!fin.eof()) {
        for (int i = 0; i <= 199; i++){
            getline(fin, tmp); //get the next line of the file
            date = tmp;

            getline(fin, date, ',');
            time = date;

            getline(fin, time, ',');
            lat = time;

            getline(fin, lat, ',');
            longitude = lat;

            getline(fin, longitude, ',');
            speed = longitude;

            getline(fin, speed, ',');
            angle = speed;
            speedTemp += stod(angle);

            getline(fin, angle, ',');
            altitude = angle;

            getline(fin, altitude, ',');
            sat = altitude;
            altTemp += stod(sat);

            getline(fin, sat, ',');
            RH = sat;
            satTemp += stod(RH);

            getline(fin, RH, ',');
            T = RH;
            RHTemp += stod(T);

            getline(fin, T, ',');
            CC = T;
            TTemp += stod(CC);

            getline(fin, CC, ',');
            C_Ht = CC;
            C_HtTemp += stod(CC);

            getline(fin, C_Ht, ',');
            C_HtIn = C_Ht;
            C_HtInTemp += stod(C_Ht);

            getline(fin, C_HtIn, ',');
            GC = C_HtIn;
            GCTemp += stod(C_HtIn);

            getline(fin, GC, ',');
            G_Ht = GC;
            G_HtTemp += stod(GC);

            getline(fin, G_HtIn, ',');
            G_Ht = G_HtIn;
            G_HtInTemp += stod(G_HtIn);

            getline(fin, G_Ht, ',');
            flags = G_Ht;

            getline(fin, flags, ',');
            tmp3 = flags;
            }

        double avgSpeed = averageFunction(speedTemp);
        double speedStd = stdDeviation(speedTemp, avgSpeed, 1.9);
        double avgAlt = averageFunction(altTemp);
        double altStd = stdDeviation(altTemp, avgAlt, 303);
        double avgSat = averageFunction(satTemp);
        double satStd = stdDeviation(satTemp, avgSat, 7);
        double avgT = averageFunction(TTemp);
        double Tstd = stdDeviation(TTemp, avgT, 30.3);
        double cornHeight;
        double belowCorn = C_HtTemp-G_HtTemp;
        double avgRH = averageFunction(belowCorn);
        double aboveCorn = C_HtInTemp - G_HtInTemp;
        double stdRH = stdDeviation(RHTemp, avgRH, 49.8);
        double aveRHabove = averageFunction(aboveCorn);
        double stdRHabove = stdDeviation(RHTemp, aveRHabove, 49.8);

        cout << "Enter minimum height of corn plant in inches: " << endl;
        cin >> cornHeight;
        double avgCorn, cornStd;
        if (cornHeight >= C_HtInTemp) {
            avgCorn = averageFunction(cornHeight);
            cornStd = stdDeviation(cornHeight, avgCorn, cornHeight);
        }

        cout << "The average speed of the sprayer was " << avgSpeed << " mph with standard deviation " << speedStd << " mph." << endl;
        cout << "The average altitude above mean sea level was " << avgAlt << "m with standard deviation " << altStd << " m" << endl;
        cout << "The average number of satellites was " << avgSat << " with standard deviation " << satStd << " in." << endl;
        cout << "The average temperature was " << avgT << " C with standard deviation " << Tstd << "C" << endl;
        cout << "The average height of the corn plants was: " << avgCorn << "in with standard deviation " << cornStd << "in." << endl;
        cout << "The average relative humidity when above corn plants was " << avgRH << "% with standard deviation " << stdRH << "%" << endl;
        cout << "The average relative humidity when not above corn plants was " << aveRHabove << "% with standard deviation "<< stdRHabove << "%" << endl;
    }
    fin.close();
    return 0;
}
// Function to compute the Average
// Input: sum of all values
// Output: the average
double averageFunction(double sum) {
    double avg = sum/200;
    return avg;
}
// Function to compute the standard deviation.
// Inputs: total sum, the average, and an Xvalue
// Output: standard deviation
double stdDeviation(double sum, double avg, double xVal) {
    double eqn = (xVal - avg);
    eqn = eqn*eqn;
    double mySum = xVal + avg + eqn + avg;
    double newSum = mySum/200;
    double finalAns = sqrt(newSum);
    return finalAns;
}