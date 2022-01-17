pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


pushd ./Engine
make DEBUG=0
popd

# Update the Library in Sandbox
cp ./Engine/libEngine.a ./Sandbox/lib/

pushd ./Sandbox
make DEBUG=0
make run
popd
