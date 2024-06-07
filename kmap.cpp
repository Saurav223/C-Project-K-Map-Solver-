#include <string>
#include <cmath>
#include <algorithm>
#include "kmap.h"
#include <map>
#include <sstream>
using namespace std;

void KMap::Kmap(int size) {
    this->size = size;
}

void KMap::getOnes(string input) {
    size_t pos = 0;
    while ((pos = input.find(",")) != string::npos) {
        ones.push_back(stoi(input.substr(0, pos)));
        input.erase(0, pos + 1);
    }
    ones.push_back(stoi(input));
}

void KMap::getDontCares(string input) {
    size_t pos = 0;
    while ((pos = input.find(",")) != string::npos) {
        dontCares.push_back(stoi(input.substr(0, pos)));
        input.erase(0, pos + 1);
    }
    dontCares.push_back(stoi(input));
}

void KMap::set(std::string s){
    res = s;
}
std::string KMap::get(){
    return res;
}

void KMap::repeat(){
    int size = groups.size();
    std::vector<int> red = groups[0];
    std::vector<int> blue;
    std::vector<int> green;
    std::vector<int> yellow;
    std::vector<int> gray;
    std::vector<int> magenta;
    if(1< size){
        blue =groups[1];
    }
    if(2< size){
        green =groups[2];
    }
    if(3< size){
        yellow = groups[3];
    }
    if(4< size){
        gray = groups[4];
    }
    if(5< size){
        magenta = groups[5];
    }

        std::map<int, int> countMap;

        // Count occurrences of each number
        for (int num : red) countMap[num]++;
        for (int num : blue) countMap[num]++;
        for (int num : green) countMap[num]++;
        for (int num : yellow) countMap[num]++;
        for (int num : gray) countMap[num]++;
        for (int num : magenta) countMap[num]++;

        std::stringstream result; // String stream to hold the result

        // Construct string for counts of numbers that occur more than once
        for (const auto& pair : countMap) {
            if (pair.second > 1) {
                result << "Group of Min-term " << pair.first << " = "<< " (";
                if (std::find(red.begin(), red.end(), pair.first) != red.end()) result << "red ";
                if (std::find(blue.begin(), blue.end(), pair.first) != blue.end()) result << "blue ";
                if (std::find(green.begin(), green.end(), pair.first) != green.end()) result << "green ";
                if (std::find(yellow.begin(), yellow.end(), pair.first) != yellow.end()) result << "yellow ";
                if (std::find(gray.begin(), gray.end(), pair.first) != gray.end()) result << "gray ";
                if (std::find(magenta.begin(), magenta.end(), pair.first) != magenta.end()) result << "magenta ";
                result << ")\n";
            }
        }
        results << result.str();


}

KMap mapp;


