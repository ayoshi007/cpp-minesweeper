while getopts "G:B:T" flag
do
    case "${flag}" in
        G) GENERATOR=${OPTARG};;
        B) BUILD_TYPE=${OPTARG};;
        T) CPPMS_ENABLE_TESTING=${OPTARG};;
    esac
done

if [[ -z "${GENERATOR}" ]] ; then
    GENERATOR="Ninja"
fi

if [[ -z "${BUILD_TYPE}" ]] ; then
    BUILD_TYPE=Debug
fi

if [[ -z "${CPPMS_ENABLE_TESTING}" ]] ; then
    if [[ "$BUILD_TYPE" = "Debug" ]] ; then
        CPPMS_ENABLE_TESTING=ON
    elif [[ "$BUILD_TYPE" = "Release" ]] ; then
        CPPMS_ENABLE_TESTING=OFF
    else
        CPPMS_ENABLE_TESTING=OFF
    fi
fi

BUILD_DIR=`echo ${BUILD_TYPE} | tr A-Z a-z`

command=(cmake -S . -B build)

echo "=== Options ==="
echo "Generator (-G):" "${GENERATOR}"
echo "Build type (-B):" "${BUILD_TYPE}"
echo "Enable testing (-T):" "${CPPMS_ENABLE_TESTING}"
echo

cmake -S . -B build/"${BUILD_DIR}" -G "${GENERATOR}" \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DCPPMS_ENABLE_TESTING="${CPPMS_ENABLE_TESTING}" \
    -DFTXUI_BUILD_EXAMPLES=OFF \
    -DFTXUI_BUILD_TESTS=OFF
cmake --build build/"${BUILD_DIR}"