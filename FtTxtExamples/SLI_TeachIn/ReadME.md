# Example SLI Teachin with read/save
The  SLI offers the possiblity to read a set of coordinates from a file N on the Data area and also to write a list of coordinates to a file M on the Data area.

## Can these files  edit manualy?
These files can copy with the TXT web interface to your local system, then edit en copy back to the TXT.

##  How to instal?
Copy the `....so` with the TXT web interface to the `libs` map.
(Or with a SFTP tool like FileZilla.)

## Robopro
Run the TeachIn RoboPro program in the on-line mode.
After opening the program, the you will find some extra buttons and displays on the consol.
- TeachIn.rpp => for robots with switches and motors
- TeachIn_TC-C => for robots with two encoder motors and 2 normal motors+switches.
- TexachIn complete=> Both system and smulation.

## File format
Each line contains a coordinate plus a new line <end off line>
`x,y,z,r <eol>`

The coordinates can be: edit, inset new or deleted.
Don't forget to add a new line to the last coordinate.
The read will skip empty lines.
Pay attention to the maximum ranges. The is no control check!
