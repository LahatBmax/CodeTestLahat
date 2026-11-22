#include <iostream>
#include <fstream>
#include <filesystem>
#include "json.hpp"

using json = nlohmann::json;

// Cette fonction gère le chemin, les erreurs d'ouverture et le parsing
json Lire_fichier_json() {
    std::string pathIMAGEstring;
    std::cout << "Veuillez entrer le path du .json : ";
    std::getline(std::cin, pathIMAGEstring);
    
    if (!pathIMAGEstring.empty() && pathIMAGEstring.front() == '"')
        pathIMAGEstring = pathIMAGEstring.substr(1, pathIMAGEstring.size() - 2);

    std::filesystem::path json_path(pathIMAGEstring);

    if (!std::filesystem::exists(json_path)) {
        std::cerr << "Erreur : Le fichier specifie n'existe pas !" << std::endl;
        exit(1); // Quitte proprement si le fichier n'existe pas
    }

    std::ifstream fichier_json(json_path);
    if (!fichier_json.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier JSON." << std::endl;
        exit(1);
    }

    json data;
    fichier_json >> data;
    return data;
}