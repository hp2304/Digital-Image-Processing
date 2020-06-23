for elements = 1:25
 B(elements) = input(['Enter value ' num2str(elements) ' : \n']);   % This loop will take all values of our matrix(5*5)
end

A = reshape(B,5,5); % Create a 5*5(A) matrix from 1*25(B) (Column wise)
A = [A; eye(5,5)];  % Connect 5*5 identity matrix in matrix A now A is 10*5
A = transpose(A);   % Make A 5*10 matrix
nRows = size(A,1);  % Find the number of rows
nCols = size(A,2);  % Find the number of columns
A                   % Print A

Main = A(1:nRows, 1:nRows);     % Store the original matrix in Main(5*5)

if det(Main)==0                 % Check if determinant of Main matrix is zero or not
   disp('Can not find the inverse because determinant of matrix is 0')
   
else 
    for j=1:nCols
        for i=1:nRows
            
            if i==j && A(i,j)==0
                for k=1:5          % This loop will switch the row which has zero at pivot positions.(Switch with other row below it)
                    if A(k,j)~=0 && k>i 
                        temp = A(i,:);
                        A(i,:) = A(k,:);
                        A(k,:) = temp;
                        break;
                    end
                end
            end
            
            if i==j && A(i,j) ~= 0          % It will generate 1 at pivot positions 
                A(i,:) = A(i,:) / A(i,j);
            end
            
            if i~=j && i>j                  % It will generate zeroes below pivot positions using row operations(Forward phase)
                A(i,:) = (-(A(i,j)/A(j,j))) * A(j,:) + A(i,:);
            end
            
        end
    end
    
    disp('Echelon form')
    A                                       % Print echelon form of A 
    
    for j=nRows:-1:1
        for i=nRows:-1:1                    % This loops will generate zeros above pivot positions using row operations(Backward phase)
           if A(i,j) ~= 0 && j>i
               A(i,:) = (-(A(i,j)/A(j,j))) * A(j,:) + A(i,:);
           end
        end
    end
    
    disp('Row reduced echelon form')
    A                                       % Print row reduced echelon form of A(5*10)
    
end