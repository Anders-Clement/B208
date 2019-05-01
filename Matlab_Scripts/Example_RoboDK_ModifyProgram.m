
clc
clear
close all

%% Section Retriving matrices from robodk

% Generate a Robolink object RDK. This object interfaces with RoboDK.
RDK = Robolink;

robot = RDK.Item('UR5');

% Get the library path
path = RDK.getParam('PATH_LIBRARY');

% Display a list of all items
% fprintf('Available items in the station:\n');
% disp(RDK.ItemList());
tooltop = RDK.Item('tooltop2');
matrices = cell(tooltop.InstructionCount(),1);
reference = RDK.Item('Reference SW');

tool = [     1.000000,     0.000000,     0.000000,     0.000000 ;
      0.000000,     1.0,    -0.0,   0.000000 ;
      0.000000,     0.0,     1.0,    100.000000 ;
      0.000000,     0.000000,     0.000000,     1.000000 ];

counter = 0;

for i = 1:tooltop.InstructionCount()
    [name, instype, movetype, isjointtarget, pose, joints] = tooltop.Instruction(i);
    if pose ~= -1 
        counter = counter + 1;
        matrices{counter} = reference.Pose()*pose;
    end
end

%% Section UR5 Forward Kinematics


%Lengths of links and distances:
d1 = 89.2;
a2 = -425;
a3 = -392.43;
d4 = 109;
d5 = 93.65;
d6 = 82;

%Forwards kinematics in symbolics

syms t1 t2 t3 t4 t5 t6

%Denavit Hartenberg parameters:
%  "alpha"   "a"     "d"        "theta"
Q=[0         ,0      ,d1        ,t1;
   pi/2      ,0      ,0         ,t2;
   0         ,a2     ,0         ,t3;
   0         ,a3     ,d4        ,t4;
   pi/2      ,0      ,d5        ,t5;
   -pi/2     ,0      ,d6        ,t6;
 ];

i = 1;
T01 = [cos(Q(i,4))                 ,-sin(Q(i,4))                   ,0                  ,Q(i,2);
    sin(Q(i,4))*cos(Q(i,1))     ,cos(Q(i,4))*cos(Q(i,1))        ,-sin(Q(i,1))       ,-sin(Q(i,1))*Q(i,3);
    sin(Q(i,4))*sin(Q(i,1))     ,cos(Q(i,4))*sin(Q(i,1))        ,cos(Q(i,1))        ,cos(Q(i,1))*Q(i,3);
    0                           ,0                              ,0                  ,1];

i = 2;
T12 = [cos(Q(i,4))                 ,-sin(Q(i,4))                   ,0                  ,Q(i,2);
    sin(Q(i,4))*cos(Q(i,1))     ,cos(Q(i,4))*cos(Q(i,1))        ,-sin(Q(i,1))       ,-sin(Q(i,1))*Q(i,3);
    sin(Q(i,4))*sin(Q(i,1))     ,cos(Q(i,4))*sin(Q(i,1))        ,cos(Q(i,1))        ,cos(Q(i,1))*Q(i,3);
    0                           ,0                              ,0                  ,1];
i = 3;

T23 = [cos(Q(i,4))                 ,-sin(Q(i,4))                   ,0                  ,Q(i,2);
    sin(Q(i,4))*cos(Q(i,1))     ,cos(Q(i,4))*cos(Q(i,1))        ,-sin(Q(i,1))       ,-sin(Q(i,1))*Q(i,3);
    sin(Q(i,4))*sin(Q(i,1))     ,cos(Q(i,4))*sin(Q(i,1))        ,cos(Q(i,1))        ,cos(Q(i,1))*Q(i,3);
    0                           ,0                              ,0                  ,1];

i = 4;
T34 = [cos(Q(i,4))                 ,-sin(Q(i,4))                   ,0                  ,Q(i,2);
    sin(Q(i,4))*cos(Q(i,1))     ,cos(Q(i,4))*cos(Q(i,1))        ,-sin(Q(i,1))       ,-sin(Q(i,1))*Q(i,3);
    sin(Q(i,4))*sin(Q(i,1))     ,cos(Q(i,4))*sin(Q(i,1))        ,cos(Q(i,1))        ,cos(Q(i,1))*Q(i,3);
    0                           ,0                              ,0                  ,1];

