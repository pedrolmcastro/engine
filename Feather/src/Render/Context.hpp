#pragma once


namespace Feather::Render {
    class Context {
    public:
        Context();
        ~Context();
    private:
        static bool init;
    };
}
