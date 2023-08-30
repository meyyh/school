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
mkdir -p /pxe/{menu,os}  
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

and add the follwoing to /etc/dnsmasq.conf and make sure to edit the top 4 lines to be correct
```
interface=eth0
dhcp-range=start,end,mask,time
dhcp-option=3,gateway
dhcp-option=6,dns
dhcp-authoritative

# Tag dhcp request from iPXE
dhcp-match=set:ipxe,175

# inspect the vendor class string and tag BIOS client
dhcp-vendorclass=BIOS,PXEClient:Arch:00000

# 1st boot file - Legacy BIOS client
dhcp-boot=tag:!ipxe,tag:BIOS,undionly.kpxe

# 1st boot file - EFI client
# at the moment all non-BIOS clients are considered
# EFI client
dhcp-boot=tag:!ipxe,tag:!BIOS,ipxe.efi

# 2nd boot file
dhcp-boot=tag:ipxe,menu/boot.ipxe

log-queries
log-dhcp
```

edit /etc/nginx/nginx.xonf
```
user http;
worker_processes auto;
worker_cpu_affinity auto;

events {
    multi_accept on;
    worker_connections 1024;
}
http {
    charset utf-8;
    sendfile on;
    tcp_nopush on;
    tcp_nodelay on;
    server_tokens off;
    log_not_found off;
    types_hash_max_size 4096;
    client_max_body_size 16M;

    # MIME
    include mime.types;
    default_type application/octet-stream;

    # logging
    access_log /var/log/nginx/access.log;
    error_log /var/log/nginx/error.log warn;

    # load configs
    include /etc/nginx/conf.d/*.conf;
    include /etc/nginx/sites-enabled/*;
    server {
      listen  80;
      server_name  172.16.0.100;

      location / {
        root /pxe
      }
    }
}
```
