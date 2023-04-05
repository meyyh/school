#config for pfsense as firewall 192.168.0.1
		AD+DHCP+WDS 192.168.0.2
		centos 8 stream pxeserver with ipxe loading netboot.xyz 192.168.0.3





#centos setup

#set address to 192.168.0.3/24 and both gateway and dns server to 192.168.0.1 then restart the interface to apply changes


dnf install dnsmasq ipxe-bootimgs 

mkdir -p /tftp/menu
chmod 777 /tftp


vim /etc/dnsmasq.conf
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
# disable DNS server
port=0

# enable built-in tftp server
enable-tftp
tftp-root=/tftp
vvvvvvvvvvvvvvvvvvvvvvvvvvvvv
systemctl enable dnsmasq
systemctl start dnsmasq


sudo firewall-cmd --add-service=dhcp --permanent
sudo firewall-cmd --add-service=tftp --permanent
sudo firewall-cmd --add-service=dns --permanent
sudo firewall-cmd --reload


cp /usr/share/ipxe/{undionly.kpxe,ipxe.efi} /tftp/

vim /tftp/menu/boot.ipxe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#!ipxe

menu PXE Boot Options

item shell iPXE shell
item exit  Exit to BIOS

choose --default exit --timeout 10000 option && goto ${option}

:shell
shell

:exit
exit

##add netboot.xyz here
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
