/*
    This program acts as a solution to the day 4 part 1 of AoC 2023
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
#include <array>
#include <utility>

std::array<std::tuple<std::unordered_set<unsigned>, std::unordered_set<unsigned>, unsigned>, 202> table;

unsigned get_cards(unsigned id)
{
    unsigned r = 0;
    for (const unsigned &i : std::get<1>(table.at(id)))
        if (std::get<0>(table.at(id)).count(i))
            std::get<2>(table.at(id + (++r))) += 1 * std::get<2>(table.at(id));

    return std::get<2>(table.at(id));
}

void process_line(std::istringstream &&ss, unsigned vp)
{

    for (unsigned x = 0, i = 0; i < 10; i++)
    {
        ss >> x;
        std::get<0>(table.at(vp)).insert(x);
    }

    while (ss.get() != '|') continue;
    ss.get();

    for (unsigned x = 0, i = 0; i < 25; i++)
    {
        ss >> x;
        std::get<1>(table.at(vp)).insert(x);
    }
    std::get<2>(table.at(vp)) = 1;
}

int main()
{
    std::ifstream fp ("../inputs/input4.txt");
    if (!fp.is_open())
        return EXIT_FAILURE;
    else
    {
        unsigned r = 0;
        std::string str;
        for (unsigned i = 0; std::getline(fp, str); i++)
            process_line(std::istringstream(str.substr(str.find_first_of(':') + 1)), i);

        for (unsigned i = 0; i < 202; i++)
            std::cout << (r += get_cards(i)) << '\n';
        std::cout << r << '\n';
        fp.close();
    }
    return EXIT_SUCCESS;
}