# Docker

* **Docker** is a platform for running applications in an _isolated environment_ called a **_"container"_** (or Docker container). 

* Applications like Jenkins can be downloaded as read-only "images" (or Docker images), each of which is run in Docker as a container. 

* A Docker container is in effect a "running instance" of a Docker image. From this perspective, an image is stored permanently more or less (i.e. insofar as image updates are published), whereas containers are stored temporarily. 

* Docker’s fundamental platform and container design means that a single Docker image (for any given application like Jenkins) can be run on any supported operating system (macOS, Linux and Windows) or cloud service (AWS and Azure) which is also running Docker.

* To always restart a container after system restart, use `--restart` flag

```shell
$ docker run -d --restart=always redis
```

* To stop the container from restarting always use `docker update` command

```shell
$ docker update --restart=no redis
```

* Container is an isolated environment for running applications. Lightweight and use OS of the host operating system.

* Hypervisors: VirtualBox, VMWare, Hyper-V (Windows only)

* Container is a special process.

```shell
$ docker image ls
$ docker images

# List running container
$ docker ps

# List all container
$ docker ps -a
```

Linux Distros (More than 1000 distributation of Linux)
1. Ubuntu
1. Debian
1. Alpine
1. Fedora
1. CentOS

Package Managers
1. npm
1. yarn
1. pip 
1. NuGet 
1. apt (advance package tool) apt-get is older version

```
# 
$ apt list
$ apt update # update package database
$ apt list
```

* Container lives in container repository. Public repository for Docker called DockerHub. (10K+ container images)

```shell
$ docker stop container_name
$ docker start container_name
$ docker ps --help
# Remove all containers 
$ docker rm $(docker ps -aq)
# force remove running containers
$ docker rm -f $(docker ps -aq)

$ docker ps --format "ID\t{{.ID}}\n"
```

* Docker volumes allow to share data between host and container and between containers.

* volumen: source:destination:ro

* nginx server serve's website from location "usr/share/nginx/html"

bootstrap single page template
https://github.com/StartBootstrap/startbootstrap-grayscale.git

https://www.youtube.com/watch?v=p28piYY_wv8