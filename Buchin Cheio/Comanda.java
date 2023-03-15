package Buchin.Cheio;
public abstract class Comanda {
    //Atributos
    protected String consumo;
    protected double valor;

    //Getters & Setters
    public String getConsumo() {
        return consumo;
    }
    public double getValor() {
        return valor;
    }
    public void setConsumo(String consumo) {
        if(this.consumo == null) this.consumo = "| " + consumo + "\n";

        else this.consumo += "| " + consumo + "\n";
    }
    public void setValor(double valor) {
        if(this.valor == 0) this.valor = valor;
        else this.valor += valor;
    }

    public abstract void fechaComanda();
}