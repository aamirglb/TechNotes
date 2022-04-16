# Docker

* **Docker** is a platform for running applications in an _isolated environment_ called a **_"container"_** (or Docker container).

* **Podman** and **Containerd** are other alternatives to Docker.

* [Play With Docker PWD](https://labs.play-with-docker.com)

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

# Docker In Action

* _Docker_ is an open source project for building, shipping and running programs.

* _Containers_ is an operating system technology.
* _Docker_ is an open source project for building, shipping and running programs.

* _Containers_ is an operating system technology.

* Running state of a container is directly tied to the state of a single running program inside the container.

* Containers are an operating system feature.

* Docker uses Linux `namespaces` and `cgroups`, which have been part of Linux since 2007. Docker doesn’t provide
the container technology, but it specifically makes it simpler to use.

* Docker builds containers using 10 major system features.

    1. _PID namespace_ - Process identifiers and capabilities
    1. _UTS namespace_ - Host and domain name
    1. _MNT namespace_ - Filesystem access and structure
    1. _IPC namespace_ - Process communication over shared memory
    1. _NET namespace_ - Network access and structure
    1. _USR namespace_ - User names and identifiers
    1. _chroot syscall_ - Controls the location of the filesystem root
    1. _cgroups_ - Resource protection
    1. _CAP drop_ - Operating system feature restrictions
    1. _Security modules_ - Mandatory access controls

* _Docker image_ is a bundled snapshot of all the files that should be available to a program running inside a container.

* On macOS and Windows, Docker uses a single, small virtual machine to run all the containers.

* Every time you run docker run and create a new container, that new container will get a 1024-bit unique identifier.

```shell
docker run --interactive --tty \
    --link web:web \
    --name web_test \
    busybox:1.29 /bin/sh
```

* To detach an interactive terminal, hold down the Ctrl (or Control) key and press P and then Q. This will work only when you’ve used the `--tty` option.

* The docker logs command has a flag, `--follow` or `-f` , that will display the logs and then continue watching and updating the display with changes to the log as they occur.

* The `docker stop` command tells the program with PID 1 in the container to halt.

* A _PID namespace_ is a set of unique numbers that identify
processes. Linux provides tools to create multiple PID namespaces. Each namespace has a complete set of possible PIDs. This means that each PID namespace will contain
its own PID 1, 2, 3, and so on.

* Docker creates a new PID namespace for each container by default. A container’s PID namespace isolates processes in
that container from processes in other containers.

```shell
$ docker exec <container-name> <command>
# execute ps command inside container nsA
$ docker exec nsA ps
```

* you can optionally create containers without their own PID namespace by setting the `--pid` flag on `docker create` or `docker run` and setting the value to `host`.

```shell
$ docker run --pid host busybox:1.29 ps 1
```

* _metaconflicts_: conflicts between containers in the Docker layer.

* By default, Docker assigns a unique (human-friendly) name to each container it creates. The `--name` flag overrides that process with a known value.

```shell
$ docker rename webid webid-old
```

* The `docker create` command is similar to `docker run`, the primary difference being that the container is created in a
stopped state.

```shell
$ CID=$(docker create nginx:latest)
$ echo $CID
```

* Both the `docker run` and `docker create` commands provide another flag to write the ID of a new container to a known file:

```shell
$ docker create --cidfile /tmp/web.cid nginx
$ cat /tmp/web.cid
```

* Docker won’t create a new container by using the provided CID file if that file already exists.

* get the truncated ID of the last created container

```shell
$ docker ps --latestt --quiet
$ docker ps -l -q

# get complete id
$ docker ps -l -q --no-trunc
```

* The link mechanism injects IP addresses into dependent containers, and containers that aren’t running don’t have
IP addresses.

* Links create a unidirectional network connection from one container to other containers on the same host.

* __WordPress__ is a popular open source content-management and blogging program. WordPress uses a database program called MySQL to store most of its data.

* The `docker inspect` command will display all the metadata (a JSON document) that Docker maintains for a container.

* Setup a WordPress website using Docker

```shell
# MySQL container
$ docker run -d --name wpdb \
    -e MYSQL_ROOT_PASSWORD=ch2demo \
    mysql:5.7v

# WordPress website
docker run -d --name wp3 \
    --link wpdb:mysql \
    -p 8000:80 \
    --read-only \
    -v /run/apache2/ \
    --tmpfs /tmp \
    wordpress:5.0.0-php7.2-apache
```

* Navigate to `http://localhost:8000` to visit the website.

* Environment variable injection

```shell
$ docker run --env MY_ENV_VVAR="test variable" busybox:1.29 env
```

* The `--env` flag, or `-e` for short, can be used to inject any environment variable.

* An _init system_ is a program that’s used to launch and maintain the state of other programs. Any process with __PID 1__ is treated like an init process by the Linux kernel (even
if it is not technically an init system).

* Several init systems could be used inside a container. The most popular include `runit`, `Yelp/dumb-init`, `tini`, `supervisord`, and `tianon/gosu`.

* To see which processes are running inside the container, use the `docker top` command.

* The `top` subcommand will show the _host PID_ for each of the processes in the container.

* Docker containers run something called an _entrypoint_ before executing the command. Entrypoints are perfect places to put code that validates the preconditions of a container.

* To remove a container from your computer, use the `docker rm` command.

* You can stop the container with `docker stop` command or by using the `-f` flag on `docker rm`. The key difference is that when you stop a process by using the `-f` flag, Docker sends a `SIG_KILL` signal, which immediately terminates the receiving process. In contrast, using `docker stop` will send a `SIG_HUP` signal. Recipients of `SIG_HUP` have time to perform finalization and cleanup tasks. The `SIG_KILL` signal makes for no such allowances and can result in file corruption or poor network experiences.

* A _named repository_ is a named bucket of images. A
repository’s name is made up of the name of the host where the image is located, the user account that owns the image, and a short name.

          User/organization
docker.io/dockerinaction/ch3_hello_registry
^^^^^^^^^                ^^^^^^^^^^^^^^^^^^
Registry host            short name

* Just as there can be several versions of software, a repository can hold several images. Each image in a repository is identified uniquely with _tags_.

* `freegeoip` is a web application that can be used to get the rough geographical location associated with a network address.

* _Docker Hub_ is a registry and index with a web user interface run by Docker Inc.







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

* A Docker registry allows multiple users to push and pull images from a central store using a RESTful API.

* Use the `docker search` command to find the image to pull, and then run it.

* The growing popularity of both the Kubernetes’ pod and docker-compose concepts has made the _host-like container_ relatively redundant - separate containers can be conjoined into a single entity at a higher level, rather than manag-
ing multiple processes using a traditional init service.

* Each Dockerfile command creates a single new layer on top of the previous one, but using `&&` in your `RUN` statements effectively ensures that several commands get run as one command. This is useful because it can keep your images small.

* Use [Supervisor](http://supervisord.org/) to manage the processes in your container.

* Committing a container only stores the state of the filesystem at the
time of the commit, not the processes.

* Remove containers

```shell
# All containers (both stopped and running)
$ docker ps -a -q | xargs --no-run-if-empty docker rm -f

# Remove stopped containers
$ docker ps -a -q --filter status=exited | xargs --no-run-if-empty docker rm

# same as above command
$ docker container prune
```


















www.alpinelinux.org

bootstrap single page template
https://github.com/StartBootstrap/startbootstrap-grayscale.git

https://www.youtube.com/watch?v=p28piYY_wv8
