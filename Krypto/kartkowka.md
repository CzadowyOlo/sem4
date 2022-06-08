Mamy taka maszyne do robienia podpisow
Dziala to tak, że każdy może wsadzić do niej jakąś wiadomość
i ta maszynka podpisuje ją.
Każdy może sprawdzic ze ten podpis jest legitny

Podpisywanie RSA(klucz prywatny d, N. Klucz publiczny (e, N))
1. Użytkownik chce podpisać wiadomość M, wysyła do maszynki
2. Maszynka podpisuje i robi S = M^d mod N
3. Przesyla to uzytkownikowi.
4. Każdy jest w stanie sprawdzic ze wiadomość M jest podpisana przez maszynke poprzez zrobienie
$S^e mod N$
$S^e = (M^d)^e mod N = M^{d\cdot e} mod N = M mod N$
5. Pytanie brzmi:
Czy ktos jest w stanie podać takie S, i M, że S^e = M oraz ani S ani M nie bylo podpisane przez maszynke


Zadanie:
1. Atakujacy wysyla wiadomosci m1, m2, ... mn do maszynki
2. Maszynka je podpisuje i zwraca s1, s2 ... sn

    Każdy użytkownik moze sprawdzic że Decr(s1) = m1 oraz Decr(s2) = m2

3. Atakujacy wygrywa gdy jest w stanie znalezc podrobić podpis M, czyli takie S, że Decr(S) = M
Oraz $M \neq m1$ i $ M \neq m2 $ 
oraz robi to z niezerowym prawdopodobienstwem

Rozwiazanie:
Jak chce podrobić wiadomość M. To jeżeli jest ona liczbą złożoną to wezmy $M = m1 \cdot m2$
Wyslijmy do maszynki i dostajemy s1, s2
Wtedy $S=s1\cdot s2$
Koniec.
Dlaczego?
Ponieważ  $$Decr(S) = S^e mod N = (s_1\cdot s_2)^e mod N = (m_1^d\cdot m_2^d)^e mod N = (m_1\cdot m_2)^{d\cdot e}modN = M ^ 1$$
