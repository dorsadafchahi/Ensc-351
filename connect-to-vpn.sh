#!/bin/bash

# Check if the script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run with sudo or as root."
  exit 1
fi

# Your SFU User ID
SFU_USERID="daa28"

# VPN server and port
VPN_SERVER="vpn.its.sfu.ca:10433"

# Run openfortivpn with the provided information
sudo openfortivpn $VPN_SERVER -u $SFU_USERID
