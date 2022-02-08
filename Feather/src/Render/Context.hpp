#pragma once


class GLFWwindow;

namespace Feather::Render {
    class Context {
    public:
        Context();
        ~Context();

        static void Load(GLFWwindow* window);
    private:
        static bool init;
    };
}
