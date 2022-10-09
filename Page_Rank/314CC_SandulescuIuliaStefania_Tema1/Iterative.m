function R = Iterative(nume, d, eps)
%format shortG
[file,eroare]=fopen(nume,'r');
%file=fopen(nume,"r")
if file == -1
    disp(eroare)
    return;
end

v=fscanf(file, "%f");
[randuri, coloane]=size(v);

N=v(1);%N memoreaza numarul total de noduri
A=zeros(N);
c=2;%c este un contor ce imi va numara indicii pana cand ajunge la un nod nou
for i=1:N
    if(c<randuri)
        nod=v(c);%in cadrul for-ului imi memoreaza fiecare nod pe rand
        c=c+1;
        nrleg=v(c);%in cadrul for-ului imi memoreaza numarul de legaturi pentru fiecare nod
        c=c+1;
        for j=c:c+nrleg-1
            if nod~=v(j)%am pus aceasta conditie pentru a lua in considerare si cazul in care o pagina are legatura cu ea insasi
                A(nod,v(j))=1;
            end
        end
        c=c+nrleg;
    end
end
PR=A';%Am memorat in PR transpusa matricei de adiacenta
for i=1:N
    k=0;
    for j=1:N
        if PR(j,i)==1
            k=k+1;%k a devenit un contor ce imi numara numarul de aparitii ale lui unu in matricea PR(deci numara de fapt legaturile fiecarui nod)
        end
    end
    PR(:,i)=PR(:,i)/k;%aici am inlocuit in matricea de adiacenta valorile, memorand probabilitatile de a ajunge din nodul ales catre celelalte noduri
end
Rant=ones(N, 1)/N;
R=d*PR*Rant+(1-d)/N;%aici doar am urmat formula de pe wikipedia din cadrul algoritmului iterativ pentru PageRank
while abs(R-Rant)>eps
    Rant=R;
    R=d*PR*Rant+(1-d)/N;
    
end

 

fclose(file);

end
