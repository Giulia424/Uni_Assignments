    Pentru functia Iterative am incercat initial sa ma asigur ca afisez intocmai 
ca in cerinta (cu sase zecimale) valorile cerute si am incercat sa schimb formatul
folosind dormat shortG, insa asta imi afisa doar cinci cifre. Deci am renuntat la 
asta si am decis sa las afisarea pentru functia PageRank de la subpunctul 3
Am deschis mai intai fisierul in modul read only si m-am asigurat ca am facut asta cum 
trebuie, iar in caz contrar am afisat un mesaj de eroare.
Am citit toate valorile din fisier si le-am inserat in vectorul v pe care l-am facut float.
Apoi am gasit numarul nodurilor sau a paginilor web si l-am memorat in variabile N.
Am initializat matricea de adiacenta si am umplut-o cu zero-uri, urmand sa memorez in ea
legaturile dintre noduri.Mi-am luat un contor c care incepe de la pozitia a doua din vector,
deci preia valoarea primului nod. Apoi am facut un for in cadrul caruia am decis sa mai iau
doua variabile:nod, care memoreaza nodul la curent si nrleg care tine minte numarul de legaturi
ale nodului ales. Astfel am parcurs vectorul v si pe linii am umplut matricea in momentul
in care am gasit o legatura cu un nod nou.
    Dupa toate astea, am transpus matricea de adiacenta si am salvat-o intr-o alta matrice (PR), 
pe care am continuat sa o prelucrez pana cand am reusit sa stochez in ea vectorul PageRank.
M-am folosit de link-urile date in cerinta (https://en.wikipedia.org/wiki/PageRank) si am folosit 
formula gasita in cadrul algoritmului iterativ, folosind alte doua matrice (Rant in loc de R(t)
si R in loc de R(t+1))

    Functia Algebraic incepe asemanator cu cea Iterative:imi deschide fisierul dat ca parametru, 
verifica sa nu apar nicio eroare si citeste din fisier toate valorile pe care le stocheaza in vectorul v.
Apoi calculeaza in acelasi mod matricea  PR, retinand probabilitatile de a ajunge dintr-un nod in celelalte.
Am urmarit din nou formulele de pe wikipedia si tot din cadrul algoritmului iterativ alea alta formula pe care
am utilizat-o la acest subpunct(cea de la notarea in matrice). In urma prelucrarii acesteia am realizat ca am 
nevoie de o functie ce imi calculeaza inversa unei matrice. Asa ca am facut o functie separata numita PR_Inv, 
careia i-am trimis ca parametru functia calculata(M).

       In cadrul functiei PR_Inv am  folosit algoritmul Gram Schmidt modificat gasit in laborator,unde avem 
A, R si Q, astfel incat
A=Q*R (A este matricea cautata, R este matricea superior triunghiulara).Apoi am folosit algoritmul de 
rezolvare a sistemelor superior triunghiulare ce primeste ca parametru matricea R si cate o coloana din matricea Q
si returneaza cate o coloana din matricea B, pe care le insereaza apoi in matrice.
   \
    In functia finala, PageRank, am deschis din nou fisierul dat in modul read only si am citit din acesta 
toate valorile intr-un  vector v, apoi am gasit numarul total de noduri si l-am stocat in variabila N.A trebuit 
sa afisez valorile cerute intr-un fisier cu acelasi nume ca cel de intrare, dar cu extensia .out, deci am ales 
sa concatenez numele fisierului dat initial cu aceasta extensie. Apoi am deschis fisierul de iesire in modul 
write only.Am determinat faptul ca functia u(x) este discontinua in punctele x1=val1 si x2=val2 si am prelucrat 
aceasta informatie pana cand a rezultat un sistem de doua ecuatii din care au iesit variabilele a si b, in functie
de cele doua valori cititie in finalul fisierului.
    Am folosit functiile Iterative si Algebraic pentru a stoca in vectorii X si Y vectorii de PageRank calculati 
anterior.Mai departe am folosit vectorul Y, reprezentand cel de-al doilea vector pe care l-am sortat descrescator 
si pe care l-am folosit la sortarea nodurilor. Apoi am aflat functia F, luand-o pe ramuri si inlocuind in u(x) x-ul cu 
Pr1(i), in functie de  valorile 1 si 2.
    In final, am afisat intocmai ca in cerinta clasamentul paginilor web :indicii de la 1 la N, numarul nodurilor 
si apoi gradele de apartenenta
    