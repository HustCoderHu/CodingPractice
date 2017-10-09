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
逻辑上数据包从 IFNAME:1 进入linux，被NAT后从IFNAME:1流出linux，物理上就是从网卡进再出来进入Internet

**单网卡不能启动DHCPserver的原因** : 而且路由器的WAN和LAN连接的设备是分处不同的网路，所以LAN上可以启动DHCPserver。上述情况因为只有一个物理网卡，在这个子网卡上启动DHCPserver，DHCPserver直接出现在WAN网络里，干扰其他人接入网络，表现为断网。

# 配置windows
使用文件dhcp_staticIP.bat
