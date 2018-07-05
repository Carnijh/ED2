package Compressores;

import java.util.PriorityQueue;

public class Huffman {

    public void Constroitabela(String nome, int Alfabeto) {//costroi a tabela de frequencias dada uma string e o tamanho do alfabeto
        int[] freq = new int[Alfabeto];
        for (char c : nome.toCharArray()) {
            freq[c]++;
        }
    }

    public static ArvoreHuff ConstroiArvore(int[] frequencias) {//constroi a arvore de prefixo
        PriorityQueue<ArvoreHuff> arvores = new PriorityQueue<>();
        for (int i = 0; i < frequencias.length; i++) {//cria e insere folhas soltas em uma fila de prioridade
            if (frequencias[i] > 0) {
                arvores.offer(new FolhaHuff(frequencias[i], (char) i));
            }
        }
        assert arvores.size() > 0;        
        while (arvores.size() > 1) {// loop ate que so reste uma arvore
            // separa as duas arvores com a menor Frequencia
            ArvoreHuff a = arvores.poll();
            ArvoreHuff b = arvores.poll();
            // coloca em um novo no e re-insere na lista da arvores 
            arvores.offer(new NoHuff(a, b));
        }
        return arvores.poll();
    }

    public static void Imprime(ArvoreHuff arv, StringBuffer prefixo) {// imprime a arvore de codificação
        assert arv != null;
        if (arv instanceof FolhaHuff) {
            FolhaHuff folha = (FolhaHuff) arv;
            System.out.println(folha.getValor() + "\t" + folha.getFrequencia() + "\t" + prefixo);
        } else if (arv instanceof NoHuff) {
            NoHuff node = (NoHuff) arv;
            prefixo.append('0');
            Imprime(node.getEsq(), prefixo);
            prefixo.deleteCharAt(prefixo.length() - 1);
            prefixo.append('1');
            Imprime(node.getDir(), prefixo);
            prefixo.deleteCharAt(prefixo.length() - 1);
        }
    }
}
