function [ bw ] = manualPreFilter( bw, ymin, ymax, xmin, xmax )
%MANUALPREFILTER sets pixels in binary image to 0 within given pixel ranges
[rows, col] = size(bw);

for k = ymin:ymax
    for kk = xmin:xmax
    bw(k,kk)=0;
    end
end

end

