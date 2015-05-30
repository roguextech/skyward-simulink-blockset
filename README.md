# skyward-simulink-blockset

This repository contains the Simulink blockset for the GY-88 IMU


# INSTALLATION INSTRUCTIONS
# 

# Linux 

* Make sure to have GCC installed (sudo apt-get install gcc g++)
* From MATLAB command window run mex -setup (this will configure the mex compiler)
* Run skywardconfigurescript.m
* Refresh Simulink library browser

# Windows

* From Add/Remove programs uninstall "Microsoft Visual C++ 2010 Redistributable" both x86 and x64 version
* Download and install the Windows 7 SDK, make sure to select "Microsoft Visual C++ Compiler" during the setup process
* From MATLAB command line run mex -setup, you should see "MATLAB configured to use Microsoft Visual C++ Compiler"
* Run skywardconfigurescript.m
* Refresh Simulink library browser
* 
# OS X

* Currently not tested

# NOTES  

* You MUST have MATLAB R2015a with Arduino support package installed !
* When you want to test your algorithm and schemas, make sure to set simulation mode to "External", then click the play button
* When you want to deploy your algorithm to the board, just push the deploy button. Make sure to select Arduino Mega 2560 board from model options, and to set model to fixed-step/discrete

# F.A.Q



