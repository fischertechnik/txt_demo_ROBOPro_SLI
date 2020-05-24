# Examples for the end-user
[link](#tracelog)

[link](#dinpanel)


[link2](#how-to-consult-the-trace-log)

Here you will find pre-compiled examples.
## What are these maps about?
### For a SLI:
- lib map: The shared library in the
- RoboPro map: One or more RoboPro programs, which shows how to use this SLI
- root: Documentation about the functionality of this SLI
### For the local executable
- C-Program map: The executable
- root: Documentation about the functionality of this executable.

## How to install?
The installation of the SLI's and executable can be done with the TXT web interface.
The TXT interface enables also the maintenance of the public maps on the TXT, including connected USB-memory and SD-card (formatted as FAT32)
- The TXT web server needs to be activated.
- Use your web browser to access the web page
URL= http://<ip-addres of the TXT>
- ID=TXT, pasword= the actual number of the TXT
- upload the SLI library to the libs map.
- upload the executable to the C-Program map

## How to consult the trace log? {#tracelog}
When you are developing a RoboPro application which is using a SLI, it could be useful to consult the trace log.
How to do that?
- Start a SSH connection with Putty with a screen -r command.
  Be sure that Putty is login to a file. See also: 
- 
 
## Overview examples

### SLI_TeachIn
- This SLI TeachIn is the industrial Robot with 4 motors and switches as for the industrial Robot with 2 encoder motors and 2 motor (TX-C set).
- Both the TeachIn RoboPro programs has been extended.
  There is now one extended player for both versions.
- Target controller: fischertechnik TXT
- The libTxtSliSaveTeachIn.so SLI makes it possible to read and to write files with  4D-coordinate set from and to the `/etc/knobloch/Data` (Date area on the TXT)
#### Panel player
![console](./SLI_TeachIn/docs/player(panel_02).png)
#### Panel TeachIn
![console](./SLI_TeachIn/docs/TeachIn(panel_02).png)

<a name="#dinpanel"></a>
# document history
- 2020-05-16/22 v 466.1.1 new
