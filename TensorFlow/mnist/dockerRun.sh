docker run -di \
--mount type=bind,source=/etc/localtime,target=/etc/localtime,readonly \
--mount type=bind,source=/etc/apt/sources.list,target=/etc/apt/sources.list,readonly \
--mount type=bind,source=/home/hzx/srcDir,target=/home/srcDir \
tensorflow/tensorflow bash