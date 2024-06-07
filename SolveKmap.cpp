#include "SolveKmap.h"

int countOnes(std::vector<int> inp)
{
    int c = 0;
    for (int b : inp)
    {
        if (b == 1)
            c++;
    }
    return c;
}

bool is_neighbour(std::vector<int> v1, std::vector<int> v2)
{
    int different_counter = 0;
    for (int i = 0; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i])
            different_counter++;
    }

    return different_counter == 1;
}

bool my_find(std::vector<int> v, int value)
{
    bool result = false;
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

std::vector<std::vector<Implicant>> group_minterms(std::vector<int> minterms, std::vector<int> dontcare, int n_vars)
{
    // combine minterms and don't cares to a single vector
    std::vector<int> mt_plus_dc;
    for (int i : minterms)
    {
        mt_plus_dc.push_back(i);
    }
    for (int i : dontcare)
    {
        mt_plus_dc.push_back(i);
    }

    std::vector<std::vector<Implicant>> result;

    for (int i = 0; i <= n_vars; ++i)
    {
        std::vector<Implicant> group;
        for (int m : mt_plus_dc)
        {
            Implicant tmp(n_vars, m);
            if (countOnes(tmp.get_binary_rep()) == i)
            {
                group.push_back(tmp);
            }
        }
        result.push_back(group);
    }

    // remove empty vectors inside result
    result.erase(
        std::remove_if(result.begin(), result.end(), [](const std::vector<Implicant> &innerVector)
                       { return innerVector.empty(); }),
        result.end());

    return result;
}

std::vector<std::vector<Implicant>> match_pairs(std::vector<std::vector<Implicant>> &foo, std::vector<Implicant> &prime_implicants)
{
    // if(foo.size()==1) return foo;
    int no_of_matching_pairs = 0;

    std::vector<std::vector<Implicant>> result;
    for (int i = 0; i < foo.size() - 1; ++i)
    {
        std::vector<Implicant> group;
        for (Implicant &im1 : foo[i])
        {
            for (Implicant &im2 : foo[i + 1])
            {
                if (is_neighbour(im1.get_binary_rep(), im2.get_binary_rep()))
                {
                    group.push_back(im1 ^ im2);
                    im1.setmatched(true);
                    im2.setmatched(true);
                    no_of_matching_pairs++;
                }
            }
        }
        result.push_back(group);
    }

    if (!no_of_matching_pairs)
        return foo;

    // select unmatched implicants as prime implicants
    for (std::vector<Implicant> v : foo)
    {
        for (Implicant i : v)
        {
            if (!i.getmatched())
            {
                prime_implicants.push_back(i);
            }
        }
    }
    return match_pairs(result, prime_implicants);
}

std::vector<Implicant> get_essential_prime_implicants(std::vector<Implicant> piv, std::vector<int> minterms)
{
    std::vector<std::vector<int>> table;
    std::vector<Implicant> essential_prime_implicants;
    for (Implicant &p : piv)
    {
        std::vector<int> row;
        for (int i : minterms)
        {
            if (my_find(p.get_minterms(), i))
            {
                row.push_back(1);
            }
            else
            {
                row.push_back(0);
            }
        }
        table.push_back(row);
    }

    // process the columns to find the column with only 1, its corresponding row will be our essential prime implicant
    for (int col = 0; col < minterms.size(); ++col)
    {
        int count = 0;
        int row_no = 0;
        for (int row = 0; row < piv.size(); ++row)
        {
            if (table[row][col] == 1)
            {
                count++;
                row_no = row;
            }
        }
        if (count == 1)
        {
            essential_prime_implicants.push_back(piv[row_no]);
        }
    }
    return essential_prime_implicants;
}

std::vector<Implicant> solveKmap(int n_vars, std::vector<int> minterms, std::vector<int> dontcare)
{
    std::vector<Implicant> prime_implicants;

    std::vector<std::vector<Implicant>> step1 = group_minterms(minterms, dontcare, n_vars);
    std::vector<std::vector<Implicant>> step2 = match_pairs(step1, prime_implicants);

    // add all fully matched implicants to prime implicants
    for (int i = 0; i < step2.size(); ++i)
    {
        for (Implicant &im : step2[i])
        {
            prime_implicants.push_back(im);
        }
    }

    // remove repeating implicants from prime implicants
    for (int i = 0; i < prime_implicants.size(); ++i)
    {
        for (int j = i + 1; j < prime_implicants.size(); ++j)
        {
            if (prime_implicants[j] == prime_implicants[i])
            {
                prime_implicants.erase(prime_implicants.begin() + j);
                --j;
            }
        }
    }

    // get essential prime implicants from prime implicants
    std::vector<Implicant> ess = get_essential_prime_implicants(prime_implicants, minterms);

    // remove repeating implicants from essential prime implicants
    for (int i = 0; i < ess.size(); ++i)
    {
        for (int j = i + 1; j < ess.size(); ++j)
        {
            if (ess[j] == ess[i])
            {
                ess.erase(ess.begin() + j);
            }
        }
    }

    return ess;
}

std::string get_sop(std::vector<Implicant> epi)
{
    std::string result = "";
    for (Implicant im : epi)
    {
        for (int i = 0; i < im.get_binary_rep().size(); ++i)
        {
            int j = im.get_binary_rep()[i];
            if (j != -1)
            {
                result.push_back((char)(65 + i));
            }
            if (j == 0)
            {
                result += "'";
            }
        }
        result += "+";
    }
    result.pop_back();
    return result;
}
std::vector<std::vector<int>> get_groups(std::vector<Implicant> epi){
    std::vector<std::vector<int>> result;
    for(Implicant im:epi){
        result.push_back(im.get_minterms());
    }
    return result;
}
