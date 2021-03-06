% zwraca elementy listy L na parzystych indeksach i zwraca liste R, z
% pozostalych elementow i robi to wiele razy dla kazdego parzystego
% indeksu jednorazowo
%
nieparzysty(L,X,Reszta) :-
    nth0(I,L,X,Reszta), % nth0/4 ktora dla kazdego indeksu I zwraca element i liste pozostalych elementow
    I mod 2 =:= 0.

% PomList - pomocnicza lista w której sa elementy juz wstawione do ciagu
% ale tylko raz
% PrawieList - lista tyl na przod, X - wynik


%odwracam mojo liste tyl na przod
rek([], Y, Y, P2, X) :-
    reverse(P2,X).


rek(PomList, I, Limit, PrawieList, X) :-
    J is I+1,
    I < Limit, % czekam az uzpelnie PomListy numerami od 1 do N
    rek([J | PomList], J, Limit, [J | PrawieList], X).

rek(PomList, I, Limit, PrawieList, X) :- % to robie, jakjuz sa uzupelnione czesciowo
    nieparzysty(PomList,N,Reszta), % to mi odpowiada z a permutacje, bo przestawiam do nowych list kolejne elementy z parzystych indeksow
    rek(Reszta, I, Limit, [N | PrawieList], X). % powtarzam dla listy permutowanej

list(N, X) :-
    rek([], 0, N, [], X).
