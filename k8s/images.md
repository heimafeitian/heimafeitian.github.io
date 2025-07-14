
制作镜像
Dockerfile

make

容器网络

https://blog.51cto.com/namesam/1907472


容器中不能使用systemctl
https://blog.csdn.net/yao00037/article/details/122688115

http://www.manongjc.com/detail/62-ljioxaeimoonuck.html


安装grafana

https://grafana.com/grafana/download
http://www.manongjc.com/detail/62-ljioxaeimoonuck.html
https://cloud.tencent.com/developer/article/1990741

wget https://dl.grafana.com/enterprise/release/grafana-enterprise-9.3.2.linux-amd64.tar.gz


# 安装支持库
yum install nss atk  libatk-bridge-2.0.so.0 at-spi2-atk cups-libs libdrm libXcomposite libXdamage mesa-libgbm libpango-1.0.so.0  pango alsa-lib libxshmfence

#安装
grafana-cli plugins install grafana-image-renderer

#重启服务
systemctl restart grafana-server


systemctl status grafana-server

安装mysql

https://www.cnblogs.com/minqiliang/archive/2022/08/11/16577102.html
https://blog.csdn.net/qq_21361773/article/details/125829452

[root@iZuf6hx48jsavuzwp5hv7jZ soft]# /bin/systemctl start mysqld.service//启动命令
[root@iZuf6hx48jsavuzwp5hv7jZ soft]# service mysqld status //


[root@432ac968f521 grafana]# grep 'temporary password' /var/log/mysqld.log
2023-05-21T23:38:59.135721Z 6 [Note] [MY-010454] [Server] A temporary password is generated for root@localhost: mrvwTC3&hA3O


systemctl status mysqld.service


运行容器打包成镜像


https://blog.csdn.net/Done_for_me/article/details/129788536
https://www.jianshu.com/p/d6de22d91879


[root@dcpae-centos-64-jack centos-grafana]# docker ps
CONTAINER ID   IMAGE                     COMMAND                  CREATED        STATUS        PORTS                                       NAMES
432ac968f521   grafana-centos:latest     "/usr/sbin/init"         2 hours ago    Up 2 hours                                                clever_noether
e0cd0d8ecc98   registry:2                "/entrypoint.sh /etc…"   23 hours ago   Up 23 hours   0.0.0.0:5000->5000/tcp, :::5000->5000/tcp   my-registry
e5806e6de93a   centos                    "/usr/sbin/init"         24 hours ago   Up 24 hours   0.0.0.0:2060->22/tcp, :::2060->22/tcp       centos8
9bcba430eb61   adevur/centos-8:systemd   "/sbin/init"             25 hours ago   Up 25 hours                                               my-container




docker commit -a "mjy" -m "creat a new docker centos-grafana image by mjy" 432ac968f521 centos8-grafana:v1.0

[root@dcpae-centos-64-jack centos-grafana]# docker images
REPOSITORY                      TAG       IMAGE ID       CREATED          SIZE
centos8-grafana                 v1.0      bf45dff93f2b   13 seconds ago   2.54GB/usr/sbin/init
grafana-centos                  0.0.3     405bfaf3c1a1   22 hours ago     730MB
grafana-centos                  latest    405bfaf3c1a1   22 hours ago     730MB
localhost:5000/grafana-centos   latest    405bfaf3c1a1   22 hours ago     730MB
registry                        2         65f3b3441f04   10 days ago      24MB
hello-world                     latest    9c7a54a9a43c   2 weeks ago      13.3kB
centos                          latest    5d0da3dc9764   20 months ago    231MB
adevur/centos-8                 systemd   553f1bf2bb8e   3 years ago      219MB
adevur/centos-8                 latest    cdb604a057ab   3 years ago      219MB


docker save -o centos8-grafana.tar centos8-grafana:v1.0


docker load -i centos8-grafana.tar


docker run --name centos8-grafana-test --privileged --network=host -itd    centos8-grafana:v1.0   /usr/sbin/init


docker exec -it 8e6d5c3eb082 /bin/bash


docker exec -it e9e4b2f35909 /bin/bash

