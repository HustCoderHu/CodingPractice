# 旦哥 asus 1080ti
# remote_ip="192.168.110.244"
remote_ip=115.156.157.164
usr=hzx
remote_dir=/home/hzx/tftest
# remote_dir="/home/$usr/cnn-hzx/weights_zerod"


# file_list="include/ src/ test/ scripts/ CMakeLists.txt *.cpp"
file_list="lstm.py"

echo ${file_list}
echo on
# tar cfv $pkg_id ${file_list}

# CDIR="cd "${remote_dir}

# cmd_r=${CDIR}
# cmd_r=${cmd_r}"; rm -rf ${file_list}; tar xf ${pkg_id}"

scp ${file_list} $usr@${remote_ip}:${remote_dir}

# scp ${pkg_id} $usr@${remote_ip}:${remote_dir}
# ssh -t -t -p 22 $usr@${remote_ip} ${cmd_r}

# cmd_r=${CDIR}
# cmd_r=${cmd_r}"; make -j2"
# ssh -t -t -p 22 $usr@${remote_ip} ${cmd_r}