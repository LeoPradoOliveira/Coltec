import java.io.IOException;
import java.io.PrintStream;
import java.net.*;
import java.util.Scanner;

public class Cliente {
    public static void main(String[] args) throws UnknownHostException, IOException {
        String nick;

        Socket cliente = new Socket("127.0.0.1", 6969);
        System.out.println("Conectado com sucesso!");
        Scanner teclado = new Scanner(System.in);
        System.out.print("Qual será seu nick: ");
        nick = teclado.nextLine();
        
        PrintStream saida = new PrintStream(cliente.getOutputStream());

        while (teclado.hasNextLine()) {
            saida.println(nick + ": " + teclado.nextLine());
        }

        saida.close();
        teclado.close();
        cliente.close();
    }

    
}
