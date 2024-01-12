
#include <cstdlib>
#include <first_app.hpp>
#include <iostream>

auto main() -> int {
    mkk::FirstApp app{};

    try{
        app.run();
    } catch (const std::exception &e){
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}