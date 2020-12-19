#!/bin/sh

# Add nodes
sudo echo "192.182.0.100 master master" >> /etc/exports
sudo echo "192.182.0.101 slave1 slave1" >> /etc/exports

# Show result
cat /etc/hosts
