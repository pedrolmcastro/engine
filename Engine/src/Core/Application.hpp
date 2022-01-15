#pragma once


namespace Engine {
    class Application {
    public:
        Application();
        virtual ~Application();

        // Defined by the client
        static Application *create();

        void run();
    };
};
