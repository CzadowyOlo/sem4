#!usr/bi/perl

use HTTP::Daemon;
use HTTP::Status; 
use Data::Dumper;
use IO::File;

#$post =~ s/^\r*\n$/<br>/g;

$Data::Dumper::Terse = 1;
$Data::Dumper::Useqq = 1; 

my $d = HTTP::Daemon->new( #konstruktor serwera
        LocalAddr => 'localhost', #alias ip mojego komputera
        LocalPort => 2168, #wolny socket
    )|| die;

print "Please contact me at: <URL:", $d->url, ">\n";

# wpisuję sobie tekst do headera (na razie tylko na stringu), bo oprócz samego requesta wrzuce tam hiperłącze do indeks.html
my $str = <<END;
I AM header<br><a href="indeks.html"><strong>GO BACK</strong></a><br><br>
END
my $strendline = <<END;
<br>
<br>
next header: 
<br>
END
# $SIG{INT} = \&tsktsk;
# sub tsktsk {
#     $SIG{INT} = \&tsktsk;           # See ``Writing A Signal Handler''
#     "npx kill-port 2169" | bash
#     warn "\aThe long habit of living indisposeth us for dying.\n";
#     # shutdown($LocalPort, 0) if $LocalPort;
#     # shutdown($LocalPort, 2) if $LocalPort;
#     # close($LocalPort) if $LocalPort;
# }


my $dir = "./Web"; # w tym folderze mam podstrony mojej sieci
my $filename = "./Web/header.html"; #odnosimy się do pliku indeks
open(FH, '>', $filename) or die $!; #otwieramy
print FH $str; #zrzucam wcześniej przygotowanego stringa do header.html
close(FH); #zamykamy plik ze stroną html (header)

while (my $c = $d->accept) { #sprawdzamy czy sie połaczyliśmy do witryny i zwracamy na c adres hosta albo 0

    while (my $r = $c->get_request) { #This method reads data from the client and turns it into an HTTP::Request object which is returned. 
    #It returns undef if reading fails. If it fails, then the HTTP::Daemon::ClientConn object ($c) should be discarded, 
    #and you should not try to call this method again on it. The $c->reason method might give you some information about why $c->get_request failed.

        if ($r->method eq 'GET') {
            my $header = $r->headers->as_string; #pobieramy rządanie ze zmiennej r i zapisujemy je pod stringiem
            my $filename = "./Web/header.html"; #odnosimy się do pliku header
            open(FH, '>>', $filename) or die $!; #otwieramy

            foreach($r->header_field_names) {
                print FH ($_. "\t----->\t" . $r->header($_) . "<br>" );
            }

            print FH $strendline;
            close(FH); #zamykamy plik ze stroną html (header)

            # r->uri A uniform resource identifier, 
            # or URI, is a short string containing a name or address which refers to an object in the "web."
            # w momwncie otwarcia samego adresu, doklejamy do niego strone startową
            if($r->uri eq "/" | $r->uri eq "/favicon.ico"){ #obsluga przekierowań i inicjacji | jakiś smiec ktory si epojawia w uri
                my $file_s= "./Web/main.html";    # main.html - istniejacy plik - strona startowa
                $c->send_file_response($file_s);
            } else{
                $file_s = $dir.$r->uri; #idziemy do folderu z innymi podstronami
                #mam tutaj listę moich podstron
                $c->send_file_response($file_s);
                #przekierowanie na wybraną przez kliknięcie podstronę z hiperłącza
            }
        }else {
            $c->send_error(RC_FORBIDDEN)
        }
    }
    $c->close;
    undef($c);
}
