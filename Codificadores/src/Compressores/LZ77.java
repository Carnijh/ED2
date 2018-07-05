/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Compressores;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 *
 * @author ylhal
 */
public class LZ77 {

    private static int[] makeCharTable(ArrayList<Character> needle) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    private static int[] makeOffsetTable(ArrayList<Character> needle) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    private ArrayList<Character> dicionario;
    private ArrayList<Character> buffer;
    int Nd = 6;
    int Nb = 4;
    int Tam = 0;

    public LZ77() {

    }

    public LZ77(int nd, int nb) {
        Nd = nd;
        Nb = nb;
    }

    public List<Character> Compressao(String texto) {
        int i;
        for (i = 0; i < Nb; i++) {
            buffer.add(texto.charAt(i));
        }
    }

    public List<Character> Insere() {
        List<Character> lista = null;
        lista.add('<');
        if (dicionario.isEmpty()) {
            lista.add('0');
            lista.add('0');
            lista.add(buffer.get(0));
            dicionario.add(buffer.get(0));
            if (Tam < Nd) {
                Tam++;
            } else {
                dicionario.remove(0);
            }
        } else {
            ArrayList copia = buffer;
            for (int i = Nb; i > 0; i++) {
                int pos = indexOf(dicionario, copia);
                if (pos > 0) {
                    lista.add((char) pos);
                    lista.add((char) copia.size());
                    lista.add('>');
                    for (int j = 0; j < copia.size(); j++) {
                        dicionario.remove(0);
                        dicionario.add(buffer.get(j));
                    }
                    return lista;
                }
            }
        }
    }

    public static int indexOf(ArrayList<Character> haystack, ArrayList<Character> needle) {
        if (needle.isEmpty()) {
            return 0;
        }
        int charTable[] = makeCharTable(needle);
        int offsetTable[] = makeOffsetTable(needle);
        for (int i = needle.size() - 1, j; i < haystack.size();) {
            for (j = needle.size() - 1; Objects.equals(needle.get(j), haystack.get(i)); --i, --j) {
                if (j == 0) {
                    return i;
                }
            }
            i += Math.max(offsetTable[needle.size() - 1 - j], charTable[haystack.get(i)]);
        }
        return -1;
    }
}
