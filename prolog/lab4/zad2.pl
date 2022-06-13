% zagadka zwelstaina

left_of(X, Y) :- Y is X+1.
right_of(X, Y) :- left_of(Y, X).

next_to(X, Y) :- left_of(X, Y).
next_to(X, Y) :- left_of(Y, X).

%number, naionality, color, animal, drink, cigar

solution(FishMan) :-
    Street = [
           house(1, norweigan,  _,     _,   _,    _),
           house(2, _,  _,     _,   _,    _),
           house(3, _,  _,     _,   milk,    _),
           house(4, _,  _,     _,   _,    _),
           house(5, _,  _,     _,   _,    _)],
    %member(house(1, norweigan,     _,          _,      _,          _           ), Street),
    member(house(_, britol,          red,        _,      _,          _           ), Street),
    member(house(A, _,             green,      _,      _,          _           ), Street),
    member(house(B, _,             white,      _,      _,          _           ), Street),
    left_of(A, B),
    member(house(_, daneman,          _,          _,      tea,        _           ), Street),
    member(house(C, _,             _,          _,      _,          light       ), Street),
    member(house(D, _,             _,          cats,   _,          _           ), Street),
    next_to(C, D),
    member(house(_, _,             yellow,     _,      _,          cigar     ), Street),
    member(house(_, german,        _,          _,      _,          pipe      ), Street),
    %member(house(3, _,             _,          _,      milk,       _           ), Street),
    %linia 30
    member(house(_, _,             _,          birds,  _,          nofilter   ), Street),
    member(house(_, swede,         _,          dog,    _,          _           ), Street),
    member(house(G, norweigan,     _,          _,      _,          _           ), Street),
    member(house(H, _,             blue,       _,      _,          _           ), Street),
    next_to(G, H),
    member(house(E, _,             _,          horse,  _,          _           ), Street),
    member(house(F, _,             yellow,          _,      _,          _     ), Street),
    next_to(E, F),

    % na pale wycialem i wkleiłem z lini 30 
    member(house(I, _,             _,          _,      _,          light       ), Street),
    member(house(J, _,             _,          _,      water,      _           ), Street),
    next_to(I, J),
    % i spadło z 16k do 5k

    member(house(_, _,             _,          _,      beer, menthol        ), Street),
    member(house(_, _,             green,      _,      coffee,     _           ), Street),
    member(house(_, FishMan,     _,          fish,   _,          _           ), Street).




    
    % #1 Norweg zamieszkuje pierwszy dom
    % #2 Anglik mieszka w czerwonym domu.
    % #3 Zielony dom znajduje się bezpośrednio po lewej stronie domu białego.
    % #4 Duńczyk pija herbatkę.
    % #5 Palacz papierosów light mieszka obok hodowcy kotów.
    % #6 Mieszkaniec żółtego domu pali cygara.
    % #7 Niemiec pali fajkę.
    % #8 Mieszkaniec środkowego domu pija mleko.
    % #9 Palacz papierosów light ma sąsiada, który pija wodę.
    % #10 Palacz papierosów bez filtra hoduje ptaki.
    % #11 Szwed hoduje psy.
    % #12 Norweg mieszka obok niebieskiego domu.
    % #13 Hodowca koni mieszka obok żółtego domu.
    % #14 Palacz mentolowych pija piwo.
    % #15 W zielonym domu pija się kawę.