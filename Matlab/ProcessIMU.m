function out = ProcessIMU(data, zero)
    out = quatmultiply(data, quatinv(zero));
end