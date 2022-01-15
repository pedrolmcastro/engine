pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


pushd ./Engine
make
popd

# Update the Library in Sandbox
cp ./Engine/libEngine.a ./Sandbox/lib/

pushd ./Sandbox
make
make run
popd
