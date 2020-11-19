function [angularVels] = fromTorqueToAngularVels(torques,armLength, kT, kQ) %#codegen
    torqueConstant = (armLength / sqrt(2)) * kT;
    
    forwardKinematics = [   torqueConstant -torqueConstant -torqueConstant  torqueConstant;
                            torqueConstant  torqueConstant  -torqueConstant -torqueConstant;
                            -kQ             kQ              -kQ             kQ;
                            kT              kT              kT              kT];
     
    angularVelsSquared = pinv(forwardKinematics) * torques;
    angularVelsSquared(angularVelsSquared < 0) = 0;
    angularVels = sqrt(angularVelsSquared);
end