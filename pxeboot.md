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
