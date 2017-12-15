close all;
clear all;


[sf, Fs] = audioread('4notas.wav'); %SF recebe o sinal e FS recebe a taxa de amostragem (frequencia)
Ts = 1/Fs; %TS eh o periodo do sinal recebido.

dt = [0:Ts: (length(sf)/Fs)-Ts]; %dt e a duraçao do audio, que vai de zero a N-TS segundos, a passos de TS em TS 

flag1 = 111;
flag2 = 222222;

k = 1;
        nfft = length(sf);   %aqui dizemos quantas amostras de S temos.
        nfft2 = 2^nextpow2(nfft);   %aqui dizemos quantas possibilidades diferentes de frequencias temos, de acordo com o tamanho de S.

for a = 1 : (columns(dt))
    s(k) = sf(a);
    if(k == Fs)
        k = 0;
        
        ff = fft(s, nfft2);   %aqui calculamos a transformada rapida de fourier do sinal de comprimento nfft2, e retornamos os coeficientes para FF.
        fff = ff(1:(nfft2/2)); %aqui pegamos ate metade do intervalo, para retirar a parte espelhada.
        fff = fff/max(fff);     %aqui normalizamos o eixo das intensidades, de forma que o maior valor seja 1 e os restantes sejam porcentagens deste.
        xfft = Fs*(0:nfft2/2-1)/nfft2;   %aqui estamos normalizando o eixo das frequencias
        
        [pks idx] = findpeaks(abs(fff));  %aqui pegamos todos os picos positivos, ou seja, todos os maiores coreficientes.
        idx = Fs*(idx/nfft2);     %aqui pegamos todas as frequencias para essa quantidade de picos
        
       
        figure
        plot(xfft,abs(fff));
        figure
        stem(idx,pks);
        
        
        pkstxt = "pks.txt";
        pksFile = fopen(pkstxt, "a");
        
        idxtxt = "idx.txt";
        idxFile = fopen(idxtxt, "a");
        
        for i = 1: length(pks)
          fprintf(pksFile, '%.5f\n', pks(i));
        endfor
        fprintf(pksFile, '%.5f\n', flag1);
        fclose(pksFile);
        
        for i = 1: length(idx)
          fprintf(idxFile, '%.5f\n', idx(i));
        endfor
        fprintf(idxFile, '%.5f\n', flag2);
        fclose(idxFile);
        endif
      a++;
      k++;
endfor
for i = 1: (columns(dt))
  s(i) = sf(i);     %copiamos a matriz que contem o sinal para um vetor que guardara todos os valores do sinal no intervalo de duracao DT
endfor

