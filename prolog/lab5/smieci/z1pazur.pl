scanner(X,Y):-
    czytaj(X,R),
%    close(X),
    na_token(R,Y).

na_token([],[]).
na_token([H|R],W):-
    na_token(R,W1),
    rozdzielacz(H,W2),
    append(W2,W1,W).

token_pom(X,[key(X)]):-
    key(X),
    !.
token_pom(X,[sep(X)]):-
    sep(X),
    !.
token_pom(X,[int(R)]):-
    atom_number(X,R),
    !.
token_pom(X,[Z]):-
    \+ (sub_atom(X,_,1,_,C),
       \+ char_type(C,upper)),
    Z =.. [id,X],
    !.

rozdzielacz(S,R):-
    atom_chars(S,Sl),
    rozdzielacz(Sl,'',0,[],R).


typ_chara(H,T1):-
    (   (char_type(H,digit),T1=4)
        ;(char_type(H,lower),T1=2)
        ;(char_type(H,upper),T1=1)
        ;(char_type(H,prolog_symbol),T1=3)
        ;(H = ';',T1=3)),
        !.
% slowo, bufor,typ (0-nieznany,1-id,2-key,3-sep,4-int), lista, wynik
rozdzielacz([],B,_,L,W):-
    (   B = '' -> L = W; (token_pom(B,R),append(L,R,W))),
    !.

rozdzielacz([H|R],_,0,L,W):-
    typ_chara(H,T1),
    rozdzielacz(R,H,T1,L,W),
    !.
rozdzielacz([H|R],B,T,L,W):-
    typ_chara(H,T1),
    T1 = T,
    atom_concat(B,H,B1),
    rozdzielacz(R,B1,T,L,W),
    !.
rozdzielacz([H|R],B,_,L,W):-
    typ_chara(H,T1),
    token_pom(B,B1),
    append(L,B1,L1),
    rozdzielacz(R,H,T1,L1,W).


% strumien danych, tablica wyników
czytaj(Str,R):-
    get_char(Str,C),
    czytaj(Str,C,R).
czytaj(_,end_of_file,[]):-!.
czytaj(Str,C,R):-
    koniec(C),
    get_char(Str,C1),
    czytaj(Str,C1,R),
    !.
czytaj(Str,C,R):-
    czytaj_slowo(Str,C,'',X),
    czytaj(Str,R1),
    append(X,R1,R),
    !.
% strumien danych, znaleziony char, slowo, lista słów, wczesniejszy
% wynik
czytaj_slowo(end_of_file,_,S,[S]):-!.
% przypadek do 2 argumentowych sep
czytaj_slowo(_,C,Slowo,[Slowo]):-
    koniec(C),
    !.
czytaj_slowo(Str,C,Slowo,Res):-
    atom_concat(Slowo,C,Sl),
    get_char(Str,C1),
    czytaj_slowo(Str,C1,Sl,Res),
    !.



koniec(' ').
koniec('\n').
koniec('\r').
koniec('\t').

key(read).
key(write).
key(if).
key(then).
key(else).
key(fi).
key(while).
key(do).
key(od).
key(and).
key(or).
key(mod).

sep(';').
sep('+').
sep('-').
sep('*').
sep('/').
sep('(').
sep(')').
sep('<').
sep('>').
sep('=').
sep('/=').
sep('=<').
sep('>=').
sep(':=').
