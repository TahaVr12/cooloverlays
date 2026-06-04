set -e

APP_NAME="overlay"
SRC_DIR="src"
COMMON_SRC="$SRC_DIR/main.cpp"

TARGET="$1"
if [ -z "$TARGET" ]; then
    case "$(uname -s)" in
        Linux*)               TARGET="linux"   ;;
        MINGW*|MSYS*|CYGWIN*) TARGET="windows" ;;
        *) echo "Unknown OS, assuming linux"; TARGET="linux" ;;
    esac
fi

case "$TARGET" in
  linux)
    CXX="g++"
    BACKEND="$SRC_DIR/globalmouse_linux.cpp"
    OUT="$APP_NAME"
    LIBS="-lraylib -lX11 -lGL -lm -lpthread -ldl -lrt"
    ;;
  windows)
    if [ "$(uname -s)" = "Linux" ] && command -v x86_64-w64-mingw32-g++ >/dev/null 2>&1; then
        CXX="x86_64-w64-mingw32-g++"
    else
        CXX="g++"
    fi
    BACKEND="$SRC_DIR/globalmouse_windows.cpp"
    OUT="$APP_NAME.exe"
    LIBS="-lraylib -lopengl32 -lgdi32 -lwinmm"
    ;;
  *)
    echo "wtf is '$TARGET'??? use linux or windows"
    exit 1
    ;;
esac

echo ">> im buildings [$TARGET] with $CXX  ->  $OUT"
"$CXX" "$COMMON_SRC" "$BACKEND" -o "$OUT" -I"$SRC_DIR" $LIBS
echo ">> im finnish:  ./$OUT"