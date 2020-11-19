
kT = single(0.01);
kQ = single(7.8263 * 10 ^(-4));
armLength = single(0.062);
torques = single([0.0; 0.0; 0.0; 0.0]);

angularVels = fromTorqueToAngularVels(torques, armLength, kT, kQ);

disp(angularVels);