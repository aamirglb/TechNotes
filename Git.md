# Git

Git first time setup.

```bash
# default behaviour
$ git config --local user.email "you@example.com"
$ git config --local user.name "Your Name"

$ git config --global user.email "you@example.com"
$ git config --global user.name "Your Name"
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
