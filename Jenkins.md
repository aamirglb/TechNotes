# Jenkins Notes

In 2016 and 2017, **CloudBees**, the enterprise company that is the majority contributor to the Jenkins project, introduced an enhanced programming syntax for pipelines-as-
code called **Declarative Pipelines**. This syntax adds a clear, expected structure to pipe‐
lines as well as enhanced **DSL (Domain Specific Language)** elements and constructs. The result more closely resembles the workflow of constructing a pipeline in the web interface (with Freestyle
projects).

```Groovy
pipeline {
    agent any
    stages {
        stae('Source')
        git branch:
        stash name:
    }
    stage('Build')
    {
        'test', url: 'git@diyvb:repos/gradle-greetings'
        'test-sources', includes: 'build.gradle,/src/test'
        {
        }
    }
}
```

*Blue Ocean*, the new Jenkins visual interface. Blue Ocean adds a graphical representation for each stage of a pipeline showing indicators of success/failure and progress, and allowing point-and-click access to logs for each individual piece.

pipelines can either be written in a ***“scripted”*** syntax style or a ***“declarative”*** syntax style.

Jenkins can automatically set up an organization ***webhook*** (a notification from the website) on the hosting side that will notify your Jenkins instance when any changes are made in the repository. When Jenkins is notified, it detects the Jenkinsfile as a marker in the repository and executes the commands in the Jenkinsfile to run the pipeline.

In <span style="color:lime">**Scripted Pipeline**</span>, we don’t have a built-in way to do such post-build actions. We are limited to the DSL steps plus whatever can be done with Groovy coding.

```Groovy
node {
    try {
        // do some work
    }
    catch(e) {
        currentBuild.result = "FAILED"
        throw e
    }
    finally {
        mail to:"buildAdmin@mycompany.com",
        subject:"STATUS FOR PROJECT: ${currentBuild.fullDisplayName}",
        body: "RESULT: ${currentBuild.result}"
    }
}
```
### **Declarative Pipeline structure**
<span style="color:lime">**Declarative Pipeline**</span>
```Groovy
pipeline {
    agent any
    stages {
        stage ("dowork") {
            steps {
                // do some work
            }
        }
    }
    post {
        always {
            mail to:"buildAdmin@mycompany.com",
            subject:"STATUS FOR PROJECT: ${currentBuild.fullDisplayName}",
            body: "RESULT: ${currentBuild.result}"
        }
    }
}
```
Artifactory, a binary artifact manager.

Jenkins 2 supports pipelines-as-code

Two different styles to write pipelines in Jenkins 2 
 1. Scripted syntax, and
 2. Declarative syntax.

*Scripted syntax* refers to the initial way that pipelines-as-code have been done in Jen‐
kins. It is an imperative style, meaning it is based on defining the logic and the pro‐
gram flow in the pipeline script itself. It is also more dependent on the Groovy
language and Groovy constructs—especially for things like error checking and deal‐
ing with exceptions.

*Declarative syntax* is a newer option in Jenkins. Pipelines coded in the declarative
style are arranged in clear sections that describe (or “declare”) the states and out‐
comes we want in the major areas of the pipeline, rather than focusing on the logic to
accomplish it.