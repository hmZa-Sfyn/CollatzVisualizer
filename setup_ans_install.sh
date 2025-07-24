#!/bin/bash

# Function to display help message
show_help() {
    echo "Collatz Visualizer Setup and Run Script"
    echo "======================================"
    echo "This script installs prerequisites, compiles, and runs the Collatz Visualizer app."
    echo ""
    echo "Usage: $0 [option]"
    echo "Options:"
    echo "  --help, -h    Display this help message"
    echo "  --install     Install dependencies and compile the app"
    echo "  --run         Run the compiled app"
    echo "  --clean       Clean up compiled files"
    echo ""
    echo "How to use the app:"
    echo "1. Run './setup_and_run.sh --install' to set up dependencies and compile."
    echo "2. Run './setup_and_run.sh --run' to start the web server."
    echo "3. Open a browser and go to http://localhost:8080."
    echo "4. Enter a positive integer to visualize the Collatz sequence."
    echo "5. Results are saved in ./computated/<number>.json."
    echo ""
    echo "Notes:"
    echo "- Ensure collatz_webserver.cpp is in the current directory."
    echo "- The app requires internet access for Chart.js (via CDN)."
    echo "- JSON files are stored in ./computated/."
    exit 0
}

# Function to install dependencies
install_dependencies() {
    echo "Updating package list..."
    sudo apt-get update

    echo "Installing g++, Boost, and other dependencies..."
    sudo apt-get install -y g++ libboost-all-dev git curl

    echo "Creating include and lib directories..."
    mkdir -p include lib

    echo "Downloading nlohmann/json..."
    if [ ! -d "include/nlohmann" ]; then
        curl -L https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp -o include/nlohmann/json.hpp
    else
        echo "nlohmann/json already downloaded."
    fi

    echo "Downloading Crow..."
    if [ ! -f "include/crow.h" ]; then
        curl -L https://github.com/CrowCpp/crow/releases/download/v1.2.0/crow_all.h -o include/crow.h
    else
        echo "Crow already downloaded."
    fi

    echo "Creating computated directory..."
    mkdir -p computated

    echo "Compiling collatz_webserver.cpp..."
    if [ -f "collatz_webserver.cpp" ]; then
        g++ -std=c++17 collatz_webserver.cpp -o collatz_webserver -I./include -L./lib -pthread
        if [ $? -eq 0 ]; then
            echo "Compilation successful!"
        else
            echo "Compilation failed. Please check for errors."
            exit 1
        fi
    else
        echo "Error: collatz_webserver.cpp not found in current directory."
        exit 1
    fi
}

# Function to run the app
run_app() {
    if [ -f "collatz_webserver" ]; then
        echo "Starting Collatz Visualizer web server on http://localhost:8080..."
        ./collatz_webserver
    else
        echo "Error: collatz_webserver executable not found. Run './setup_and_run.sh --install' first."
        exit 1
    fi
}

# Function to clean up
clean_up() {
    echo "Cleaning up compiled files..."
    rm -f collatz_webserver
    echo "Clean complete."
}

# Check for arguments
case "$1" in
    --help|-h)
        show_help
        ;;
    --install)
        install_dependencies
        ;;
    --run)
        run_app
        ;;
    --clean)
        clean_up
        ;;
    *)
        echo "Invalid option. Use --help for usage information."
        exit 1
        ;;
esac