# How to start with my first fischertechnik SLI project?

In [How to setup my Eclipse workspace?](./HowToStartWithFtTxtWorkspace.md) we see how we can make Eclipse ready to start for the real work: creating, compiling and testing of program.<br/>
Now we are going to compile and run a SLI and setup our first new SLI.
We will also see how to trace the progression of a running RoboPro program, which is using a SLI with Putty and Notepad++

The support this introduction you will find a set of projects with the name `TxtSharedLibraryInterface``in the `FtTxtWorkspace`. 

## TxtSharedLibraryInterface
`TxtSharedLibraryInterface` is about the basics:
- compiling
- installing
- using in a RoboPro programming
- tracing with Putty and consultation of the trace log with Notepad++
- tracing with SPDlog.

The 'TxtDeps` root contains a README.me about the instruction of how to make use of these libraries and includes in your projects

Each root  of the following projects  contains a README.md with the detail, description  and instructions for that project
### TxtSharedLibraryInterface
`TxtSharedLibraryInterface` is about the basics.

### TxtSharedLibraryInterface2
`TxtSharedLibraryInterface2` is about the on-line 5 sec problem
### `TxtSharedLibraryInterface3`
`TxtSharedLibraryInterface3` the blocking problem.
### TxtSharedLibraryInterfaceDemo01
 `TxtSharedLibraryInterfaceDemo01`is about the use of the TA (`transfer area`)- -
### TxtSharedLibraryInterfaceDemo02
 `TxtSharedLibraryInterfaceDemo02` is about the use of an encoder motor
### TxtMyProject
Is about creating the start code for your first project.

## Adding projects to this `FtTxtWorkspace`
Later you can add more new projects or projects from others into this `FtTxtWorkspace`.
It is also possible to have both SLI and executable projects in this `FtTxtWorkspace`. Both are using the same FtxDeps and `LinaroMap` Environment variable. Only the asset different.
- Add an existing Eclipse TXT project to this workspace.
  Copy that relevant project into the `FtTxtWorkspace` and use the Eclipse menu `file|Import` to add this project to the workspace. **Check if the project properties are fine!** 
  
- Create a new project by copying an existing one.
  Select the project, which you prefer to copy, in the`FtTxtWorkspace`.<br/>
  Go with the right mouse button to the properties and select `Copy`.<br/>
  Go with the right mouse button to the properties and select `Past`.<br/>
  You will see a popup-box with the question for a new name. Fill the name for your project in. Press the `Copy` button.<br/>
  Check the project properties of the `C/C++ General`| `Paths and Symbols`  for the includes are fine. Probably you will need to change some paths.<br/>
  Clean the `src` file and start with coding. 
- How the create  a new SLI project from scratch has been describe in:   ![link]() 

That is all folks, have fun and success with your proper SLI's and/or executables.

# document history <a id="dinpanel"></a>
- 2020-05-24 CvL 466.1.1 new<br/>
  Original from: on-line training SLI-programming<br/>
  © 2020-04 ing. C. van Leeuwen Btw. Enschede Netherlands
