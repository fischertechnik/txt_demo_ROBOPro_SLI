[Back to main content overview](../README.md#overview)

# Eclipse example projects
Here you will the TXT library and some Eclipse projects.

## Overview example projects
> You need TXT firmware version >=4.6.6

> see ROBOPro help in section 8.2.9 and 8.2.10

## Overview examples

All examples are Eclipse projects.
### [TxtSharedLibraryInterface](./TxtSharedLibraryInterface/README.md)
    SLI basics.
### [TxtSharedLibraryInterface2](./TxtSharedLibraryInterface2/README.md)
    Workaround for the online 5sec problem.    .    
### [TxtSharedLibraryInterfaceDemo01](./TxtSharedLibraryInterfaceDemo01/README.md)
    SLI show the use of the Joystick<br/>
    A control element for a two wheels FT-bot (TXT discovery kit)
### [TxtSharedLibraryInterfaceDemo02](./TxtSharedLibraryInterfaceDemo01/README.md)
    (not yet available)
    SLI show the use of the Extended Motor control

### [TxtDeps](./TxtDeps/README.md)
    Contains the include and library fields for the fischertechnik SLI's and local programs Eclipse project (TxtDeps is also a project)
		
## My first projects
Exercise:<br/>
You are going make the basics for your first project. 

### Copy and Paste the start projects
- Select the `TxtSharedLibraryInterface` in the Eclipse `Project Explorer`. 
- Right click the mouse and select `Copy. 

![](./docs/NewProject(01).png)

- Right click again the mouse and select `Paste`

![](./docs/NewProject(02).png)

- Change the name of the project.

![](./docs/NewProject(03).png) 

- Rename also in the src the `LibExampleSLI.cpp` file. and in the root the `TxtSharedLibraryInterface.doxyfile` 
- 
![](./docs/NewProject(04).png) 

### Inspecting and updating the project properties

(See in case of problems also)[../ProjectSetUp(so).md ] for information over the settings.<br/>
![](./docs/NewProject(05).png)
![](./docs/NewProject(06).png)
![](./docs/NewProject(07).png)

  
- Add the `StayAwake` function
```	
/*! \brief need to be used in the online mode.
 * \bug In the online mode, RoboPro is terminating
 * ("ERROR calling read") the contact with the SLI modules after 5 sec of inactivity.
 * As workaround for this bug, RoboPro can call this empty function every  msec <5000.
 * \param t not in use
 * \return 0
 */
int setStayAwakeShort(short t) {

	if (!IsInit) {
		fprintf(stderr, "setStayAwakeShort: Not initialized!\n");
		return -1;
	} else {
		// fprintf( "ExampleSLI:setValueDouble: already initialized!\n");
	}

	return 0;
}
``` 	

# document history <a id="history"></a>
- 2020-05-16,24 Cvl 466.1.1 new
