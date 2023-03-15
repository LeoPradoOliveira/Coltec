package Chat;

import java.io.InputStream;
import java.util.Scanner;

public class Recebedor implements Runnable {

    private InputStream servidor;

    public Recebedor(InputStream servidor) {
        this.servidor = servidor;
    }

    @Override
    public void run() {
        // recebe msgs do servidor e imprime na tela
        Scanner s = new Scanner(this.servidor);
        while (s.hasNextLine()) {
            System.out.println(s.nextLine());
        }
        s.close();
    }
}
