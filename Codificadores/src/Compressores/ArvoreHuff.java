/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Compressores;

/**
 *
 * @author ylhal
 */
abstract class ArvoreHuff implements Comparable<ArvoreHuff> {

    private final int frequencia; // frequencia da arvore

    public ArvoreHuff(int freq) {//construtor
        frequencia = freq;
    }

    // compara as frequencias frequencia
    @Override
    public int compareTo(ArvoreHuff arv) {
        return frequencia - arv.frequencia;
    }

    public int getFrequencia() {
        return frequencia;
    }
}
