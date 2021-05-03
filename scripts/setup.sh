#!/bin/bash

XAUTH=/tmp/.docker.xauth
xauth_list=$(xauth nlist :0 | sed -e 's/^..../ffff/')
if [ ! -f $XAUTH ]
then
    echo XAUTH file does not exist. Creating one...
    touch $XAUTH
    chmod a+r $XAUTH
    if [ ! -z "$xauth_list" ]
    then
        echo $xauth_list | xauth -f $XAUTH nmerge -
    fi
fi

# Prevent executing "docker run" when xauth failed.
if [ ! -f $XAUTH ]
then
  echo "[$XAUTH] was not properly created. Exiting..."
  exit 1
fi

#xhost +local:root

docker run --name jenkins-blueocean \
  --network jenkins \
  --env DOCKER_HOST=tcp://docker:2376 \
  --env DOCKER_CERT_PATH=/certs/client --env DOCKER_TLS_VERIFY=1 \
  --env="DISPLAY=$DISPLAY" \
  --env="QT_X11_NO_MITSHM=1" \
  --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
  --volume="/etc/localtime:/etc/localtime:ro" \
  --volume="/home/aaal/Downloads:/home/jenkins/shared_volume:rw" \
  --volume="/dev/input:/dev/input" \
  --volume="$XAUTH:$XAUTH" \
  --env="XAUTHORITY=$XAUTH" \
  --privileged \
  --publish 8080:8080 --publish 50000:50000 \
  --volume jenkins-docker-certs:/certs/client:ro \
  myjenkins-blueocean:1.1