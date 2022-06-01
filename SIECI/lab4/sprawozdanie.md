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

