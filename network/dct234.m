for N=2:4
    for ii = 1:N
        for jj=1:N
            if ii==1
                c(ii,jj)=sqrt(1/N)*cos((2*jj-1)*(ii-1)*pi/2/N);
            else
                c(ii,jj)=sqrt(2/N)*cos((2*jj-1)*(ii-1)*pi/2/N);
            end
        end
    end
    c
end
            
    