x = videoinput('winvideo',1);
xinfo = imaqhwinfo(x);
for i=1:10
    img = getsnapshot(x);
    fname = ['Image' num2str(i)];
    imwrite(img,fname,'jpg');
    pause(2);
end