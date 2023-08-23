#!/bin/bash

for arg in "$@"; do
    case "$arg" in
        -h|--help)
            echo "Usage: build.sh [OPTIONS]"
            echo "Options:"
            echo "  -h, --help  Show this help message"
            echo "  -c, --clean Perform a clean build"
            exit
            ;;
        -c|--clean)
            echo "Performing clean build..."
            rm -rf build
            ;;
        *)
            echo "Unknown option: $arg"
            exit
            ;;
    esac
done

if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

cmake --build --preset=default