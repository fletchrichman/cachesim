function displayExecTime(prog,resArray)
    configNames={'Base','L12W','L22W','All2W','2W/4W'...
        ,'L2B','AllFA'};
    figure
    hold on
    for i=1:7
       configname=['config',num2str(i)];
       bar(i,resArray.(prog)(i).results.execTime)
       title([prog, ' Execute Time Per Configuration'])
       ylabel('Execute Time')
       xlabel('Configuration')
    end
    set(gca,'XTick',1:7,'xticklabel',configNames)
    
    
end