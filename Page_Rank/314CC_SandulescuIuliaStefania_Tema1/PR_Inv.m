function B = PR_Inv(A)
[randuri, coloane]=size(A);
B=zeros(randuri,coloane);
R=zeros(randuri);
Q=zeros(randuri);
for i=1:randuri
    R(i,i)=norm(A(:,i),2);
    Q(:,i)=A(:,i)/R(i,i);
    for j=i+1:randuri
        R(i,j)=Q(:,i)'*A(:,j);
        A(:,j)=A(:,j)-Q(:,i)*R(i,j);
   
    end
end
Q=Q';
for i=1:randuri
    B(:,i)=RezolvSist(R,Q(:,i));
    
end