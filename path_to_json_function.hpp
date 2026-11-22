#include <iostream>
#include <string>
#include <filesystem>

std::filesystem::path path_json_function()
{ 
std::string pathIMAGEstring;
std::filesystem::path Pathimagev2;

std::cout << "veuillez entrez le path du .json : ";
std::getline(std::cin, pathIMAGEstring);
if (!pathIMAGEstring.empty() && pathIMAGEstring.front() == '"')
pathIMAGEstring = pathIMAGEstring.substr(1, pathIMAGEstring.size() - 2);

return Pathimagev2 = pathIMAGEstring;

}