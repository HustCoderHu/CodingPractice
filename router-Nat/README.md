# linux 认证代理
使用linux iptables的nat 功能，实现一台设备认证，其他设备路由方式接入网络。
以HUST校园网为例，在一台linux系统里通过锐捷客户端认证之后，其他设备设置静态ip，并网关设置为linux虚拟机的ip，即可接入互联网。类似的解决方案有：刷好锐捷的路由器，淘宝有售。

标签：linux iptables NAT 路由 子网卡
# keyword：linux, iptables, NAT, 路由, 子网卡
---

- [1 NAT](#nat)
- [1.1 linux NAT](#ip转发)
- [1.2 清空iptables规则](#清空iptables规则)
- [1.3 设置NAT](#设置nat)
- [1.4 单网卡实现](#单网卡实现)
- [2 配置windows](#配置windows)
- [3 路由机主从热备](#主从热备)

# NAT
文件**408router-singleNIC**包含了将linux变成路由器(IPv4)需要的命令，
文件头部有chkconfig需要的前缀，在centos7上测试通过，debian系注意。
## IP转发
```
echo 1 > /proc/sys/net/ipv4/ip_forward
```
## 清空iptables规则
如果有自定义规则，请注意保留
```
service iptables restart
iptables -P INPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -P OUTPUT ACCEPT
iptables -F
```
## 设置NAT
从其他网卡(除IFNAME之外的)，进入系统的package会被替换源地址为IFNAME的地址，然后从IFNAME转发出去，详细原理请自行查阅iptables nat的资料
```
iptables -t nat -A POSTROUTING -o ${IFNAME} -j MASQUERADE
```
## 单网卡实现
虚拟机里测试的时候可以添加额外的网卡，一个网卡认证(WAN)，另一个网卡接收局域网数据(LAN)，就像路由器的WAN和LAN一样。
本人遇到的情况是可以用独立的台式机搭这个router，但是台式机只有一块网卡。找到的解决办法就是子网卡。可以暂时理解为虚拟出来的一块网卡，具体原理请自行查阅资料。
=-=-=-=-=-=-=-=-=-=-=-=-
ifconfig可看到形如 IFNAME:1 的设备，可以类似通过文件配置网卡静态IP的方式(ifcfg-enp1s0_1)，在 /etc/sysconfig/network-scripts目录下添加ip配置
注意文件名设备名都是带有分号的，这个子网卡作为LAN端，其他设备接入时手动分配ip，并制定WAN卡IP为网关。
逻辑上数据包从 `IFNAME:1` 进入linux，被NAT后从IFNAME流出linux，物理上就是从网卡进再出来进入Internet

**单网卡不能启动DHCPserver的原因** : 而且路由器的WAN和LAN连接的设备是分处不同的网路，所以LAN上可以启动DHCPserver。上述情况因为只有一个物理网卡，在这个子网卡上启动DHCPserver，DHCPserver直接出现在WAN网络里，干扰其他人接入网络，表现为断网。

# 配置windows
使用文件dhcp_staticIP.bat

# 主从热备
碰到过几次系统挂了导致实验室同学无法联网的情况，周末在家里看分布式的书时想到或许可以搞个备份机。不过和常规的应用层主从热备有几点
- 备份内容是ip
  > `IFNAME:1`的ip， 也就是接入逻辑LAN的其他机器需要设置的网关ip
- 上线检测
  > 同一局域网里不能有两个相同的ip

## 设计思路

- 1 上线时持有和网关ip同一网络的某个特殊ip `B`
  > 上线时可能已经有个主机在正常工作，这时当前机器就是备份机，开始 2
- 2 备份机定时向主机发送icmp包，主机接到后响应
  > 也可以自己定义一套简单的基于tcp的通信协议，不过服务端的响应代码要自己写
- 3 超过指定时间没有收到相应就认定主机 fail，把自己升级为主
  > 超时时间可以设置长一点，避免意外情况  
  升级为主具体来说，就是启动锐捷接入校园网，接入成功(比如ping下baidu)之后，给网关分配 `IFNAME:1`的ip

实现上推荐 python

## 场景分析
目前的主机是一台独立的台式，备份机计划用虚拟机，考虑到两机性能存在一些差距，当主机能正常工作时  
当然是用独立的物理机更好。所以上面的思路需要做调整

元信息
```
身份值 # 代表节点的处理能力，这里就是nat和ip包转发的能力
固有ip # 和 `IFNAME:1` 通信所需
当前状态 # 主或者备
```

- 上线抢占
  > 某机器 B 上线时向当前工作的路由机 H 请求身份值，和自己的身份值比较，如果自己更大，向 H 发送切换备机指令，  
  之后把自己提升到主。抢占过程可能会导致用户连接断开，需要提前通知

## 负载均衡
ip层的负载均衡存在 负载均衡服务器网卡带宽 问题，所以负载均衡可能需要在链路层做，具体见最后的参考

# reference
每天进步一点点——负载均衡之IP  
<https://blog.csdn.net/cywosp/article/details/38036537>  
每天进步一点点——负载均衡之数据链路层  
<https://blog.csdn.net/cywosp/article/details/38056811>  
