# Extended C/C++ programming for the TXT
## Introduction
This is all about writing and/or using local programs on the TXT and RoboPro extensions.

There are different possibilities to use C/C++ programs localy on the TXT.
- As TXT Shared Library Interface (SLI) for ROBOPro<br/>
A SLI extends the basic set of RoboPro elements with new one's.
It enables the user to add functionality to RoboPro.
- As TXT local programs
A local program replaces a local RoboPro program.



A **developer** will find here information about the toolbox needed, setting up a development environment on MS-Windows. How to use this environment to ceate, document and use your custom SLI's or executable.
An **end-user** will find here information and examples about how to use the results of what has been develop.

Besides the local use, there are also possibilities to incorporate the TXT remotely in programs which are running on other systems.
- The TXT works with Berkely sockets and so called transfer area (TA) for communication.
- The TXT is using a socket with port 65000 for the TA, 65001 for the video and 65002 for the I2C.
- [Here](https://github.com/fischertechnik/txt_demo_c_online) you will find how to do this from a .NET Visual Studio environment.
- It is also possible to use Python with the [FtRoboPy](https://github.com/ftrobopy/ftrobopy) (pre installed on the TXT)<br/>
  However Python is using a connection over the sockets and is in fact a remote program that runs with the IP-address (localhost) 127.0.0.1.

However this C/C++ part covers only programs that will run directly on the TXT.

## The organisation of this GitHub  repossitory
- The map `FtTxtExamples` is aiming on the end user<br/>
The map contains usable examples.
- The map `FtTxtWorkspace` is aiming on the developer<br/>
The root contains Eclipse example projects and the supporting TXT libraries.
- In the root you will find a descriptions of "How to ... ? and overviews"

Both the `FtTxtExamples` and `FtTxtWorkspace` maps will be available under "release" as seperate zip files.


## Documentation
### For the developer:
- this Document
- [What is an SLI?](SLI.md).
- [What is in my toolbox? My program development environment](WhichToolsYouNeed.md)
- [How to setup my Eclipse workspace and start with my first project?](HowToStartWithFtTxtWorkspace.md)
- [How to start a new project]()
- [Notes](Notes.md).
- [Introduction and overview SLI project for the developer](./FtTxtWorkspace/README.md).
### For the end-user:
- [Introduction and overview SLI projects for the end user](./FtTxtExamples/README.md).

# document history
- 2020-05-16,18 CvL 466.1.1 new
