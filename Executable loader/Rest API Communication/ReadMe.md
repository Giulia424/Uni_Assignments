Am rezolvat toate cerintele, mi-a luat vreo trei zile dar nu am lucrat
un numar de ore constant pe zi. Mi-a luat cateva ore pentru ca 
initial nu folosisem biblioteca parson decat la unele functii, 
si la altele in loc sa parsez cum ar trebui am folosit functii 
din libc cum ar fi strstr.
In principiu am inecput pe baza scheletului de laborator si pe ce
am lucrar la laboratorul de HTTP, utilizand functiile compute_get_request
si compute_post_request, la care am adaugat ulterior functia 
compute_delete_request. 
# Main
Am inceput prin constructia unei structuri care sa imi reprezinte clientul
in care am retinut informatiile care mi s-au parut importante si necesare
in urmatoarele subpuncte, cum ar fi token-ul si cookie-urile, pentru care
am alocat memorie cu ajutorul functiei calloc.
Puteam retine si altele cum ar fi username-ul,parola, etc. 
Apoi am citit de la tastatura comenzile date de user si am cautat 
sa vad ce trebuie sa fac, oprindu-ma doar la introducerea comandei exit.
 In principiu aici am tratat si cateva erori
cum ar fi incercarea de a intra in biblioteca fara a fi logat sau cererea
unei carti fara a fi intrat in biblioteca. Am afisat mesaje de eroare
daca a fost cazul.
# Register  
Mai intai am dechis conexiunea si am verificat sa nu fie nicio eroare
cu socketul. Apoi am citit de la tastatura inputul, usernameul si parola,
asigurandu-ma mai intai ca acestea sunt valide, deci ca ele nu contin
spatii. In caz contrar, am afisat un mesaj de eroare la stdout. Initial folosisem doar fscanf peste tot, dar am avut destule 
probleme din cauza lui si m-am decis sa trec pe fgets. 
Apoi am creat obicetul JSON pentru a il trimite serverului, si a il 
folosi in functia compute_post_request. In cadrul acestei functii, 
construiesc cererea de tip HTTP (message) pe care i-o trimit serverului
adaugand campuri de care am nevoie cum ar fi host-ul, tokenul, tipul continutului, cookies-urile etc.
In final, in functia register verific ca json-ul primit de la server
sa nu imi fi intors nicio eroare, sau in cazul acesta afisez din nou
un mesaj de eroare. Eliberez memoria alocata si inchid conexiunea.

# Login
Merg pe acelasi tipar basically, deschid conexiunea, verific input-ul, creez obiectul de tip JSON ce urmeaza sa fie trimis serverului. Apelez
la aceeasi functie compute_post request si comunic cu serverul, verificand
sa nu fie nicio eroare. Diferenta dintre Register si Login ar fi faptul
ca de data am avut nevoie sa extrag cookie-ul din header pentru a demonstra
ca am fost logata si pentru a il folosi ulterior. 

# Enter_library
Aici am inceput la fel, dar de data asta trebuia sa fie o cerere de tip GET si atunci am folosit compute_get_request in schimb. Functia asta
are aceeasi functionalitate ca functia compute_post_request si imi
construieste cererea trimisa serverului. 
In cadrul functiei enter_libr am deschis conexiunea si am comunicat cu 
serverul. Am extras token-ul primit si am pus prefixul "Bearer" inainte de a il retine in structura mea. Apoi am verificat din nou
sa nu am nicio eroare si am eliberat memoria, am inchis conexiunea.

# get_books
Am denumit functia all_books. Asemanator, am deschis conexiunea,
am apelat functia compute_get_request am trimis o cerere catre server
si am primit raspunsul. Apoi am extras din header json-ul pe care l-am 
parcurs cu ajutorul functiilor din biblioteca parson. Mi-am luat un
aray de carti, denumit books pe care l-am parcurs cu un for. La fiecare
carte, am luat pe rand id-ul si titlul pe care le-am afisat. Am afisat
mesajul de eroare daca am primit vreunul.
# Get_book
Inca o data am comunicat cu serverul si pe baza cererii primite am extras
cartea si informatiile sale. Am folosit functiile json_object_get_string 
si json_object_get_number pentru a primi titlul,autorul,publisher-ul, 
genul si numarul de pagini (pe care l-am castat la int pentru ca am vazut
ca functia returneaza double for some reason).

# add_book
Dupa ce am comunicat iar cu serverul, am comunicat cu user-ul pentru 
a afla informatii despre cartea care trebuie introdusa. Aici am verificat
validiatea datelor (page_count sa nu fie altceva decat un numar).
Apoi am folosit functiile din biblioteca parson pentru a creea obiectul,
cartea pe care il folosesc in functia compute_post_request. Verific
erorile, eliberez memoria si opresc conexiunea.

# delete_book
Aici nu mai fac altceva decat ce am facut si in celelalte functii,
trimit o cerere, primesc alta de la server si apelez functia
compute_delete_request care e pretty much bazata pe compute_get_request.

# logout 
Aici singura diferenta ar fi ca folosesc memset-ul pentru a sterge
cookie-urile si token-ul pentru a pierde orice fel de acces la contul
din care am iesit sau la biblioteca sa.
