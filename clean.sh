pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


pushd Feather
    make clean
popd

pushd Sandbox
    make clean
popd
