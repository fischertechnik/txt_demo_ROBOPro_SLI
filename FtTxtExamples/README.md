[Back to main content overview](/README.me#overview)
# Examples for the end-user
(readme of the 'FtTxtExamples' root)

Here you will find pre-compiled examples.
## What are these maps about?
### For a SLI:
The project maps contains at least:
- `libs` map: The shared libraries, compiled C/C++ file(s) 
- `RoboPro` map: One or more RoboPro programs, which shows how to use this SLI
- `root` Documentation about the functionality of this SLI  |   |  

### For the local executable
The project maps contains at least:
- `C-Program` map: The executables, compiled C/C++ file(s).
- `root`  Documentation about the functionality of this executable.

## How to install?
The installation of the SLI's and executable can be done with the [TXT web server interface](../HowToUseTxtWeb.md).
The TXT web server interface enables also the maintenance of the public maps on the TXT, including connected USB-memory and SD-card (formatted as FAT32)
- The TXT web server needs to be activated.
- Use your web browser to access the web page
URL= http://<ip-addres of the TXT>
- ID=TXT, password= the actual number of the TXT
- upload the SLI library to the libs map.
- upload the executable to the C-Program map

## How to get and to inspect the trace log?<a id="howtracelog"></a> 
When you are developing a RoboPro application which is using a SLI, it could be useful to consult the trace log.
How to do that?
- Activate your TXT and check the ip-address.
- Copy the SLI to the TXT in `libs` map with FileZilla. [See also:](../WhichToolsYouNeed.md#filezillasetup) 
- Start a SSH connection with Putty with a screen -r command.<br/>
  Be sure that Putty is writing his log to a file. [See also:](../WhichToolsYouNeed.md#puttysetup)
- Open this trace log file with Notepad++. [See also:](../WhichToolsYouNeed.md#notepad)<br/>
  When the trace log become longer, Notepad will ask you for reloading it.<br/>
  With Notepad++ it is easy the search in the trace log file and to inspect the trace log.
- Start the accompanying RoboPro program try to understand wat is in the trace log file.<br/>

This is a typical of a SLI function that has been called from RoboPro.<br>
- `ENTRY 0`  the start with here a input value 0;
- `***** get CoorR=0` a line with information written by the SLI. 
- `RESULT 0 0` end of the call, `0` is the return value and means no error, `11` is the parameter value.
   
```
SharedLibraryInterface_ExecuteReadINT16 libTxtSliSaveTeachIn.so getCoorRShort: ENTRY 0
SharedLibraryInterface_ExecuteReadINT16 lib 0xb3501628
SharedLibraryInterface_ExecuteReadINT16 func 0xb40482fd
***** get CoorR=0
SharedLibraryInterface_ExecuteReadINT16 libTxtSliSaveTeachIn.so getCoorRShort RESULT 0 11 
 ```
## Overview examples

### SLI_TeachIn

- This SLI TeachIn is the industrial Robot with 4 motors and switches as for the industrial Robot with 2 encoder motors and 2 motor (TX-C set).
- Both the TeachIn RoboPro programs has been extended.
  There is now one extended player for both versions.
- Target controller: fischertechnik TXT
- The libTxtSliSaveTeachIn.so SLI makes it possible to read and to write files with  4D-coordinate set from and to the `/etc/knobloch/Data` (Date area on the TXT)
- [See also the project readme](./SLI_TeachIn/README.md)
#### Panel player
![console](./SLI_TeachIn/docs/player(panel_02).png)
#### Panel TeachIn
![console](./SLI_TeachIn/docs/TeachIn(panel_02).png)


# document history <a id="history"></a>
- 2020-05-16/22 CvL 466.1.1 new
