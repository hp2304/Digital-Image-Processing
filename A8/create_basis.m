function [ basis_mat ] = create_basis( num_samples )
    basis_mat = zeros(num_samples, num_samples);
    for n = 1:num_samples
        for k = 1:num_samples
            basis_mat(n, k) = omega_func(num_samples, (n-1), (k-1));
        end
    end
    basis_mat = (1/(num_samples^.5)).*basis_mat;
end

