#!/bin/bash
echo
for arg in "$@"; do
    case "$arg" in
        -h|--help)
            echo "Usage: build.sh [OPTIONS]"
            echo "Options:"
            echo "  -h, --help      Show this help message"
            echo "  -c, --clean     Perform a clean build"
            echo "  -p, --preset    Specify a workflow to run"
            echo
            cmake --workflow --list-presets
            exit 0
            ;;
        -c|--clean)
            echo "Performing clean build..."
            fresh="--fresh"
            ;;
        -p|--preset)
            shift
            preset="$1"
            ;;
        *)
            echo "Unknown option: $arg"
            exit
            ;;
    esac
done

if [ -z "$preset" ]; then
    preset="default"
fi

echo "Executing preset \"$preset\"..."

cmake --workflow --preset=$preset $fresh