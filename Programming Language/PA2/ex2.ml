let prime n =
    let rec divide n div = 
            match div with
            | 1 -> true    
            | _ -> (n mod div <> 0) && divide n (div-1)
    in match n with
    | 0 | 1 -> false
    | _ -> divide n (n-1)

in
Format.printf "prime 2 => %b\n" (prime 2);
Format.printf "prime 3 => %b\n" (prime 3);
Format.printf "prime 4 => %b\n" (prime 4);
Format.printf "prime 17 => %b\n" (prime 17);
