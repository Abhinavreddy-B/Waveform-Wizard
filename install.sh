#!/bin/bash

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Function to display error message and exit script
display_error() {
    echo -e "${RED}Error: $1${NC}" >&2
    exit 1
}

# Function to display success message
display_success() {
    echo -e "${GREEN}$1${NC}"
}

# Function to display warning message
display_warning() {
    echo -e "${YELLOW}$1${NC}"
}

# Echo messages with color
display_warning "Installing python requirements..."
pip install -r requirements.txt || display_error "Failed to install python requirements"
display_success "Installed python requirements"

display_warning "Compiling resample library..."
cd app/dependencies/resample/lib/resampleWrapper || display_error "Failed to change directory"
rm -f *.o examples/*.o 2>/dev/null # Redirect error output to /dev/null
g++ -c *.cpp -lm -fopenmp -fPIC || display_error "Failed to compile resample library"
g++ -c -o examples/resample.o examples/resample.cpp -lm -fopenmp -I ./ -fPIC || display_error "Failed to compile resample examples"
g++ -shared *.o examples/resample.o -o resampleWrapper.so -fPIC -fopenmp || display_error "Failed to link resample library"
cd ../../../../../
display_success "Compiling resample library successfully"

display_warning "Compiling ZERO_TIME_WIND_SPECTRUM library..."
cd app/dependencies/ZERO_TIME_WIND_SPECTRUM/lib/TIME_entrypoint_Wrapper || display_error "Failed to change directory"
rm -f *.o 2>/dev/null
g++ -c *.cpp -lm -fopenmp -fPIC || display_error "Failed to compile ZERO_TIME_WIND_SPECTRUM library"
g++ -c -o TIME_entrypoint.o TIME_entrypoint.cpp -lm -fopenmp -I ./ -fPIC || display_error "Failed to compile TIME_entrypoint"
g++ -shared *.o -o libTIME.so -fPIC -fopenmp || display_error "Failed to link libTIME"
cd ../../../../../
display_success "Compiling ZERO_TIME_WIND_SPECTRUM library successfully"

display_warning "Installing pyinstaller..."
pip3 install pyinstaller || display_error "Failed to install pyinstaller"
display_success "Installed pyinstaller successfully"

display_warning "Building files..."
rm -rf build dist
pyinstaller wavvy.spec || display_error "Failed to build"
display_success "Built successfully"

display_warning "Adding Wavvy to your application list..."
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
BASE_DIR="$SCRIPT_DIR/dist/wavvy"
BINARY_NAME="wavvy"
BINARY_PATH="$BASE_DIR/$BINARY_NAME"
APP_NAME="Wavvy"
APP_DESCRIPTION="Audio analysis tool"
ICON_PATH="$SCRIPT_DIR/assets/logo.png"
WORKING_DIRECTORY="$BASE_DIR"
cd "$BASE_DIR" || display_error "Failed to change directory"
display_warning "Switching to root for privileged operations (adding application to your system tray)"
sudo su <<EOF
  echo "[Desktop Entry]
  Version=1.0
  Type=Application
  Name=$APP_NAME
  Comment=$APP_DESCRIPTION
  Exec=$BINARY_PATH
  Icon=$ICON_PATH
  Terminal=false
  Categories=Utility;" > /usr/share/applications/$APP_NAME.desktop || exit 1
EOF
display_success "Application '$APP_NAME' has been added."
