<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Eclipse example projects](#eclipse-example-projects)
	- [Overview example projects](#overview-example-projects)
		- [TxtSharedLibraryInterface](#txtsharedlibraryinterface)
		- [TxtSharedLibraryInterface2](#txtsharedlibraryinterface2)
		- [TxtSharedLibraryInterfaceDemo01](#txtsharedlibraryinterfacedemo01)
		- [TxtSharedLibraryInterfaceDemo02](#txtsharedlibraryinterfacedemo02)
		- [TxtDeps](#txtdeps)
	- [My first project](#my-first-project)
		- [Copy and Paste the start projects](#copy-and-paste-the-start-projects)
		- [Rename some files](#rename-some-files)
		- [Inspecting and updating the project properties](#inspecting-and-updating-the-project-properties)
		- [Start with coding](#start-with-coding)
- [document history <a id="history"></a>](#document-history-a-idhistorya)

<!-- /TOC -->
[Back to main content overview](../README.md#overview)

# Eclipse example projects
Here you will the TXT library and some Eclipse projects.

> You need TXT firmware version >=4.6.6

> see ROBOPro help in section 8.2.9 and 8.2.10

## Overview example projects

All examples are Eclipse projects.
###  TxtSharedLibraryInterface
[See readme](./TxtSharedLibraryInterface/README.md)<br/>
    Step 1 What are the SLI basics?
    
### TxtSharedLibraryInterface2
[See readme](./TxtSharedLibraryInterface2/README.md)<br/>
    Step 2 Does  fischertechnik RoboPro SLI-mechanism knows some peculiarities?<br/>
    Blocking issues, a workaround for the online 5sec problem and init/stop issues. 
       .    
### TxtSharedLibraryInterfaceDemo01
[See readme](./TxtSharedLibraryInterfaceDemo01/README.md)<br/>
    SLI show the use of the Joystick<br/>
    A control element for a two wheels FT-bot (TXT discovery kit)
    
### TxtSharedLibraryInterfaceDemo02
[See readme](./TxtSharedLibraryInterfaceDemo01/README.md)<br/>
    (not yet available)
    SLI show the use of the Extended Motor control

### TxtDeps
[See readme](./TxtDeps/README.md)<br/>
    This project contains the include and library fields for the fischertechnik SLI's and local programs Eclipse project. It is as it is, no need to compile or change.
		
## My first project
Advice: Stdy carefully the TxtSharedLibraryInterface, TxtSharedLibraryInterface2 and TxtSharedLibraryInterface3 before you start with proper project.
Exercise:<br/>
You are going make the basics for your first project. 

### Copy and Paste the start projects
- Select the `TxtSharedLibraryInterface` in the Eclipse `Project Explorer`. 
- Right click the mouse and select `Copy. 

![](./docs/NewProject(01).png)

- Right click again the mouse and select `Paste`.

![](./docs/NewProject(02).png)

- Change the name of the project.
 ![](./docs/NewProject(03).png)
 
### Rename some files
Rename in the src the `LibExampleSLI.cpp` file, the ROBOPro' and in the root the `TxtSharedLibraryInterface.doxyfile`

![](./docs/NewProject(06).png)
![](./docs/NewProject(07).png)

### Inspecting and updating the project properties

(See in case of problems also)[../ProjectSetUp(so).md ] for information over the settings.<br/>
Select the project properties
 
![](./docs/NewProject(04).png)
 
Inspect the setting and correct the reference to the project his `include` map

![](./docs/NewProject(05).png)

- Compile the project and see if everything is fine. Otherwise correct small mistakes.<br/>
After this you project is ready to start with writing code.
 
### Start with coding
- You can remove the 4 examples functions but you can also use them as templates.
- Update the iit and stop.
- Add the `StayAwake` function
  ```C	
int setStayAwakeShort(short t) {
	if (!IsInit) {
		fprintf(stderr, "setStayAwakeShort: Not initialized!\n");
		return -1;
	} else {// fprintf( "ExampleSLI:setValueDouble: already initialized!\n");
	}
	return 0;
}
``` 	
- Don't forget to keep your documentation up to date.

# document history <a id="history"></a>
- 2020-05-16,24 Cvl 466.1.1 new
