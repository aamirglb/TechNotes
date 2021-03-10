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

```bash
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
