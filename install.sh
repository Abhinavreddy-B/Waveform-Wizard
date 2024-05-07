echo "Installing python requirements..."
pip install -r requirements.txt
echo "Installed python requirements"

echo "Compiling resample library..."
cd app/dependencies/resample/lib/resampleWrapper
rm *.o examples/*.o || echo "No .o files to remove, continuing silently"
g++ -c *.cpp -lm -fopenmp -fPIC
g++ -c -o examples/resample.o examples/resample.cpp -lm -fopenmp -I ./ -fPIC
g++ -shared *.o examples/resample.o -o resampleWrapper.so -fPIC -fopenmp
cd ../../../../../
echo "Compiling resample library succesfully"

echo "Compiling ZERO_TIME_WIND_SPECTRUM library..."
cd app/dependencies/ZERO_TIME_WIND_SPECTRUM/lib/TIME_entrypoint_Wrapper
rm *.o || echo "No .o files to remove, continuing silently"
g++ -c *.cpp -lm -fopenmp -fPIC
g++ -c -o TIME_entrypoint.o TIME_entrypoint.cpp -lm -fopenmp -I ./ -fPIC
g++ -shared *.o -o libTIME.so -fPIC -fopenmp
cd ../../../../../
echo "Compiling ZERO_TIME_WIND_SPECTRUM library succesfully"

echo "Adding Wavvy to your application list..."
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
BASE_DIR="$SCRIPT_DIR/app"
FILE_NAME="main.py"
FILE_PATH="$BASE_DIR/$FILE_NAME"
APP_NAME="Wavvy"
APP_DESCRIPTION="Audio analysis tool"
ICON_PATH="$SCRIPT_DIR/assets/logo.jpeg"
WORKING_DIRECTORY="$BASE_DIR"
cd "$BASE_DIR" || exit

echo "Switching to root for privileged operations (adding application to your system tray)"
sudo su <<EOF
  echo "[Desktop Entry]
  Version=1.0
  Type=Application
  Name=$APP_NAME
  Comment=$APP_DESCRIPTION
  Exec=python3 $FILE_PATH
  Icon=$ICON_PATH
  Terminal=false
  Categories=Utility;" > /usr/share/applications/$APP_NAME.desktop
EOF

echo "Application '$APP_NAME' has been added."