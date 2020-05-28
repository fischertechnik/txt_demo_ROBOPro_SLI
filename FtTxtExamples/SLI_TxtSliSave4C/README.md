
#TxtSliSave4C project

## Introduction 
This SLI makes it possible to write to and read from files in the public data area.
[See also the fischertechnik public web interface](https://github.com/fischertechnik/txt_demo_ROBOPro_SLI/blob/master/HowToUseTxtWeb.md)

The SLI is able to write/read sets of coordinates to/from files in the TXT public Data map. The files are numbered with Fn.<br/>
The coordinates can 3D, 4D or 5D. (D = Dimension).<br/>
At the end of each read or write subroutines the file is closed.<br/>
The dim (dimension) and/or Fn (file number) can be changed before a read or write operation.<br/> 
The data is saved as text file, so this files can be edit manual too.


## RoboPro perspective

### Main routine

![](./docs/rb(1.3_f01).png)


### Write routine

![](./docs/rb(1.3_f02).png)

Fn = file numbered (int>=0)<br/>
dim =dimension (3,4 or 5)<br/>
Append =1 means that the information is add to the file; 0 file will be, if exist, overwritten.


### Read routine

![](./docs/rb(1.3_f03).png)
Fn = file numbered (int>=0)<br/>
dim =dimension (3,4 or 5)<br/>
Append =1 means that the read information is add to the lists elements; 0 that the list is renewed.

# document history 
- 2020-05-16/17/18/19/24 CvL 466.1.1 new<br/>
- Original from: on-line training SLI-programming<br/>
  © 2020-04 ing. C.van Leeuwen Btw. Enschede Netherlands



