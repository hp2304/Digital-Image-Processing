function [u,s,v] = my_svd(inp)
    u = zeros(size(inp,1), size(inp,1));
    v = zeros(size(inp,2), size(inp,2));
    s = zeros(size(inp));
    sq_inp = (inp')*inp;
    syms lambda;
    %eq = det(sq_inp - lambda.*eye(size(sq_inp)));
    eq = charpoly(sq_inp, lambda);
    coeff_vec = coeffs(eq);
    coeff_vec = [coeff_vec, zeros(1,size(inp,2)+1-size(coeff_vec, 2))];
    eigen_vals = roots(coeff_vec);
    eigen_vals = 1./eigen_vals;
    eigen_vals(~isfinite(eigen_vals))=0;
    eigen_vals = double(eigen_vals);
    eigen_vals = sort(eigen_vals, 'descend');
    eigen_vals = real(eigen_vals);
    temp_s = diag(eigen_vals).^(0.5);
    num_nonzero_vals = rank(inp);

    for i=1:num_nonzero_vals
        s(i,i) = temp_s(i,i);
    end
    clear i;
    for i=1:num_nonzero_vals
        v(:,i) = null(sq_inp - (eigen_vals(i).*eye(size(inp,2), size(inp,2))));
        v(:,i) = v(:,i) / norm(v(:,i));
    end
    if num_nonzero_vals<size(inp,2)
        null_inp = null(inp);
        v(:,num_nonzero_vals+1:size(inp, 2)) = null_inp(:,1:size(inp, 2)-num_nonzero_vals);
    end

    for j=1:num_nonzero_vals
        u(:,j) = (1/s(j,j)).*(inp*v(:,j));
    end
    if num_nonzero_vals<size(inp,1)
        null_u = null(u(:,1:num_nonzero_vals)');
        u(:,num_nonzero_vals+1:size(inp, 1)) = null_u(:,1:size(inp, 1)-num_nonzero_vals);
    end
    u = real(u);
    v = real(v);
end