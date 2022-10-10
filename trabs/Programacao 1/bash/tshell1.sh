#!/bin/bash

path=/home/html/inf/cursos/ci1001/tshell1/
cd $path 2>&1

# função que procura arquivo que não é diretorio nem vazio
# caso não é diretório (-f) nem vazio (-s) ele escreve o nome do arquivo
function acha_n_vazio_n_dir() {
	for line in $(ls)
        do
                if [ ! -d $line ] && [ -s $line ]
                then
			echo $line
		fi
	done
}

# lê o que está escrito na linha 3 e coluna 2 de PISTA1
var1=$(cat PISTA1 -n | grep 3 | cut -d '|' -f2)

# decodifica o conteúdo do arquivo que a var1 armazena o nome
var2=$(cat $var1 | base64 --decode)

# mostra conteúdo do arquivo cujo nome está armazenado em var2
var3=$(cat "$var2")

# conta a quantidades de linhas do arquivo cujo nome está armazenado em var3
tmp=$(cat ./${var3} | wc -l)

# encontra arquivo com tamanho igual a quantidade de linhas contabilizado anteriormente em tmp (em bytes)
var4=$(cat $(find $path -size ${tmp}c 2>/dev/null))

# escreve um alias no arquivo .bashrc onde desloca 13 caracteres no conteúdo da var4
echo "alias rot13='echo $var4 | tr '[a-z]' '[n-za-m]'' " >> ~/.bashrc

# roda .bashrc e armazena o resultado do alias criado 
source ~/.bashrc
var5=.$(rot13)

echo $var5

cd $var5 

# encontra diretório com permissão de escrita para "outros"
tmp=$(ls -l | cut -c9- | grep '^w' | cut -s -d" " -f10)

cd $tmp

# chama função e armazena valor do conteúdo do arquivo encontrado na var6
tmp=$(acha_n_vazio_n_dir)
var6=$(cat $tmp)

# troca caracteres 
coordenadas=$(echo $var6 | tr 'i' '1' | tr 's' '5' | tr 'o' '0' | tr 'e' '3' | tr '^' 'N' | tr '_' 'S' | tr '>' 'E' | tr '<' 'W' ) 

echo Coordenadas do tesouro: $coordenadas
