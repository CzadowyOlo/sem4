## Task description
1. In GNS3 simulation program create a virtual network with a given topology such that:
   1. the virtual network is connected with the outside „physical” network represented by device named `Cloud`.
   2. `R5` has a dynamic IP address given by `Cloud`
   3. other devices have their static IP address inside their local networks
   4. all devices are able to communicate with each other via `ping`
   5. all devices are able to communicate with the outside world e.g. `google.com`
2. Setup packet capture on networks `192.168.0.0.`, `192.168.2.0`, `192.168.3.0`.
3. Analyse captured packets sent and received due to executing `ping google.com` in the terminal of PC2.
