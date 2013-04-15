function displayCPI(prog, resArray)
    configNames={'Base','L12W','L22W','All2W','2W/4W'...
        ,'L2B','AllFA'};
    figure
    hold on
    cpiAll = [];
    for i=1:7
       cpi = [resArray.(prog)(i).results.cpi.load,...
              resArray.(prog)(i).results.cpi.store,...
              resArray.(prog)(i).results.cpi.branch,...
              resArray.(prog)(i).results.cpi.computation,...
              resArray.(prog)(i).results.cpi.total];
       cpiAll = [cpiAll; cpi];
    end    
    bar(cpiAll)
    title([prog, ' CPI for each configuration'])
    ylabel('CPI')
    xlabel('Configuration')
    legend('Load','Store','Branch','Computation','Overall');
       
    set(gca,'XTick',1:7,'xticklabel',configNames)
end