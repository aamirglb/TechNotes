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

# Pro Git Notes

* Distributed version control systems such as **Git** give each developer his or her own copy of the project's history, a _clone_ of a repository.

* Git is very fast: nearly all operations are performed locally, and are flexible

* Version control is a system
that records changes to a file or set of files over time so that you can recall spe-
cific versions later.

* One of the more popular VCS tools was a system called **RCS**, which is still
distributed with many computers today. RCS
works by keeping patch sets (that is, the differences between files) in a special
format on disk; it can then re-create what any file looked like at any point in
time by adding up all the patches.

* Centralized Version Control Systems (CVCSs) such as _CVS_, _Subversion_, and _Perforce_, have a single server that contains all the versioned files, and a number of clients that check out files from that central place.

* Distributed Version Control Systems (DVCSs) such as _Git_, _Mercurial_, _Bazaar_ or _Darcs_, clients don’t just check out the latest snapshot of the files: they fully mirror the repository. Every clone is really a full backup
of all the data.

* The major difference between Git and any other VCS  is the way Git thinks about its data.
Most other systems store information as a **list of file-based changes**. These systems think of the information they keep as a set of
files and the changes made to each file over time.

* Git doesn’t think of or store its data this way. Instead, Git thinks of its data
more like a set of snapshots of a miniature filesystem. Every time you commit,
or save the state of your project in Git, it basically takes a picture of what all
your files look like at that moment and stores a reference to that snapshot. To
be efficient, if files have not changed, Git doesn’t store the file again, just a link
to the previous identical file it has already stored. Git thinks about its data more
like a stream of snapshots.

* Everything in Git is check-summed before it is stored and is then referred to by
that checksum. The mechanism that Git uses for this checksumming is called a **SHA-1** hash.
This is a 40-character string composed of hexadecimal characters and calculated based on the contents of a file or directory structure in Git.

* Git stores everything in its database not by file name but by
the hash value of its contents.

* Git has three main states that your files can reside in: **committed**, **modified**, and **staged**. This leads us to the three main sections of a Git project: the _Git directory_, the _working directory_, and the _staging area_.

* The **Git directory** is where Git stores the metadata and object database for your project. This is the most important part of Git, and it is what is copied when you clone a repository from another computer.

* The **working directory** is a _single checkout_ of one version of the project. These files are pulled out of the compressed database in the Git directory and placed on disk for you to use or modify.

* The **staging area** is a file, generally contained in your Git directory, that stores information about what will go into your next commit. It’s sometimes referred to as the **“index”**, but it’s also common to refer to it as the _staging area_.

* Git comes with a tool called `git config` that lets you get and set configuration variables that control all aspects of how Git looks and operates.

* `/etc/gitconfig`: system wide settings `git config --system` to read and write these settings.

* `~/.gitconfig` or `~/.config/git/config` : User specific `git config --global`

* `.git/config`: Specific to repository

```shell
$ git config --system --list (or -l)
$ git config --global --list
```

* user name and email address is immutably baked into the commits you start creating.

```shell
$ git config --global core.editor emacs
$ git config --global core.editor "'C:/Program Files/Notepad++/notepad++.exe' -multiInst -no...'"

# List configuration
$ git config --list 

# get specific key
$ git config user.name
$ git config user.email
```

* `git init` creates a new subdirectory named `.git` that contains all of your necessary repository files - a Git repository skeleton.

* `git add` specify the files you want to track, followed by a `git commit`

* `git clone [url]` receives a full copy of nearly all data that the server has.

* `git clone [url] [local_directory]` use a different directory name.

* Git has a number of different transfer protocols like `https://` protocol, and also `git://` or `user@server:path/to/repo.git`, which uses the SSH transfer protocol.

* _Tracked files_ are files that were in the last snapshot; they can be _unmodified_, _modified_, or _staged_. Untracked files are every-
thing else - any files in your working directory that were not in your last snapshot and are not in your staging area.

* `git status` determine which files are in which state

```shell
# more compact/simplyfied output
$ git status -s
$ git status --short
 M README
MM Rakefile
 A lib/git.rb
 M lib/simplegit.rb
?? LICENSE.txt
```

  ^ status of staging area
  |^ status of working tree
  ||
* ?? untracked file 
   A new files that have been added to the staging area 
   M modified files 

* There are two columns to the output - the left-hand column indicates the status of the staging area and the right-hand column indicates the status of the working tree. 

* `.gitignore` class of files that you don’t want Git to automatically add or even show you as being untracked.

```shell
$ cat .gitignore
*.[oa]  # files ending in ".o" or ".a"
*~      # ignore all files whose names end with a tilde
```

