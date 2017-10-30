#!/bin/sh

# IFNAME="ens256"

# IFCFG="ifcfg-eth"
chkconfigADDfile="408router-singleNIC"
# IF_LABEL="${IFNAME}:1"
# DST_FILE="/etc/sysconfig/network-scripts/ifcfg-${IF_LABEL}"

# echo ${DST_FILE}
# LAN_GW="192.168.0.1"
# MASK="16"

# echo "     IFNAME" : ${IFNAME}
# echo "   IF_LABEL" : ${IF_LABEL}
# echo "LAN gateway" : ${LAN_GW}
# echo "       MASK" : ${MASK}

# sub interface config
# sed -r -i "s/NAME=.*/NAME=${IF_LABEL}/" ${IFCFG}
# sed -r -i "s/DEVICE=.*/DEVICE=${IF_LABEL}/" ${IFCFG}
# rm -f ${DST_FILE}
# cp ${IFCFG} ${DST_FILE}

# -i 直接编辑文件
# sed -r -i "s/IFNAME=.*/IFNAME=${IFNAME}/" ${chkconfigADDfile}
# sed -r -i "s/IF_LABEL=.*/IF_LABEL=${IF_LABEL}/" ${chkconfigADDfile}
# sed -r -i "s/LAN_GW=.*/LAN_GW=${LAN_GW}/" ${chkconfigADDfile}
# sed -r -i "s/MASK=.*/MASK=${MASK}/" ${chkconfigADDfile}

# init file
# sed -r -i "s/ifup.*/ifup ${IF_LABEL}/" ${chkconfigADDfile}

postfix stop
systemctl stop postfix.service
systemctl disable postfix.service

systemctl stop firewalld.service
systemctl disable firewalld.service

setenforce 0

chmod +x ${chkconfigADDfile}
chkconfig --del /etc/rc.d/init.d/${chkconfigADDfile}
rm -f /etc/rc.d/init.d/${chkconfigADDfile}
cp ${chkconfigADDfile} /etc/rc.d/init.d/
chkconfig --add /etc/rc.d/init.d/${chkconfigADDfile}