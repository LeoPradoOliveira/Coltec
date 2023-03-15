package Buchin.Cheio;

import java.util.LinkedList;
public class Cardapio {
    //Atributos
    private LinkedList<Produto> produtos = new LinkedList<Produto>();

    //Getters & Setters
    public LinkedList<Produto> getProdutos() {
        return produtos;
    }

    public void setProdutos(LinkedList<Produto> produtos) {
        this.produtos = produtos;
    }

    //Métodos
    public void addProduto(String nome, double preco, boolean ehBebida){
        Produto p = new Produto();
        produtos.add(p);
        this.produtos.getLast().setNome(nome);
        this.produtos.getLast().setPreco(preco);
        this.produtos.getLast().setBebida(ehBebida);
        this.produtos.getLast().setCodigo(this.produtos.size());
    }

    public void removeProduto(int codigo){
        if(codigo-1 <= this.produtos.size() && codigo > 0){
            this.produtos.remove(codigo-1);
            for(int i = 0; i < this.produtos.size(); i++){
                this.produtos.get(i).setCodigo(i + 1);
            }
        }
        else{
            System.out.println("Não existe um produto com tal código");
        }
    }

    public void listar(){
        System.out.println("Cardápio");
        for(int i = 0; i < this.produtos.size(); i++){
            System.out.printf("[" + this.produtos.get(i).getCodigo() + "] " + this.produtos.get(i).getNome() + " = %.2f R$\n", this.produtos.get(i).getPreco());
        }
        System.out.println();
    }



    //Cria cardápio default
    public void geraCardapio(){
        addProduto("Porção de arroz",12.00, false);
        addProduto("Costela de porco",50.00, false);
        addProduto("Isca de filé de tilápia",59.90, false);
        addProduto("Caldo de feijão",14.99, false);
        addProduto("Porção de fritas",25.00, false);
        addProduto("Pizza média",48.00, false);
        addProduto("Pizza Grande",53.00, false);
        addProduto("Pizza gigante",58.00, false);
        addProduto("Petit gateau",25.00, false);                    
        addProduto("Coca-Cola 2L",12.00, true);
        addProduto("Guaraná 2L",11.00, true);
        addProduto("Suco natural",10.00, true);
        addProduto("Água com gás",2.50, true);
        addProduto("Água sem gás",2.00, true);
    }

}