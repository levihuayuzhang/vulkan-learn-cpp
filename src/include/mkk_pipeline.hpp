#pragma once

#include <string>
#include <vector>
#include "mkk_device.hpp"

namespace mkk {
    struct PipelineConfigInfo {};

    class MkkPipeline {
        public:
            MkkPipeline (MkkDevice &device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo &configInfo);

            ~MkkPipeline() {}

            MkkPipeline(const MkkPipeline&) = delete;
            void operator = (const MkkPipeline&) = delete;

            static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
        
        private:
            static std::vector<char> readFile (const std::string& filePath);

            void createGraphicPipeline (const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo &configInfo);

            void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

            MkkDevice& mkkDevice;
            VkPipeline graphicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;
    };
}