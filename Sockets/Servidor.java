import java.io.IOException;
import java.net.*;
import java.util.Scanner;

public class Servidor {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(6969);
        System.out.println("Servidor aberto, porta: 6969");

        Socket cliente = server.accept();
        System.out.println(cliente.getInetAddress().getHostAddress() + " entrou no chat");

        Scanner bufferIn = new Scanner(cliente.getInputStream());
        while(bufferIn.hasNextLine()){
            System.out.println(bufferIn.nextLine());
        }

        bufferIn.close();
        System.out.println("Conexão com " + cliente.getInetAddress().getHostAddress() + " perdida");
        cliente.close();
        server.close();
        System.out.println("Servidor fechado");
    }
}