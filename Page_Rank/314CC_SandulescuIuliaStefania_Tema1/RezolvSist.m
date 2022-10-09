function X=RezolvSist(A,B)
[randuri,coloane]=size(A);
X=zeros(randuri,1);
for i=randuri:-1:1
    j=i+1;
    X(i)=(B(i)-A(i,j:randuri)*X(j:randuri))/A(i,i);
    
end
end