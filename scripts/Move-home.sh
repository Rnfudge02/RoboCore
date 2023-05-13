#!/bin/bash

#Copyright (c) 2023, Robert Fudge
#All rights reserved.
#
#This source code is licensed under the BSD-style license found in the
#LICENSE file in the root directory of this source tree. 

if [ "$EUID" -e 0 ];then
    echo "This script should not be run as root, remove 'sudo' and try again"
    exit 1
fi

mkdir -p $HOME/Projects/C++/
cp -r ../RoboCore $HOME/Projects/C++/