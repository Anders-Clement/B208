
clc
clear
close all

%% Connection to the robot

% Get the robot ip from the teach pendant: File -> About
robot_ip = '192.168.0.79';

sock = tcpip(robot_ip, 30000, 'NetworkRole', 'server');
fclose(sock);
disp('Press Play on robot');
fopen(sock);
disp('Connected!');

%% Section Retriving matrices from robodk

% Generate a Robolink object RDK. This object interfaces with RoboDK.
RDK = Robolink;

robot = RDK.Item('UR5');

% Display a list of all items
% fprintf('Available items in the station:\n');
% disp(RDK.ItemList());
tooltop = RDK.Item('tooltop2');
reference = RDK.Item('Reference SW').Pose();
table = RDK.Item('Table Reference').Pose();

tool = [    1.000000,     0.000000,     0.000000,     0.000000 ;
            0.000000,     1.000000,     0.0,          0.000000 ;
            0.000000,     0.000000,     1.0,         95.000000 ;
            0.000000,     0.000000,     0.000000,     1.000000 ];


counter = 0;
PosZYX = zeros(100,6);

for i = 1:tooltop.InstructionCount()
    [name, instype, movetype, isjointtarget, pose, joints] = tooltop.Instruction(i);
    if pose ~= -1 
        counter = counter + 1;
        matrix = table*reference*pose;
        temp(1,1:3) = matrix(1:3,4).';
        temp(1,4:6) = tr2rpy(matrix, 'zyx');
        PosZYX(counter,:) = temp(1,:);
        %robot.MoveL(matrix)
    end
end

%%

for indexs = 1:length(PosZYX)
   if PosZYX(indexs,4) < 0
       PosZYX(indexs,4) = PosZYX(indexs,4) + 2*pi;
   end
   if PosZYX(indexs,5) < 0
        PosZYX(indexs,5) = PosZYX(indexs,5) + 2*pi;
   end
   if PosZYX(indexs,6) < 0
        PosZYX(indexs,6) = PosZYX(indexs,6) + 2*pi;
   end
end

%% Section Trajectories generation.
res = 0.1;
movementSpeed = 50; % mm/sec

variables = cell(counter, 4);
time = [0  0;
        0  0; ];
accumTime = 0;

for i=1:counter-1
    
    TB1C = PosZYX(i,:);
    TB2C = PosZYX(i+1,:);
    
    lengths = sqrt( (TB2C(1) - TB1C(1))^2 + (TB2C(2) - TB1C(2))^2 + (TB2C(3) - TB1C(3))^2 );
    
    tf = lengths / movementSpeed; %tf is the time, whichs is the length / ( mm / sec )

    a1 = TB1C;
    a2 = zeros(size(TB1C));
    a3 = 3/tf^2*(TB2C-TB1C);
    a4 = -2/tf^3*(TB2C-TB1C);
    
    variables{i,1} = a1;
    variables{i,2} = a2;
    variables{i,3} = a3;
    variables{i,4} = a4;
    
    time(i,1) = tf;
    accumTime = accumTime + tf;
    time(i,2) = accumTime;
end

%% Testing times

clearvars a1 a2 a3 a4;

values = 1:res:accumTime;
Trans = cell(length(values), 1);
counter = 1;
cords(1,1:6) = [1; 2; 3; 4; 5; 6];
valuesTemp = values.';

for i=1:length(values)
    
    for j=1:size(time,1)
        
        if values(i) < time(j,2)
            
            if j == 1
                timeIntoPeriode = values(i);
            else
                timeIntoPeriode = (values(i) - time(j-1,2) );
            end
            
            if time(j,1) < timeIntoPeriode
                time(j-1,2)
                values(i)
                timeIntoPeriode
            end
           
            a1 = variables{j,1};
            a2 = variables{j,2};
            a3 = variables{j,3};
            a4 = variables{j,4};
            
            cords(counter, 1:6) = a1 + a2*timeIntoPeriode + a3*timeIntoPeriode^2 + a4*timeIntoPeriode^3;
            counter = counter + 1;
            break;
        end
    end
end

plot(valuesTemp,cords(:,4:6))

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

Angles = cell(counter,1);
ToolInv = inv(tool);
hold on;

for i = 1:counter-1
    pos = cords(i,1:3);
    R1 = rotz(cords(i,4)) * roty(cords(i,5)) * rotx(cords(i,6));
    R1(1:3,4) = pos.';
    R1(4,1:4) = [ 0 0 0 1];
    T06 = R1 * ToolInv;
    
    %trplot(R1);
    
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
        continue;
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
        continue;
    end

    %For t4, T34 is needed, which can be calculated from now known thetas 
    %and symbolic transformation matrices:
    T30 = eval(inv(T23) * inv(T12) * inv(T01));
    T04 = T06*eval(inv(T56)*inv(T45));
    newT34 = T30*T04;
    
    if and(isreal(newT34(2,1)), isreal(newT34(1,1)))
        t4 = atan2(newT34(2,1), newT34(1,1));
    else
        continue;
    end
        
    %robot.MoveL(rad2deg([t1 t2 t3 t4 t5 t6]));
    
    Angles{i,1} = [t1 t2 t3 t4 t5 t6];
end

%% Sending the positions to the robot.
hold on

plotMatrix = [];

for idx=1 : length(values)
   AnglesTemp = Angles{idx,1};
   if length(AnglesTemp) == 0
       continue
   end
   plotMatrix(idx,:) = rad2deg(AnglesTemp);
end

plot(valuesTemp,plotMatrix)
