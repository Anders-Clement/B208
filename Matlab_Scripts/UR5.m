clear;

%Lengths of links and distances:
d1 = 89.159;
a2 = -425;
a3 = -392.25;
d4 = 109.15;
d5 = 94.65;
d6 = 82.3;

%Build the arm, using our DH-parameters:
Rev1 = RevoluteMDH('a', 0, 'alpha', 0, 'd', d1);
Rev2 = RevoluteMDH('a', 0, 'alpha', 1.570796327, 'd',0);
Rev3 = RevoluteMDH('a', a2, 'alpha', 0, 'd',0);
Rev4 = RevoluteMDH('a', a3, 'alpha', 0, 'd',d4);
Rev5 = RevoluteMDH('a', 0, 'alpha', 1.570796327, 'd',d5);
Rev6 = RevoluteMDH('a', 0, 'alpha', -1.570796327, 'd',d6);
%Putting them all together:
Arm = SerialLink(Rev1 + Rev2 + Rev3 + Rev4 + Rev5 + Rev6, 'name', 'UR5');
%And show it:
Arm.teach();


%%
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

% Make and save the transformation matrices between each frame, using the
% DH parameters which are saved in Q. i is used to access different rows of
% Q
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

 T06_symb = T01*T12*T23*T34*T45*T56
% T06 can be evaluated when t1...t6 are defined, which gives the forwards
% kinematics
% T06 is overwritten in the next section and used as the goal...


%%
    
%This is our goal, i.e. chosen end-effector position:
% alpha, beta, gamma and x,y,z can be changed to get a certain end
% position:

alpha = deg2rad(-15);
beta = deg2rad(30);
gamma = deg2rad(-16);
x = -219.95;
y = 17.315;
z = 9.92;

%rot = rotx(alpha)*roty(beta)*rotz(gamma);
rot = rpy2r(alpha,beta,gamma);
trans = [x;y;z];

T06 = [rot trans;
        0, 0, 0, 1]


%%

t1 = deg2rad(115);
t2 = deg2rad(-28.57);
t3 = deg2rad(-32.31);
t4 = deg2rad(-74.06);
t5 = deg2rad(34.95);
t6 = deg2rad(23.87);

tmp = eval(T06_symb)
%%

%Calculating P05 in order to calculate theta1:
P05 = T06*[0; 0; -d6; 1];
t1 = atan2(P05(2), P05(1)) - acos(d4/( sqrt(P05(1)^2 + P05(2)^2) )) + pi/2;

%P06 is simply the position vector from our T06, that is, the 4th column:
P06 = T06(:,4);
t5 =  acos((P06(1)*sin(t1) - P06(2)*cos(t1) - d4) /d6 );

%Find T60, so we can describe Y60 and X60:
T60 = inv(T06);
Y60 = T60(:,2);
X60 = T60(:,1);
t6 = atan2(( -X60(2)*sin(t1) + Y60(2)*cos(t1)) /sin(t5), (X60(1)*sin(t1)-Y60(1)*cos(t1))/sin(t5));

%We need T14 for t3, calculate with known thetas, and symbolic
%transformation matrices:
T16 = inv(T01)*T06;
T65 = inv(T56);
T54 = inv(T45);
T14 = eval(T16*T65*T54);

%Also need the norm of the vector from frame 1 to 4, in the xz plane:
nP14xz = sqrt(T14(1,4)^2 + T14(3,4)^2);

t3 = -acos( (nP14xz^2 - a2^2 - a3^2) / (2*a2*a3) );
t2 = atan2(-T14(3,4),-T14(1,4)) - asin( (-a3*sin(t3)) / (nP14xz));

%For t4, T34 is needed, which can be calculated from now known thetas 
%and symbolic transformation matrices:
T30 = eval(inv(T23) * inv(T12) * inv(T01));
T04 = T06*eval(inv(T56)*inv(T45));
newT34 = T30*T04;
t4 = atan2(newT34(2,1), newT34(1,1));

%Display result in a nice manner, courtesy of Hans (Who probably stole it
%somewhere :p )
X = ['Thetas from inv. kin, t1: ', num2str(rad2deg(t1)), ' t2: ', num2str(rad2deg(t2)), ' t3: ', num2str(rad2deg(t3)), ' t4: ', num2str(rad2deg(t4)), ' t5: ', num2str(rad2deg(t5)), ' t6: ', num2str(rad2deg(t6))];
disp(X)
tmp = tr2rpy(T06);
rot_in_degrees = rad2deg(tmp)
%use the earlier derived forwards kinematics to check if the thetas from
%the inverse kinematics give the goal back as a result:
q = [t1 t2 t3 t4 t5 t6];
forward_from_inverse = fkine(Arm, q)

