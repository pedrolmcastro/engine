pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


pushd ./Engine
make DEBUG=1
popd

# Update the Library in Sandbox
cp ./Engine/libEngine.a ./Sandbox/lib/

pushd ./Sandbox
make DEBUG=1
make run
popd
