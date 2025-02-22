#include <string>
#include <vector>
#include <iostream>
#include <cassert>

namespace stringutils{

    /** splits str into vector of substrings, str is not changed */
    std::vector<std::string> split(std::string str, const std::string delim)
    {
        std::vector<std::string> res;
        size_t pos;
        while ((pos = str.find(delim)) != std::string::npos)
        {
            res.push_back(str.substr(0, pos));
            str.erase(0, pos + delim.length());
        }
        res.push_back(str);
        return res;
    }


    /** joins a vector of strings into a single string */
    std::string join(const std::vector<std::string> &strs, const std::string delim)
    {
        if (strs.size() == 0) return "";
        std::vector<char> res;
        for (uint i = 0; i < strs.size()-1; ++i)
        {
            for (auto c: strs[i]) res.push_back(c);
            for (auto c: delim) res.push_back(c);
        }
        for (auto c: strs[strs.size()-1]) res.push_back(c);
        return std::string{res.begin(), res.end()};
    }

}
