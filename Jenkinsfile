pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh 'echo "Hello World" >> /tmp/pipeline'
                sh '''
                    echo "Multiline shell steps works too" >> /tmp/pipeline
                    ls 
                '''
            }
        }
    }
}

pipeline {
    agent any
    stages {
        stage('Deploy') {
            steps {
                timeout(time: 3, unit: 'MINUTES') {
                    retry(5) {
                        sh echo Pipeline in Deploy >> /tmp/pipeline
                    }
                }
            }
        }
    }
}

pipeline {
    agent any
    stages {
        stage('Test') {
            steps {
                sh 'echo "Fail!"; exit 1'
            }
        }
    }
    post {
        always {
            echo 'This will always run' >> /tmp/pipeline
        }
        success {
            echo 'This will run only if successful'  >> /tmp/pipeline

        }
        failure {
            echo 'This will run only if failed' >> /tmp/pipeline

        }
        unstable {
            echo 'This will run only if the run was marked as unstable' >> /tmp/pipeline

        }
        changed {
            echo 'This will run only if the state of the Pipeline has changed' >> /tmp/pipeline

            echo 'For example, if the Pipeline was previously failing but is now successful' >> /tmp/pipeline

        }
    }
}
