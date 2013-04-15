function displayRatio(prog,resArray)
    configNames={'Base','L12W','L22W','All2W','2W/4W'...
        ,'L2B','AllFA'};
    figure
    hold on
    for i=1:7
       ratio = double(resArray.(prog)(i).results.simulatedCycles) / ...
               double(resArray.(prog)(i).results.perfectCycles);
       bar(i,ratio)
       title([prog, ' Performance ratio (simulated/perfect)'])
       ylabel('Performance ratio')
       xlabel('Configuration')
    end
    set(gca,'XTick',1:7,'xticklabel',configNames)
end