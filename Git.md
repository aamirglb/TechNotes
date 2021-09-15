# Git

Git first time setup.

```bash
# default behaviour
$ git config --local user.email "you@example.com"
$ git config --local user.name "Your Name"

$ git config --global user.email "you@example.com"
$ git config --global user.name "Your Name"
```

### Discard all local changes
```shell
# revert changes made to working copy
$ git checkout .

# remove untrack files
$ git clean -f

# remove untrack directories
$ git clean -fd
```

### Rename master to main 
```shell
$ git branch -m master main
```

### git stash

git stash temporarily shelves (or stashes) changes you've made to your working copy so you can work on something else, and then come back and re-apply them later on.

The git stash command takes your uncommitted changes (both staged and unstaged), saves them away for later use, and then reverts them from your working copy

```shell
$ git stash  # stash all changes
$ git stash pop  # removes the changes from stash and reapplies them to your working copy
$ git stash apply # reapply the changes to working copy and keep them in stash (useful for applying same changes to multiple branches)
$ git stash -u # stash untracked files also
# git stash -a # stash ignored files also

$ git stash list # view all stashes
$ git stash save "message"  # annotate git stash
$ git stash pop stash@{2}   # select stash to re-apply
$ git stash show  # show summary of stash
$ git stash show -p # view full difference of stash

$ git stash -p (--patch)  # partial stash
```

If the changes on your branch diverge from the changes in your stash, you may run into conflicts when popping or applying your stash. Instead, you can use `git stash branch` to create a new branch to apply your stashed changes to.

```shell
$ git stash branch add-stylesheet stash@{1}
$ git stash drop stash@{1}  # delete a stash
$ git stash clear  # delete all stash

$ git log --oneline --graph stash@{0}
```

### Git Tags
Tags are reference points in the repository. Tags are usually used as references for release versions.
Tags are Git objects meaning that **they can be checkout out** like a branch or a commit.
Git has the ability to tag specific points in a repository’s history as being important.

Git supports two types of tags: **lightweight** and **annotated**.
A *lightweight tag* is very much like a branch that doesn’t change; iit’s just a pointer to a specific commit.

*Annotated tags*, however, are stored as full objects in the Git database. They’re checksummed; contain the tagger name, email, and date; have a tagging message; and can be signed and verified with GNU Privacy Guard (GPG). It’s generally recommended that you create annotated tags so you can have all this information.

```bash
# list tags
$ git tag

# search for tags that match a particular pattern. 
$ git tag -l "v1.8.5*"

# create an annotated tag
$ git tag -a v1.0.0 -m "GCS SW v1.0.0"

# push only one tag to remote
$ git push <repo-name> <tag-name>
$ git push origin v1.0.1

# push all tags to remote
$ git push --tags <repo-name>

# fetch latest tags from remote repository
# git fetch --all --tags

$ git checkout tags/<tag> -b <branch>

# inspect the state of branch
$ git log --oneline --graph
```

### Git delete branch
Git will not let you delete the branch you are currently on so you must make sure to checkout a branch that you are NOT deleting. 
```bash
// delete branch locally
git branch -d localBranchName

// delete branch remotely
git push origin --delete remoteBranchName
```

The `-d` option will delete the branch only if it has already been pushed and merged with the remote branch. Use `-D` instead if you want to force the branch to be deleted, even if it hasn't been pushed or merged yet.

```bash
# 
git fetch -p
```

The `-p` flag means "prune". After fetching, branches which no longer exist on the remote will be deleted.

### Git Large File Storage (LFS) Extension
How to use git LFS to store large files (>100 MB).

```bash
sudo apt-get install git-lfs
cd ~/gcs_sw_binary/
git lfs install --local
git lfs track "*.AppImage"
git add .gitattributes
git add QGroundControl.AppImage
git commit -m "GCS SW version v1.0.0"
git push origin main

```

* `Gitolite` tool allows you to setup git hosting on a central server, with fine-grained access control and many more powerful features.

