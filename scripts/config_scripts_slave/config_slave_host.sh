#!/bin/sh

HOSTS_DIR=/etc/hosts

# Add nodes
sudo echo "192.182.0.100 master master" >> $HOSTS_DIR
sudo echo "192.182.0.101 slave1 slave1" >> $HOSTS_DIR

# Show result
cat $HOSTS_DIR
