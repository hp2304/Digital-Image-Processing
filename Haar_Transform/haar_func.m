function [ out ] = haar_func( p, n, t )
    for i=1:length(t)
        if t(i)>=(n/(2^p)) && t(i)<((n+.5)/(2^p))
            out(i) = (2^p)^.5;
        elseif t(i)>=((n+.5)/(2^p)) && t(i)<((n+1)/(2^p))  
            out(i) = -(2^p)^.5;
        else
            out(i) = 0;
        end
    end
end

