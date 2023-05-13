#!/bin/bash

#Copyright (c) 2023, Robert Fudge
#All rights reserved.
#
#This source code is licensed under the BSD-style license found in the
#LICENSE file in the root directory of this source tree. 

if [ "$EUID" -ne 0 ];then
    echo "This script should be run as root, prepend 'sudo' and try again"
    exit 1
fi

USER_HOME=$(getent passwd $SUDO_USER | cut -d: -f6)

sudo dd if=/dev/zero of=$USER_HOME/RAMDISK/zero bs=4k count=100000