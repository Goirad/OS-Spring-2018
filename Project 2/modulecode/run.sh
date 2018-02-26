sudo make clean
sudo make
sudo rmmod test-toy
sudo insmod test-toy.ko
dmesg|tail

