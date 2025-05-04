#pragma once
#include <vulkan/vulkan.h>
#include <Headers/glfw_window.h>

namespace veng {

    class Graphics {
        public:
        Graphics(gsl::not_null<Window*> window);
        ~Graphics();

        private:
        void InitializeVulkan();
        void CreateInstance();
        void SetupDebugMessenger();
        void PickPhysicalDevice();
        std::vector<gsl::czstring> GetRequiredInstanceExtensions();

        static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
        static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
        static bool AreAllExtensionsSupported(gsl::span<gsl::czstring> extensions);

        static std::vector<VkLayerProperties> GetSupportedValidatedLayers();
        static bool AreAllLayersSupported(gsl::span<gsl::czstring> layers);

        bool IsDeviceSuitable(VkPhysicalDevice device);
        std::vector<VkPhysicalDevice> GetAvailableDevices();

        VkInstance instance_ = nullptr;
        VkPhysicalDevice physical_device_ = nullptr;
        VkDebugUtilsMessengerEXT debug_messenger_;
        gsl::not_null<Window*> window_;
        bool validation_enabled_ = false;
    };

}