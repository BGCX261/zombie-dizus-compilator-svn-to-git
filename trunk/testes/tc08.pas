program tc08;
vars i,j,k:integer;
procedure teste1(p1par1,p1par2:integer;p1par3:boolean);
        procedure teste11(p11par1:integer);
		begin
			i:=i*1;
                        j:=j*p11par1;
			k:=k*1
		end;
	begin
		i:=i+1;
                teste11(i);
		k:=k+1
	end;
procedure teste2(k:boolean);
	begin
		i:=i-1;
		if k then j:=j-1;
		k:=k or true
	end;
begin
	i:=1;j:=1;k:=1;
	if (i<11)
	then begin
		teste1(1,2,false);
        end;
	if not(j<=k)
	then begin
		if (i + j)>5 then teste2(i>j)
	end
	else begin
		if j>0 then teste1(i+1,i+2,j<3)
		else teste2(0=0)
	end;
        if 3=4 then
        begin
        end
end.
