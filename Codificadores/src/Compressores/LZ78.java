/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Compressores;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author ylhal
 */
public class LZ78 {

    List<String> dicionario;

    public LZ78() {
        dicionario = new ArrayList<>();
        dicionario.add(null);
    }

    public List<Character> codificarInt(List<Integer> listaString) {
        String cod = "";
        List<Character> Lista = new ArrayList<>();
        String letra = "";
        boolean x = false;
        int pos = 0;
        for (int i = 0; i <= listaString.size() + 1; i++) {
            int val = listaString.get(i);
            letra += (char) val;
            if (!dicionario.contains(letra)) {
                dicionario.add(letra);
                cod += 0;
                Lista.add('0');
                cod += letra;
                char paso = letra.charAt(0);
                Lista.add(paso);
                letra = "";
            } else {
                while (dicionario.contains(letra)) {
                    i++;
                    if (i >= listaString.size()) {
                        x = true;
                        if (!dicionario.contains(letra)) {
                            Lista.add('0');
                            char paso2 = letra.charAt(0);
                            Lista.add(paso2);
                        } else {
                            int index = dicionario.indexOf(letra);
                            String paso3 = "" + index;
                            for (int j = 0; j < paso3.length(); j++) {
                                Lista.add(paso3.charAt(j));
                            }
                        }
                        break;
                    }
                    pos = dicionario.indexOf(letra);
                    val = listaString.get(i);
                    letra += (char) val;
                }
                if (x) {
                    break;
                }
                i++;
                dicionario.add(letra);
                letra = "" + letra.charAt(letra.length() - 1);
                cod += pos;
                String numero = "" + pos;
                for (int j = 0; j < numero.length(); j++) {
                    Lista.add(numero.charAt(j));
                }
                cod += letra;
                char paso = letra.charAt(0);
                Lista.add(paso);
                letra = "";
                i--;
            }
        }
        System.out.println(cod);
        return Lista;
    }

    public List<Character> codificarString(List<String> listaString) {
        
    }
}