* Rules for patterns in the .gitignore file are as follows:
    * Blank lines or lines starting with # are ignored.
    * Standard glob patterns work.
    * You can start patterns with a forward slash ( / ) to avoid recursivity.
    * You can end patterns with a forward slash ( / ) to specify a directory.
    * You can negate a pattern by starting it with an exclamation point ( ! ).
    * two asterisks to match nested directories; a/**/z would match a/z, a/b/z, a/b/c/z, and so on.

* `.gitignore` file examples for dozens of projects and languages at [](https://github.com/github/gitignore)

* `git diff` shows you the exact lines added and removed

```shell
# compares what is in your working directory with what is in your staging area
$ git diff

# what you’ve staged that will go into your next commit
$ git diff --staged (or --cached)
```

* `git commit -v` puts the diff of your change in the editor so you can see exactly what changes you’re committing

* `git commit -m "message"` - commit message inline

* `git commit -a` command makes Git automatically stage every file that is already tracked before doing the commit, letting you skip
the `git add` part

```shell
$ git commit -a -m "new commit"
```

* `git rm --cached README` keep the file in your working tree but remove it from your staging area.

* Git doesn’t explicitly track file movement. If
you rename a file in Git, no metadata is stored in Git that tells it you renamed
the file.

* `git mv file_from file_to` rename a file

* `git log` look back to see what has happend in the repository

* `git log -p` show the difference introduced in each commit

* `git log -p -2` limit the output to the last two entries

* `git log --stat` show stats

* `git log --pretty=oneline`

* `git log --pretty=format:"%h - %an, %ar : %s"`

Useful options for git log --pretty=format

| Option | Description of Output |
|--------|-----------------------|
| %H | Commit hash |
| %h | Abbreviated commit hash |
| %T | Tree hash |
| %t | Abbreviated tree hash |
| %P | Parent hashes |
| %p | Abbreviated parent hashes |
| %an|  Author name |
| %ae|  Author email |
| %ad|  Author date (format respects the --date=option) |
| %ar|  Author date, relative |
| %cn|  Committer name |
| %ce|  Committer email |
| %cd|  Committer date |
| %cr|  Committer date, relative |
| %s | Subject |
[Table caption, works as a reference][Caption]

* `git log --pretty=format:"%h %s" --graph` adds a nice little ASCII graph

Common options to git log

| Option | Description |
|--------|-------------|
| -p     | Show the patch introduced with each commit. |
| --stat | Show statistics for files modified in each commit. |
| --shortstat | Display only the changed/insertions/deletions line from the --stat command. |
| --name-only | Show the list of files modified after the commit information. |
| --name-status | Show the list of files affected with added/modified/deleted information as well. |
| --abbrev-commit | Show only the first few characters of the SHA-1 checksum instead of all 40. |
| --relative-date | Display the date in a relative format (for example, “2 weeks ago”) instead of using the full date format. |
| --graph | Display an ASCII graph of the branch and merge history beside the log output. |
| --pretty | Show commits in an alternate format. Options include `oneline`, `short`, `full`, `fuller`, and `format` (where you specify your own format) |

* `git log --since=2.weeks` list of commits made in last 2 weeks

* `git log -Sfunction_name` takes a string and only shows the commits that introduced a change to the code that added or removed that string

* The last really useful option to pass to `git log` as a filter is a _path_. If you specify a directory or file name, you can limit the log output to commits that introduced a change to those files. This is always the last option and is generally preceded by double dashes ( -- ) to separate the paths from the options.

Options to limit the output of git log

| Option | Description |
|--------|-------------|
| -(n) | Show only the last n commits |
| --since, --after | Limit the commits to those made after the speci- fied date. |
| --until, --before | Limit the commits to those made before the specified date. |
| --author | Only show commits in which the author entry matches the specified string. |
| --committer | Only show commits in which the committer entry matches the specified string. |
| --grep | Only show commits with a commit message containing the string |
| -S | Only show commits adding or removing code matching the string |

* `git commit --amend` override previous commit

```shell
$ git commit -m 'initial commit'
$ git add forgotten_file
$ git commit --amend  # second commit replaces the results of the first.
```

* `git restore --staged Git.md` to unstage Git.md

* `git checkout -- CONTRIBUTING.md` discard the changes made to the file

* Anything that is committed in Git can almost always be recovered. Even commits that were on branches that were deleted or commits that
were overwritten with an `--amend` commit can be recovered. However, anything you lose that was never committed is likely never to be seen again.

* **Remote repositories** are versions of your project that are hosted on the Internet or network somewhere.

* `git remote` lists the shortnames of each remote handle you’ve specified. **origin** is the default name Git gives to the server you cloned from.

* `git remote -v` shows the URLs that Git has stored for the shortname to be used when reading and writing to that remote.

* `git remote add <shortname> <url>` add a new remote explicitly. To add a new remote Git repository as a shortname you can reference
easily.

* `git remote add pb https://github.com/paulboone/ticgit`
Now you can use the string `s` on the command line in lieu of the whole URL

* `git fetch [remote-name]` pulls down all the data from that remote project that you don’t have yet.

* `git fetch` doesn’t automatically merge it with any of your work or modify what you’re currently working on.

* `git pull` command automatically fetch and then merge that remote branch into your current branch.

* `git push origin master` push your master branch to your origin server

* `git remote show [remote-name]` see more information about a particular remote

* `git remote rename pb paul` change a remote’s shortname.

* `git remote rm paul` remove a remote

* **Tagging**: Git has the ability to tag specific points in history as being important.

* `git tag` list available tags

* `git tag -l "v1.8.5*"` search with a particular pattern

* Git uses two main types of tags: **lightweight** and **annotated**.

* A _lightweight tag_ is very much like a branch that doesn’t change – it’s just a pointer to a specific commit. Lightweight tag is basically the commit checksum stored in a file - no other information is kept.

* _Annotated tags_, however, are stored as full objects in the Git database. They’re checksummed; contain the tagger name, email, and date; have a tagging message; and can be signed and verified with GNU Privacy Guard (GPG).

* `git tag -a v1.4 -m "my version 1.4"` create annotated tag with a tagging message

* `git tag -a v1.2 9fceb02` tag commits using SHA checksum after moving past the commits

* By default, the `git push` command doesn’t transfer tags to remote servers. You will have to explicitly push tags to a shared server after you have created them. This process is just like sharing remote branches – you can run `git push origin [tagname]`.

* `git push origin --tags` push all tags to remote

* `git checkout v1.4` will checkout the v1.4 tag. This puts the repo in a **detached HEAD** state. This means any changes made will not update the tag. Therefore it is a best practice to create a new branch anytime you're making changes in a detached HEAD state.

* `git checkout -b version2 v2.0.0` create a branch from tag

* If you don’t want to type the entire text of each of the Git commands, you can easily set up an alias for each command using git config. 

```shell
$ git config --global alias.co checkout
$ git config --global alias.br branch
$ git config --global alias.ci commit
$ git config --global alias.st status
```

* Branching means you diverge from the main line of development and continue to do work without messing with that main line.

* Git doesn’t store data as a series of changesets or differences, but instead as a series of **snapshots**.

* A branch in Git is simply a lightweight movable pointer to one of these commits.

* `git branch testing` created a new branch, it didn’t switch to that branch.

* `git log --oneline --decorate` shows where the branch pointers are pointing.

* `git checkout testing` switch to an existing branch.

* A branch in Git is in actuality a simple file that contains the 40 character SHA-1 checksum of the commit it points to, branches are cheap to create and destroy.

* `git checkout -b iss53`

* When you try to merge one commit with a commit that can be reached by following the first commit's history, Git simplifies things by moving the pointer forward because there is no divergent work to merge together – this is called a "fast-forward."

* `git branch -d hotfix` delete a branch

* Git adds standard conflict-resolution markers to the files that have conflicts, so you can open them manually and resolve those conflicts.

* After you’ve resolved each of
these sections in each conflicted file, run git add on each file to mark it as re-
solved. Staging the file marks it as resolved in Git.

* `git branch` get listing of current branches

* `git branch -v` see the last commit on each branch

* `git branch --merged` see which branches are already merged into the branch you’re on

* `git branch --no-merged` see all the branches that contain work you haven’t yet merged in

* `git ls-remote [remote]` or `git remote show [remote]` get a full list of remote references explicitly

* `git clone -o booyah` booyah instead of origin

* If you don’t want to type your password every single time you push, you can set up a **"credential cache"**. The simplest is just to keep it in memory for a few minutes, which you can easily set up by running `git config --global credential.helper cache`.

```shell
$ git fetch origin

# directly merge the remote/serverfix branch into current branch
$ git merge origin/serverfix

# create a branch to track remote/serverfix branch
$ git branch -b serverfix origin/serverfix

# shortcut for the above command
$ git checkout --track origin/serverfix

# set up a local branch with a different name than the remote branch
$ git checkout -b sf origin/serverfix
```

* Checking out a local branch from a remote-tracking branch automatically creates what is called a **"tracking branch"** (and the branch it tracks is called an **"upstream branch"**).

* When you have a tracking branch set up, you can reference its upstream branch with the `@{upstream}` or `@{u}` shorthand.

* `git merge @{u}` instead of `git merge origin/master`

* `git branch -vv` list out your local branches with more information including what each branch is tracking and if your local branch is
ahead, behind or both.

* `git pull` is essentially a `git fetch` immediately followed by a `git merge` in most cases.

* `git push origin --delete serverfix` delete remote branch

* In Git, there are two main ways to _integrate changes from one branch into another_: the **merge** and the **rebase**.