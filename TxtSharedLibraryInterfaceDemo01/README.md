# TXT Shared Library Interface (SLI) Demo01 for ROBOPro

This demo shows how to use the incoming  IR data in the transfer area from the IR-JoyStick in a SLI.
The left Joystick data (X and Y) is use to calculate the motor powers for a two wheel drive FT-Bot. For example the TXT-discovery set.
Joystick up: is more forwards speed; down is backwards speed. Joystick left/right makes the FT-bot turns or even rotated.
To have more control over the model, the power is corrected to avoid too less power.


Basic information about the SLI can be found in the **TxtSharedLibraryInterface**, the starting example.

> You need TXT firmware version >=4.4.3

> see ROBOPro help in section 8.2.9 and 8.2.10

> See for the set up of your Eclipse development environement:

> The .so binairies in the Release map can lso use directly.

# What is in this library?
In this library are two main RoboPro element available
> The RoboPro element "Joystick".
  This element takes as input which joystick and calculates  the power for the left and right motor.
  These results are available by two other RoboPro elements.
  This functionality will runs in both online and local mode.
> See RoboPro example code: **TxtSliDemo01_A.rpp** and **TxtSliDemo01_AA.rpp**.
 
> The RoboPro element "JoystickMotors" 
  Is an extended version of the RoboPro element "Joystick".
  The left and right moter are powered directly.
  This functionality will only runs in the local mode.
> See RoboPro example code: **TxtSliDemo01_B.rpp** and **TxtSliDemo01_BB.rpp**

# overview of the RoboPro elements in the SliDemo01 SLI
Joystick and JoystickMotors are the main elements.

## (set) Joystick (short):
   Result:  Set the values for MotorLeftPower and MotorRightPower.
   Input: the id for the fischertechnik IR-controller
          1: both switches off
          2: switch 1 on,  switch 2 off
		  3: switch 1 off, switch 2 on
		  4: both switches on
   Error flow in case of an error or wrong value for the IR-controller ID

### (set) Transformer:
     choice for the algoritme for the behavior of the X_Y-joystick to left/right motor power.  
     [1..3]
     0 is liniar
     1 elimination of offset 0..10%, 10%.. 100% log-function.
     2 elimination of offset 0..5%, 5%.. 100% log-function
     3 liniar with an offset of 0..45%	 

### (get) MotorLeftPower and  (get) MotorRightPower:
    get the calculated value for the motor power.
    [-512..0..512]
	Note: Use this in combination with the RoboPro element MotorOutput.
    Note: the property resolution of the element MotorOutput needs to configure for 512 steps 

## (set) JoystickMotors (short):
   Result: The new values are sent to both the Motors and set also the values for MotorLeftPower and MotorRightPower.
   Input: the id for the fischertechnik IR-controller
          1: both switches off
          2: switch 1 on,  switch 2 off
		  3: switch 1 off, switch 2 on
		  4: both switches on
   Error flow in case of an error or wrong value for the IR-controller ID

###  (set) MotorIdLeft and (set) MotorIdLeft:
     Set which motor is in use as right and which one as left motor.
     Default: Left =1 (M1) and Right = 2 (M2).	 

### (set) Transformer:
     choice for the algoritme for the behavior of the X_Y-joystick to left/right motor power.  
     [1..3]
     0 is liniar
     1 elimination of offset 0..10%, 10%.. 100% log-function.
     2 elimination of offset 0..5%, 5%.. 100% log-function
     3 liniar with an offset of 0..45%	 

### (get) MotorLeftPower and  (get) MotorLeftPower:
     get the calculated value for the motor power.
     [-512..0..512]
	 Note: this elements can for example used for printing the actual power.
    
## ROBOPro
The function names should start with get and end with Short or Double to indicate the type, but arbitrary names can be used as well. A return value of 0 is interpreted as success, all other return values as error.

> **Please note:** the functions must be declared as extern “C” in C++ code, because at the link level C++ functions have complicated mengled names, which encode the data type of the function. C functions have their usual name at the link level.
 
![Window_input](docs/Window_input.png)

![Window_output](docs/Window_output.png)

### Property Window
- Under Library name you can enter the name of the shared library file. The library file must be copied to the TXT controller into the ```/opt/knobloch/libs``` or ```/usr/libs``` folder. If Extend library name is checked, the name is prepended with lib and the extension .so is appended.

- Under Function name the C name of the function to be called is entered. If Extend Function Name is checked, the name is prepended with get and the selected data type, either Short or Double, is appended.

- If Error output is checked, the element gets an additional flow output, which is used when the called C function returns an error (that is 1).

- If Lock Interface is checked, the shared library IO is locked to the current ROBOPro thread. This allows safe combination of several shared library input and output elements without interruptions from other threads. The last element in a sequence must have this unchecked. Otherwise no other ROBOPro thread can use the shared library interface.

- The Data type of the value returned can be either a 16 bit signed integer or a floating point value. If the data type is floating point, the value is converted from C 64 bit double format to ROBOPro 48 bit float format. Please note that the range and precision of these types is different and conversion errors may occur, especially for out of range values. Please also note that for 16 bit integers values a value of -32768 is treated as undefined/error in ROBOPro and is usually displayed as '?'.
