RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

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

if [ "$EUID" -ne 0 ]; then
    display_error "Please run this script as root or using sudo to be able to remove from app tray."
    exit 1
fi

display_warning "Attempting to remove Wavvy from your application list..."
APP_NAME="Wavvy"

if ! [ -e "/usr/share/applications/$APP_NAME.desktop" ]; then
    display_error "Application '$APP_NAME' does not exists. Exiting..."
fi

rm /usr/share/applications/$APP_NAME.desktop
display_success "Application '$APP_NAME' has been removed."