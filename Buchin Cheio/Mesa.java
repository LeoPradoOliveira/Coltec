import java.util.LinkedList;

public class Mesa {
    // Atributos
    private int numeroMesa;
    private String data;
    private boolean reserva; // True para reservado, False para o contrário
    private ComandaBebida bebidas;
    private ComandaComida comidas;

    private LinkedList<Cliente> clientes = new LinkedList<Cliente>();

    // Getters & Setters
    public int getNumeroMesa() {
        return numeroMesa;
    }

    public void setNumeroMesa(int numeroMesa) {
        this.numeroMesa = numeroMesa;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public boolean isReserva() {
        return reserva;
    }

    public void setReserva(boolean reserva) {
        this.reserva = reserva;
    }

    public ComandaBebida getBebidas() {
        return bebidas;
    }

    public void setBebidas(ComandaBebida bebidas) {
        this.bebidas = bebidas;
    }

    public ComandaComida getComidas() {
        return comidas;
    }

    public void setComidas(ComandaComida comidas) {
        this.comidas = comidas;
    }

    public LinkedList<Cliente> getClientes() {
        return clientes;
    }

    public void setClientes(LinkedList<Cliente> clientes) {
        this.clientes = clientes;
    }

    // Métodos
    public void listarConsumo() {
        System.out.print("| Consumo da mesa " + this.numeroMesa + "\n" + this.bebidas.getConsumo() + this.comidas.getConsumo());
    }

    public double calcular10porcento() {
        return (this.bebidas.getValor() + this.comidas.getValor())/ 10;
    }

    public double dividirConta() {
        return (this.bebidas.getValor() + this.comidas.getValor())/ this.clientes.size();
    }

    public void adicionaClientes(int nClientes) {
        for (int i = 0; i < nClientes; i++) {
            Cliente c = new Cliente();
            clientes.add(c);
        }
    }

    // Exclusões
    public void excluiComanda() {
        this.bebidas = null;
        this.comidas = null;
    }

    public void excluiClientes() {
        this.clientes.clear();
    }
}
