#include "mkk_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace mkk {
    MkkPipeline::MkkPipeline (const std::string& vertFilepath, const std::string& fragFilepath) {
        createGraphicPipeline(vertFilepath, fragFilepath);
    }

    std::vector<char> MkkPipeline::readFile (const std::string& filePath) {

        std::ifstream file{filePath, std::ios::ate | std::ios::binary};

        if (!file.is_open()) {
            throw std::runtime_error("Failed to Open File: " + filePath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    void MkkPipeline::createGraphicPipeline (const std::string& vertFilepath, const std::string& fragFilepath) {
        auto vertCode = readFile(vertFilepath);
        auto fragCode = readFile(fragFilepath);

        std::cout << "Vertex Shader Code Size: " << vertCode.size() << "\n";
        std::cout << "Fragment Shader Code Size: " << fragCode.size() << "\n";
    }
}