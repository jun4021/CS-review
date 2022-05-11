import java.io.IOException;
import org.antlr.v4.runtime.*;

public class program {

    public static void main(String[] args) throws IOException {
                
        // Get Lexer
        ExprLexer lexer = new ExprLexer(CharStreams.fromStream(System.in));
        
        // Get a list of matched tokens
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        // Pass tokens to parser
        ExprParser parser = new ExprParser(tokens);
        BuildAstVisitor buildVisitor = new BuildAstVisitor();
        buildVisitor.visitProg(parser.prog());

        // root node
        AstNodes root = buildVisitor.root;
        // Call AST
        AstCall TreeCall = new AstCall();
        TreeCall.call(root,0);
        // Calculate result
        Evaluate res = new Evaluate();
        System.out.println(res.evaluate(root));
    }
}
