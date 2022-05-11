/*

print the Ast that we build in BuildAstVisitor.java

*/


public class AstCall {

    public void call(AstNodes node, Integer depth){
        if(node !=null){
            for(int i =0;i<depth;i++){
                System.out.print("       ");
            }
            System.out.println(node.op);
            call(node.left,depth+1);

            call(node.right,depth+1);
        }
    }
    
}
