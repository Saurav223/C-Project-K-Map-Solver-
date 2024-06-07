#ifndef KMAP_H
#define KMAP_H

#include <vector>
#include <string>
#include <sstream>

class KMap {
public:
    void Kmap(int size);
    void getOnes( std::string);
    void getDontCares( std::string);

    std::string res;
    void set(std::string);
    std::string get();

    int size;
    std::vector<int> ones;
    std::vector<int> dontCares;
    std::vector<std::vector<int>> groups;
    std::string ab;
    std::string bc;
    std::stringstream results;
    void repeat();
};
extern KMap mapp;

#endif // KMAP_H
