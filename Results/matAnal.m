clear all
close all
clc
files = dir('L/*.txt');

for i = 1:size(files),
    
    fname = files(i).name;
%     disp(['Iter:',num2str(i),' fname:',fname])
    fnametokens = textscan(fname,'%d%s%s%s','Delimiter','.');
    
    tracename = char(fnametokens{2}(1));
        
    configname = char(fnametokens{3}(1));
    confignum = textscan(configname,'gz_config_%d');
    confignum = confignum{1}+1;
    configname=['config',num2str(confignum)];
%     resArray.(tracename).(configname).results=parseCacheRes(['L/',fname]);
    tempRes=parseCacheRes(['./L/',fname]);
    resArray.(tracename)(confignum).results=tempRes;
end
list=fieldnames(resArray)';
for prog=list
%     displayExecTime(char(prog),resArray);
%     displayHitMiss(char(prog),resArray);
%     displayCPI(char(prog),resArray);
%      displayRatio(char(prog),resArray);
%     displayKickouts(char(prog),resArray);
    
end
perfRatio=[];
cost=[];
for ii=1:7
    perfRatio=[perfRatio, double(resArray.gcc(ii).results.simulatedCycles)];
    cost=[cost,resArray.gcc(ii).results.cost.total];
end
[costY,costI]=sort(cost);
perfRatioY=perfRatio(costI);

displayPerfPerDollar(list,resArray);