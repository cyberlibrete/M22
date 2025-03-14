#include <iostream>
#include <map>
#include <string>

bool is_anagram(const std::string& value_0, const std::string& value_1)
{
    if (value_0.length() != value_1.length())
        return false;

    std::map<char, int> counter;

    int idx = 0;
    while (idx < value_0.length())
    {
        counter[value_0[idx]]++;
        counter[value_1[idx]]--;
        idx++;
    }
    
    std::map<char, int>::iterator _it = counter.begin();
    while (_it != counter.end())
    {
        if (_it->second != 0)
            return false;
        ++_it;
    }
    return true;
}

int main()
{
    std::cout	<< "MODULE 22 | Task 03" << std::endl
				<< "Anagram" << std::endl
				<< "-------------------" << std::endl << std::endl;
    
    std::string value0, value1;

    std::cout   << "Enter two words separated by a space to check the possibility of anagramming the first meaning from the second" << std::endl
                << "> ";
    
    std::cin >> value0 >> value1;
  
    std::cout << "They are " << (is_anagram(value0, value1) ? "": "NOT ") << "anagrams." << std::endl;
    return 0;
}