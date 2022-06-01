## Przygotowanie
1. Pobrałem z jakiejś stronnki, mam nadzieję że nie z wirusami, obraz routera `c7200`.
2. Pobrałem aplikację `gns3` przez terminal za pomocą *sudo apt install*
3. Zaimportowałem do projektu w `gns3` pobrany router:

![imporowanie](screens/s1.png)
4. Następnie wstawiłem wszystkie elementy sieci aby stworzyć topologię zadaną przez prowadzącego:

![wstępna topologia](screens/s2.png)
5. W konfiguracji routerow pododawalem odpowiednie porty, by je wzajemnie łączyć:

![router1](screens/s3.png)
![router2](screens/s4.png)
6. Skonfigurowałem chmurę tak o:
  1. PPM na chmurę i opcja ==conigure==.
  2. Dodałem interfejs internetowy z opcji ==show special enthernet interfaces==.
  3. Wybrałem ==virbr0==.
  4. Laptopa mam podlączonego kabelkiem do routera, wiec nie było problemów  z tym.
7. Następnie zająłem się szczegółową konfiguracją urządzeń.

## Konfiguracja urządzeń

Aby sprawdzić, czy dane urządzenie jest podlączone do sieci, wystarczy spingować googla:
```bash
ping google.com
```
1. Routery:


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
### `R6`

```
conf t
int f0/0
no shut
ip add 192.168.3.5 255.255.255.0
end

conf t
ip domain-lookup source-interface f0/0
ip name-server 8.8.8.8
end

conf t
int f1/0
no shut
ip add 192.168.4.2 255.255.255.0
end

conf t
int f2/0
no shut
ip add 192.168.1.11 255.255.255.0
end

conf t
router rip
version 2
no auto-summary
network 192.168.1.0
network 192.168.4.0
network 192.168.3.0
end

wr
```

### `R2`

```
conf t
int f1/0
ip add 192.168.2.1 255.255.255.0
no shut
int f0/0
ip add 192.168.4.6 255.255.255.0
no shut
end

conf t
router rip
version 2
no auto-summary
network 192.168.2.0
network 192.168.4.0
end

conf t
ip domain-lookup
ip name-server 8.8.8.8
end
```

### `R3`

```
conf t
int f0/0
ip add 192.168.2.2 255.255.255.0
no shut
end

conf t
router rip
version 2
no auto-summary
network 192.168.2.0
end

conf t
ip domain-lookup
ip name-server 192.168.42.129
end
wr
```
2. Pecety:

### `PC-1`

```
ip 192.168.1.1/24 192.168.1.11
ip dns 8.8.8.8
wr
```
You can test if connected to web
```
ping google.pl
google.pl resolved to ...

84 bytes from ...
84 bytes from ...
84 bytes from ...
84 bytes from ...
84 bytes from ...
```

### `PC-2`

```
ip 192.168.2.22/24 192.168.2.1
ip dns 8.8.8.8
wr
```

### `PC-3`

```
ip 192.168.2.3/24 192.168.2.1
ip dns 8.8.8.8
wr
```

Po zakończonej konfiguracji oraz uruchomieniu (*start all nodes*), sieć prezentuje sie następująco:

![siec](screens/s5.png)

## Testowanie czy działa:


