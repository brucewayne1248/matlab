%% Reading video
v = VideoReader('dp1.mp4');
while hasFrame(v)
    video = readFrame(v);
end
whos video
%%
vidWidth = v.Width;
vidHeight = v.Height;
%%
mov = struct('cdata',zeros(vidHeight, vidWidth,3,'uint8'),'colormap',[]);

%%