#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

int getMinGates(vector<int> landingTimes, vector<int> takeOffTimes, int maxWaitTime, int initialPlanes) {
    if (!landingTimes.size()) return initialPlanes;
    if (!takeOffTimes.size()) return (landingTimes.size() + initialPlanes);
    for (auto& i : landingTimes) {
        int temp = i % 100;
        i = (i / 100) * 60 + temp;
    }
    for (auto& i : takeOffTimes) {
        int temp = i % 100;
        i = (i / 100) * 60 + temp;
    }
    int p_land = 0;
    int p_takeoff = 0;
    int curr_count = initialPlanes;
    int gates = initialPlanes;
    while (p_land < landingTimes.size()) {
        if (landingTimes[p_land] == takeOffTimes[p_takeoff]) {
            if (!initialPlanes) {
                gates = max(gates, ++curr_count);
                ++p_land;
                ++p_takeoff;
            }
            else {
                --curr_count;
                ++p_takeoff;
                --initialPlanes;
            }
        }
        else if (landingTimes[p_land] + maxWaitTime < takeOffTimes[p_takeoff]) {
            gates = max(gates, ++curr_count);
            ++p_land;
        }
        else if (landingTimes[p_land] + maxWaitTime >= takeOffTimes[p_takeoff]) {
            --curr_count;
            ++p_takeoff;
        }
        if (p_takeoff == takeOffTimes.size() && p_land != landingTimes.size()) {
            curr_count += landingTimes.size() - p_land;
            gates = max(gates, curr_count);
            break;
        }
    }
    return gates;
}

int main() {
    vector<int> land{ 1837,1837,1941 };
    vector<int> take_off{ 1837 };
    cout << getMinGates(land, take_off, 18, 1);
    return 0;
}