#!/bin/bash

#Copyright (c) 2023, Robert Fudge
#All rights reserved.
#
#This source code is licensed under the BSD-style license found in the
#LICENSE file in the root directory of this source tree. 

if [ "$EUID" -ne 0 ];then
    echo "Please run this script as root"
    exit 1
fi

USER_HOME=$(getent passwd $SUDO_USER | cut -d: -f6)

mkdir $USER_HOME/RAMDISK
sudo mount -t tmpfs -o size=2048m RAMDISK $USER_HOME/RAMDISK