# Which tools you need?
As software developer you need a tool box, the sofware development environment. For the more experiance software engineers this is a personal set of tools. But were to start as beginner? Creatif programming and problem solving is more then only entering program code and compiling. It has also something to do with:
- understand and decrib the problem
- create and decrib a solution
- implement this solution including documentation
- testing an error searching.

For this there is  needed a set of tools. Hereby an overview:

- a program development environment with some plug in tools, like
  - a  documentation generator
- a basic text editor for text, markdown, XML/JSON/HTML
- a remote SSH terminal
- a SFTP file transfer tools
- RoboPro 4.6.6
- TXT with firmware 4.6.6 or 4.7.0

## Toolbox for the starter (advice)
### Step 1 What to download?

1. Eclipse
Versie: Eclipse 2020-03 or higher (only 64 bits)

   [Download]( https://www.eclipse.org/downloads/packages/release/2020-03/r/eclipse-ide-cc-developers-includes-incubating-components)  Remark: This is only the installer.

   Here you can find [additional help]( https://help.eclipse.org/2020-03/index.jsp) <br/>
   Eclipse has two different possibilities to install additinal functionality.

1. Linaro
The TXT firmware is using gcc-linaro-7.2.1-2017.11-i686-mingw32_arm-linux-gnueabihf.

   [Download]( https://releases.linaro.org/components/toolchain/binaries/7.2-2017.11/arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-i686-mingw32_arm-linux-gnueabihf.tar.xz)

2. FileZilla

   [Download]( https://filezilla-project.org/download.php)

4. Putty

    [Download](https://putty.org/)


5. Notepad ++

    [Download]( https://notepad-plus-plus.org/downloads/)
    This software can be use to inspect log files and edit text files.
 [Plugins overview]( https://npp-user-manual.org/docs/plugins/)<br/>
 [Plugins List](https://github.com/notepad-plus-plus/nppPluginList/)<br/>
     Suggestions for Plugins:
    - MarkdownViewerPlusPlus

6. ATOM editor

   [Download](https://atom.io/ Atom 1.46.0 ot higher) <br/>
   Packages: [The functionality of Atom can be extended with the so called packages.](https://atom.io/packages)<br/>
Suggestions for packages:
    - language-markdown
    - markdown-preview-plus
    - markdown-image-paste

1. VNC-client
   To make use of the TXT VNC-server you will need a viewer:
   [Download RealVNC viewer ](https://www.realvnc.com/en/connect/download/viewer/)

1. Graphviz
For the graphical part of the DOxyGen documentation tool you will need to install graphviz.
[Download](https://graphviz.gitlab.io/_pages/Download/Download_windows.html)

1.	RoboPro
    [See RoboPro 4.6.6 and the firmware 4.6.6 and 4.7.0](
https://github.com/fischertechnik/FT-TXT/releases)
Firmware 4.7.0 can be boot from SD-card ans used in coorporation with RoboPro 4.6.6.

### Step 2 How to install?
Note: Graphviz needs to be install after the installing  Eclox from the Eclipse Marktplace.
#### Maps
First of all, create on the same drive, the following maps:
-	\eclipse\\<br/>
  Installation map for Eclipse
-	\workspaces\\<br/>
  Map were you can put the root maps for the Eclipse workspaces.
-	\TXT\<br/>
-	\TXT\toolchain\<br/>
  Installation map for the Linaro toochain
-	\Log\<br/>
- \Log\Putty\<br/>
   Map for the Putty Log-files

#### Software
After this start with the installations of the downloaded software
-	Install Notepad ++, Atom ,FileZilla, Putty and RealVNC viewer<br/>
 like you are use to do with Windows programs.<br/>
 Their installation programs will guide you through the process.

- Eclipse<br/>
Run the installer.<br/>
Install “Eclipse IDE for C/C++ developers” in the map: `H:\eclipse\cpp-2020-03`.<br/>
The installer will also install or ask for “Java 1.8+ VM”.<br/>
Eclipse is a JAVA application and needs Java.<br/>
See also the following 3 screen dumps:

<img src="./docs/toolbox/install(Eclipse01).png" width="40%" >
<img src="./docs/toolbox/install(Eclipse02).png" width="40%" >
<img src="./docs/toolbox/install(Eclipse03).png" width="40%" >

- Linaro<br/>

    Last but not least is making the Linaro toolchain available.<br/>
Unzip the Linaro toolchain into the map \TXT\toolchain\.<br/>
You will get something like this.<br/>
 `H:\TXT\toolchain\gcc-linaro-7.2.1-2017.11-i686-mingw32_arm-linux-gnueabihf`<br/>
In this case `H:` can be a different drive. This path you will need later to configurate the tool chain in your C/C++ project in Eclipse.<br/>
An image of how this looks like in the Windows explorer:

  <img src="./docs/toolbox/install(Linaro01).png" width="70%" >



### Step 3 How to setup the software?
Prepare the TXT, the SSH remote console) and SFTP (remote file system)
Setting up FileZilla and Putty. Install DoxyGen with Eclipse Marktplace.

#### How to prepare the TXT controller?

  It is time to create the connections with your TXT.

  - Start your TXT and test the connection with RoboPro.
  - Write down the IP-address of this connection. It does not matter if you are using Bluetooth, USB, Wifi or Wifi-access point.
  - Don’t forget to activate on the your the SSH Daemon and WEB server

<img src="./docs/toolbox/install(TXT01).png" width="35%" >
<img src="./docs/toolbox/install(TXT02).png" width="35%" >

#### How to set up Putty for a SSH connection with the TXT?
Putty is a remote console; it can be used to work with LINUX command.
We are using Putty as console.

Start Putty and create a new SSH-session with the general user ROBOPro.
The user name: `ROBOPro`, the password: `ROBOPro`
- Fill in the IP-address from your TXT01
- Choose SHH
- Fill in the map for the logfiles: `h:/Log/Putty/putty_&Y-&M-&D_&T.log` .
-	As remote command: [screen -r](https://www.geeksforgeeks.org/screen-command-in-linux-with-examples/)
     You can find what this means in the Linux command help on the internet.
When you leave this line blanc, you will get the console prompt.
-  Save these setting and start the connection.
-  Run with RoboPro a small RoboPro program and observe what the console shows you.
- Go with the Windows file manager to the \Log\Putty\ map and open with Notepad++ the log file.
Now you can also inspect the results. When the log file changes, Notepad++ will reload the file.
- Warning: Use only the TXT root account for very special activities.

<img src="./docs/toolbox/install(Putty01).png" width="45%" >

<img src="./docs/toolbox/install(Putty02).png" width="45%" >

<img src="./docs/toolbox/install(Putty03).png" width="45%" >

#### How to set up FileZilla?
FileZilla is a file transfer program.
- Start FileZilla, go to the “file” menu and start the “site manager”.
- Create a “new site” for a SFTP- (Secure File Transfer Protocol)
for the IP-address of the TXT controller.
The user name: `ROBOPro`,
 the password: `ROBOPro`.
  - Warning: Use only the root account for very special activities

<img src="./docs/toolbox/install(FileZilla01).png" width="60%" >

Start FileZilla and observe what you are seeing.<br/>
Remark: The public maps can also be inspected and maintain via the TXT web interface.<br/>
See for an introduction the first part on [this link:]( https://github.com/fischertechnik/txt_training_factory/blob/master/doc/WEBServer_de.md)

<img src="./docs/toolbox/install(FileZilla02).png" width="60%" >

-  The “default local directory” is for later.
-  The “default remote library” is normally `/opt/Knobloch/`.
    Here you will find the maps for the `Data`, `libs`, `C-program`, etc.

#### How to set up Eclipse?
How to work with the SLI workspace and set up a new project will discuss later. But we still have to install the DoxyGen tool as code documentation plugin for Eclipse.

   installation: [Eclox via Eclipse Markplace](https://anb0s.github.io/eclox/),<br/> [See also](http://www.doxygen.nl/download.html)
   - Start Eclipse
   - Go to top menu `Help`
   - Select `Eclipse Markplace..`
   - Search for `Eclox`
   - Instal eclox
   - `Instal Now` and `Finish`
<img src="./docs/toolbox/install(DoxyGen01).png" width="45%">

<img src="./docs/toolbox/install(DoxyGen02).png" width="50%">

#### Install Graphviz
Install the WIndows application `Graphviz`.<br/> **Check after the installation** if the path to the bin has been added to the System Environment variable `Path`!)

<img src="./docs/toolbox/install(grap01).png" width="99%"><br/>

Now we are ready to start with the [set up of the SLI workspace and start programming](HowToStartProgramming.md)


# document history
- 2020-05-16/17/18 CvL 466.1.1 new<br/>
  Original from: on-line training SLI-programming<br/>
  © 2020-04  ing. C. van Leeuwen Btw.  Enschede Netherlands
