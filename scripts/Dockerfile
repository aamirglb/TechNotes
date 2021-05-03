FROM jenkins/jenkins:2.277.2-lts-jdk11
USER root
RUN apt-get update && apt-get install -y apt-transport-https \
       ca-certificates curl gnupg2 \
       software-properties-common

RUN curl -fsSL https://download.docker.com/linux/debian/gpg | apt-key add -
RUN apt-key fingerprint 0EBFCD88
RUN add-apt-repository \
       "deb [arch=amd64] https://download.docker.com/linux/debian \
       $(lsb_release -cs) stable"

RUN apt-get update && apt-get install -y docker-ce-cli

ARG QT_VERSION=5.12.6

ENV DEBIAN_FRONTEND noninteractive

ENV DISPLAY :99

ENV QMAKESPEC linux-g++-64

ENV QT_PATH /opt/Qt
ENV QT_DESKTOP $QT_PATH/${QT_VERSION}/gcc_64

ENV PATH /usr/lib/ccache:$QT_DESKTOP/bin:$PATH

RUN apt-get update && apt-get -y --quiet --no-install-recommends install \
		apt-utils \
		build-essential \
		ca-certificates \
		ccache \
		cmake \
		curl \
		espeak \
		fuse \
		g++ \
		gcc \
		git \
		gosu \
		kmod \
		libespeak-dev \
		libfontconfig1 \
		libfuse2 \
		libgstreamer-plugins-base1.0-dev \
		libgstreamer1.0-0:amd64 \
		libgstreamer1.0-dev \
		libsdl2-dev \
		libssl-dev \
		libudev-dev \
		locales \
		make \
		ninja-build \
		openssh-client \
		openssl \
		pkg-config \
		python2 \
		rsync \
		speech-dispatcher \
		vim \
		wget \
		xvfb \
		zlib1g-dev \
	&& apt-get -y autoremove \
	&& apt-get clean autoclean \
	&& rm -rf /var/lib/apt/lists/{apt,dpkg,cache,log} /tmp/* /var/tmp/*

# create user with id 1001 (jenkins docker workflow default)
RUN useradd --shell /bin/bash -u 1001 -c "" -m user && usermod -a -G dialout user

USER jenkins
RUN jenkins-plugin-cli --plugins "blueocean:1.24.6 docker-workflow:1.26"