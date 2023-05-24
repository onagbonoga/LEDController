LED Controller Project
==============================================

This project allows the control of an RGB led's colors using a web application

What's Here
-----------

* README.md - this file
* buildspec.yml - this file is used by AWS CodeBuild to package your
  application for deployment to AWS Lambda
* requirements.txt - this file is used install Python dependencies needed by
  the Flask application
* setup.py - this file is used by Python's setuptools library to describe how
  your application will be packaged and installed
* LEDController/ - this directory contains the Python source code for your Flask application
* tests/ - this directory contains unit tests for your application
* .ebextensions/ - this directory contains the configuration files that allow
  AWS Elastic Beanstalk to deploy your application
* template.yml - this file contains the description of AWS resources used by AWS
  CloudFormation to deploy your infrastructure
* template-configuration.json - this file contains the project ARN with placeholders used for tagging resources with the project ID

Getting Started
---------------

These directions assume you want to develop on  your development environment or a Cloud9 environment, and not
from the Amazon EC2 instance itself. If you're on the Amazon EC2 instance, the
virtual environment is already set up for you, and you can start working on the
code.

To work on the sample code, you'll need to clone your project's repository to your
local computer. You can find instructions in the AWS CodeStar user guide at https://docs.aws.amazon.com/codestar/latest/userguide/getting-started.html#clone-repo.

1. Create a Python virtual environment for your Flask project. This virtual
   environment allows you to isolate this project and install any packages you
   need without affecting the system Python installation. At the terminal, type
   the following command:

        $ python3 -m venv ./venv

2. Activate the virtual environment:

        $ source ./venv/bin/activate

3. Install Python dependencies for this project:

        $ pip install -r requirements.txt

4. Install the sample application code into your virtual environment:

        $ python setup.py install

5. Start the Flask development server:

        $ python LEDController/app.py --port 8000

6. Open http://127.0.0.1:8000/ in a web browser to view the output of your
   service.
