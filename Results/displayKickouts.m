function displayKickouts(prog, resArray)
    configNames={'Base','L12W','L22W','All2W','2W/4W'...
        ,'L2B','AllFA'};
    figure
    hold on
    l1iAll = [];
    l1dAll = [];
    l2All = [];
    for i=1:7
       l1i = [resArray.(prog)(i).results.stat.l1i.kickouts,...
              resArray.(prog)(i).results.stat.l1i.dirtykickouts,...
              resArray.(prog)(i).results.stat.l1i.transfers];
       l1iAll = [l1iAll; l1i];
       l1d = [resArray.(prog)(i).results.stat.l1d.kickouts,...
              resArray.(prog)(i).results.stat.l1d.dirtykickouts,...
              resArray.(prog)(i).results.stat.l1d.transfers];
       l1dAll = [l1dAll; l1d];
       l2 = [resArray.(prog)(i).results.stat.l2.kickouts,...
              resArray.(prog)(i).results.stat.l2.dirtykickouts,...
              resArray.(prog)(i).results.stat.l2.transfers];
       l2All = [l2All; l2];
    end  
    
    bar(l1iAll)
    title([prog, ' L1I kickouts/transfers for each configuration'])
    ylabel('kickouts/transfers')
    xlabel('Configuration')
    legend('Kickouts','Dirty Kickouts', 'Transfers');
    
    figure
    
    bar(l1dAll)
    title([prog, ' L1D kickouts/transfers for each configuration'])
    ylabel('kickouts/transfers')
    xlabel('Configuration')
    legend('Kickouts','Dirty Kickouts', 'Transfers');
    
    figure
    
    bar(l2All)
    title([prog, ' L2 kickouts/transfers for each configuration'])
    ylabel('kickouts/transfers')
    xlabel('Configuration')
    legend('Kickouts','Dirty Kickouts', 'Transfers');
    
    
       
    set(gca,'XTick',1:7,'xticklabel',configNames)
end