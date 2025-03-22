clear;close all;


a1=220/100; a2=7.5/100; a3=(65.5+130)/100; a4=30/100; %[mm]

link1 = rigidBody("link1");
link1.Joint = rigidBodyJoint("joint1","revolute");
link1.Joint.setFixedTransform([0 pi/2 0 0],"dh");
link1.Joint.HomePosition=0;

link2 = rigidBody("link2");
link2.Joint = rigidBodyJoint("joint2","revolute");
link2.Joint.setFixedTransform([a1 0 0 0],"dh");
link2.Joint.HomePosition=pi/2;
link2.Joint.PositionLimits=deg2rad([-230/2 +230/2]);

link3 = rigidBody("link3");
link3.Joint = rigidBodyJoint("joint3","revolute");
link3.Joint.setFixedTransform([0 pi/2 a2 0],"dh");
link3.Joint.HomePosition=deg2rad(-43);
link3.Joint.PositionLimits=deg2rad([-270/2 +270/2]);

link4 = rigidBody("link4");
link4.Joint = rigidBodyJoint("joint4","revolute");
link4.Joint.setFixedTransform([0 -pi/2 a3 0],"dh");
link4.Joint.PositionLimits=deg2rad([-270/2 +270/2]);

link5 = rigidBody("link5");
link5.Joint = rigidBodyJoint("joint5","revolute");
link5.Joint.setFixedTransform([0 pi/2 0 0],"dh");
link5.Joint.PositionLimits=deg2rad([-180/2 +180/2]);

link6 = rigidBody("end_eff");
link6.Joint = rigidBodyJoint("end_eff","fixed");
link6.Joint.setFixedTransform([0 0 a4 0],"dh");

myRobot = rigidBodyTree(DataFormat="row");

myRobot.addBody(link1,myRobot.BaseName);
myRobot.addBody(link2,link1.Name);
myRobot.addBody(link3,link2.Name);
myRobot.addBody(link4,link3.Name);
myRobot.addBody(link5,link4.Name);
myRobot.addBody(link6, link5.Name);

myRobot.homeConfiguration
myRobot.showdetails

figure(1);
myRobot.show(myRobot.homeConfiguration);

ik = inverseKinematics('RigidBodyTree',myRobot,'SolverAlgorithm','LevenbergMarquardt');

ikWeights = [0 0 0 1 1 1]; % [orientation_weight, position_weight]

desiredPosition = trvec2tform([-1.19, 0.077, 1.602]); %  position example

[configSol, solInfo]= ik("end_eff", desiredPosition, ikWeights, myRobot.homeConfiguration );

figure(2)
myRobot.show(configSol);
