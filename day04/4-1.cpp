/*
    This program acts as a solution to the day 4 part 2 of AoC 2023
    Copyright (C) 2023 by Ezra Alvarion

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>

unsigned process_line(std::istringstream &&ss)
{
    std::unordered_set<unsigned> winnumbers;
    std::unordered_set<unsigned> ordnumbers;

    for (unsigned x = 0, i = 0; i < 10; i++)
    {
        ss >> x;
        winnumbers.insert(x);
    }

    while (ss.get() != '|') continue;
    ss.get();

    for (unsigned x = 0, i = 0; i < 25; i++)
    {
        ss >> x;
        ordnumbers.insert(x);
    }
    
    unsigned t = 1;

    for (auto &i : ordnumbers)
        if (winnumbers.count(i))
            t <<= 1;
    return t >> 1;
}

int main()
{
    std::ifstream fp ("../inputs/input4.txt");
    if (!fp.is_open())
        return EXIT_FAILURE;
    else
    {
        unsigned r = 0;
        for (std::string str; std::getline(fp, str);)
        {
            r += process_line(std::istringstream(str.substr(str.find_first_of(':') + 1)));
        }
        std::cout << r << '\n';
        fp.close();
    }
    return EXIT_SUCCESS;
}