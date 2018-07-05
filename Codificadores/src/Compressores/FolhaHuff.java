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
public class FolhaHuff extends ArvoreHuff {//Nos folhas contendo informação

    private final char valor; // caracter representado

    public FolhaHuff(int freq, char val) {//construtor
        super(freq);
        valor = val;
    }

    public char getValor() {
        return valor;
    }
}
