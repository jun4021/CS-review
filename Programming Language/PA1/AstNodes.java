/*

define Ast Nodes

*/
public class AstNodes {
    AstNodes left;
    AstNodes right;
    String op;


    public AstNodes getLeft() {
        return left;
    }

    public void setLeft(AstNodes left) {
        this.left = left;
    }

    public AstNodes getRight() {
        return right;
    }

    public void setRight(AstNodes right) {
        this.right = right;
    }

    public String getOp() {
        return op;
    }

    public void setOp(String op) {
        this.op = op;
    }

}