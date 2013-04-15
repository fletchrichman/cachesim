function results=resultsStruct()
    %DCache Memory Config
    results.memSys.l1d.size=[];
    results.memSys.l1d.ways=[];
    results.memSys.l1d.blocksize=[];
    %ICache Memory Config
    results.memSys.l1i.size=[];
    results.memSys.l1i.ways=[];
    results.memSys.l1i.blocksize=[];
    %L2 Cache Memory Config
    results.memSys.l2.size=[];
    results.memSys.l2.ways=[];
    results.memSys.l2.blocksize=[];
    
    %Memory Config
    results.memSys.mem.readyTime=[];
    results.memSys.mem.chunksize=[];
    results.memSys.mem.chunktime=[];
    
    %Overall
    results.execTime=[];
    results.refs.total=[];
    results.refs.inst=[];
    results.refs.data=[];
    
    %Instruction Count
    results.numInst.load=[];
    results.numInst.store=[];
    results.numInst.branch=[];
    results.numInst.computation=[];
    results.numInst.total=[];
    
    %Cycle COunt
    results.cycles.load=[];
    results.cycles.store=[];
    results.cycles.branch=[];
    results.cycles.computation=[];
    results.cycles.total=[];
    
    %CPI
    results.cpi.load=[];
    results.cpi.store=[];
    results.cpi.branch=[];
    results.cpi.computation=[];
    results.cpi.total=[];
    
    results.perfectCycles=[];
    results.simulatedCycles=[];
    
    %Hit Miss Stats
    results.stat.l1i.hit=[];
    results.stat.l1i.miss=[];
    results.stat.l1i.total=[];
    results.stat.l1i.kickouts=[];
    results.stat.l1i.dirtykickouts=[];
    results.stat.l1i.transfers=[];
    
    results.stat.l1d.hit=[];
    results.stat.l1d.miss=[];
    results.stat.l1d.total=[];
    results.stat.l1d.kickouts=[];
    results.stat.l1d.dirtykickouts=[];
    results.stat.l1d.transfers=[];
    
    results.stat.l2.hit=[];
    results.stat.l2.miss=[];
    results.stat.l2.total=[];
    results.stat.l2.kickouts=[];
    results.stat.l2.dirtykickouts=[];
    results.stat.l2.transfers=[];
    
    results.cost.l1=[];
    results.cost.l2=[];
    results.cost.mem=[];
    results.cost.total=[];
end