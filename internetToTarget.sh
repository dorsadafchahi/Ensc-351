#!/bin/sh
sudo iptables --table nat --append POSTROUTING --out-interface ens33 -j MASQUERADE
sudo iptables --append FORWARD --in-interface enx9889247b7ee7 -j ACCEPT
echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward
