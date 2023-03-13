public class ComandaComida extends Comanda{

    @Override
    public void fechaComanda(){
        if(this.consumo == null) {
            System.out.println("Nenhuma comida foi consumida");
        }

        else{
            System.out.print("| Consumo de comidas:\n" + this.consumo);
            System.out.printf("| Valor das comidas: %.2f R$\n", this.valor);
        }
    }
}
