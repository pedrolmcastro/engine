pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


pushd ./Feather
    make -s
popd

# Update the Library in Sandbox
cp ./Feather/libFeather.a ./Sandbox/lib/

pushd ./Sandbox
    # Rebuild on Configuration Change
    source ../data.sh
    if [ $1 != $last ]; then
        make clean
        echo "last=\"$1\"" > ../data.sh
    fi

    make $1=1
    make run
popd
