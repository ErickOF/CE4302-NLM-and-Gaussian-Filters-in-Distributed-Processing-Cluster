#!/bin/sh

SHARED_DIR=shared_dir
EXPORTS=/etc/exports


# Creating a shared directory
if [ ! -d $HOME/$SHARED_DIR ]; then
	mkdir $HOME/$SHARED_DIR;
fi

# Export directory by nfs to be used by slave nodes
sudo echo "/home/<user>/$SHARED_DIR 192.168.0.0/24(rw,no_subtree_check,async,no_root_squash)" >> $EXPORTS
sudo exportfs -a

# Show results
cat $EXPORTS

# Restart nfs service
sudo service nfs-kernel-server restart
