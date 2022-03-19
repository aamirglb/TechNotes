FROM ubuntu:latest

ARG USER=aamir

RUN adduser \
    --system \
    --shell /bin/bash \
    --gecos $USER \
    --group \
    --disabled-password \
    --home /home/$USER \
    $USER

USER $USER

COPY bashrc /home/$USER/.bashrc
COPY params1.json /home/$USER



