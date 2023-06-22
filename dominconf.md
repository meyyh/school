#config for pfsense as firewall 172.16.0.1
		w2k19 AD1+DNS 172.16.0.2
  		w2k19 AD2+DNS 172.16.0.3
    		w2k19 wins wds and other 172.16.0.4
		rocky linux IPXE+netboot.xyz 192.168.0.100


#rocky setup

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
