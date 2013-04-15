function displayPerfPerDollar(proglist,resArray)
    configNames={'Base','L12W','L22W','All2W','2W/4W'...
        ,'L2B','AllFA'};
    
    figure
    hold on
    metric=[];
    for j=1:7
        for i=1:6
           ratio = double(resArray.(proglist{i})(j).results.simulatedCycles) / ...
                   double(resArray.(proglist{i})(j).results.perfectCycles);
           metric(i,j)=((1/ratio)./double(resArray.(proglist{i})(j).results.cost.total));
        end
    end
    bar(metric)
    set(gca,'XTick',1:6,'xticklabel',proglist)
    legend(configNames)
    title('Performance/cost for each configuration')
    ylabel('(Perfect/Simulated)Cycles/Dollar')
    
end