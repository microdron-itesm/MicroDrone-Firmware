function out = ProcessIMU(data, zero)
    out = quatnormalize(quatmultiply(quatinv(zero), data));
end