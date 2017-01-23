function [ bw_filter ] = manualPreFilter2( bw, ymin, ymax, xmin, xmax )
%MANUALPREFILTER sets all pixels to 0 in binary image except for given
%range
[rows, col] = size(bw);

for k = 1:rows
    for kk = 1:col
        if ( k >= ymin & k <= ymax & kk >= xmin & kk <= xmax )
            bw_filter(k,kk) = bw(k,kk);
        else
            bw_filter(k,kk) = 0;
        end
    end
end

end

