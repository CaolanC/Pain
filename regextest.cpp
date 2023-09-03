#include <regex>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::string a = "a\nb";

    for (char b : a)
    {
        if (b == '\n')
        {
            std::cout << "newline\n";
        };
    };    
};