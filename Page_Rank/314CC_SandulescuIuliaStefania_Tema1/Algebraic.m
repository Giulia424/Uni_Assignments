function R = Algebraic(nume, d)
format shortG
[file,mesaj]=fopen(nume,"r");
if file == -1
    disp(mesaj)
    return;
end

v=fscanf(file, "%f");
[randuri, coloane]=size(v);
N=v(1);
A=zeros(N);
c=2;
for i=1:N
    if(c<randuri)
        nod=v(c);
        c=c+1;
        nrleg=v(c);
        c=c+1;
        for j=c:c+nrleg-1
            if nod~=v(j)
                A(nod,v(j))=1;
            end
        end
        c=c+nrleg;
    end
end
PR=A';
for i=1:N
    k=0;
    for j=1:N
        if PR(j,i)==1
            k=k+1;
        end
    end
    PR(:,i)=PR(:,i)/k;	
end
%in continuare am folosit formula de pe wikipedia pe care am prelucrat-o
%pana am ajuns la o formula convenabila
I=eye(N);
M=I-d*PR;
V=PR_Inv(M);
R=zeros(N,1);
for i=1:N
    R(i)=((1-d))/N;
end
    R=V*R;%aici doar am calculat matricea de PageRank folosind formula gasita pe wikipedia
    


end



