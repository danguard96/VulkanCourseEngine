#pragma once
#include <Headers/glfw_window.h>
#include <Headers/buffer_handle.h>
#include <Headers/vertex.h>
#include <Headers/uniform_transformations.h>

namespace veng {
    class Graphics final {
    public:
        Graphics(gsl::not_null<Window*> window);
        ~Graphics();

        bool BeginFrame();
        void SetModelMatrix(glm::mat4 model);
        void SetViewProjection(glm::mat4 view, glm::mat4 projection);
        void RenderBuffer(BufferHandle handle, std::uint32_t vertex_count);
        void RenderIndexedBuffer(BufferHandle vertex_buffer, BufferHandle index_buffer, std::uint32_t count);
        void EndFrame();

        BufferHandle CreateVertexBuffer(const gsl::span<Vertex> vertices);
        BufferHandle CreateIndexBuffer(const gsl::span<uint32_t> indices);
        void DestroyBuffer(BufferHandle handle);

    private:
        struct QueueFamilyIndices {
            std::optional<uint32_t> graphics_family = std::nullopt;
            std::optional<uint32_t> presentation_family = std::nullopt;

            bool IsValid() const { return graphics_family.has_value() && presentation_family.has_value(); }
        };

        struct SwapchainProperties {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> present_modes;
            bool IsValid() const { return !formats.empty() && !present_modes.empty(); }
        };

        void InitializeVulkan();
        void CreateInstance();
        void SetupDebugMessenger();
        void PickPhysicalDevice();
        void CreateLogicalDeviceAndQueues();
        void CreateSurface();
        void CreateSwapchain();
        void CreateImageViews();
        void CreateRenderPass();
        void CreateGraphicsPipeline();
        void CreateFramebuffers();
        void CreateCommandPool();
        void CreateCommandBuffer();
        void CreateSignals();
        void CreateDescriptorSetLayout();
        void CreateDescriptorPool();
        void CreateDescriptorSet();

        void RecreateSwapchain();
        void CleanupSwapchain();

        //Rendering

        void BeginCommands();
        void EndCommands();

        std::vector<gsl::czstring> GetRequiredInstanceExtensions();

        static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
        static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
        static bool AreAllExtensionsSupported(gsl::span<gsl::czstring> extensions);

        static std::vector<VkLayerProperties> GetSupportedValidatedLayers();
        static bool AreAllLayersSupported(gsl::span<gsl::czstring> layers);

        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
        SwapchainProperties GetSwapchainProperties(VkPhysicalDevice device);

        bool IsDeviceSuitable(VkPhysicalDevice device);
        std::vector<VkPhysicalDevice> GetAvailableDevices();
        std::vector<VkExtensionProperties> GetDeviceAvailableExtensions(VkPhysicalDevice device);
        bool AreAllDeviceExtensionsSupported(VkPhysicalDevice device);

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(gsl::span<VkSurfaceFormatKHR> formats);
        VkPresentModeKHR ChooseSwapPresentMode(gsl::span<VkPresentModeKHR> modes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        std::uint32_t ChooseSwapImageCount(const VkSurfaceCapabilitiesKHR& capabilities);

        VkShaderModule CreateShaderModule(gsl::span<std::uint8_t> buffer);

        std::uint32_t FindMemoryType(std::uint32_t type_bits_filter, VkMemoryPropertyFlags required_properties);

        BufferHandle CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
        VkCommandBuffer BeginTransientCommandBuffer();
        void EndTransientCommandBuffer(VkCommandBuffer command_buffer);
        void CreateUniformBuffers();

        VkViewport GetViewport();
        VkRect2D GetScissor();

        std::array<gsl::czstring, 1> required_device_extensions_{
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

        VkInstance instance_ = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debug_messenger_ = VK_NULL_HANDLE;

        VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
        VkDevice logical_device_ = VK_NULL_HANDLE;
        VkQueue graphics_queue_ = VK_NULL_HANDLE;
        VkQueue present_queue_ = VK_NULL_HANDLE;

        VkSurfaceKHR surface_ = VK_NULL_HANDLE;
        VkSwapchainKHR swap_chain_ = VK_NULL_HANDLE;
        VkSurfaceFormatKHR surface_format_;
        VkPresentModeKHR present_mode_;
        VkExtent2D extent_;
        std::vector<VkImage> swap_chain_images_;
        std::vector<VkImageView> swap_chain_image_views_;
        std::vector<VkFramebuffer> swap_chain_framebuffers_;

        VkPipelineLayout pipeline_layout_ = VK_NULL_HANDLE;
        VkRenderPass render_pass_ = VK_NULL_HANDLE;
        VkPipeline pipeline_ = VK_NULL_HANDLE;
        VkDescriptorSetLayout descriptor_set_layout_ = VK_NULL_HANDLE;

        VkCommandPool command_pool_ = VK_NULL_HANDLE;
        VkCommandBuffer command_buffer_ = VK_NULL_HANDLE;

        VkSemaphore image_available_signal_ = VK_NULL_HANDLE;
        VkSemaphore render_finished_signal_ = VK_NULL_HANDLE;
        VkFence still_rendering_fence_ = VK_NULL_HANDLE;

        std::uint32_t current_image_index_ = 0;

        VkDescriptorPool descriptor_pool_ = VK_NULL_HANDLE;
        VkDescriptorSet descriptor_set_ = VK_NULL_HANDLE;
        BufferHandle uniform_buffer_;
        void* uniform_buffer_location_;

        gsl::not_null<Window*> window_;
        bool validation_enabled_ = false;
    };
}
