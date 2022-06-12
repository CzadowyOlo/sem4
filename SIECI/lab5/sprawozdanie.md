## Lista nr 5 - HTTP
File server3.pl contains example program of a server protocol HTTP.  

1. Execute the script, test and think how it works.
2. Establish connection using web browser.
3. Change script or write your own server, that sends back request header.
4. Change script (or write your own server in any programming language) to manage client requests to simple text WWW service (few static websites with static links to each other) saved in some folder on local disc of user.
5. Intercept communicates to/from server using any analyser - Analyse their structure
6. Write simple report.

## Przygotowanie
1. Pobrałem kod servera i zmieniłem alias ip mojego komputera z 'luki' na 'locolhost'
2. Stworzyłem plik indeks.html
<br />
server.pl:

```bash
#!usr/bi/perl
use HTTP::Daemon;
use HTTP::Status;  
#use IO::File;
my $d = HTTP::Daemon->new(
         LocalAddr => 'localhost',
         LocalPort => 4321,
     )|| die;

print "Please contact me at: <URL:", $d->url, ">\n";
while (my $c = $d->accept) {
    while (my $r = $c->get_request) {
        if ($r->method eq 'GET') {
            
            $file_s= "./index.html";    # index.html - jakis istniejacy plik
            $c->send_file_response($file_s);
        }
        else {
            $c->send_error(RC_FORBIDDEN)
        }
    }
    $c->close;
    undef($c);
}
```
3. Uruchomiłem program i wpisałem w przegladarkę danego linka, nic sie nie wyświetliło, bo plik index.html był pusty.
