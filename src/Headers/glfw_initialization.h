#ifndef GLFW_INITIALIZATION_H
#define GLFW_INITIALIZATION_H

namespace veng {
    struct GlfwInitialization {
    public:
        GlfwInitialization();
        ~GlfwInitialization();

        GlfwInitialization(const GlfwInitialization&) = delete;
        GlfwInitialization& operator=(const GlfwInitialization&) = delete;
    };
}

#endif //GLFW_INITIALIZATION_H
