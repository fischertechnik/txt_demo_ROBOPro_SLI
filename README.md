# Extended /C++ programming for the TXT
## Introduction
There are 2 possibilities
- TXT Shared Library Interface (SLI) for ROBOPro
A SLI extends the basic set of RoboPro elements with new one's.  
It enable the user to add functionality to RoboPro.
- TXT local programs
A local program replaces a local RoboPro program.


A developerwill find a description about setting up a development environment on MS-Windows.  
How to use this environment to ceate, document and use your custom SLI's or executable.  
An End-User will find here some usable examples.

## The organisation
- The map FtTxtExamples is aiming on the end user.  
The map contains usable examples.
- The map FtTxtWorkspace is aiming on the developer
The maps contains Eclipse example projects and the supporting TXT libraries.
- In the root you will find a description of "How to ... ? and overviews"

The shared library input/output element allows to call functions and return/supply a value from/to shared library modules installed on the TXT controller. Such libraries are typically written in the C or C++ programming language. This allows interfacing ROBOPro with C / C++ programs, which is useful for accessing advanced sensors or for compute intensive tasks like image processing.

## Documentaion
- this Document
- [What is an SLI](SLI.md).
- [The program develpment environment](tools.md).
- [Notes](Notes.md).
- [Introduction and overview SLI project for Eclipse]( FtTxtWorkspace/README.md).
- [Introduction and overview SLI applications for the end user](FtTxtExamples/README.md).

# document history
- 2020-05-16 v 466.1.1 new
