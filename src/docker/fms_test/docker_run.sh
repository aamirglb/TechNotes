#!/usr/bin/env bash

DOCKER_REPO="test:latest"
CONTAINER_NAME="fms_test"
USER_NAME=aamir
WORKSPACE_DIR=~/${CONTAINER_NAME}_shared_volume

if [ ! -d $WORKSPACE_DIR ]; then
    mkdir -p $WORKSPACE_DIR
fi

if [ "$(docker ps -aq -f name=${CONTAINER_NAME})" ]; then
    if [ "$(docker ps -aq -f status=exited -f name=${CONTAINER_NAME})" ]; then
        docker start ${CONTAINER_NAME}
    else
        docker exec -it --user $USER_NAME ${CONTAINER_NAME} bash
    fi
else
    docker run -it \
    --user=$USER_NAME \
    --workdir="/home/$USER_NAME" \
    --name=${CONTAINER_NAME} \
    --volume="${WORKSPACE_DIR}:/home/$USER_NAME/shared_volume:rw" \
    $DOCKER_REPO \
    bash
fi
