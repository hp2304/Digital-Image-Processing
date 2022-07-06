function [ output ] = omega_func( N, k, n )
    output = exp(-(j*2*pi*n*k)/(N));
end

