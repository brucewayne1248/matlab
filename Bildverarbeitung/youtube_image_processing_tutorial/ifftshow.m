function [ ] = ifftshow( f )
%T17_IFFTSHOW Summary of this function goes here
%   Detailed explanation goes here
f1 = abs(f);
fm = max(f1(:));
figure, imshow(f1/fm);
end

