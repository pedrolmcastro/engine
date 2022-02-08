pushd() { builtin pushd "$@" > /dev/null; }
popd()  { builtin popd  "$@" > /dev/null; }


source .data.sh
CONFIG=${1:-DEBUG}


# Compile GLFW
if [ $GLFW != "YES" ]; then
    pushd Vendor/GLFW
        ./build.sh
    popd
    sed -i "s/GLFW=\"$GLFW\"/GLFW=\"YES\"/g" .data.sh
fi

# Compile Glad
if [ $GLAD != "YES" ]; then
    pushd Vendor/Glad
        make clean
        make -s
    popd
    sed -i "s/GLAD=\"$GLAD\"/GLAD=\"YES\"/g" .data.sh
fi

# Compile Feather
pushd ./Feather
    make -s
popd

# Compile Sandbox
pushd Sandbox
    if [ $CONFIG != $LAST ]; then
        make clean
        sed -i "s/LAST=\"$LAST\"/LAST=\"$CONFIG\"/g" ../.data.sh
    fi

    export PKG_CONFIG_PATH=$(realpath lib)
    make $CONFIG=1 -s
    make run
popd
