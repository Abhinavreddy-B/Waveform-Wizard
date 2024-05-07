if [ "$EUID" -ne 0 ]; then
    echo "Please run this script as root or using sudo to be able to remove from app tray."
    exit 1
fi

echo "Attempting to remove Wavvy from your application list..."
APP_NAME="Wavvy"

if ! [ -e "/usr/share/applications/$APP_NAME.desktop" ]; then
    echo "Application '$APP_NAME' does not exists. Exiting..."
    exit 1
fi

rm /usr/share/applications/$APP_NAME.desktop
echo "Application '$APP_NAME' has been removed."