/*

Calculate The Input String
And Return the result

*/

import static java.lang.Math.*;

// ADD MUL SUB DIV ASSIGN min max pow sqrt
class Evaluate {
    public Double evaluate(AstNodes node){
        Double result;
        switch (node.op) {
            case "ADD":
                result = evaluate(node.left) + evaluate(node.right);
                break;
            case "MUL":
                result = evaluate(node.left) * evaluate(node.right);
                break;
            case "SUB":
                result = evaluate(node.left) - evaluate(node.right);
                break;
            case "DIV":
                result = evaluate(node.left) / evaluate(node.right);
                break;
            case "ASSIGN":
                result = 0.0;
                break;
            case "min":
                result = min(evaluate(node.left), evaluate(node.right));
                break;
            case "max":
                result = max(evaluate(node.left), evaluate(node.right));
                break;
            case "pow":
                result = pow(evaluate(node.left), evaluate(node.right));
                break;
            case "sqrt":
                result = sqrt(evaluate(node.left));
                break;
            default:
                result = Double.parseDouble(node.op);

        }
        return result;
    }
}