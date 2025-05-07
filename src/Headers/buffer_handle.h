#pragma once
#include <vulkan/vulkan_core.h>

namespace veng {
    struct BufferHandle {
        VkBuffer buffer;
        VkDeviceMemory memory;
    };
}
