function results=parseCacheRes(file)
    fd=fopen(file);
    fgetl(fd);
    fgetl(fd);
    fgetl(fd);
    fgetl(fd);

    %DCache Memory Config
    out = textscan(fd,'   Dcache size = %u64 : ways = %u64 : block size = %u64');
    results.memSys.l1d.size=out{1};
    results.memSys.l1d.ways=out{2};
    results.memSys.l1d.blocksize=out{3};
    %ICache Memory Config
    out = textscan(fd,'   Icache size = %u64 : ways = %u64 : block size = %u64');
    results.memSys.l1i.size=out{1};
    results.memSys.l1i.ways=out{2};
    results.memSys.l1i.blocksize=out{3};
    %L2 Cache Memory Config
    out = textscan(fd,'   L2-cache size = %u64 : ways = %u64 : block size = %u64');
    results.memSys.l2.size=out{1};
    results.memSys.l2.ways=out{2};
    results.memSys.l2.blocksize=out{3};
    
    %Memory Config
    out = textscan(fd,'   Memory ready time = %u64 : chunksize = %u64 : chunktime = %u64');
    results.memSys.mem.readyTime=out{1};
    results.memSys.mem.chunksize=out{2};
    results.memSys.mem.chunktime=out{3};
    
    
    %Overall
    out = textscan(fd,'Execute time = %u64     Total Refs = %u64');
    results.execTime=out{1};
    results.refs.total=out{2};
    out = textscan(fd,'Instruction Refs = %u64     Data Refs = %u64');
    results.refs.inst=out{1};
    results.refs.data=out{2};
    
    fgetl(fd);
    
    %Instruction Count
    out = textscan(fd,'Loads (L) = %u64    %*s   :   Stores (S) = %u64\t%*s');
    results.numInst.load=out{1};
    results.numInst.store=out{2};
    out = textscan(fd,'Branch (B) = %u64    %*s   :   Computation (C) = %u64\t%*s');
    results.numInst.branch=out{1};
    results.numInst.computation=out{2};
    out = textscan(fd,'   Total = %u64');
    results.numInst.total=out{1};
    
    fgetl(fd);
    %Cycle COunt
    out = textscan(fd,'Loads (L) = %u64    %*s   :   Stores (S) = %u64\t%*s');
    results.cycles.load=out{1};
    results.cycles.store=out{2};
    out = textscan(fd,'Branch (B) = %u64    %*s   :   Computation (C) = %u64\t%*s');
    results.cycles.branch=out{1};
    results.cycles.computation=out{2};
    out = textscan(fd,'   Total = %u64');
    results.cycles.total=out{1};
    
    fgetl(fd);
    %CPI
    out = textscan(fd,'   Loads (L) = %f      :   Stores (S) = %f');
    results.cpi.load=out{1};
    results.cpi.store=out{2};
    out = textscan(fd,'   Branch (B) = %f     :   Computation (C) = %f');
    results.cpi.branch=out{1};
    results.cpi.computation=out{2};
    out = textscan(fd,'   Overall = %f');
    results.cpi.total=out{1};
    
    out = textscan(fd,'Cycles for processor w/perfect memory system %u64 ');
    results.perfectCycles=out{1};
    out = textscan(fd,'simulated memory system %u64');
    results.simulatedCycles=uint64(out{1});
    
    fgetl(fd);
    fgetl(fd);
    fgetl(fd); % Ratio
    %Hit Miss Stats
    out = textscan(fd,'   Hit Count = %u64     Miss Count = %u64   Total Request = %u64');
    results.stat.l1i.hit=out{1};
    results.stat.l1i.miss=out{2};
    results.stat.l1i.total=out{3};
    fgetl(fd); % Hit/miss Rate
    out = textscan(fd,'   Kickouts : %u64   Dirty Kickouts : %u64  Transfers : %u64');
    results.stat.l1i.kickouts=out{1};
    results.stat.l1i.dirtykickouts=out{2};
    results.stat.l1i.transfers=out{3};
    
    fgetl(fd);
    out = textscan(fd,'   Hit Count = %u64     Miss Count = %u64   Total Request = %u64');
    results.stat.l1d.hit=out{1};
    results.stat.l1d.miss=out{2};
    results.stat.l1d.total=out{3};
    fgetl(fd); % Hit/miss Rate
    out = textscan(fd,'   Kickouts : %u64   Dirty Kickouts : %u64  Transfers : %u64');
    results.stat.l1d.kickouts=out{1};
    results.stat.l1d.dirtykickouts=out{2};
    results.stat.l1d.transfers=out{3};
    
    fgetl(fd);
    out = textscan(fd,'   Hit Count = %u64     Miss Count = %u64   Total Request = %u64');
    results.stat.l2.hit=out{1};
    results.stat.l2.miss=out{2};
    results.stat.l2.total=out{3};
    fgetl(fd); % Hit/miss Rate
    out = textscan(fd,'   Kickouts : %u64   Dirty Kickouts : %u64  Transfers : %u64');
    results.stat.l2.kickouts=out{1};
    results.stat.l2.dirtykickouts=out{2};
    results.stat.l2.transfers=out{3};
    
    
    out = textscan(fd,'L1 cache cost (Icache $%*u64) + (Dcache $%*u64) = $%u64');
    results.cost.l1=out{1};
    
    out = textscan(fd,'2 cache cost = $%u64');
    results.cost.l2=out{1};
    out = textscan(fd,'Memory cost = $%u64');
    results.cost.mem=out{1};
    out = textscan(fd,'Total cost = $%u64');
    results.cost.total=out{1};
    fclose(fd);
end