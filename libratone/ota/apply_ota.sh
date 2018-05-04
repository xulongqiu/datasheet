#!/bin/sh

echo '\033[34m'
echo '  ____                   ___ _____  _    '
echo ' / ___|___   ___ ___    / _ \_   _|/ \   '
echo '| |   / _ \ / __/ _ \  | | | || | / _ \  '
echo '| |__| (_) | (_| (_) | | |_| || |/ ___ \ '
echo ' \____\___/ \___\___/   \___/ |_/_/   \_\'
echo '                                         '

adb shell ls /cache/lost*

if [ $? -ne 0 ]; then
	echo "\033[31m ADB unconnect, please check.\033[0m"
	exit_cnt=1
	while true; do
		adb shell busybox ls > /dev/null 2>&1
		if [ $? -eq 0 ]; then
			break;
		else
			exit_cnt=`expr $exit_cnt + 1`
			echo "\033[31m Please Check your ADB usb cable link~\033[0m"
			if [ $exit_cnt -eq 5 ]; then
				echo "\033[31m Please retry again...\033[0m"
				exit
			fi
		fi
		sleep 2
	done
fi

echo '\033[32m'

fix_numbers()
{
        if [ $1 -ne 1 ]; then 
                echo s; 
        fi
}

# 参数检查
if [ $# != 1 ] ; then
	echo "\033[31m[INFO] Usage: ./apply_ota.sh <Your ota package path>\033[0m"
	exit
fi

# 参数检查
if [ ! -f $1 ]; then
	echo "\033[31m[ERROR] $1 is'nt a file\033[0m"
	exit
fi

f_name=`basename $1`
cmd_file=/cache/recovery/command

# 如果/cache/delta2-*zip升级包已经存在且和将要传输的完全相同(MD5)则跳过, 否则进行传输
cccheck_exist=`adb shell "if [ -f /cache/$f_name ]; then echo \"1\"; else echo \"0\"; fi"`
need_copy=true
if [ $cccheck_exist -eq 1 ] ; then
	host_md5=`md5sum $1 | awk '{print $1}'`
	target_md5_ori=`adb shell md5sum /cache/$f_name`
	target_md5=`echo $target_md5_ori | awk '{print $1}'`
	if [ _X"$host_md5" = _X"$target_md5" ]; then
		echo "[INFO] $f_name have no changed..."
		need_copy=false
	fi
fi
if $need_copy; then
	echo "[EXEC] adb push $1 /cache/$f_name"
	adb push $1 /cache/
	adb shell sync
fi

# 清空/cache/recovery/的内容
adb shell "if [ -d `dirname $cmd_file` ]; then rm -rf /cache/recovery/; fi"
sync

# 生成/cache/recovery/command文件
echo "[INFO] Prepare arguments for recovery..."
adb shell mkdir `dirname $cmd_file`
adb shell sync
adb shell "if [ ! -f $cmd_file ]; then touch $cmd_file; fi"
adb shell "echo \"--update_package=CACHE:$f_name\" > $cmd_file"

adb shell unzip /cache/$f_name recovery.img -o -d /cache/
adb shell "if [ -f /cache/recovery.img ]; then
        encode -d -key:168 /cache/recovery.img /cache/recovery.img.dcd
	echo \"[INFO] Updating recovery.img -> /dev/block/recovery \"
        cat /cache/recovery.img.dcd > /dev/block/recovery
        rm -rf /cache/recovery.img
        rm -rf /cache/recovery.img.dcd
fi"

# 重启系统


wait_sec=3
echo "Wait $wait_sec second`fix_numbers $wait_sec`\033[0m"
while [ $wait_sec -gt 0 ]; do
        echo -n "[INFO] restarting target after: $wait_sec`fix_numbers $wait_sec` \033[999D"
        sleep 1
        wait_sec=$(($wait_sec - 1))
done 

echo "Reboot Device"
adb shell reboot recovery
sleep 0.5

while true; do
	adb shell busybox ls > /dev/null 2>&1
	if [ $? -eq 0 ]; then
		break;
	fi
	sleep 0.5
done

echo "\033[33m"
adb shell busybox tail -f /tmp/recovery.log
echo "\033[0m"
