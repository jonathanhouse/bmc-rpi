#!/bin/bash 
sudo make 
cp kernel8.img /Volumes/bootfs/kernel8.img
diskutil eject /dev/disk4