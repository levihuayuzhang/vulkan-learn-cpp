#pragma once

#include <string>
#include <vector>

namespace mkk {
    class MkkPipeline {
        public:
            MkkPipeline (const std::string& vertFilepath, const std::string& fragFilepath);
        
        private:
            static std::vector<char> readFile (const std::string& filePath);

            void createGraphicPipeline (const std::string& vertFilepath, const std::string& fragFilepath);
    };
}