#!/bin/bash
sudo docker run \
    --rm\
    -u $(id -u):$(id -g) \
    -v .:/home/dev/project \
    throwtheswitch/madsciencelab:latest \
    ceedling test:all
