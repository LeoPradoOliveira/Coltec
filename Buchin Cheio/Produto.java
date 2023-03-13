public class Produto {
    // Atributos
    private String nome;
    private double preco;
    private int codigo;
    private boolean ehBebida;

    // Getters & Setters
    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public double getPreco() {
        return preco;
    }

    public void setPreco(double preco) {
        this.preco = preco;
    }

    public int getCodigo() {
        return codigo;
    }

    public void setCodigo(int codigo) {
        this.codigo = codigo;
    }

    public boolean isBebida() {
        return ehBebida;
    }
    public void setBebida(boolean bebida) {
        this.ehBebida = bebida;
    }
}