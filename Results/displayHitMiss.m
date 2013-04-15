function cache=displayHitMiss(prog,resArray)
    configNames={'Base','L12W','L22W','All2W','2W/4W'...
        ,'L2B','AllFA'};
    
    cache={[],[],[]};

    for i=1:7
      cache{1}=[cache{1};resArray.(prog)(i).results.stat.l1i.hit...
                resArray.(prog)(i).results.stat.l1i.miss...
                resArray.(prog)(i).results.stat.l1i.total];
        cache{2}=[cache{2};resArray.(prog)(i).results.stat.l1d.hit...
            resArray.(prog)(i).results.stat.l1d.miss...
            resArray.(prog)(i).results.stat.l1d.total];
        cache{3}=[cache{3};resArray.(prog)(i).results.stat.l2.hit...
            resArray.(prog)(i).results.stat.l2.miss...
            resArray.(prog)(i).results.stat.l2.total];
%        bar(i,resArray.(prog)(i).results.execTime)

    end
cachename={'L1I','L1D','L2'};
for i=1:3
    figure
    subplot(3,2,1:2)
    bar(cache{i}(:,1))
    title([prog,' - ',cachename{i}, ' :   Hit count Per Configuration'])
    ylabel('Hit Count')
	xlabel('Configuration')
    set(gca,'XTick',1:7,'xticklabel',configNames)
%     legend('Hit Count')
    
    subplot(3,2,3:4)
    bar(cache{i}(:,2))
 
    title([prog,' - ',cachename{i}, ' :   Miss count Per Configuration'])
    ylabel('Miss Count')
	xlabel('Configuration')
    set(gca,'XTick',1:7,'xticklabel',configNames)
%     legend('Miss Count')
    
    subplot(3,2,5:6)
    bar(cache{i}(:,3))
    title([prog,'-',cachename{i}, ':Total count Per Configuration'])
    ylabel('Total References')
	xlabel('Configuration')
    set(gca,'XTick',1:7,'xticklabel',configNames)
    suptitle(['Hit/Miss/Total for ',cachename{i}])
%     legend('Total References')
end

