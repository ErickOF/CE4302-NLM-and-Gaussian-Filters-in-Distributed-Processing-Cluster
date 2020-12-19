#!/bin/sh

SHARED_DIR=shared_dir

# Creating a shared directory if not exists
if [ ! -d $HOME/$SHARED_DIR ]; then
	mkdir $HOME/$SHARED_DIR;
fi

# Mount directory
sudo mount -t nfs 192.168.0.100:/path/to/dir/$SHARED_DIR /path/to/dir/$SHARED_DIR/

# Add directory to fstab
sudo echo "192.168.0.100:/path/to/dir/$SHARED_DIR/ /path/to/dir/$SHARED_DIR/ nfs rw,async,hard,intr 0 0" >> /etc/fstab

# Test
sudo umount /path/to/dir/$SHARED_DIR/
sudo mount -a
df -h
