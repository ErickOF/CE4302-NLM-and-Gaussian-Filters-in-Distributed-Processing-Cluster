#!/bin/sh

# Generate ssh key
ssh-keygen

# Copy key
scp ~/.ssh/id_rsa.pub <user>@168.192.0.101:~/.ssh/authorized_keys
