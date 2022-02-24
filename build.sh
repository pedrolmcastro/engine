pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


source .data.sh
CONFIG=${1:-DEBUG}


if [ $STB != "YES" ]; then
    pushd Vendor/stb
        make clean
        make -s
    popd

    sed -i "s/STB=\"$STB\"/STB=\"YES\"/g" .data.sh
fi

if [ $GLAD != "YES" ]; then
    pushd Vendor/Glad
        make clean
        make -s
    popd

    sed -i "s/GLAD=\"$GLAD\"/GLAD=\"YES\"/g" .data.sh
fi

if [ $GLFW != "YES" ]; then
    pushd Vendor/GLFW
        ./build.sh
    popd

    sed -i "s/GLFW=\"$GLFW\"/GLFW=\"YES\"/g" .data.sh
fi


if [ $CONFIG != $LAST ]; then
    pushd Feather
        make clean
    popd

    pushd Sandbox
        make clean
    popd

    sed -i "s/LAST=\"$LAST\"/LAST=\"$CONFIG\"/g" .data.sh
fi

pushd Feather
    make $CONFIG=1 -s
popd

pushd Sandbox
    export PKG_CONFIG_PATH=$(realpath lib)
    make $CONFIG=1 -s

    make run
popd
