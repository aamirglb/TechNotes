#!/usr/bin/env bash

create_config_file() {
    echo && echo "Generating params1.config file"
    echo ""

    if [[ -z ${MAVLINK_SYS_ID} || -z ${FMS_CLIENT_PORT} || \
          -z ${FMS_CLIENT_IP}  || -z ${FMS_SERVER_PORT} || \
          -z ${FMS_SERVER_IP} ]]; then

          echo "ERROR: Required environment varialbe/s not defined"
          echo ""
          echo "Please add following variable/s to the environment and re-run script"
          echo "MAVLINK_SYS_ID FMS_CLIENT_PORT FMS_CLIENT_IP FMS_SERVER_PORT 8FMS_SERVER_IP"
          echo ""
            exit 2
    else
        config_template="{
            \"rate\": 1,
            \"robot_name\": \"uav_${MAVLINK_SYS_ID}\",
            \"port\": ${FMS_CLIENT_PORT},
            \"server_port\": ${FMS_SERVER_PORT},
            \"ip_address\": \"${FMS_CLIENT_IP}\",
            \"host_ip_address\": \"${FMS_SERVER_IP}\"
            }"

        echo $config_template > params1.json
    fi
}

remove_config_file() {
    rm -rf params1.json
}

IMAGE_TAG=test:latest
DOCKERFILE=Dockerfile

create_config_file

echo && echo "Building $IMAGE_TAG image..." && echo

docker build -t ${IMAGE_TAG} -f ${DOCKERFILE} .

remove_config_file