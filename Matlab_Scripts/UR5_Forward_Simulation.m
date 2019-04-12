%RMMS Topic 6
clc;    % clears screen
clear;  % clear workspace
close all;  % close all figures

%% UR 5 Kinematics

%Exercise 1a
L1 = 425;
L2 = 392.430;

D1 = 89.200;
D4 = 109.00;
D5 = 93.65;
D6 = 82.00;

L(1) = Link('alpha',0,              'a',0,      'd',D1,'modified');    %rotational
L(2) = Link('alpha',deg2rad(90),    'a',0,      'd',0,'modified');   %rotational
L(3) = Link('alpha',0,              'a',-L1,    'd',0,'modified');
L(4) = Link('alpha',0,              'a',-L2,    'd',D4,'modified');
L(5) = Link('alpha',deg2rad(90),    'a',0,      'd',D5,'modified');
L(6) = Link('alpha',-deg2rad(90),   'a',0,      'd',D6,'modified');

UR=SerialLink(L,'name','UR10');

UR.plotopt = {'workspace',[ -1000, 1000, -1000, 1000, -1000, 1000]};

UR.teach();


