#pragma once
#include <Headers/precomp.h>
#include "glfw_initialization.h"

struct GLFWwindow;

namespace veng {
    class Window {
    public:
        Window(gsl::czstring name, glm::ivec2 size);
        ~Window();

        glm::ivec2 GetWindowSize() const;
        glm::ivec2 GetFramebufferSize() const;
        bool ShouldClose() const;
        GLFWwindow* GetHandle() const;

        bool TryMoveMonitor(std::uint16_t monitor_number);

    private:
        GLFWwindow* window_;
    };
}
