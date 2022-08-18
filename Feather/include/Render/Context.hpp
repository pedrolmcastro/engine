#pragma once


class GLFWwindow;

namespace Feather::Render {
    class Context {
    public:
        Context();
        ~Context();

        static void Version();
        static void Load(GLFWwindow* window);
    };
}
