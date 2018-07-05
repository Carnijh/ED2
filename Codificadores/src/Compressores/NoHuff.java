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
public class NoHuff extends ArvoreHuff {//Nos intermediarios

    private final ArvoreHuff esq, dir; // subarvores

    public NoHuff(ArvoreHuff l, ArvoreHuff r) {
        super(l.getFrequencia() + r.getFrequencia());
        esq = l;
        dir = r;
    }

    public ArvoreHuff getEsq() {
        return esq;
    }

    public ArvoreHuff getDir() {
        return dir;
    }
}
