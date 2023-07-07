#!/bin/bash

usage_msg () {
    cat << EOF
Usage:
./build.sh [options]

Options:                        Description:                    Default:
-g |--generator <GENERATOR>     The build generator to use      "Ninja"

-c | --config <CONFIG>          Build configuration name        "Debug"

-t |--enable-tests              Builds tests and registers      On if config is "Debug",
                                with CTest                      off otherwise

-nt|--disable-tests             Does not build tests            Opposite of -t

-ui|--run-ui-tests              Will build                      Off
                                interactive UI tests

Make sure you have your desired build generator installed on your system
If the configuration is "Debug", testing will be turned on
If testing is turned off, the interactive UI tests will be off regardless of its option
If both -t and -nt are specified, the one appearing later will be reflected in the build.
EOF
    exit
}

# parse options
while [[ "$#" -gt 0 ]]; do
    case "$1" in
        -g|--generator)
            [ -z "$2" ] && usage_msg
            GENERATOR="$2"
            shift ;;
        -c|--config)
            [ -z "$2" ] && usage_msg
            CONFIG="$2"
            shift ;;
        -t|--enable-tests)
            CPPMS_ENABLE_TESTING=ON ;;
        -nt|--disable-tests)
            CPPMS_ENABLE_TESTING=OFF ;;
        -ui|--run-ui-tests)
            CPPMS_RUN_UI_TESTS=ON ;;
        -h|--help)
            usage_msg ;;
        *)
            usage_msg ;;
    esac
    shift
done

# configure default arguments
if [[ -z "${GENERATOR}" ]] ; then
    GENERATOR="Ninja"
fi

if [[ -z "${CONFIG}" ]] ; then
    CONFIG=Debug
fi

if [[ -z "${CPPMS_ENABLE_TESTING}" ]] ; then
    if [[ "${CONFIG}" = "Debug" ]] ; then
        CPPMS_ENABLE_TESTING=ON
    elif [[ "${CONFIG}" = "Release" ]] ; then
        CPPMS_ENABLE_TESTING=OFF
    else
        CPPMS_ENABLE_TESTING=OFF
    fi
fi

if [[ -z "${CPPMS_RUN_UI_TESTS}" ]] ; then
    CPPMS_RUN_UI_TESTS=OFF
elif [[ "${CPPMS_ENABLE_TESTING}" = "OFF" ]] ; then
    CPPMS_RUN_UI_TESTS=OFF
fi


BUILD_DIR=`echo ${CONFIG} | tr A-Z a-z`

command=(cmake -S . -B build)

# CPPMS_RUN_UI_TESTS not working
cat << EOF
=== Options ===
Generator (-g):         ${GENERATOR}
Configuration (-c):     ${CONFIG}
Build tests (-t,-nt):   ${CPPMS_ENABLE_TESTING}
Run UI tests (-ui):     ${CPPMS_RUN_UI_TESTS}
EOF

cmake -S . -B build/"${BUILD_DIR}" -G "${GENERATOR}" \
    -DCMAKE_BUILD_TYPE="${CONFIG}" \
    -DCPPMS_ENABLE_TESTING="${CPPMS_ENABLE_TESTING}" \
    -DCPPMS_RUN_UI_TESTS="${CPPMS_RUN_UI_TESTS}" \
    -DFTXUI_BUILD_EXAMPLES=OFF \
    -DFTXUI_BUILD_TESTS=OFF
cmake --build build/"${BUILD_DIR}"