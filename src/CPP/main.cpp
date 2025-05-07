#include <Headers/precomp.h>
#include "Headers/glfw_initialization.h"
#include <Headers/glfw_monitor.h>
#include "glm/gtc/matrix_transform.hpp"
#include "Headers/glfw_window.h"
#include "Headers/graphics.h"

std::int32_t main(std::int32_t argc, gsl::czstring* argv) {
    veng::GlfwInitialization _glfw;

    veng::Window window("Vulkan Engine", {800, 600});
    window.TryMoveMonitor(0);

    veng::Graphics graphics(&window);

    std::array<veng::Vertex, 3> vertices = {
        veng::Vertex{glm::vec3{0.0f, -0.5f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}},
        veng::Vertex{glm::vec3{0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}},
        veng::Vertex{glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}},
    };

    veng::BufferHandle buffer = graphics.CreateVertexBuffer(vertices);

    std::array<std::uint32_t, 3> indices = {0, 1, 2};

    veng::BufferHandle index_buffer = graphics.CreateIndexBuffer(indices);

    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    graphics.SetViewProjection(view, projection);

    while (!window.ShouldClose()) {
        glfwPollEvents();
        if (graphics.BeginFrame()) {
            graphics.RenderIndexedBuffer(buffer, index_buffer, indices.size());
            graphics.EndFrame();
        }
    }

    graphics.DestroyBuffer(buffer);
    graphics.DestroyBuffer(index_buffer);

    return EXIT_SUCCESS;
}
