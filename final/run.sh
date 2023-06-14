#sudo make clean
#sudo make
sudo mknod /dev/lab6-2 c 61 0
ls -al /dev/lab6-2
sudo insmod lab6-2.ko

#sudo echo 1 > /dev/lab6-2
sudo echo start
sudo python3 final.py
sudo echo end 
