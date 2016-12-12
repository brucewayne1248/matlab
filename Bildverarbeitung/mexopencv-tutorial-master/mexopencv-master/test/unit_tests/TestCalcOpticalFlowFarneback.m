classdef TestCalcOpticalFlowFarneback
    %TestCalcOpticalFlowFarneback

    properties (Constant)
        im = 255*uint8([...
            0 0 0 0 0 0 0 0 0 0;...
            0 0 0 0 0 0 0 0 0 0;...
            0 0 0 0 0 0 0 0 0 0;...
            0 0 0 1 1 1 0 0 0 0;...
            0 0 0 1 0 1 0 0 0 0;...
            0 0 0 1 1 1 0 0 0 0;...
            0 0 0 0 0 0 0 0 0 0;...
            0 0 0 0 0 0 0 0 0 0;...
            0 0 0 0 0 0 0 0 0 0;...
            0 0 0 0 0 0 0 0 0 0;...
        ]);
    end

    methods (Static)
        function test_1
            im1 = TestCalcOpticalFlowFarneback.im;
            im2 = circshift(im1, [0 1]);
            flow = cv.calcOpticalFlowFarneback(im1, im2);
            validateattributes(flow, {'single'}, ...
                {'3d', 'size',[size(im1,1) size(im1,2) 2]});
        end

        function test_2
            prevImg = cv.imread(fullfile(mexopencv.root(),'test','RubberWhale1.png'), 'Grayscale',true);
            nextImg = cv.imread(fullfile(mexopencv.root(),'test','RubberWhale2.png'), 'Grayscale',true);
            flow = cv.calcOpticalFlowFarneback(prevImg, nextImg);
            validateattributes(flow, {'single'}, ...
                {'3d', 'size',[size(prevImg,1) size(prevImg,2) 2]});
        end

        function test_error_argnum
            try
                cv.calcOpticalFlowFarneback();
                throw('UnitTest:Fail');
            catch e
                assert(strcmp(e.identifier,'mexopencv:error'));
            end
        end
    end

end
