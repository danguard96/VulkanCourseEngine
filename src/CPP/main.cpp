#include <Headers/precomp.h>
#include "Headers/glfw_initialization.h"
#include <Headers/glfw_monitor.h>
#include "Headers/glfw_window.h"
#include "Headers/graphics.h"

std::int32_t main(std::int32_t argc, gsl::czstring* argv) {
    veng::GlfwInitialization _glfw;

    veng::Window window("Vulkan Engine", {800, 600});
    window.TryMoveMonitor(0);

    veng::Graphics graphics(&window);

    while (!window.ShouldClose()) { glfwPollEvents(); }

    return EXIT_SUCCESS;
}
