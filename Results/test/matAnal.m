files = dir('*.txt');
resArray(length(files)).results=resultsStruct();
for i = 1:size(files),
    fname = files(i).name;
    fnametokens = textscan(fname,'%d%s%s%s','Delimiter','.');
    
    tracename = char(fnametokens{2}(1));
        
    configname = char(fnametokens{3}(1));
    confignum = textscan(configname,'gz_config_%d');
    confignum = confignum{1};
    
    resArray(i).results=parseCacheRes(fname);
end
