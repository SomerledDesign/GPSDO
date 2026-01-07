Lady Heather Version 4.0 (with Linux support)

To use this program on Linux:

1) Create a directory to install it in and switch to that directory.

2) Unzip the zip file into the directory

3) Make sure you have the g++ compiler and libx11-dev packages installed:
      sudo apt-get install g++
      sudo apt-get install libx11-dev

4) Compile the code:
      make

5) Run it:
   ./heather -1u             (for ttyUSB0 serial input)
   ./heather -1              (for ttyS0 serial input)
   ./heather -id=device_name (for using a non-standard serial device)
   ./heather -ip=addr:port   (for internet connected server)

   The you can use a different digit on the -1 or -1u options.  You use
   a # digit one more than the desired ttyS# or ttyUSB# port number!

   To run heather on Linux, the user must have access;permissions
   for the serial device.  You can run heather with sudo or
   (much better idea) give the user access to the "dialout" group:
       sudo usermod -a -G dialout user_name
   

Known issues:
   With some (older) Linux distros you may need to add a -lrt option to the
   linker command in the makefile.  This links the the library for getting
   and setting the system clock.  Most distros have these functions in the
   standard C library. For the system clock setting functions to work, you need
   to have root permissions.  Since most Linux boxes have NTP running, you
   probably should not be using the system time setting commands, anyway.

   On some distros, resizing the window may occasionally cause the connection 
   to the X11 display server to go away.  The window will disappear. This mainly
   seems to happen when maximizing the display.  Ctrl-C your terminal window 
   and restart Heather.

   If you maximize the display window, you cant restore the previous window
   size by clicking the button again.  You will need to drag a corner of the
   window with the mouse to reduce the window size.



