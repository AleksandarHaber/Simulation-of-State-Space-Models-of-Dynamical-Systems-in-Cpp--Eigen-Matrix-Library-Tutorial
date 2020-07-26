clear,pack,clc
double x0;
double input;
double output;
double state;

% these are simulation conditions and results generated using the Eigen C++
% matrix library
output=dlmread('simulatedOutputSequenceFileOutput.csv');
state=dlmread('simulatedStateSequenceFileOutput.csv');

% these are original system matrices and conditions
A=dlmread('AFile.csv');
B=dlmread('BFile.csv');
C=dlmread('CFile.csv');
x0 = dlmread('x0File.csv');
input = dlmread('inputFile.csv');

[m,sampleTime]=size(input);
[r,~]=size(output);
[n,~]=size(A)

% these two matrices store MATLAB simulation results
MATLAB_state=zeros(n,sampleTime);
MATLAB_output=zeros(r,sampleTime);
tic
for i=1:sampleTime
   if i==1
       MATLAB_state(:,i)=x0;
       MATLAB_output(:,i)=C*x0;
       
   else
       MATLAB_state(:,i)=A*MATLAB_state(:,i-1)+B*input(:,i-1);
       MATLAB_output(:,i)=C*MATLAB_state(:,i);
   end
end
time1=toc

% compare the results
figure(1)
plot(MATLAB_output(2,:),'r')
hold on 
plot(output(2,:),'k')

figure(2)
plot(MATLAB_output(2,:)-output(2,:))

norm(MATLAB_output-output,'fro')/norm(MATLAB_output,'fro')
norm(MATLAB_state-state,'fro')/norm(MATLAB_state,'fro')