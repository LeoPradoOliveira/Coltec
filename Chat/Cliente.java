package Chat;

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Cliente {
    private String host;
    private int porta;
    private String name;
    public static void main(String[] args)
            throws UnknownHostException, IOException {
        // dispara cliente
        new Cliente("127.0.0.1", 12345).executa();
    }


    public Cliente(String host, int porta) {
        this.host = host;
        this.porta = porta;
    }

    public void executa() throws UnknownHostException, IOException {
        Socket cliente = new Socket(this.host, this.porta);
        System.out.println("O cliente se conectou ao servidor!");

        Scanner scanf = new Scanner(System.in);
        System.out.print("Qual será seu nick: ");
        this.name = scanf.nextLine();

        // thread para receber mensagens do servidor
        Recebedor r = new Recebedor(cliente.getInputStream());
        new Thread(r).start();

        // lê msgs do teclado e manda pro servidor
        Scanner teclado = new Scanner(System.in);
        PrintStream saida = new PrintStream(cliente.getOutputStream());
        while (teclado.hasNextLine()) {
            saida.println(this.name + ":" + teclado.nextLine());
        }

        saida.close();
        teclado.close();
        cliente.close();
        scanf.close();
    }
}