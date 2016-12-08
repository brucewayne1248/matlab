info = imaqhwinfo('winvideo');
dev_info = info.DeviceInfo.SupportedFormats;
vid  = videoinput('winvideo',1);
