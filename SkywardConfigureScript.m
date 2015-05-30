% Author: Francescodario Cuzzocrea
% Email: francescodario.cuzzocrea@skywarder.eu

%% SKYWARD CONFIGURE SCRIPT

% Just run the script and it will install the Simulink library

ProjDir = pwd;
disp('Adding Current Path to MATLAB path three...');
addpath(ProjDir,[ProjDir,'\blocks']);
savepath;
disp('Building Skyward blocks');

cd ([ProjDir,'\blocks\GY-88']);
        mex 'GY_88.c' 'GY_88_wrapper.cpp'
        

% Complete Compilation
cd (ProjDir);
disp('Adding Skyward Blockset Simulink...');

slxFile = 'swblockset'; 
load_system(slxFile);
set_param(slxFile,'Lock','off');   
set_param(slxFile,'EnableLBRepository','on');  
save_system(slxFile);

disp('Setup Complete ! Happy Hacking :D');
clear all
