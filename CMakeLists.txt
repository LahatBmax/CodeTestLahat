cmake_minimum_required(VERSION 3.14)
project(Reconstruction3D_XA CXX)

# Spécifie la norme C++ (C++17 est recommandé pour std::filesystem et nlohmann/json)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Recherche de la bibliothèque Eigen3 (nécessaire pour les matrices et la SVD)
find_package(Eigen3 REQUIRED)

# 2. Recherche de la bibliothèque nlohmann_json (pour parser le JSON)
find_package(nlohmann_json REQUIRED)

# 3. Déclaration de ton exécutable principal
# Liste ici tous tes fichiers source (.cpp) et d'en-tête (.hpp)
add_executable(Reconstruction3D
    Main.cpp
    P_intrinseque.cpp
    P_extrinseque.cpp
    XACamera.cpp
    ProjectionMultivues.cpp
)

# 4. Association des bibliothèques externes à ton exécutable
target_link_libraries(Reconstruction3D PRIVATE 
    Eigen3::Eigen 
    nlohmann_json::nlohmann_json
)