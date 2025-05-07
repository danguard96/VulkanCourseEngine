#pragma once
#include "glm/fwd.hpp"

namespace veng {
    struct UniformTransformations {
        glm::mat4 view;
        glm::mat4 projection;
    };
}
