pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


pushd ./Engine
make clean
popd

pushd ./Sandbox
make clean
popd