```bash
$ git init --bare new_repo.git

# git status short (-s, --short)
$ git status -s

# -a, --all: take all changes to the tracked files
$ git commit -a -m "message"

$ git config --global user.name "Aamir"
$ git config --global user.email "aamir@aamir.com"

# show log
$ git log

$ git diff

# always use rename and copy detection
$ git config --global diff.renames copies

$ git mv random.c src/random.c

# bring in changes from remote repo
$ git pull

$ git show

$ git tag -a -m "random v0.1" v0.1
$ git tag --list
$ git log -1 --decorate --abbrev-commit
$ git push origin tag v0.1

$ git mergetool

# git diff statistics
$ git diff --stat

# undo changes to a file
$ git checkout -- rand.c

# create a branch and switch to it
$ git checkout -b better-random

# same as above
$ git branch better-random
$ git checkout better-random

$ git push --set-upstream origin better-random

# show changes exclusive to better-random branch
$ git log HEAD..origin/better-random

# undo an unpublished merge
$ git reset --hard @{1} 
# or go to previous (pre-merge) commit
```

## Git Submodules

* Git _submodules_ allow you to keep a Git repository as a subdirectory of another Git repository. This lets you clone another repository into your project and keep your commits separate.

* To add a new submodule you use the git submodule add command with the absolute or relative URL of the project you would like to start tracking.

```shell
$ git submodule add https://github.com/chaconinc/DbConnector
```
* `.gitmodules` configuration file stores the mapping between the project’s URL and the local subdirectory you’ve pulled it into:

```
[submodule "DbConnector"]
	path = DbConnector
	url = https://github.com/chaconinc/DbConnector
```

### Cloning a Project with Submodules

* When a project with submodules is cloned, by default you get the directories that contain submodules, but none of the files within them yet:

```shell
$ git clone https://github.com/chaconinc/MainProject

# initialize local configuration file
$ git submodule init

# fetch all the data from that project and check out the appropriate commit listed in your superproject
$ git submodule update
```

* A simpler way to clone project with submodules is to use `--recurse-submodules`. automatically initialize and update each submodule in the repository, including nested submodules.

```
$ git clone --recurse-submodules https://github.com/chaconinc/MainProject
```

* `~/.gitconfig` file contains information that will be used to identify commits in log. Either create `.gitconfig` file or use `git config` command from command line. 

* `.git` directory contains entire repository in Git internal format, and some repository-specific administrative information. `getrepository-layout (5)` manpage.

* A Git version identifier is a SHA-1 hash. 

* To setup a branch as private, needs to configure the server with hooks.

* **Directed Acyclic Graph (DAG)** of revisions. The structure that Git uses to represent the possible non-linear history of a project is called a Directed Acyclic graph (DAG).

* A directed graph is a data structure from computer science (and mathematics)
composed of nodes (vertices) that are connected with directed edges (arrows). A
directed graph is acyclic if it doesn't contain any cycles.

* The DAG of revisions uses following representation:
    1. **Nodes**: Each node represenet one revision of a project. These objects are called **commits**.
    2. **Directed Edges**: Each edge is based on relationship between two revisions. The arrow goes from a later **child** revision to an earlier **parent** revision.

* DAG of revisions is laid out _left-to-right_ (root nodes on the left, leaves on the right) or _bottom-to-top_ (the most recent revisions on top).

* There are two special type of nodes in any DAG:
    1. **Root node**: Nodes (revisions) that have no parents.. There is at least one root node in DAG of revisions, which represents initial version of project.
    2. **Leaf node**: Nodes that have no children (no incoming edges). there is at least one such node. Usually, each leaf in DAG of revisions has a branch head pointing to it.

* Both branches and tags, sometimes called references (refs) together, have the
same meaning (the same representation) within the DAG of revisions.

* A **tag** is a symbolic name (for example, v1.3-rc3 ) for a given revision. It always points to the same object; it does not change.

* A **branch** is a symbolic name for the line of development. The most recent commit
(leaf revision) on such a line of development is referred to as the top or tip of the
branch, or branch head, or just a branch.

* Git stored _branches_ and _tags_ in files inside .git administrative area, in the `.git/refs/heads/` and `.git/refs/tags/` directories, respectively.
