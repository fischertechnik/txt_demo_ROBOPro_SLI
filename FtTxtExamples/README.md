# Examples for the end-user
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
 
## Overview examples

### SLI_TeachIn
-  For both the TeachIn for a industrial Robot with 4 motors and switches and a industrial Robot with 2 encoder motors and 2 motor (TX-C set).
-  Target controller: fischertechnik TXT
-  With the libTxtSliSaveTeachIn.so. This SLI makes it possible to read and write files with the 4D coordinate set from and to /etc/knobloch/Data (Date area on the TXT)


# document history
- 2020-05-16/22 v 466.1.1 new
