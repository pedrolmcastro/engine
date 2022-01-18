pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


pushd ./Feather
make DEBUG=1
popd

# Update the Library in Sandbox
cp ./Feather/libFeather.a ./Sandbox/lib/

pushd ./Sandbox
make DEBUG=1
make run
popd
