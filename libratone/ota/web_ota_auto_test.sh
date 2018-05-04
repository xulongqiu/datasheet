#!/bin/sh

echo '\033[34m'

echo '__        _______ ____     ___ _____  _      _____ _____ ____ _____ '
echo '\ \      / / ____| __ )   / _ \_   _|/ \    |_   _| ____/ ___|_   _|'
echo ' \ \ /\ / /|  _| |  _ \  | | | || | / _ \     | | |  _| \___ \ | |  '
echo '  \ V  V / | |___| |_) | | |_| || |/ ___ \    | | | |___ ___) || |  '
echo '   \_/\_/  |_____|____/   \___/ |_/_/   \_\   |_| |_____|____/ |_|  '
echo ''
echo '\033[0m'

fix_numbers()
{
        if [ $1 -ne 1 ]; then
                echo s;
        fi
}

if [ $# != 2 ] ; then
        echo "\033[31m[INFO] Usage: ./web_ota_auto_test.sh <Your ota package path> <Device IP>\033[0m"
        exit
fi

ping -w 1 $2
adb_net_test=$?
ping_cnt=0
while [ $adb_net_test -ne 0 ]
do
	ping_cnt=`expr $ping_cnt + 1`
	if [ $ping_cnt -eq 5 ]; then
		echo "Device offline..."
		exit
	fi
	ping -w 1 $2
	adb_net_test=$?
done

echo "Uploading ota packages..."
curl -d "json={\"Control\":\"5\",\"SEQ\":\"0\",\"ControlContent\":\"None\"}" "http://$2/cgi?Update" 
curl -S -H "Expect:" -F multipleFileUpload=@$1 "http://$2/cgi?UploadFile"
echo "Updating exccuting..."
curl -d "json={\"Control\":\"0\",\"SEQ\":\"0\",\"ControlContent\":\"None\"}" "http://$2/cgi?Update"
curl -d "json={\"Control\":\"4\",\"SEQ\":\"0\",\"ControlContent\":\"None\"}" "http://$2/cgi?Update"
curl -d "json={\"Control\":\"0\",\"SEQ\":\"0\",\"ControlContent\":\"None\"}" "http://$2/cgi?Update"

adb_net_test=$?
ping_cnt=0
while [ $adb_net_test -ne 0 ]
do
	if [ $ping_cnt -gt 10 ]; then
		echo "Device ota maybe failure..."
		exit
	else
		if [ $ping_cnt -lt 2 ]; then
			echo "升级失败, 设备可能没有重启..."
			exit
		fi
	fi
	ping_cnt=`expr $ping_cnt + 1`
	sleep 10
	ping -w 1 $2
	adb_net_test=$?
done

ret=`curl "http://$2/cgi?Overview"`
check=`echo $2 | awk -F- '{print $4}' | awk -F. '{print $1}'`
result=$(echo $ret | grep "${check}")
if [ "$result" != "" ]; then
	echo "检查升级成功"
else
	echo "检查升级失败"
fi
