#pragma once
#include <vulkan/vulkan.h>
#include <Headers/glfw_window.h>

namespace veng {

    class Graphics {
        public:
        Graphics(gsl::not_null<Window*> window);
        ~Graphics();

        private:

        struct QueueFamilyIndices {
            std::optional<uint32_t> graphics_family = std::nullopt;
            std::optional<uint32_t> presentation_family = std::nullopt;

            bool IsValid() const {return graphics_family.has_value() /*&& presentation_family.has_value()*/;}
        };

        void InitializeVulkan();
        void CreateInstance();
        void SetupDebugMessenger();
        void PickPhysicalDevice();
        void CreateLogicalDeviceAndQueues();
        std::vector<gsl::czstring> GetRequiredInstanceExtensions();

        static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
        static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
        static bool AreAllExtensionsSupported(gsl::span<gsl::czstring> extensions);

        static std::vector<VkLayerProperties> GetSupportedValidatedLayers();
        static bool AreAllLayersSupported(gsl::span<gsl::czstring> layers);

        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

        bool IsDeviceSuitable(VkPhysicalDevice device);
        std::vector<VkPhysicalDevice> GetAvailableDevices();

        VkInstance instance_ = nullptr;
        VkDebugUtilsMessengerEXT debug_messenger_ = nullptr;

        VkPhysicalDevice physical_device_ = nullptr;
        VkDevice logical_device_ = nullptr;
        VkQueue graphics_queue_ = nullptr;

        gsl::not_null<Window*> window_;
        bool validation_enabled_ = false;
    };

}