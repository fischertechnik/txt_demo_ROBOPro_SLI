# How to setup my Eclipse workspace and start with my first project?
 [What is in my toolbox?](WhichToolsYouNeed.md)

Now that our toolbox [our toolbox](./WhichToolsYouNeed.md) is ready, it is time to learn how to get started with your own project via the examples.

## How to set up the FtTxtWorkspace?
`H:/workspaces` has been used  in this example as path to the `FtTxtWorkspace`. But feel free to use your own path.
- Download the `FtTxtWorkspace.zip` from the [txt_demo_ROBOPro_SLI/releases](https://github.com/fischertechnik/txt_demo_ROBOPro_SLI/releases)
- Unzip this file in the `H:/workspaces`. This will looks like something like:

  <img src="./docs/toolbox/start(01).png" width= "65%" >
- Start now Eclipse <br/>
  Select the right path to your workspace, here: `H:/workspaces/FtTxtWorkspace`:<br/>
  Press `Launch`.

  <img src="./docs/toolbox/start(02).png" width="65%">

- Close the `Welcome` screen

   <img src="./docs/workspace1/start(03).PNG" width="90%" >

   You will see this screen

  <img src="./docs/workspace1/start(04).PNG" width="90%" >

  ![](./docs/ProjectSetup/start(04).png)


- Go in the top menu to the item `Windows` en select `Preferences`

  <img src="./docs/ProjectSetup/start(04A).png" width="90%" >

- Select `C/C++`, `Build` and then `Environment`, <br/>
  add a new Environment variable `LINAROMAP`,<br/>
  and take your map with the Linaro toochain as value (no / or \ at the end!!),<br/>
  Press `Apply` and `Apply and Close`.

  <img src="./docs/ProjectSetup/start(04B).png" width="90%" >

  You will see this screen again:

  <img src="./docs/ProjectSetup/start(04).png" width="90%" >

-  Go in the top menu to the item `FIle` en select `Import`<br/>
   Select `General` and `Existing Projects into Workspace`<br/>
   Press `Next`.

  <img src="./docs/ProjectSetup/start(05).png" width="90%" >

-  Enter the root directory of the workspace FtTxtWorkSpace,<br/>
   select the appearing 3 projects,<br/>
   press `Finish`.

  <img src="./docs/ProjectSetup/start(06).png" width="90%" >

- If everything went well, you will see this.<br/>
   In the Eclipse map Includes (this is not the same as the user map inlcudes) you will see something like this. The ${LINARO} variable has been fill in nicely.

  <img src="./docs/ProjectSetup/start(07).png" width="90%" >

   Your workspace is now ready to use, to start programming and testing.
   For example, you can start with compiling the first project `TxtSharedLibraryInterface`.
    - The [xxx document]() will describe how you can get the result to work on the TXT and you will learn about a strategy for troubleshooting and error discovering.
    - The [xxxx document]() will describe how you can create a new project and then start working on your own project.
  - With File | Import you can also add other existing projects to your workspace. Eclipse is very versatile, see it as a challenge to discover the available possibilities step by step.






# document history
- 2020-05-18,19 CvL 466.1.1 new
