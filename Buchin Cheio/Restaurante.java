package Buchin.Cheio;
import java.util.LinkedList;
import java.util.Scanner;

public class Restaurante {
    // Atributos
    private String nome;
    private String endereco;
    private LinkedList<Mesa> mesas = new LinkedList<Mesa>();
    private Cardapio cardapio = new Cardapio();

    // Construtor
    public Restaurante(String nome, String endereco) {
        this.nome = nome;
        this.endereco = endereco;
    }

    // Getters & Setters
    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEndereco() {
        return endereco;
    }

    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    public void setMesas(LinkedList<Mesa> mesas) {
        this.mesas = mesas;
    }

    // Métodos
    public void adicionaMesas(int n) {
        for (int i = 0; i < n; i++) {
            Mesa m = new Mesa();
            m.setNumeroMesa(this.mesas.size() + 1);
            m.setReserva(false);
            this.mesas.add(m);
        }
    }

    public void removeMesas(int n) {
        for (int i = 0; i < n; i++) {
            if (this.mesas.getLast().getClientes().size() == 0) {
                this.mesas.removeLast();
            }
            this.mesas.getLast().excluiClientes();
            this.mesas.getLast().excluiComanda();
            this.mesas.removeLast();
        }
    }

    // Menu
    public void menu() {
        System.out.println("+-------------------------------+\n"
                + "|   Bem vindo ao Buchin Cheio   |");
        Scanner scanner = new Scanner(System.in);
        char op = '1';
        while (op != '0') {
            System.out.print("+-------------------------------+\n"
                    + "| 0 - Sair                      |\n"
                    + "| 1 - Adicionar mesas           |\n"
                    + "| 2 - Remover mesas             |\n"
                    + "| 3 - Adicionar reserva         |\n"
                    + "| 4 - Fazer um pedido           |\n"
                    + "| 5 - Mostra cardápio           |\n"
                    + "| 6 - Fecha conta               |\n"
                    + "| 7 - Manipula cardápio         |\n"
                    + "| 8 - Gera cardápio default     |\n"
                    + "+-------------------------------+\n");
            op = scanner.next().charAt(0);

            switch (op) {
                case '0': {
                    System.out.println("Fim");

                    break;
                }

                // Adiciona N mesas no restaurante
                case '1': {
                    System.out.print("Quantidade de mesas a serem adicionadas: ");
                    int nMesas = scanner.nextInt();
                    this.adicionaMesas(nMesas);

                    break;
                }

                // Remove N mesas no restaurante
                case '2': {
                    System.out.print("Quantidade de mesas a serem removidas: ");
                    int nMesas = scanner.nextInt();

                    if (nMesas > this.mesas.size()) {
                        nMesas = this.mesas.size();
                        System.out.println("O número digitado excede o atual número de mesas, removendo todas elas");
                    }
                    removeMesas(nMesas);

                    break;
                }

                // Aloca N clientes na mesa e uma comanda para a mesma
                case '3': {
                    System.out.print("Quantidade de clientes da mesa: ");
                    int nClientes = scanner.nextInt();
                    scanner.nextLine(); // Limpador de buffer
                    if (nClientes > 0) {
                        for (int i = 0; i < this.mesas.size(); i++) {
                            if (this.mesas.get(i).isReserva() == false) {
                                this.mesas.get(i).setReserva(true);
                                ComandaBebida b = new ComandaBebida();
                                ComandaComida c = new ComandaComida();
                                this.mesas.get(i).setBebidas(b);
                                this.mesas.get(i).setComidas(c);

                                this.mesas.get(i).adicionaClientes(nClientes);

                                for (int j = 0; j < nClientes; j++) {
                                    System.out.print("Digite o nome do cliente " + (j + 1) + ": ");
                                    String nomeCliente = scanner.nextLine();
                                    this.mesas.get(i).getClientes().get(j).setNome(nomeCliente);

                                    System.out.print("Digite o email do cliente " + (j + 1) + ": ");
                                    String emailCliente = scanner.nextLine();
                                    this.mesas.get(i).getClientes().get(j).setEmail(emailCliente);
                                }
                                System.out.println("Reserva realizada na mesa de código " + i + 1);
                                i = this.mesas.size();

                            } else {
                                if (i + 1 == (this.mesas.size())) {
                                    System.out.println("Não há mesas disponíveis no momento");
                                    i = this.mesas.size();

                                }
                            }
                        }
                    }

                    break;
                }

                // Faz o pedido de um produto na mesa N
                case '4': {

                    System.out.print("Digite o código da mesa: ");
                    int mesa = scanner.nextInt();
                    scanner.nextLine(); // Limpador de buffer
                    if (mesa > this.mesas.size() || mesa < 1) {
                        System.out.println("Tal mesa não existe");
                        break;
                    }

                    if (this.mesas.get(mesa - 1).getBebidas() == null) {
                        System.out.println("Tal mesa não possui comanda");
                        break;
                    }

                    System.out.print("Digite o código do pedido: ");
                    int code = scanner.nextInt();
                    scanner.nextLine(); // Limpador de buffer
                    if (code > this.cardapio.getProdutos().size() || code < 1) {
                        System.out.println("Tal produto não existe");
                        break;
                    }

                    if (this.cardapio.getProdutos().get(code - 1).isBebida()) {
                        this.mesas.get(mesa - 1).getBebidas()
                                .setConsumo(this.cardapio.getProdutos().get(code - 1).getNome());
                        this.mesas.get(mesa - 1).getBebidas()
                                .setValor(this.cardapio.getProdutos().get(code - 1).getPreco());
                    } else {
                        this.mesas.get(mesa - 1).getComidas()
                                .setConsumo(this.cardapio.getProdutos().get(code - 1).getNome());
                        this.mesas.get(mesa - 1).getComidas()
                                .setValor(this.cardapio.getProdutos().get(code - 1).getPreco());
                    }

                    break;
                }

                // Lista o cardápio
                case '5': {
                    this.cardapio.listar();

                    break;
                }

                // Fecha a conta da mesa N
                case '6': {
                    System.out.print("Digite o código da mesa: ");
                    int mesa = scanner.nextInt();
                    scanner.nextLine(); // Limpador de buffer
                    if (mesa > this.mesas.size() || mesa < 1) {
                        System.out.println("Tal mesa não existe");
                        break;
                    }

                    if (this.mesas.get(mesa - 1).getBebidas() == null) {
                        System.out.println("Tal mesa não possui comanda");
                        break;
                    }

                    this.mesas.get(mesa - 1).getBebidas().fechaComanda();
                    System.out.println("+----------------------------------");
                    this.mesas.get(mesa - 1).getComidas().fechaComanda();
                    System.out.println("+----------------------------------");
                    System.out.println("| Total a pagar: " + (this.mesas.get(mesa - 1).getComidas().valor
                            + this.mesas.get(mesa - 1).getBebidas().valor));
                    int o = 0;
                    while (o == 0) {
                        System.out.println("Deseja dividir a conta? [y/n]");
                        char dividir = scanner.next().charAt(0);
                        scanner.nextLine(); // Limpador de buffer

                        if (dividir == 'y' || dividir == 'Y') {
                            System.out.printf("Cada um deve pagar: %.2f R$\n", this.mesas.get(mesa - 1).dividirConta());
                            o += 1;
                        } else if (dividir == 'n' || dividir == 'N') {
                            o += 1;
                        }
                    }

                    this.mesas.get(mesa - 1).excluiClientes();
                    this.mesas.get(mesa - 1).excluiComanda();
                    this.mesas.get(mesa - 1).setReserva(false);
                    System.out.println("Conta paga");

                    break;
                }

                // Manipula o cardápio
                case '7': {
                    System.out.println("0 - Sair \n1 - Adicionar \n2 - Remover Produto");
                    char op2 = scanner.next().charAt(0);
                    switch (op2) {
                        case '0': {
                            break;
                        }
                        case '1': {
                            scanner.nextLine(); // Limpador de buffer
                            System.out.printf("Nome do produto: ");
                            String nomeproduto = scanner.nextLine();

                            System.out.print("Valor, use vírgula para a casa decimal: ");
                            double valorproduto = scanner.nextDouble();

                            int o = 0;
                            while (o == 0) {
                                System.out.print("Digite 1 se for uma bebida, 2 se for uma comida: ");
                                char a = scanner.next().charAt(0);

                                if (a == '1') {
                                    this.cardapio.addProduto(nomeproduto, valorproduto, true);
                                    o += 1;
                                } else if (a == '2') {
                                    this.cardapio.addProduto(nomeproduto, valorproduto, false);
                                    o += 1;
                                }

                            }
                            break;
                        }
                        case '2': {
                            System.out.println("Código do produto: ");
                            int codproduto = scanner.nextInt();
                            this.cardapio.removeProduto(codproduto);
                            break;
                        }
                        default: {
                            System.out.println("Opção inválida");
                            break;
                        }
                    }

                    break;
                }

                // Adiciona um cardápio default
                case '8': {
                    this.cardapio.geraCardapio();
                    System.out.println("Cardápio default adicionado");

                    break;
                }

                // Separa comanda da mesa N por comida e bebida
                case '9': {

                    break;
                }

                default: {
                    System.out.println("Opção inválida");

                    break;
                }

            }
        }
        scanner.close();
    }
}