i = 5;
T45 = [cos(Q(i,4))                 ,-sin(Q(i,4))                   ,0                  ,Q(i,2);
    sin(Q(i,4))*cos(Q(i,1))     ,cos(Q(i,4))*cos(Q(i,1))        ,-sin(Q(i,1))       ,-sin(Q(i,1))*Q(i,3);
    sin(Q(i,4))*sin(Q(i,1))     ,cos(Q(i,4))*sin(Q(i,1))        ,cos(Q(i,1))        ,cos(Q(i,1))*Q(i,3);
    0                           ,0                              ,0                  ,1];

i = 6;
T56 = [cos(Q(i,4))                 ,-sin(Q(i,4))                   ,0                  ,Q(i,2);
    sin(Q(i,4))*cos(Q(i,1))     ,cos(Q(i,4))*cos(Q(i,1))        ,-sin(Q(i,1))       ,-sin(Q(i,1))*Q(i,3);
    sin(Q(i,4))*sin(Q(i,1))     ,cos(Q(i,4))*sin(Q(i,1))        ,cos(Q(i,1))        ,cos(Q(i,1))*Q(i,3);
    0                           ,0                              ,0                  ,1];


clearvars i;
%% Section calculation the join angles

Angles = cell(counter);

for i = 1:counter
    T06 = matrices{i} * inv(tool);
    
    %Calculating P05 in order to calculate theta1:
    P05 = T06*[0; 0; -d6; 1];
    t1 = atan2(P05(2), P05(1)) + acos(d4/( sqrt(P05(1)^2 + P05(2)^2) )) + pi/2;

    %P06 is simply the position vector from our T06, that is, the 4th column:
    P06 = T06(:,4);
    t5 =  -acos((P06(1)*sin(t1) - P06(2)*cos(t1) - d4) /d6 );

    %Find T60, so we can describe Y60 and X60:
    T60 = inv(T06);
    Y60 = T60(:,2);
    X60 = T60(:,1);
    
    atanTop = ( -X60(2)*sin(t1) + Y60(2)*cos(t1)) /sin(t5);
    atanBottom = (X60(1)*sin(t1)-Y60(1)*cos(t1))/sin(t5);
    
    if and(isreal(atanTop), isreal(atanBottom))
        t6 = atan2(atanTop, atanBottom );
    else
        t6 = deg2rad(180);
    end

    %We need T14 for t3, calculate with known thetas, and symbolic
    %transformation matrices:
    T16 = inv(T01)*T06;
    T65 = inv(T56);
    T54 = inv(T45);
    T14 = eval(T16*T65*T54);

    %Also need the norm of the vector from frame 1 to 4, in the xz plane:
    nP14xz = sqrt(T14(1,4)^2 + T14(3,4)^2);

    t3 = acos( (nP14xz^2 - a2^2 - a3^2) / (2*a2*a3) );
    
    atan2Top = (-T14(3,4));
    atan2Bottom = (-T14(1,4));
    
    if and(isreal(atan2Top), isreal(atan2Bottom))
        t2 = atan2(atan2Top, atan2Bottom) - asin( (-a3*sin(t3)) / (nP14xz));
    else
        t2 = atan(atan2Top / atan2Bottom) -asin( (-a3*sin(t3)) / (nP14xz));
    end

    %For t4, T34 is needed, which can be calculated from now known thetas 
    %and symbolic transformation matrices:
    T30 = eval(inv(T23) * inv(T12) * inv(T01));
    T04 = T06*eval(inv(T56)*inv(T45));
    newT34 = T30*T04;
    t4 = atan2(newT34(2,1), newT34(1,1));
    
    Angles{i} = rad2deg([t1 t2 t3 t4 t5 t6]);
    
%     X = ['Thetas from inv. kin, t1: ', num2str(rad2deg(t1)), ' t2: ', num2str(rad2deg(t2)), ' t3: ', num2str(rad2deg(t3)), ' t4: ', num2str(rad2deg(t4)), ' t5: ', num2str(rad2deg(t5)), ' t6: ', num2str(rad2deg(t6))];
%     disp(X)
end

%% Section 
for i=1:counter
    robot.MoveJ(Angles{i});
end
