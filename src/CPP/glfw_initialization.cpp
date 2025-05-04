#include "Headers/glfw_initialization.h"

namespace veng {

    void glfw_error_callback(std::int32_t error_code, gsl::czstring message) {
        spdlog::error("GLFW Validation: {}", message);
    }

    GlfwInitialization::GlfwInitialization() {

        glfwSetErrorCallback(glfw_error_callback);

        if (glfwInit() != GLFW_TRUE) std::exit(EXIT_FAILURE);
    }

    GlfwInitialization::~GlfwInitialization() { glfwTerminate(); }
}
