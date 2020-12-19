#!/bin/sh

# Generate ssh key
ssh-keygen

# Copy ssh key
scp ~/.ssh/id_rsa.pub <user>@168.192.0.100:~/.ssh/authorized_keys
