function [R1 R2] = PageRank(nume, d, eps)
[file,mesaj]=fopen(nume,'r');%am deschis fisierul de intrare in modul read only
v=fscanf(file, "%f");
[nrrand,nrcol]=size(v);
N=v(1);
name=strcat(nume, ".out");%am concatenat numele fisierului dat cu extensia .out pentru a rezulta fisierul de iesire
[file,mesaj]=fopen(name,'w');%am deschis fisierul de iesire in modul write only
val1=v(nrrand-1);
val2=v(nrrand);%am memorat in cele variabilele val1 si in val2 cele doua valori citite din datele de intrare
a=1/(val2-val1);
b=(-1)*a*val1;
X=Iterative(nume, d, eps);
Y=Algebraic(nume,d);
[randuri,coloane]=size(X);
fprintf(file,'%d\n',randuri);
fprintf(file,'%6f\n',X);%am avut grija sa printez toate cele 6 zecimale
fprintf(file,'\n');
fprintf(file,'%6f\n',Y);
fprintf(file,'\n');
v=zeros(randuri,1);
for i=1:randuri
    v(i)=i;
end
[Pr1,vsorted]=sort(Y,'descend');
%aici am sortat vectorul Y (pe care l-am retinut ulterior in PR1), dar si vectorul v dupa aceeasi regula
for i=1:randuri%aici am exprimat functia F luand in considerare cele trei ramuri prezentate in functia u(x)
    if Pr1(i)>=0 & Pr1(i)<val1
        Pr1(i)=0;
    else if Pr1(i)>=val1 & Pr1(i)<=val2
            
            Pr1(i)=a*Pr1(i)+b;
        end
    end
end
for i=1:randuri
    fprintf(file,'%d %d %6f\n',i,vsorted(i),Pr1(i));
end
type(name);%am afisat continutul fisierului de iesire name(nume.out)