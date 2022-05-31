## Task description
1. In GNS3 simulation program create a virtual network with a given topology such that:
   1. the virtual network is connected with the outside „physical” network represented by device named `Cloud`.
   2. `R5` has a dynamic IP address given by `Cloud`
   3. other devices have their static IP address inside their local networks
   4. all devices are able to communicate with each other via `ping`
   5. all devices are able to communicate with the outside world e.g. `google.com`
2. Setup packet capture on networks `192.168.0.0.`, `192.168.2.0`, `192.168.3.0`.
3. Analyse captured packets sent and received due to executing `ping google.com` in the terminal of PC2.

## Setup
1. Download `c7200` router from [here](https://yaser-rahmati.gitbook.io/gns3/cisco-ios-images-for-dynamips)
2. Download `gns3` by running commands  [here](https://yaser-rahmati.gitbook.io/gns3/linux-installation). If on windows then go [here](https://yaser-rahmati.gitbook.io/gns3/chapter1)
3. Run by typing in terminal `gns3` when on Linux. I had problems with permissions so I am running with `sudo gns3`.
4. Add cisco router to gns3 by following [this tutorial](https://www.computernetworkingnotes.com/ccna-study-guide/how-to-add-install-or-import-ios-in-gns3.html).  
    As a result you should see  
5. Create your project and start moving needed boxes from `all devices panel` to create photo like from task description.  
6. Now time to add links. To do this click `add a link` button on the left panel and connect two objects. They need to have got open ethernet hub. If they lack one then click on the router and add slots like this.
Configuring cloud slots may be different for everyone. I am connected to ethernet and it for me it was to
    1. Click on cloud
    2. Show special Ethernet Interfaces
    3. On the bar choose virb0 and click Add 
7. Config devices by double clicking on one. Console should show up.

## Devices configuration
After every configuration, you can check if router is connected to outside world by typing
```bash
ping google.pl
```
### `R5`
```bash
conf t
int f0/0
ip address dhcp
ip nat outside
no shut
end

conf t
ip domain-lookup
ip name-server 8.8.8.8
end

conf t
int f1/0
ip add 192.168.3.6 255.255.255.0
ip nat inside
no shut
end

conf t
router rip
version 2
no auto-summary
network 192.168.42.0
network 192.168.3.0
default-information originate
end

conf t
access-list 10 permit 192.168.1.0 0.0.254.255
access-list 10 permit 192.168.2.0 0.0.253.255
access-list 10 permit 192.168.3.0 0.0.252.255
access-list 10 permit 192.168.4.0 0.0.251.255

ip nat inside source list 10 interface f0/0 overload
end

wr
```
