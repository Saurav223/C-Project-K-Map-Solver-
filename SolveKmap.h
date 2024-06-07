#ifndef SOLVEKMAP_H
#define SOLVEKMAP_H

#include <vector>
#include <bitset>
#include <algorithm>

class Implicant
{
    std::vector<int> minterms;
    std::vector<int> binary_rep;
    bool matched = false;

public:
    // constructors
    Implicant() {}
    Implicant(int size, int value)
    {
        minterms.push_back(value);
        std::bitset<32> bin(value);
        for (int i = size - 1; i >= 0; --i)
        {
            binary_rep.push_back(bin[i]);
        }
    }

    // getters
    std::vector<int> get_binary_rep() { return binary_rep; }
    std::vector<int> get_minterms() { return minterms; }
    bool getmatched() { return matched; }

    // setters
    void setmatched(bool b) { matched = b; }

    // operators
    friend Implicant operator^(Implicant &op1, Implicant &op2)
    {
        Implicant tmp;
        for (int i : op1.get_minterms())
        {
            tmp.minterms.push_back(i);
        }
        for (int i : op2.get_minterms())
        {
            tmp.minterms.push_back(i);
        }

        for (int i = 0; i < op1.binary_rep.size(); ++i)
        {
            if (op1.binary_rep[i] != op2.binary_rep[i])
            {
                tmp.binary_rep.push_back(-1);
            }
            else
            {
                tmp.binary_rep.push_back(op1.binary_rep[i]);
            }
        }
        return tmp;
    }
    friend bool operator==(Implicant &op1, Implicant &op2)
    {
        return op1.binary_rep == op2.binary_rep;
    }
};

int countOnes(std::vector<int> inp);

bool is_neighbour(std::vector<int> v1, std::vector<int> v2);

bool my_find(std::vector<int> v, int value);

std::vector<std::vector<Implicant>> group_minterms(std::vector<int> minterms, std::vector<int> dontcare, int n_vars);

std::vector<std::vector<Implicant>> match_pairs(std::vector<std::vector<Implicant>> &foo, std::vector<Implicant> &prime_implicants);

std::vector<Implicant> get_essential_prime_implicants(std::vector<Implicant> piv, std::vector<int> minterms);

std::vector<Implicant> solveKmap(int n_vars, std::vector<int> minterms, std::vector<int> dontcare);

std::string get_sop(std::vector<Implicant> epi);
std::vector<std::vector<int>> get_groups(std::vector<Implicant>);
#endif // SOLVEKMAP_H
