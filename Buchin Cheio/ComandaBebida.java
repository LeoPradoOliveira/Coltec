public class ComandaBebida extends Comanda{

    @Override
    public void fechaComanda(){
        if(this.consumo == null) {
            System.out.println("Nenhuma bebida foi consumida");
        }

        else{
            System.out.print(  "| Consumo de bebidas:\n" + this.consumo);
            System.out.printf("| Valor das bebidas: %.2f R$\n", this.valor);
        }
    }
}