module F = Format
module M = Map.Make(String)

let add (n1 :Value.t) (n2 :Value.t) : Value.t =
match n1, n2 with
| NumV i1, NumV i2 -> NumV (i1+i2)

let sub (n1 :Value.t) (n2 :Value.t) : Value.t =
match n1, n2 with
| NumV i1, NumV i2 -> NumV (i1-i2)

let rec interp_expr (e: Ast.expr) (g: FStore.t) (s: Store.t) : Value.t = 
    match e with
    | Num n -> NumV n
    | Add (e1,e2) -> add (interp_expr e1 g s) (interp_expr e2 g s)
    | Sub (e1,e2) -> sub (interp_expr e1 g s) (interp_expr e2 g s)
    | Id x -> (try M.find x s with Not_found -> failwith ("Free identifier: " ^ x ))
    | LetIn (x, e1, e2) -> interp_expr e2 g (M.add x (interp_expr e1 g s) s)
    | Call (x, el) -> (try 
        match M.find x g with
        |(pl, e) -> (try interp_expr e g ((List.combine pl (List.map(fun e -> interp_expr e g s) el)) |> List.to_seq |> M.of_seq)
        with Invalid_argument _-> failwith ("The number of arguments of "^ x ^" mismatched: Required: " ^ string_of_int (List.length pl) ^ ", Actual: " ^ string_of_int (List.length el)))
        with Not_found -> failwith ("Undefined function: " ^ x ))
        

let interp_fundef (d: Ast.fundef) (g: FStore.t) : FStore.t = 
    match d with
    | FunDef (x, pl, e) -> M.add x (pl,e) g

let rec addg (g:FStore.t) (dl: Ast.fundef list) : FStore.t = 
    match dl with
    | [] -> g
    | hd::tl -> addg (interp_fundef hd g) tl

let interp (p: Ast.prog) : Value.t =
    let total_g = M.empty in
    let total_s = M.empty in
    match p with
    | Prog ([],e) -> interp_expr e total_g total_s
    | Prog (dl,e) -> interp_expr e (addg total_g dl) total_s

