# view this boi RAW!





#config for pfsense as firewall 172.16.0.1
		w2k19 AD1+DNS 172.16.0.2
  		w2k19 AD2+DNS 172.16.0.3
    		w2k19 wins+wds+file share and other 172.16.0.4
		rocky linux IPXE+netboot.xyz+dhcp 192.168.0.100


file share have one central file share with a folder everyone can access then have 5 gb folders auto created for each user plus a shared folder and a ro iso folder
auto added folder done with quotas?
linux isos should be handled by netboot.xyz but if need be we can put extra isos in the currently only win iso folder or have the pxe server host them
	/share/
 		users/
   			user1/
      			user2/
	 		etc ....
	 	full-access/
   				img.png
       				configfile.conf
	   			worddoc.docx.exe
       		win-iso&winpe/
	 			archlinux.iso
    				amongus.iso
	
need to make a limited gpo for normal users things to limit
app installs
cmd/pwrshl
settings/ctrlpanl
more things i cant think of rn


make testing area 
use vms
how to isolate and then access things
	firewall rules
 	ssh/rdp into control machines inside of the isolated areas
	template
  




# funny to do
custom dns things
	swap rick roll and darude sandstorm & dont make loop
 	blocklist
  	log list
replace windows sounds


# win server 2k19-1
install wds wsus and group policy management
install updates in C:\updates
