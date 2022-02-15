pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


rm -r build/*
cmake -S src -B build -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF

pushd build
    make -s
popd


cp build/src/libglfw3.a ../../Sandbox/lib
cp build/src/glfw3.pc ../../Sandbox/lib
