/*

Build Ast using the method in MathBaseVisitor.java 
you should override the methods.

*/


public class BuildAstVisitor<T> extends ExprBaseVisitor<AstNodes> {

    AstNodes root = new AstNodes();
    public void CheckRoot(AstNodes node){
        if(this.root.getOp() == null){
            this.root = node;
        }

    }

    public AstNodes visitParensExpr(ExprParser.ParensExprContext ctx) {
        return visit(ctx.children.get(1));
    }

    public AstNodes visitProg(ExprParser.ProgContext ctx) {
        return super.visitProg(ctx);
    }

    public AstNodes visitMaxExpr(ExprParser.MaxExprContext ctx) {
        AstNodes newNode = new AstNodes();
        newNode.setOp("max");
        CheckRoot(newNode);

        newNode.left = visit(ctx.children.get(2));
        newNode.right = visit(ctx.children.get(4));
        return newNode;
    }

    public AstNodes visitInfixExpr(ExprParser.InfixExprContext ctx) {
        AstNodes newNode = new AstNodes();
        String operation = ctx.children.get(1).getText();
        switch (operation){
            case "+":
                operation = "ADD";
                break;
            case "-":
                operation = "SUB";
                break;
            case "*":
                operation = "MUL";
                break;
            case "/":
                operation = "DIV";
                break;

        }
        newNode.setOp(operation);
        CheckRoot(newNode);

        newNode.left = visit(ctx.children.get(0));
        newNode.right = visit(ctx.children.get(2));

        return newNode;

    }

    public AstNodes visitMinExpr(ExprParser.MinExprContext ctx) {

        AstNodes newNode = new AstNodes();
        newNode.setOp("min");
        CheckRoot(newNode);

        newNode.left = visit(ctx.children.get(2));
        newNode.right = visit(ctx.children.get(4));
        return newNode;
    }

    public AstNodes visitSqrtExpr(ExprParser.SqrtExprContext ctx) {
        AstNodes newNode = new AstNodes();
        newNode.setOp("sqrt");
        CheckRoot(newNode);

        newNode.left = visit(ctx.children.get(2));
        return newNode;
    }

    public AstNodes visitNumberExpr(ExprParser.NumberExprContext ctx) {
        AstNodes number = new AstNodes();

        number.setOp(ctx.children.get(0).getChild(0).getText());
        return number;
    }

    public AstNodes visitPowExpr(ExprParser.PowExprContext ctx) {
        AstNodes newNode = new AstNodes();
        newNode.setOp("pow");
        CheckRoot(newNode);

        newNode.left = visit(ctx.children.get(2));
        newNode.right = visit(ctx.children.get(4));
        return newNode;
    }

    public AstNodes visitAssignExpr(ExprParser.AssignExprContext ctx) {
        AstNodes newNode = new AstNodes();
        newNode.setOp("ASSIGN");
        CheckRoot(newNode);

        AstNodes leftNode = new AstNodes();
        leftNode.op = ctx.children.get(0).getText();

        newNode.left = leftNode;
        newNode.right = visit(ctx.children.get(2));
        return newNode;
    }
}
