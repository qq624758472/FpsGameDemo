#下载dockerhub镜像


#从镜像启动容器
docker run -v /home/hao/my_work/Learning_set/server_model/c++/FpsServer/server:/server -p 3306:3306 -p 4399:4399  -it qq624758472/ubuntu:v0.0.2 /bin/bash
