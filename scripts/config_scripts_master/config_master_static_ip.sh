#!/bin/sh

# Set static IP and mask
ifconfig eth0 192.168.0.100 netmask 255.255.255.0 up

# Set default gateway
route add default gw 192.168.1.1

# Set DNS
echo "nameserver 8.8.8.8" > /etc/resolv.conf
