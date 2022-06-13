% z2

% :- ['my_scaner.pl','zad1.pl','interpreter.pl'].
:- consult('my_scaner.pl').
:- consult('zad1.pl').
:- consult('interpreter_wyklad.pl').

% opens file, reads key words from it (with lexer) and then using parser checks if its 
% gramaticly correct program. after that program is executed

wykonaj(N) :- 
	open(N,read,X),
	scanner(X,Y),
	close(X),
	phrase(program(PROGRAM),Y), 
	interpreter(PROGRAM).
    