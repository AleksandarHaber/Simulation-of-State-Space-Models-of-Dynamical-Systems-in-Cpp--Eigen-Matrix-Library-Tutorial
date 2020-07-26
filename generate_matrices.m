%csvwrite(filename,M)
clear,pack,clc

A=0.06*randn(100,100);
B=0.1*randn(100,10);
C=ones(10,100);
input=rand(10,1000);
x0=randn(100,1);
[m,sampleTime]=size(input);
[r,~]=size(C);
[n,~]=size(A)

MATLAB_state=zeros(n,sampleTime);
MATLAB_output=zeros(r,sampleTime);

for i=1:sampleTime
   if i==1
       MATLAB_state(:,i)=x0;
       MATLAB_output(:,i)=C*x0;
       
   else
       MATLAB_state(:,i)=A*MATLAB_state(:,i-1)+B*input(:,i-1);
       MATLAB_output(:,i)=C*MATLAB_state(:,i);
   end
end

plot(MATLAB_output(1,:),'r')

csvwrite("AFile.csv",A)
csvwrite("BFile.csv",B)
csvwrite("CFile.csv",C)
csvwrite("x0File.csv",x0)
csvwrite("inputFile.csv",input);
