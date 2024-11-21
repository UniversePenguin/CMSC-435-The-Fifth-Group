function FV=FEGS(data)
[P,V]=coordinate;
s=fastaread(strcat(num2str(data),'.fasta'));
data={s(:).Sequence};
l=length(data);
parfor i=1:l

    fprintf('Starting %d\n', i);

    g_p{i}=GRS(data{i},P,V);
    for u=1:158
        EL(i,u)=ME(g_p{i}{u});
    end

    fprintf('Finished %d\n', i);
end
char='ARNDCQEGHILKMFPSTWYV';
display('Done with matrices')
parfor i=1:l
    [AAC,DIC]=SAD(data{i},char);
    FA(i,:)=AAC';
    FD(i,:)=DIC(:)';
    display(i);
end
FV=[EL FA FD];