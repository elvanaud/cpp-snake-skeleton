cmake_minimum_required( VERSION 3.0 )
project(SnakeCpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
    -Wall    
    -Wextra  
    -Wshadow  
    -Wnon-virtual-dtor 
    -Wfatal-errors
)

include_directories(include)
add_subdirectory( src )

set(SFML_DIR "D:/MesDocuments/Informatique/Ordinateur/Programmation/C++/Librairies/SFML/SFML-install/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


add_executable(${PROJECT_NAME}.out main.cpp)
target_link_libraries(${PROJECT_NAME}.out PUBLIC ${PROJECT_NAME} sfml-graphics sfml-audio)
#target_link_libraries(${PROJECT_NAME}.out sfml-graphics sfml-audio)

install(TARGETS ${PROJECT_NAME}.out DESTINATION bin)