# Extended C/C++ programming for the TXT
## Introduction
There are 2 possibilities to use C/C++ programs localy on the TXT.
- As TXT Shared Library Interface (SLI) for ROBOPro
A SLI extends the basic set of RoboPro elements with new one's.  
It enable the user to add functionality to RoboPro.
- As TXT local programs
A local program replaces a local RoboPro program.


A developer will find here a description about setting up a development environment on MS-Windows.  
How to use this environment to ceate, document and use your custom SLI's or executable.  
An End-User will find here some usable examples.

Besides the local use, there are also possibilities to incorporate the TXT remotely in programs which are running on other systems.
The TXT works with Berkely sockets and so called transfer area (TA) for communication.
The TXT is using a socket with port 65000 for the TA, 65001 for the video and 65002 for the I2C.
On --- you will find how to do this from a .NET Visual Studio environment.
On ---- you will find how to do this from Python.

However this C/C++ part covers only programs that will run directly on the TXT.

## The organisation of the repsitory
- The map FtTxtExamples is aiming on the end user.  
The map contains usable examples.
- The map FtTxtWorkspace is aiming on the developer
The maps contains Eclipse example projects and the supporting TXT libraries.
- In the root you will find a description of "How to ... ? and overviews"

Both maps will be available under "release" as zip files.


## Documentaion
- this Document
- [What is an SLI](SLI.md).
- [The program development environment](tools.md).
- [Notes](Notes.md).
- [Introduction and overview SLI project for Eclipse]( FtTxtWorkspace/README.md).
- [Introduction and overview SLI applications for the end user](FtTxtExamples/README.md).

# document history
- 2020-05-16 v 466.1.1 new
