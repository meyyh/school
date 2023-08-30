few things to note 

subnet is 172.16.255.255 or 172.16.0.0/16  
router is opnsense 172.16.0.1  
pxeboot server is arch linux (because you cant stop me) 172.16.0.100

we will be using [ipxe](https://ipxe.org) [chainloading](https://ipxe.org/howto/chainloading)

once you have a booted arch system install these packages

```
sudo pacman -S git dnsmasq nginx
```
git to clone this repo for ipxe files  
dnsmasq for dhcp and netbooting  
nginx as the web server for hosting the iso and ipxe files over http  

## setup
make the folders  
mkdir -p/pxe/{menu,os}  
now clone my repo  
```
git clone https://github.com/meyyh/school
```
and copy **undionly.kpxe** from school/ipxe and **ipxe.efi** from school/ipxe/x86_64 to /pxe  

make the file /pxe/menu/boot.ipxe and put the following inside  
```
#!ipxe

:start
menu PXE Boot Options
item shell iPXE shell
item callname displayname
set sroot //172.16.0.100

item exit  Exit to BIOS

choose --default exit --timeout 10000 option && goto ${option}

:shell
shell

:callname
initrd ${sroot}/os/fedora36/initrd.img
kernel ${sroot}/os/fedora36/vmlinuz inst.repo=${server_root}/ ip=dhcp ipv6.disable initrd=initrd.img
boot

:exit
exit
```
