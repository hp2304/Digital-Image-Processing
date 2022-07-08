A = [[1 2 2 1 0 0]; [4 5 6 0 1 0]; [7 8 9 0 0 1]]

disp('Input your path one number at a time');

for nn = 1:9
 x(nn) = input(['Enter number ' num2str(nn) '\n']);
end

x = reshape(x,3,3);
x = [x; eye(3,3)];
x = transpose(x);
nRows = size(x,1);
nCols = size(x,2);
x
if det(x)==0
   fprintf('Cant find the inverse because determinant of matrix is 0'); 
else 
     for i = 1:nRows
         for j = 1:nCols
             if i==1 && j==1 
                 if x(i,j) == 0
                     if i == 1 AND j == 1
                        if x(2,1)~=0
                            B = x(1,:);
                            x(1,:) = x(2,:);
                            x(2,:) = B;
                        else
                            B = x(1,:);
                            x(1,:) = x(3,:);
                            x(3,:) = B;
                        end
                     end
                 end 
                 x(2,:) = (-(x(2,1)/x(1,1))) * x(1,:) + x(2,:);
                 x(3,:) = (-(x(3,1)/x(1,1))) * x(1,:) + x(3,:);
             end
             if i==2 && j==2 
                 if x(i,j) == 0  
                   B = x(2,:);
                   x(2,:) = x(3,:);
                   x(3,:) = B;
                 end 
                 x(3,:) = (-(x(3,2)/x(2,2))) * x(2,:) + x(3,:); 
             end
         end
     end
     for i = 1:3
       if x(i,i) ~= 0
            x(i,:) = x(i,:)/x(i,i);
       end    
     end
     x
end


%{
    if A(1:1)==0
       B = A(1,:);
       A(1,:) = A(3,:);
       A(3,:) = B;

    else
       A(2,:) = (-(A(2,1)/A(1,1))) * A(1,:) + A(2,:);
       A(3,:) = (-(A(3,1)/A(1,1))) * A(1,:) + A(3,:);
    end

 A 
if A(2,2)==0
   B = A(2,:);
   A(2,:) = A(3,:);
   A(3,:) = B;
   
else
   A(3,:) = (-(A(3,2)/A(2,2))) * A(2,:) + A(3,:); 
end
A

for i = 1:3
   if A(i,i) ~= 0
        A(i,:) = A(i,:)/A(i,i);
   end    
end
A
%}