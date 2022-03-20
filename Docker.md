# Docker

* **Docker** is a platform for running applications in an _isolated environment_ called a **_"container"_** (or Docker container).

* **Podman** and **Containerd** are other alternatives to Docker.

* ![Play With Docker PWD](https://labs.play-with-docker.com)

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

* "ID:\t{{.ID}}\nNAME:\t{{.Names}}\nIMAGE:\t{{.Image}}\nPORTS:\t{{.Ports}}\nCOMMAND\t{{.Command}}\nCREATED\t{{.CreatedAt}}\nSTATUS:\t{{.Status}}\n"

* Use --volume-from option to mount volumne from one container to other container

# Docker In Practice

* **Docker Images**: An image is a collection of filesystem layers and some metadata.
Taken together, they can be spun up as Docker containers.

* **Layers**: A layer is a collection of changes to files.

* **Containers**: A container is a running instance of an image. You can have multiple  running from the same image.

* Docker Commands:

 | Commands |  Purpose |
 |----------|----------|
 | `docker build` | Build a Docker image |
 | `docker run` | Run a Docker image as a container |
 | `docker commit` | Commit a Docker container as an image |
 | `docker tag` | Tag a Docker image |

 * The metadata has information on environment variables, port mappings, volumes, and other details.

 * `docker diff <container-name>` subcommand show what files have been affected since the image was instantiated as a container.

* A _RESTful API_ uses standard HTTP request types such as GET, POST, DELETE, and others to represent resources and operations on them. In case of Docker, images, containers, volumes, and the like are the represented resources.

* The default Docker configuration, where access is restricted via the `/var/run/docker.sock` domain socket. Processes external to the host can't gain access to Docker.

* To stop the docker daemon

```shell
$ sudo service docker stop

# or
$ sudo systemctl stop docker

$ ps -ef | grep -E 'docker(d| -d| daemon)\b' | grep -v grep

$ sudo docker daemon -H tcp://0.0.0.0:2375

# connect from outside
$ docker -H tcp://<host-ip>:2357 <sub-command>

$ docker run -p 2375:2375 -v /var/run/docker.sock:/var/run/docker.sock sequenceid/socat
```

* `socat - Multipurpose relay (SOcket CAT)` socat is a command line based utility that estblishes two bidirectional byte streams and transfers data between them.

* Use `-d` (detached flag) to run a Docker container in the background.

* `docker run --restart <restart-policy>`

| Policy | Description |
|--------|-------------|
|  `no`  | Don't restart when the container exits |
| `always` | Always restart when the container exits |
| `unless-stopped` | Always restart, but remember explicitly stopping |
| `on-failure[:max-retry]` | Restart only on failure |

* Change the folder where Docker stores its data.

```shell
$ dockerd -g /home/dockeruser/mydocker
```

* The Docker server is a standard application server written in **Go** that returns an HTTP response.

```shell
$ socat -v UNIX-LISTEN:/tmp/dockerapi.sock,fork UNIX-CONNECT:/var/run/docker.sock &
$ docker -H unix:///tmp/dockerapi.sock ps -a
```

* **Cross-Origin-Resource Sharing (CORS)** is a mechanism that carefully bypasses the usual restriction of JavaScript that limits you to only accessing the current domain. In this case, CORS allows the daemon to listen on a different port from where you serve your Docker terminal page.

* Use Docker’s `-p` flag to map a container’s port to your host machine. host_port:container_port

* To obtain images from external locations, you can use the `docker pull` command. By default, images will be downloaded from the Docker Hub.

* Docker allow user-defined networks to enable containers to communicate with each other.

```shell
$ docker network create my_network
```

* All containers are connected to the Docker bridge network by default.

* A Docker registry allows multiple users to push and pull images from a central store
using a RESTful API.

* Use the `docker search` command to find the image to pull, and then run it.




















www.alpinelinux.org

bootstrap single page template
https://github.com/StartBootstrap/startbootstrap-grayscale.git

https://www.youtube.com/watch?v=p28piYY_wv8